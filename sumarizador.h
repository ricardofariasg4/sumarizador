#ifndef SUMARIZADOR_H
#define SUMARIZADOR_H

#include <stdio.h>
#include <stdbool.h>

typedef unsigned char t_tempo;

typedef struct _t_data {
    t_tempo dia;
    t_tempo mes;
} t_data;

typedef struct _timestamp {
    t_tempo hora;
    t_tempo minuto;
    t_tempo segundo;
} timestamp;

typedef struct _contadores {
    int contador_a,
        contador_b,
        contador_c,
        contador_d,
        contador_e,
        contador_f;
} contadores;

typedef struct _resumo {
    char bicicleta[25];
    int tamanho_log;
    t_data *data;
    timestamp **timestamp; //vetor de ponteiros para timestamps
    double *altitude;
    double distancia;
    double *velocidade_media;    
    double velocidade_maxima;
    double *heart_rate_medio;
    double heart_rate_maximo;
    double *cadencia_media;
    double subida_acumulada;
    contadores *c;
} resumo;

//Associa um dia e um mês literal ao formato dia/mês
t_data* processar_data (char *linha_atual);

//tps = timestamp para segundos
int tps (timestamp *t);

//Verifica se t2 é de fato sequência de t1, retorna 1 se sim e 0 caso contrário
int eh_sequencia_timestamp (int t1, int t2);

//Retorno: 1 se t2>t1, 0 se t1>t2 e 2 se t1=t2
int eh_maior_timestamp (int t1, int t2);

//Torna o timestamp manipulável, deixando-o de acordo com sua struct
timestamp* processar_timestamp (char *buffer_char, resumo *s);

//Faz o calculo das medias necessarias de acordo com o resumo
void calcular_medias (resumo *s);

//Calcula a subida acumulada
void calcular_altimetria (resumo *s);

//Processa o topo de cada log de atividades
void processar_topo (FILE *arquivo, resumo *s, char *buffer_char);

//Verifica os limites do arquivo para realizar a correta alocação de memória
void pre_processamento (FILE *arquivo, resumo *s, char *buffer_char, contadores *c);

//Inicializa as estruturas restantes, que não foram inicializadas no pre_processamento
void inicializar_resumo (resumo *s);

//Função principal na sumarização
resumo* sumarizar_log (char *nome_arquivo);

void limpa_memoria_sumarizador (resumo *s);

#endif


