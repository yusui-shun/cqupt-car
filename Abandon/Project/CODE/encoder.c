#include "headfile.h"
#include "encoder.h"
/*extern int16 EncoderGetSpeed;
int16 p=0;

void encoder_init(void)
{
	ctimer_count_init(CTIM3_P04);
	//��ʱ��1��ʼ�� ��ʱ���ж� ��ȡ�ٶ�ֵ
	TM1PS = 350-1;     //35m/350 = 10e5   				35 000 000  35000   1000
	TMOD = 0x00; //ģʽ 0
	TL1 = 0xEF;    				//55535  ��10000����   //0.1s
	TH1 = 0xD8;
	TR1 = 1; //������ʱ��
	ET1 = 1; //ʹ�ܶ�ʱ���ж�
	EA = 1; 
}

int16 encoder_get(CTIMN_enum pin)
{
	uint16 t;
	t=ctimer_count_read(pin);
	ctimer_count_clean(pin);
	return t;
}

void TM1_Isr() interrupt 3   //��ʱ��1���ж϶�ȡ�ٶ�
{
	TL1 = 0xEF;    
	TH1 = 0xD8;
	EncoderGetSpeed = encoder_get();
//	pid_motor.ActualValue = (uint16) (PWMA_CNTRH << 8) | PWMA_CNTRL; //��ȡ��ǰ��������ֵ
//	Exp_Val = pid_motor.ActualValue + PID_Control_Inc(&pid_motor);   //����ֵ��������Ŀ��ֵ��										
	//pwm.....(Exp_Val); //����ֵת����ռ�ձ� 
//	PWMB_CNTRH = 0; //���������������ֵ
//	PWMB_CNTRL = 0;	
} */