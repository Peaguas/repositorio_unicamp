#include <stdio.h>

int main(){
    int a;
    int b;
    int* c;
    a = b;
    c = &b;
    printf("%d %d %p", a, b, c);
}