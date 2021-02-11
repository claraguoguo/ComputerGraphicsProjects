#include "AABBTree.h"
#include "insert_box_into_box.h"


AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  // Reference: Textbook Page-304
  if(num_leaves == 0){
    this->left = NULL;
    this->right = NULL;
  }
  else if (num_leaves == 1) {
    this->left = objects[0];
    this->right = NULL;
    this->box = objects[0]->box;
  }
  else if (num_leaves == 2) {
    this->left = objects[0];
    this->right = objects[1];
    insert_box_into_box(this->left->box, this->box);
    insert_box_into_box(this->right->box, this->box);
  } 
  else {    
    // Put all object->box into the root bounding box
    for (int i = 0; i < num_leaves; ++i) {
      insert_box_into_box(objects[i]->box, this->box);
    }

    // Find the longest axis & its range
    Eigen::RowVector3d axis_diff = this->box.max_corner - this->box.min_corner;
    double longest_axis = std::max(std::max(axis_diff.x(), axis_diff.y()), axis_diff.z());
    double axis_mid_point = 0.5 * longest_axis;

    // Find the axis index. x-axis = 0, y-axis = 1, z-axis = 2.
    int axis_index;
    if (longest_axis == axis_diff.x()) axis_index = 0;
    else if (longest_axis == axis_diff.y()) axis_index = 1;
    else axis_index = 0;

    // Sort object by its center along the longest axis and determine the left-right split.
    std::vector<std::shared_ptr<Object>> left_half_objects; 
    std::vector<std::shared_ptr<Object>> right_half_objects; 

    for (int i = 0; i < num_leaves; ++i) {
      if (objects[i]->box.center()(axis_index) < axis_mid_point) {
        left_half_objects.push_back(objects[i]);
      }
      else {
        right_half_objects.push_back(objects[i]);
      }
    }

    // Will get error if one of arrays is empty
    if (left_half_objects.empty() && !right_half_objects.empty()) {
      left_half_objects.push_back(right_half_objects.back());
      right_half_objects.pop_back();
    }
    else if (right_half_objects.empty() && !left_half_objects.empty()) {
      right_half_objects.push_back(left_half_objects.back());
      left_half_objects.pop_back();
    }

    this->left = std::make_shared<AABBTree>(left_half_objects, a_depth + 1);
    this->right = std::make_shared<AABBTree>(right_half_objects, a_depth + 1);
  }
  ////////////////////////////////////////////////////////////////////////////
}

bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{

  // Reference: Textbook page-303
  bool has_hit = ray_intersect_box(ray, this->box, min_t, max_t);
  if (!has_hit) return false;

  double left_t, right_t;
  std::shared_ptr<Object> left_desc, right_desc;

  bool has_left_hit = (this->left != NULL) && (this->left->ray_intersect(
    ray, min_t, max_t, left_t, left_desc));

  bool has_right_hit = (this->right != NULL) && (this->right->ray_intersect(
    ray, min_t, max_t, right_t, right_desc));

  // Set the descendent to itself if not set
  if (has_left_hit && !left_desc) left_desc = this->left;
  if (has_right_hit && !right_desc) right_desc = this->right;

  if (has_left_hit && has_right_hit) {
    if (left_t < right_t) {
      t = left_t;
      descendant = left_desc;
    }
    else {
      t = right_t;
      descendant = right_desc;
    }
  }
  else if (has_left_hit) {
    t = left_t;
    descendant = left_desc;
  }
  else if (has_right_hit) {
    t = right_t;
    descendant = right_desc;
  }
  else {
    return false;
  }
  return true;
}