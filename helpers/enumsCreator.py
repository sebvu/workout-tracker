import tomllib
from pathlib import Path

PARENT_DIR = Path(__file__).resolve().parent.parent
CONFIG_TOML = PARENT_DIR / "config.toml"
EXERCISES_TOML = PARENT_DIR / "toml" / "exercises.toml"

# create a enums folder with all relevant enums

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
        

### VARIANT ENUMS ###

# write the header guards

# sub groups
for categoryName, exerciseNames in categories.items():
    newName = categoryName.replace(" ", "")
    fileName = newName[0].lower() + newName[1:]
    # include to enumsVarian
    with open(f"{PARENT_DIR}/include/enums/{fileName}.hpp", "w") as enumsFile:
        # header guard
        enumsFile.write(f"#ifndef {newName.upper()}_HPP\n#define {newName.upper()}_HPP\n\n")
        # enum class
        fullCategoryName = f"{categoryName.replace(" ", "")}"
        # appending names to enumNameArray
        enumsFile.write(f"enum class {fullCategoryName} {{")
        for name in exerciseNames:
            enumsFile.write(f"\n\t{name.replace(" ", "_").replace("-", "_").replace("(", "").replace(")", "")},")
        enumsFile.write("\n};")
        enumsFile.write(f"\n\n#endif // {newName.upper()}_HPP")
