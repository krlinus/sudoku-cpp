# sudoku-cpp
At the heart of this solution is a group of board navigators.
1. Crosshair: This loops through the cells on the same row and column as the cell in question.
2. CrossBrush: This loops through sets of 3 rows and columns, but omits the square of the originating cell
3. 3x3: This loops through all cells within a square unit of the board.

All the above three take a particular cell as the input, and also a function that will be run on each cell of the region

I plan to solve the sudoku puzzles using the above primitives. At the time of this writing, the solver solves easy level puzzles. This is a work in progress
