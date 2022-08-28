#pragma once

#include <string>
#include "json_processor.h"
#include "dialogue.h"

namespace datingsim {
using std::string;

/**
 * A class representing a potato character that the player interacts with
 */
class Potato {
public:
  Potato() = default;
  /**
   * Constructs a potato object with all member variables initialized
   */
  Potato(const string& set_name, size_t set_age,
         const string& set_type, const string& set_description,
         const string& set_room, float set_love_rating,
         const vector<Dialogue>& set_character_dialogue,
         size_t set_current_dialogue);
  /**
   * Sets the name of this potato
   * @param set_name A string representing this potato's name
   */
  void SetName(const string& set_name);
  /**
   * Sets the age of this potato
   * @param set_age A size_t representing this potato's age
   */
  void SetAge(size_t set_age);
  /**
   * Sets the type of this potato
   * @param set_type A string representing this potato's type
   */
  void SetType(const string& set_type);
  /**
   * Sets the description of this potato
   * @param set_description A string describing this potato
   */
  void SetDescription(const string& set_description);
  /**
   * Sets the room this potato resides in
   * @param set_room A string representing the this potato's resides
   */
  void SetRoom(const string& set_room);
  /**
   * Sets the love rating this potato feels
   * @param set_love_rating A float representing current love for the player
   */
  void SetLoveRating(float set_love_rating);
  /**
   * Sets the character dialogue this potato has
   * @param set_character_dialogue A vector of Dialogue representing the 
   * conversations for that character 
   */
  void SetCharacterDialogue(const vector<Dialogue>& set_character_dialogue);
  /**
   * Sets the current dialogue's id
   * @param set_current_dialogue A size_t representing the dialogue's id
   */
  void SetCurrentDialogue(size_t set_current_dialogue);
  /**
   * Gets this potato's name
   * @return A string representing this potato's name
   */
  string GetName() const&;
  /**
   * Gets this potato's name
   * @return A size_t representing this potato's age
   */
  size_t GetAge() const;
  /**
   * Gets this potato's  type
   * @return A string representing this potato's type
   */
  const string& GetType() const;
  /**
   * Gets this potato's description
   * @return A string describing this potato
   */
  const string& GetDescription() const;
  /**
   * Gets the image url for this potato 
   * @return A string representing the image url
   */
  const string& GetImageUrl() const;
  /**
   * Gets the room this potato resides in
   * @return A string representing the this potato's resides
   */
  const string& GetRoom() const;
  /**
   * Gets the room image url for this potato 
   * @return A string representing the room image url
   */
  const string& GetRoomUrl() const;
  /**
   * Gets the love rating this potato feels
   * @return A float representing current love for the player
   */
  float GetLoveRating() const;
  /**
   * Gets the character dialogue this potato has
   * @return A vector of Dialogue representing the 
   * conversations for that character 
   */
  const vector<Dialogue>& GetCharacterDialogue() const;
  /**
   * Gets the current dialogue's id
   * @return A size_t representing the dialogue's id
   */
  size_t GetCurrentDialogue() const;
  /**
   * Converts Potato object to Json object 
   * @param j A json object 
   * @param potato A potato object
   */
  friend void to_json(json& j, const Potato& potato);
  /**
   * Converts Json object to Potato object 
   * @param j A json object 
   * @param potato A potato object
   */
  friend void from_json(const json& j, Potato& potato);
private:
  string name_;
  size_t age_;
  string type_;
  string description_;
  string image_url_;
  string room_;
  string room_url_;
  float love_rating_;
  vector<Dialogue> character_dialogue_;
  size_t current_dialogue_;
};

} // namespace datingsim
