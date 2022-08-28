#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/game_engine.h"
#include "visuals/game_menu.h"

namespace datingsim {

namespace visuals {
class GameApp : public ci::app::App {
public:
  GameApp();

  void draw() override;
  
  void update() override;

  void mouseDown(ci::app::MouseEvent event) override;
  
  const float kWindowSizeY = 800.0;
  const float kWindowSizeX = 1200.0;
  const float kMargin = 100.0;
  const float kSpacing = 200.0;

private:
  GameEngine game_engine_;
  GameMenu game_menus_;
  size_t current_menu_ = 0;
  string current_option_ = "";
  Potato current_date_;
  bool has_options_;
};

} // namespace visuals

} // namespace datingsim

