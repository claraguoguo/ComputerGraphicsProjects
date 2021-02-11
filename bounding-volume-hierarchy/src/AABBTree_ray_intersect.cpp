#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  t = 0;

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
  ////////////////////////////////////////////////////////////////////////////
}

