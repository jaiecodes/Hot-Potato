#pragma once

#include <string>
#include <vector>
#include "json_processor.h"

namespace datingsim {
using std::string;
using std::vector;

/**
 * A class represent a dialogue node in branching dialogue
 */
class Dialogue {
public:
  Dialogue() = default;
  /**
   * Constructs a dialogue object with all member variables initialized
   */
  Dialogue(size_t set_id, const string& set_line,
           const string& set_phase, const vector<size_t>& set_options);
  /**
   * Sets the id for this dialogue object
   * @param set_id A size_t representing the ID of the dialogue object
   */
  void SetId(size_t set_id);
  /**
   * Sets the line for this dialogue object
   * @param set_line A string representing the line text to 
   * display for this dialogue object
   */
  void SetLine(const string& set_line);
  /**
   * Sets the game phase for this dialogue object
   * @param set_phase A string representing that game phase 
   * this dialogue object belongs to 
   */
  void SetPhase(const string& set_phase);
  /**
   * Sets the options for this dialogue object
   * @param set_options A vector of size_t's representing the id's of the 
   * succeeding dialogue objects 
   */
  void SetOptions(const vector<size_t>& set_options);
  /**
   * Gets the id of this dialogue object
   * @return A size_t representing the ID of the dialogue object
   */
  size_t GetId() const;
  /**
   * Gets the line text of this dialogue object
   * @return A string representing the line text to 
   * display for this dialogue object
   */
  const string& GetLine() const;
  /**
   * Gets the game phase of this dialogue object
   * @return A string representing that game phase 
   * this dialogue object belongs to 
   */
  const string& GetPhase() const;
  /**
   * Gets the dialogue options of this dialogue object
   * @return A vector of size_t's representing the id's of the 
   * succeeding dialogue objects 
   */
  const vector<size_t>& GetOptions() const;
  
  float GetLoveRating() const;
  
  bool GetIsInterlude() const;
  /**
   * Converts Dialogue object to Json object 
   * @param j A json object 
   * @param dialogue A dialogue object
   */
  friend void to_json(json& j, const Dialogue& dialogue);
  /**
   * Converts Json object to Dialogue object 
   * @param j A json object 
   * @param dialogue A dialogue object
   */
  friend void from_json(const json& j, Dialogue& dialogue);
private:
  string phase_;
  size_t id_;
  string line_;
  vector<size_t> options_;
  float love_rating_;
  bool is_interlude_;
};

}
