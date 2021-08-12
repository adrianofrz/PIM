#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"


int main(void)
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

