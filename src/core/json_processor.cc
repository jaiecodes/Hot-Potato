#include <fstream>
#include "core/json_processor.h"

namespace datingsim {

json JsonProcessor::ReadFile(const std::string& file_path) {
  std::ifstream ifs(file_path);
  json j;
  ifs >> j;
  return j;
}

void JsonProcessor::WriteFile(const std::string& file_path, const json& j) {
  std::ofstream ofs(file_path);
  ofs << std::setw(4) << j << std::endl;
}

} // namespace datingsim