class Maze:
    def __init__(self, filename):
        self.grid = []
        with open(filename, 'r') as f:
            for line in f:
                line = line.replace(" ", "")
                # verwijder newline en maak een lijst van karakters
                self.grid.append(list(line.rstrip('\n')))

    def at(self, row, column):
        return self.grid[row][column]

    def __len__(self):
        return len(self.grid)

    def __getitem__(self, key):
        return self.grid[key]


def replace_straight_paths(maze):
    rows = len(maze)
    cols = len(maze[0])
    new_maze = [row[:] for row in maze]  # kopie

    for r in range(rows):
        for c in range(cols):
            if maze[r][c] != '+':
                continue

            if maze[r][c] not in ['+', 'W', '.']:
                print(f"{r} {c} unexpected char {maze[r][c]}")
            # buren ophalen, buiten maze = 'W'
            top = maze[r-1][c] if r > 0 else ' '
            bottom = maze[r+1][c] if r < rows-1 else ' '
            left = maze[r][c-1] if c > 0 else ' '
            right = maze[r][c+1] if c < cols-1 else ' '

            # verticale rechte pad
            if (top == 'w' or top == ' ') and (bottom == 'w' or bottom == ' '):
                new_maze[r][c] = '.'
            # horizontale rechte pad
            elif (left == 'w' or left == ' ') and (right == 'w' or right == ' '):
                new_maze[r][c] = '.'

            count_blocked = sum(b in ['w', ' ']
                                for b in [top, bottom, left, right])
            if count_blocked > 2 and new_maze[r][c] == '.':
                new_maze[r][c] = '+'

    return new_maze


def write_maze_to_file(maze, filename):
    with open(filename, 'w') as f:
        for row in maze:
            # voeg spaties tussen karakters
            line = " ".join(row)
            f.write(line + "\n")


# Voorbeeld van gebruik
if __name__ == "__main__":
    maze = Maze("maze2.txt")  # vervang door jouw bestandsnaam
    new_maze = replace_straight_paths(maze)
    write_maze_to_file(new_maze, "out.txt")
