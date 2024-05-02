#define INR_SIZE 21

unsigned char ModbusTcpRxBuftest[INR_SIZE][100];
unsigned char Test_TXtest[INR_SIZE][100];
unsigned char ModbusTcpRxBuf[100];
unsigned char ModbusTcpTxBuf[25];
unsigned char Test_tx[25];
unsigned short int COIL[25];
unsigned short int COIL1[25];
unsigned char regis[25] = {0};
unsigned short int Dataregister[100];
int increment;
int Test_Res;
unsigned int incrs;
int test_c;
unsigned int ModbusTxLength;
unsigned short int receivedData;
unsigned short int add;
unsigned short int numRegisters;
