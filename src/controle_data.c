#include <time.h>
#include "controle_data.h"
#include "utils.h"
//#include "defs.h"
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
            return "";
    }
}
