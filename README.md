WAVES

The task of this project is to make a quick hacksprint project in C++ for the "waves" prompt.

This is a demo game called "Waves of Trash" and it is a deserted island rescue made using ncurses.

The goal of the game is to collect the trash on the beach by putting it into the bin, and then burn it using the magnifying glass when a ship is spotted, in hopes of rescue.

INSTALLATION INFO:

These automated tools are intended for debian/Ubuntu systems. The game is intended to run in a console window of 80 columns and 24 rows that is capable of changing colors and has unicode/UTF-8 support.

Build the game:

$ sudo ./build.sh

Run the game:

$ ./waves

Controls:

- Arrow keys move the player and change the direction they are facing
- Spacebar performs the player action on the character the player is facing
- 'x' (lower case) exits the game

NOTES:

I wanted to make a console application that uses ncurses/ncursesw with emojis. I was mostly concerned with finishing on time, and there are a few things that could be less repetitive in the code. I'll add more things and clean it up eventually. The map.cpp file makes me sad. I tested this using xfce-terminal on Ubuntu 20.04 (Xubuntu). I don't see why it won't work on higher versions and most Linux distributions as well. I'm sure there are some cool things that can be done in the build.sh file to make the installations more portable. Feel free to send me feedback or a pull request.
