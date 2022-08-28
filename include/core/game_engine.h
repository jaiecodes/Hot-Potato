#pragma once

#include "game_state.h"
#include <iostream>

namespace datingsim {

class GameEngine {
public:
  GameEngine() = default;
  
  void SetIsNewGame(bool is_new_game);

  Dialogue GetCurrentDialogue() const;

  vector<Dialogue> GetDialogueTree() const;

  vector<Dialogue> GetCurrentOptions(const Dialogue& cur_dialogue) const;

  vector<Dialogue> GetCharacterDialogueTree(Potato character) const;
  
  Dialogue GetCurrentCharacterDialogue(Potato character) const;

  vector<Dialogue> GetCurrentCharacterOptions(const Dialogue& cur_dialogue,
                                              Potato character) const;
  
  vector<Potato> GetCharactersInRoom(const string& room) const;

  Potato GetCharacterByName(const string& character);

  void UpdateLoveRating(Potato& character, float love_adjustment);

  vector<string> GetUniqueRooms() const;

  vector<string> GetUniqueRoomsURLs() const;
  
  void UpdateName(const string& set_name);

  void UpdateType(const string& set_type);
  
  string ReadName();
  
  string ReadType();
  
  void UpdateCurrentDialogue(size_t set_id);

  void UpdateCurrentCharacterDialogue(size_t set_id, Potato& character);
  
  void Save();
private:
  const string kNewGameFile = "/Users/Yousher/CLionProjects/Cinder"
                              "/my-projects/final-project-Jeideun"
                              "/data/new_game.json";
  const string kSavedGameFile = "/Users/Yousher/CLionProjects/Cinder"
                                "/my-projects/final-project-Jeideun"
                                "/data/saved_game.json";
  GameState game_;
  json game_json_;
};

} // namespace datingsim
