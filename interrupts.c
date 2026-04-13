#include <xc.h>
#include "user.h"

extern volatile unsigned char BufferIMU[30];
extern volatile unsigned char NbIMUData;

void __interrupt(high_priority) HighISR(void) {
    if(PIR8bits.U2RXIF == 1) {
        if(NbIMUData < 30) BufferIMU[NbIMUData++] = U2RXB;
        else NbIMUData = 0;
        PIR8bits.U2RXIF = 0;
    }
}
