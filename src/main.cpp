#include "exercises.hpp"
#include "toml.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  toml::table exercises;
  const std::string FILE_PATH = "./toml/exercises.toml";

  try {
    // logic
  } catch (const toml::parse_error &err) {
    std::cerr << "Parsing failed:" << std::endl << err << std::endl;
    return 1;
  }
  return 0;
}
