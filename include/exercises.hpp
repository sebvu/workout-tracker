#ifndef EXERCISES_HPP
#define EXERCISES_HPP
#include "variantEnums.hpp"
#include <toml++/toml.hpp>
#include <variant>
//

class Exercise {
  private:
  const std::string name;
  std::optional<std::vector<std::string>> primary_muscles;
  std::optional<std::vector<std::string>> secondary_muscles;
  const std::string commentary;
  std::optional<std::vector<std::string>> instructions;

  // helper function
  std::optional<std::vector<std::string>>
  parseOptionalVectorArray(const toml::array *arr);

  // optional variant enum that is category specific
  ExerciseVariant exerciseVariant;

  public:
  Exercise(const toml::table &exercise);

  const std::string getName() const;

  const std::optional<std::vector<std::string>> &getPrimaryMuscles() const;

  const std::optional<std::vector<std::string>> &getSecondaryMuscles() const;

  const std::string getCommentary() const;

  const std::optional<std::vector<std::string>> &getInstructions() const;
};

//

class ExerciseCategory {
  private:
  enum class MuscleGroup {
    Chest,
    Shoulder,
    Biceps,
    Triceps,
    Legs,
    Back,
    Glute,
    Abs,
    Calves,
    ForearmFlexors,
    ForearmExtensors,
    CardioTraining,
  };

  const std::string categoryName;

  std::vector<Exercise> exerciseList;

  const int totalExercises;

  public:
  ExerciseCategory(const toml::table &category);

  const std::string getName() const;

  int getTotalExercise() const;

  const std::vector<Exercise> &getExerciseList() const;

  void printExercises() const;
};

#endif
