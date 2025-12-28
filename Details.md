# Implementation details 

## World
The World consists of entities and a maze. 
The maze is read from an input file and implemented with a node map.
Entities that can move around the maze are called Characters (Pacman + ghosts).

## The node map
The node map is used to implement Character's movement
around the maze.
Characters move from node to node. Nodes are placed at intersections and corners.
They are indicated in the input file.

## Input file syntax
- '+' Node
- '.' Path
- 'W' Wall
- 'S' start
- 'c' coin
- 'f' fruit
- 'C' coin/node
- 'F' fruit/node
- 'G' ghost home node
- <number> portal (same numbers are connected portals)

