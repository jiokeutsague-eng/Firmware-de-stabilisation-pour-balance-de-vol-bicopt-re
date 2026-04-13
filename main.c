#include <xc.h>
#include <stdio.h>
#include "user.h"
#include "imu.h"

#pragma config FEXTOSC = OFF, RSTOSC = HFINTOSC_64MHZ, WDTE = OFF, LVP = ON
#define _XTAL_FREQ 64000000

extern volatile unsigned char BufferIMU[30];
extern volatile unsigned char NbIMUData;

short CombineBytes(unsigned char lower, unsigned char upper) {
    return (short)((upper << 8) | lower);
}

void main(void) {
    OSCCON1 = 0x60;
    OSCFRQ = 0x08;
    
    InitApp();        // UART2 (IMU), UART1 (PC), GPIO
    pwm_init();       // 4 canaux PWM (CCP1 à CCP4)
    
    INTCON0bits.GIE = 1;
    
    // Arrêt moteurs
    CCPR1 = CCPR2 = CCPR3 = CCPR4 = 0;
    
    // Consignes : 0° (horizontal)
    float consigne_roll = 0.0;
    float consigne_pitch = 0.0;
    
    // PID (P+D) pour roll et pitch
    float Kp = 4.5, Kd = 1.5;
    float erreur_roll = 0, erreur_prec_roll = 0, PID_roll = 0;
    float erreur_pitch = 0, erreur_prec_pitch = 0, PID_pitch = 0;
    
    int gaz_moyen = 400;  // puissance de base (0-1023)
    
    __delay_ms(1000);
    imu_init();           // BNO055 en mode NDOF
    __delay_ms(100);
    
    while(1) {
        NbIMUData = 0;
        imu_ask_euler_angles();
        __delay_ms(15);
        
        if(NbIMUData >= 8 && BufferIMU[0] == 0xBB) {
            // Envoi trame brute vers PC
            for(int i = 0; i < NbIMUData; i++) putch(BufferIMU[i]);
            
            // Extraction Roll (bytes 4-5) et Pitch (bytes 6-7)
            short rawRoll  = CombineBytes(BufferIMU[4], BufferIMU[5]);
            short rawPitch = CombineBytes(BufferIMU[6], BufferIMU[7]);
            float roll  = rawRoll / 16.0;
            float pitch = rawPitch / 16.0;
            
            // PID Roll
            erreur_roll = consigne_roll - roll;
            PID_roll = Kp * erreur_roll + Kd * (erreur_roll - erreur_prec_roll);
            erreur_prec_roll = erreur_roll;
            
            // PID Pitch
            erreur_pitch = consigne_pitch - pitch;
            PID_pitch = Kp * erreur_pitch + Kd * (erreur_pitch - erreur_prec_pitch);
            erreur_prec_pitch = erreur_pitch;
            
            // Mixage quadricoptère (configuration X)
            // M1 avant gauche, M2 avant droit, M3 arrière gauche, M4 arrière droit
            int mot1 = gaz_moyen + (int)PID_roll + (int)PID_pitch;
            int mot2 = gaz_moyen - (int)PID_roll + (int)PID_pitch;
            int mot3 = gaz_moyen + (int)PID_roll - (int)PID_pitch;
            int mot4 = gaz_moyen - (int)PID_roll - (int)PID_pitch;
            
            // Bornes 0-1023
            #define LIMIT(x) if(x>1023) x=1023; if(x<0) x=0;
            LIMIT(mot1); LIMIT(mot2); LIMIT(mot3); LIMIT(mot4);
            
            CCPR1 = mot1;   // CCP1 -> Moteur 1
            CCPR2 = mot2;   // CCP2 -> Moteur 2
            CCPR3 = mot3;   // CCP3 -> Moteur 3
            CCPR4 = mot4;   // CCP4 -> Moteur 4
        }
    }
}
