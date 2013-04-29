extern char* title, game_win, game_lose, input_dolphin, input_subma, input_bombs, input_rbombs;
extern int width, height, subma_ids, subma_locs, subma_base, subma_num, dolphin_ids, dolphin_locs, dolphin_base, dolphin_num;
extern int bomb_ids, bomb_base, bomb_num, bomb_count, rbomb_ids, rbomb_base, rbomb_num, rbomb_count;

struct input {
    int bomb;
    int air;
    int cool;
};

struct input input_game_params();
