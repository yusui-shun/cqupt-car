#include "headfile.h"
#include "motor.h"


void Encoder_init(void){
	ctimer_count_clean(P53);
	ctimer_count_clean(P35);
	ctimer_count_init(CTIM3_P04);
	ctimer_count_init(CTIM0_P34);
}

int16 encoder_get(CTIMN_enum pin)
{
	int16 t;
	t=ctimer_count_read(pin);
	ctimer_count_clean(pin);
	return t;
}

void Motor_Init(void)
{
		pwm_init(MotorA_N, MotorFre, 0);//引脚
		pwm_init(MotorB_N, MotorFre, 0);
		pwm_init(MotorB_P, MotorFre, 0);
		pwm_init(MotorA_P, MotorFre, 0);
}

void Motor_SpeedSet(int16 Duty_L,int16 Duty_R)
{
    if(Duty_L>=0)
    {
				Duty_L=8.315*Duty_L+429.69;
				Duty_Limit(Duty_L);
        pwm_duty(MotorB_N,0);
        pwm_duty(MotorA_N,Duty_L);
    }
    else if(Duty_L < 0)
    {
				Duty_L=-Duty_L;
				Duty_L=8.315*Duty_L+429.69;
				Duty_Limit(Duty_L);
        pwm_duty(MotorB_N,Duty_L);
        pwm_duty(MotorA_N,0);
    }

    if(Duty_R>=0)
    {
			 Duty_R=8.3372*Duty_R+469.37;
			 Duty_Limit(Duty_R);
       pwm_duty(MotorA_P,Duty_R);
       pwm_duty(MotorB_P,0);
    }
    else if(Duty_R < 0)
    {		
				Duty_R=-Duty_R;
				Duty_R=8.3372*Duty_R+469.37;
				Duty_Limit(Duty_R);
        pwm_duty(MotorA_P,0);
        pwm_duty(MotorB_P,Duty_R);
    }
}
void Duty_Limit(int16 Duty){
	   if(Duty>MAXDUTY)
     {
         Duty=MAXDUTY;
     }
}
