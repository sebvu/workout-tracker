#include "exceptions.hpp"
#include "exercises.hpp"
#include "toml.hpp"
#include <cstdlib>
#include <iostream>

void checkArguments(int argc, char *argv[]) {
  if (argc != 2) {
    throw InvalidArgumentCount(argc);
  }
  if (std::strcmp(argv[1], "config.toml") != 0) {
    throw InvalidArgumentUsage(argv[1]);
  }
}

template <typename T>
bool verifyPath(const T configPath, const std::string &stringPath) {
  return configPath ? true : throw InvalidConfigurationFile(stringPath);
}

void verifyPaths(const toml::table config) {
  verifyPath(config["config"], "config");
  verifyPath(config["config"]["important"], "config.important");
  verifyPath(config["config"]["important"]["toml_path"],
             "config.important.toml_path");
  verifyPath(config["config"]["important"]["exercise_file"],
             "config.important.exercise_file");
}

const toml::table getExercises(const toml::table config) {
  verifyPaths(config);
  std::optional<std::string>
    tomlPath = config["config"]["important"]["toml_path"].value<std::string>(),
    exerciseFileName =
      config["config"]["important"]["exercise_file"].value<std::string>();
  return toml::parse_file(*tomlPath + *exerciseFileName);
}

int main(int argc, char *argv[]) {
  try {
    // check for valid arguments
    checkArguments(argc, argv);

    const toml::table configToml = toml::parse_file(argv[1]);

    const toml::table exercisesToml = getExercises(configToml);

    std::cout << exercisesToml << std::endl;

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
