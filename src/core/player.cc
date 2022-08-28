#include "core/player.h"

namespace datingsim {

Player::Player(const string& set_name, const string& set_type) {
  name_ = set_name;
  type_ = set_type;
}

void Player::SetName(const string& set_name) {
  name_ = set_name;
}

void Player::SetType(const string& set_type) {
  type_ = set_type;
}

const string& Player::GetName() const{
  return name_;
}

const string& Player::GetType() const{
  return type_;
}

void to_json(json& j, const Player& player) {
  j = json{{"name", player.name_},
           {"type", player.type_}};
}

void from_json(const json& j, Player& player) {
  j.at("name").get_to(player.name_);
  j.at("type").get_to(player.type_);
}

} // namespace datingsim