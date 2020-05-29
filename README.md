# ai-search

Implementation of 5 different AI search algorithms:

- Depth First Search (`depth_first_search`)
- Breadth First Search (`breadth_first_search`)
- Best First Search (`best_first_search`)
- A* (`a_star`)
- Hill Climbing (`hill_climbing`)

## Mazes

## Scripts

### `make` <sub>or `make build`</sub>

Compile all search algorithms. Each algorithm is a different program.

The binaries are saved in the `.bin` directory.

### `make clean`

Remove the `.bin` directory and its contents.

### `make exec a=[algorithm]`

#### `[algorithm]` is one of:

- `depth_first_search` or `dfs`;
- `breadth_first_search` or `bfs`;
- `best_first_search` or `bsfs`;
- `a_star` or `as`;
- `hill_climbing` or `hc`.

E.g. to execute the A* search binary with the maze with index 0:

```
make exec a=a_star m=0
```

### TODO: `make average a=a_star m=0 n=100`
