#include "controle_caixa.h"
#include "controle_sala.h"
#include "utils.h"

Caixa ctrl_caixa = {0,0};

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

void iniciarVenda()
{
    escolhaPeca();    
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
            printf("Rei Le�o\r\n");
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
