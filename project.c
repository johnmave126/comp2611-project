#include "project.h"

inline int min(a, b){
    return (a<b)?(a):(b);
}

inline int max(a, b){
    return (a>b)?(a):(b);
}


void create_simple_bomb(int id, int x_loc, int y_loc, int speed) {
    const register int t1 asm("a0") = id;
    const register int t2 asm("a1") = x_loc;
    const register int t3 asm("a2") = y_loc;
    const register int t4 asm("a3") = speed;
    __asm__(
        "li     $v0, 106\n\t"
        "syscall\n\t"::"r"(t1), "r"(t2), "r"(t3), "r"(t4):"v0");
}

void create_remote_bomb(int id, int x_loc, int y_loc, int speed) {
    const register int t1 asm("a0") = id;
    const register int t2 asm("a1") = x_loc;
    const register int t3 asm("a2") = y_loc;
    const register int t4 asm("a3") = speed;
    __asm__(
        "li     $v0, 107\n\t"
        "syscall\n\t"::"r"(t1), "r"(t2), "r"(t3), "r"(t4):"v0");
}

int getX(int id) {
    const register int t1 asm("a0") = id;
    register int t2 asm("v0");
    __asm__(
        "li     $v0, 110\n\t"
        "syscall\n\t"::"r"(t1):"v0", "v1");
    return t2;
}

int getY(int id) {
    const register int t1 asm("a0") = id;
    register int t2 asm("v1");
    __asm__(
        "li     $v0, 110\n\t"
        "syscall\n\t"::"r"(t1):"v0", "v1");
    return t2;
}

int getHit(int id) {
    const register int t1 asm("a0") = id;
    register int t2 asm("v0");
    __asm__(
        "li     $v0, 118\n\t"
        "syscall\n\t"::"r"(t1):"v0");
    return t2;
}

void destory_object(int id) {
    const register int t1 asm("a0") = id;
    __asm__(
        "li     $v0, 116\n\t"
        "syscall\n\t"::"r"(t1):"v0");
}

void activate_r_bomb(int id) {
    const register int t1 asm("a0") = id;
    __asm__(
        "li     $v0, 109\n\t"
        "syscall\n\t"::"r"(t1):"v0");
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

void update_object_status() {
    int i, t;
    i = 0;
    while(i < dolphin_num) {
        if(getHit(dolphin_ids[i]) == 0) {
            destory_object(dolphin_ids[i]);
            dolphin_num--;
            t = dolphin_ids[i];
            dolphin_ids[i] = dolphin_ids[dolphin_num];
            dolphin_ids[dolphin_num] = t;
            dolphin_locs[2 * i] = dolphin_locs[2 * dolphin_num];
            dolphin_locs[2 * i + 1] = dolphin_locs[2 * dolphin_num + 1];
        }
        else {
            i++;
        }
    }
    i = 0;
    while(i < subma_num) {
        if(getHit(subma_ids[i]) == 0) {
            destory_object(subma_ids[i]);
            subma_num--;
            t = subma_ids[i];
            subma_ids[i] = subma_ids[subma_num];
            subma_ids[subma_num] = t;
            subma_locs[2 * i] = subma_locs[2 * subma_num];
            subma_locs[2 * i + 1] = subma_locs[2 * subma_num + 1];
        }
        else {
            i++;
        }
    }
    i = 0;
    while(i < bomb_count) {
        if(getHit(bomb_ids[i]) == 0) {
            destory_object(bomb_ids[i]);
            bomb_count--;
            t = bomb_ids[i];
            bomb_ids[i] = bomb_ids[bomb_count];
            bomb_ids[bomb_count] = t;
        }
        else {
            i++;
        }
    }
    i = 0;
    while(i < rbomb_count) {
        if(getHit(rbomb_ids[i]) == 0) {
            destory_object(rbomb_ids[i]);
            rbomb_count--;
            t = rbomb_ids[i];
            rbomb_ids[i] = rbomb_ids[rbomb_count];
            rbomb_ids[rbomb_count] = t;
        }
        else {
            i++;
        }
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

int check_game_end() {
    if(subma_num == 0) {
        return 1;
    }
    else if(dolphin_num == 0) {
        return 2;
    }
    return 0;
}

void pp() {
    create_remote_bomb(10, 12,23,2);
}
