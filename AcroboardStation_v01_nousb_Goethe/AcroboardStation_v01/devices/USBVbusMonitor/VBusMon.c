/*
 * VBusMon.c
 *
 * Created: 6/23/2013 12:49:35 AM
 *  Author: fabio
 */ 

#include <asf.h>
#include "VBusMon.h"
#include "devices/statusled/status_led.h"
#include "globals.h"


void VBusMon_init(void)
{
	//PORT_ConfigureInterrupt0( &PORTD, PORT_INT0LVL_LO_gc, 0x20 );
	
}

void VBusMon_check(void)
{
	//static volatile uint8_t r = 0;
	//if(1==r) return;
	//r = 1;
	//if(ioport_pin_is_low(USB_PROBE_PIN)) {
		//vbus_action(false);
		//udc_stop();
		//irqflags_t flags;
//
		//flags = cpu_irq_save();
		//OSC.DFLLCTRL = 2;
		//DFLLRC32M.CTRL = 1;
		//cpu_irq_restore(flags);
//
		//statusled_blink(2);
		//debug_string(VERBOSE,PSTR("[EVENT] USB off\r\n"),true);
	//} else {
		//irqflags_t flags;
//
		//flags = cpu_irq_save();
		//
		//OSC.DFLLCTRL = 4;
		//DFLLRC32M.CTRL = 1;
		//DFLLRC32M.COMP1 = 0x80;
		//DFLLRC32M.COMP2 = 0xBB;
		//cpu_irq_restore(flags);
//
		//udc_start();
		//vbus_action(true);
		//statusled_blink(2);
		//debug_string(VERBOSE,PSTR("[EVENT] USB on\r\n"),true);
	//}
	//r=0;
}

/*
ISR(PORTD_INT0_vect)
{
	VBusMon_check();
}
*/
