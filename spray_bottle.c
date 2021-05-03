// NAME: Spray Bottle Event (MP3)
// GAMES: MP3_USA
// EXECUTION: Direct
// AUTHOR: Kyon2570

// BASE CODE: Random Coins From Range
// https://github.com/PartyPlanner64/events/blob/master/C/Give%20Random%20Coins%20in%20Range.c

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

char *spray_bottle_msg =
    "Whoops\xC2 Looks like you were sprayed with a spray bottle\xC2"
    "\x0A"
    "Time to buy a new set of clothes\xC2"
    "\xFF";

extern s16 GetCurrentPlayerIndex();

void cleanupMessage() {
    func_800EC9DC();
    CloseMessage();
    func_800EC6EC();
}

void main() {
    s32 player_index = GetCurrentPlayerIndex();
    int numCoins = GetRandomByte() % 20;
    numCoins++;

    ShowMessage(-1, spray_bottle_msg, 0, 0, 0, 0, 0);
    cleanupMessage();

    AdjustPlayerCoinsGradual(player_index, -numCoins);
    ShowPlayerCoinChange(player_index, -numCoins);

    SleepProcess(30);
}