#include <stdio.h>

void Ajusta(int x, int *y, int *z){
    x = x + 1;
    *y = *y + 1;
    z = y;
    *z = *z + 10;
}

int main(void){
    int a = 1, b = 2, c = 3;

    Ajusta(a, &b, &c);
    printf("a=%d b=%d c=%d\n", a, b, c);

    return 0;
}