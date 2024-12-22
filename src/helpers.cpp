#include "helpers.hpp"
#include "exceptions.hpp"

void checkArguments(int argc, char *argv[]) {
  if (argc != 2) {
    throw InvalidArgumentCount(argc);
  }
  if (std::strcmp(argv[1], "config.toml") != 0) {
    throw InvalidArgumentUsage(argv[1]);
  }
}

template <typename T>
bool verifyPath(const T configPath, const std::string &stringPath) {
  return configPath ? true : throw InvalidConfigurationFile(stringPath);
}

void verifyPaths(const toml::table config) {
  verifyPath(config["config"], "config");
  verifyPath(config["config"]["important"], "config.important");
  verifyPath(config["config"]["important"]["toml_path"],
             "config.important.toml_path");
  verifyPath(config["config"]["important"]["exercise_file"],
             "config.important.exercise_file");
}

const toml::table getExercises(const toml::table config) {
  verifyPaths(config);
  std::optional<std::string>
    tomlPath = config["config"]["important"]["toml_path"].value<std::string>(),
    exerciseFileName =
      config["config"]["important"]["exercise_file"].value<std::string>();
  return toml::parse_file(*tomlPath + *exerciseFileName);
}
