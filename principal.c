#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define NULL 0
#define TAM_LUGARES 10*10

#define VALOR_DIVINA_COMEDIA    10.00
#define VALOR_REI_LEAO          12.00
#define VALOR_PINOQUIO          12.00

//Horario peças
#define DIVINA_COMEDIA_1    "14:00"
#define DIVINA_COMEDIA_2    "17:00"
#define DIVINA_COMEDIA_3    "20:00"
#define DIVINA_COMEDIA_4    "23:00"

#define REI_LEAO_1    "10:00"
#define REI_LEAO_2    "13:00"
#define REI_LEAO_3    "16:00"
#define REI_LEAO_4    "19:00"

#define PINOQUIO_1    "10:00"
#define PINOQUIO_2    "13:00"
#define PINOQUIO_3    "15:00"
#define PINOQUIO_4    "18:00"


typedef int bool;

typedef enum
{
    DIVINA_COMEDIA = 1,
    REI_LEAO,
    PINOQUIO
}
pecaEnum;

typedef enum
{
    DISPONIVEL =0,
    OCUPADO    
}
assento;

typedef enum
{
    domingo =0,
    segunda,
    terca,
    quarta,
    quinta,
    sexta,
    sabado
}
dias_semana;

typedef struct venda
{
    int peca;
    int dia;
    int hora;
    int lugar;
    float valor;
}
Venda;

typedef struct controle_caixa
{
    int qtde;
    float valor;
    //char data[14];
}
Caixa;
/*
peca
dias
horas
*/
typedef struct st_horaPeca
{
    char hora[12];
    int lugares[TAM_LUGARES];

    //st_horaPeca * prox;
}
HoraPeca;

typedef struct st_dias_peca
{
    HoraPeca hora[4];
}
DiasPeca;

typedef struct st_peca
{
    int pecaId;
    int dia;
    char hora[12];    
    DiasPeca peca[sabado+1];
}
Peca;

Caixa ctrl_caixa = {0,0};
Peca ctrl_sala[3];
Peca divina_comedia;
Peca pinoquio;
Peca rei_leao;

//Prototippos de funções
bool retirar_lugar(Venda * peca);
bool verifica_disponibilidade(Venda * peca);
bool verifica_sala(Venda * peca);
void inicia_sala();
void zera_caixa();
void atualiza_caixa(float valor);
void grava_datahora(char * retorno, int tamanho);
bool verifica_terca();
void retorna_data(struct tm * data);
int fechamento();
float vendaIngresso100(int peca);
float vendaMeiaEntrada(int peca);
float vendaInteira(int peca);
int tipoEntrada(Venda* peca);
int escolhaPeca();
int iniciarVenda();
void limpar_tela();
void emitirComprovante(Venda * peca);
void pausa();
void inicia_pinoquio();
void inicia_reileao();
void inicia_divina_comedia();
Peca* getPeca(int peca);
char * getDiaSemanda(int dia);

int 
main()
{
    bool sair = FALSE;
    int opcao;
        
    inicia_sala();
    // loop principal da aplicacao
    do
    {
        limpar_tela();

        printf("Principal:\r\n");
        printf("1-Venda entrada:\r\n");
        printf("2-Fechamento caixa:\r\n");
        printf("0-Sair:\r\n");
		
		scanf("%d", &opcao);
		
        switch (opcao)
        {
            case 0:
                sair = TRUE;
                break;
            case 1:
                iniciarVenda();
                break;
            case 2:
                fechamento();
                sair = TRUE;
                break;        
            default:
                continue;
        }
    } 
    while (sair == FALSE);
    
    
    pausa();
    return 0;
}

int iniciarVenda()
{
    escolhaPeca();    
}

int escolhaPeca()
{
    int opcao;
    Venda peca = {0,0,0};
    
    limpar_tela();

    printf("Escolha a peça\r\n");
    printf("1-Divina comedia:\r\n");
    printf("2-Rei Leao:\r\n");    
    printf("3-Pinoquio:\r\n");
    printf("0-Cancelar:\r\n");

    scanf("%d", &opcao);

    switch (opcao)
    {
        case 0:
            return 0;
        case 1:
            peca.peca = DIVINA_COMEDIA;
            if(escolhaDia(&peca) == TRUE)
                tipoEntrada(&peca);
            break;
        case 2:
            peca.peca = REI_LEAO;
            if(escolhaDia(&peca) == TRUE)
                tipoEntrada(&peca);
            break;        
        case 3:
            peca.peca = PINOQUIO;
            if(escolhaDia(&peca) == TRUE)
                tipoEntrada(&peca);
            break;
        
        default:
            break;
    }
    
    return 1;
}

int escolhaDia(Venda* peca)
{
    int escolha=-1;
    int retorno = 0;

    limpar_tela();
    printf("1-Domingo\r\n");
    printf("2-Segunda\r\n");
    printf("3-Terca\r\n");
    printf("4-Quarta\r\n");
    printf("5-Quinta\r\n");
    printf("6-Sexta\r\n");
    printf("7-Sabado\r\n");
    printf("0-Voltar\r\n");

    printf("Escolha o dia:\r\n");
    scanf("%d", &escolha);
    
    switch (escolha-1)
    {
        case domingo:
            peca->dia = domingo;
            retorno = escolhoHorario(peca);
            break;
        case segunda:
            peca->dia = segunda;
            retorno = escolhoHorario(peca);
            break;
        case terca:
            peca->dia = terca;
            retorno = escolhoHorario(peca);
            break;
        case quarta:
            peca->dia = quarta;
            retorno = escolhoHorario(peca);
            break;
        case quinta:
            peca->dia = quinta;
            retorno = escolhoHorario(peca);
            break;
        case sexta:
            peca->dia = sexta;
            retorno = escolhoHorario(peca);
            break;
        case sabado:
            peca->dia = sabado;
            retorno = escolhoHorario(peca);
            break;
        case -1:
            retorno = 0;
        default:
            break;
    }

    return retorno;
}

int escolhoHorario(Venda* peca)
{
    int retorno = 0;
    int tecla = 0;

    limpar_tela();

    switch (peca->peca)
    {
        case 0: 
            retorno = 0;           
            break;
        case DIVINA_COMEDIA:
            printf("1-%s\r\n", DIVINA_COMEDIA_1);
            printf("2-%s\r\n", DIVINA_COMEDIA_2);
            printf("3-%s\r\n", DIVINA_COMEDIA_3);
            printf("4-%s\r\n", DIVINA_COMEDIA_4);
            printf("0-Voltar\r\n");
            retorno = 1;
            break;
        case REI_LEAO:
            printf("1-%s\r\n", REI_LEAO_1);
            printf("2-%s\r\n", REI_LEAO_2);
            printf("3-%s\r\n", REI_LEAO_3);
            printf("4-%s\r\n", REI_LEAO_4);
            printf("0-Voltar\r\n");
            retorno = 1;
            break;        
        case PINOQUIO:
            printf("1-%s\r\n", PINOQUIO_1);
            printf("2-%s\r\n", PINOQUIO_2);
            printf("3-%s\r\n", PINOQUIO_3);
            printf("4-%s\r\n", PINOQUIO_4);            
            printf("0-Voltar\r\n");
            retorno = 1;
            break;
        
        default:
            retorno = 0;
            break;
    }
    
    printf("Escolha o horario:\r\n");
    scanf("%d", &tecla);   
    peca->hora = tecla - 1; 
    return retorno;
}

void emitirComprovante(Venda * peca)
{
    char data[41];

    memset(data, 0, sizeof(data));
    grava_datahora(data, sizeof(data));
    limpar_tela();
    printf("          Comprovante de compra          \r\n");
    printf("Data: %s \r\n%s\r\n", data, getDiaSemanda(peca->dia));

    switch (peca->peca)
    {
        case 0:            
            return;
        case DIVINA_COMEDIA:
            printf("Divina comedia\r\n");
            printf("Valor R$ %.2f\r\n", peca->valor);
            printf("Poltrona: %d\r\n", peca->lugar);
            break;
        case REI_LEAO:
            printf("Rei Leão\r\n");
            printf("Valor R$ %.2f\r\n", peca->valor);
            printf("Poltrona: %d\r\n", peca->lugar);
            break;        
        case PINOQUIO:
            printf("Pinoquio\r\n");
            printf("Valor R$ %.2f\r\n", peca->valor);
            printf("Poltrona: %d\r\n", peca->lugar);
            break;
        
        default:
            break;
    }
    pausa();
}

int tipoEntrada(Venda* peca)
{
    int opcao;
    float valor;

    limpar_tela();

    printf("Escolha entrada\r\n");
    printf("1-Inteira:\r\n");
    printf("2-Meia entrada:\r\n");
    if(verifica_terca())
        printf("3-Ingresso 100:\r\n");
    printf("0-Cancelar:\r\n");

    scanf("%d", &opcao);

    switch (opcao)
    {
        case 0:
            
            return 0;
        case 1:
            if(verifica_sala(peca) == TRUE)
            {            
                peca->valor = vendaInteira(peca->peca);
                emitirComprovante(peca);
                retirar_lugar(peca);
            }
            break;
        case 2:
            if(verifica_sala(peca) == TRUE)
            {
                peca->valor = vendaMeiaEntrada(peca->peca);
                emitirComprovante(peca);
                retirar_lugar(peca);
            }
            break;        
        case 3:
            if(verifica_sala(peca) == TRUE)
            {
                peca->valor = vendaIngresso100(peca->peca);
                emitirComprovante(peca);
                retirar_lugar(peca);
            }
            break;
        
        default:
            break;
    }

    return 1;
}

float vendaInteira(int peca)
{
    float valor;
    switch (peca)
    {
        case 0:            
            return 0;
        case DIVINA_COMEDIA:
            valor = VALOR_DIVINA_COMEDIA;
            atualiza_caixa(valor);
            break;
        case REI_LEAO:
            valor = VALOR_REI_LEAO;
            atualiza_caixa(valor);
            break;        
        case PINOQUIO:
            valor = VALOR_PINOQUIO;
            atualiza_caixa(valor);
            break;
        
        default:
            break;
    }

    return valor;
}

float vendaMeiaEntrada(int peca)
{
    float valor;
    switch (peca)
    {
        case 0:            
            return 0;
        case DIVINA_COMEDIA:
            valor = VALOR_DIVINA_COMEDIA / 2;
            atualiza_caixa(valor);
            break;
        case REI_LEAO:
            valor = VALOR_REI_LEAO / 2;
            atualiza_caixa(valor);
            break;        
        case PINOQUIO:
            valor = VALOR_PINOQUIO / 2;
            atualiza_caixa(valor);
            break;        
        default:
            break;
    }

    return valor;
}

float vendaIngresso100(int peca)
{
    switch (peca)
    {
        case 0:            
            return 0;
        case DIVINA_COMEDIA:
            atualiza_caixa(0);
            break;
        case REI_LEAO:
            atualiza_caixa(0);
            break;        
        case PINOQUIO:
            atualiza_caixa(0);
            break;        
        default:
            break;
    }

    return 0;
}

int fechamento()
{
    limpar_tela();
    printf("   FECHAMENTO DO DIA  \r\n\r\n");
    printf("Qtde vendas:......(%d)\r\n", ctrl_caixa.qtde);
    printf("Saldo do caixa:...(%.2f)\r\n", ctrl_caixa.valor);
    pausa();
    return 0;
}

//time lib

void retorna_data(struct tm * data)
{
    time_t dia;    

    time (&dia);
    memcpy(data, localtime(&dia), sizeof(struct tm));
}

bool verifica_terca()
{
    struct tm data;

    retorna_data(&data);
    return (data.tm_wday == terca) ? TRUE : FALSE;
}

void grava_datahora(char * retorno, int tamanho)
{
    struct tm data;

    retorna_data(&data);
    strftime (retorno, tamanho, "%d/%m/%Y %X", &data);
}

// controle de caixa
void atualiza_caixa(float valor)
{
    ctrl_caixa.qtde = ctrl_caixa.qtde + 1;
    ctrl_caixa.valor = ctrl_caixa.valor + valor;
}

void zera_caixa()
{
    ctrl_caixa.qtde = 0;
    ctrl_caixa.valor = 0;
}

void inicia_sala()
{ 
    inicia_pinoquio();
    inicia_reileao();
    inicia_divina_comedia();
}

void inicia_pinoquio()
{
    int hora =0;
    int dia = 0;
    
    pinoquio.pecaId = PINOQUIO;

    for(dia =0 ; dia < sabado+1; dia++)
    {
        for(hora = 0; hora < 4; hora++)
        {
            memset(pinoquio.peca[dia].hora[hora].lugares, DISPONIVEL, TAM_LUGARES * sizeof(int));
        }
    }    
}

void inicia_reileao()
{
    int hora =0;
    int dia = 0;
    
    rei_leao.pecaId = REI_LEAO;

    for(dia =0 ; dia < sabado+1; dia++)
    {
        for(hora = 0; hora < 4; hora++)
        {
            memset(rei_leao.peca[dia].hora[hora].lugares, DISPONIVEL, TAM_LUGARES * sizeof(int));
        }
    }
}

void inicia_divina_comedia()
{
    int hora =0;
    int dia = 0;

    divina_comedia.pecaId = DIVINA_COMEDIA;

    for(dia =0 ; dia < sabado+1; dia++)
    {
        for(hora = 0; hora < 4; hora++)
        {
            memset(divina_comedia.peca[dia].hora[hora].lugares, DISPONIVEL, TAM_LUGARES * sizeof(int));
        }
    }
}

bool verifica_sala(Venda * peca)
{
    int linha, i = 0;
    char tela[2048];
    char disponivelAux[4];
    int condicaoParada;
    int tecla;
    Peca *pecaId = NULL;

    if(verifica_disponibilidade(peca) == FALSE)
    {
        limpar_tela();
        printf("INGRESSOS ESGOTADOS... =(");
        pausa();
        return FALSE;
    }

    memset(tela, 0, sizeof(tela));
    pecaId = getPeca(peca->peca);
	
	condicaoParada = TAM_LUGARES;
	
    for(linha = 0; linha < condicaoParada; linha++)
    {
        if(linha % 10 == 0)
            strcat(tela, "\r\n");

        if(linha == 0)
        {
            if(pecaId->peca[peca->dia].hora->lugares[linha] == DISPONIVEL)
                sprintf(tela, " %03d",  linha+1);
            else
                sprintf(tela, " N/D");
                
        }
        else
        {
            strcat(tela, " ");

            if(pecaId->peca[peca->dia].hora->lugares[linha]  == DISPONIVEL)
            { 
                memset(disponivelAux, 0, sizeof(disponivelAux));
                sprintf(disponivelAux, "%03d",  linha+1);
                strcat(tela, disponivelAux);
            }
            else
            {   
                //Ocupado             
                strcat(tela, "N/D");
            }            
        }        
    } 

    do
    {
        limpar_tela();        
        printf(" |                PALCO               |\r\n");
        printf(" |____________________________________|\r\n");
        printf(tela);
        printf("\r\nEscolha um lugar:\r\n\r\n");
        scanf("%d", &tecla);

        if(tecla < 0 || tecla > TAM_LUGARES)
        {
            limpar_tela();
            printf("Poltrona invalida");
            pausa();
            continue;
        }
        else if(pecaId->peca[peca->dia].hora->lugares[tecla-1] == OCUPADO)
        {
            printf("Lugar ocupado");
            pausa();
            continue;
        }
        else
        {
            i=1;
            peca->lugar = tecla;
        }
        
    } 
    while(i == 0);
      

    return TRUE;
}

bool verifica_disponibilidade(Venda *peca)
{
    int i =0;
    bool tem_disponivel = FALSE;
    Peca * pecaId;

    pecaId = getPeca(peca->peca);
    
    for(i = 0; i < TAM_LUGARES; i++)
    {
       if(pecaId->peca[peca->dia].hora[peca->hora].lugares[i] == DISPONIVEL)
       {
            tem_disponivel = TRUE;
            break;
       }
    }   

    return tem_disponivel;
}

Peca* getPeca(int peca)
{
    Peca * pecaId = NULL;

    switch (peca)
    {
        case REI_LEAO:
            pecaId = &rei_leao;
            break;
        case PINOQUIO:
            pecaId = &pinoquio;
            break;
        case DIVINA_COMEDIA:
            pecaId = &divina_comedia;
            break;
        default:
            break;
    }

    return pecaId;
}

bool retirar_lugar(Venda * peca)
{
    Peca * pecaId = NULL;

    pecaId = getPeca(peca->peca);
    pecaId->peca[peca->dia].hora[peca->hora].lugares[peca->lugar-1] = OCUPADO;
}

void limpar_tela()
{
    system("cls");
}

void pausa()
{
    system("pause");
}

char * getDiaSemanda(int dia)
{
    switch (dia)
    {
        case domingo:
            return "Domingo";
        case segunda:
            return "Segunda";
        case terca:
            return "Terca";
        case quarta:
            return "Quarta";
        case quinta:
            return "Quinta";
        case sexta:
            return "Sexta";
        case sabado:
            return "Sabado";
    
        default:
            break;
    }
}
