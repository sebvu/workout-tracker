# Workout tool

> Tracking workouts, making a plan, idfk.

## CONTEXT

just for tracking workouts and making my own workout plan the CS way

### How to contribute?

(i've never done this before)

- just clone the repo

setup project

- for accurate linting,
  - install [bear](https://github.com/rizsotto/Bear)
  - run `bear -- make` to generate compile_commands.json
- `make` to generate new binary `exec-main`
- `make run` to run project
- `make clean` to clean build artifacts

notes

- the python files in `src/` is left there for legacy reasons. they were initially made to scrape [strengthlog](https://www.strengthlog.com/exercise-directory/) for the curr `exercises.toml` file
- configuration options are in `config.toml`. as of `12/19/2024` (happy holidays me) there are no configuration options
