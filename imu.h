#ifndef IMU_H
#define IMU_H

#include <stdint.h>
#include <stdbool.h>

#define IMU_ADDR_PAGE_ID    0x07
#define IMU_ADDR_OPR_MODE   0x3D
#define IMU_ADDR_UNIT_SEL   0x3B
#define IMU_ADDR_EULER_HEAD 0x1A

#define IMU_MODE_CONFIG     0x00
#define IMU_MODE_NDOF       0x0C
#define IMU_PAGE_ID_0       0x00

void imu_init(void);
void imu_ask_euler_angles(void);

#endif
