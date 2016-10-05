# Underlogue

Overview
------
Underlogue uses the ncurses library to produce Undertale-style dialogue boxes in the bash terminal. Features (will) include animated character portraits, creation of dialogue scenes in a bespoke language with a movie script-like syntax, and the ability to let the player choose between two options at any point for different branches of dialogue.

![preview](preview.png)

Usage
------

Like most command line tools, simply pass a file path (i.e. dialogue "script") as an argument to the program to use it, e.g. `./Underlogue exampleScript.txt`. As in Undertale, the Z key will continue to the next line of dialogue when the character has finished speaking, while X will skip through it. When options are displayed, the arrow keys are used to select different choices and Z to confirm the selected one.

Here's an example of a "script" located in the `parser` directory:
~~~~
Alphys ("anxious 6"): "H-hey! I'm uh... not interrupting, am I?" (Yes/No)
Yes:
(
    Alphys ("anxious 3"): "Oh...! Sorry!"
    Alphys ("anxious 5"): "I guess I'll get out of your hair then..."
)
No:
(
    Alphys ("surprised"): "Oh! Well... good!"
    Alphys: "Anyway, I was just here to remind you to take a break."
    Alphys: "You know, get up and stretch a bit."
    Alphys ("anxious 3"): "I mean, you wouldn't want to end up with posture like mine, r-right?"
    Alphys ("anxious 1"): "H-hahahaha...!!"
    Alphys ("anxious 7"): "Yeah... I'm gonna go now."
)
~~~~
Data concerning characters and their Unicode art "sprites" and corresponding names/sounds is stored in art/art.json. Currently, only Alphys and Undyne are available.

Library Dependencies
-------
* Ncursesw (displaying elements)
* Rapidjson (accessing character-specific data stored in JSON)
* SDL (sound - to be added)
* Flex & Bison ("movie script" language)

Todo (in order of importance)
------
1. Fix various bugs with the ncurses display
1. Add the rest of the characters to the JSON file
3. Better layout of ncurses windows
2. Handle terminal window resizing
5. Allow spaces in expression names
4. Prevent words being cut off on new lines
6. Character voice sounds
7. Reimplement entire project in Python in future?

Undertale &copy; Toby Fox
