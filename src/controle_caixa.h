#ifndef __CONTROLE_CAIXA_H
#define __CONTROLE_CAIXA_H

#include "defs.h"

int tipoEntrada(Venda* peca);
float vendaInteira(int peca);
float vendaMeiaEntrada(int peca);
float vendaIngresso100(int peca);
int fechamento();
void zera_caixa();
void atualiza_caixa(float valor);
void iniciarVenda();
void emitirComprovante(Venda * peca);

#endif