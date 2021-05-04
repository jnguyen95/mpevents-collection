// NAME: TRG Colosseum - Give Free Star (MP3)
// GAMES: MP3_USA
// EXECUTION: Direct
// AUTHOR: Kyon2570

#include "ultra64.h"
#define MAX_STARS 99

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

extern s16 GetCurrentPlayerIndex();

void cleanupMessage() {
    func_800EC9DC();
    CloseMessage();
    func_800EC6EC();
}

char *trgc_msg =
    "Hello\xC2 This is the TRG Colosseum staff\xC2"
    "\xFF";
    
char *free_star_msg =
    "Thank you for your hard work doing the TRG Colosseum\xC2"
    "\x0A"
    "Here\x5Cs a star to thank you for all of your efforts\xC2"
    "\xFF";

char *too_many_stars_msg =
    "Thank you for your hard work doing the TRG Colosseum\xC2"
    "\x0A"
    "Unfortunately\x82 you have too many stars\x85"
    "\xFF"

void main() {
    s32 cur_player_index = GetCurrentPlayerIndex();
    struct player *player = GetPlayerStruct(cur_player_index);
    ShowMessage(-1, trgc_msg, 0, 0, 0, 0, 0);
    cleanupMessage();

    if (player->stars >= MAX_STARS) {
        ShowMessage(-1, too_many_stars_msg, 0, 0, 0, 0, 0);
        cleanupMessage();
    }
    else {
        ShowMessage(-1, free_star_msg, 0, 0, 0, 0, 0);
        cleanupMessage();

        PlayMusic(111);
        player->stars++;
        SetBoardPlayerAnimation(-1, 6, 0);
        func_8004ACE0(610, cur_player_index);
        SleepProcess(60);
        SleepProcess(50);

        PlayMusic(GetBoardAudioIndex());
    }
}