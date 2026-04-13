#include <xc.h>
#include "user.h"
#include "imu.h"

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 64000000UL
#endif

static void IMU_Write_Char(char data) {
    while(!U2TXIF);
    U2TXB = data;
}

void imu_init(void) {
    char trame_config[] = {0xAA, 0x00, IMU_ADDR_OPR_MODE, 0x01, IMU_MODE_CONFIG};
    envoie_trame(trame_config, 5);
    __delay_ms(30);
    
    char trame_page[] = {0xAA, 0x00, IMU_ADDR_PAGE_ID, 0x01, IMU_PAGE_ID_0};
    envoie_trame(trame_page, 5);
    __delay_ms(10);
    
    char trame_unit[] = {0xAA, 0x00, IMU_ADDR_UNIT_SEL, 0x01, 0x00};
    envoie_trame(trame_unit, 5);
    __delay_ms(10);
    
    char trame_ndof[] = {0xAA, 0x00, IMU_ADDR_OPR_MODE, 0x01, IMU_MODE_NDOF};
    envoie_trame(trame_ndof, 5);
    __delay_ms(30);
}

void imu_ask_euler_angles(void) {
    char trame_read[] = {0xAA, 0x01, IMU_ADDR_EULER_HEAD, 0x06};
    envoie_trame(trame_read, 4);
}
