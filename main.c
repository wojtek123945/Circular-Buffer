#include <stdio.h>
#include "circular_buffer.h"

int main() {

    int size;
    printf("Siema, podaj wielkosc buforka: ");
    if(scanf("%d", &size) != 1){
        printf("Incorrect input");
        return 1;
    }
    if(size<=0){
        printf("Incorrect input data");
        return 2;
    }
    struct circular_buffer_t *cb;
    int error = circular_buffer_create_struct(&cb, size);
    if(error == 2){
        printf("Failed to allocate memory");
        return 8;
    }
    while (1){
        int error_code;
        int what_next;
        printf("A co chcesz teraz zrobic (0-6): ");
        if(scanf("%d", &what_next) != 1){
            printf("Incorrect input");
            circular_buffer_destroy_struct(&cb);
            return 1;
        }
        switch (what_next) {
            case 0:{
                circular_buffer_destroy_struct(&cb);
                return 0;
            }
            case 1:{
                int add;
                printf("Podaj liczbe: ");
                if(scanf("%d", &add) != 1){
                    printf("Incorrect input");
                    circular_buffer_destroy_struct(&cb);
                    return 1;
                }
                circular_buffer_push_back(cb, add);
                break;
            }
            case 2:{
                int extract;
                extract = circular_buffer_pop_back(cb, &error_code);
                if(error_code == 2){
                    printf("Buffer is empty\n");

                }else{
                    printf("%d\n", extract);

                }
            }break;
            case 3:{
                int extract;
                extract = circular_buffer_pop_front(cb, &error_code);
                if(error_code == 2){
                    printf("Buffer is empty\n");

                }else{
                    printf("%d\n", extract);

                }
            }break;
            case 4:{
                if(circular_buffer_empty(cb) == 1){
                    printf("Buffer is empty\n");

                } else{
                    circular_buffer_display(cb);
                    printf("\n");
                }
            }break;
            case 5:{
                error = circular_buffer_empty(cb);
                if(error == 1){
                    printf("1\n");

                }else{
                    printf("0\n");

                }
            }break;
            case 6:{
                error = circular_buffer_full(cb);
                if(error == 1){
                    printf("1\n");

                }else{
                    printf("0\n");

                }
            }break;
            default:{
                printf("Incorrect input data\n");
                continue;
            }
        }
    }
}
