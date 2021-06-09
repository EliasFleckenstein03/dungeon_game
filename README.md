# Dungeon Game
A small but flexible dungeon crawler written in C. Needs GCC to compile (`__USE_GNU`). Renders directly into the terminal using unicode and escape sequences. Enlarge font size to see what's happening ingame better. The game supports changing the font size or window size of the terminal emulator while running.

You can easily create plugins for the game by putting a new folder into plugins/ with the name of your plugin and then compiling your code into a shared library placed inside this folder named "<plugin name>.so" (`-shared -fpic`).
You might want to include the game.h file from plugins/game/game.h. Have a look into it to see available API. See the existing plugins for examples.

Controls: WASD to move, Q to quit.

To build the loader and the plugins in the plugins/ folder, simply type `make` or `make all`. There are separate targets for the loader (`dungeon`) and the plugins. All Makefiles that are placed in plugin directories, so you might want to include a makefile in your plugin. The plugins target simply depends on ${PLUGINS}, so just add things to this in your plugin Makefile to add them to the plugins target (usually your plugin.so)
To run the loader, type `./dungeon`. It will load all plugins including the game itself dynamically and run the game.

If you want to make a plugin that depends on another plugin (including the game itself), make sure to depend on that plugin. To add dependencies to a plugin, create a file named dependencies.txt in the plugin folder. Put the names of all plugins your plugin depends on into that file. You can use spaces or newlines as seperators.
