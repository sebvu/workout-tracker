# REFACTORED WEB SCRAPER
# This script scrapes the StrengthLog website for exercise information and writes it to a TOML file.
# Used once to initially generate an accurate configuration file for the exercise database.

import json
import re
import time

import openai
import requests
from bs4 import BeautifulSoup

import creds

API_KEY = creds.API_KEY

# GLOBAL VARIABLES
MAIN_URL = "https://www.strengthlog.com/exercise-directory/"
FILE_TO_OPEN = "../toml/exercises.toml"
CLEAR = "\033[0m\n"
LIGHTPURPLE = "\033[1;36m"
BLUE = "\033[1;34m"
RED = "\033[1;31m"
AUTOMODE = True  # ADVISORY! Will automatically choose AI option.
openai.api_key = API_KEY
MODEL = "gpt-4o-mini"

# FUNCTIONS


def findSections(SOUP) -> list:
    sections = []

    listOfAllExercisesHeader = SOUP.find(
        "a", string=re.compile(r"Muscle Directory*", re.I)
    )

    if listOfAllExercisesHeader:
        listOfAllExercises = listOfAllExercisesHeader.find_next("ul")
        allExerciseAnchors = listOfAllExercises.find_all("a")
        for listAnchor in allExerciseAnchors:
            # list name
            listName = listAnchor.text
            # calculating total exercises & pulling URLs
            totalExercises, exercisesArr = 0, []
            listHref = listAnchor.get("href")
            listID = listHref.lstrip("#")
            idBlockParent = SOUP.find(id=listID).parent
            orderedListBlock = idBlockParent.find_next("ol")
            listExerciseItems = orderedListBlock.find_all("li")
            for listAnchor in listExerciseItems:
                listAnchor = listAnchor.find("a")
                totalExercises += 1
                tempExerciseURLPair = {
                    "Name": listAnchor.text,
                    "URL": listAnchor.get("href"),
                }
                exercisesArr.append(tempExerciseURLPair)
            # assembly
            tempDict = {
                "muscleGroup": listName,
                "total": totalExercises,
                "exercises": exercisesArr,
            }
            sections.append(tempDict)
    return sections


def writeToFile(file, sections) -> None:
    # VARIABLES
    total = sum(section["total"] for section in sections)
    header = "# TOML file scraped from StrengthLog source https://www.strengthlog.com/exercise_directory/"
    counter = 1  # for tracking

    # FUNCTIONS

    def cardioGPTResponse(exercise: str, steps: int) -> list:
        instructions = []
        chatLog = []
        SYSTEM_CONTEXT = f"You are to explain the steps for how to perform {exercise}. There will be {steps} steps in total. Respond one step at a time in chronological order. In your text, do NOT specify the step you are on like 'Step X:'. Just explain the step itself. Make sure this is a smaller response then usual as this is instructions on a list."

        chatLog.append({"role": "system", "content": SYSTEM_CONTEXT})

        for step in range(1, steps + 1):
            user_message = (
                f"Provide step {step} of {steps} for the exercise {exercise}."
            )
            chatLog.append({"role": "user", "content": user_message})

            response = openai.chat.completions.create(model=MODEL, messages=chatLog)
            assistant_response = response.choices[0].message.content.strip("\n").strip()

            chatLog.append({"role": "assistant", "content": assistant_response})
            instructions.append(assistant_response.replace('"', "'"))

            print(f"{BLUE}Step {step}: {assistant_response}{CLEAR}")
        return instructions

    def gptResponse(exercise: str) -> str:
        # VARIABLES
        chatLog = []
        SYSTEM_CONTEXT = f"You are describing the exercise {exercise} for a configuration file. The description of {exercise} should be a paragraph long. The user will talk to you and adjust your response as needed. However, ONLY respond with the paragraph and do NOT make any new unecessary lines or ask if the user would like any more help."

        initialPrompt = f"Could you describe {exercise} please?"
        print(f"describing {exercise}..")
        chatLog.append({"role": "user", "content": initialPrompt})
        chatLog.append({"role": "system", "content": SYSTEM_CONTEXT})

        # first API call to generate initial response
        response = openai.chat.completions.create(model=MODEL, messages=chatLog)
        assistant_response = response.choices[0].message.content.strip("\n").strip()
        chatLog.append({"role": "assistant", "content": assistant_response})
        print(f"{BLUE}{assistant_response}{CLEAR}")

        return assistant_response

    def printSummary() -> None:
        categoryCounter = 0
        for section in sections:
            file.write(f"\n# - {section["muscleGroup"]}: {section["total"]}")
            categoryCounter += 1
        file.write(f"\n\ntotalCategories = {categoryCounter}")

    def primaryMuscle(SOUP, muscleGroup):
        primaryMuscleHeader = SOUP.find("h3", string=re.compile(r"Primary*", re.I))
        primaryList = []
        if primaryMuscleHeader:
            primaryMuscleList = primaryMuscleHeader.find_next_sibling("ul")
            listItems = primaryMuscleList.find_all("li")
            for listItem in listItems:
                primaryList.append(listItem.text)
        elif muscleGroup == "Cardio Training":
            primaryMuscleList = SOUP.find("ul", attrs={"class": "wp-block-list"})
            listItems = primaryMuscleList.find_all("li")
            for listItem in listItems:
                primaryList.append(listItem.text)
        else:
            print(f"{RED}No primary muscle header found. Exiting.{CLEAR}")
            exit()
        file.write(f"primary_muscles = {json.dumps(primaryList)}\n")
        return primaryMuscleHeader

    def secondaryMuscle(SOUP, muscleGroup) -> None:
        secondaryMuscleHeader = SOUP.find("h3", string=re.compile(r"Secondary*", re.I))
        if secondaryMuscleHeader:
            secondaryList = []
            secondaryMuscleList = secondaryMuscleHeader.find_next_sibling("ul")
            listItems = secondaryMuscleList.find_all("li")
            for listItem in listItems:
                secondaryList.append(listItem.text)
            file.write(f"secondary_muscles = {json.dumps(secondaryList)}\n")
        else:
            if muscleGroup != "Cardio Training":
                print(f"{LIGHTPURPLE}No secondary muscle header found{CLEAR}")

    def commentary(SOUP, name) -> None:
        commentaryHeader = SOUP.find("h2", string=re.compile(r"^Commentary$", re.I))
        if commentaryHeader:
            commentary = commentaryHeader.find_next_sibling("p")
            commentaryText = commentary.text.replace('"', "'")
            file.write(f'commentary = "{commentaryText}"\n')
        else:
            if not AUTOMODE:
                choice = input(
                    f"{LIGHTPURPLE}There is no commentary for {name}.\n[1] AI\n[*] Manual{CLEAR}\n"
                )
                match choice:
                    case "1":
                        response = gptResponse(name)
                        file.write(f'commentary = "{response}"\n')
                        return
                    case _:
                        newCommentary = input(
                            f"{LIGHTPURPLE}Please provide commentary for {name} (DO NOT INCLUDE DOUBLE QUOTES): {CLEAR}"
                        )
                        file.write(f'commentary = "{newCommentary}"\n')
                        return
            else:
                response = gptResponse(name)
                file.write(f'commentary = "{response}"\n')

    def instructions(primaryMuscleHeader, muscleGroup, name) -> None:
        if muscleGroup != "Cardio Training":
            if primaryMuscleHeader.find_next("div"):
                instructionsDiv = primaryMuscleHeader.find_next("div")
                orderedInstructionList = instructionsDiv.find_next("ol")
                listItems = orderedInstructionList.find_all("li")
                file.write("instructions = [\n")
                for listItem in listItems:
                    listItemText = listItem.text.replace('"', "'")
                    file.write(f'\t"{listItemText}",\n')
                file.write("]\n")
            else:
                print(f"{LIGHTPURPLE}Div container for instructions not found{CLEAR}\n")
        else:
            listItems = []
            if not AUTOMODE:
                instructionStep = 1
                while True:
                    newInstruction = input(
                        f"{LIGHTPURPLE}Please provide step {instructionStep} for {name}. (type [end] when done) (DO NOT INCLUDE QUOTES): {CLEAR}"
                    )
                    if newInstruction.lower() == "end":
                        break
                    listItems.append(newInstruction)
                    instructionStep += 1
            else:
                listItems = cardioGPTResponse(name, 5)
            file.write("instructions = [\n")
            for listItem in listItems:
                file.write(f'\t"{listItem}",\n')
            file.write("]\n")

    file.write(f"{header}\n\n# total exercises: {total}")
    printSummary()
    file.write(f"\n\ntotal = {total}\n\n")

    for section in sections:
        if counter != 1:
            file.write("###\n\n")
        file.write(
            f'[[category]]\n\nname = "{section["muscleGroup"]}"\n\ntotal = {section["total"]}\n\n'
        )
        for exercise in section["exercises"]:
            PAGE_TO_SCRAPE = requests.get(exercise["URL"])
            time.sleep(0.5)  # buffer time to allow server to catch up
            STATUS_CODE = PAGE_TO_SCRAPE.status_code
            if STATUS_CODE == 200:
                exerciseName = exercise["Name"]
                print(f"{counter} | {exerciseName}")
                SOUP = BeautifulSoup(PAGE_TO_SCRAPE.text, "html.parser")
                muscleGroup = section["muscleGroup"]
                file.write("[[category.exercise]]\n")
                file.write(f'name = "{exercise["Name"]}"\n')
                primaryMuscleHeader = primaryMuscle(SOUP, muscleGroup)
                secondaryMuscle(SOUP, muscleGroup)
                commentary(SOUP, exerciseName)
                instructions(primaryMuscleHeader, muscleGroup, exerciseName)
                file.write("\n")
            else:
                print(
                    f"{RED}Failed to retrieve {exercise["Name"]} URL {exercise["URL"]}. Status code: {STATUS_CODE}{CLEAR}\n"
                )
                exit()
            counter += 1


# MAIN
with open(FILE_TO_OPEN, "w") as file:
    PAGE_TO_SCRAPE = requests.get(MAIN_URL)
    STATUS_CODE = PAGE_TO_SCRAPE.status_code

    if STATUS_CODE == 200:
        SOUP = BeautifulSoup(PAGE_TO_SCRAPE.text, "html.parser")
        # Setup sections key value pair array
        sections = findSections(SOUP)
        # Map to TOML
        writeToFile(file, sections)
    else:
        print(
            f"{RED}Failed to retrieve main URL {MAIN_URL}. Status code: {STATUS_CODE}{CLEAR}\n"
        )
        exit()
