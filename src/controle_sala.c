//#include "defs.h"
#include "controle_sala.h"
#include "utils.h"

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
        printf("%s", tela);
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

void retirar_lugar(Venda * peca)
{
    Peca * pecaId = NULL;

    pecaId = getPeca(peca->peca);
    pecaId->peca[peca->dia].hora[peca->hora].lugares[peca->lugar-1] = OCUPADO;
}

int escolhaPeca()
{
    int opcao;
    Venda peca = {0,0,0};
    
    limpar_tela();

    printf("Escolha a pe�a\r\n");
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