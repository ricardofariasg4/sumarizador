#include "sumarizador.h"
#include "inicio.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

t_data* processar_data (char *linha_atual)
{
    enum meses_enum {jan, feb, mar, apr, may, june, july, aug, sept, oct, nov, dec};
    char *meses[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    int mes_atual, i, j;
    char dia[3];

    t_data *data = (t_data *) malloc(sizeof(t_data));
    confere_malloc(data, "tipo_erro: malloc | funcao: processar_data | arquivo: sumarizador.c |");

    for (mes_atual=jan; mes_atual<=dec; mes_atual++)
        if (strstr(linha_atual, meses[mes_atual]))
            break;

    data->mes = mes_atual+1; //Se for jan=0 então é mês 1

    dia[2]='\0';
    //Captura a data de trás pra frente colocando no vetor dia nas posições 1 e dps 0 pois a 2 tem o \0
    for (i=1, j=strlen(linha_atual)-1; i>=0; i--, j--)
        dia[i]=linha_atual[j];
    
    data->dia = atoi(dia);

    return data;
}

int tps (timestamp *t)
{
    return ((t->hora*3600)+(t->minuto*60)+t->segundo);
}

int eh_sequencia_timestamp (int t1, int t2)
{
    return ((t2-t1)==1) ? 1 : 0;
}

int eh_maior_timestamp (int t1, int t2)
{
    if (t2>t1) return 1;

    if (t1>t2) return 0;

    return 2;
}

timestamp* processar_timestamp (char *buffer_char, resumo *s)
{
    //Ex de buffer_char = 09:05:39
    int tamanho=strlen(buffer_char)-1;
    char hora[3], minuto[3], segundo[3];

    timestamp* ts = (timestamp *) malloc(sizeof(timestamp));
    confere_malloc(ts, "tipo_erro: malloc | funcao: processar_timestamp | arquivo: sumarizador.c |");
    
    segundo[2]='\0';
    segundo[1] = buffer_char[tamanho];
    segundo[0] = buffer_char[tamanho-1];

    minuto[2]='\0';
    minuto[1] = buffer_char[tamanho-3];
    minuto[0] = buffer_char[tamanho-4];

    hora[2]='\0';
    hora[1] = buffer_char[tamanho-6];
    hora[0] = buffer_char[tamanho-7];

    ts->hora = (t_tempo) atoi(hora);
    ts->minuto = (t_tempo) atoi(minuto);
    ts->segundo = (t_tempo) atoi(segundo);

    return ts;
}

void calcular_medias (resumo *s)
{
    double cadencia_media=0.0;
    double heart_rate_medio=0.0;
    double velocidade_media=0.0;

    int i, 
        peso_speed=0, soma_pesos_speed=0,
        peso_cadence=0, soma_pesos_cadence=0,
        peso_heart_rate=0, soma_pesos_heart_rate=0;

    for (i=0; i<s->tamanho_log-1; i++)
    {
        if ( s->velocidade_media[i] > 0 )
        {
            peso_speed = ( tps(s->timestamp[i+1]) - tps(s->timestamp[i]) );
            soma_pesos_speed += peso_speed;
            velocidade_media += ( s->velocidade_media[i] * peso_speed );
        }

        if ( s->cadencia_media[i] > 0 )
        {
            peso_cadence = ( tps(s->timestamp[i+1]) - tps(s->timestamp[i]) );
            soma_pesos_cadence += peso_cadence;
            cadencia_media += ( s->cadencia_media[i] * peso_cadence );
        }

        if ( s->heart_rate_medio[i] > 0 )
        {
            peso_heart_rate = ( tps(s->timestamp[i+1]) - tps(s->timestamp[i]) );
            soma_pesos_heart_rate += peso_heart_rate;
            heart_rate_medio += ( s->heart_rate_medio[i] * peso_heart_rate );
        }
    }

    velocidade_media /= soma_pesos_speed;
    cadencia_media /= soma_pesos_cadence;
    heart_rate_medio /= soma_pesos_heart_rate;
    
    if (s->c->contador_b > 0)
        s->velocidade_media[0]=velocidade_media;
    else
        s->velocidade_media[0]=0;
    
    if (s->c->contador_c > 0)
        s->heart_rate_medio[0]=heart_rate_medio;
    else
        s->heart_rate_medio[0]=0;

    if (s->c->contador_d > 0)
        s->cadencia_media[0]=cadencia_media;
    else
        s->cadencia_media[0]=0;
}

void calcular_altimetria (resumo *s)
{
    for (int i=1; i<s->tamanho_log; i++)
        if (eh_maior_timestamp(tps(s->timestamp[i-1]), tps(s->timestamp[i])) && s->altitude[i-1]<s->altitude[i])
            s->subida_acumulada+=(s->altitude[i]-s->altitude[i-1]);
}

void processar_topo (FILE *arquivo, resumo *s, char *buffer_char)
{
    //Remove da stream o campo "Gear:"
    fscanf(arquivo, "%s", buffer_char); 
    
    //Remove o espaço após o "Gear:" andando um char para frente
    fseek(arquivo, sizeof(char), SEEK_CUR); 

    //Captura o modelo da bicicleta
    fscanf(arquivo, "%[^\n]\n", buffer_char); 
    strcpy(s->bicicleta, buffer_char); 

    //Captura a data e converte para um formato conveniente
    fscanf(arquivo, "%[^,]", buffer_char);
    s->data = processar_data(buffer_char);
}

void pre_processamento (FILE *arquivo, resumo *s, char *buffer_char, contadores *c)
{
    c->contador_a=0;
    while (fgets(buffer_char, LIMITE_BUFFER, arquivo))
        if (buffer_char[0]=='\n')
            c->contador_a+=1;
    c->contador_a-=1;
    
    s->altitude = (double *) malloc(c->contador_a * sizeof(double));
    confere_malloc(s->altitude, "tipo_erro: malloc_1 | funcao: pre_processamento | arquivo: sumarizador.c |");

    s->cadencia_media = (double *) malloc(c->contador_a * sizeof(double));
    confere_malloc(s->cadencia_media, "tipo_erro: malloc_2 | funcao: pre_processamento | arquivo: sumarizador.c |");

    s->velocidade_media = (double *) malloc(c->contador_a * sizeof(double));
    confere_malloc(s->velocidade_media, "tipo_erro: malloc_3 | funcao: pre_processamento | arquivo: sumarizador.c |");

    s->heart_rate_medio = (double *) malloc(c->contador_a * sizeof(double));
    confere_malloc(s->heart_rate_medio, "tipo_erro: malloc_4 | funcao: pre_processamento | arquivo: sumarizador.c |");
    
    s->timestamp = (timestamp **) malloc(c->contador_a * sizeof(timestamp*));
    confere_malloc(s->timestamp, "tipo_erro: malloc_5 | funcao: pre_processamento | arquivo: sumarizador.c |");

    s->tamanho_log = c->contador_a;

    c->contador_a=0; //reseta o c.contador_a
}

void inicializar_resumo (resumo *s) 
{
    s->velocidade_maxima = 0.0;
    s->heart_rate_maximo = 0.0;
    s->subida_acumulada = 0.0;
}

//Essa função poderia devolver o ponteiro para um resumo, e então este ser inserido em uma lista encadeada
resumo* sumarizar_log (char *nome_arquivo)
{
    int campo_sensor;
    contadores c = {0, 0, 0, 0, 0, 0};
    double buffer_double;
    char buffer_char[LIMITE_BUFFER+1];

    enum t_campos_log {altitude, cadence, distance, heart_rate, speed, timestamp};
    char *campos_log[] = {"altitude:", "cadence:", "distance:", "heart_rate:", "speed:", "timestamp:"};

    //abre o arquivo teste.log e testa
    FILE *arquivo = NULL;
    arquivo = fopen(nome_arquivo, "r");
    
    if (!teste(arquivo))
        return NULL;

    resumo *s = (resumo *) malloc(sizeof(resumo));
    confere_malloc(s, "tipo_erro: malloc | funcao: sumarizar_log | arquivo: sumarizador.c |");
    s->c = &c; //para apurar os valores de cadence
    
    //captura o nome e a data disponível no cabeçalho dos arquivos de log
    processar_topo(arquivo, s, buffer_char);

    //realiza uma pré leitura para alocar memória de maneira adequada
    pre_processamento(arquivo, s, buffer_char, s->c);

    inicializar_resumo(s);

    //retorna ao inicio do arquivo
    rewind(arquivo); 

    while (!feof(arquivo))
    {
        fscanf(arquivo, "%s", buffer_char);
        
        //if para garantir que só será comparado campo com campo
        if (strcmp(&buffer_char[strlen(buffer_char)-1], ":")==0)
        {
            for (campo_sensor=altitude; campo_sensor<=timestamp; campo_sensor++)
                if (strcmp(buffer_char, campos_log[campo_sensor])==0)
                    break;
        }
        else
            campo_sensor=timestamp+1;
                
        switch (campo_sensor)
        {
            case altitude:
                fscanf(arquivo, "%lf", &buffer_double);
                s->altitude[s->c->contador_a] = buffer_double;
                s->c->contador_a++;
            break;

            case distance:
                //Basta pegar a última distancia
                fscanf(arquivo, "%lf", &buffer_double); 
                s->distancia = buffer_double;
            break;

            case speed:
                fscanf(arquivo, "%lf", &buffer_double);
                s->velocidade_media[s->c->contador_b] = buffer_double;
                if (buffer_double > s->velocidade_maxima)
                    s->velocidade_maxima = buffer_double;
                s->c->contador_b++;
            break;

            case heart_rate:
                fscanf(arquivo, "%lf", &buffer_double);
                s->heart_rate_medio[s->c->contador_c] = buffer_double;
                if (buffer_double > s->heart_rate_maximo)
                    s->heart_rate_maximo = buffer_double;
                s->c->contador_c++;
            break;

            case cadence:
                fscanf(arquivo, "%lf", &buffer_double);
                s->cadencia_media[s->c->contador_d] = buffer_double;
                s->c->contador_d++;
            break;

            case timestamp:
                //O primeiro fscanf só remove LIXO da stream
                fscanf(arquivo, "%s", buffer_char);
                fscanf(arquivo, "%s", buffer_char);
                s->timestamp[s->c->contador_e] = processar_timestamp(buffer_char, s);
                s->c->contador_e++;
            break;
        }
    }

    calcular_altimetria(s);

    calcular_medias(s);

    fclose(arquivo);

    return s;
}

void limpa_memoria_sumarizador (resumo *s)
{
    int i;
    
    s->c = NULL;
    free(s->data);
    free(s->altitude);
    free(s->velocidade_media);
    free(s->heart_rate_medio);
    free(s->cadencia_media);

    for (i=0; i<s->tamanho_log; i++)
        free(s->timestamp[i]);
    
    free(s->timestamp);
}