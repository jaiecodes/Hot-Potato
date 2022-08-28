#include "core/game_state.h"

namespace datingsim {

GameState::GameState(size_t set_id, const Player& set_player,
                     const vector<Potato>& set_characters,
                     const vector<Dialogue>& set_dialogue_tree,
                     size_t set_current_dialogue,
                     const string& set_current_phase,
                     const string& set_current_room) {
  id_ = set_id;
  player_ = set_player;
  characters_ = set_characters;
  dialogue_tree_ = set_dialogue_tree;
  current_dialogue_ = set_current_dialogue;
  current_phase_ = set_current_phase;
  current_room_ = set_current_room;
}

void GameState::SetId(size_t set_id) {
 id_ = set_id;
}

void GameState::SetPlayer(const Player& set_player) {
  player_ = set_player;
}

void GameState::SetCharacters(const vector<Potato>& set_characters) {
  characters_ = set_characters;
}

void GameState::SetDialogueTree(const vector<Dialogue>& set_dialogue_tree) {
  dialogue_tree_ = set_dialogue_tree;
}

void GameState::SetCurrentDialogue(size_t set_current_dialogue) {
  current_dialogue_ = set_current_dialogue;
}

void GameState::SetCurrentPhase(const string& set_current_phase) {
  current_phase_ = set_current_phase;
}

void GameState::SetCurrentRoom(const string& set_current_room) {
  current_room_ = set_current_room;
}

size_t GameState::GetId() const {
  return id_;
}

const Player& GameState::GetPlayer() const {
  return player_;
}

const vector<Potato>& GameState::GetCharacters() const {
  return characters_;
}

const vector<Dialogue>& GameState::GetDialogueTree() const {
  return dialogue_tree_;
}

size_t GameState::GetCurrentDialogue() const {
  return current_dialogue_;
}

const string& GameState::GetCurrentPhase() const {
  return current_phase_;
}

const string& GameState::GetCurrentRoom() const {
  return current_room_;
}

void to_json(json &j, const GameState &game) {
  j = json{{"id", game.id_},
           {"player", game.player_},
           {"characters", game.characters_},
           {"dialogue_tree", game.dialogue_tree_},
           {"current_dialogue", game.current_dialogue_},
           {"current_phase", game.current_phase_},
           {"current_room", game.current_room_}};
}

void from_json(const json &j, GameState &game) {
  j.at("id").get_to(game.id_);
  j.at("player").get_to(game.player_);
  j.at("characters").get_to(game.characters_);
  j.at("dialogue_tree").get_to(game.dialogue_tree_);
  j.at("current_dialogue").get_to(game.current_dialogue_);
  j.at("current_phase").get_to(game.current_phase_);
  j.at("current_room").get_to(game.current_room_);
}

} // namespace datingsim