# Workout Planner

the quick CLI way of building and organizing your workout plans

<hr />

**❗WARNING❗**

- This project is NOT done and there will be bugs.

<hr />

### 📓 CONTEXT

I got bored one day, and I realized that;

> "wow, making workouts is a lot of bologna."

so, I made this to make my own workout plans!

<hr />

### 🛠️ INSTALLATION & USAGE

#### Installation & quick usage

1. clone the repo

```sh
git clone https://github.com/sebvu/workout-tracker.git
```

2. run `make` to setup basic project deps

3. run `make run` to run project!

#### Custom Usages

- there is a `config.toml` file in the root directory. within the stated guidelines of the config file, you are **able to create your own custom exercise entires** by adding your toml table snippet

```toml
[[config.custom]]
category = "Abs"
name = "Hallow Hold"
primary_muscles = ["Abs"]
commentary = "This is a great exercise for building core strength... etc"
instructions = [
  "Hold your body in a hollow position",
  "Keep your lower back pressed into the floor",
  "etc.. more copilot comments",
]
```

- once you add a new toml table snippet, run `make` once more!

<hr />

### How to contribute?

(WIP, but feel free to fork and make any current contriutions)
