#include "headfile.h"
#include "motor.h"


void Encoder_init(void){
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
//	if	(!(Duty_R==0 && Duty_L==0))
//	{
//		Duty_L>0 ? Duty_L+=250 : Duty_L-=250;
//		Duty_R>0 ? Duty_R+=750 : Duty_R-=750;	
//	}

	
     if(Duty_L>MAXDUTY)
     {
         Duty_L=MAXDUTY;
     }
     if(Duty_R>MAXDUTY)
     {
         Duty_R=MAXDUTY;
     }
		 if(Duty_L<-MAXDUTY)
     {
         Duty_L=-MAXDUTY;
     }
     if(Duty_R<-MAXDUTY)
     {
         Duty_R=-MAXDUTY;
     }
		 
    if(Duty_L>=0)
    {
        pwm_duty(MotorB_N,0);
        pwm_duty(MotorA_N,Duty_L);
    }
    else if(Duty_L < 0)
    {
        pwm_duty(MotorB_N,-Duty_L);
        pwm_duty(MotorA_N,0);
    }

    if(Duty_R>=0)
    {
       pwm_duty(MotorA_P,Duty_R);
       pwm_duty(MotorB_P,0);
    }
    else if(Duty_R < 0)
    {

        pwm_duty(MotorA_P,0);
        pwm_duty(MotorB_P,-Duty_R);
    }
}
