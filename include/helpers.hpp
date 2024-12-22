#ifndef HELPERS_HPP
#define HELPERS_HPP
#include "toml.hpp"
#include <string>

void checkArguments(int argc, char *argv[]);

template <typename T>
bool verifyPath(const T configPath, const std::string &stringPath);

const toml::table getExercises(const toml::table config);

#endif
