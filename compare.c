#include "testhead.h"
// function for testing the output with the expected output
unsigned short int Test_ing(const unsigned char ModbusTcpTxBuf[], const unsigned char Test_tx[])
{   
    Test_Res = 1;
    test_c = 0;

    // Data enter check for FC 0x06
    if (ModbusTcpRxBuf[7] == 0x06)
    {
        add = (ModbusTcpRxBuf[8] << 8) | ModbusTcpRxBuf[9];
        test_c = (Dataregister[add] != ((ModbusTcpRxBuf[10] << 8) | ModbusTcpRxBuf[11])) ? 1 : 0;
    }

    // Data enter check for FC  0x10
    if (ModbusTcpRxBuf[7] == 0x10)
    {
        add = (ModbusTcpRxBuf[8] << 8) | ModbusTcpRxBuf[9];
        numRegisters = (ModbusTcpRxBuf[10] << 8) | ModbusTcpRxBuf[11];

        for (increment = 0; increment < numRegisters; increment++)
        {
            receivedData = (ModbusTcpRxBuf[13 + increment * 2] << 8) | ModbusTcpRxBuf[14 + increment * 2];
            test_c = (Dataregister[add + increment] != receivedData) ? 1 : 0;
        }
    }
 
    // Data enter check for FC  0x05
    if (ModbusTcpRxBuf[7] == 0x05)
    {
        int reg = (ModbusTcpRxBuf[9] - 1) / 16;
        int bit = (ModbusTcpRxBuf[9] - 1) % 16;

        if (ModbusTcpRxBuf[10] == 0xff)
        {
            SET(regis[reg], bit);
        }
        else
        {
            CLR(regis[reg], bit);
        }
       // printf("\n%04x - %04x", COIL[reg],regis[reg]);
        test_c = (Dataregister[reg] != regis[reg]) ? 1 : 0;
    }

    if (ModbusTcpRxBuf[7] == 0x0f)
    {
        unsigned int bit_count, reg, regbit, a, b, d;
        unsigned short int c[25];

        for (int i = 0; i < ModbusTcpRxBuf[12]; i++)
        {
            c[i] = (ModbusTcpRxBuf[(i * 2) + 14] << 8) | ModbusTcpRxBuf[(i * 2) + 13];
        }

        for (bit_count = ModbusTcpRxBuf[11] - 1; bit_count >= 0; bit_count--)
        {
            regbit = ((ModbusTcpRxBuf[9] + bit_count) - 1) % 16;
            reg = ((ModbusTcpRxBuf[9] + bit_count) - 1) / 16;

            a = bit_count % 16;
            b = bit_count / 16;

            d = GET_BIT(c[b], a);

            if (d == 0x1)
            {
                SET(COIL1[reg], regbit);
            }
            else
            {
                CLR(COIL1[reg], regbit);
            }
            if (bit_count == 0)
            {
                break;
            }
        }
        reg = ((ModbusTcpRxBuf[9] + bit_count) - 1) / 16;
        for (int i = reg; i <= reg +(ModbusTcpRxBuf[12]/2); i++)
        {
            printf("\n%04x--%04x  ", COIL[i], COIL1[i]);
            if ((Dataregister[i] != COIL1[i]))
            {
                test_c = 1;
                break;
            }
        }
    }

    numRegisters = (ModbusTcpTxBuf[7] < 0x80) ? (0x09 + ModbusTcpTxBuf[8]) : 0x09;
    // send packet check for all function code
    for (increment = 0; increment < numRegisters; increment++)
    {
        // Test_Res = (ModbusTcpTxBuf[increment] != Test_tx[increment]) ? 0 : 1;
        if ((ModbusTcpTxBuf[increment] != Test_tx[increment]))
        {
            Test_Res = 0;
            break; // Exit the loop or block
        }
    }

    return Test_Res;
}
