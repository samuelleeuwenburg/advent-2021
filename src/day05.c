#include <stdio.h>

#define max(x,y) (((x) >= (y)) ? (x) : (y))
#define min(x,y) (((x) <= (y)) ? (x) : (y))

#define GRID_SIZE 1000
#define POSITIONS GRID_SIZE * GRID_SIZE

typedef enum {
    All,
    IgnoreDiagonal,
} Mode;

size_t x_y_to_pos(size_t grid_size, int x, int y) {
    return y * grid_size + x;
}

void populate_grid(size_t const len, size_t grid[len], Mode mode, FILE* fp) {
    int x1, y1, x2, y2;

    while (fscanf(fp, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) == 4) {
        if (y1 == y2) {
            // horizontal
            for (size_t x = min(x1, x2); x < max(x1, x2) + 1; ++x) {
                grid[x_y_to_pos(GRID_SIZE, x, y1)] += 1;
            }
        }
        else if (x1 == x2) {
            // vertical
            for (size_t y = min(y1, y2); y < max(y1, y2) + 1; ++y) {
                grid[x_y_to_pos(GRID_SIZE, x1, y)] += 1;
            }
        } else if (mode != IgnoreDiagonal) {
            // diagonal
            size_t y = x1 > x2 ? y2 : y1;
            for (size_t x = min(x1, x2); x < max(x1, x2) + 1; ++x) {
                grid[x_y_to_pos(GRID_SIZE, x, y)] += 1;

                if ((x1 > x2 && y2 > y1) || (x1 < x2 && y1 > y2)) {
                    --y;
                } else if ((x1 > x2 && y1 > y2) || (x1 < x2 && y2 > y1)) {
                    ++y;
                }
            }
        }
    }
}

size_t count_overlaps(size_t const len, size_t grid[len]) {
    size_t count = 0;

    for (size_t i = 0; i < len; ++i) {
        if (grid[i] > 1)
            ++count;
    }

    return count;
}

int main() {
    FILE* fp = fopen("./input/day05.txt", "r");
    size_t grid[POSITIONS] = { 0 };

    populate_grid(POSITIONS, grid, All, fp);
    printf("overlaps: %zu \n", count_overlaps(POSITIONS, grid));

    return 0;
}
