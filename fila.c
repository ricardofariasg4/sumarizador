#include "inicio.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

//Retorna 1 se data_a > data_b, 2 caso contrário e 0 se forem iguais
static int compara_prioridade (t_data *data_a, t_data *data_b)
{
    if (data_a->mes > data_b->mes)
        return 1;
    
    if (data_b->mes > data_a->mes)
        return 2;

    if (data_a->dia > data_b->dia)
        return 1;

    if (data_b->dia > data_a->dia)
        return 2;
    
    return 0;
}

static t_nodo* criar_nodo (resumo *elemento)
{
    t_nodo *nodo = (t_nodo *) malloc(sizeof(t_nodo));
    confere_malloc(nodo, "tipo_erro: malloc | funcao: criar_nodo | arquivo: fila.c |");

    nodo->elemento = elemento;
    nodo->proximo_elemento = NULL;
    nodo->elemento_anterior = NULL;

    return nodo;
}

t_fila* criar_fila (char *nome_fila)
{
    t_fila *fila = (t_fila *) malloc(sizeof(t_fila));
    confere_malloc(fila, "tipo_erro: malloc | funcao: criar_fila | arquivo: fila.c |");
    
    fila->nome_fila = nome_fila;
    fila->primeiro_elemento = NULL;
    fila->ultimo_elemento = NULL;
    fila->comprimento_fila = 0;

    return fila;
}

int fila_vazia (t_fila *fila)
{
    return fila->comprimento_fila==0 ? 1 : 0;
}

void inserir_na_fila (resumo *elemento, t_fila *fila)
{
    t_nodo *nodo = criar_nodo(elemento);
    t_nodo *nodo_auxiliar;
    int prioridade_auxiliar;

    if (fila_vazia(fila)==1)
    {
        fila->primeiro_elemento = nodo;
        fila->ultimo_elemento = nodo;
    }
    else
    {
        //Percorrer até a posição correta de inserção
        nodo_auxiliar=fila->ultimo_elemento;
        while (nodo_auxiliar!=NULL)
        {
            prioridade_auxiliar = compara_prioridade(nodo_auxiliar->elemento->data, nodo->elemento->data);
            
            //Nodo que chegou com data mais velha que o nodo da fila
            if (prioridade_auxiliar==2) 
                break;

            //Nodo da fila com a mesma data do novo nodo
            if (prioridade_auxiliar==0) 
                break;
                
            nodo_auxiliar=nodo_auxiliar->elemento_anterior;
        }

        /* 
            Inserção na cabeça da fila:
            Significa que percorremos até o ponteiro "elemento_anterior" do primeiro elemento
            da fila, ou seja, é uma inserção na cabeça. 
        */
        if (nodo_auxiliar == NULL)
        {
            nodo->proximo_elemento = fila->primeiro_elemento;
            fila->primeiro_elemento->elemento_anterior = nodo;
            fila->primeiro_elemento = nodo;        
        }

        /* 
            Inserção no meio da fila: 
            Quando o ponteiro de ida e volta de onde paramos são válidos. 
        */
        else if (nodo_auxiliar->proximo_elemento && nodo_auxiliar->proximo_elemento->elemento_anterior)
        {
            nodo->proximo_elemento = nodo_auxiliar->proximo_elemento;
            nodo->elemento_anterior = nodo_auxiliar;
            nodo->proximo_elemento->elemento_anterior = nodo;
            nodo_auxiliar->proximo_elemento = nodo;
        }

        //A opção restante só pode ser a cauda
        else
        {
            nodo_auxiliar->proximo_elemento = nodo;
            nodo->elemento_anterior = nodo_auxiliar;
            fila->ultimo_elemento = nodo;
        }
    }
    
    nodo_auxiliar = NULL;
    fila->comprimento_fila += 1;
}

void exibir_fila (t_fila *fila)
{
    t_nodo *nodo_auxiliar;
    nodo_auxiliar=fila->primeiro_elemento;
    
    printf("Bicicleta: %s\n", nodo_auxiliar->elemento->bicicleta);
    while (nodo_auxiliar!=NULL)
    {
        printf("data:%d/%d cad:%.0lf  hr:%.0lf  hr_m:%.0lf  s:%.2lf  s_m:%.2lf  dist:%.2lf  elev:%.2lf\n", 
        nodo_auxiliar->elemento->data->dia,
        nodo_auxiliar->elemento->data->mes,
        nodo_auxiliar->elemento->cadencia_media[0],
        nodo_auxiliar->elemento->heart_rate_medio[0],
        nodo_auxiliar->elemento->heart_rate_maximo,
        nodo_auxiliar->elemento->velocidade_media[0]*3.6,
        nodo_auxiliar->elemento->velocidade_maxima*3.6,
        nodo_auxiliar->elemento->distancia/1000,
        nodo_auxiliar->elemento->subida_acumulada);
        
        nodo_auxiliar=nodo_auxiliar->proximo_elemento;
    }

    printf("Total de atividades = %d\n", fila->comprimento_fila);
}

static int compara_double (const void *a, const void *b)
{
    if (((aux_ordenacao *)a)->buffer_double  == ((aux_ordenacao *)b)->buffer_double)
        return 0;
    else
    {
        if (((aux_ordenacao *)a)->buffer_double > ((aux_ordenacao *)b)->buffer_double)
            return 1;

        return -1;
    }
}

static int compara_data (const void *a, const void *b)
{
    if (((aux_ordenacao *)a)->data.mes > ((aux_ordenacao *)b)->data.mes)
        return 1;
    
    if (((aux_ordenacao *)b)->data.mes > ((aux_ordenacao *)a)->data.mes)
        return -1;

    if (((aux_ordenacao *)a)->data.dia > ((aux_ordenacao *)b)->data.dia)
        return 1;
    
    if (((aux_ordenacao *)b)->data.dia > ((aux_ordenacao *)a)->data.dia)
        return -1;
    
    return 0;
}

void exibicao_por_data (t_fila *fila)
{
    aux_ordenacao *vetor_auxiliar;
    t_nodo *nodo_auxiliar;

    vetor_auxiliar = (aux_ordenacao *) malloc(fila->comprimento_fila * sizeof(aux_ordenacao));
    confere_malloc(vetor_auxiliar, "tipo_erro: malloc | funcao: exibicao_por_data | arquivo: fila.c |");

    nodo_auxiliar = fila->primeiro_elemento;
    for (int i=0; i<fila->comprimento_fila; i++)
    {
        vetor_auxiliar[i].data.dia = nodo_auxiliar->elemento->data->dia;
        vetor_auxiliar[i].data.mes = nodo_auxiliar->elemento->data->mes;
        vetor_auxiliar[i].resumo = nodo_auxiliar->elemento;
        nodo_auxiliar = nodo_auxiliar->proximo_elemento;
    }

    qsort(vetor_auxiliar, fila->comprimento_fila, sizeof(aux_ordenacao), compara_data);

    nodo_auxiliar = fila->primeiro_elemento;
    for (int i=0; i<fila->comprimento_fila; i++)
    {
        nodo_auxiliar->elemento = vetor_auxiliar[i].resumo;
        nodo_auxiliar = nodo_auxiliar->proximo_elemento;
    }

    free(vetor_auxiliar);
    
    exibir_fila(fila);
}

void exibicao_por_distancia (t_fila *fila)
{
    aux_ordenacao *vetor_auxiliar;
    t_nodo *nodo_auxiliar;

    vetor_auxiliar = (aux_ordenacao *) malloc(fila->comprimento_fila * sizeof(aux_ordenacao));
    confere_malloc(vetor_auxiliar, "tipo_erro: malloc | funcao: exibicao_por_distancia | arquivo: fila.c |");

    nodo_auxiliar = fila->primeiro_elemento;
    for (int i=0; i<fila->comprimento_fila; i++)
    {
        vetor_auxiliar[i].buffer_double = nodo_auxiliar->elemento->distancia;
        vetor_auxiliar[i].resumo = nodo_auxiliar->elemento;
        nodo_auxiliar = nodo_auxiliar->proximo_elemento;
    }

    qsort(vetor_auxiliar, fila->comprimento_fila, sizeof(aux_ordenacao), compara_double);

    nodo_auxiliar = fila->primeiro_elemento;
    for (int i=0; i<fila->comprimento_fila; i++)
    {
        nodo_auxiliar->elemento = vetor_auxiliar[i].resumo;
        nodo_auxiliar = nodo_auxiliar->proximo_elemento;
    }

    free(vetor_auxiliar);
    
    exibir_fila(fila);
}

void exibicao_por_subida_acumulada (t_fila *fila)
{
    aux_ordenacao *vetor_auxiliar;
    t_nodo *nodo_auxiliar;

    vetor_auxiliar = (aux_ordenacao *) malloc(fila->comprimento_fila * sizeof(aux_ordenacao));
    confere_malloc(vetor_auxiliar, "tipo_erro: malloc | funcao: exibicao_por_subida_acumulada | arquivo: fila.c |");

    nodo_auxiliar = fila->primeiro_elemento;
    for (int i=0; i<fila->comprimento_fila; i++)
    {
        vetor_auxiliar[i].buffer_double = nodo_auxiliar->elemento->subida_acumulada;
        vetor_auxiliar[i].resumo = nodo_auxiliar->elemento;
        nodo_auxiliar = nodo_auxiliar->proximo_elemento;
    }

    qsort(vetor_auxiliar, fila->comprimento_fila, sizeof(aux_ordenacao), compara_double);

    nodo_auxiliar = fila->primeiro_elemento;
    for (int i=0; i<fila->comprimento_fila; i++)
    {
        nodo_auxiliar->elemento = vetor_auxiliar[i].resumo;
        nodo_auxiliar = nodo_auxiliar->proximo_elemento;
    }

    free(vetor_auxiliar);
    
    exibir_fila(fila);
}

static int numero_para_digito (double a, int decremento)
{   
    if (a-decremento <= -1)
        return 1;

    return 1 + numero_para_digito(a, decremento*10);
}

void exibir_histograma (t_fila *fila)
{
    //1 passo: determinar o maior e o menor elemento do rol
    t_nodo *nodo_auxiliar=NULL;
    double i=0.0, j=0.0, maior=0.0, menor=0.0, amplitude=0.0, chao=0.0, teto=0.0;
    int k, l;

    nodo_auxiliar = fila->primeiro_elemento;
    maior = nodo_auxiliar->elemento->distancia;
    menor = nodo_auxiliar->elemento->distancia;

    //Etapa para encontrar o maior e o menor para o cálculo da amplitude
    for (i=1; i<fila->comprimento_fila; i++)
    {
        if (nodo_auxiliar->elemento->distancia > maior)
            maior = nodo_auxiliar->elemento->distancia;
        
        if (nodo_auxiliar->elemento->distancia < menor)
            menor = nodo_auxiliar->elemento->distancia;

        nodo_auxiliar = nodo_auxiliar->proximo_elemento;
    }
    
    amplitude = (maior-menor)/10;

    //Abaixo, segue o código para a exibição do Histograma
    LIMPA_TELA
    printf("Histograma da bicicleta %s:\n", fila->nome_fila);
    for (i=menor; i<maior; i+=amplitude)
    {
        chao = (i/1000);
        teto = (i+amplitude)/1000;

        k = numero_para_digito(chao, 10) + numero_para_digito(teto, 10);

        printf("%.0lf - %.0lf", chao, teto);
        for (l=0; l<(11-(k+3)); l++)
            printf(" ");
        printf("|");
            
        //[INICIO] - Processamento das estrelas
        nodo_auxiliar = fila->primeiro_elemento;
        for (j=1; j<fila->comprimento_fila; j++)
        {
            if (nodo_auxiliar->elemento->distancia>i && nodo_auxiliar->elemento->distancia<(i+amplitude))
                printf("*");
            
            nodo_auxiliar = nodo_auxiliar->proximo_elemento;
        }
        PULA
        //[FIM] - Processamento das estrelas
    }
    printf("           0123456789#0123456789#0123456789#\n");
    printf("Distancia  |\t\tQuantidade\n");
}

void destruir_fila (t_fila *fila)
{
    t_nodo *iterador, *nodo_auxiliar;

    iterador = fila->primeiro_elemento;
    while (iterador)
    {
        nodo_auxiliar = iterador;
        iterador = iterador->proximo_elemento;
        free(nodo_auxiliar);
    }
}

