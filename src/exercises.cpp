#include "exercises.hpp"
#include <iostream>

/* Exercise
 * variables:
 * const std::string name;
 * std::optional<std::vector<std::string>> primary_muscles;
 * std::optional<std::vector<std::string>> secondary_muscles;
 * const std::string commentary;
 * std::optional<std::vector<std::string>> instructions;
 * */

Exercise::Exercise(const toml::table &exercise)
  : name(exercise["name"].as_string()->value_or("undefined")),
    commentary(exercise["commentary"].as_string()->value_or("undefined")) {
  primary_muscles =
    exercise["primary_muscles"]
      ? parseOptionalVectorArray(exercise["primary_muscles"].as_array())
      : std::nullopt;
  secondary_muscles =
    exercise["secondary_muscles"]
      ? parseOptionalVectorArray(exercise["secondary_muscles"].as_array())
      : std::nullopt;
  instructions =
    exercise["instructions"]
      ? parseOptionalVectorArray(exercise["instructions"].as_array())
      : std::nullopt;
}

std::optional<std::vector<std::string>>
Exercise::parseOptionalVectorArray(const toml::array *arr) {
  std::vector<std::string> vector;

  for (const auto &node : *arr) {
    vector.push_back(node.as_string()->value_or("undefined"));
  }

  return vector;
}

const std::string Exercise::getName() const { return name; }

const std::optional<std::vector<std::string>> &
Exercise::getPrimaryMuscles() const {
  return primary_muscles;
}

const std::optional<std::vector<std::string>> &
Exercise::getSecondaryMuscles() const {
  return secondary_muscles;
}

const std::string Exercise::getCommentary() const { return commentary; }

const std::optional<std::vector<std::string>> &
Exercise::getInstructions() const {
  return instructions;
}

/* ExerciseCategory
 * variables:
 * const std::string categoryName;
 * std::vector<Exercise> exerciseList;
 * const int totalExercises;
 * */

ExerciseCategory::ExerciseCategory(const toml::table &category)
  : categoryName(category["name"].as_string()->value_or("undefined")),
    totalExercises(category["total"].as_integer()->value_or(-1)) {
  for (int i = 0; i < totalExercises; i++) {
    exerciseList.push_back(Exercise(*category["exercise"][i].as_table()));
  }
}

const std::string ExerciseCategory::getName() const { return categoryName; }
int ExerciseCategory::getTotalExercise() const { return totalExercises; }
const std::vector<Exercise> &ExerciseCategory::getExerciseList() const {
  return exerciseList;
}
void ExerciseCategory::printExercises() const {
  for (const auto &exercise : exerciseList) {
    std::cout << exercise.getName() << std::endl;
  }
}

/* ExerciseTable
 * variables:
 * const int totalExercises;
 * const int totalCategories;
 * std::vector<ExerciseCategory> exerciseCategories;
 * */

ExerciseTable::ExerciseTable(const toml::table &config)
  : totalExercises(config["totalExercises"].as_integer()->value_or(-1)),
    totalCategories(config["totalCategories"].as_integer()->value_or(-1)) {
  for (int i = 0; i < totalCategories; i++) {
    exerciseCategories.push_back(
      ExerciseCategory(*config["category"][i].as_table()));
  }
}

int ExerciseTable::getTotalExercise() const { return totalExercises; }

int ExerciseTable::getTotalCategories() const { return totalCategories; }

const std::vector<ExerciseCategory> &
ExerciseTable::getExerciseCategories() const {
  return exerciseCategories;
}

void ExerciseTable::printCategories() const {
  for (const auto &category : exerciseCategories) {
    std::cout << category.getName() << std::endl;
  }
}
