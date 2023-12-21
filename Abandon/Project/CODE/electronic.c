#include "headfile.h"
#include "electronic.h"

#define count 10

//采样512个点
//差比和加权系数
float weightA=1, weightB=1;
float Limit=1;//限幅系数
float  electro_error=0;
int8 Turn_flag=0;
int16 L0=0,L1=0,L2=0,R0=0,R1=0,R2=0;
int16 MagneticField=0;//磁场整体强度
int16 left = 0,middle = 0, right = 0;  // 电感偏移量
int16 LnowADC[6]={0,0,0,0,0,0};           // 电感当前ADC数值
int16 ad_max_heng,ad_max_shu,ad_max_xie; 						//每个新赛道都需要重新标定最大值和最小值
int16 ad_min_heng,ad_min_shu,ad_min_xie;  

int16 ADC_DATA_CH0[12];
int16 ADC_DATA_CH5[12],ADC_DATA_CH2[12];

// ADC_DATA_CH1[12],ADC_DATA_CH2[12]	,ADC_DATA_CH3[12],,ADC_DATA_CH5[12];

void adc_data_convert(void);
uint16 adc_filter(int16 *a);


/**************6路电磁初始化函数*******
 * 函数名称  ADC_6_road_init
 * 入口参数  void
 * 输出参数  void
 */
void ADC_6_road_init()
{
    adc_init(ADC0, ADC_SYSclk_DIV_2);
    adc_init(ADC1, ADC_SYSclk_DIV_2);
    adc_init(ADC2, ADC_SYSclk_DIV_2);
    adc_init(ADC3, ADC_SYSclk_DIV_2);
		adc_init(ADC4, ADC_SYSclk_DIV_2);
		adc_init(ADC5, ADC_SYSclk_DIV_2);
}
/*************************************************************************
 *  函数名称：void InductorNormal(void)
 *  功能说明：采集电感电压并归一化；
 *  参数说明：无 ,
 *  函数返回：无
 *  修改时间：2020年11月18日
 *  备    注：   注意要先标定运放的放大倍数
 *************************************************************************/
void InductorNormal(void)
{
//			LnowADC[0] =  adc_mean_filter_convert(ADC0) ; //左横
//			LnowADC[1] =  adc_mean_filter_convert(ADC1);  //左竖
//			LnowADC[2] =  adc_mean_filter_convert(ADC2);  //左斜
//			LnowADC[3] =  adc_mean_filter_convert(ADC3);  //右斜
//			LnowADC[4] =  adc_mean_filter_convert(ADC4);  //右竖
//			LnowADC[5] =  adc_mean_filter_convert(ADC5);  //右横
	
	  adc_data_convert();
	
	  LnowADC[0] =  adc_filter(ADC_DATA_CH0);
	  LnowADC[5] =  adc_filter(ADC_DATA_CH5);
		LnowADC[2] =  adc_filter(ADC_DATA_CH2);
//		LnowADC[1] =  adc_filter(ADC_DATA_CH1);
//	  LnowADC[4] =  adc_filter(ADC_DATA_CH4);
	
//		//归一化
//			L0 = (LnowADC[0] - ad_min_heng) * 100 / (ad_max_heng - ad_min_heng); 		//用vofa打印最大值最小值 好看最大值和最小值
//			L1 = (LnowADC[1] - ad_min_shu) * 100 / (ad_max_shu - ad_min_shu); 
//			L2 = (LnowADC[2] - ad_min_xie) * 100 / (ad_max_xie - ad_min_xie); 
//			R0 = (LnowADC[3] - ad_min_xie) * 100 / (ad_max_xie - ad_min_xie); 
//			R1 = (LnowADC[4] - ad_min_shu) * 100 / (ad_max_shu - ad_min_shu); 
//			R2 = (LnowADC[5] - ad_min_heng) * 100 / (ad_max_heng - ad_min_heng); 
	
      MagneticField= LnowADC[0]+LnowADC[5];//磁场整体强度//差比和加权
//			electro_error=
//            (weightA*(LnowADC[0] - LnowADC[5])+weightB*(LnowADC[1] - LnowADC[4]))*Limit
//            /
//            (weightA*(LnowADC[0] + LnowADC[5])+weightB*(LnowADC[1] + LnowADC[4]));
		electro_error=
            (weightA*(LnowADC[0] - LnowADC[5]))*Limit
            /
            (weightA*(LnowADC[0] + LnowADC[5])+1);
			electro_error*=100;
		Turn_flag=1;
	}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ADC 均值滤波转换
// 参数说明     ch              选择 ADC 通道 (详见 zf_driver_adc.h 中枚举 adc_channel_enum 定义)
// 参数说明     count           均值滤波次数
// 返回参数     uint16          转换的 ADC 值
// 使用示例     adc_mean_filter_convert(ADC1_CH0_A0, 5);                        // 采集5次去掉最大和最小值 然后返回平均值
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_mean_filter_convert(ADCN_enum vadc_chn)
{
    uint8 xdata i;
		int16 xdata a[count+2],filter_temp,out=0,j;
	//采集电感
	for(i=0;i<count+2;i++)
	{
	a[i] = adc_once(vadc_chn, ADC_10BIT);
	}
	//冒泡排列
	for(j = 0; j < count+1; j++)
    {
        for(i = 0; i < count+1 - j; i++)
        {
            if(a[i] > a[i + 1])
            {
                filter_temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = filter_temp;
            }
        }
    }
	//去掉最大以及最小值
    for(i = 1; i < count+1; i++)
    {
      out += a[i];
    } 
	//取平均值
    out = out / count ;
    return (uint16)out;
}




void adc_data_convert(void)
{
	  uint8 xdata i;
	  for(i=0;i<12;i++)
	{
		ADC_DATA_CH0[i] = adc_once(ADC0,ADC_10BIT);
//		ADC_DATA_CH1[i] = adc_once(ADC1,ADC_10BIT);
		ADC_DATA_CH2[i] = adc_once(ADC2,ADC_10BIT);
//		ADC_DATA_CH2[i] = adc_once(ADC2,ADC_10BIT);
//		ADC_DATA_CH3[i] = adc_once(ADC3,ADC_10BIT);
//		ADC_DATA_CH4[i] = adc_once(ADC4,ADC_10BIT);
		ADC_DATA_CH5[i] = adc_once(ADC5,ADC_10BIT);
	}
}


uint16 adc_filter(int16 *a)
{
    uint8 xdata i;
		int16 xdata out=0;
	  
	  for(i = 0; i < 12; i++)
    {
      out += a[i];
    }
	  
    out = out / 12 ;
    return (int16)out;
}
