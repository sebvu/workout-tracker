#include "exercises.hpp"
#include <iostream>

/* Exercise */

std::optional<std::vector<std::string>>
Exercise::parseOptionalVectorArray(toml::array *arr) {}

Exercise::Exercise(toml::table &exercise) {}

std::string Exercise::getName() const {}

const std::optional<std::vector<std::string>> &
Exercise::getPrimaryMuscles() const {}

const std::optional<std::vector<std::string>> &
Exercise::getSecondaryMuscles() const {}

std::string Exercise::getCommentary() const {}

const std::optional<std::vector<std::string>> &
Exercise::getInstructions() const {}

/* ExerciseCategory */

ExerciseCategory::ExerciseCategory(toml::table &category) {}

int ExerciseCategory::getTotalExercise() const {}

const std::vector<Exercise> &ExerciseCategory::getExerciseList() const {}

void ExerciseCategory::printExercises() const {}

/* Exercises */

Exercises::Exercises(toml::table &config) {}

int Exercises::getTotalExercise() const {}
const std::vector<ExerciseCategory> &Exercises::getExerciseCategories() const {}
void Exercises::printCategories() const {}
