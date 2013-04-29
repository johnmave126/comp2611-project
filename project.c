#include "project.h"

inline int min(a, b){
    return (a<b)?(a):(b);
}

inline int max(a, b){
    return (a>b)?(a):(b);
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

int test() {
    struct input t;
    t = input_game_params();
    return t.bomb;
}
