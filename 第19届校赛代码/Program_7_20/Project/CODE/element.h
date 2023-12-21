#include "headfile.h"
#include "bal.h"
#include "motor.h"
#include "LQ_PID.h"
#include "encoder.h"
void Judge_Game(void);
void get_tuoluoyi(void);


extern int16 L0,L1,L2,R0,R1,R2;
extern bit ring_road_flag;
extern float road_L,road_R,road;
extern int16 gyro_z;
void go_ring(void);
void go_4_ring(void);
void out_garage(void);
void in_garage(void);