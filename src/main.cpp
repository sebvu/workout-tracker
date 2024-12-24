#include "exceptions.hpp"
#include "exercises.hpp"
#include "helpers.hpp"
#include <cstdlib>
#include <iostream>
#include <toml++/toml.hpp>

int main(int argc, char *argv[]) {
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

  try {
    // check for valid arguments
    checkArguments(argc, argv);

    const toml::table configToml = toml::parse_file(argv[1]);

    const toml::table exercisesToml = getExercises(configToml);

    std::cout << "works" << std::endl;

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
