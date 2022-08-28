#include "visuals/game_menu.h"
#include "cinder/gl/gl.h"

namespace datingsim {

namespace visuals {

GameMenu::GameMenu(float set_window_size_x, float set_window_size_y,
                   float set_margin, float set_spacing) {
  window_size_x_ = set_window_size_x;
  window_size_y_ = set_window_size_y;
  kCenterX = window_size_x_ / 2;
  kCenterY = window_size_y_ / 2;
  margin_ = set_margin;
  spacing_ = set_spacing;
}

void GameMenu::DisplayStartScreen() {
  layout_.clear();
  layout_options_.clear();
  ci::gl::drawStringCentered("Hot Potato",
                             vec2(kCenterX, kCenterY - 100),
                             kRose, kFontTitle);
  DisplayStartButtons(kRose, kWhite);
}

void GameMenu::DisplayIntro(const Dialogue& current_dialogue) {
  layout_.clear();
  layout_options_.clear();
  DisplayBackgroundBox(kYellowGreen);
  DrawString(current_dialogue.GetLine(), kCenterX, kCenterY,
             kDarkGreen, kFontSingleDisplay);
  DisplayNextButton(kDarkGreen, kWhite);
}

void GameMenu::DisplayMainMenu(const GameEngine& game) {
  layout_.clear();
  layout_options_.clear();
  
  vector<string> rooms = game.GetUniqueRooms();
  vector<string> rooms_urls = game.GetUniqueRoomsURLs();
  float modifier = 1.5;
  float box_dimension = spacing_ * modifier;
  float box_margin = margin_ / 2;
  float text_margin = margin_ * modifier;
  float x_pos_box = kCenterX - ((box_dimension / 2 + box_margin / 2)
                            * ( (float) rooms.size() - 1));
  float y_pos_box = kCenterY + box_margin;
  float x_pos_text = x_pos_box;
  float y_pos_text = y_pos_box - text_margin + kFontButtons.getSize();
  
  DisplayBackgroundBox(kCoral);
  DrawString("Where would you like to go?", kCenterX,
             text_margin , kRose, kFontSingleDisplay);
  
  
  for (size_t i = 0; i < rooms.size(); i++) {
    Box room_container(box_dimension, box_dimension, x_pos_box, y_pos_box);
    room_container.DrawBox(kLightOrange, true);
    DrawImage(rooms_urls[i], room_container.GetDimensions()[0],
              room_container.GetDimensions()[1]);
    DrawString(rooms[i], x_pos_text, y_pos_text,kWhite, kFontButtons);
    
    layout_.push_back(room_container);
    layout_options_[room_container] = rooms[i];
    
    x_pos_box += box_dimension + box_margin;
    x_pos_text += box_dimension + box_margin;
  }
}

void GameMenu::DisplayCharacters(const GameEngine& game, const string& room) {
  layout_.clear();
  layout_options_.clear();
  
  vector<Potato> potatoes = game.GetCharactersInRoom(room);
  float modifier = 1.5;
  float box_dimension_x = spacing_ * modifier;
  float box_dimension_y = spacing_ * 2;
  float box_margin = margin_ / 2;
  float text_margin = margin_ * modifier;
  float x_pos_box = kCenterX - ((box_dimension_x / 2 + box_margin / 2)
                                * ( (float) potatoes.size() - 1));
  float y_pos_box = kCenterY + box_margin;
  float x_pos_text = x_pos_box;
  float y_pos_text = y_pos_box - text_margin - 
          box_margin / 1.5 + kFontButtons.getSize();
  
  DisplayBackgroundBox(kLightOrange);
  DrawString("Who would you like to meet?", kCenterX,
             text_margin, kWhite, kFontSingleDisplay);
  DisplayBackButton(kRose, kWhite);
  
  for (const Potato& potato : potatoes) {
    float temp_y_pos_text = y_pos_text;
    Box room_container(box_dimension_x, box_dimension_y, x_pos_box, y_pos_box);
    room_container.DrawBox(kYellowGreen, true);
    DrawString("Name:", x_pos_text, temp_y_pos_text ,
               kDarkGreen, kFontButtons);
    DrawString(potato.GetName(), x_pos_text, 
               temp_y_pos_text += kFontButtons.getSize() ,
               kDarkGreen, kFontButtons);
    DrawString("Age:", x_pos_text, 
               temp_y_pos_text += kFontButtons.getSize(),
               kDarkGreen, kFontButtons);
    DrawString(std::to_string(potato.GetAge()), x_pos_text, 
               temp_y_pos_text += kFontButtons.getSize(),
               kDarkGreen, kFontButtons);
    DrawString("Type:", x_pos_text, 
               temp_y_pos_text += kFontButtons.getSize(),
               kDarkGreen, kFontButtons);
    DrawString(potato.GetType(), x_pos_text, 
               temp_y_pos_text += kFontButtons.getSize(),
               kDarkGreen, kFontButtons);
    DrawString("Description:", x_pos_text, 
               temp_y_pos_text += kFontButtons.getSize(),
               kDarkGreen, kFontButtons);
    DrawString(potato.GetDescription(), x_pos_text, 
               temp_y_pos_text += kFontButtons.getSize() * 21.5,
               kDarkGreen, kFontButtons);
    temp_y_pos_text -= kFontButtons.getSize() * 17.5;
    DrawString("Love Rating:", x_pos_text, 
               temp_y_pos_text += kFontButtons.getSize(),
               kDarkGreen, kFontButtons);
    DrawString(std::to_string(potato.GetLoveRating()), x_pos_text, 
               temp_y_pos_text += kFontButtons.getSize(),
               kDarkGreen, kFontButtons);

    layout_.push_back(room_container);
    layout_options_[room_container] = potato.GetName();

    x_pos_box += box_dimension_x + box_margin;
    x_pos_text += box_dimension_x + box_margin;
  }
}
void GameMenu::DisplayDate(Potato& character, const Dialogue& current_dialogue,
                           const vector<Dialogue>& options, bool has_options) {
  layout_.clear();
  layout_options_.clear();
  
  DisplayBackgroundBox(kRose);
  vec2 left_top_image(margin_, margin_ / 2);
  vec2 right_bot_image(window_size_x_ - margin_, 
                       window_size_y_ - spacing_ - window_size_y_ / 6);
  DrawImage(character.GetImageUrl(), left_top_image, right_bot_image);
  if (!has_options || current_dialogue.GetIsInterlude()) {
    DisplayNextButton(kLightOrange, kWhite);
    DrawDateDialogue(current_dialogue);
  } else {
    DrawDateDialogueOptions(options);
  }
  
}

const vector<Box>& GameMenu::GetLayout() const {
  return layout_;
}

void GameMenu::DrawString(const string& text, float x, float y,
                          const Color& color, const cinder::Font& font) {
  string line = text;
  string delimiter = "\n";
  vector<string> lines;
  size_t pos = 0;
  string token;
  while ((pos = line.find(delimiter)) != string::npos) {
    token = line.substr(0, pos);
    lines.push_back(token);
    line.erase(0, pos + delimiter.length());
  }
  if (lines.empty()) {
    ci::gl::drawStringCentered(text, vec2(x, y), color, font);
  } else {
    if (lines.size() > 2) {
      y -= (y / 2 + font.getSize() * 2);
    } else {
      y -= (font.getSize() * 2);
    }
    for (const string &part : lines) {
      ci::gl::drawStringCentered(part, vec2(x, y += font.getSize()), 
                                 color, font);
    }
  }
}

void GameMenu::DisplayNextButton(const Color& button_color,
                                 const Color& text_color) {
  float button_x = window_size_x_ - margin_;
  float button_y = window_size_y_ - margin_ - 10;
  Box next_button(margin_, margin_ - kFontButtons.getSize(),
                  button_x, button_y);
  next_button.DrawBox(button_color, false);
  layout_.push_back(next_button);
  layout_options_[next_button] = "Next";
  ci::gl::drawStringCentered("Next",
                             vec2(button_x,
                                  button_y - kFontButtons.getSize() / 2),
                             text_color, kFontButtons);
}

void GameMenu::DisplayBackButton(const Color& button_color,
                                 const Color& text_color) {
  float button_x = 0 + margin_;
  float button_y = window_size_y_ - margin_ - 10;
  Box back_button(margin_, margin_ - kFontButtons.getSize(),
                  button_x, button_y);
  back_button.DrawBox(button_color, false);
  layout_.push_back(back_button);
  layout_options_[back_button] = "Back";
  ci::gl::drawStringCentered("Back",
                             vec2(button_x,
                                  button_y - kFontButtons.getSize() / 2),
                             text_color, kFontButtons);
}

void GameMenu::DisplayBackgroundBox(const Color &color) {
  float button_x = window_size_x_ - margin_;
  float button_y = window_size_y_ - margin_;
  Box text_box(button_x, button_y, kCenterX, kCenterY);
  text_box.DrawBox(color, true);
}

void GameMenu::DisplayStartButtons(const Color& button_color,
                                   const Color& text_color) {
  float start_x = window_size_x_ / 2;
  float start_y = window_size_y_ / 2 + spacing_;
  Box start_button(spacing_, spacing_ / 2, start_x, start_y);
  start_button.DrawBox(button_color, true);
  layout_.push_back(start_button);
  DrawString("Start\nNew Game\n", start_x, start_y,
             text_color, kFontButtons);
}

bool GameMenu::IsMenuChange(size_t id, const vector<Dialogue>& dialogue_tree) {
  if (id < 2 && id > dialogue_tree.size()) {
    return false;
  }
  if (dialogue_tree[id].GetPhase() != dialogue_tree[id - 1].GetPhase() &&
      dialogue_tree[id - 1].GetPhase() == dialogue_tree[id - 2].GetPhase()) {
    return true;
  } else {
    return false;
  }
}

const map<Box, string>& GameMenu::GetLayoutOptions() const {
  return layout_options_;
}

void GameMenu::DrawImage(const string& url, const vec2& left_top,
                         const vec2& right_bot) {
  auto image = loadImage(cinder::loadUrl(url) );
  texture_ = cinder::gl::Texture2d::create(image);
  vec2 img_left_top = left_top;
  vec2 img_right_bot = right_bot;
  img_left_top.y += (margin_ + kFontButtons.getSize()) / 2 ;
  img_left_top.x += margin_ / 4;
  img_right_bot.x -= margin_ / 4;
  img_right_bot.y -= margin_ / 4;
  cinder::gl::draw(texture_,ci::Rectf(img_left_top, img_right_bot));
}

void GameMenu::DrawDateDialogue(const Dialogue& dialogue) {
  float box_dimension_x = window_size_x_ - spacing_ * 2;
  float box_dimension_y = window_size_y_ / 4;
  float y_pos = window_size_y_ - margin_ - box_dimension_y / 2;
  Box dialogue_box(box_dimension_x, box_dimension_y, kCenterX, y_pos);
  dialogue_box.DrawBox(kCoral, true);
  DrawString(dialogue.GetLine(), kCenterX, 
             y_pos - kFontButtons.getSize() / 2,
             kWhite, kFontButtons);
}

void GameMenu::DrawDateDialogueOptions(const vector<Dialogue>& options) {
  float box_dimension_x = (window_size_x_ - spacing_ * 2) / options.size();
  float box_dimension_y = window_size_y_ / 4;
  float box_margin = margin_ / 2;
  float x_pos = kCenterX - ((box_dimension_x / 2 + box_margin / 2) 
          * (options.size() - 1));
  float x_pos_text = x_pos;
  float y_pos = window_size_y_ - margin_ - box_dimension_y / 2;
  for (size_t i = 0; i < options.size(); i++) {
    Box dialogue_box(box_dimension_x, box_dimension_y, x_pos, y_pos);
    dialogue_box.DrawBox(kCoral, true);
    DrawString(options[i].GetLine(), x_pos_text, 
               y_pos - kFontButtons.getSize() / 2,
               kWhite, kFontButtons);
    layout_.push_back(dialogue_box);
    layout_options_[dialogue_box] = std::to_string(options[i].GetId());

    x_pos += box_dimension_x + box_margin;
    x_pos_text += box_dimension_x + box_margin;
  }
}


} // namespace visuals

} // namespace datingsim