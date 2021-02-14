#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 
#include <iostream>

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  // Reference: Lec4 - P31 - BVH Intersection Queries 
  std::list<std::pair<std::shared_ptr<AABBTree>,std::shared_ptr<AABBTree> > > Q;

  if (box_box_intersect(rootA->box, rootB->box)) {
    Q.emplace_back(std::make_pair(rootA, rootB));
  }

  while (!Q.empty()){
    std::shared_ptr<AABBTree> nodeA = Q.front().first;
    std::shared_ptr<AABBTree> nodeB = Q.front().second;
    Q.pop_front();
    // std::cout << Q.size() << std::endl;

    if (!box_box_intersect(nodeA->box, nodeB->box)) continue;

    // Cast std::shared_ptr<Object> to std::shared_ptr<AABBTree>
    std::shared_ptr<AABBTree> nodeA_left_child, nodeB_left_child, nodeA_right_child, nodeB_right_child;
    nodeA_left_child = (nodeA->left) ? std::static_pointer_cast<AABBTree>(nodeA->left) : NULL;
    nodeA_right_child = (nodeA->right) ? std::static_pointer_cast<AABBTree>(nodeA->right) : NULL;
    nodeB_left_child = (nodeB->left) ? std::static_pointer_cast<AABBTree>(nodeB->left) : NULL;
    nodeB_right_child = (nodeB->right) ? std::static_pointer_cast<AABBTree>(nodeB->right) : NULL;

    if (nodeA->num_leaves <= 2 && nodeB->num_leaves <= 2){ // if both subtress are leaves
        if (nodeA_left_child && nodeB_left_child && box_box_intersect(nodeA->left->box, nodeB->left->box)){
          leaf_pairs.push_back(std::make_pair(nodeA->left, nodeB->left));
        }
        if (nodeA_left_child && nodeB_right_child && box_box_intersect(nodeA->left->box, nodeB->right->box)){
          leaf_pairs.push_back(std::make_pair(nodeA->left, nodeB->right));
        }
        if (nodeA_right_child && nodeB_left_child && box_box_intersect(nodeA->right->box, nodeB->left->box)){
          leaf_pairs.push_back(std::make_pair(nodeA->right, nodeB->left));
        }
        if (nodeA_right_child && nodeB_right_child && box_box_intersect(nodeA->right->box, nodeB->right->box)){
          leaf_pairs.push_back(std::make_pair(nodeA->right, nodeB->right));
        }
    }
    else if (nodeA->num_leaves <= 2) {
      // Check {left, right} child of nodeB
      if (nodeB_left_child && box_box_intersect(nodeA->box, nodeB->left->box)){
          Q.push_back(std::make_pair(nodeA, nodeB_left_child));
      }
      if (nodeB_right_child && box_box_intersect(nodeA->box, nodeB->right->box)){
        Q.push_back(std::make_pair(nodeA, nodeB_right_child));
      }
    }
    else if (nodeB->num_leaves <= 2) {
      // Check {left, right} child of nodeA
      if (nodeA_left_child && box_box_intersect(nodeB->box, nodeA->left->box)){
          Q.push_back(std::make_pair(nodeA_left_child, nodeB));
      }
      if (nodeA_right_child && box_box_intersect(nodeB->box, nodeA->right->box)){
        Q.push_back(std::make_pair(nodeA_right_child, nodeB));
      }
    }
    else {
      if (nodeA_left_child && nodeB_left_child && box_box_intersect(nodeA->left->box, nodeB->left->box)) {
        Q.push_back(std::make_pair(nodeA_left_child, nodeB_left_child));
      }
      if (nodeA_left_child && nodeB_right_child && box_box_intersect(nodeA->left->box, nodeB->right->box)) {
        Q.push_back(std::make_pair(nodeA_left_child, nodeB_right_child));
      }
      if (nodeA_right_child && nodeB_left_child && box_box_intersect(nodeA->right->box, nodeB->left->box)) {
        Q.push_back(std::make_pair(nodeA_right_child, nodeB_left_child));
      }
      if (nodeA_right_child && nodeB_right_child && box_box_intersect(nodeA->right->box, nodeB->right->box)) {
        Q.push_back(std::make_pair(nodeA_right_child, nodeB_right_child));
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////
}
