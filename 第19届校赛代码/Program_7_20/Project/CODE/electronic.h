#ifndef __ELECTRONIC__H_
#define __ELECTRONIC__H_

#define  ADC0 ADC_P00//×óºá Êú Ð±
#define  ADC1 ADC_P01
#define  ADC2 ADC_P06

#define  ADC3 ADC_P15//ÓÒÐ± Êú ºá
#define  ADC4 ADC_P14
#define  ADC5 ADC_P11



void ADC_6_road_init(void);
void InductorNormal(void);
uint16 adc_mean_filter_convert(ADCN_enum vadc_chn);

#endif
/*
#define  ADC0 ADC_P00//×óºá Êú Ð±
#define  ADC1 ADC_P01
#define  ADC2 ADC_P05

#define  ADC3 ADC_P15//ÓÒÐ± Êú ºá
#define  ADC4 ADC_P14
#define  ADC5 ADC_P11
*/
