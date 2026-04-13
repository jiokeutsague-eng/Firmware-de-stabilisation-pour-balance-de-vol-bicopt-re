#ifndef USER_H
#define USER_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

extern volatile unsigned char BufferIMU[30];
extern volatile unsigned char NbIMUData;

void InitApp(void);
void pwm_init(void);
void envoie_trame(char *Trame, unsigned char count);
void putch(char data);
void UART_Flush(void);

#endif
