#pragma once

#include <vector>
#include "cinder/gl/gl.h"

namespace datingsim {

namespace visuals {

using std::vector;
using glm::vec2;
using ci::Color;


class Box {
public:
  Box(float width, float height, float x_pos, float y_pos);
  void DrawBox(Color box_color, bool isRounded);
  const vector<vec2>& GetDimensions() const;
  friend bool operator==(const Box& this_box, const Box& other_box);
  friend bool operator<(const Box& this_box,  const Box& other_box);
private:
  vector<vec2> dimensions_;
  float x_buffer_;
  float y_buffer_;
};

} // namespace visuals

} // namespace datingsim

