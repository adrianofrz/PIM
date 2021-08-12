#ifndef __CONTROLE_CAIXA_H
#define __CONTROLE_CAIXA_H

#include "defs.h"
#include <stdlib.h>

void retorna_data(struct tm * data);
bool verifica_terca();
void grava_datahora(char * retorno, int tamanho);
char * getDiaSemanda(int dia);

#endif