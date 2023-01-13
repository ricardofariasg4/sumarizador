#include "inicio.h"
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

void limpeza_buffer ()
{
    char c;
    while ((c = getchar()) != '\n');
}

void confere_malloc (bool alocado, char *descricao)
{
    if (alocado) return;

    perror(descricao);
    exit(1);
}

int teste (bool teste)
{
    if (teste) return 1;

    return 0;
}

char* tratamento_entrada (int argc, char **argv)
{
    char *caminho_pasta = NULL;
    int opcao;
    
    //opcao: -d valor (definido por "d:")
    opcao = getopt(argc, argv, "d:");
    
    if (opcao=='d')
        caminho_pasta = optarg;
    else
    {
        fprintf(stderr, "Uso: %s -d caminho_do_arquivo\n", argv[0]);
        exit(1);
    }

    return caminho_pasta;
}

void gerenciador_resumos (resumo *s, t_lista_bicicleta *lista_bicicleta)
{
    t_fila *fila_de_atividades;

    fila_de_atividades = busca_bicicleta(s->bicicleta, 0, lista_bicicleta);

    if (fila_de_atividades!=NULL)
    {   
        //quer dizer que a bike ta la
        inserir_na_fila(s, fila_de_atividades);
    } 
    else
    {
        fila_de_atividades = criar_fila(s->bicicleta);
        inserir_na_fila(s, fila_de_atividades);
        inserir_bicicleta(s->bicicleta, fila_de_atividades, lista_bicicleta);
    }
}

void processamento_log (char *caminho_pasta, t_lista_bicicleta *lista_bicicletas)
{
    char caminho_arquivo[LIMITE_BUFFER+1];
    resumo *log_sumarizado;
    DIR *diretorio = NULL;
    struct dirent *arquivo = NULL;
    
    diretorio = opendir(caminho_pasta);

    if (!teste(diretorio))
    {
        LIMPA_TELA
        printf("Diretorio invalido\n");
        exit(1);
    }

    arquivo = readdir(diretorio);
    while (arquivo!=NULL)
    {
        if (strstr(arquivo->d_name, ".log"))
        {
            strcpy(caminho_arquivo, caminho_pasta);
            strcat(caminho_arquivo, arquivo->d_name);
            
            log_sumarizado = sumarizar_log(caminho_arquivo);
            
            if (teste(log_sumarizado))
                gerenciador_resumos(log_sumarizado, lista_bicicletas);
            
            LIMPA_TELA
            printf("Executando...\n");
        }  
        
        arquivo = readdir(diretorio); 
    }

    closedir(diretorio);
}

int validar_operacao (int operacao, t_lista_bicicleta *lista_bicicleta)
{
    if (operacao>0 && operacao<=lista_bicicleta->qtd_bicicletas)
        return 1;
    
    LIMPA_TELA
    printf("Bicicleta nao encontrada!\n");
    printf("Pressione Enter para voltar ao menu...\n");
    PAUSE
    return 0;
}

void menu_interacao (struct_sumario_geral *sumario_geral, t_fila *fila_de_atividades, t_lista_bicicleta *lista_bicicletas)
{
    int menu_opt=-1, sub_menu_opt=-1;
    
    LIMPA_TELA
    printf
    (
        "Resumo Final:\n"
        "Total de atividades = %d\n"
        "Total percorrido em km = %.2lf\n"
        "Pedal mais longo em km = %.2lf\n"
        "Pedal mais curto em km = %.2lf\n"
        "Distancia media em km = %.2lf\n",
        sumario_geral->quantidade_de_atividades,
        sumario_geral->total_percorrido/1000,
        sumario_geral->pedal_mais_longo/1000,
        sumario_geral->pedal_mais_curto/1000,
        sumario_geral->distancia_media/1000
    );
    printf("Pressione Enter para ir ao menu...\n");
    PAUSE

    while (menu_opt!=0)
    {
        LIMPA_TELA
        
        printf
        (
            "1 - Bicicletas Encontradas\n"
            "2 - Digite o numero da bicicleta para ver o resumo desejado\n"
            "3 - Atividades Ordenadas por data\n"
            "4 - Atividades Ordenadas por distancia\n"
            "5 - Atividades Ordenadas por subida acumulada\n"
            "6 - Digite o numero da bicicleta para ver o histograma desejado\n"
            "0 - Sair do programa\n"
            "Entrada: "
        );

        scanf("%d", &menu_opt);
        limpeza_buffer();

        switch (menu_opt)
        {
            case 1: 
                LIMPA_TELA
                exibir_lista_bicicletas(lista_bicicletas);
                printf("Pressione Enter para voltar ao menu...\n");
                PAUSE
             break;

            case 2: 
                LIMPA_TELA
                printf("Entre com o numero da bicicleta:\n");
                scanf("%d", &sub_menu_opt);
                limpeza_buffer();
                if (validar_operacao(sub_menu_opt, lista_bicicletas))
                {
                    fila_de_atividades = busca_bicicleta(NULL, sub_menu_opt, lista_bicicletas);
                    
                    if (fila_de_atividades) 
                        exibir_fila(fila_de_atividades);
                    
                    printf("Pressione Enter para voltar ao menu...\n");
                    PAUSE    
                }
            break;

            case 3:
                LIMPA_TELA
                exibicao_expandida(lista_bicicletas, POR_DATA);
                printf("Pressione Enter para voltar ao menu...\n");
                PAUSE
            break;

            case 4:
                LIMPA_TELA
                exibicao_expandida(lista_bicicletas, POR_DISTANCIA);
                printf("Pressione Enter para voltar ao menu...\n");
                PAUSE
            break;

            case 5:
                LIMPA_TELA
                exibicao_expandida(lista_bicicletas, POR_SUBIDA_ACUMULADA);
                printf("Pressione Enter para voltar ao menu...\n");
                PAUSE
            break;

            case 6:
                LIMPA_TELA
                printf("Entre com o numero da bicicleta para gerar o Histograma:\n");
                scanf("%d", &sub_menu_opt);
                limpeza_buffer();
                if (validar_operacao(sub_menu_opt, lista_bicicletas))
                {
                    fila_de_atividades = busca_bicicleta(NULL, sub_menu_opt, lista_bicicletas);
                    
                    if (fila_de_atividades) 
                        exibir_fila(fila_de_atividades);

                    exibir_histograma(fila_de_atividades);
                    printf("Pressione Enter para voltar ao menu...\n");
                    PAUSE
                }
            break;

            case 0: break;

            default:
                LIMPA_TELA
                printf("A opcao solicitada nao existe!\n");
                PAUSE
            break;
        }
    }
    LIMPA_TELA
}

void limpar_ram (t_lista_bicicleta *lista_bicicleta, struct_sumario_geral *sumario_geral)
{
    nodo_bicicleta *nb_auxiliar;
    t_nodo *nodo_auxiliar;

    free(sumario_geral);
    
    for (nb_auxiliar = lista_bicicleta->primeiro_elemento; nb_auxiliar!=NULL; nb_auxiliar = nb_auxiliar->proximo_elemento)
    {
        for (nodo_auxiliar=nb_auxiliar->fila->primeiro_elemento; nodo_auxiliar!=NULL; nodo_auxiliar=nodo_auxiliar->proximo_elemento)
            limpa_memoria_sumarizador(nodo_auxiliar->elemento);
        
        destruir_fila(nb_auxiliar->fila);
    }

    destruir_lista(lista_bicicleta);
}