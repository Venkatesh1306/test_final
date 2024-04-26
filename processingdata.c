#include "testhead.h"

/*
Function to split the input frame and send
the expected frame
*/
unsigned short int processexpecteddata(unsigned char *ModbusTcpRxBuf, unsigned char *Test_TX, unsigned short int Dataregister[])
{

    for (increment = 0; increment < 12; increment++)
    {
        Test_TX[increment] = ModbusTcpRxBuf[increment];
    }

    // expected output for test function 0x03 -- read holding register
    if (ModbusTcpRxBuf[7] == 0x03)
    {
        Test_TX[8] = ModbusTcpRxBuf[11] * 2;
        Test_TX[5] = Test_TX[8] + 0x03;
        for (increment = 0; increment < ModbusTcpRxBuf[11]; increment++)
        {
            Test_TX[9 + increment * 2] = Dataregister[ModbusTcpRxBuf[9] + increment] / 0x100;  // High unsigned char
            Test_TX[10 + increment * 2] = Dataregister[ModbusTcpRxBuf[9] + increment] % 0x100; // Low unsigned char
        }
    }

    // expected output for test function 0x01 -- read coil status
    if (ModbusTcpRxBuf[7] == 0x01)
    {
        int input_array[5] = {0};
        int k = 0;
        int reg = ModbusTcpRxBuf[9] / 16;
        int reg_bit = ModbusTcpRxBuf[9] % 16;
        int num_of_bits = ModbusTcpRxBuf[11];
        int num_bytes = (num_of_bits + reg_bit) / 16 + ((num_of_bits + reg_bit) % 16 == 0 ? 0 : 1);

        Test_TX[8] = (num_of_bits + reg_bit + 7) / 8; // Number of bytes needed to represent bits
        Test_TX[5] = 0x03 + Test_TX[8];

        for (int i = reg; i < reg + num_bytes; i++)
        {
            for (int j = (i == reg) ? reg_bit : 0; j < ((i == reg + num_bytes - 1) ? (num_of_bits + reg_bit) % 16 : 16); j++)
            {
                input_array[k / 16] |= (GET_BIT(Dataregister[i], j) << (k % 16));
                k++;
            }
        }

        for (int i = 0; i < (k / 16) + 1; i++)
        {
            Test_TX[9 + i * 2] = input_array[i] % 0x100;
            Test_TX[10 + i * 2] = input_array[i] / 0x100;
        }
    }

    // error code
    /*
    error functions
    01 - function error
    02 - address error
    03 - illegal data value
    */
    if (ModbusTcpRxBuf[7] != 0x03 && ModbusTcpRxBuf[7] != 0x06 && ModbusTcpRxBuf[7] != 0x10 && ModbusTcpRxBuf[7] != 0x01 && ModbusTcpRxBuf[7] != 0x05)
    {
        Test_TX[5] = 0x03;
        Test_TX[7] = 0x80 + Test_TX[7];
        Test_TX[8] = 0x01;
    }
    else if (ModbusTcpRxBuf[9] > 0x19)
    {
        Test_TX[5] = 0x03;
        Test_TX[7] = 0x80 + Test_TX[7];
        Test_TX[8] = 0x02;
    }

    if (ModbusTcpRxBuf[7] == 0x06 && ModbusTcpRxBuf[10] > 253 && ModbusTcpRxBuf[11] > 232)
    {
        Test_TX[5] = 0x03;
        Test_TX[7] = 0x80 + Test_TX[7];
        Test_TX[8] = 0x03;
    }

    if (ModbusTcpRxBuf[7] == 0x10)
    {
        for (int increment = 0; increment < ModbusTcpRxBuf[11] * 2; increment++)
        {
            if (ModbusTcpRxBuf[increment * 2 + 13] > 253 && ModbusTcpRxBuf[increment * 2 + 14] > 232)
            {
                Test_TX[5] = 0x03;
                Test_TX[7] = 0x80 + Test_TX[7];
                Test_TX[8] = 0x03;
                break; // Exit the loop after the first occurrence
            }
        }
    }
    return 0;
}
