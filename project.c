#include "project.h"

inline int min(a, b){
    return (a<b)?(a):(b);
}

inline int max(a, b){
    return (a>b)?(a):(b);
}

struct input __attribute__ ((noinline)) wrap_igp() {
    __asm(
        "addi   $sp, $sp, -24\n\t"
        "sw     $4, 16($sp)\n\t"
        "sw     $ra, 20($sp)\n\t"
        "jal    input_game_params\n\t"
        "lw     $2, 16($sp)\n\t"
        "lw     $ra, 20($sp)\n\t"
        "lw     $t0, 0($sp)\n\t"
        "sw     $t0, 0($2)\n\t"
        "lw     $t0, 4($sp)\n\t"
        "sw     $t0, 4($2)\n\t"
        "lw     $t0, 8($sp)\n\t"
        "sw     $t0, 8($2)\n\t"
        "lw     $t0, 12($sp)\n\t"
        "sw     $t0, 12($2)\n\t"
        "addi   $sp, $sp, 24\n\t"
        "jr     $ra\n\t");
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
