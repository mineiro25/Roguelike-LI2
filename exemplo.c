/**
@file exemplo.c
*/

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include "cgi.h"
#include "estado.h"


/** 
\brief Macro que define o comprimento máximo da string que imprime o link 
*/
#define MAX_BUFFER              10240

/** 
\brief Macro que define o tamanho 
*/
#define TAM                     10

/** 
\brief Macro que define a escala 
*/
#define ESCALA                  40



/**
\brief Estrutura que imprime um inimio na posição (x,y)
@param e O estado
*/
void Print_enemy (ESTADO e, int x, int y);



/**
\brief Estrutura que faz imprimir a passagem de nivel na posição (x,y)
@param e O estado
*/
void Print_door (ESTADO e){
                int x,y;
                x = e.saida.x;
                y = e.saida.y;
                IMAGEM(x, y, ESCALA, "cookie.png");
}

/**
\brief Estrutura que verifica se uma determinada posição (x,y) é válida
*/
int valide_position(int x, int y) {
        return x >= 0 && y >= 0 && x < TAM && y < TAM;
}


/**
\brief Estrutura que imprime uma casa na posição (x,y)
*/
void Print_houset(int x, int y) {
        char *cor[] = {"#696969", "#D3D3D3"};
        int idx = (x + y) % 2;
        QUADRADOT(x, y,ESCALA, cor[idx]);
}



/**
\brief Estrutura que imprime uma casa na posição (x,y)
*/
void Print_house(int x, int y) {
        char *cor[] = {"#696969", "#D3D3D3"};
        int idx = (x + y) % 2;
        QUADRADO(x, y,ESCALA, cor[idx]);
}


/**
\brief Estrutura que verifica se uma determinada posição é igual às coordenadas (x,y)
@param p Posição
*/
int equal_position(POSICAO p, int x, int y){
        return p.x == x && p.y == y;
}


/**
\brief Estrutura que verifica se o jogador se encontra numa determinada posição (x,y)
@param e O estado
*/
int have_player(ESTADO e, int x, int y){
        return equal_position(e.jog, x , y);
}


/**
\brief Estrutura que verifica se um inimigo se encontra numa dada posição (x,y)
@param e O estado
*/
int have_enemy(ESTADO e, int x, int y){
        int i;
        for(i=0; i<e.num_inimigos; i++)
                if (equal_position(e.inimigo[i], x, y))
                        return 1;
        return 0;
}


/**
\brief Estrutura que verifica se existe um obstáculo em (x,y)
@param e O estado
*/
int have_obstacle(ESTADO e, int x, int y){
        int i;
        for(i=0; i<e.num_obstaculos; i++)
                if (equal_position(e.obstaculo[i], x, y))
                        return 1;
        return 0;
}


/**
\brief Estrutura que verifica se uma dada posição (x,y) está ocupada
@param e O estado
*/
int occupied_position(ESTADO e, int x, int y){
        return have_player(e, x, y) || have_enemy(e, x, y) || have_obstacle(e, x, y);
}


/**
\brief Estrutura que inicializa o inimigo
@param e O estado 
*/
ESTADO initiate_enemy(ESTADO e){
        int x, y;
        do {
                x = random() % TAM;
                y = random() % TAM;
        } while(occupied_position(e, x, y));

        e.inimigo[(int)e.num_inimigos].x = x;
        e.inimigo[(int)e.num_inimigos].y = y;

        e.num_inimigos++;
        return e;

}


/**
\brief Estrutura que inicializa os inimigos
@param e O estado
*/
ESTADO initiate_enemys(ESTADO e, int num){
        int i;
        for (i=0; i < num; i++)
                e = initiate_enemy(e);
        return e;
}


/**
\brief Estrutura que inicializa um obstáculo
@param e O estado
*/
ESTADO initiate_obstacle(ESTADO e){
        int x, y;
        do {
                x = random() % TAM;
                y = random() % TAM;
        } while(occupied_position(e, x, y));

        e.obstaculo[(int)e.num_obstaculos].x = x;
        e.obstaculo[(int)e.num_obstaculos].y = y;

        e.num_obstaculos++;
        return e;

}



/**
\brief Estrutura que imprime a saída
@param e O estado
@param e.saida.x Coordenada X da porta gerada aleatoriamente
@param e.saida.y Coordenada Y da porta gerada aleatoriamente
*/
ESTADO initiate_exit(ESTADO e){
        int x, y;
        do {
                x = random() % TAM;
                y = random() % TAM;
        } while(occupied_position(e, x, y));

        e.saida.x = x;
        e.saida.y = y;

        return e;

}



/**
\brief Estrutura que inicializa os obstáculos
@param num Número de obstáculos
@param e O estado
*/
ESTADO initiate_obstacles(ESTADO e, int num){
        int i;
        for (i=0; i < num; i++)
                e = initiate_obstacle(e);
        return e;
}


/**
\brief Estrutura que inicializa o jogo com o jogador, os inimigos e a saida 
*/
ESTADO initiate(int x, int y) {
        ESTADO e = {{0}};
        e.jog.x = 5;
        e.jog.y = 9;
        e.num_inimigos_mortos=y;
        e.nivel = x;
        e = initiate_enemys(e, 20);

        e = initiate_obstacles(e, 30);
        e = initiate_exit(e);
        if (x == 0 && y == 0){
                e.fim_jogo = 'm';
        }
        else
                e.fim_jogo = 'g'; //para continuar o jogo

        return e;
}



/**
\brief Estrutura que calcula o score do jogador
@param e O estado
*/
int score_calculator (ESTADO e){
        int resultado;

        resultado = 20 * (int)e.num_inimigos_mortos + 100 * (int)e.nivel;

        return resultado;
}



/**
\brief Estrutura que imprime o score do jogador
@param e O estado
*/
void Print_score (ESTADO e){
        printf("<text fill=%s font-size=%d font-family=%s x=%d y=%d>Score: %d</text>" ,"#FFFFF",35,"Verdana",40,450, score_calculator(e));

}

int calculateSizeIntArray(int array []){
    int result = 0;

    int s = (sizeof(array)/sizeof(int));

    for (int i=0; i< s; i++){
        if(array[i] == -1){
            result++;
        }
    }

    return (sizeof(array)/sizeof(int)) - result;
}


int* insert_value_ordenated(int a[], int size, int key){
  int* result = malloc(sizeof(int)*size);

    a[size] = key;
    int size_a = calculateSizeIntArray(a);
    int h1 = -1, h2 = -1, h3 = -1;

    for(int i=0;i<size_a;i++){
        if(a[i] > h1){
            h3 = h2; h2 = h1; h1 = a[i];
        }
        else if (a[i] > h2){
            h3 = h2; h2 = a[i];
        }
        else if  (a[i] > h3){
            h3 = a[i];
        }
    }

    result[0] = h1;
    result[1] = h2;
    result[2] = h3;

  return result;
}


/**
\brief Estrutura que guarda o score do jogador
@param score_calculator Score do jogador
*/
void Save_score(int score_calculator) {

        FILE* High_Scores = fopen("High_Scores.txt", "r");

        int file_scores_int[4] = {-1,-1,-1,-1};

        if(High_Scores != NULL){
            int aux;
            int i=0;
            fscanf (High_Scores, "%d", &aux);
            while (!feof (High_Scores)){
                file_scores_int[i]=aux;
                fscanf (High_Scores, "%d", &aux);
                i++;
            }

        }



        int file_scores_int_size = calculateSizeIntArray(&file_scores_int);
        int* top_three = insert_value_ordenated(file_scores_int, file_scores_int_size, score_calculator);
        High_Scores = fopen("High_Scores.txt", "wa+");
        int top_three_size = calculateSizeIntArray(top_three);
        for(int x = 0; x< top_three_size; x++){
            fprintf(High_Scores, "%d\n", top_three[x]);
        }

        fclose(High_Scores);
}

/**
\brief Estrutura que faz com que os inimigos possam matar o jogador numa dada posição (x,y)
@param e O estado
*/
ESTADO kill_player(ESTADO e, int x, int y){

        int i, j;

        int a, b, c, d;

        for (i=0; i < e.num_inimigos - 1; i++){
                a = e.jog.x - e.inimigo[i].x; //coordenadas de um inimigo
            b = e.jog.y - e.inimigo[i].y;

            for(j = 0; j < e.num_inimigos; j++){

                    c = e.jog.x - e.inimigo[j].x;//coordenadas do inimigo seguinte
                    d = e.jog.y - e.inimigo[j].y;

                        if( a <= 1 && a >= -1 && b <= 1 && b >= -1 && //testa se um inimigo está ao lado do jogador
                                c <= 1 && c >= -1 && d <= 1 && d >= -1 && //testa se  o inimigo seguinte está ao lado do jogador
                                i != j ) {  //testa se estão a ser testados inimigos diferentes

                                //Guarda e ordena os scores no ficheiro
                                int score = score_calculator(e);
                                Save_score (score);

                                //VAI ATIVAR A MUDANCA DE "ESTADO" PARA O PAINEL DE GAME OVER
                                e.fim_jogo = 'x';
                        }
                }
        }

        return e;

}


/**
\brief Estrutura que permite ao jogador matar os inimigos numa dada posição (x,y)
@param e O estado
*/
ESTADO kill_enemy(ESTADO e, int x, int y) {
        int i;
        for(i=0; i < e.num_inimigos; i++)
                if (e.inimigo[i].x == x && e.inimigo[i].y == y)
                        break;
        for(i=0;i < e.num_inimigos - 1;i++)
                e.inimigo[i] = e.inimigo[i +1];

        e.num_inimigos--;

        e.num_inimigos_mortos++;

        return e;
}



/**
\brief Estrutura que dá o movimento aos inimigos
@param i Número do inimigo
@param e O estado
*/
ESTADO move_monster(ESTADO e, int i){

        int a,b;

        a = (random() % TAM);
        b = (random() % TAM);

        if(occupied_position(e, a, b) || (a == e.saida.x && b == e.saida.y) || (a == e.jog.x && b == e.jog.y))
                return (e);
        if(!valide_position(a,b))
                return (e);
        e.inimigo[i].x = a;
        e.inimigo[i].y = b;

        return (e);
}
/**
\brief Estrutura que imprime o melhor score
*/
void Print_highscores(FILE *Scores){
        Scores = fopen("/tmp/Scores.txt", "r");

        if(Scores == NULL) {
      perror("Error opening file");
      exit(1);
        } else{
                size_t bufsize = 1000;
                char *buffer = (char* )malloc(bufsize * sizeof(char));
                ssize_t read;

                while ((read= getline(&buffer, &bufsize, Scores)) != -1) {
                        printf("<text fill=%s font-size=%d font-family=%s x=%d y=%d>%zd\n</text>" ,"#FFFFFF",20,"Verdana",70,30,read);
                }

        fclose(Scores);
        }
}

/**
\brief Estrutura que permite o movimento dos inimigos
@param e O estado
*/
ESTADO move_monsters(ESTADO e){
        int i;
        for (i=0; i < e.num_inimigos; i++){
                e = move_monster(e,i);
        }
        return e;
}


/**
\brief Estrutura que imprime movimento em todo o jogo
@param e O estado
*/
void Print_movement(ESTADO e, int dx, int dy) {

        int x = e.jog.x + dx;
        int y = e.jog.y + dy;

        char link[MAX_BUFFER];
        if(!valide_position(x, y))
                return;

        if(occupied_position(e, x, y)) {
                if(have_enemy(e,x,y)){

                        sprintf(link, "http://localhost/cgi-bin/exemplo?%d,%d", x, y);
                        ABRIR_LINK(link);
                        Print_enemy(e,x,y);
                        FECHAR_LINK;
                }
                else
                        return;
        }

        else {


        sprintf(link, "http://localhost/cgi-bin/exemplo?%d,%d", x, y);

        ABRIR_LINK(link);
        Print_houset(x, y);
        FECHAR_LINK;

        }
}


/**
\brief Estrutura que imprime os movimentos
@param e O estado
*/
void Print_movements(ESTADO e) {
        int dx, dy;

        for(dx = -1; dx <= 1; dx++)
                for(dy = -1; dy <= 1; dy++)
                        Print_movement(e,  dx, dy);

}


/**
\brief Estrutura que imprime o jogador
@param e O estado
*/
void Print_player(ESTADO e) {
        IMAGEM(e.jog.x, e.jog.y, ESCALA, "coockiemonster.png");
        Print_movements(e);
}



/**
\brief Estrutura que converte o ficheiro num estado
*/
ESTADO ficheiro2estado() {
        ESTADO e;
        FILE* f = fopen("estado25", "rb");
        fread(&e, sizeof(ESTADO), 1, f);
        fclose(f);
        return e;
}


/**
\brief Estrutura que lê o estado do jogo
*/
ESTADO ler_estado(char *args) {
        int x = 0,y = 0;

        if(strlen(args) == 0)
                return initiate(0,0);
        else {
                ESTADO e = ficheiro2estado();
                int a, b;

                sscanf(args, "%d,%d", &a, &b);

                if (a == 11 && b == 11){
                        e.fim_jogo='g';
                        return e;
                }

/*                if (a == 100 && b == 100){
                        e.fim_jogo = 'h';
                        return e;
                  }
*/
                if(have_enemy(e, a, b)) {
                        e = kill_enemy(e, a, b);
                }
                else {
                        e.jog.x = a;
                        e.jog.y = b;
                }
                e = move_monsters(e);
                e = kill_player(e,x,y);


                return e;
        }
}


/**
\brief Estrutura que imprime o inimigo no mapa
@param e O estado
*/
void Print_enemy (ESTADO e, int x, int y){
         IMAGEM(x,y, ESCALA, "oscarthegrouch.png");
}


/**
\brief Estrutura que imprime os inimigos no mapa
@param e O estado
*/
void Print_enemys(ESTADO e) {
        int i;
        for(i = 0; i < e.num_inimigos; i++)
                Print_enemy(e,e.inimigo[i].x, e.inimigo[i].y);


}


/**
\brief Estrutura que imprime os obstáculos no mapa
@param e O estado
*/
void Print_obstacles(ESTADO e) {
        int i;
        for(i = 0; i < e.num_obstaculos; i++)
                IMAGEM(e.obstaculo[i].x, e.obstaculo[i].y, ESCALA, "trashcan.png");
}



/**
\brief Estrutura  
*/
int main() {

        int x, y;
        srand(time(NULL));
        ESTADO e = ler_estado(getenv("QUERY_STRING"));

        if (strcmp(getenv("QUERY_STRING"), "hs") == 0) {
            char link[100];
            sprintf(link, "http://localhost/cgi-bin/exemplo?");
            COMECAR_HTML;
            ABRIR_SVG(600, 600);
            ABRIR_LINK(link);
            printf("<rect x=%d y=%d width=%d height=%d fill=%s />\n",0,0,400,400,"#D3D3D3");
            FECHAR_LINK;
            printf("<text fill=%s font-size=%d font-family=%s x=%d y=%d>HIGH SCORES</text>\n","#FF6600",30,"Verdana",70,100);
            FILE *High_Scores;
            Print_highscores(High_Scores);
            FECHAR_SVG;

        }

        else {

            if(e.fim_jogo == 'm'){

            COMECAR_HTML;
            ABRIR_SVG(600, 600);

            printf("<rect x=%d y=%d width=%d height=%d fill=%s />\n",0,0,400,400,"#D3D3D3");
            printf("<text fill=%s font-size=%d font-family=%s x=%d y=%d>ROGUE ONE</text>\n","#FF6600",40,"Verdana",70,200);
        	char link[MAX_BUFFER];
            sprintf(link, "http://localhost/cgi-bin/exemplo?%d,%d", 11, 11);
        	ABRIR_LINK(link);
            IMAGEM(0, 2, 100, "button-play.png"); //IMAGEM PLAY, CARREGA SE NESTE BOTAO E O JOGO INICIA
            FECHAR_LINK;
            sprintf(link, "http://localhost/cgi-bin/exemplo?hs");
       		ABRIR_LINK(link);
            IMAGEM(3, 2, 100, "leaderboard-512.png"); //IMAGEM SCOREBOARD, CARREGA NESTE BOTAO E APARECE A TABELA DE SCORES
            FECHAR_LINK;
            FECHAR_SVG;

            estado2ficheiro(e);

            return 0;

            }

            if (e.saida.x == e.jog.x && e.saida.y == e.jog.y){
                    int incnivel = e.nivel+1;
                    e = initiate(incnivel, e.num_inimigos_mortos);

            }

    /*      COMECAR_HTML;
            ABRIR_SVG(600, 600);

            if (e.fim_jogo == 'h'){ // Ir para o menu de highscores
                    char link[MAX_BUFFER];
                    ABRIR_LINK(link);
                    printf("<rect x=%d y=%d width=%d height=%d fill=%s />\n",0,0,400,400,"#D3D3D3");
                    printf("<text fill=%s font-size=%d font-family=%s x=%d y=%d>HIGHSCORE</text>\n","#FF6600",40,"Verdana",70,20);
                    FECHAR_LINK;
            FECHAR_SVG;

            estado2ficheiro(e);

            return 0;
            }

    */       COMECAR_HTML;
            ABRIR_SVG(600, 600);

            if(e.fim_jogo == 'x'){

                    ABRIR_LINK(RESTART); //Ira retornar ao jogo, basta clickar em qualquer espaco do menu

                    // Mete o ecra a negro e imprime a mensagem de game over
            		printf("<rect x=%d y=%d width=%d height=%d fill=%s />\n",0,0,400,400,"#000000");
            		printf("<text fill=%s font-size=%d font-family=%s x=%d y=%d>GAME OVER</text>\n","#FFFFFF",40,"Verdana",70,200);
            		printf("<text fill=%s font-size=%d font-family=%s x=%d y=%d>Obtained score: %d</text>" ,"#FFFFFF",15,"Verdana",75,220, score_calculator(e));
                    //o printf de cima indica o score final obtido
                    FECHAR_LINK;
            }

            else {
                    for(y = 0; y < 10; y++)
                            for(x = 0; x < 10; x++)
                                    Print_house(x, y);

            Print_enemys(e);
            Print_obstacles(e);
            Print_door(e);
            Print_player(e);
            Print_score(e);
            }
            FECHAR_SVG;

            estado2ficheiro(e);

    }

        return 0;
}