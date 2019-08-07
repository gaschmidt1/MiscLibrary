

#include "WS0010.h"

/*------------------------------------------------------------------------------
 ***   ROTINA DE COMUNICAÇÃO COM Ws0010  ***
 ***   Gerry Adriano Schmidt    ***
 ***      STATUS OK       ***
--------------------------------------------------------------------------------
                               REV: 29-11-2010
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
 ***   Definições do Ws0010   ***
------------------------------------------------------------------------------*/

//uint8_t  f_reinit;

//uint16_t reinit_cnt;

uint8_t Ws0010_buffer[LcdBufferLen];

uint16_t ptr;

void DelayLongo(void)
{
    uint8_t f;
    for (f = 0; f < 10; f++)
    {
        __delay_ms(200);
    }
        //Delay10KTCYx(250);
}



/*------------------------------------------------------------------------------
 ***   Rotina que envia o byte   ***
------------------------------------------------------------------------------*/

void Ws0010PutByte(uint8_t end, uint8_t fras)
{
    TrisLcd &= NIBBLE1;
    RsLcd = end;

#if (defined(USE_LOW_NIBBLE_LCD))
    fras = SwapNibbles(fras);
#endif

#if (defined(USE_HIGH_NIBBLE_LCD) || defined(USE_LOW_NIBBLE_LCD))
    PortLcd &= NIBBLE1;
    DelayWs0010();
    envia_nibble(fras);
    DelayWs0010();
    EnLcd = HIGH;
    DelayWs0010();
    EnLcd = LOW;
    DelayWs0010();
    RsLcd = end;

    fras = SwapNibbles(fras);

    PortLcd &= NIBBLE1;
    DelayWs0010();
    envia_nibble(fras);
    DelayWs0010();
    EnLcd = HIGH;
    DelayWs0010();
    EnLcd = LOW;
    DelayWs0010();
#endif

#if (defined(USE_8BITS_LCD))

    PORT_LCD = fras;
    DelayWs0010();
    EN_LCD = TRUE;
    DelayWs0010();
    EN_LCD = FALSE;
    DelayWs0010();
#endif
}

/*------------------------------------------------------------------------------
 ***   Rotina que inicializa o LCD   ***
------------------------------------------------------------------------------*/

void Ws0010Init(void)
{
    // sequencia do Weber
#if (defined(USE_HIGH_NIBBLE_LCD) || defined(USE_LOW_NIBBLE_LCD))
    //uint8_t init[14] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x88, 0x00, 0xCC, 0x11, 0xFF, 0x00, 0x22};
    uint8_t init[14] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x88, 0x00, 0xCC, 0x11, 0xFF, 0x00, 0x66};
#endif
#if (defined(USE_8BITS_LCD))
    uint8_t init[14] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x08, 0x00, 0x0C, 0x01, 0x0F, 0x00, 0x06};
#endif
    uint8_t i;
    // inicializa o sentido dos pinos
    TrisLcdEn = LOW;
    TrisLcdRs = LOW;

    for (i = 0; i < 14; i++)
    {
        TrisLcd &= NIBBLE1;
        RsLcd = 0;
        PortLcd &= NIBBLE1;
        DelayWs0010();
        envia_nibble(init[i]);
        DelayWs0010();
        EnLcd = HIGH;
        DelayWs0010();
        EnLcd = LOW;
        DelayWs0010();
        DelayWs0010();
        DelayWs0010();
        DelayWs0010();
    }
}

/*------------------------------------------------------------------------------
 ***     Rotina que posiciona LCD   ***
------------------------------------------------------------------------------*/

void Ws0010PutGotoXY(uint8_t posx, uint8_t posy)
{
    Ws0010PutByte(0, posx + 0x7F);
    Ws0010PutByte(0, posy + 0x3F);
}

/*------------------------------------------------------------------------------
 *** operações com buffer     ***
------------------------------------------------------------------------------*/

void Ws0010BufGotoXY(uint8_t posx, uint8_t posy)
{
    ptr = (posx - 1) + ((LcdBufferLen / LcdNbrLines) * (posy - 1));
}

/*------------------------------------------------------------------------------
                        Rotina para escrever no display
------------------------------------------------------------------------------*/

void Ws0010Buf4x6Char(uint8_t carac, uint8_t inv)
{
    uint8_t j;
    for (j = 0; j < 4; j++)
    {
        if (inv)
            Ws0010_buffer[ptr++] = ~ascii_table4x6[(carac - 0x20)][j];
        else
            Ws0010_buffer[ptr++] = ascii_table4x6[(carac - 0x20)][j];
    }
    if (inv)
        Ws0010_buffer[ptr++] = ~0x00;
    else
        Ws0010_buffer[ptr++] = 0x00;
}

void Ws0010Buf5x7Char(uint8_t carac, uint8_t inv)
{
    uint8_t j;
    for (j = 0; j < 5; j++)
    {
        if (inv)
            Ws0010_buffer[ptr++] = ~ascii_table5x7[(carac - 0x20)][j];
        else
            Ws0010_buffer[ptr++] = ascii_table5x7[(carac - 0x20)][j];
    }
    if (inv)
        Ws0010_buffer[ptr++] = ~0x00;
    else
        Ws0010_buffer[ptr++] = 0x00;
}

void Ws0010Buf9x16Char(uint8_t carac, uint8_t inv)
{
    uint16_t j;

    for (j = 0; j < 18; j++)
    {
        if (j == 9)
        {
            if (inv)
                Ws0010_buffer[ptr++] = ~0x00;
            else
                Ws0010_buffer[ptr++] = 0x00;
            Ws0010BufGotoXY((ptr - 9), 2);
        }
        if (inv)
            Ws0010_buffer[ptr++] = ~ascii_table9x16[carac - 0x30][j];
        else
            Ws0010_buffer[ptr++] = ascii_table9x16[carac - 0x30][j];
    }
    if (inv)
        Ws0010_buffer[ptr++] = ~0x00;
    else
        Ws0010_buffer[ptr++] = 0x00;
    // retorna primeira linha
    ptr -= 100;
}
/*------------------------------------------------------------------------------
                        Rotina para escrever no display
------------------------------------------------------------------------------*/
void Ws0010BufString(const uint8_t *frase, uint8_t inv, void(*Ptr2Func)(uint8_t, uint8_t))
{
    while (*frase)
        Ptr2Func(*frase++, inv);
}
/*------------------------------------------------------------------------------
                        Rotina para escrever no display
------------------------------------------------------------------------------*/
void Ws0010Bufu8(uint8_t inteiro, uint8_t nro, uint8_t inv, void(*Ptr2Func)(uint8_t, uint8_t))
{
    uint8_t dado;
    uint8_t mask[4] = {0, 1, 10, 100};
    uint8_t rasc;

    if (nro < 3)
        inteiro = inteiro % mask[nro + 1];

    mask[0] = mask[nro];
    rasc = inteiro;

    while (nro)
    {
        dado = (rasc / mask[0]);
        rasc = rasc % mask[0];
        dado = dado + '0';
        Ptr2Func(dado, inv);
        mask[0] = mask[0] / 10;
        nro--;
    }
}
/*------------------------------------------------------------------------------
 ***                           ***
------------------------------------------------------------------------------*/

void Ws0010Bufu16(uint16_t inteiro, uint8_t nro, uint8_t inv, void(*Ptr2Func)(uint8_t, uint8_t))
{
    uint8_t dado;
    uint16_t mask[6] = {0, 1, 10, 100, 1000, 10000};
    uint16_t rasc;

    if (nro < 5)
        inteiro = inteiro % mask[nro + 1];

    mask[0] = mask[nro];
    rasc = inteiro;

    while (nro)
    {
        dado = (uint8_t) (rasc / mask[0]);
        rasc = rasc % mask[0];
        dado = dado + '0';
        Ptr2Func(dado, inv);
        mask[0] = mask[0] / 10;
        nro--;
    }
}

/*------------------------------------------------------------------------------
 ***                           ***
------------------------------------------------------------------------------*/

void Ws0010Bufu32(uint32_t inteiro, uint8_t nro, uint8_t inv, void(*Ptr2Func)(uint8_t, uint8_t))
{
    uint8_t dado;
    uint32_t mask[11] = {0, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    uint32_t rasc;

    if (nro < 10)
        inteiro = inteiro % mask[nro + 1];

    mask[0] = mask[nro];
    rasc = inteiro;

    while (nro)
    {
        dado = (uint8_t) (rasc / mask[0]);
        rasc = rasc % mask[0];
        dado = dado + '0';
        Ptr2Func(dado, inv);
        mask[0] = mask[0] / 10;
        nro--;
    }
}

/*------------------------------------------------------------------------------
 ***                           ***
------------------------------------------------------------------------------*/

void Ws0010BufPatern(uint8_t dado, uint8_t count)
{
    uint8_t i;
    if (count > LcdBufferLen)
        count = LcdBufferLen;
    for (i = 0; i < count; i++)
    {
        Ws0010_buffer[ptr++] = dado;
    }
}

/*------------------------------------------------------------------------------
            escreve uma barra de progresso
------------------------------------------------------------------------------*/

void Ws0010BufBargraph(uint8_t percent, uint8_t size)
{
    uint8_t i;
    percent = (uint8_t) ((uint16_t) ((uint16_t) percent * (uint16_t) size) / 100);

    for (i = 0; i < size - 1; i++)
    {
        if (i <= percent)
            Ws0010_buffer[ptr++] = 0x7E;
        else
            Ws0010_buffer[ptr++] = 0x42;
    }
    Ws0010_buffer[ptr++] = 0x7E;
}
/*------------------------------------------------------------------------------
                        Rotina para escrever no display
------------------------------------------------------------------------------*/

void Ws0010Refresh(void)
{
    uint8_t j, dado;
    Ws0010PutGotoXY(1, 1);

    for (j = 0; j < LcdBufferLen; j++)
    {
        dado = Ws0010_buffer[j];
        if (!dado)
            Ws0010PutByte(0, 0x06);
        Ws0010PutByte(1, dado);
    }

}

/*------------------------------------------------------------------------------
                        Rotina para desenhar o logo CLK no display
------------------------------------------------------------------------------*/
void Ws0010BufBitmap(const uint8_t* Image, uint8_t Size)
{
    uint8_t gap;
    uint16_t j;
    gap = (LcdBufferLen - Size) / 4;
    Ws0010BufGotoXY(1, 1);
    for (j = 0; j < Size; j++)
    {
        if (j < Size / 2)
            Ws0010_buffer[j + gap] = *Image;
        else
            Ws0010_buffer[j + (3 * gap)] = *Image;
        
        Image++;
    }    
}

/*------------------------------------------------------------------------------
 ***                           ***
------------------------------------------------------------------------------*/

void Ws0010BufCursor(uint8_t comp)
{
    uint8_t i;
    for (i = 0; i < comp; i++)
        Ws0010_buffer[ptr++] |= 0x80;
}

/*------------------------------------------------------------------------------
 ***                           ***
------------------------------------------------------------------------------*/

void Ws0010BufBinary(uint16_t data, uint8_t nro)
{
    uint16_t i;
    for (i = 0; i <= nro; i++)
    {
        if(data & (1L << i))
        {
            Ws0010BufPatern(0x7E, 4);
            Ws0010BufPatern(0x00, 1);
        }
        else
        {
            Ws0010BufPatern(0x7E, 1);
            Ws0010BufPatern(0x42, 2);
            Ws0010BufPatern(0x7E, 1);
            Ws0010BufPatern(0x00, 1);
        }
    }
}

/*------------------------------------------------------------------------------
 ***                           ***
------------------------------------------------------------------------------*/
