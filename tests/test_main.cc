#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <core/potato.h>
#include <core/player.h>
#include <core/dialogue.h>
#include "core/json_processor.h"

TEST_CASE("Json Processing") {
  using json = nlohmann::json;
  std::string json_potato = "/Users/Yousher/CLionProjects/Cinder/my-projects"
                            "/final-project-Jeideun/data/test_potato.json";
  std::string json_player = "/Users/Yousher/CLionProjects/Cinder/my-projects"
                            "/final-project-Jeideun/data/test_player.json";
  std::string json_dialogue = "/Users/Yousher/CLionProjects/Cinder/my-projects"
                              "/final-project-Jeideun/data/test_dialogue.json";
  json j_test;
  
  SECTION("Potato: Read") {
    j_test = datingsim::JsonProcessor::ReadFile(json_potato);
    REQUIRE(j_test.at("name") == "Mr.Potato");
    REQUIRE(j_test.at("age") == 43);
    REQUIRE(j_test.at("type") == "plain");
    REQUIRE(j_test.at("description") == "Likes to be taken apart");
    REQUIRE(j_test.at("room") == "living room");
    REQUIRE(j_test.at("love_rating") == 0.5);
    REQUIRE(j_test.at("character_dialogue").size() == 2);
    REQUIRE(j_test.at("current_dialogue") == 0);
  }

  SECTION("Player: Read") {
    j_test = datingsim::JsonProcessor::ReadFile(json_player);
    REQUIRE(j_test.at("name") == "Y/N");
    REQUIRE(j_test.at("type") == "Potato");
  }

  SECTION("Player: Read") {
    j_test = datingsim::JsonProcessor::ReadFile(json_dialogue);
    REQUIRE(j_test.at("id") == 0);
    REQUIRE(j_test.at("line") == "Hello welcome to Potatoland");
    REQUIRE(j_test.at("phase") == "tutorial");
    std::vector<size_t> options = j_test.at("options");
    REQUIRE(options[0] == 0);
    REQUIRE(options[1] == 1);
  }

  SECTION("Potato: Object") {
    j_test = datingsim::JsonProcessor::ReadFile(json_potato);
    datingsim::Potato test_potato = j_test;
    REQUIRE(test_potato.GetName() == "Mr.Potato");
    REQUIRE(test_potato.GetAge() == 43);
    REQUIRE(test_potato.GetType() == "plain");
    REQUIRE(test_potato.GetDescription() == "Likes to be taken apart");
    REQUIRE(test_potato.GetRoom() == "living room");
    REQUIRE(test_potato.GetLoveRating() == 0.5);
    std::vector<datingsim::Dialogue> dialogue = test_potato.GetCharacterDialogue();
    REQUIRE(dialogue[0].GetId() == 0);
    REQUIRE(dialogue[1].GetId() == 1);
    REQUIRE(test_potato.GetCurrentDialogue() == 0);
  }

  SECTION("Player: Object") {
    j_test = datingsim::JsonProcessor::ReadFile(json_player);
    datingsim::Player test_player = j_test;
    REQUIRE(test_player.GetName() == "Y/N");
    REQUIRE(test_player.GetType() == "Potato");
  }

  SECTION("Dialogue: Object") {
    j_test = datingsim::JsonProcessor::ReadFile(json_dialogue);
    datingsim::Dialogue test_dialogue = j_test;
    REQUIRE(test_dialogue.GetId() == 0);
    REQUIRE(test_dialogue.GetLine() == "Hello welcome to Potatoland");
    REQUIRE(test_dialogue.GetPhase() == "tutorial");
    std::vector<size_t> options = test_dialogue.GetOptions();
    REQUIRE(options[0] == 0);
    REQUIRE(options[1] == 1);
  }

  SECTION("Potato: Write") {
    j_test = datingsim::JsonProcessor::ReadFile(json_potato);
    std::string json_string = "{\"age\":43,\"character_dialogue\":[{\"id\":0,\""
                              "line\":\"Hello welcome to Potatoland\",\"options"
                              "\":[0,1],\"phase\":\"tutorial\"},{\"id\":1,\"line"
                              "\":\"Hello welcome to Potatoland\",\"options\":"
                              "[0,1],\"phase\":\"tutorial\"}],\"current_dialogue"
                              "\":0,\"description\":\"Likes to be taken apart\","
                              "\"love_rating\":0.5,\"name\":\"Mr.Potato\",\"room"
                              "\":\"living room\",\"type\":\"plain\"}";
    std::stringstream ss;
    ss << j_test;
    REQUIRE(ss.str() == json_string);
  }

  SECTION("Player: Write") {
    j_test = datingsim::JsonProcessor::ReadFile(json_player);
    std::string json_string = "{\"name\":\"Y/N\",\"type\":\"Potato\"}";
    std::stringstream ss;
    ss << j_test;
    REQUIRE(ss.str() == json_string);
  }

  SECTION("Dialogue: Write") {
    j_test = datingsim::JsonProcessor::ReadFile(json_dialogue);
    std::string json_string = "{\"id\":0,\"line\":\"Hello welcome to "
                              "Potatoland\",\"options\":[0,1],\"phase"
                              "\":\"tutorial\"}";
    std::stringstream ss;
    ss << j_test;
    REQUIRE(ss.str() == json_string);
  }

  SECTION("Potato: Json") {
    std::vector<datingsim::Dialogue> dialogue;
    std::vector<size_t> options = {0, 1};
    datingsim::Dialogue test_dialogue(0,
                                      "Hello welcome to Potatoland",
                                      "tutorial", options);
    datingsim::Dialogue test_dialogue_2(1,
                                      "Hello welcome to Potatoland",
                                      "tutorial", options);
    dialogue.push_back(test_dialogue);
    dialogue.push_back(test_dialogue_2);
    datingsim::Potato test_potato("Mr.Potato", 43, 
                                  "plain",
                                  "Likes to be taken apart", 
                                  "living room", 0.5, 
                                  dialogue, 0);
    j_test = test_potato;
    REQUIRE(j_test.at("name") == "Mr.Potato");
    REQUIRE(j_test.at("age") == 43);
    REQUIRE(j_test.at("type") == "plain");
    REQUIRE(j_test.at("description") == "Likes to be taken apart");
    REQUIRE(j_test.at("room") == "living room");
    REQUIRE(j_test.at("love_rating") == 0.5);
    REQUIRE(j_test.at("character_dialogue").size() == 2);
    REQUIRE(j_test.at("current_dialogue") == 0);
  }

  SECTION("Player: Json") {
    datingsim::Player test_player("Y/N", "Potato");
    j_test = test_player;
    REQUIRE(j_test.at("name") == "Y/N");
    REQUIRE(j_test.at("type") == "Potato");
  }

  SECTION("Dialogue: Json") {
    std::vector<size_t> options = {0, 1};
    datingsim::Dialogue test_dialogue(0, 
                                      "Hello welcome to Potatoland",
                                      "tutorial", options);
    j_test = test_dialogue;
    REQUIRE(test_dialogue.GetId() == 0);
    REQUIRE(test_dialogue.GetLine() == "Hello welcome to Potatoland");
    REQUIRE(test_dialogue.GetPhase() == "tutorial");
    std::vector<size_t> json_options = test_dialogue.GetOptions();
    REQUIRE(json_options[0] == 0);
    REQUIRE(json_options[1] == 1);
  }
   
}