# Tic-Tac-Toe Game in C

## Project Overview

A two-player Tic-Tac-Toe game developed in C and played through the terminal. The game uses a 3×3 board and allows players to enter their names, select who plays first, and take turns placing `X` and `O` symbols.

The program detects winning combinations and draws, validates player moves, and provides an option to replay the game.

## Features

- Two-player gameplay
- Player name input
- Selection of the starting player
- 3×3 game board using a two-dimensional array
- Row and column-based player input
- Input validation for board coordinates
- Prevention of moves on occupied cells
- Win detection for rows, columns, and diagonals
- Draw detection
- Replay option to start a new match
- Colored terminal output using ANSI escape sequences

## Technologies Used

- C Programming
- Two-Dimensional Arrays
- Functions
- Loops and Conditional Statements
- String Handling
- Input Validation
- ANSI Escape Codes

## Project Structure

```text
Tic-Tac-Toe/
├── code.c
└── h.c
```

## Compilation

Compile the playable game using GCC:

```bash
gcc code.c -o tic_tac_toe
```

## Execution

Run the game:

```bash
./tic_tac_toe
```

## Gameplay

1. Enter the names of both players.
2. Select which player goes first.
3. Enter the row and column coordinates to place your symbol.
4. Players alternate turns until a player wins or the board is full.
5. Choose whether to play another match.

Board coordinates range from `0` to `2` for both rows and columns.

## Game Logic

The game board is represented using a 3×3 character array. Empty cells are initialized with null characters (`'\0'`).

The program uses separate functions for:

- `reset()` – resets the board for a new game.
- `check_draw()` – checks whether all board positions are occupied.
- `check_res()` – checks all rows, columns, and diagonals for a winning combination.
- `display_board()` – displays the game board in the terminal.

## Testing

The program was successfully compiled and tested using GCC.

A test match verified that the game correctly identifies a winning combination when a player completes the top row.

## Learning Outcomes

- Practiced implementing game logic using C.
- Applied two-dimensional arrays to represent a game board.
- Improved understanding of functions and modular programming.
- Implemented input validation and conditional logic.
- Practiced string handling and player management.
- Used terminal formatting to improve user experience.

---

**Author:** Vivek  
**Language:** C
