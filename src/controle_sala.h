#ifndef __CONTROLE_SALA_H
#define __CONTROLE_SALA_H

#include "defs.h"

void inicia_sala();
void inicia_pinoquio();
void inicia_reileao();
void inicia_divina_comedia();
bool verifica_sala(Venda * peca);
bool verifica_disponibilidade(Venda * peca);
Peca* getPeca(int peca);
void retirar_lugar(Venda * peca);
int escolhaPeca();
int escolhaDia(Venda* peca);
int escolhoHorario(Venda* peca);

#endif