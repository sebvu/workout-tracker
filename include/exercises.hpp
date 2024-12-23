#ifndef EXERCISES_HPP
#define EXERCISES_HPP
#include <toml++/toml.hpp>
//

class Exercise {
  private:
  const std::string name;
  std::optional<std::vector<std::string>> primary_muscles;
  std::optional<std::vector<std::string>> secondary_muscles;
  const std::string commentary;
  std::optional<std::vector<std::string>> instructions;
  std::optional<std::vector<std::string>>
  parseOptionalVectorArray(const toml::array *arr);

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
