#include "exceptions.hpp"
#include "exercises.hpp"
#include "helpers.hpp"
#include "magic_enum.hpp"
#include "toml.hpp"
#include <cstdlib>
#include <iostream>

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

const ExerciseCategory getCategory(const MuscleGroup &category,
                                   const toml::table &exercisesToml) {
  switch (category) {
  case MuscleGroup::Chest:
    return ExerciseCategory(*exercisesToml["chest"].as_table());
    break;
  case MuscleGroup::Shoulder:
    return ExerciseCategory(*exercisesToml["shoulder"].as_table());
    break;
  case MuscleGroup::Biceps:
    return ExerciseCategory(*exercisesToml["Biceps"].as_table());
    break;
  case MuscleGroup::Triceps:
    return ExerciseCategory(*exercisesToml["Triceps"].as_table());
    break;
  case MuscleGroup::Legs:
    return ExerciseCategory(*exercisesToml["Legs"].as_table());
    break;
  case MuscleGroup::Back:
    return ExerciseCategory(*exercisesToml["Back"].as_table());
    break;
  case MuscleGroup::Glute:
    return ExerciseCategory(*exercisesToml["Glute"].as_table());
    break;
  case MuscleGroup::Abs:
    return ExerciseCategory(*exercisesToml["Abs"].as_table());
    break;
  case MuscleGroup::Calves:
    return ExerciseCategory(*exercisesToml["Calves"].as_table());
    break;
  case MuscleGroup::ForearmFlexors:
    return ExerciseCategory(*exercisesToml["ForearmFlexors"].as_table());
    break;
  case MuscleGroup::ForearmExtensors:
    return ExerciseCategory(*exercisesToml["ForearmExtensors"].as_table());
    break;
  case MuscleGroup::CardioTraining:
    return ExerciseCategory(*exercisesToml["CardioTraining"].as_table());
    break;
  }
};

int main(int argc, char *argv[]) {

  try {
    // check for valid arguments
    checkArguments(argc, argv);

    const toml::table configToml = toml::parse_file(argv[1]);

    const toml::table exercisesToml = getExercises(configToml);

    for (auto val : magic_enum::enum_values<MuscleGroup>()) {
      std::cout << magic_enum::enum_name(val) << std::endl;
    }

  } catch (const toml::parse_error &err) {
    std::cerr << "Error parsing file '" << err.source().path << "':\n"
              << err.description() << "\n (" << err.source().begin << ")\n";
    return EXIT_FAILURE;
  } catch (const InvalidConfigurationFile &err) {
    std::cerr << "Invalid configuration file: " << err.what() << std::endl;
    return EXIT_FAILURE;
  } catch (const InvalidArgumentUsage &err) {
    std::cerr << "Invalid argument usage: " << err.what() << std::endl;
    return EXIT_FAILURE;
  } catch (const InvalidArgumentCount &err) {
    std::cerr << "Invalud argument count: " << err.what() << std::endl;
    return EXIT_FAILURE;
  } catch (const std::exception &err) {
    std::cerr << "Exception: " << err.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
