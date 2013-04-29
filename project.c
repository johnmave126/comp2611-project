#include "project.h"

inline int min(a, b){
    return (a<b)?(a):(b);
}

inline int max(a, b){
    return (a>b)?(a):(b);
}


void create_simple_bomb(int id, int x_loc, int y_loc, int speed) {
    __asm__(
        "li     $v0, 106\n\t"
        "syscall\n\t");
}

void create_remote_bomb(int id, int x_loc, int y_loc, int speed) {
    __asm__(
        "li     $v0, 107\n\t"
        "syscall\n\t");
}

int getX(int id) {
    __asm__(
        "li     $v0, 110\n\t"
        "syscall\n\t");
}

int getY(int id) {
    __asm__(
        "li     $v0, 110\n\t"
        "syscall\n\t"
        "move   $v0, $v1\n\t");
}

void activate_r_bomb(int id) {
    __asm__(
        "li     $v0, 109\n\t"
        "syscall\n\t");
}

void emit_one_bomb() {
    if(bomb_count < bomb_num) {
        create_simple_bomb(bomb_ids[bomb_count], getX(1), getY(1), 6);
        bomb_count++;
    }
}

void emit_one_rbomb() {
    if(rbomb_count < rbomb_num) {
        create_remote_bomb(rbomb_ids[rbomb_count], getX(1), getY(1), 6);
        rbomb_count++;
    }
}

void activate_rbombs(){
    int i;
    for(i = 0; i < rbomb_count; i++) {
        activate_r_bomb(rbomb_ids[i]);
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

void pp() {
    create_remote_bomb(10, 12,23,2);
}
