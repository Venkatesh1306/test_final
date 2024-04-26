#define INR_SIZE 11

unsigned char ModbusTcpRxBuftest[INR_SIZE][100];
unsigned char Test_TXtest[INR_SIZE][100];
unsigned char ModbusTcpRxBuf[100];
unsigned char ModbusTcpTxBuf[25];
unsigned char Test_TX[25];
unsigned short int Dataregister[100];
int increment;
int Test_Res;
int inc;
int test_c;
unsigned int ModbusTxLength;
unsigned short int receivedData;
unsigned short int add;
unsigned short int numRegisters;