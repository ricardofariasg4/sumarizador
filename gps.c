#include "lista_bicicleta.h"
#include "fila.h"
#include "inicio.h"

int main (int argc, char **argv)
{ 
    t_lista_bicicleta *lista_bicicletas = NULL;
    t_fila *fila_de_atividades = NULL;
    struct_sumario_geral *sumario_geral = NULL;
    char *caminho_pasta;

    lista_bicicletas = criar_lista_bicicleta();

    caminho_pasta = tratamento_entrada(argc, argv);
    
    processamento_log(caminho_pasta, lista_bicicletas);
    
    sumario_geral = resumo_final(lista_bicicletas);

    menu_interacao(sumario_geral, fila_de_atividades, lista_bicicletas);

    limpar_ram(lista_bicicletas, sumario_geral);
    
    return 0;
}