#include "core/potato.h"

namespace datingsim {

Potato::Potato(const string& set_name, size_t set_age,
               const string& set_type, const string& set_description,
               const string& set_room, float set_love_rating,
               const vector<Dialogue>& set_character_dialogue,
               size_t set_current_dialogue) {
  name_ = set_name;
  age_ = set_age;
  type_ = set_type;
  description_ = set_description;
  room_ = set_room;
  love_rating_ = set_love_rating;
  character_dialogue_ = set_character_dialogue;
  current_dialogue_ = set_current_dialogue;
}

void Potato::SetName(const string& set_name) {
  name_ = set_name;
}

void Potato::SetAge(size_t set_age) {
  age_ = set_age;
}

void Potato::SetType(const string& set_type) {
  type_ = set_type;
}

void Potato::SetDescription(const string& set_description) {
  description_ = set_description;
}

void Potato::SetRoom(const string& set_room) {
  room_ = set_room;
}

void Potato::SetLoveRating(float set_love_rating) {
  love_rating_ = set_love_rating;
}

void Potato::SetCharacterDialogue(const vector<Dialogue>& set_character_dialogue) {
  character_dialogue_ = set_character_dialogue;
}

void Potato::SetCurrentDialogue(size_t set_current_dialogue) {
  current_dialogue_ = set_current_dialogue;
}

string Potato::GetName() const &{
  return name_;
}

size_t Potato::GetAge() const {
  return age_;
}

const string& Potato::GetType() const{
  return type_;
}

const string& Potato::GetDescription() const{
  return description_;
}

const string& Potato::GetImageUrl() const {
  return image_url_;
}

const string& Potato::GetRoom() const{
  return room_;
}

const string& Potato::GetRoomUrl() const{
  return room_url_;
}


float Potato::GetLoveRating() const {
  return love_rating_;
}

const vector<Dialogue>& Potato::GetCharacterDialogue() const {
  return character_dialogue_;
}

size_t Potato::GetCurrentDialogue() const {
  return current_dialogue_;
}

void to_json(json& j, const Potato& potato) {
  j = json{{"name", potato.name_},
           {"age", potato.age_},
           {"type", potato.type_},
           {"description", potato.description_},
           {"image_url", potato.image_url_},
           {"room", potato.room_},
           {"room_url", potato.room_url_},
           {"love_rating", potato.love_rating_},
           {"character_dialogue", potato.character_dialogue_},
           {"current_dialogue", potato.current_dialogue_}};
}

void from_json(const json& j, Potato& potato) {
  j.at("name").get_to(potato.name_);
  j.at("age").get_to(potato.age_);
  j.at("type").get_to(potato.type_);
  j.at("description").get_to(potato.description_);
  j.at("image_url").get_to(potato.image_url_);
  j.at("room").get_to(potato.room_);
  j.at("room_url").get_to(potato.room_url_);
  j.at("love_rating").get_to(potato.love_rating_);
  j.at("character_dialogue").get_to(potato.character_dialogue_),
  j.at("current_dialogue").get_to(potato.current_dialogue_);
}


} // namespace datingsim