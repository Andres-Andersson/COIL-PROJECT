## ARKANOID IN C COIL-PROJECT (ITBA - BHT) GROUP 1 2026

# Project name: ARKANOID IN C EDITION: A BLOCKY ADVENTURE

Students: Andres Andersson Madrigal (68007) and Agustín Quiñones (67921).
Professors: Nicolas Magliola and Marcus Purat.

# Game description

In this ARKANOID version, the objective is to hit the ball upward with a paddle smashing layers of colorful bricks to get the most points. Certain bricks spawn power capsules, which grant special powers when caught. As levels progress, the ball speeds up, making it harder to keep the ball in bounds. Will you embark on this adventure to save the galaxy from this blocky menace?

# GAME REQUIREMENTS
This game is intended to run ONLY in Linux. To play this game the requirements are:

1. Using the gcc C compiler.
2. Using the provided makefile
3. Installing the external libraries (NCURSES)

# To install NCURSES open the Linux terminal and copy and paste these commands:

sudo apt update

sudo apt install build-essential libncurses5-dev libncursesw5-dev

#Instructions to create the executable file once NCURSES is installed:

1. Open the terminal inside the folder were 'main.c' and the makefile are located
2. Execute the 'make' command to build the executable.
4. Run the executable with the command ./ARKANOID-COIL

# Game controls:

To move the paddle A (LEFT), D (RIGHT)

To pause/resume/play (SPACE BAR)

  To quit (Q)
  
  View leaderboard (L)
  

# Aditional game implementations

- Menu: Be able to pause, resume or restart game. After loosing it is possible to start playing again without exiting the program.
- Top Score: Sorted list of best scores (TOP 10) saved even after closing the game (using files).
- Advanced Score: Advance score calculation dependent on ball speed.
- Advanced Bricks: Bricks with more than 1 life (destroyed after being hit several times). Different symbol for each type of bricks.
- Advanced and Random Pattern: Fixed multiple-row bricks pattern for the first four levels, on the fifth, the brick pattern is randomized.
- Advanced Angle: Ball bounces with a different angle depending where it hits the paddle, like the original game. Narrow angle in the center, wider angle in the edges.
- Capsules: Some bricks release capsules that bestow various power-ups when caught. We have created four different power: increase on the length of the paddle, temporary slowing ball slow-down, extra ball spawn and multiple ball spawn.
- Animations: Motion graphics in the game menu, stars fall randomly and a rocket propels itself indefinitely.

# Game design decisions and resource management

Modular architecture: the game manager, data manager and the NCURSES rendering modules work independently each one of them worrying about their own responsibilities.

Memory management: all the dynamic memory is freed before exiting the game (avoiding memory leeks).

File system: all the scores are saved in scores.txt. Where a user beat its previous record, a temp file is created copying all the previous data and replacing the new record with the previous. scores.txt is destroyed and the temp file becomes the new scores.txt.

Frame rate control: usleep() usage adjusted to the specific FPS to control the game speed without jeopardizing the game-look.
