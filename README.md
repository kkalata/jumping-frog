# Jumping frog

Frogger-like game written in C using ncurses library.

The game is being written as a part of basics of computer programming classes at Gdańsk University of Technology, Faculty of Electronics, Telecommunications and Informatics. The requirements are listed below:

1. Obligatory (graphics, logic, code)
    - [x] Basic user interface: status, playable area, jumping frog, moving cars, streets (lanes), destination place, colors (1 pt)
    - [ ] Five or more cars constantly moving and randomly appearing which are wrapping or bouncing, detection of collisions between frog and cars (1 pt)
    - [ ] Timer and timing mechanism, cars running at different speeds, frog jumping with time breaks between jumps (1 pt)
    - [ ] Using separate configuration text file with parameters of the game, e.g. size and shape of the frog and cars playing area, number, types and speed of cars, random seeds, colors, etc. (1 pt)
    - [ ] Implementation requirement: well organized code with own structures (`struct`) and functions (2 pts)
2. Optional (game and more logic)
    - [ ] Some cars are disappearing when reaching the border, new random cars are placed on the street (possible time intervals between) (1 pt)
    - [ ] There are a few static obstacles (e.g., between street lanes) and the speed of some cars is changing during the game (1 pt)
    - [ ] Some cars stop the movement when the frog is close to them (1 pt)
    - [ ] Some cars are friendly cars and catch the frog and move to the another place (1 pt)
    - [ ] Game ranking (think over the concept of points) (1 pt)
    - [ ] Stork flying towards the frog (vertical, horizontal and diagonal movement) trying to catch the frog (2 pts)
    - [ ] Build the concept of levels with non-trivial logic (at least three levels) and apply it to the game (2 pts)
3. Extra points
    - [ ] Recording and playing the whole game to and from file (FILE) (2 pts)
    - [ ] Using GitHub account for storing, versioning and presenting all the history, trying to apply the agile methodology to realize the project individually (1 pt)

Failing to satisfy any requirement results in terminating the assessment, thus getting only the points scored prior the termination.
