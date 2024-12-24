import tomllib
from pathlib import Path

PARENT_DIR = Path(__file__).resolve().parent.parent
CUSTOM_ENUMS = PARENT_DIR / "include" / "customEnums.hpp"
CONFIG_TOML = PARENT_DIR / "config.toml"
EXERCISES_TOML = PARENT_DIR / "toml" / "exercises.toml"

# create a customEnums.hpp file with all relevant enums

customEnums = open(CUSTOM_ENUMS, "w")
configToml = open(CONFIG_TOML, "rb")
exercisesTOML = open(EXERCISES_TOML, "rb")

configData = tomllib.load(configToml)
exercisesData = tomllib.load(exercisesTOML)

# parse through categories and exercise names and organize into a dictionary
categories = dict()

### EXERCISES.TOML ###

for category in exercisesData["category"]:
    exercises = []
    for exercise in category["exercise"]:
        exercises.append(exercise["name"])
    exercises.sort()
    categories[category["name"]] = exercises

### CONFIG.TOML ###

if "custom" in configData["config"]:
    for custom in configData["config"]["custom"]:
        category = custom["category"]
        categories[category].append(custom["name"]).sort()
        

### CUSTOMENUMS.HPP ###


# write the header guards

customEnums.write("#ifndef CUSTOMENUMS_HPP\n#define CUSTOMENUMS_HPP\n\n")

# muscle groups
customEnums.write("enum class MuscleGroup {")
keys_list = categories.keys()
for categoryName in keys_list:
    customEnums.write(f"\n\t{categoryName.replace(" ", "_")},")
customEnums.write("\n};")

# sub groups
for categoryName, exerciseNames in categories.items():
    customEnums.write(f"\n\nenum class {categoryName.replace(" ", "")}Exercise {{")
    for name in exerciseNames:
        customEnums.write(f"\n\t{name.replace(" ", "_").replace("-", "_").replace("(", "").replace(")", "")},")
    customEnums.write("\n};")

customEnums.write("\n\n#endif // CUSTOMENUMS_HPP")
