#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 5
#define NUMS GRID_SIZE * GRID_SIZE

typedef struct BingoCard {
    int nums[NUMS];
    int marked[NUMS];
} BingoCard;

BingoCard card_new() {
    BingoCard card = {
        .nums = { 0 },
        .marked = { 0 },
    };

    return card;
}

int card_mark_num(BingoCard* const card, int const num) {
    for (size_t i = 0; i < NUMS; ++i) {
        if (card->nums[i] == num) {
            card->marked[i] = 1;
            return 1;
        }
    }

    return 0;
}

int card_check_bingo(BingoCard* const card) {
    // horizontal
    for (size_t i = 0; i < GRID_SIZE; ++i) {
        int check = 1;

        for (size_t j = 0; j < GRID_SIZE; ++j) {
            check &= card->marked[i * GRID_SIZE + j];
        }

        if (check) return 1;
    }

    // vertical
    for (size_t i = 0; i < GRID_SIZE; ++i) {
        int check = 1;

        for (size_t j = 0; j < GRID_SIZE; ++j) {
            check &= card->marked[i + j * GRID_SIZE];
        }

        if (check) return 1;
    }

    return 0;
}

size_t card_get_final_score(BingoCard* const card, int last_num) {
    size_t score = 0;

    for (size_t i = 0; i < NUMS; ++i) {
        if (!card->marked[i]) {
            score += card->nums[i];
        }
    }

    return score * last_num;
}

size_t read_nums_into(FILE* fp, size_t len, int nums[len]) {
    char buffer[1024] = { 0 };
    size_t pos = 0;

    if (fscanf(fp, "%[^\n]", buffer) != 1) {
        return 0;
    }

    char* token = strtok(buffer, ",");

    while (token != NULL) {
        nums[pos] = atoi(token);
        token = strtok(NULL, ",");
        ++pos;
    }

    return pos;
}


size_t read_bingo_cards(FILE* fp, size_t len, BingoCard cards[len]) {
    char buffer[128] = { 0 };
    size_t num_pos = 0;
    size_t pos = 0;

    cards[pos] = card_new();

    while (fgets(buffer, sizeof buffer, fp) != NULL) {
        // skip empty lines
        if (buffer[0] == '\n') continue;

        if (num_pos == 0) {
            cards[pos] = card_new();
        }

        char* token = strtok(buffer, " ");

        while (token != NULL) {
            cards[pos].nums[num_pos] = atoi(token);
            ++num_pos;
            token = strtok(NULL, " ");
        }

        if (num_pos >= 25) {
            num_pos = 0;
            ++pos;
        }
    }

    return pos;
}

size_t play_bingo() {
    FILE* fp = fopen("./input/day04.txt", "r");
    int nums[1024] = { 0 };
    BingoCard cards[128] = { 0 };
    size_t winners[128] = { 0 };
    size_t last_winner = 0;

    size_t nums_size = read_nums_into(fp, 1024, nums);
    size_t cards_size = read_bingo_cards(fp, 32, cards);


    for (size_t n = 0; n < nums_size; ++n) {
        for (size_t c = 0; c < cards_size; ++c) {
            // skip winners
            if (winners[c] > 0) continue;

            card_mark_num(&cards[c], nums[n]);

            if (card_check_bingo(&cards[c])) {
                winners[c] = card_get_final_score(&cards[c], nums[n]);
                last_winner = c;
            }
        }
    }

    return winners[last_winner];
}

int main() {
    printf("last winning card score: %zu\n", play_bingo());
    return 0;
}
