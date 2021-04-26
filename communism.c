// NAME: Jumanji: Draw Card
// GAMES: MP3_USA
// EXECUTION: Direct

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
    s16 coins; // 10
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
}; // sizeof == 56

/*Memory Addresses*/

extern u16 D_800D1112;	//Player 1 Coins
extern u16 D_800D114A;	//Player 2 Coins
extern u16 D_800D1182;	//Player 3 Coins
extern u16 D_800D11BA;	//Player 4 Coins

char *msg_communism = "\x0B"
    "To horde gold is selfish\x82 no matter who you are\x82" "\n"
    "All are seen equal\x82 praise the " "\x03" "sickle and star" "\x08" "\xC2" "\xFF";

/********************************************************
********************* SUB-FUNCTIONS *********************
********************************************************/

void msgBox(char *message){
    // First argument is character image (-1 for none).
	ShowMessage(-1, message, 0, 0);
    
    // The rest here perform the "wait for confirmation"
	// and messagebox teardown.
    func_800EC9DC();
    CloseMessage();
    func_800EC6EC();
}

/********************************************************
********************* MAIN FUNCTION *********************
********************************************************/

void main() {
    //Display card text
    msgBox(msg_communism);
    
    int totalCoins = D_800D1112 + D_800D114A + D_800D1182 + D_800D11BA;
    int newTotal = totalCoins / 4;
    
    AdjustPlayerCoinsGradual(0, -1*D_800D1112);
    AdjustPlayerCoinsGradual(1, -1*D_800D114A);
    AdjustPlayerCoinsGradual(2, -1*D_800D1182);
    AdjustPlayerCoinsGradual(3, -1*D_800D11BA);
    
    SleepProcess(30);
    
    AdjustPlayerCoinsGradual(0, newTotal);
    AdjustPlayerCoinsGradual(1, newTotal);
    AdjustPlayerCoinsGradual(2, newTotal);
    AdjustPlayerCoinsGradual(3, newTotal);
    
    SleepProcess(30);
    
}



