ICP 2016 Project - Othello
==========================

This Othello (Reversi) game program was created as a school project for the ICP
course at FIT VUT Brno. It contains both a graphical and a command-line version
of the game. Feel free to use and modify the source code, everything is licensed
under a GNU General Public License v2.0.

Created at FIT VUT Brno, 2016

Authors
=======
Pavol Plaskon, xplask00@stud.fit.vutbr.cz
Matej Postolka, xposto02@stud.fit.vutbr.cz

Compilation
===========
To compile the CLI version of the program, run `make cli`. To compile the GUI
version, run `make gui`. Alternatively, you can simply run `make` to compile
both versions.

The CLI version has the following dependencies which must be satisfied if you
want the program to compile successfully:

*libboost-serialization

Try `apt-get install libboost-serialization1.55-dev` on Debian based systems

The GUI version has the following dependencies:

*libboost-serialization
*Qt 5.5.1

See http://qt.io for more information on how to install the Qt development
libraries.

How to play
===========
`make run` to run both CLI and GUI versions.

Command line version:
  Run `./hra2016-cli` and you will see everything you need to know.

Graphical version:
  Run `./hra2016`. The only game controller is the mouse.

Rules: https://en.wikipedia.org/wiki/Reversi

The program offers a choice of two AI algorithms which you can play against.
Alterinatively, you can play against another player.

Have a nice time playing.
