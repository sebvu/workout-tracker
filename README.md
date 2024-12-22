# Workout tool

> Tracking workouts, making a plan, idfk.

## CONTEXT

just for tracking workouts and making my own workout plan the CS way

### How to contribute?

(i've never done this before)

- just clone the repo
- setup base project

  - for accurate linting,
    - install [bear](https://github.com/rizsotto/Bear)
    - run `bear -- make` to generate compile_commands.json
  - `make` to generate new binary `exec-main`
  - `make run` to run project
  - `make clean` to clean build artifacts

- if you want to use the webscraper
  - setup python environment
    - type either of the following on the project root directory
    - windows: `python -m venv env`
    - mac/linux: `python3 -m venv env`
  - activate your virtual env
  - locate `docs/requirements.txt` and `pip install -r requirements.txt` to get all necessary packages
  - to use webscrapers **AUTOMODE**, create `src/creds.py` and set `API_KEY = ` to your openai key
    - if you do not have it installed, set the **AUTOMODE** variable to false (i have no clue if there's bugs with doing it manually)
    - if you want to do it manually even with the openai key, you can still turn automode off as there is a optional ai option for some of the required inputs

notes

- configuration options are in `config.toml`, but there isn't anything to configure yet
- added back `webscraper.py` (sorry for how messy it is)
