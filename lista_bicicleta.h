#ifndef LISTA_BICICLETA_H
#define LISTA_BICICLETA_H

#include "fila.h"

//Constantes para serem usadas na função exibicao_expandida()
#define POR_DATA 0
#define POR_DISTANCIA 1
#define POR_SUBIDA_ACUMULADA 2

typedef struct _nodo_bicicleta {
    int posicao;
    t_fila *fila;
    char *bicicleta;
    struct _nodo_bicicleta *proximo_elemento;
} nodo_bicicleta;

typedef struct _t_lista_bicicleta {
    nodo_bicicleta *primeiro_elemento;
    int qtd_bicicletas;
} t_lista_bicicleta;

typedef struct _struct_sumario_geral {
    int quantidade_de_atividades;
    double total_percorrido;
    double pedal_mais_longo;
    double pedal_mais_curto;
    double distancia_media;
} struct_sumario_geral;

t_lista_bicicleta* criar_lista_bicicleta ();
void inserir_bicicleta (char *bicicleta, t_fila *fila_vinculada, t_lista_bicicleta *lista_bicicleta);
t_fila* busca_bicicleta (char *nome_bicicleta, int index, t_lista_bicicleta *lista_bicicleta);
int lista_vazia_bicicleta (t_lista_bicicleta *lista_bicicleta);
void exibir_lista_bicicletas (t_lista_bicicleta *lista_bicicleta);
void exibicao_expandida (t_lista_bicicleta *lista_bicicleta, int modo);
void destruir_lista (t_lista_bicicleta *lista_bicicleta);
struct_sumario_geral* resumo_final (t_lista_bicicleta *lista_bicicleta);

#endif