/*
 * voltmeter.h
 *
 * Created: 24/07/2013 13:27:13
 *  Author: fabio
 */ 


#ifndef VOLTMETER_H_
#define VOLTMETER_H_


void voltmeter_init(void);
uint16_t voltmeter_getValue(void);
uint16_t thermometer_getValue(void);

#define BATTERY_ADC_OVERSAMPLING 100

#endif /* VOLTMETER_H_ */