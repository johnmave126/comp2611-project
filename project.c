#include "project.h"

inline int min(a, b){
    return (a<b)?(a):(b);
}

inline int max(a, b){
    return (a>b)?(a):(b);
}

struct input wrap_igp() {
    __asm__(
        "addi   $sp, $sp, -24\n"
        "sw     $4, 16($sp)\n"
        "sw     $ra, 20($sp)\n"
        "jal    input_game_params\n"
        "lw     $2, 16($sp)\n"
        "lw     $ra, 20($sp)\n"
        "lw     $t0, 0($sp)\n"
        "sw     $t0, 0($2)\n"
        "lw     $t0, 4($sp)\n"
        "sw     $t0, 4($2)\n"
        "lw     $t0, 8($sp)\n"
        "sw     $t0, 8($2)\n"
        "lw     $t0, 12($sp)\n"
        "sw     $t0, 12($2)\n"
        "addi   $sp, $sp, 24\n"
        "jr     $ra\n");
}

int check_intersection(int *rec1, int *rec2) {
    if(max(rec1[0], rec2[0]) > min(rec1[2], rec1[2])) {
        return 0;
    }
    if(max(rec1[1], rec2[1]) > min(rec1[3], rec1[3])) {
        return 0;
    }
    return 1;
}

struct input test() {
    struct input t;
    t = wrap_igp();
    t.bomb += t.cool;
    t.bomb -= t.air;
    return t;
}
