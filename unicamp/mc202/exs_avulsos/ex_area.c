#include <stdio.h>
#define PI 3.14159265358

float AreaCirculo (float raio){
    float area = PI*raio*raio;
    return(area);
}

int main(){
    float raio, area;

    printf("Entre com o raio (cm): ");
    scanf("%f", &raio);
    area = AreaCirculo(raio);
    printf("Area circulo: %.2fcm2\n", area);
    return(0);
}