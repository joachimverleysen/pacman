# Implementation details 

## World
The World consists of entities and a maze. 
The maze is read from an input file and implemented with a node map.
Entities that can move around the maze are called Characters (Pacman + ghosts).

## The node map
The node map is an alternative way to collision detection to implement Character's movement
around the maze.
Characters move from node to node. Nodes are placed at intersections and corners.
They are indicated in the input file.

## Input file syntax
- '+' Node
- '.' Path
- 'X' Wall

