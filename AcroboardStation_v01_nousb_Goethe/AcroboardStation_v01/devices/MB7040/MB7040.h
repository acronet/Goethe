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



#ifndef MB7040_H_
#define MB7040_H_

typedef union {
	int16_t wval;
	int8_t bval[2];
} MB7040VAL;

int MB7040_Init(void);
status_code_t MB7040_TriggerReadRange(MB7040VAL * val);
void mb7040_read_data(uint16_t * ps);

#endif /* MB7040_H_ */