WAVES

The task of this project is to make a quick hacksprint project in C++ for the "waves" prompt.

This is a demo game called "Waves of Trash" and it is a deserted island rescue made using ncurses and pulseaudio's paplay program.

The goal of the game is to collect the trash on the beach, and then burn it when a ship is spotted, in hopes of rescue.

INSTALLATION:

These automated tools are intended for debian/Ubuntu systems. The game is intended to run in a console window of 80 columns and 24 rows that is capable of changing colors and has unicode/UTF-8 support.

Build the game:

$ sudo ./build.sh

Run the game:

$ ./waves

Controls:

- Arrow keys move the player
- Spacebar performs the player action on the character the player is facing
- 'x' (lower case) exits the game
