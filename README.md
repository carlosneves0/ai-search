# ai-search

Implementation of 5 different AI search algorithms:

- Depth First Search (`depth_first_search`)
- Breadth First Search (`breadth_first_search`)
- Best First Search (`best_first_search`)
- A* (`a_star`)
- Hill Climbing (`hill_climbing`)

## Scripts

### `make` <sub>or `make build`</sub>

Or  to compile all search algorithms. Each algorithm is a different program.

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

E.g. to execute the A* search binary:

```
make exec a=a_star
```

#### TODO: `make exec a=a_star n=100 i=maze/0.txt`
