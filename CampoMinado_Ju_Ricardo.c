#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//#define _QtBombas_  5
#define _QtBombas_  8
#define _Height_   10 
#define _Width_    10
#define _BOMBA_    -8
#define _ABERTA_    0
#define _FECHADA_  -1
#define _VAZIA_    -2

//void MostraTabuleiro(int Tabuleiro[_Height_][_Width_], int TabVisual[_Height_][_Width_]);
int AbreArea(int Tabuleiro[_Height_][_Width_], int TabVisual[_Height_][_Width_], int X /*coluna */, int Y /* linha */, bool celulaAntVazia)
{
	int cont = 0;

	// teste teste
	//printf("TabVisual[%d][%d]: %d  Tabuleiro[%d][%d]: %d \n", Y, X, TabVisual[Y][X], Y, X, Tabuleiro[Y][X]);

	// verifica se posição selecionada pode ser aberta.
	if (TabVisual[Y][X] == _FECHADA_ && Tabuleiro[Y][X] == _VAZIA_)
	{
		TabVisual[Y][X] = _ABERTA_;
		cont++;

		if (Y > 0)              if (TabVisual[Y - 1][X] == _FECHADA_) cont += AbreArea(Tabuleiro, TabVisual, X, Y - 1, true); // conta acima
		if (Y < (_Height_ - 1)) if (TabVisual[Y + 1][X] == _FECHADA_) cont += AbreArea(Tabuleiro, TabVisual, X, Y + 1, true); // conta abaixo
		if (X < (_Width_ - 1))  if (TabVisual[Y][X + 1] == _FECHADA_) cont += AbreArea(Tabuleiro, TabVisual, X + 1, Y, true); // conta a direita
		if (X > 0)              if (TabVisual[Y][X - 1] == _FECHADA_) cont += AbreArea(Tabuleiro, TabVisual, X - 1, Y, true); // conta a direita
	}
	else if (TabVisual[Y][X] == _FECHADA_ && Tabuleiro[Y][X] > 0 && Tabuleiro[Y][X] <= 8 && celulaAntVazia)
	{
		/* se a célula selecionada possui uma contagem, esta fechada e foi chamada
		a partir de uma célula vazia e aberta, entao a abre.*/
		TabVisual[Y][X] = _ABERTA_;
		cont++;
	}
	else if (TabVisual[Y][X] == _FECHADA_ && Tabuleiro[Y][X] > 0 && Tabuleiro[Y][X] <= 8) {
		TabVisual[Y][X] = _ABERTA_;
		cont++;
	}
	else {
		TabVisual[Y][X] = _ABERTA_;
		// BOMBA, finaliza o jogo
	}
	return (cont);

}

void MostraTabuleiro(int Tabuleiro[_Height_][_Width_], int TabVisual[_Height_][_Width_]){
    int i, L, C, ic;
    //int f = 1;
    //int z = 1;

    // parte superior da moldura
    /*for (i = 0; i < _Width_; i++)
	{
		printf("   C%d", f++);
	}*/
	printf("\n");
	printf("%c", 201);
    for (i = 0; i < _Width_; i++){
        printf("%c%c%c%c%c", 205, 205, 205, 205, 205);
    }
    printf("%c\n", 187);
	
    for (L = 0; L < _Height_; L++){
    	//printf("L%d", z++);
	    printf("%c", 186);
        for (C = 0; C < _Width_; C++){
            // celula esta aberta?
            if (TabVisual[L][C] == _ABERTA_){
                switch (Tabuleiro[L][C]){
                case -8: printf("  %c  ", 225); break;
                case 1:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 2:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 3:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 4:  printf("  %d  ", Tabuleiro[L][C]); break; //correção aqui pois estava vazio
                case 5:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 6:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 7:  printf("  %d  ", Tabuleiro[L][C]); break;
                case 8:  printf("  %d  ", Tabuleiro[L][C]); break;
                default: printf("  .  "); break;
                }
            }else{
                printf("  %c  ", 254);
            }
        }
        printf("%c\n", 186);
    }

    // parte inferior da moldura
    printf("%c", 200);
    for (i = 0; i < _Width_; i++){
        printf("%c%c%c%c%c", 205, 205, 205, 205, 205);
    }
    printf("%c\n", 188);
}


void MontaTabuleiro(int Tabuleiro[_Height_][_Width_]){
	int L, C;
	int qtBombasAlocadas = 0;
	bool achei = false;
	// "limpar" a matriz
	for (L = 0; L < _Height_; L++)
	{
		for (C = 0; C < _Width_; C++)
		{
			Tabuleiro[L][C] = -1;
			Tabuleiro[L][C] = _VAZIA_;
		}
	}

	// sorteia as posições das bombas
	while (qtBombasAlocadas < _QtBombas_)
	{
		achei = false;
		int X = rand() % (_Width_ - 1); // sorteia uma posição X (coluna)
		int Y = rand() % (_Height_ - 1); // sorteia uma posição Y (linha)
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
	// contagem de bombas para cada célula
	int contBombas = 0;
	for (L = 0; L < _Height_; L++)
	{
		for (C = 0; C < _Width_; C++)
		{
			if (Tabuleiro[L][C] != _BOMBA_)
			{
				contBombas = 0;
				// acima - abaixo - direita - esquerda
				if (L > 0)              if (Tabuleiro[L - 1][C] == _BOMBA_) contBombas++; // conta acima
				if (L < (_Height_ - 1)) if (Tabuleiro[L + 1][C] == _BOMBA_) contBombas++; // conta abaixo
				if (C < (_Width_ - 1))  if (Tabuleiro[L][C + 1] == _BOMBA_) contBombas++; // conta a direita
				if (C > 0)              if (Tabuleiro[L][C - 1] == _BOMBA_) contBombas++; // conta a esquerda
				// Diagonais dos cantos
				if (L > 0 && C > 0)							 if (Tabuleiro[L - 1][C - 1] == _BOMBA_) contBombas++; // diag sup esquerda
				if (L > 0 && (C < _Width_ - 1))              if (Tabuleiro[L - 1][C + 1] == _BOMBA_) contBombas++; // diag sup direita

				if (L < (_Height_ - 1) && C < (_Width_ - 1)) if (Tabuleiro[L + 1][C + 1] == _BOMBA_) contBombas++; // diag inf direita
				if (L < (_Height_ - 1) && C > 0)             if (Tabuleiro[L + 1][C - 1] == _BOMBA_) contBombas++; // diag inf esquerda
				//
				Tabuleiro[L][C] = contBombas;
				if (L > 0 && (C < _Width_ - 1))              if (Tabuleiro[L - 1][C + 1] == _BOMBA_) contBombas++; // diag sup direita
				if (L > 0 && C > 0)							     				 if (Tabuleiro[L - 1][C - 1] == _BOMBA_) contBombas++; // diag sup esquerda

				Tabuleiro[L][C] = (contBombas == 0 ? _VAZIA_ : contBombas);
				// caso não exista nenhuma bomba ou contagem igual a zero, entao inicia a célula com o status _VAZIA_.
			}
		}
	}

}

void abreCelula(int Tabuleiro[_Height_][_Width_], int TabVisual[_Height_][_Width_], int L, int C){
	// Não pode ser bomba e a célula tem que estar vazia e não pode ter sido aberta
	if (Tabuleiro[L][C] != _BOMBA_ /*&& Tabuleiro[L][C] == -1*/ && TabVisual[L][C] != 0)
	{
		// Abre a célula desejada
		TabVisual[L][C] = 0;
		// acima - abaixo - direita - esquerda
		//						// Não pode ser bomba e a célula tem que estar vazia e não pode ter sido aberta
		if (L > 0)              if (Tabuleiro[L - 1][C] != _BOMBA_ /*&& Tabuleiro[L - 1][C] == -1*/ && TabVisual[L - 1][C] != 0) TabVisual[L - 1][C] = 0; //abreCelula(Tabuleiro, TabVisual, L - 1, C); // acima
		if (L < (_Height_ - 1)) if (Tabuleiro[L + 1][C] != _BOMBA_ /*&& Tabuleiro[L + 1][C] == -1*/ && TabVisual[L + 1][C] != 0)TabVisual[L + 1][C] = 0; //abreCelula(Tabuleiro, TabVisual, L + 1, C); // abaixo
		if (C < (_Width_ - 1))  if (Tabuleiro[L][C + 1] != _BOMBA_ /*&& Tabuleiro[L][C + 1] == -1*/ && TabVisual[L][C + 1] != 0)TabVisual[L][C + 1] = 0; //abreCelula(Tabuleiro, TabVisual, L, C + 1); // a direita
		if (C > 0)              if (Tabuleiro[L][C - 1] != _BOMBA_ /*&& Tabuleiro[L][C - 1] == -1*/ && TabVisual[L][C - 1] != 0)TabVisual[L][C - 1] = 0; //abreCelula(Tabuleiro, TabVisual, L, C - 1); // a esquerda
		// Diagonais dos cantos
		if (L > 0 && C > 0)							 if (Tabuleiro[L - 1][C - 1] != _BOMBA_ /*&& Tabuleiro[L - 1][C - 1] == -1*/ && TabVisual[L - 1][C - 1] != 0) TabVisual[L - 1][C - 1] = 0; // diag sup esquerda
		if (L > 0 && (C < _Width_ - 1))              if (Tabuleiro[L - 1][C + 1] != _BOMBA_ /*&& Tabuleiro[L - 1][C + 1] == -1*/ && TabVisual[L - 1][C + 1] != 0) TabVisual[L - 1][C + 1] = 0; // diag sup direita
		if (L < (_Height_ - 1) && C < (_Width_ - 1)) if (Tabuleiro[L + 1][C + 1] != _BOMBA_ /*&& Tabuleiro[L + 1][C + 1] == -1*/ && TabVisual[L + 1][C + 1] != 0) TabVisual[L + 1][C + 1] = 0; // diag inf direita
		if (L < (_Height_ - 1) && C > 0)             if (Tabuleiro[L + 1][C - 1] != _BOMBA_ /*&& Tabuleiro[L - 1][C - 1] == -1*/ && TabVisual[L + 1][C - 1] != 0) TabVisual[L + 1][C - 1] = 0; // diag inf esquerda
	}
}

int main(){

	int Tabuleiro[_Height_][_Width_];
	int TabVisual[_Height_][_Width_];
	// -1 : celula fechada
	//  0 : celula aberta
	// _FECHADA_ : -1 : celula fechada
	// _ABERTA_  :  0 : celula aberta

	int L, C;

	srand(time(NULL)); // inicia a semente do randomizador

	// teste: abre tabuleiro
	for (L = 0; L < _Height_; L++)
	{
		for (C = 0; C < _Width_; C++)
		{
			//TabVisual[L][C] = -1; // todas as células no estado fechado
			TabVisual[L][C] = _FECHADA_; // todas as células estao fechadas!
		}
	}

	MontaTabuleiro(Tabuleiro);
	abreCelula(Tabuleiro, TabVisual, 10, 10);
	int pontos = 0;
	int celulas = 1;
	int inicio = 0;
	printf("Bem vindo ao campo minado\n"); //feita condicionante de inicio de jogo
	printf("Gostaria de iniciar a partida? ");
	scanf("%d", &inicio);
	if(inicio == 1){
	
		while (celulas != 0) {
			int l = 0, c = 0;
			MostraTabuleiro(Tabuleiro, TabVisual);
			printf("Digite a linha desejada:\n");
			scanf("%d", &l);

			printf("Digite a coluna desejada:\n");
			scanf("%d", &c);

			if (l < 1 || c < 1 || l > _Height_ || c > _Width_) {
				printf("Jogada em linha ou coluna invalidas ! L(%d) C(%d)\n", l, c);
			}else {
			celulas = AbreArea(Tabuleiro, TabVisual, c - 1, l - 1, false);
			pontos += celulas;
			MostraTabuleiro(Tabuleiro, TabVisual);
			}
		}
	}else{
		printf("Medo muito sinto em voce eu!!!");
	}
		
	printf("\nFinal de jogo total de pontos: %d\n", pontos);
//não entendi ainda porque limita em 3 jogadas
} 
