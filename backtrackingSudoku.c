#include <stdio.h>
#include <time.h>

#define TAM 9 //tamanho da matriz

//-------------------- inicializa a matriz -------------------------

void inicializaGrade(int grade[TAM][TAM]){
    for (int linha = 0; linha < TAM; linha++) {
        for (int coluna = 0; coluna < TAM; coluna++) {
            scanf("%d", &grade[linha][coluna]);
        }
    }
}

//------------------ procura um lugar vazio --------------------------

int LugarVazio(int grade[TAM][TAM], int *linha, int *coluna){
	for ( ;(*linha) < TAM; (*linha)++){
		for (;(*coluna) < TAM; (*coluna)++)
			if (grade[(*linha)][(*coluna)] == 0)
				return 1;
		(*coluna)=0;
	}	
	return 0;
}


//-------------- verifica se o número ja está na linha ----------------------

int RepetidoLinha(int grade[TAM][TAM], int linha, int num){
	for (int coluna = 0; coluna < TAM; coluna++)
		if (grade[linha][coluna] == num) return 1;
	return 0;
}

//-------------- verifica se o número ja está na coluna ----------------------

int RepetidoColuna(int grade[TAM][TAM], int coluna, int num){
	for (int linha = 0; linha < TAM; linha++)
		if (grade[linha][coluna] == num) return 1;	
	return 0;
}

//------------- verifica se o número ja está no grupo 3x3 ----------------------

int RepetidoGrupo(int grade[TAM][TAM], int LinhaInicial,int ColunaInicial, int num){
	for (int linha = 0; linha < 3; linha++)
		for (int coluna = 0; coluna < 3; coluna++)
			//se sim,retorna 1
			if (grade[linha + LinhaInicial][coluna + ColunaInicial] == num)
				return 1;
	//else retorna 0
	return 0;
}

//----------- verifica a validade do numero: se já está na linha/coluna/grupo -------------

int Valido(int grade[TAM][TAM], int linha,int coluna, int num){
	return !RepetidoLinha(grade, linha, num)
		&& !RepetidoColuna(grade, coluna, num)
		&& !RepetidoGrupo(grade, linha - linha % 3,coluna - coluna % 3, num);
}

//----------------------- resolve o Sudoku --------------------------------

int resolveSudoku(int grade[TAM][TAM],int ordem[],int linha,int coluna){
	if (!LugarVazio(grade, &linha, &coluna)) //se todos os lugares estão cheios, chegamos no resultado
		return 1;
		
	for (int num = 0; num < TAM; num++){
		if (Valido(grade, linha, coluna, ordem[num])){
			grade[linha][coluna] = ordem[num];
			if(resolveSudoku(grade,ordem,linha,coluna+1)){
				return 1;
			}
			grade[linha][coluna] = 0;
		}
	}
	return 0; 	//se nenhum digito for valido retrocede
}

//-------------------- printa a matriz -------------------------

void printaGrade(int grade[TAM][TAM]){
    for (int linha = 0; linha < TAM; linha++) {
            if (linha % 3 == 0) {
                printf("-------------------------\n");
            }
            for (int col = 0; col < TAM; col++) {
                if (col % 3 == 0) {
                    printf("| ");
                }
                if (grade[linha][col] != 0) {
                    printf("%d ", grade[linha][col]);
                } else {
                    printf("x ");
                }
            }
            printf("|\n");
        }
        printf("-------------------------\n");
}

//------------------------- main -------------------------------

int main(){
    int grade[TAM][TAM];
	int ordem1[] = {1,2,3,4,5,6,7,8,9};

    inicializaGrade(grade);
    resolveSudoku(grade, ordem1, 0, 0);
    printaGrade(grade);

    return 0;
}
