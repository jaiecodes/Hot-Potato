#include "core/game_engine.h"

namespace datingsim {

void GameEngine::Save() {
  game_.SetId(1);
  game_json_ = game_;
  datingsim::JsonProcessor::WriteFile(kSavedGameFile, game_json_);
}

Dialogue GameEngine::GetCurrentDialogue() const {
  for (const Dialogue& dialogue: game_.GetDialogueTree()) {
    if(dialogue.GetId() == game_.GetCurrentDialogue()) {
      return dialogue;
    }
  }
  return Dialogue();
}

vector<Dialogue> 
GameEngine::GetCurrentOptions(const Dialogue &cur_dialogue) const {
  vector<Dialogue> options;
  for (size_t ids: cur_dialogue.GetOptions()) {
    for (const Dialogue& dialogue: game_.GetDialogueTree()) {
      if (dialogue.GetId() == ids) {
        options.push_back(dialogue);
      }
    }
  }
  return options;
}

Dialogue
GameEngine::GetCurrentCharacterDialogue(Potato character) const {
  for (const Dialogue& dialogue: character.GetCharacterDialogue()) {
    if(dialogue.GetId() == character.GetCurrentDialogue()) {
      return dialogue;
    }
  }
  return Dialogue();
}

vector<Dialogue>
GameEngine::GetCurrentCharacterOptions(const Dialogue &cur_dialogue,
                                       Potato character) const {
  vector<Dialogue> options;
  for (size_t ids: cur_dialogue.GetOptions()) {
    for (const Dialogue& dialogue: character.GetCharacterDialogue()) {
      if (dialogue.GetId() == ids) {
        options.push_back(dialogue);
      }
    }
  }
  return options;
}

void GameEngine::UpdateName(const string& set_name) {
  Player temp_player = game_.GetPlayer();
  temp_player.SetName(set_name);
  game_.SetPlayer(temp_player);
  
  vector<Dialogue> temp_tree;
  for (Dialogue dialogue: game_.GetDialogueTree()) {
    string temp_line = dialogue.GetLine();
    if (temp_line.find("Y/N") != std::string::npos) {
      temp_line.replace(temp_line.find("Y/N"), 
                        3, set_name);
      dialogue.SetLine(temp_line);
    }
    temp_tree.push_back(dialogue);
  }
  game_.SetDialogueTree(temp_tree);
  temp_tree.clear();
  
  vector<Potato> temp_characters;
  for (Potato character: game_.GetCharacters()) {
    for (Dialogue dialogue: character.GetCharacterDialogue()) {
      string temp_line = dialogue.GetLine();
      if (temp_line.find("Y/N") != std::string::npos) {
        temp_line.replace(temp_line.find("Y/N"), 
                          3, set_name);
        dialogue.SetLine(temp_line);
      }
      temp_tree.push_back(dialogue);
    }
    character.SetCharacterDialogue(temp_tree);
    temp_tree.clear();
    temp_characters.push_back(character);
  }
  game_.SetCharacters(temp_characters);
}

void GameEngine::UpdateType(const string& set_type) {
  Player temp_player = game_.GetPlayer();
  temp_player.SetType(set_type);
  game_.SetPlayer(temp_player);

  vector<Dialogue> temp_tree;
  for (Dialogue dialogue: game_.GetDialogueTree()) {
    string temp_line = dialogue.GetLine();
    if (temp_line.find("N/A") != std::string::npos) {
      temp_line.replace(temp_line.find("N/A"), 
                        3, set_type);
      dialogue.SetLine(temp_line);
    }
    temp_tree.push_back(dialogue);
  }
  game_.SetDialogueTree(temp_tree);
  temp_tree.clear();

  vector<Potato> temp_characters;
  for (Potato character: game_.GetCharacters()) {
    for (Dialogue dialogue: character.GetCharacterDialogue()) {
      string temp_line = dialogue.GetLine();
      if (temp_line.find("N/A") != std::string::npos) {
        temp_line.replace(temp_line.find("N/A"), 
                          3, set_type);
        dialogue.SetLine(temp_line);
      }
      temp_tree.push_back(dialogue);
    }
    character.SetCharacterDialogue(temp_tree);
    temp_tree.clear();
    temp_characters.push_back(character);
  }
  game_.SetCharacters(temp_characters);
}

void GameEngine::UpdateCurrentDialogue(size_t set_id) {
  game_.SetCurrentDialogue(set_id);
}

void GameEngine::UpdateCurrentCharacterDialogue(size_t set_id, 
                                                Potato& character) {
  character.SetCurrentDialogue(set_id);
  
  vector<Potato> temp_characters;
  for (Potato potato: game_.GetCharacters()) {
    if(potato.GetName() == character.GetName()) {
      potato.SetCurrentDialogue(set_id);
    }
    temp_characters.push_back(potato);
  }
  game_.SetCharacters(temp_characters);
}

void GameEngine::SetIsNewGame(bool is_new_game) {
  if(is_new_game) {
    game_json_ = datingsim::JsonProcessor::ReadFile(kNewGameFile);
    game_ = game_json_;
  } else {
    game_json_ = datingsim::JsonProcessor::ReadFile(kSavedGameFile);
    game_ = game_json_;
  }
}

string GameEngine::ReadName() {
  string name;
  std::cout << "Type your name here: ";
  std::cin >> name; 
  return name;
}

string GameEngine::ReadType() {
  string type;
  std::cout << "Type your type here: ";
  std::cin >> type;
  return type;
}

vector<Dialogue> GameEngine::GetDialogueTree() const {
  return game_.GetDialogueTree();
}

vector<Dialogue> GameEngine::GetCharacterDialogueTree(Potato character) const {
  return character.GetCharacterDialogue();
}

vector<string> GameEngine::GetUniqueRooms() const {
  vector<string> temp_rooms;
  temp_rooms.reserve(game_.GetCharacters().size());
  for (Potato characters : game_.GetCharacters()) {
    temp_rooms.push_back(characters.GetRoom());
  }
  
  vector<string>::iterator it;
  it = unique(temp_rooms.begin(), temp_rooms.end());
  temp_rooms.resize(distance(temp_rooms.begin(), it));
  return temp_rooms;
}

vector<string> GameEngine::GetUniqueRoomsURLs() const {
  vector<string> temp_urls;
  temp_urls.reserve(game_.GetCharacters().size());
  for (Potato characters : game_.GetCharacters()) {
    temp_urls.push_back(characters.GetRoomUrl());
  }
  
  vector<string>::iterator it;
  it = unique(temp_urls.begin(), temp_urls.end());
  temp_urls.resize(distance(temp_urls.begin(), it));
  return temp_urls;
}

vector<Potato> GameEngine::GetCharactersInRoom(const string& room) const {
  vector<Potato> temp_characters;
  for (const Potato& character : game_.GetCharacters()) {
    if (character.GetRoom() == room) {
      temp_characters.push_back(character);
    }
  }
  return temp_characters;
}

Potato GameEngine::GetCharacterByName(const string &character) {
  for (Potato potato : game_.GetCharacters()) {
    if (potato.GetName() == character) {
      return potato;
    }
  }
  return Potato();
}

void GameEngine::UpdateLoveRating(Potato& character, float love_adjustment) {
  float new_love = character.GetLoveRating() + love_adjustment;
  character.SetLoveRating(new_love);
  
  vector<Potato> temp_characters;
  for (Potato potato: game_.GetCharacters()) {
    if(potato.GetName() == character.GetName()) {
      potato.SetLoveRating(new_love);
    }
    temp_characters.push_back(potato);
  }
  game_.SetCharacters(temp_characters);
}


} // namespace datingsim
