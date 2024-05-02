#include <stdio.h>

#define SET(x, y) x |= (1 << y)
#define READ(x, y) ((0u == (x & (1 << y))) ? 0u : 1u)
#define CLEAR(x, y) x &= ~(1 << y)

//process by bytes

unsigned short int ModbusTcpRxBuf[25] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x0f, 0x00, 0x01, 0x00, 0x07, 0x02, 0xcd, 0x01};
unsigned short int COIL[25];
unsigned short int c[25];

int main()
{
    unsigned int bit_count, reg, regbit, a, b, d;

    for (int i = 0; i < ModbusTcpRxBuf[12]; i++)
    {
        c[i] = (ModbusTcpRxBuf[(i * 2) + 14] << 8) | ModbusTcpRxBuf[(i * 2) + 13];
        //printf("%04x \n",c[i]);
    }

    for (bit_count = ModbusTcpRxBuf[11]-1; bit_count >=0  ; bit_count--)
    {
        regbit = ((ModbusTcpRxBuf[9] + bit_count) - 1) % 16;
        reg = ((ModbusTcpRxBuf[9] + bit_count) - 1) / 16;

        a = bit_count %16;
        b = bit_count /16;

        d = READ(c[b], a);

        if (d == 0x1)
        {
            printf("1-%d,%d  ", reg, regbit);
            SET(COIL[reg], regbit);
        }
        else
        {
            printf("0-%d,%d  ", reg, regbit);
            CLEAR(COIL[reg], regbit);
        }
        if (bit_count == 0)
        {
            break;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        printf("%04x ", COIL[i]);
    }
}
