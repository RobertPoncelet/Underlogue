# Underlogue

Overview
------
Underlogue uses the ncurses library to produce Undertale-style dialogue boxes in the bash terminal. Features (will) include animated character portraits, storage of dialogue in text files with a movie-script-like syntax, and the ability to let the player choose between two options at any point for different branches of dialogue.

Library Dependencies
-------
> - Ncursesw (displaying elements)
> - Rapidjson (accessing character-specific data stored in JSON)
> - SDL (sound - to be added)
> - Flex & Bison ("movie script" language)

Todo
------
> - Add portrait animation
> - Add the rest of the characters to the JSON file
> - Handle terminal window resizing
> - Better layout of ncurses windows
> - Prevent words being cut off on new lines
> - Allow spaces in expression names
> - Character voice sounds
> - Reimplement entire project in Python in future?
