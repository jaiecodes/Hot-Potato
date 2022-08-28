#include "visuals/game_app.h"

namespace datingsim {

namespace visuals {


GameApp::GameApp() : game_menus_(kWindowSizeX, kWindowSizeY, kMargin,
                                 kSpacing) {
  ci::app::setWindowSize((int) kWindowSizeX,
                         (int) kWindowSizeY);
}

void GameApp::draw() {
  ci::Color8u background_color(255, 253, 245); // light green-blue
  ci::gl::clear(background_color);
  ci::Color8u box_color(255, 213, 166); // light coral
  game_menus_.DisplayBackgroundBox(box_color);
  if (current_menu_ == 0) {
    game_menus_.DisplayStartScreen();
  }
  if (current_menu_ == 1) {
    game_menus_.DisplayIntro(game_engine_.GetCurrentDialogue());
  }
  if (current_menu_ == 2) {
    game_menus_.DisplayMainMenu(game_engine_);
  }
  if (current_menu_ == 3) {
    game_menus_.DisplayCharacters(game_engine_, current_option_);
  }
  if (current_menu_ == 4) {
    Dialogue current_dialogue =
            game_engine_.GetCurrentCharacterDialogue(current_date_);
    vector<Dialogue> current_options =
            game_engine_.GetCurrentCharacterOptions(current_dialogue,
                                                    current_date_);
    game_menus_.DisplayDate(current_date_, current_dialogue,
                            current_options, has_options_);
  }
}

void GameApp::update() {

}

void GameApp::mouseDown(ci::app::MouseEvent event) {
  int mouseX = event.getX();
  int mouseY = event.getY();
  
  if (current_menu_ == 0) {
    vector<Box> buttons = game_menus_.GetLayout();
    vector<vec2> dimensions = buttons[0].GetDimensions();
    if ((mouseX > dimensions[0].x && mouseX < dimensions[1].x) &&
        (mouseY > dimensions[0].y && mouseY < dimensions[1].y)) {
      current_menu_ = 1;
      game_engine_.SetIsNewGame(true);
    }
  } else if (current_menu_ == 1) {
    vector<Box> buttons = game_menus_.GetLayout();
    vector<vec2> dimensions = buttons[0].GetDimensions();
    if ((mouseX > dimensions[0].x && mouseX < dimensions[1].x) &&
        (mouseY > dimensions[0].y && mouseY < dimensions[1].y)) {
      if (game_engine_.GetCurrentDialogue().GetPhase() == "Name") {
        game_engine_.UpdateName(game_engine_.ReadName());
      }
      if (game_engine_.GetCurrentDialogue().GetPhase() == "Type") {
        game_engine_.UpdateType(game_engine_.ReadType());
      }
      vector<size_t> options = game_engine_.GetCurrentDialogue().GetOptions();
      game_engine_.UpdateCurrentDialogue(options[0]);
      if (game_menus_.IsMenuChange(game_engine_.GetCurrentDialogue().GetId(),
                                   game_engine_.GetDialogueTree())) {
        current_menu_ = 2;
      }
    }
  } else if (current_menu_ == 2) {
    vector<Box> buttons = game_menus_.GetLayout();
    for (Box button : buttons) {
      vector<vec2> dimensions = button.GetDimensions();
      if ((mouseX > dimensions[0].x && mouseX < dimensions[1].x) &&
          (mouseY > dimensions[0].y && mouseY < dimensions[1].y)) {
        current_option_ = game_menus_.GetLayoutOptions().at(button);
        current_menu_ = 3;
      }
    }
  } else if (current_menu_ == 3) {
    vector<Box> buttons = game_menus_.GetLayout();
    for (Box button : buttons) {
      vector<vec2> dimensions = button.GetDimensions();
      if ((mouseX > dimensions[0].x && mouseX < dimensions[1].x) &&
          (mouseY > dimensions[0].y && mouseY < dimensions[1].y)) {
        current_option_ = game_menus_.GetLayoutOptions().at(button);
        if (current_option_ == "Back") {
          current_menu_ = 2;
        } else {
          current_date_ = game_engine_.GetCharacterByName(current_option_);
          current_menu_ = 4;
          has_options_ = false;
        }
      }
    }
  } else if (current_menu_ == 4) {
    vector<Box> buttons = game_menus_.GetLayout();
    for (Box button : buttons) {
      vector<vec2> dimensions = button.GetDimensions();
      if ((mouseX > dimensions[0].x && mouseX < dimensions[1].x) &&
          (mouseY > dimensions[0].y && mouseY < dimensions[1].y)) {
        current_option_ = game_menus_.GetLayoutOptions().at(button);
        if (current_option_ == "Next") {
          has_options_ = true;
          if (game_engine_.GetCurrentCharacterDialogue(
                  current_date_).GetIsInterlude()) {
            vector<size_t> single_option = game_engine_
                    .GetCurrentCharacterDialogue(current_date_).GetOptions();
            game_engine_.UpdateCurrentCharacterDialogue(single_option[0],
                                                        current_date_);
            if (game_menus_.IsMenuChange(
                    game_engine_.GetCurrentCharacterDialogue(
                            current_date_).GetId(),
                    game_engine_.GetCharacterDialogueTree(
                            current_date_))) {
              current_menu_ = 2;
            }
          }
        } else {
          has_options_ = false;
          vector<size_t> options = game_engine_
                  .GetCurrentCharacterDialogue(current_date_).GetOptions();
          for (size_t option : options) {
            if (stoi(current_option_) == option) {
              game_engine_.UpdateCurrentCharacterDialogue(option,
                                                          current_date_);
              game_engine_.UpdateLoveRating(current_date_,
                                            game_engine_.GetCurrentCharacterDialogue(
                                                    current_date_).GetLoveRating());
            }
          }
        }
      }
    }
  }
}

} // namespace visuals

} // namespace datingsim