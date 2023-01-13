#include "lista_bicicleta.h"
#include "sumarizador.h" //Para uso da função teste em sumarizador
#include "inicio.h"
#include <stdlib.h>
#include <string.h>

t_lista_bicicleta* criar_lista_bicicleta ()
{
    t_lista_bicicleta *lista_bicicleta = (t_lista_bicicleta *) malloc(sizeof(t_lista_bicicleta));
    confere_malloc(lista_bicicleta, "tipo_erro: malloc | funcao: criar_lista_bicicleta | arquivo: lista_bicicleta.c |");

    lista_bicicleta->primeiro_elemento = NULL;
    lista_bicicleta->qtd_bicicletas = 0;

    return lista_bicicleta;
}

int lista_vazia_bicicleta (t_lista_bicicleta *lista_bicicleta)
{
    return lista_bicicleta->qtd_bicicletas==0 ? 1 : 0;
}

static nodo_bicicleta* criar_nodo_bicicleta (char *bicicleta, t_fila *fila_vinculada)
{
    nodo_bicicleta *nb = (nodo_bicicleta *) malloc(sizeof(nodo_bicicleta));
    confere_malloc(nb, "tipo_erro: malloc | funcao: criar_nodo_bicicleta | arquivo: lista_bicicleta.c |");

    nb->bicicleta = bicicleta;
    nb->fila = fila_vinculada;
    nb->proximo_elemento = NULL;

    return nb;
}

void inserir_bicicleta (char *bicicleta, t_fila *fila_vinculada, t_lista_bicicleta *lista_bicicleta)
{   
    nodo_bicicleta *nb = criar_nodo_bicicleta(bicicleta, fila_vinculada);
    nodo_bicicleta *nb_auxiliar;

    if (lista_vazia_bicicleta(lista_bicicleta))
        lista_bicicleta->primeiro_elemento = nb;
    else
    {
        nb_auxiliar = lista_bicicleta->primeiro_elemento;
        while (nb_auxiliar->proximo_elemento!=NULL)
            nb_auxiliar = nb_auxiliar->proximo_elemento;

        nb_auxiliar->proximo_elemento = nb;
    }

    lista_bicicleta->qtd_bicicletas += 1;
    nb->posicao = lista_bicicleta->qtd_bicicletas;
}

t_fila* busca_bicicleta (char *nome_bicicleta, int posicao, t_lista_bicicleta *lista_bicicleta)
{
    if (lista_vazia_bicicleta(lista_bicicleta))
        return NULL;
    
    if (posicao>0)
    {
        nodo_bicicleta *nb_auxiliar = lista_bicicleta->primeiro_elemento;

        while (nb_auxiliar)
        {
            if (nb_auxiliar->posicao==posicao)
                return nb_auxiliar->fila;    
                
            nb_auxiliar = nb_auxiliar->proximo_elemento;
        }
    }
    else
    {
        if (nome_bicicleta)
        {
            nodo_bicicleta *nb_auxiliar = lista_bicicleta->primeiro_elemento;

            while (nb_auxiliar!=NULL)
            {
                if (strstr(nome_bicicleta, nb_auxiliar->bicicleta))
                    break;
                
                nb_auxiliar = nb_auxiliar->proximo_elemento;
            }
            
            if (nb_auxiliar!=NULL)
                return nb_auxiliar->fila;
        }
    }
    
    return NULL;
}

void exibir_lista_bicicletas (t_lista_bicicleta *lista_bicicleta)
{
    if (lista_vazia_bicicleta(lista_bicicleta))
    {
        printf("Nenhuma bicicleta para exibir...\n");
        return;
    }

    int contador=1;
    nodo_bicicleta *nb_auxiliar = lista_bicicleta->primeiro_elemento;

    while (nb_auxiliar!=NULL)
    {
        printf("[%d] = %s\n", contador, nb_auxiliar->bicicleta);    
        nb_auxiliar = nb_auxiliar->proximo_elemento;
        contador++;
    }
}

void exibicao_expandida (t_lista_bicicleta *lista_bicicleta, int modo)
{
    if (lista_vazia_bicicleta(lista_bicicleta))
    {
        printf("Nenhuma bicicleta para exibir...\n");
        return;
    }

    int contador=1;
    nodo_bicicleta *nb_auxiliar = lista_bicicleta->primeiro_elemento;

    switch (modo)
    {
        case POR_DATA:
            while (nb_auxiliar!=NULL)
            {
                exibicao_por_data(nb_auxiliar->fila);    
                PULA
                nb_auxiliar = nb_auxiliar->proximo_elemento;
                contador++;
            }
        break;

        case POR_DISTANCIA:
            while (nb_auxiliar!=NULL)
            {
                exibicao_por_distancia(nb_auxiliar->fila);    
                PULA
                nb_auxiliar = nb_auxiliar->proximo_elemento;
                contador++;
            }
        break;

        case POR_SUBIDA_ACUMULADA:
            while (nb_auxiliar!=NULL)
            {
                exibicao_por_subida_acumulada(nb_auxiliar->fila);
                PULA
                nb_auxiliar = nb_auxiliar->proximo_elemento;
                contador++;
            }
        break;
    }
}

struct_sumario_geral* resumo_final (t_lista_bicicleta *lista_bicicleta)
{
    struct_sumario_geral *sumario_geral = (struct_sumario_geral *) malloc(sizeof(struct_sumario_geral));    
    confere_malloc(sumario_geral, "tipo_erro: malloc | funcao: resumo_final | arquivo: lista_bicicleta.c |");

    //Inicialização para evitar seg fault
    sumario_geral->distancia_media = 0;
    sumario_geral->pedal_mais_curto = 0;
    sumario_geral->pedal_mais_longo = 0;
    sumario_geral->quantidade_de_atividades = 0;
    sumario_geral->total_percorrido = 0;

    //Quantidade de Atividades, Total Percorrido em km, Pedal mais longo em km, Pedal mais curto em km e Distância Média em km.
    nodo_bicicleta *nb_auxiliar;
    t_nodo *nodo_auxiliar;
    
    for (nb_auxiliar = lista_bicicleta->primeiro_elemento; nb_auxiliar!=NULL; nb_auxiliar = nb_auxiliar->proximo_elemento)
    {
        sumario_geral->quantidade_de_atividades+=nb_auxiliar->fila->comprimento_fila;
        sumario_geral->pedal_mais_longo = nb_auxiliar->fila->primeiro_elemento->elemento->distancia;
        sumario_geral->pedal_mais_curto = nb_auxiliar->fila->primeiro_elemento->elemento->distancia;
        for (nodo_auxiliar=nb_auxiliar->fila->primeiro_elemento; nodo_auxiliar!=NULL; nodo_auxiliar=nodo_auxiliar->proximo_elemento)
        {
            sumario_geral->total_percorrido+=nodo_auxiliar->elemento->distancia;

            if (nodo_auxiliar->elemento->distancia > sumario_geral->pedal_mais_longo)
                sumario_geral->pedal_mais_longo = nodo_auxiliar->elemento->distancia;

            if (nodo_auxiliar->elemento->distancia < sumario_geral->pedal_mais_curto)
                sumario_geral->pedal_mais_curto = nodo_auxiliar->elemento->distancia;                        
        }
    }

    sumario_geral->distancia_media = (sumario_geral->total_percorrido/sumario_geral->quantidade_de_atividades);

    return sumario_geral;
}

void destruir_lista (t_lista_bicicleta *lista_bicicleta)
{
    nodo_bicicleta *iterador, *nb_auxiliar;

    iterador = lista_bicicleta->primeiro_elemento;
    while (iterador)
    {
        nb_auxiliar = iterador;
        iterador = iterador->proximo_elemento;
        free(nb_auxiliar);
    }
}