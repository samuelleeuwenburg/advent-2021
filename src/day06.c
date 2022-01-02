#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_SIZE 1
#define FISH_CYCLE 6
#define FISH_SPAWN_CYCLE 8

typedef struct FishVec {
    size_t len;
    size_t max_len;
    int* fish;
} FishVec;

FishVec fish_init() {
    FishVec v = {
        .len = 0,
        .max_len = INIT_SIZE,
        .fish = malloc(sizeof(int) * INIT_SIZE),
    };

    return v;
}

FishVec* fish_add(FishVec* v, int fish) {
    if (v->len >= v->max_len) {
        v->max_len *= 2;
        v->fish = realloc(v->fish, sizeof(int) * v->max_len);

        if (!v->fish) v->max_len = 0;
    }

    v->fish[v->len] = fish;
    ++v->len;

    return v;
}

FishVec* fish_spawn(FishVec* v) {
    return fish_add(v, FISH_SPAWN_CYCLE);
}

FishVec* fish_tick(FishVec* v) {
    size_t new_fish = 0;

    for (size_t i = 0; i < v->len; ++i) {
        if (v->fish[i] == 0) {
            ++new_fish;
            v->fish[i] = FISH_CYCLE;
        } else {
            --(v->fish[i]);
        }
    }

    while (new_fish--) fish_spawn(v);

    return v;
}

size_t read_input(FishVec* fish) {
    FILE* fp = fopen("./input/day06.txt", "r");
    char buffer[1024];

    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        return 1;
    }

    char* token = strtok(buffer, ",");

    while (token != NULL) {
        if (!fish_add(fish, atoi(token))) {
            return 1;
        }

        token = strtok(NULL, ",");
    }

    return 0;
}

int main() {
    FishVec fish = fish_init();
    size_t days = 256;

    read_input(&fish);

    while (days--) {
        printf("day #: %zu\n", days);
        fish_tick(&fish);
    }

    printf("\nnumber of fish: %zu\n", fish.len);

    return 0;
}
