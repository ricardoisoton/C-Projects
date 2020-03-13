#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define N 50

//Desenvolvido por Ricardo Isoton
//Data 12/03/2020			Versão 1.3


void MostraM(char M[N][N]) {
int i, j;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf(" %c", M[i][j]);
		}
		printf("\n");
	}
}
float distancia(float n1, float n2, float n3, float n4) {
	float res;
	res = abs(n1-n2)+abs(n3-n4);
	return res;
}
float eixos (float n1, float n2){
	float res;
	res = abs(n1-n2);
	return res;
}

int main() {

char M[N][N];
int k, i, j;
float d=0, x=0, y=0;
float ax=0, ay=0, bx=0, by=0, cx=0, cy=0, dx=0, dy=0, ex = 0, ey = 0, fx=0, fy=0, gx=0, gy=0;
float incx=0, incy=0;
srand (time(NULL));

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			M[i][j] = '.';
		}
	}
//Coordenadas dos pontos
ax = N-1; ay = N/2;
bx = rand() % N; by = rand() % N;
cx = rand() % N; cy = rand() % N;
dx = rand() % N; dy = rand() % N;
ex = rand() % N; ey = rand() % N;
fx = rand() % N; fy = rand() % N;
gx = rand() % N; gy = rand() % N;

{//Calculo da distancia entre os pontos A-B
d = distancia(bx, ax, by, ay);
incx = eixos(bx, ax)/d;
if(bx<ax){incx*=-1;}
incy = eixos(by, ay)/d;
if(by<ay){incy*=-1;}

x = ax;
y = ay;
	for(k=0; k<d; k++){
		M[(int) x][(int)y] = '*';
		x+=incx;
		y+=incy;
	}
}
{//Calculo da distancia entre os pontos A-C
d = distancia(cx, ax, cy, ay);
incx = eixos(cx, ax)/d;
if(cx<ax){incx*=-1;}
incy = eixos(cy, ay)/d;
if(cy<ay){incy*=-1;}

x = ax;
y = ay;

	for(k=0; k<d; k++){
		M[(int) x][(int)y] = '*';
		x+=incx;
		y+=incy;
	}
}
{//Calculo da distancia entre os pontos A-D
d = distancia(dx, ax, dy, ay);
incx = eixos(dx, ax)/d;
if(dx<ax){incx*=-1;}
incy = eixos(dy, ay)/d;
if(dy<ay){incy*=-1;}

x = ax;
y = ay;
	for(k=0; k<d; k++){
		M[(int) x][(int)y] = '*';
		x+=incx;
		y+=incy;
	}
}
{//Calculo da distancia entre os pontos A-E
d = distancia(ex, ax, ey, ay);
incx = eixos(ex, ax)/d;
if(ex<ax){incx*=-1;}
incy = eixos(ey, ay)/d;
if(ey<ay){incy*=-1;}

x = ax;
y = ay;
	for(k=0; k<d; k++){
		M[(int) x][(int)y] = '*';
		x+=incx;
		y+=incy;
	}
}
{//Calculo da distancia entre os pontos A-F
d = distancia(fx, ax, fy, ay);
incx = eixos(fx,ax)/d;
if(fx<ax){incx*=-1;}
incy = eixos(fy, ay)/d;
if(fy<ay){incy*=-1;}

x = ax;
y = ay;
	for(k=0; k<d; k++){
		M[(int) x][(int)y] = '*';
		x+=incx;
		y+=incy;
	}
}
{//Calculo da distancia entre os pontos A-G
d = distancia(gx, ax, gy, ay);
incx = eixos(gx,ax)/d;
if(gx<ax){incx*=-1;}
incy = eixos(gy, ay)/d;
if(gy<ay){incy*=-1;}

x = ax;
y = ay;
	for(k=0; k<d; k++){
		M[(int) x][(int)y] = '*';
		x+=incx;
		y+=incy;
	}
}

	M[(int)ax][(int)ay] = 'A';
	M[(int)bx][(int)by] = 'B';
	M[(int)cx][(int)cy] = 'C';
	M[(int)dx][(int)dy] = 'D';
	M[(int)ex][(int)ey] = 'E';
	M[(int)fx][(int)fy] = 'F';
	M[(int)gx][(int)gy] = 'G';
	
	MostraM(M);
	
	return 0;
	
}
