# Report

## Which algorithm did what
**`bfs`/`dijkstra`** are single-pair searches, each stopping the instant the target is
settled; every ordered pair among the K+2 key points is computed independently (not
mirrored) so the symmetry check is a real test. **`astar`** is `dijkstra` plus a
heuristic. **`dfsPath`** is a plain stack-based DFS that stops at the *first* time it reaches
`t`.It is deliberately NOT the shortest path. **`bestOrder`**
backtracks over coin-visit orderings using the precomputed matrix only, pruning any partial
sum that already reaches the current best; called once on the `bfs` matrix (uniform block),
once on `dijkstra`'s (weighted block). Since all weights are ≥ 0, pruning only drops
provably-worse branches.

## DFS really doesn't guarantee shortest paths
"First path found" instead of "best path found" means `dfsPath` is often longer than `bfs`!

| Maze | Pairs where DFS > BFS |
|---|---|
| tiny_2coins | 6/12 (50%) |
| medium_5coins | 33/42 (79%) |
| weighted_4coins | 8/12 (67%) |
| stress_8coins | 89/110 (81%) |

This is exactly why `bestOrder` is fed the `bfs` matrix, never a `dfsPath` one.

## A* vs Dijkstra: cells expanded
Same per-pair, early-stopping architecture on both sides makes "A* ≤ Dijkstra" a guarantee:
A* only settles nodes with `g+h ≤ optimal`; since `h ≥ 0`, that's always a subset of what
Dijkstra (`h=0`) settles.

| Maze | Dijkstra | A* | Saved |
|---|---|---|---|
| tiny_2coins | 318 | 145 | 54% |
| medium_5coins | 2,175 | 865 | 60% |
| weighted_4coins | 350 | 160 | 54% |
| stress_8coins | 9,009 | 2,938 | 67% |

## weighted_4coins.txt: why weighted beats step-count on cost
Cheap corridor (digit 1) vs. expensive column (digit 9). Traced leg-by-leg: BFS's
shortest-*step* route between the two coins costs **36** in real terrain terms; the true
cheapest route for that leg (back through S, avoiding the 9 column) costs only **12**! 3x
cheaper for the same step count! Total optimal cost is 24 vs. 22 uniform steps, not because
weighted is "worse," just that the only remaining efficient route still crosses a couple of
cost>1 cells, and Dijkstra correctly won't trade that for a cheaper-looking path BFS can't see.

## Best coin order — medium_5coins.txt
Cost 32, identical for both runs (no terrain digits in this maze, so weighted collapses to
uniform, same as `tiny_2coins`).
