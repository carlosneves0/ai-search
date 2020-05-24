# ai-search

Implementation of 5 different AI search algorithms:

- Depth First Search (`depth_first_search`)
- Breadth First Search (`breadth_first_search`)
- Best First Search (`best_first_search`)
- A* (`a_star`)
- Hill Climbing (`hill_climbing`)

## Actions

### `make`

Or `make build` to compile all search algorithms. Each algorithm is a different program.

The binaries are saved in the `.bin` directory.

### `make clean`

Remove the `.bin` directory and its contents.

### `make exec a=[algorithm] n=[n]`

#### `[algorithm]` is one of:

- `depth_first_search` or `dfs`;
- `breadth_first_search` or `bfs`;
- `best_first_search` or `bsfs`;
- `a_star` or `as`;
- `hill_climbing` or `hc`.

#### `[n]` is how many times you want to execute the program (default is 1).

E.g.: to execute the A* search binary: `make start algorithm=a_star` or `make start algorithm=as`.

<!-- ## `make test algorithm=[algorithm]`

#### `[algorithm]` is one of: `depth_first_search` or `dfs`; `breadth_first_search` or `bfs`; `best_first_search` or `bsfs`; `a_star` or `as`; `hill_climbing` or `hc`. -->
