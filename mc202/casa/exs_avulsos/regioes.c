#include <stdio.h>

int Regiao(float x1, float x2, float y1, float y2, float x, float y){
    if ((x1<=x) && (x<=x2) && (y1<=y) && (y<=y2)){
        return(3);
    } else {
        if (((x1<=x) && (x<=x2)) || ((y1<=y) && (y<=y2))){
            return(2);
        } else {
            return(1);
        }
    }
}

int main(){
    float x1, x2, y1, y2, x, y;
    int reg;
    printf("Insira o limite inferior: ");
    scanf("%f %f", &x1, &y1);
    printf("Insira o limite superior: ");
    scanf("%f %f", &x2, &y2);
    printf("Insira as coordenadas: ");
    scanf("%f %f", &x, &y);
    reg = Regiao(x1, x2, y1 ,y2, x, y);
    printf("Suas coordenadas se encontram na regiao %d", reg);
}