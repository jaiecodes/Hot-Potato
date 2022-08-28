#pragma once

#include <string>
#include "json_processor.h"

namespace datingsim {
using std::string;

/**
 * A class represent the player and their information
 */
class Player {
public:
  Player() = default;
  /**
   * Constructs a player object with all member variables initialized
   */
  Player(const string& set_name, const string& set_type);
  /**
   * Sets the player's name
   * @param set_name A string representing the player's name
   */
  void SetName(const string& set_name);
  /**
   * Sets the player's potato type
   * @param set_type A string representing the player's potato type
   */
  void SetType(const string& set_type);
  /**
   * Gets the player's name
   * @return A string representing the player's name
   */
  const string& GetName() const;
  /**
   * Gets the player's potato type
   * @return A string representing the player's potato type
   */
  const string& GetType() const;
  /**
   * Converts Player object to Json object 
   * @param j A json object 
   * @param player A player object
   */
  friend void to_json(json& j, const Player& player);
  /**
   * Converts Json object to Player object 
   * @param j A json object 
   * @param player A player object
   */
  friend void from_json(const json& j, Player& player);
private:
  string name_;
  string type_;
};

} // namespace datingsim


