#include "circular_buffer.h"
#include <stdlib.h>
#include "stdio.h"

#ifndef CIRECULAR_BUFFER_H
#define CIRECULAR_BUFFER_H

//Struck
//int *ptr;
//    int begin;
//    int end;
//    int capacity;
//    unsigned char full: 1;

int circular_buffer_create(struct circular_buffer_t *a, int N){
    if(!a || N<=0){
        return 1;
    }
    a->ptr = malloc(sizeof(int) * N);
    if(!(a->ptr)){
        return 2;
    }
    a->begin = 0;
    a->end = 0;
    a->capacity = N;
    a->full = 0;
    return 0;
}
int circular_buffer_create_struct(struct circular_buffer_t **cb, int N){
    if(!cb || N<=0){
        return 1;
    }
    *cb = malloc(sizeof(struct circular_buffer_t));
    if(!*cb){
        return 2;
    }
    int error = circular_buffer_create(*cb, N);
    if(error == 1){
        free(*cb);
        return 1;
    }else if(error == 2){
        free(*cb);
        return 2;
    }
    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *cb){
    if(cb && cb->ptr){
        free(cb->ptr);
    }
}
void circular_buffer_destroy_struct(struct circular_buffer_t **cb){
    if(!cb){
        return;
    }
    circular_buffer_destroy(*cb);
    free(*cb);
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value){
    // Funkcja dodaje element value na koniec tablicy w strukturze cb, aktualizując wartości odpowiednich pól struktury.

    if(!cb || cb->capacity <= 0 || !cb->ptr || cb->begin<0 || cb->begin >= cb->capacity || cb->end <0 || cb->end>=cb->capacity){
        return 1;
    }
    *(cb->ptr + cb->end) = value;
    cb->end++;
    if(cb->end == cb->capacity){
        cb->end = 0;
        //Begin dodaje bo takto wskazywał by na ostatni elemnet a nie na pierwszy !!!
    }
    if(cb->full == 1){
        cb->begin++;
        if(cb->begin == cb->capacity){
            cb->begin = 0;
        }
    }
    //Sprawdzanie flagi

        if(cb->end == cb->begin){
            cb->full=1;
        } else{
            cb->full=0;
        }
    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *cb, int *err_code){
    if(!cb || cb->capacity <= 0 || !cb->ptr || cb->begin<0 || cb->begin >= cb->capacity || cb->end <0 || cb->end>=cb->capacity){
        if(err_code){
            *err_code = 1;
        }
        return -100000;
    }
    //Funkcja zwraca i usuwa pierwszy element tablicy w strukturze cb, aktualizując wartości odpowiednich pól struktury.
    if(cb->end == cb->begin && cb->full==0){
        if(err_code){
            *err_code = 2;
        }
        return -100000;
    }
    int temp = *(cb->ptr + cb->begin);
    cb->begin++;
    if(cb->begin == cb->capacity){
        cb->begin = 0;
    }
    if(err_code){
        *err_code=0;
    }
    cb->full=0;
    return temp;
}

int circular_buffer_pop_back(struct circular_buffer_t *cb, int *err_code){
    if(!cb || cb->capacity <= 0 || !cb->ptr || cb->begin<0 || cb->begin >= cb->capacity || cb->end <0 || cb->end>=cb->capacity){
        if(err_code){
            *err_code = 1;
        }
        return -100000;
    }
    //Sprawdzenie czy buffor nie jest pusty
    if(cb->begin == cb->end && cb->full==0){
        if(err_code){
            *err_code = 2;
        }
        return -1000000;
    }
        int temp;
        if(cb->end == 0){
            temp = *(cb->ptr + cb->capacity-1);
            cb->end = cb->capacity-1;
        }else{
            temp=*(cb->ptr + cb->end-1);
            cb->end--;
        }
        if(err_code){
            *err_code = 0;
        }
        cb->full=0;
        return temp;

}

int circular_buffer_empty(const struct circular_buffer_t *cb){
    if(!cb || cb->capacity <= 0 || !cb->ptr || cb->begin<0 || cb->begin >= cb->capacity || cb->end <0 || cb->end>=cb->capacity){
        return -1;
    }
    if(cb->begin == cb->end && cb->full==0){
        return 1;
    }else{
        return 0;
    }
}
int circular_buffer_full(const struct circular_buffer_t *cb){
    if(!cb || cb->capacity <= 0 || !cb->ptr || cb->begin<0 || cb->begin >= cb->capacity || cb->end <0 || cb->end>=cb->capacity){
        return -1;
    }
    if(cb->end == cb->begin && cb->full==1){
        return 1;
    }else{
        return 0;
    }
}
void circular_buffer_display(const struct circular_buffer_t *cb){
    if(!cb || cb->capacity <= 0 || !cb->ptr || cb->begin<0 || cb->begin >= cb->capacity || cb->end <0 || cb->end>=cb->capacity){
        return;
    }
    if(circular_buffer_empty(cb) == 1){
        return;
    }
    if(cb->end>cb->begin){
        for (int i = cb->begin; i < cb->end; ++i) {
            printf("%d ", *(cb->ptr + i));
        }
    }else if(cb->end <= cb->begin){
        for (int i = cb->begin; i < cb->capacity ; ++i) {
            printf("%d ", *(cb->ptr + i));
        }
        for (int i = 0; i < cb->end; ++i) {
            printf("%d ", *(cb->ptr + i));
        }
    }
    return;
}
#endif