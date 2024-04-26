#include "testhead.h"

void printfunction()
{
    printf(ANSI_COLOR_RESET "\nQuery Packet:%d", inc + 1);

    if (ModbusTcpTxBuf[7] > 0x80)
    {
        switch (ModbusTcpTxBuf[8])
        {
        case 1:
            printf(ANSI_COLOR_ORANGE " - Function Error ");
            break;
        case 2:
            printf(ANSI_COLOR_ORANGE " - Address Error ");
            break;
        case 3:
            printf(ANSI_COLOR_ORANGE " - Data Error ");
            break;
        }
    }

#ifdef result

    printf(ANSI_COLOR_RESET "\n");
    printf("Number of packets to send: %d\n", ModbusTxLength);

    for (int i = 0; i < ModbusTcpRxBuftest[inc][0]; i++)
        printf("%02X ", ModbusTcpRxBuf[i]);
    printf("\n");

    printf("Expected Response:\n");
    for (int i = 0; i < Test_TXtest[inc][0]; i++)
        printf("%02X ", Test_TX[i]);
    printf("\n");

    printf("Actual Response:\n");
    int responseLength = (ModbusTcpTxBuf[7] == 0x06) ? 0x0C : ((ModbusTcpTxBuf[7] < 0x80) ? 0x09 + ModbusTcpTxBuf[8] : 0x09);
    for (int i = 0; i < responseLength; i++)
        printf("%02X ", ModbusTcpTxBuf[i]);
    printf("\n");

#endif

    printf(Test_Res == 1 ? ANSI_COLOR_GREEN " Test Passed" : ANSI_COLOR_RED " Test failed\n");

    if (ModbusTcpRxBuf[7] == 0x6 || ModbusTcpRxBuf[7] == 0x10)
        printf(test_c == 1 ? ANSI_COLOR_RED " - Data not Entered" : ANSI_COLOR_GREEN " - Data Entered");

    printf("\n");
    printf(ANSI_COLOR_RESET); // Reset color to default
}
