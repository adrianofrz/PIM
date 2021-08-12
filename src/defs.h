#ifndef __DEFS_H
#define __DEFS_H

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

#define TAM_LUGARES 10*10

#define VALOR_DIVINA_COMEDIA    10.00
#define VALOR_REI_LEAO          12.00
#define VALOR_PINOQUIO          12.00

//Horario pe�as
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


Peca ctrl_sala[3];
Peca divina_comedia;
Peca pinoquio;
Peca rei_leao;

#endif
//Prototippos de fun��es
/*



*/