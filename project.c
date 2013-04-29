#include "project.h"

inline int min(a, b){
    return (a<b)?(a):(b);
}

inline int max(a, b){
    return (a>b)?(a):(b);
}

struct test {
    int x, y;
};

void create_simple_bomb(int id, int x_loc, int y_loc, int speed) {
    __asm__(
        "li     $v0, 106\n\t"
        "syscall\n\t":::"v0");
}

void create_remote_bomb(int id, int x_loc, int y_loc, int speed) {
    __asm__(
        "li     $v0, 107\n\t"
        "syscall\n\t":::"v0");
}

void emit_one_bomb() {
    if(bomb_count < bomb_num) {
        
    }
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

struct test pp() {
    struct test t;
    t.x = 19;
    t.y = 20;
    return t;
}
