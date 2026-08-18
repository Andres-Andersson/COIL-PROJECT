## ARKANOID IN C COIL-PROJECT GROUP 1 2026

# Project name: ARKANOID IN C EDITION: A BLOCKY ADVENTURE

Students: Andres Andersson Madrigal (68007) and Agustín Quiñones (67921).
Professors: Nicolas Magliola and Marcus Purat.

# Game description

In this ARKANOID version, the objective is to hit the ball upward with a paddle smashing layers of colorful bricks to get the most points. Certain bricks spawn power capsules, which grant special powers when caught. As levels progress, the ball speeds up, making it harder to keep the ball in bounds. Will you embark on this adventure to save the galaxy from this blocky menace?

# GAME REQUIREMENTS
This game is intended to run ONLY in Linux. To play this game the requirements are:

1 Using the gcc C compiler.
2 Using makefile
3 Installing the external libraries (NCURSES)

# To install NCURSES open the Linux terminal and copy and paste these commands:

sudo apt update
sudo apt install build-essential libncurses5-dev libncursesw5-dev

# Game controls:

  To move the paddle A (LEFT), D (RIGHT)
  To pause/resume/play (SPACE BAR)
  To quit (Q)
  View leaderboard (L)

7. Características Implementadas (Features & Modos de Juego)

8. Decisiones de Diseño y Manejo de Recursos (Importante para la Defensa)

Un apartado breve donde expliquen decisiones técnicas clave:

    Manejo de memoria: "Toda la memoria dinámica asignada para los niveles/entidades se libera al finalizar la partida o cerrar el juego mediante la función end_program()."

    Mapeo de archivos/Persistencia: Cómo guardan las puntuaciones (ej. scores.dat).

    Frame rate / Control de tiempo: Uso de usleep() ajustado a 40 FPS para controlar la velocidad del juego de manera homogénea.
