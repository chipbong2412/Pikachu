# Pikachu++

## Project Overview

Pikachu++ is a console-based C++ game implemented in a small, self-contained project. It provides a tile-matching game rendered in the console, with simple assets and highscore persistence.

## Requirements

- A Windows system.
- A working C++ toolchain (for example, MinGW-w64) available from a command prompt.
- Administrator privileges when running the compiled program.

## Build & Run

### Manual compile:

1. Open a Command Prompt or PowerShell.
2. Change directory to the project root where the repository is located. Example:
  `cd C:\path\to\pikachu`

3. Compile the project with this command:

  `g++ src/main.cpp src/Board/*.cpp src/BoardRenderer/*.cpp src/Console/*.cpp src/Game/*.cpp src/Menu/*.cpp -I src -lwinmm -o pikachu.exe`

4. Run the produced executable as administrator: right-click `pikachu.exe` and choose "Run as administrator".

Running with administrator privileges is required for the game to apply certain console window settings (for example setting window width/height, changing the console title, or other console configuration calls).

### Quick:

Run the script `runPikachu.bat`. It contains the commands to compile and run the project as administrator. If the program requires administrator rights, selects Yes and continue.

If you want to inspect or run the compile steps manually, open `runPikachu.bat` in a text editor.

## Project Layout

Top-level files and folders:

- `runPikachu.bat`: Windows batch script used to compile and/or run the project.
- `settings.txt`: Runtime settings used by the game.
- `highscores.csv`: Highscore persistence file.
- `assets/`: Game assets and sound effects.
  - `title.txt`
  - `background/`
    - `easy.txt`
    - `medium.txt`
    - `hard.txt`
  - `sfx/` (includes sound-effect files)

- `src/`: Main source tree.
  - `main.cpp`: Program entry point.
  - `Board/`:
    - `2DLinkedList.h`
    - `ArrayBoard.cpp`
    - `ArrayBoard.h`
    - `Board.cpp`
    - `Board.h`
    - `Coordinate.h`
    - `LinkedBoard.cpp`
    - `LinkedBoard.h`
  - `BoardRenderer/`:
    - `ArrayBoardRenderer.cpp`
    - `ArrayBoardRenderer.h`
    - `BoardRenderer.cpp`
    - `BoardRenderer.h`
    - `LinkedBoardRenderer.cpp`
    - `LinkedBoardRenderer.h`
  - `Console/`:
    - `Colors.cpp`
    - `Colors.h`
    - `Console.cpp`
    - `Console.h`
    - `Constants.h`
    - `Input.cpp`
    - `Input.h`
    - `Renderer.cpp`
    - `Renderer.h`
  - `Game/`:
    - `Game.cpp`
    - `Game.h`
    - `Highscores.cpp`
    - `Highscores.h`
    - `Result.h`
  - `Menu/`:
    - `Button.cpp`
    - `Button.h`
    - `Menu.cpp`
    - `Menu.h`
    - `OptionsList.cpp`
    - `OptionsList.h`

## Notes

- If you don't have a C++ toolchain installed, install MinGW-w64 or and ensure the compiler (`g++`) is on your PATH.
- This is a small educational project for Object-Oriented Programming course at Faculty of Physics and Engineering Physics, VNU-HCMUS.
