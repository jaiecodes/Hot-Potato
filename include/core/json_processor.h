#pragma once

#include "../../cmake-build-debug/_deps/json-src/include/nlohmann/json.hpp"

namespace datingsim {

using json = nlohmann::json;
/**
 * Class that processes files and jsons
 */
class JsonProcessor {
public:
  /**
   * A static function that reads from file and creates a json object
   * @param file_path Path of file to read from
   * @return A json object representing information in json file
   */
  static json ReadFile(const std::string &file_path);
  /**
   * A static function that writes from json object to file 
   * @param file_path Path of file to write to
   * @param j A json object representing information
   */
  static void WriteFile(const std::string &file_path, const json &j);
};
} // namespace datingsim


