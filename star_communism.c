// NAME: Star Communism (MP3)
// GAMES: MP3_USA
// EXECUTION: Direct
// AUTHOR: Kyon2570

#include "ultra64.h"

struct player {
    s8 unk0;
    s8 cpu_difficulty;
    s8 controller;
    u8 character;
    /**
     * Miscellaneous flags.
     * 1: Is CPU player
     */
    u8 flags;
    s8 pad0[5];
    /**
     * Current coin count.
     */
    s16 coins; // 10
    /**
     * Coins obtained during a Mini-Game.
     */
    s16 minigame_coins; // 12
    s8 stars; // 14

    u8 cur_chain_index; // 15
    u8 cur_space_index; // 16
    u8 next_chain_index; // 17
    u8 next_space_index; // 18
    u8 unk1_chain_index; // 19
    u8 unk1_space_index; // 20
    u8 reverse_chain_index; // 21
    u8 reverse_space_index; // 22

    u8 flags2; // 23
    u8 items[3]; // 24
    u8 bowser_suit_flag; // 27
    u8 turn_color_status; // 28

    s8 pad1[7]; // 29 - 35

    void *obj; // 36 // struct object *
    s16 minigame_star; // 40
    s16 coin_star; // 42
    s8 happening_space_count; // 44
    s8 red_space_count;
    s8 blue_space_count;
    s8 chance_space_count;
    s8 bowser_space_count; // 48
    s8 battle_space_count;
    s8 item_space_count;
    s8 bank_space_count;
    s8 game_guy_space_count; // 52

    // s8 pad2[3];
};

extern u8 D_800D1116; // Player 1 Star Count
extern u8 D_800D114E; // Player 2 Star Count
extern u8 D_800D1186; // Player 3 Star Count
extern u8 D_800D11BE; // Player 4 Star Count

void cleanupMessage() {
    func_800EC9DC();
    CloseMessage();
    func_800EC6EC();
}

void ReplacePlayerStars(int index, int new_star_count) {
    struct player *player = GetPlayerStruct(index);
    player->stars = new_star_count;
}

char *star_comm_msg = 
    "I hope you liked your stars\x82"
    "\x0A"
    "because it\x5Cs time for star communism\xC2"
    "\xFF";

char *stars_leftover_msg =
    "Wait\x82 the stars distributed aren\x5Ct equal\xC3"
    "\x0A"
    "Ah well\x82 hope RNG saves you today\xC2"
    "\xFF";

void main() {
    int random_player;
    int player1_new_stars;
    int player2_new_stars;
    int player3_new_stars;
    int player4_new_stars;
    short player1_flag;
    short player2_flag;
    short player3_flag;
    short player4_flag;

    ShowMessage(-1, star_comm_msg, 0, 0, 0, 0, 0);
    cleanupMessage();

    int total_stars = D_800D1116 + D_800D114E + D_800D1186 + D_800D11BE;
    int stars_to_distribute = total_stars / 4;
    int stars_leftover = total_stars % 4;
    if (stars_leftover == 0) {
        ReplacePlayerStars(0, stars_to_distribute);
        ReplacePlayerStars(1, stars_to_distribute);
        ReplacePlayerStars(2, stars_to_distribute);
        ReplacePlayerStars(3, stars_to_distribute);
    }
    else {
        player1_new_stars = stars_to_distribute;
        player2_new_stars = stars_to_distribute;
        player3_new_stars = stars_to_distribute;
        player4_new_stars = stars_to_distribute;

        player1_flag = 0;
        player2_flag = 0;
        player3_flag = 0;
        player4_flag = 0;

        ShowMessage(-1, stars_leftover_msg, 0, 0, 0, 0, 0);
        cleanupMessage();
    
        while (stars_leftover > 0) {
            random_player = GetRandomByte() % 4;
            switch (random_player) {
                case 0:
                    if (player1_flag == 0) {
                        player1_new_stars++;
                        player1_flag = 1;
                        stars_leftover--;
                    }
                    break;
                case 1:
                    if (player2_flag == 0) {
                        player2_new_stars++;
                        player2_flag = 1;
                        stars_leftover--;
                    }
                    break;
                case 2:
                    if (player3_flag == 0) {
                        player3_new_stars++;
                        player3_flag = 1;
                        stars_leftover--;
                    }
                    break;
                case 3:
                    if (player4_flag == 0) {
                        player4_new_stars++;
                        player4_flag = 1;
                        stars_leftover--;
                    }
                    break;
            }
        }
        ReplacePlayerStars(0, player1_new_stars);
        ReplacePlayerStars(1, player2_new_stars);
        ReplacePlayerStars(2, player3_new_stars);
        ReplacePlayerStars(3, player4_new_stars);
    }
}