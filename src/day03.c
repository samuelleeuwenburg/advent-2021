#include <stdio.h>
#include <stdlib.h>

// assume 12 bit input
#define BIT_SIZE 12

static size_t convert_to_binary(size_t const len, signed const arr[len]) {
    size_t result = 0;

    for (size_t i = 0; i < len; ++i) {
        result <<= 1;

        if (arr[i] > 0) {
            result += 1;
        }
    }

    return result;
}

size_t part_one() {
    FILE* fp = fopen("./input/day03.txt", "r");
    char buffer[BIT_SIZE + 1];
    signed bit_count[BIT_SIZE] = { 0 };

    while (fscanf(fp, "%s", buffer) == 1) {
        int num = (int) strtol(buffer, NULL, 2);

        for (size_t i = 0; i < BIT_SIZE; ++i) {
            if (num & 1 << (BIT_SIZE - i - 1)) {
                bit_count[i] += 1;
            } else {
                bit_count[i] -= 1;
            }
        }
    }

    size_t result = convert_to_binary(BIT_SIZE, bit_count);
    size_t inverted_result = ~result & 0xFFF;

    return result * inverted_result;
}

typedef enum {
    Most,
    Least,
} Mode;

int find_value(
    size_t const len,
    int const arr[len],
    size_t const bit_pos,
    Mode const mode
) {
    if (len == 1) {
        return arr[0];
    }

    int zeroes[1024] = { 0 };
    int ones[1024] = { 0 };
    size_t zeroes_size = 0;
    size_t ones_size = 0;

    for (size_t i = 0; i < len; ++i) {
        if (arr[i] & (1 << bit_pos)) {
            ones[ones_size] = arr[i];
            ++ones_size;
        } else {
            zeroes[zeroes_size] = arr[i];
            ++zeroes_size;
        }
    }

    if (ones_size >= zeroes_size) {
        if (mode == Most) {
            return find_value(ones_size, ones, bit_pos - 1, mode);
        } else {
            return find_value(zeroes_size, zeroes, bit_pos - 1, mode);
        }
    } else {
        if (mode == Most) {
            return find_value(zeroes_size, zeroes, bit_pos - 1, mode);
        } else {
            return find_value(ones_size, ones, bit_pos - 1, mode);
        }
    }
}

size_t part_two() {
    FILE* fp = fopen("./input/day03.txt", "r");
    char buffer[BIT_SIZE + 1];
    int nums[1000];
    size_t i = 0;

    while (fscanf(fp, "%s", buffer) == 1) {
        nums[i] = (int) strtol(buffer, NULL, 2);
        ++i;
    }

    int most = find_value(1000, nums, BIT_SIZE - 1, Most);
    int least = find_value(1000, nums, BIT_SIZE - 1, Least);

    return most * least;
}

int main() {
    printf("part_one: %lu\n", part_one());
    printf("part_two: %lu\n", part_two());
    return 0;
}
