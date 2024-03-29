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
    __asm__ __volatile__(
        "li     $v0, 110\n\t"
        "syscall\n\t":"=r"(t2):"r"(t1):"v1");
    return t2;
}

int getY(int id) {
    const register int t1 asm("a0") = id;
    register int t2 asm("v1");
    __asm__ __volatile__(
        "li     $v0, 110\n\t"
        "syscall\n\t":"=r"(t2):"r"(t1):"v0");
    return t2;
}

int getHit(int id) {
    const register int t1 asm("a0") = id;
    register int t2 asm("v0");
    __asm__(
        "li     $v0, 118\n\t"
        "syscall\n\t":"=r"(t2):"r"(t1));
    return t2;
}

int getScore(int id) {
    const register int t1 asm("a0") = id;
    register int t2 asm("v0");
    __asm__(
        "li     $v0, 115\n\t"
        "syscall\n\t":"=r"(t2):"r"(t1));
    return t2;
}

void setScore(int score) {
    const register int t1 asm("a0") = score;
    __asm__(
        "li     $v0, 117\n\t"
        "syscall\n\t"::"r"(t1):"v0");
}

void update_bomb(int b, int r) {
    const register int t1 asm("a0") = b;
    const register int t2 asm("a1") = r;
    __asm__(
        "li     $v0, 123\n\t"
        "syscall\n\t"::"r"(t1),"r"(t2):"v0");
}

void hit(int id, int point) {
    const register int t1 asm("a0") = id;
    const register int t2 asm("a1") = point;
    __asm__(
        "li     $v0, 114\n\t"
        "syscall\n\t"::"r"(t1),"r"(t2):"v0");
}

int isActive(int id) {
    const register int t1 asm("a0") = id;
    register int t2 asm("v0");
    __asm__(
        "li     $v0, 108\n\t"
        "syscall\n\t":"=r"(t2):"r"(t1));
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

void play_sound(int id) {
    const register int t1 asm("a0") = id;
    __asm__(
        "li     $a1, 0\n\t"
        "li     $v0, 105\n\t"
        "syscall\n\t"::"r"(t1):"a1");
}

void emit_one_bomb() {
    if(bomb_count < bomb_num) {
        create_simple_bomb(bomb_ids[bomb_count], getX(1) + 80, 260, 5);
        bomb_count++;
        update_bomb(bomb_num - bomb_count, rbomb_num - rbomb_count);
        play_sound(2);
    }
}

void emit_one_rbomb() {
    if(rbomb_count < rbomb_num) {
        create_remote_bomb(rbomb_ids[rbomb_count], getX(1) + 80, 260, 5);
        rbomb_count++;
        update_bomb(bomb_num - bomb_count, rbomb_num - rbomb_count);
        play_sound(2);
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
            base_score += getScore(subma_ids[i]);
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
    update_bomb(bomb_num - bomb_count, rbomb_num - rbomb_count);
}

__attribute__ ((noinline)) int check_intersection(int *rec1, int *rec2) {
    if(max(rec1[0], rec2[0]) > min(rec1[2], rec2[2])) {
        return 0;
    }
    if(max(rec1[1], rec2[1]) > min(rec1[3], rec2[3])) {
        return 0;
    }
    return 1;
}

__attribute__ ((noinline)) void check_one_bomb_hit(int id) {
    int i;
    int flag = 0;
    int rec1[4], rec2[4];
    rec1[0] = getX(id);
    rec1[1] = getY(id);
    rec1[2] = rec1[0] + 30;
    rec1[3] = rec1[1] + 30;
    if(id < rbomb_base || isActive(id)) {
        //Dolphin
        for(i = 0; i < dolphin_num; i++) {
            rec2[0] = getX(dolphin_ids[i]);
            rec2[1] = getY(dolphin_ids[i]);
            rec2[2] = rec2[0] + 60;
            rec2[3] = rec2[1] + 40;

            if(check_intersection(rec1, rec2)) {
                hit(dolphin_ids[i], getHit(dolphin_ids[i]));
                flag = 1;
            }
        }
        //Submarine
        for(i = 0; i < subma_num; i++) {
            rec2[0] = getX(subma_ids[i]) + 35;
            rec2[1] = getY(subma_ids[i]);
            rec2[2] = rec2[0] + 10;
            rec2[3] = rec2[1] + 40;

            if(check_intersection(rec1, rec2)) {
                hit(subma_ids[i], getHit(subma_ids[i]));
                flag = 1;
            }

            rec2[0] -= 35;
            rec2[2] = rec2[0] + 80;

            if(check_intersection(rec1, rec2)) {
                hit(subma_ids[i], 5);
                flag = 1;
            }
        }
    }
    if(flag) {
        hit(id, getHit(id));
        play_sound(1);
        play_sound(5);
    }
}

void check_bomb_hits() {
    int i;
    for(i = 0; i < bomb_count; i++) {
        check_one_bomb_hit(bomb_ids[i]);
    }
    for(i = 0; i < rbomb_count; i++) {
        check_one_bomb_hit(rbomb_ids[i]);
    }
}

int check_game_end() {
    if(dolphin_num == 0) {
        return 2;
    }
    else if(subma_num == 0) {
        return 1;
    }
    return 0;
}

void update_score() {
    int i;
    int score = base_score;
    for(i = 0; i < subma_num; i++) {
        score += getScore(subma_ids[i]);
    }
    setScore(score);
}
