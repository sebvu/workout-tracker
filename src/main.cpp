#include "exercises.hpp"
#include "toml.hpp"
#include <iostream>

int main() {

  toml::table tbl = toml::parse_file("toml/exercises.toml");

  std::cout << tbl << std::endl;

  exercises exercise = exercises();

  exercise.test();  // should work!!
}
