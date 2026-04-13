# Firmware de stabilisation pour balance de vol


**Microcontrôleur** : PIC18F57Q43 @ 64 MHz  
**Capteur** : BNO055 (fusion de capteurs, angles Euler)  
**Actionneurs** : 2 moteurs DC via PWM (pont en H L293D)  
**Outils** : MPLAB X IDE v6.x, XC8 compiler v2.x

---

## 📌 Description

Projet académique visant à fiabiliser la commande de vol d'un drone.
Il implémente un **firmware temps réel** qui :

- Configure le BNO055 en mode NDOF (fusion complète)
- Lit les angles de roulis (Roll) via UART
- Calcule une correction PID proportionnelle‑dérivée (P+D)
- Applique une commande différentielle sur deux moteurs via PWM
- Envoie les trames brutes vers un PC (MATLAB / interface de visualisation)

Le système a été validé sur une **balance de vol** à deux moteurs (configuration bicoptère) et constitue une base pour un futur drone stabilisé.

---

## ⚙️ Fonctionnalités

- ✅ Initialisation du BNO055 (mode config, page 0, unités degrés)
- ✅ Lecture des angles Euler (Heading, Roll, Pitch) sur 6 octets
- ✅ PID avec consigne réglable (exemple : stabilisation à -45° pour test)
- ✅ Génération PWM 16 bits sur deux canaux (CCP1, CCP2)
- ✅ Interruption UART pour réception des trames IMU
- ✅ Communication série de diagnostic (vers PC)


## 🔌 Brochage matériel (extrait)

| PIC18F57Q43 | Composant              |
|-------------|------------------------|
| RB1 (RX)    | BNO055 – TX            |
| RB2 (TX)    | BNO055 – RX            |
| RC1         | PWM – Moteur 1 (CCP2)  |
| RC5         | PWM – Moteur 2 (CCP1)  |
| RF4, RF5    | LCD (optionnel)        |
| RD0–RD7     | LCD (optionnel)        |

## 📚 Références

- [PIC18F57Q43 Datasheet](https://www.microchip.com/wwwproducts/en/PIC18F57Q43)
- [BNO055 Datasheet](https://www.bosch-sensortec.com/products/smart-sensors/bno055/)

## 📝 Licence

MIT – voir fichier `LICENSE`.
