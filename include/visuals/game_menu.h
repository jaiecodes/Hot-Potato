#pragma once

#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "visuals/box.h"
#include "core/game_engine.h"
#include <core/dialogue.h>

namespace datingsim {

namespace visuals {
using std::string;
using std::pair;
using std::map;

class GameMenu {
public:
  GameMenu(float set_window_size_x, float set_window_size_y,
           float set_margin, float set_spacing);
  void DisplayStartScreen();
  void DisplayIntro(const Dialogue& current_dialogue);
  void DisplayBackgroundBox(const Color& color);
  void DisplayNextButton(const Color& button_color, const Color& text_color);
  void DisplayBackButton(const Color& button_color, const Color& text_color);
  void DisplayStartButtons(const Color& button_color, const Color& text_color);
  void DisplayMainMenu(const GameEngine& game);
  void DisplayCharacters(const GameEngine& game, const string& room);
  void DisplayDate(Potato& character, const Dialogue& current_dialogue,
                   const vector<Dialogue>& options, bool has_options);
  bool IsMenuChange(size_t id, const vector<Dialogue>& dialogue_tree);
  const vector<Box>& GetLayout() const;
  const map<Box, string>& GetLayoutOptions() const;
  void DrawString(const string& text, float x, float y,
                  const Color& color, const cinder::Font& font);
  void DrawImage(const string& url, const vec2& left_top, const vec2& right_bot);
  void DrawDateDialogue(const Dialogue& dialogue);
  void DrawDateDialogueOptions(const vector<Dialogue>& options);
private:
  const ci::Color8u kWhite = ci::Color8u(255, 253, 245);
  const ci::Color8u kDarkGreen = ci::Color8u(65, 109, 94);
  const ci::Color8u kYellowGreen = ci::Color8u(194, 207, 104);
  const ci::Color8u kRose = ci::Color8u(255, 135, 125);
  const ci::Color8u kLightOrange = ci::Color8u(255,213,166);
  const ci::Color8u kCoral = ci::Color8u(255,196,174);
  const cinder::Font kFontTitle = cinder::Font("Comic Sans MS", 150);
  const cinder::Font kFontSingleDisplay = cinder::Font("Comic Sans MS", 50);
  const cinder::Font kFontButtons = cinder::Font("Comic Sans MS", 25);
  float kCenterX;
  float kCenterY;
  float window_size_x_;
  float window_size_y_;
  float margin_;
  float spacing_;
  vector<Box> layout_;
  map<Box, string> layout_options_;
  cinder::gl::Texture2dRef texture_;
};

} // namespace visuals

} // namespace datingsim
