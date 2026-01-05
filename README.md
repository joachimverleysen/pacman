# pacman

name: Joachim Verleysen

student nr: s0231444

## Recent changes

- Ghosts now immediately respawn after they're eaten
- Fix: double 'death' sound at GameOverScreen

>[!NOTE]
>In the video, ghosts don't respawn immediately yet. It is now implemented.

## Evaluation

### Core Game requirements (40 points)

- [x] Startup screen + scoreboard
- [x] Maze & collision correctness
- [x] Smooth continuous movement
- [x] Ghost AI (4 modes)
- [x] Coin/fruit score modifiers
- [x] Fear mode + ghost reversal
- [x] Level clearing + scaling difficulty
- [x] Life system & game over

### Soft. Design & Code Arch. (40 points)

- [x] Clear MVC separation
- [x] Patterns: MVC, Observer, Abstract Factory, Singleton, State
- [x] Logic as standalone library
- [x] Camera & normalized coords
- [x] Good polymorphism & extensibility

### Project defense video (10 points)

>[!NOTE]
>In the video, ghosts don't respawn immediately yet. It is now implemented.

### Documentation (10 points)

To access Doxygen documentation:

#### Generate manually

- Inside root folder, run "doxygen Doxyfile"
- Open /docs/html/index.html

#### Download zip file

Alternatively, download the docs.zip under Releases > First release > Assets

### Bonus features

- [x] sound/music
- [x] generic programming
- [x] Extra design patterns: Visitor & Double Dispatch
