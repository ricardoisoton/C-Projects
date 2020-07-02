/* Campo Minado
// Juliana Costa e Ricardo Isoton
// versão 4.0 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define _QtBombas_  1
#define _Height_   10 
#define _Width_    10
#define _BOMBA_    -8
#define _ABERTA_    0
#define _FECHADA_  -1
#define _VAZIA_    -2
#define _BANDEIRA_ -5

int AbreArea(int Tabuleiro[_Height_][_Width_], int TabVisual[_Height_][_Width_], int X /*coluna */, int Y /* linha */, bool celulaAntVazia){
	int cont = 0;
	// teste teste
	//printf("TabVisual[%d][%d]: %d  Tabuleiro[%d][%d]: %d \n", Y, X, TabVisual[Y][X], Y, X, Tabuleiro[Y][X]);
	// verifica se posição selecionada pode ser aberta.
	if (TabVisual[Y][X] == _FECHADA_ && Tabuleiro[Y][X] == _VAZIA_){
		TabVisual[Y][X] = _ABERTA_;
		cont++;
		if (Y > 0)              if (TabVisual[Y - 1][X] == _FECHADA_) cont += AbreArea(Tabuleiro, TabVisual, X, Y - 1, true); // conta acima
		if (Y < (_Height_ - 1)) if (TabVisual[Y + 1][X] == _FECHADA_) cont += AbreArea(Tabuleiro, TabVisual, X, Y + 1, true); // conta abaixo
		if (X < (_Width_ - 1))  if (TabVisual[Y][X + 1] == _FECHADA_) cont += AbreArea(Tabuleiro, TabVisual, X + 1, Y, true); // conta a direita
		if (X > 0)              if (TabVisual[Y][X - 1] == _FECHADA_) cont += AbreArea(Tabuleiro, TabVisual, X - 1, Y, true); // conta a direita
	}else if (TabVisual[Y][X] == _FECHADA_ && Tabuleiro[Y][X] > 0 && Tabuleiro[Y][X] <= 8 && celulaAntVazia){
		// se a célula selecionada possui uma contagem, esta fechada e foi chamada
		// a partir de uma célula vazia e aberta, entao a abre.
		TabVisual[Y][X] = _ABERTA_;
		cont++;
	}else if (TabVisual[Y][X] == _FECHADA_ && Tabuleiro[Y][X] > 0 && Tabuleiro[Y][X] <= 8 && !celulaAntVazia) {
		TabVisual[Y][X] = _ABERTA_;
		cont++;
	}else if (TabVisual[Y][X] == _FECHADA_ && Tabuleiro[Y][X] == _BOMBA_) {
		TabVisual[Y][X] = _ABERTA_;
		cont = _BOMBA_;
		// BOMBA, finaliza o jogo
	}
	return (cont);
}
void MostraTabuleiro(int Tabuleiro[_Height_][_Width_], int TabVisual[_Height_][_Width_]) {
	int i, L, C, ic;
    int f = 1;
    int z = 1;

    // parte superior da moldura
	int c = 1;
	printf(" ");
	for (i = 0; i < _Width_; i++){
		if (c < 10){
			printf("  C%d ", c);
		}else{
			printf(" C%d ", c);
		c += 1;
		}
	}
	printf("\n");
	printf("%c", 201);
	for (i = 0; i < _Width_; i++){
		printf("%c%c%c%c%c", 205, 205, 205, 205, 205);
	}
	printf("%c\n", 187);
	int l = 1;
	for (L = 0; L < _Height_; L++){
		printf("%c", 186);
		for (C = 0; C < _Width_; C++){
			// celula esta aberta?
			
			if (TabVisual[L][C] == _ABERTA_){
				switch (Tabuleiro[L][C]){
				case _BOMBA_: printf("  %c  ", 225); break;
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:  printf("  %d  ", Tabuleiro[L][C]); break;
				case _BANDEIRA_: printf("  %c  ", 63); break;
				default: printf("  .  "); break;
				}
			}else {
				if (Tabuleiro[L][C] == _BANDEIRA_) {
					printf("  %c  ", 63);
				}else {
					printf("  %c  ", 254);
				}
			}
		}
		printf("%c L%d\n", 186, l);
		l += 1;
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
	for (L = 0; L < _Height_; L++){
		for (C = 0; C < _Width_; C++){
			Tabuleiro[L][C] = _VAZIA_;
		}
	}
	// sorteia as posições das bombas
	while (qtBombasAlocadas < _QtBombas_){
		achei = false;
		int X = rand() % (_Width_ - 1); // sorteia uma posição X (coluna)
		int Y = rand() % (_Height_ - 1); // sorteia uma posição Y (linha)
		if (Tabuleiro[Y][X] == _BOMBA_){
			achei = true;
		}if (!achei){
			Tabuleiro[Y][X] = _BOMBA_;
			qtBombasAlocadas++;
		}
	}
	// contagem de bombas para cada célula
	int contBombas = 0;
	for (L = 0; L < _Height_; L++){
		for (C = 0; C < _Width_; C++){
			if (Tabuleiro[L][C] != _BOMBA_){
				contBombas = 0;
				if (L > 0)              if (Tabuleiro[L - 1][C] == _BOMBA_) contBombas++; // conta acima
				if (L < (_Height_ - 1)) if (Tabuleiro[L + 1][C] == _BOMBA_) contBombas++; // conta abaixo
				if (C < (_Width_ - 1))  if (Tabuleiro[L][C + 1] == _BOMBA_) contBombas++; // conta a direita
				if (C > 0)              if (Tabuleiro[L][C - 1] == _BOMBA_) contBombas++; // conta a esquerda
				if (L < (_Height_ - 1) && C < (_Width_ - 1)) if (Tabuleiro[L + 1][C + 1] == _BOMBA_) contBombas++; // diag inf direita
				if (L < (_Height_ - 1) && C > 0)             if (Tabuleiro[L + 1][C - 1] == _BOMBA_) contBombas++; // diag inf esquerda
				if (L > 0 && (C < _Width_ - 1))              if (Tabuleiro[L - 1][C + 1] == _BOMBA_) contBombas++; // diag sup direita
				if (L > 0 && C > 0)							     				 if (Tabuleiro[L - 1][C - 1] == _BOMBA_) contBombas++; // diag sup esquerda
				Tabuleiro[L][C] = (contBombas == 0 ? _VAZIA_ : contBombas);
				// caso não exista nenhuma bomba ou contagem igual a zero, entao inicia a célula com o status _VAZIA_.
			}
		}
	}

}
void Bandeira(int Tabuleiro[_Height_][_Width_], int TabAuxiliar[_Height_][_Width_], int l, int c) {
	if (Tabuleiro[l][c] != _BANDEIRA_){
		TabAuxiliar[l][c] = Tabuleiro[l][c];
		Tabuleiro[l][c] = _BANDEIRA_;
		printf("Bandeira adicionada !\n");
	}else {
		Tabuleiro[l][c] = TabAuxiliar[l][c];
		TabAuxiliar[l][c] = _BANDEIRA_;
		printf("Bandeira removida !\n");
	}
}
int main() {

	int Tabuleiro[_Height_][_Width_];
	int TabVisual[_Height_][_Width_];
	int TabAuxiliar[_Height_][_Width_];
	int L, C;
	
	// inicia a semente do randomizador
	srand(time(NULL));
	
	for (L = 0; L < _Height_; L++) {
		for (C = 0; C < _Width_; C++) {
			TabVisual[L][C] = _FECHADA_;
		}
	}
	MontaTabuleiro(Tabuleiro);
	bool venceu = false;
	int pontos = 0;
	printf("Bem vindo ao desafio:\n");
	MostraTabuleiro(Tabuleiro, TabVisual);
	
	while (true) {
		int op = 0;
		
		printf("Quer mesmo continuar?\n");
		printf("1 - Jogada normal, 2 - Inserir/Remover Bandeira, 3 - Sair\n");
		scanf_s("%d", &op);
		
		// Valida a opção de jogada digitada pelo usuário
		if (op < 1 || op >3) {
			printf("Opcao invalida !\n");
			continue;
		}if(op==3) {
			printf("Medo muito sentir eu em voce");
			break;
		}
		int l = 0, c = 0;
		printf("Digite a linha desejada:\n");
		scanf_s("%d", &l);
		printf("Digite a coluna desejada:\n");
		scanf_s("%d", &c);
		
		system("cls");
		if (l < 1 || c < 1 || l > _Height_ || c > _Width_) {
		
			printf("Jogada em linha ou coluna invalidas ! L(%d) C(%d)\n", l, c);
		
		}else{
			if (op == 1){
				int celulas = AbreArea(Tabuleiro, TabVisual, c - 1, l - 1, false);
				
				if (celulas == _BOMBA_) {
					printf("Campo Minado:\n");
					MostraTabuleiro(Tabuleiro, TabVisual);
					printf("Voce perdeu! Treine mais para a proxima vez, sua pontuacao: 0\n");
					break;
				}
				pontos += celulas;
			}if(op==2){
				Bandeira(Tabuleiro, TabAuxiliar, l - 1, c - 1);				
			} 
			printf("Campo Minado:\n");
			MostraTabuleiro(Tabuleiro, TabVisual);
			printf("Pontuacao atual: %d\n", pontos);
		}

		int i, j, contbomba=0, contbandeira=0;
		venceu = false;
		
		for (i = 0; i < _Height_; i++){
	        for (j = 0; j < _Width_; j++){
	            if(TabAuxiliar[i][j] == _BOMBA_){
	            	contbomba++;
				}
	        }
	    }
		for (i = 0; i < _Height_; i++){
	        for (j = 0; j < _Width_; j++){
	            if(Tabuleiro[i][j] == _BANDEIRA_){
	            	contbandeira++;
				}
	        }
	    }	
		if(contbomba == _QtBombas_ && pontos == ((_Height_ * _Width_) - _QtBombas_)){
			venceu = true;
		}else if(pontos < ((_Height_ * _Width_) - _QtBombas_ ) && contbomba == _QtBombas_) {
			venceu = true;
		}
		if(venceu){
			for (L = 0; L < _Height_; L++) {
				for (C = 0; C < _Width_; C++) {
				TabVisual[L][C] = _ABERTA_;
				}
			}
			MostraTabuleiro(Tabuleiro, TabVisual);
			printf("O poder da forca sentir eu em voce, parabens");
			printf("\nVoce venceu");
			break;
		}else{
				printf("\nPrecisa marcar todas as bandeiras");
		}
	}
}
