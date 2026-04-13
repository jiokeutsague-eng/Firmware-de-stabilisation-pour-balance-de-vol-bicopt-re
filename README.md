# Firmware de vol pour quadricoptère – PIC18F57Q43 + BNO055

**Statut** : ✅ Opérationnel (stabilisation roll/pitch)  
**Cible** : Drone de type quadricoptère (4 moteurs)

## Caractéristiques
- Microcontrôleur : PIC18F57Q43 @ 64 MHz
- Capteur d'orientation : BNO055 (fusion complète, UART)
- 4 sorties PWM (16 bits) pour ESC brushless
- PID proportionnel-dérivé (P+D) sur les axes roulis et tangage
- Communication série (115200 bauds) vers PC pour debug

## Mixage moteurs (configuration X)
- M1 = gaz + roll + pitch
- M2 = gaz - roll + pitch
- M3 = gaz + roll - pitch
- M4 = gaz - roll - pitch

## Brochage principal
| PIC18F57Q43 | Fonction               |
|-------------|------------------------|
| RB1 (RX)    | BNO055 TX              |
| RB2 (TX)    | BNO055 RX              |
| RC5         | CCP1 → Moteur 1        |
| RC1         | CCP2 → Moteur 2        |
| RC2         | CCP3 → Moteur 3        |
| RC3         | CCP4 → Moteur 4        |
| RF0         | UART1 TX → PC          |

## Utilisation
1. Ouvrir `mplab_project/` dans MPLAB X IDE.
2. Compiler avec XC8 (v2.00+).
3. Flasher le PIC.
4. Alimenter le drone et observer la stabilisation.

## Améliorations possibles
- Ajout d'un terme intégral (PID complet)
- Réglage des gains par télémétrie
- Gestion du lacet (yaw) via magnétomètre

## Auteur
Chris TSAGUE – [LinkedIn](https://linkedin.com/in/chris-tsague)

## Licence
MIT
