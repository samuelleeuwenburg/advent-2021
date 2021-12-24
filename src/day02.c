#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t part_one() {
    FILE* fp = fopen("./input/day02.txt", "r");
    char command[128];
    int amount;

    size_t depth = 0;
    size_t horizontal = 0;

    while (fscanf(fp, "%s %d", command, &amount) == 2) {
        if (strcmp("up", command) == 0) {
            depth -= amount;
        } else if (strcmp("down", command) == 0) {
            depth += amount;
        } else if (strcmp("forward", command) == 0) {
            horizontal += amount;
        }
    }

    return depth * horizontal;
}

size_t part_two() {
    FILE* fp = fopen("./input/day02.txt", "r");
    char command[128];
    int amount;

    size_t depth = 0;
    size_t horizontal = 0;
    size_t aim = 0;

    while (fscanf(fp, "%s %d", command, &amount) == 2) {
        if (strcmp("up", command) == 0) {
            aim -= amount;
        } else if (strcmp("down", command) == 0) {
            aim += amount;
        } else if (strcmp("forward", command) == 0) {
            horizontal += amount;
            depth += amount * aim;
        }
    }

    return depth * horizontal;
}

int main() {
    printf("part_one: %lu\n", part_one());
    printf("part_two: %lu\n", part_two());

    return 0;
}
