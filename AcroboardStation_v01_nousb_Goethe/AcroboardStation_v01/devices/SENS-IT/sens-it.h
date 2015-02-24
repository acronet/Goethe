/*
 * ACRONET Project
 * http://www.acronet.cc
 *
 * Copyright ( C ) 2014 Acrotec srl
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the EUPL v.1.1 license.  See http://ec.europa.eu/idabc/eupl.html for details.
 */ 

#ifndef SENS_IT_H_
#define SENS_IT_H_

typedef struct {
	uint32_t gas;				// gas measurement
	uint32_t res;				// resistence
	int16_t temp;				// temperature
	int16_t fan;				// fan (RPS)
	uint8_t error_check;	// check for errors: error if != 0
	uint8_t target_gas [2];		// the first character is the sensor address (A-Z) and the second
								// specifies the target gas: 1=CO - 2=NO2 - 3=O3 - 4=CH4 - 5=NOx - 6=C6H6
} SENSIT_STATS;

void sens_it_init(void);
void sens_it_get_sample(uint8_t address);

#endif /* SENS_IT_H_ */