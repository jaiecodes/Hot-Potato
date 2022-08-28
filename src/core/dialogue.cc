#include "core/dialogue.h"

namespace datingsim {

Dialogue::Dialogue(size_t set_id, const string& set_line,
                   const string& set_phase, const vector<size_t>& set_options) {
  id_ = set_id;
  line_ = set_line;
  phase_ = set_phase;
  options_ = set_options;
}

void Dialogue::SetId(size_t set_id) {
  id_ = set_id;
}

void Dialogue::SetLine(const string& set_line) {
  line_ = set_line;
}

void Dialogue::SetPhase(const string& set_phase) {
  phase_ = set_phase;
}

void Dialogue::SetOptions(const vector<size_t>& set_options) {
  options_ = set_options;
}

size_t Dialogue::GetId() const {
  return id_;
}

const string& Dialogue::GetLine() const{
  return line_;
}

const string& Dialogue::GetPhase() const{
  return phase_;
}

const vector<size_t>& Dialogue::GetOptions() const{
  return options_;
}

float Dialogue::GetLoveRating() const {
  return love_rating_;
}

bool Dialogue::GetIsInterlude() const {
  return is_interlude_;
}

void to_json(json& j, const Dialogue& dialogue) {
  j = json{{"id", dialogue.id_},
           {"line", dialogue.line_},
           {"phase", dialogue.phase_},
           {"options", dialogue.options_},
           {"love_rating", dialogue.love_rating_},
           {"is_interlude", dialogue.is_interlude_}};
}

void from_json(const json& j, Dialogue& dialogue) {
  j.at("id").get_to(dialogue.id_);
  j.at("line").get_to(dialogue.line_);
  j.at("phase").get_to(dialogue.phase_);
  j.at("options").get_to(dialogue.options_);
  j.at("love_rating").get_to(dialogue.love_rating_);
  j.at("is_interlude").get_to(dialogue.is_interlude_);
}

} // namespace datingsim