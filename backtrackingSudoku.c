#include <stdio.h>
#include <time.h>

#define TAM 9 //tamanho da matriz
int operationCount = 0;

//-------------------- inicializa a matriz -------------------------

void inicializaGrade(int grade[TAM][TAM]){
    for (int linha = 0; linha < TAM; linha++) {
        for (int coluna = 0; coluna < TAM; coluna++) {
            scanf("%d", &grade[linha][coluna]);
        }
    }
}

//------------------ procura um lugar vazio --------------------------

int lugarVazio(int grade[TAM][TAM], int *linha, int *coluna){
	for ( ;(*linha) < TAM; (*linha)++){
		for (;(*coluna) < TAM; (*coluna)++)
			if (grade[(*linha)][(*coluna)] == 0)
				return 1;
		(*coluna)=0;
	}	
	return 0;
}


//-------------- verifica se o número ja está na linha ----------------------

int repetidoLinha(int grade[TAM][TAM], int linha, int num){
	for (int coluna = 0; coluna < TAM; coluna++)
		if (grade[linha][coluna] == num) return 1;
	return 0;
}

//-------------- verifica se o número ja está na coluna ----------------------

int repetidoColuna(int grade[TAM][TAM], int coluna, int num){
	for (int linha = 0; linha < TAM; linha++)
		if (grade[linha][coluna] == num) return 1;	
	return 0;
}

//------------- verifica se o número ja está no grupo 3x3 ----------------------

int repetidoGrupo(int grade[TAM][TAM], int LinhaInicial,int ColunaInicial, int num){
	for (int linha = 0; linha < 3; linha++)
		for (int coluna = 0; coluna < 3; coluna++)
			if (grade[linha + LinhaInicial][coluna + ColunaInicial] == num)
				return 1;
	return 0;
}

//----------- verifica a validade do numero: se já está na linha/coluna/grupo -------------

int valido(int grade[TAM][TAM], int linha,int coluna, int num){
	return !repetidoLinha(grade, linha, num)
		&& !repetidoColuna(grade, coluna, num)
		&& !repetidoGrupo(grade, linha - linha % 3,coluna - coluna % 3, num);
}

//----------------------- resolve o Sudoku --------------------------------

int resolveSudoku(int grade[TAM][TAM],int ordem[],int linha,int coluna){
	if (!lugarVazio(grade, &linha, &coluna)) //se todos os lugares estão cheios, chegamos no resultado
		return 1;
		
	for (int num = 0; num < TAM; num++){
		operationCount++;
		if (valido(grade, linha, coluna, ordem[num])){
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
	clock_t start, end;
    double executionTime;
    
    start = clock(); // inicia a contagem do tempo

    int grade[TAM][TAM];
	int ordem1[] = {1,2,3,4,5,6,7,8,9};

    inicializaGrade(grade);
    if (resolveSudoku(grade, ordem1, 0, 0)){
		end = clock(); // Finaliza a contagem do tempo
        executionTime = ((double) (end - start)) / CLOCKS_PER_SEC * 1000; // Tempo de execução em milissegundos
        printaGrade(grade);
        printf("\nNúmero de operações: %d\n", operationCount);
        printf("Tempo de execução: %.2f ms\n", executionTime);
	} else {
        printf("Não é possível resolver o Sudoku.\n");
    }

    return 0;
}
