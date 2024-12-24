#ifndef CUSTOMENUMS_HPP
#define CUSTOMENUMS_HPP
#include "abs.hpp"
#include "back.hpp"
#include "biceps.hpp"
#include "calves.hpp"
#include "cardioTraining.hpp"
#include "chest.hpp"
#include "forearmExtensors.hpp"
#include "forearmFlexors.hpp"
#include "glute.hpp"
#include "legs.hpp"
#include "shoulder.hpp"
#include "triceps.hpp"
#include <variant>

using ExerciseVariant =
  std::variant<Chest, Shoulder, Biceps, Triceps, Legs, Back, Glute, Abs, Calves,
               ForearmFlexors, ForearmExtensors, CardioTraining>;

#endif  // CUSTOMENUMS_HPP
