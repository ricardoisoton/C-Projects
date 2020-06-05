#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _QtBombas_  5
#define _Height_   10 
#define _Width_    10
#define _BOMBA_    -8
#define _ABERTA_    0
#define _FECHADA_  -1
#define _VAZIA_    -2

int AbreArea( int Tabuleiro[_Height_][_Width_],
              int TabVisual[_Height_][_Width_],
              int X /*coluna */,
              int Y /* linha */){
     int cont = 0;
    
    
     // verifica se posi��o selecionada pode ser aberta.
     if( TabVisual[Y][X] == _FECHADA_ && Tabuleiro[Y][X] == _VAZIA_ )
     {
        TabVisual[Y][X] = _ABERTA_;
        cont++;
       
       if( Y > 0 )              if( TabVisual[Y-1][X] == _FECHADA_ ) cont+= AbreArea(Tabuleiro, TabVisual, X, Y-1); if (Tabuleiro[Y-1][X] > 0) TabVisual[Y-1][X] = _ABERTA_; // conta acima
       if( Y < (_Height_ - 1))  if( TabVisual[Y+1][X] == _FECHADA_ ) cont+= AbreArea(Tabuleiro, TabVisual, X, Y+1); if (Tabuleiro[Y+1][X] > 0) TabVisual[Y+1][X] = _ABERTA_; // conta abaixo
       if( X < (_Width_ - 1 ))  if( TabVisual[Y][X+1] == _FECHADA_ ) cont+= AbreArea(Tabuleiro, TabVisual, X+1, Y); if (Tabuleiro[Y][X+1] > 0) TabVisual[Y][X+1] = _ABERTA_; // conta a direita
       if( X > 0 )              if( TabVisual[Y][X-1] == _FECHADA_ ) cont+= AbreArea(Tabuleiro, TabVisual, X-1, Y); if (Tabuleiro[Y][X-1] > 0) TabVisual[Y][X-1] = _ABERTA_; // conta a direita
     }
     
     return ( cont );
  
}

void MostraTabuleiro(int Tabuleiro[_Height_][_Width_],
    int TabVisual[_Height_][_Width_])
{
    int i, L, C;

    // parte superior da moldura
    printf("%c", 201);
    for (i = 0; i < _Width_; i++)
    {
        printf("%c%c%c%c%c", 205, 205, 205, 205, 205);
    }
    printf("%c\n", 187);

    for (L = 0; L < _Height_; L++)
    {
        printf("%c", 186);
        for (C = 0; C < _Width_; C++)
        {
            // celula esta aberta?
            if (TabVisual[L][C] == _ABERTA_)
            {
                switch (Tabuleiro[L][C])
                {
                case -8: printf("  %c  ", 225); break;
                case 1:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 2:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 3:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 4:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 5:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 6:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 7:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 8:  printf("  %d  ", Tabuleiro[L][C]); break;
                default: printf("  .  "); break;
                }
            }
            else
            {
                printf("  %c  ", 254);
            }
        }
        printf("%c\n", 186);
    }

    // parte inferior da moldura
    printf("%c", 200);
    for (i = 0; i < _Width_; i++)
    {
        printf("%c%c%c%c%c", 205, 205, 205, 205, 205);
    }
    printf("%c\n", 188);

}


void MontaTabuleiro(int Tabuleiro[_Height_][_Width_])
{
    int L, C;
    int qtBombasAlocadas = 0;
    bool achei = false;

    // "limpar" a matriz
    for (L = 0; L < _Height_; L++)
    {
        for (C = 0; C < _Width_; C++)
        {
            Tabuleiro[L][C] = _VAZIA_;
        }
    }

    // sorteia as posi��es das bombas
    while (qtBombasAlocadas < _QtBombas_)
    {
        achei = false;
        int X = rand() % (_Width_  - 1); // sorteia uma posi��o X (coluna)
        int Y = rand() % (_Height_ - 1); // sorteia uma posi��o Y (linha)

        if (Tabuleiro[Y][X] == _BOMBA_)
        {
            achei = true;
        }

        if (!achei)
        {
            Tabuleiro[Y][X] = _BOMBA_;
            qtBombasAlocadas++;
        }

    }

    // contagem de bombas para cada c�lula
    int contBombas = 0;
    for (L = 0; L < _Height_; L++)
    {
        for (C = 0; C < _Width_; C++)
        {
            if (Tabuleiro[L][C] != _BOMBA_)
            {
                contBombas = 0;
                if (L > 0)              if (Tabuleiro[L - 1][C] == _BOMBA_) contBombas++; // conta acima
                if (L < (_Height_ - 1)) if (Tabuleiro[L + 1][C] == _BOMBA_) contBombas++; // conta abaixo
                if (C < (_Width_ - 1))  if (Tabuleiro[L][C + 1] == _BOMBA_) contBombas++; // conta a direita
                if (C > 0)              if (Tabuleiro[L][C - 1] == _BOMBA_) contBombas++; // conta a esquerda

                if (L < (_Height_ - 1) && C < (_Width_ - 1)) if (Tabuleiro[L + 1][C + 1] == _BOMBA_) contBombas++; // diag inf direita
                if (L < (_Height_ - 1) && C > 0)             if (Tabuleiro[L + 1][C - 1] == _BOMBA_) contBombas++; // diag inf esquerda
                if (L > 0 && (C < _Width_ - 1))              if (Tabuleiro[L - 1][C + 1] == _BOMBA_) contBombas++; // diag sup direita
                if (L > 0 && C > 0)							 if (Tabuleiro[L - 1][C - 1] == _BOMBA_) contBombas++; // diag sup esquerda

                Tabuleiro[L][C] = (contBombas == 0 ? _VAZIA_ : contBombas);
                // caso n�o exista nenhuma bomba ou contagem igual a zero, entao inicia a c�lula com o status _VAZIA_.
            }
        }
    }

}

int main()
{

    int Tabuleiro[_Height_][_Width_];
    int TabVisual[_Height_][_Width_];
    // _FECHADA_ : -1 : celula fechada
    // _ABERTA_  :  0 : celula aberta

    int L, C;

    srand(time(NULL)); // inicia a semente do randomizador

    // teste: abre tabuleiro
    for (L = 0; L < _Height_; L++)
    {
        for (C = 0; C < _Width_; C++)
        {
            TabVisual[L][C] = _FECHADA_; // todas as c�lulas estao fechadas!
        }
    }
   /*TabVisual[5][5] = _ABERTA_;
   TabVisual[5][6] = _ABERTA_;
   TabVisual[6][5] = _ABERTA_;
   TabVisual[6][6] = _ABERTA_; */

    MontaTabuleiro(Tabuleiro);
    int cont = AbreArea( Tabuleiro, TabVisual, 0, 0);
  
    MostraTabuleiro(Tabuleiro, TabVisual);
    
    printf("\nCelulas abertas: %d\n", cont);

}
