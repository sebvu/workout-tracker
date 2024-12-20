#include "exceptions.hpp"
#include <iostream>

// invalid argument count

InvalidArgumentCount::InvalidArgumentCount(int argc) {
  message =
    "Invalid argument count: " + std::to_string(argc) + "\nExpect 2 arguments.";
}

const char *InvalidArgumentCount::what() const noexcept {
  return message.c_str();
}

// invalid argument usage

InvalidArgumentUsage::InvalidArgumentUsage(const std::string &arg) {
  message = "Argument " + arg + " is invalid.\nExpect config.toml";
}

const char *InvalidArgumentUsage::what() const noexcept {
  return message.c_str();
}

// invalid configuration file

InvalidConfigurationFile::InvalidConfigurationFile(const std::string lookup) {
  message = "Could not find path " + lookup +
            ".\nPlease refer to docs for correct configuration file: "
            "https://github.com/sebvu/workout-tracker";
}

const char *InvalidConfigurationFile::what() const noexcept {
  return message.c_str();
}
