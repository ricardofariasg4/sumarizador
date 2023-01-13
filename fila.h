#ifndef FILA_H
#define FILA_H

#include "sumarizador.h"

typedef struct tipo_nodo {
    resumo *elemento;
    struct tipo_nodo *proximo_elemento;
    struct tipo_nodo *elemento_anterior;
} t_nodo;

typedef struct tipo_fila {
    char *nome_fila;
    int comprimento_fila;
    t_nodo *primeiro_elemento;
    t_nodo *ultimo_elemento;
} t_fila;

typedef struct _aux_ordenacao {
    resumo *resumo;
    double buffer_double;
    t_data data;
} aux_ordenacao;

t_fila* criar_fila (char *nome_fila);
void inserir_na_fila (resumo *elemento, t_fila *fila);
int fila_vazia (t_fila *fila);
void exibir_fila (t_fila *fila);
void destruir_fila (t_fila *fila);
void exibicao_por_distancia (t_fila *fila);
void exibicao_por_subida_acumulada (t_fila *fila);
void exibicao_por_data (t_fila *fila);
void exibir_histograma (t_fila *fila);

#endif