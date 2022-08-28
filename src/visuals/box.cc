#include "visuals/box.h"

namespace datingsim {

namespace visuals {


Box::Box(float width, float height, float x_pos, float y_pos) {
  x_buffer_ = width/2;
  y_buffer_ = height/2;
  vec2 left_top_pos(x_pos - x_buffer_, y_pos - y_buffer_);
  vec2 right_bottom_pos(x_pos + x_buffer_,y_pos + y_buffer_);
  dimensions_.push_back(left_top_pos);
  dimensions_.push_back(right_bottom_pos);
}

void Box::DrawBox(Color box_color, bool isRounded) {
  ci::gl::color(box_color);
  if (isRounded){
    ci::gl::drawSolidRoundedRect(ci::Rectf(dimensions_[0], dimensions_[1]),
                                 20.0, 4);
  } else {
    ci::gl::drawSolidRect(ci::Rectf(dimensions_[0], dimensions_[1]));
  }
}

const vector<vec2>& Box::GetDimensions() const {
  return dimensions_;
}

bool operator==(const Box& this_box, const Box& other_box) {
  if (this_box.dimensions_[0].x == other_box.dimensions_[0].x
      && this_box.dimensions_[0].y == other_box.dimensions_[0].y
      && this_box.dimensions_[1].x == other_box.dimensions_[1].x
      && this_box.dimensions_[1].y == other_box.dimensions_[1].y) {
    return true;
  } else {
    return false;
  }
}

bool operator<(const Box &this_box, const Box &other_box) {
  return (this_box.dimensions_[0].x < other_box.dimensions_[0].x
            && this_box.dimensions_[1].x < other_box.dimensions_[1].x) 
            || (this_box.dimensions_[0].y < other_box.dimensions_[0].y
                && this_box.dimensions_[1].y < other_box.dimensions_[1].y);
}


} // namespace visuals

} // namespace datingsim
