CUSTOM_ENUMS = "../include/customEnums.hpp"
CONFIG_TOML = "../config.toml"
EXERCISES_TOML = "../toml/exercises.toml"

# create a customEnums.hpp file with all relevant enums

customEnums = open(FILE_TO_OPEN, "w")

    file.write("#ifndef CUSTOMENUMS_HPP\n#define CUSTOMENUMS_HPP\n\n")
