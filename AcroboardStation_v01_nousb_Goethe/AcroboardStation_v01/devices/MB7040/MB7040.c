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
#include <asf.h>
#include <stdio.h>
#include "board.h"
//#include "sysclk.h"
#include "twi_master.h"
//#include "led.h"
#include <stdio.h>

#include "conf_board.h"
#include "MB7040.h"
#include "delay.h"
#include "globals.h"

#include "devices/MB7040/MB7040.h"


#define MB7040_TWI_READ_ADDR  0xE1
#define MB7040_TWI_WRITE_ADDR  0xE0

#define MB7040_TAKE_RANGE_COMMAND 0x51
#define MB7040_I2C_ADDR1_COMMAND 0xAA
#define MB7040_I2C_ADDR1_COMMAND 0xA5

int MB7040_Init(void)
{
	// TWI master initialization options.
	
	twi_master_options_t opt = {
		.speed =10000,					//10kHz ?
		.chip  = TWI_MASTER_ADDRESS,
	};
	
	// Initialize the TWI master driver.
	
	return twi_master_setup(AUX_TWI_PORT, &opt);
}

static status_code_t MB7040_internalWrite(twi_package_t * ppak)
{
	
	const status_code_t r = twi_master_write(AUX_TWI_PORT, ppak);
	switch(r) {
		case TWI_SUCCESS:
		debug_string(VERBOSE,PSTR("[MB7040_internalWrite] Write Succeeded\r\n"),true);
		return r;
		break;
		case ERR_IO_ERROR:
		debug_string(NORMAL,PSTR("[MB7040_internalWrite] Write Failed: ERR_IO_ERROR\r\n"),true);
		break;
		case ERR_FLUSHED:
		debug_string(NORMAL,PSTR("[MB7040_internalWrite] Write Failed: ERR_FLUSHED\r\n"),true);
		break;
		case ERR_TIMEOUT:
		debug_string(NORMAL,PSTR("[MB7040_internalWrite] Write Failed: ERR_TIMEOUT\r\n"),true);
		break;
		case ERR_BAD_DATA:
		debug_string(NORMAL,PSTR("[MB7040_internalWrite] Write Failed: ERR_BAD_DATA\r\n"),true);
		break;
		case ERR_PROTOCOL:
		debug_string(NORMAL,PSTR("[MB7040_internalWrite] Write Failed: ERR_PROTOCOL\r\n"),true);
		break;
		case ERR_UNSUPPORTED_DEV:
		debug_string(NORMAL,PSTR("[MB7040_internalWrite] Write Failed: ERR_UNSUPPORTED_DEV\r\n"),true);
		break;
		case ERR_NO_MEMORY:
		debug_string(NORMAL,PSTR("[MB7040_internalWrite] Write Failed: ERR_NO_MEMORY\r\n"),true);
		break;
		case ERR_INVALID_ARG:
		debug_string(NORMAL,PSTR("[MB7040_internalWrite] Write Failed: ERR_INVALID_ARG\r\n"),true);
		break;
		case ERR_BAD_ADDRESS:
		debug_string(NORMAL,PSTR("[MB7040_internalWrite] Write Failed: ERR_BAD_ADDRESS\r\n"),true);
		break;
		case ERR_BUSY:
		debug_string(NORMAL,PSTR("[MB7040_internalWrite] Write Failed: ERR_BUSY\r\n"),true);
		break;
		case ERR_BAD_FORMAT:
		debug_string(NORMAL,PSTR("[MB7040_internalWrite] Write Failed: ERR_BAD_FORMAT\r\n"),true);
		break;
		default:
		debug_string(NORMAL,PSTR("[MB7040_internalWrite] Write Failed: UNKONWN ERROR\r\n"),true);
	}
	return r;
}

static status_code_t MB7040_internalRead(twi_package_t * ppak)
{

	const status_code_t r = twi_master_read(AUX_TWI_PORT, ppak);
	switch(r) {
		case TWI_SUCCESS:
		//debug_string(NORMAL,PSTR("READ Succeeded\r\n"));
		return r;
		break;
		case ERR_IO_ERROR:
		debug_string(NORMAL,PSTR("[MB7040_internalRead] READ Failed: ERR_IO_ERROR\r\n"),true);
		break;
		case ERR_FLUSHED:
		debug_string(NORMAL,PSTR("[MB7040_internalRead] READ  Failed: ERR_FLUSHED\r\n"),true);
		break;
		case ERR_TIMEOUT:
		debug_string(NORMAL,PSTR("[MB7040_internalRead] READ  Failed: ERR_TIMEOUT\r\n"),true);
		break;
		case ERR_BAD_DATA:
		debug_string(NORMAL,PSTR("[MB7040_internalRead] READ  Failed: ERR_BAD_DATA\r\n"),true);
		break;
		case ERR_PROTOCOL:
		debug_string(NORMAL,PSTR("[MB7040_internalRead] READ  Failed: ERR_PROTOCOL\r\n"),true);
		break;
		case ERR_UNSUPPORTED_DEV:
		debug_string(NORMAL,PSTR("[MB7040_internalRead] READ  Failed: ERR_UNSUPPORTED_DEV\r\n"),true);
		break;
		case ERR_NO_MEMORY:
		debug_string(NORMAL,PSTR("[MB7040_internalRead] READ  Failed: ERR_NO_MEMORY\r\n"),true);
		break;
		case ERR_INVALID_ARG:
		debug_string(NORMAL,PSTR("[MB7040_internalRead] READ  Failed: ERR_INVALID_ARG\r\n"),true);
		break;
		case ERR_BAD_ADDRESS:
		debug_string(NORMAL,PSTR("[MB7040_internalRead] READ  Failed: ERR_BAD_ADDRESS\r\n"),true);
		break;
		case ERR_BUSY:
		debug_string(NORMAL,PSTR("[MB7040_internalRead] READ  Failed: ERR_BUSY\r\n"),true);
		break;
		case ERR_BAD_FORMAT:
		debug_string(NORMAL,PSTR("[MB7040_internalRead] READ  Failed: ERR_BAD_FORMAT\r\n"),true);
		break;
		default:
		debug_string(NORMAL,PSTR("[MB7040_internalRead] READ  Failed: UNKONWN ERROR\r\n"),true);

	}
	return r;
}

status_code_t MB7040_TriggerReadRange(MB7040VAL * val) // Occhio all'argomento
{
	uint8_t cmd_buff = MB7040_TAKE_RANGE_COMMAND;

	debug_string(VERBOSE,PSTR("[MB7040_TriggerReadRange] IN\r\n"),true);
	
	twi_package_t pak = {
		.addr[0]	  = cmd_buff,
		.addr_length  = 1,
		.chip         = MB7040_TWI_READ_ADDR,
		.buffer       = (void *)val,
		.length       = 2
	};
	
	return MB7040_internalRead(&pak);
}

void mb7040_read_data(uint16_t * ps)
{
	MB7040VAL range, range2;
	
	MB7040_TriggerReadRange(&range);
	
	range2.bval[1] = range.bval[0];
	range2.bval[0] = range.bval[1];
	
	delay_ms(5);

	char szBUF[64];
	sprintf_P(szBUF,PSTR("Range: %u\r\n"),range2.wval);
	debug_string(NORMAL,szBUF,false);
}