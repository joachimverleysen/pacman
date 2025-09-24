# Doodle Jump

## What I learned building this project
- Design patterns (e.g. MVC model and factory pattern)
- smart pointers

## Technical discussion

### General
- The "Game" class is responsible for handling input, running and rendering.
- The "World" is responsible for managing entities and generating platforms.

### Design patterns
- Model-View-Controller structure
- Abstract/Concrete factory
- Composition over inheritance (PlatformBehavior class)
- Subject + Observer (Entity + View)
- Singleton (Stopwatch)
- Object oriented + Polymorphism

### Coordinate system
- The origin is the top-left corner
- x-values grow to the right, y-values grow upwards
- Coordinates are converted to SFML coordinates

### Texture Management
- A texture is defined by a file name and a specific area on the texture.
- When a new texture is requested, it is loaded once and can later be re-used.
- New textures can dynamically be added in the json configuration.

### Platform generation
- Random positions
- Use parameters _max_y, margin..._
- no colliding platforms (collision checking)


### Other
- CollisionHandler class: works with bounding boxes
- Physics class for applying gravity or updating speed
- Delta time in StopWatch: to regulate framerate
- Constants in seperate file, separated with namespaces

### To do:
- Score
- Bonuses


# How to run

`
cmake -B build
`

`
cmake --build build
`

`
./build/bin/main
`
# pacman
