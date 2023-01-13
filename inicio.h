#ifndef INICIO_H
#define INICIO_H

#include "sumarizador.h"
#include "fila.h"
#include "lista_bicicleta.h"

#define LIMITE_BUFFER 100
#define PULA printf("\n");
#define PAUSE getchar();
#define LIMPA_TELA system("clear");

void limpeza_buffer ();
void confere_malloc (bool alocado, char *descricao);
int teste (bool teste);
char* tratamento_entrada (int argc, char **argv);
void gerenciador_resumos (resumo *s, t_lista_bicicleta *lista_bicicleta);
void processamento_log (char *caminho_pasta, t_lista_bicicleta *lista_bicicletas);
int validar_operacao (int operacao, t_lista_bicicleta *lista_bicicleta);
void menu_interacao (struct_sumario_geral *sumario_geral, t_fila *fila_de_atividades, t_lista_bicicleta *lista_bicicletas);
void limpar_ram (t_lista_bicicleta *lista_bicicleta, struct_sumario_geral *sumario_geral);

#endif