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
#include "twi_master.h"
#include <stdio.h>

#include "conf_board.h"
#include "globals.h"
#include <conf_usart_serial.h>
#include "config/conf_usart_serial.h"

#include "devices/SENS-IT/sens-it.h"

volatile char g_szBuf[64];


void sens_it_init(void)
{
	static usart_rs232_options_t RS485_SERIAL_OPTIONS = {
		.baudrate = USART_SENSIT_BAUDRATE,
		.charlength = USART_CHAR_LENGTH,
		.paritytype = USART_PARITY,
		.stopbits = USART_STOP_BIT
	};
	sysclk_enable_module(SYSCLK_PORT_C,PR_USART0_bm);
	usart_serial_init(USART_SENSIT, &RS485_SERIAL_OPTIONS);
	usart_set_rx_interrupt_level(USART_SENSIT,USART_INT_LVL_LO); // Occhio alla priorità
	
	
}

void sens_it_get_sample(uint8_t address)
{
	char szBuf[128];
	uint32_t gas = 0, res = 0;
	int16_t temp = 0, fan = 0, sign=0;
	uint8_t error_check = 0, target_gas [2], idx = 0;
	debug_string(NORMAL,PSTR("\r\nSending &D command\r\n"),true);
	usart_rx_disable(USART_SENSIT);
	gpio_set_pin_high(SENSIT_USART_TX_ENABLE);
	delay_ms(1);
	usart_putchar(USART_SENSIT,'&');
	delay_ms(500);
	usart_putchar(USART_SENSIT,address);
	delay_ms(1);
	gpio_set_pin_low(SENSIT_USART_TX_ENABLE);
	usart_rx_enable(USART_SENSIT);
	delay_s(5);
	
	uint8_t i=0, field=0;
	uint8_t flag=1;
	while(flag)
	{
		
		const char c=g_szBuf[i++];
		//usart_putchar(USART_DEBUG,c);
		if (c == ';')
		{
			field++;
		}		else{			if (c == '.')				continue;			if(field==2)			{				target_gas[idx++] = c;			}			if(field==3)			{				gas=gas*10+c-48;			}			else if(field==4)			{				res=res*10+c-48;			}			else if(field==5)			{				if(c=='+')				sign=1;				else if(c=='-')				sign=-1;				else				temp=temp*10+c-48;			}			else if(field==6)			{				fan=fan*10+c-48;			}			else if(field==7)			{				error_check=error_check*10+c-48;			}			if(c=='\r' || c=='\n')			{				temp *=sign;				flag =0;			}		}			}
	sprintf_P(szBuf,PSTR("\r\nfield = %u\ti = %u\tval=%u\r\n"),field,i,gas);	debug_string(NORMAL,szBuf,false);
}

static bool usartc_USARTC0_RX_CBuffer_Complete(void)
{
	static uint8_t idx=0;	USART_t * const ad = USART_SENSIT;
	const uint8_t dt = ad->DATA;
	if(dt=='#')
		idx=0;
	usart_putchar(USART_DEBUG,dt);
	g_szBuf[idx++]=dt;
}

ISR(USARTC0_RXC_vect)
{
	usartc_USARTC0_RX_CBuffer_Complete();
}