#include "exercises.hpp"
#include <iostream>

// Exercise

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

// ExerciseCategory

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
