#include <xc.h>
#include "user.h"

#define _XTAL_FREQ 64000000

volatile unsigned char BufferIMU[30];
volatile unsigned char NbIMUData = 0;

void InitApp(void) {
    // Broches moteurs (à adapter selon votre câblage)
    TRISCbits.TRISC4 = 0; LATCbits.LATC4 = 0;
    TRISCbits.TRISC2 = 0; LATCbits.LATC2 = 1;
    TRISCbits.TRISC3 = 0; LATCbits.LATC3 = 0;
    TRISAbits.TRISA7 = 0; LATAbits.LATA7 = 1;
    
    // UART2 pour BNO055 (RB2 TX, RB1 RX)
    TRISBbits.TRISB2 = 0; TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSELB1 = 0;
    U2BRGH = 0; U2BRGL = 138;
    U2CON0 = 0xB0; U2CON1 = 0x80; U2CON2 = 0x00;
    PIE8bits.U2RXIE = 1;
    
    // UART1 pour PC (RF0 TX, RF1 RX)
    TRISFbits.TRISF0 = 0; TRISFbits.TRISF1 = 1;
    ANSELFbits.ANSELF1 = 0;
    U1BRGH = 0; U1BRGL = 138;
    U1CON0 = 0xB0; U1CON1 = 0x80; U1CON2 = 0x00;
}

void pwm_init(void) {
    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 0;
    RC5PPS = 0x15;   // CCP1 -> RC5
    RC1PPS = 0x16;   // CCP2 -> RC1
    RC2PPS = 0x17;   // CCP3 -> RC2
    RC3PPS = 0x18;   // CCP4 -> RC3
    RB2PPS = 0x23;   // UART2 TX
    U2RXPPS = 0x09;  // UART2 RX
    RF0PPS = 0x20;   // UART1 TX
    U1RXPPS = 0x29;  // UART1 RX
    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 1;
    
    TRISCbits.TRISC5 = 0; TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0; TRISCbits.TRISC3 = 0;
    
    // Timer2 pour CCP1 et CCP2
    T2CLKCON = 0x01; T2CONbits.T2CKPS = 0b011; T2PR = 199;
    CCP1CON = 0b10001100; CCP2CON = 0b10001100;
    T2CONbits.ON = 1;
    
    // Timer4 pour CCP3 et CCP4
    T4CLKCON = 0x01; T4CONbits.T4CKPS = 0b011; T4PR = 199;
    CCP3CON = 0b10001100; CCP4CON = 0b10001100;
    T4CONbits.ON = 1;
    
    CCPR1 = CCPR2 = CCPR3 = CCPR4 = 0;
}

void envoie_trame(char *Trame, unsigned char count) {
    for(unsigned char i=0; i<count; i++) {
        while(!U2TXIF);
        U2TXB = *Trame++;
    }
}

void putch(char data) {
    while(!U1TXIF);
    U1TXB = data;
}

void UART_Flush(void) {
    NbIMUData = 0;
}
