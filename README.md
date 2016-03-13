# Underlogue

Overview
------
Underlogue uses the ncurses library to produce Undertale-style dialogue boxes in the bash terminal. Features (will) include animated character portraits, storage of dialogue in text files with a movie-script-like syntax, and the ability to let the player choose between two options at any point for different branches of dialogue.
![preview](preview.png)

Library Dependencies
-------
> - Ncursesw (displaying elements)
> - Rapidjson (accessing character-specific data stored in JSON)
> - SDL (sound - to be added)
> - Flex & Bison ("movie script" language)

Todo
------
1. Fix various bugs with the ncurses display
1. Add the rest of the characters to the JSON file
3. Better layout of ncurses windows
2. Handle terminal window resizing
5. Allow spaces in expression names
4. Prevent words being cut off on new lines
6. Character voice sounds
7. Reimplement entire project in Python in future?
