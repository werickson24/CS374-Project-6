#include "myalloc.h"
#include <stdio.h>

int main(void){
    void *p;

    print_data();
    p = myalloc(16);
    print_data();
    p = myalloc(16);
    printf("%p\n", p);
}
