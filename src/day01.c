#include <stdio.h>
#include <stdlib.h>

size_t part_one() {
    FILE* file_pointer = fopen("./input/day01.txt", "r");
    int num;
    size_t prev_num = 0;
    size_t total_decrease = 0;

    while (fscanf(file_pointer, "%d", &num) == 1) {
        if (prev_num != 0 && num > prev_num) {
            ++total_decrease;
        }

        prev_num = num;
    }

    return total_decrease;
}

size_t part_two() {
    FILE* file_pointer = fopen("./input/day01.txt", "r");
    int num;
    size_t nums[8192];
    size_t pos = 0;
    size_t prev_total = 0;
    size_t total_decrease = 0;

    while (fscanf(file_pointer, "%d", &num) == 1) {
        nums[pos] = num;
        ++pos;
    }

    for (size_t i = 0; i < pos - 1; ++i) {
        size_t total = nums[i] + nums[i + 1] + nums[i + 2];

        if (prev_total != 0 && total > prev_total) {
            ++total_decrease;
        }

        prev_total = total;
    }

    return total_decrease;
}

int main() {
    printf("part one: %lu \n", part_one());
    printf("part two: %lu \n", part_two());

    return 0;
}
