**Develop a program in C – a visualization of The Game of Life. To display the graphics, only use ASCII characters (with output to the terminal). You need to implement interactive version (using the "ncurses" library) of the Game of life. Also create the option for adjusting the speed of the "game".**

* ***Graphics***

Treat the playing field - a rectangle of 80 by 25 cells – as a matrix of the state of the "game". 
It is assumed that the field is "closed to itself", for example, in the lower right square, the neighbor on the right is the lower left square, and the neighbor on the bottom is the upper right.

Provide for original initialization of the "game" state via stdin. 
Prepare files with initial states for quick launch and initialization through input redirection. 

* ***Control***

"A/Z" - Control of the left racket

"K/M" - Control of the right racket
