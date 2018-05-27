/**
@file estado.h
Definição do estado e das funções que convertem estados em strings e vice-versa
*/

/** \brief O nº máximo de inimigos */
#define MAX_INIMIGOS		25

/** \brief O nº máximo de obstáculos */
#define MAX_OBSTACULOS		35


/**
\brief Estrutura que armazena uma posição
*/
typedef struct posicao {
	char x;
	char y;
} POSICAO;


/**
\brief Estrutura que armazena o estado do jogo
*/
typedef struct estado {
	/** \brief A posição do jogador */
	POSICAO jog;
	/** \brief O nº de inimigos */
	char num_inimigos;
	/** \brief O nº de obstáculos */
	char num_obstaculos;
	/** \brief Array com a posição dos inimigos */
	POSICAO inimigo[MAX_INIMIGOS];
	/** \brief Array com a posição dos obstáculos */
	POSICAO obstaculo[MAX_OBSTACULOS];
	
	POSICAO saida;


	char fim_jogo;

	int num_inimigos_mortos;

	int nivel;
	
} ESTADO;

/**
\brief Função que converte um estado numa string
@param e O estado
@returns A string correspondente ao estado e
*/
char *estado2str(ESTADO e);

void estado2ficheiro(ESTADO e);



