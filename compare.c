#include "testhead.h"

// function for testing the output with the expected output
unsigned short int Test_ing(const unsigned char ModbusTcpTxBuf[], const unsigned char Test_TX[])
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

    numRegisters = (ModbusTcpTxBuf[7] < 0x80) ? (0x08 + ModbusTcpTxBuf[8]) : 0x09;
    // send packet check for all function code
    for (increment = 0; increment < numRegisters; increment++)
    {
        Test_Res = (ModbusTcpTxBuf[increment] != Test_TX[increment]) ? 0 : 1;
    }

    return Test_Res;
}
