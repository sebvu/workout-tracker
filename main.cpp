#include "libs/toml.hpp"
#include <iostream>

int main() {
  toml::table tbl = toml::parse_file("toml/exercises.toml");
  std::cout << tbl << std::endl << std::endl;
  std::cout << tbl["powerlifting"]["back"] << std::endl;
}
