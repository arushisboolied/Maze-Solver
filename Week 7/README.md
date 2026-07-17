# Maze Solver — README

**Compile:** `g++ -O2 maze_solver.cpp -o maze_solver`
**Run:** `./maze_solver test_mazes/input_maze.txt` (for example `./maze_solver test_mazes/tiny_2coins.txt`)

## Expected output on `test_mazes/tiny_2coins.txt`

```
=== UNIFORM COST (BFS + DFS) ===
Coins: 2
Best order: S -> c(3,0) -> c(0,7) -> G
Total steps: 17
Path:
S******c
*......*
*...#..*
c......*
.......G

=== WEIGHTED (Dijkstra + A*) ===
Coins: 2
Best order: S -> c(3,0) -> c(0,7) -> G
Total cost: 17
A* cells expanded across all pair queries: 145
Dijkstra cells expanded across all pair queries: 318

SUMMARY | BFS pairs computed: 12 | DFS orderings tried: 4 | Dijkstra:318 | A*:145
```
