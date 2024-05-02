// including the required header files
#include "Z:\ModbusTcpRenamed8Fn\modhead.h"
#include "Z:\ModbusTcpRenamed8Fn\libModbus\ModbusTcp.h"
#include <stdio.h>
//#include <stdint.h>


// define the values
#define test_ing
#define result
#define INR_SIZE 21
#define GET_BIT(x, pos) ((x >> pos) & 1)
#define SET(PIN, N) (PIN |= (1 << N))
#define CLR(PIN, N) (PIN &= ~(1 << N))

// ANSI escape codes for text color - for testing features
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_ORANGE "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Variables and Values
extern unsigned char ModbusTcpRxBuftest[INR_SIZE][100];
extern unsigned char Test_TXtest[INR_SIZE][100];
extern unsigned char ModbusTcpRxBuf[100];
extern unsigned char ModbusTcpTxBuf[25];
extern unsigned char Test_tx[25];
extern unsigned short int COIL1[25];
extern unsigned short int COIL[25];
extern unsigned char regis[25];
extern unsigned short int Dataregister[100];
extern int increment;
extern int Test_Res;
extern unsigned int incrs;
extern int test_c;
extern unsigned int ModbusTxLength;
extern unsigned short int receivedData;
extern unsigned short int add;
extern unsigned short int numRegisters;


// declaration of the function
unsigned short int processexpecteddata(unsigned char *ModbusTcpRxBuf, unsigned char *Test_tx, unsigned short int Dataregister[]);
unsigned short int Test_ing(const unsigned char ModbusTcpTxBuf[], const unsigned char Test_tx[]);
uint16_t modbusTcpFrame (uint8_t *p_modbusRxBuf, uint16_t *p_dataMemory, uint8_t *p_modbusTxBuf,uint16_t modBusframeLength);
void printfunction();