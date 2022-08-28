#pragma once

#include "json_processor.h"
#include "potato.h"
#include "dialogue.h"
#include "player.h"

namespace datingsim {

/**
 * A class representing the current game state
 */
class GameState {
public:
  GameState() = default;
  /**
   * Constructs a GameState object with all member variables initialized
   */
  GameState(size_t set_id, const Player& set_player,
            const vector<Potato>& set_characters,
            const vector<Dialogue>& set_dialogue_tree,
            size_t set_current_dialogue, const string& set_current_phase,
            const string& set_current_room);

  /**
   * Sets the id value of this GameState
   * @param set_id A size_t representing the id number of this GameState object
   */
  void SetId(size_t set_id);

  /**
   * Sets the current Player state of this GameState
   * @param set_player A Player object representing the player current state
   */
  void SetPlayer(const Player& set_player);

  /**
   * Sets the current characters and their state of this GameState
   * @param set_characters A vector of Potato objects
   * representing this Game's characters
   */
  void SetCharacters(const vector<Potato>& set_characters);

  /**
   * Sets the current set of dialogue options of this GameState
   * @param set_dialogue_tree A vector of Dialogue objects
   * representing this Game's branching dialogue tree
   */
  void SetDialogueTree(const vector<Dialogue>& set_dialogue_tree);

  /**
   * Sets the current dialogue node of in this GameState's branching dialogue
   * @param set_current_dialogue A size_t representing a Dialogue object's id 
   */
  void SetCurrentDialogue(size_t set_current_dialogue);

  /**
   * Sets the current game phase in this GameState
   * @param set_current_phase A string representing the current game phase
   */
  void SetCurrentPhase(const string& set_current_phase);

  /**
   * Sets the current room of this GameState
   * @param set_current_room A string representing the current room the player
   * is occupying 
   */
  void SetCurrentRoom(const string& set_current_room);

  /**
   * Gets the id value of this GameState
   * @return A size_t representing the id number of this GameState object
   */
  size_t GetId() const;

  /**
   * Gets the current Player state of this GameState
   * @return A Player object representing the player's current state
   */
  const Player& GetPlayer() const;

  /**
   * Gets the current characters and their state of this GameState
   * @return A vector of Potato objects representing this Game's characters
   */
  const vector<Potato>& GetCharacters() const;

  /**
   * Gets the current set of dialogue options of this GameState
   * @return A vector of Dialogue objects representing this 
   * Game's branching dialogue tree
   */
  const vector<Dialogue>& GetDialogueTree() const;

  /**
   * Gets the current dialogue node of in this GameState's branching dialogue
   * @return A size_t representing a Dialogue object's id 
   */
  size_t GetCurrentDialogue() const;

  /**
   * Gets the current game phase in this GameState
   * @return A string representing the current game phase
   */
  const string& GetCurrentPhase() const;

  /**
   * Gets the current room of this GameState
   * @return A string representing the current room the player is occupying 
   */
  const string& GetCurrentRoom() const;

  /**
   * Converts GameState object to Json object 
   * @param j A json object 
   * @param game A GameState object
   */
  friend void to_json(json& j, const GameState& game);
  /**
   * Converts Json object to GameState object 
   * @param j A json object 
   * @param game A GameState object
   */
  friend void from_json(const json& j, GameState& game);
private:
  size_t id_;
  Player player_;
  vector<Potato> characters_;
  vector<Dialogue> dialogue_tree_;
  size_t current_dialogue_;
  string current_phase_;
  string current_room_;
};

} // namespace datingsim