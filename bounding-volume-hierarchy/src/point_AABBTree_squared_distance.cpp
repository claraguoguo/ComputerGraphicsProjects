#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include <limits>// std::numeric_limits<double>::infinity();

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  sqrd = std::numeric_limits<double>::infinity();
  descendant = NULL;
  double min_dist = std::numeric_limits<double>::infinity();
  auto greater = [](std::pair<double, std::shared_ptr<AABBTree>> node1,
                std::pair<double, std::shared_ptr<AABBTree>> node2) {
                  return node1.first > node2.first;
                };

  std::priority_queue<std::pair<double, std::shared_ptr<AABBTree>>,
                      std::vector<std::pair<double, std::shared_ptr<AABBTree>>>,
                      decltype(greater)> my_queue(greater);

  // Push ROOT node to the queue
  my_queue.emplace(std::make_pair(point_box_squared_distance(query, root->box), root));

  // Loop until the queue is empty
  while (!my_queue.empty()) {
    double curr_dis = my_queue.top().first;
    std::shared_ptr<AABBTree> curr_node = my_queue.top().second;
    my_queue.pop();

    std::shared_ptr<Object> curr_desc;

    if (curr_dis > min_dist) continue; 
    
    if (curr_node->num_leaves <= 2) { // subtree is a leaf
      if (curr_node->left && curr_node->left->point_squared_distance(
         query, min_sqrd, max_sqrd, curr_dis, curr_desc)){
        if (curr_dis < min_dist) { 
          min_dist = curr_dis;
          descendant = curr_node->left;
        }
      }
      if (curr_node->right && curr_node->right->point_squared_distance(
        query, min_sqrd, max_sqrd, curr_dis, curr_desc)){
        if (curr_dis < min_dist) { 
          min_dist = curr_dis;
          descendant = curr_node->right;
        }
      }
    }

    else {
      if (curr_node->left) {
        my_queue.emplace(std::make_pair(
          point_box_squared_distance(query, curr_node->left->box),
          std::static_pointer_cast<AABBTree>(curr_node->left)));
      }
      if (curr_node->right) {
        my_queue.emplace(std::make_pair(
          point_box_squared_distance(query, curr_node->right->box),
          std::static_pointer_cast<AABBTree>(curr_node->right)));
      }
    }
  }
  sqrd = min_dist;

  if (!descendant) return false;
  
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
