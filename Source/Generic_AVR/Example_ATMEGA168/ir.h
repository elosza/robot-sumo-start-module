/*
 * ir.h
 *
 *  Created on: 25 dec 2009
 *      Author: benjamin
 *
 * Copyright (c) 2009 Benjamin Vedder
 *
 * Everything in this driver is implemented using the information
 * available at this site:
 *
 * http://www.sbprojects.com/knowledge/ir/ir.htm
 *
 * This driver has been tested with several different remote controls and
 * everything seems to work so far.
 *
 * How to use the driver (tested on atmega168):
 *
 * Connect the ir receiver to the int0-pin (or another dedicated interrupt pin) and you are done with hw.
 *
 * Add this to your code
 *
 * #include "ir.h"
 *
 * Init the driver:
 * ir_init();
 *
 * Set the i-flag
 * sei();
 *
 * If something is in the buffer:
 *
 * if (ir_has_next()) {
 *
 * 		IRDATA ir;
 * 		ir_get_next(&ir);
 *
 * 		command = ir.command;
 * 		address = ir.address;
 *
 * }
 *
 *
 * The driver uses timer0 or timer1 or timer2 (see HW part) to keep track of the time for all protocols.
 *
 */

#ifndef IR_H_
#define IR_H_

/*
 * Proocol
 */
//#define IR_NEC_PROTOCOL
//#define IR_JVC_PROTOCOL
#define IR_RC5_PROTOCOL
//#define IR_ATLAS_PROTOCOL

/*
 * HW-dependent stuff. Change these macros if your hardware differs.
 */

/*
 * XMEGA32A4 PB1, TCC0
 */
//#define IR_INT_EN() PORTB_INTCTRL |= PORT_INT0LVL_MED_gc; PORTB_INT0MASK |= _BV(1)
//
//#ifndef IR_RC5_PROTOCOL
//#define IR_FALLING_INT()	PORTB_PIN1CTRL = 0b00011010
//#define IR_RISING_INT()	PORTB_PIN1CTRL = 0b00011001
//#endif
//
//#define IR_ANY_EDGE_INT()	PORTB_PIN1CTRL = 0b00011000
//
//#define IR_CNT_PRESCALE_SET()	TCC0_CTRLA = TC_CLKSEL_DIV64_gc;	// Prescale 64
//#define IR_CNT TCC0_CNT
//#define IR_CNT_OVF_EN()	TCC0_INTCTRLA = 0x03; TCC0_PER = 255
//
//#define IR_PIN_ISR PORTB_INT0_vect
//#define IR_CNT_ISR TCC0_OVF_vect
//
//#define IR_GET_EDGE()	(PORTB_IN & _BV(1))
//#define IR_EDGE_LOW()	!IR_GET_EDGE()
//#define IR_EDGE_HIGH()	IR_GET_EDGE()

/*
 * ATMega644 int0
 */
//#define IR_INT_EN() EIMSK |= _BV(INT0)
//
//#ifndef IR_RC5_PROTOCOL
//#define IR_FALLING_INT()	EICRA |= _BV(ISC01); EICRA &= ~_BV(ISC00)
//#define IR_RISING_INT()	EICRA |= _BV(ISC00) | _BV(ISC01)
//#endif
//
//#define IR_ANY_EDGE_INT()	EICRA |= _BV(ISC00); EICRA &= ~_BV(ISC01)
//
//#define IR_CNT_PRESCALE_SET()	TCCR0B |= _BV(CS00) | _BV(CS01)	// Prescale 64
//#define IR_CNT TCNT0
//#define IR_CNT_OVF_EN()	TIMSK0 |= _BV(TOIE0)
//
//#define IR_PIN_ISR INT0_vect
//#define IR_CNT_ISR TIMER0_OVF_vect
//
//#define IR_GET_EDGE()	(PIND & _BV(2))
//#define IR_EDGE_LOW()	!IR_GET_EDGE()
//#define IR_EDGE_HIGH()	IR_GET_EDGE()

/*
 * ATMega 168 int0, timer0
 */
//#define IR_INT_EN() EIMSK |= _BV(INT0)
//
//#ifndef IR_RC5_PROTOCOL
//#define IR_FALLING_INT()	EICRA |= _BV(ISC01); EICRA &= ~_BV(ISC00)
//#define IR_RISING_INT()	EICRA |= _BV(ISC00) | _BV(ISC01)
//#endif
//
//#define IR_ANY_EDGE_INT()	EICRA |= _BV(ISC00); EICRA &= ~_BV(ISC01)
//
//#define IR_CNT_PRESCALE_SET()	TCCR0B |= _BV(CS00) | _BV(CS01)	// Prescale 64
//#define IR_CNT TCNT0
//#define IR_CNT_OVF_EN()	TIMSK0 |= _BV(TOIE0)
//
//#define IR_PIN_ISR INT0_vect
//#define IR_CNT_ISR TIMER0_OVF_vect
//
//#define IR_GET_EDGE()	(PIND & _BV(2))
//#define IR_EDGE_LOW()	!IR_GET_EDGE()
//#define IR_EDGE_HIGH()	IR_GET_EDGE()

/*
 * ATMega 168 int0, timer2
 */
//#define IR_INT_EN() EIMSK |= _BV(INT0)
//
//#ifndef IR_RC5_PROTOCOL
//#define IR_FALLING_INT()	EICRA |= _BV(ISC01); EICRA &= ~_BV(ISC00)
//#define IR_RISING_INT()	EICRA |= _BV(ISC00) | _BV(ISC01)
//#endif
//
//#define IR_ANY_EDGE_INT()	EICRA |= _BV(ISC00); EICRA &= ~_BV(ISC01)
//
//#define IR_CNT_PRESCALE_SET()	TCCR2B |= _BV(CS22)	// Prescale 64
//#define IR_CNT TCNT2
//#define IR_CNT_OVF_EN()	TIMSK2 |= _BV(TOIE2)
//
//#define IR_PIN_ISR INT0_vect
//#define IR_CNT_ISR TIMER2_OVF_vect
//
//#define IR_GET_EDGE()	(PIND & _BV(2))
//#define IR_EDGE_LOW()	!IR_GET_EDGE()
//#define IR_EDGE_HIGH()	IR_GET_EDGE()

/*
 * Introbot09 (atmega168)
 * IR-sense1 (PB7, RC5 only)
 * Timer2
 * TESTED, should work.
 */
#define IR_INT_EN() PCICR |= _BV(PCIE0)

#ifndef IR_RC5_PROTOCOL
#error *** Only RC5 protocol supported on this hardware (interrupt pin) ***
//#define IR_FALLING_INT()	EICRA |= _BV(ISC01); EICRA &= ~_BV(ISC00)
//#define IR_RISING_INT()	EICRA |= _BV(ISC00) | _BV(ISC01)
#endif

#define IR_ANY_EDGE_INT()	PCMSK0 |= _BV(PCINT7);

#define IR_CNT_PRESCALE_SET()	TCCR2B |= _BV(CS22)	// Prescale 64
#define IR_CNT TCNT2
#define IR_CNT_OVF_EN()	TIMSK2 |= _BV(TOIE2)

#define IR_PIN_ISR PCINT0_vect
#define IR_CNT_ISR TIMER2_OVF_vect

#define IR_GET_EDGE()	(PINB & _BV(7))
#define IR_EDGE_LOW()	!IR_GET_EDGE()
#define IR_EDGE_HIGH()	IR_GET_EDGE()

/*
 * ATMega2560 int3
 */
//#define IR_INT_EN() EIMSK |= _BV(INT3)
//#define IR_FALLING_INT()	EICRA |= _BV(ISC31); EICRA &= ~_BV(ISC30)
//#define IR_RISING_INT()	EICRA |= _BV(ISC30) | _BV(ISC31)
//#define IR_ANY_EDGE_INT()	EICRA |= _BV(ISC30); EICRA &= ~_BV(ISC31)
//
//#define IR_CNT_PRESCALE_SET()	TCCR0B |= _BV(CS00) | _BV(CS01)	// Prescale 64
//#define IR_CNT TCNT0
//#define IR_CNT_OVF_EN()	TIMSK0 |= _BV(TOIE0)
//
//#define IR_PIN_ISR INT3_vect
//#define IR_CNT_ISR TIMER0_OVF_vect
//
//#define IR_GET_EDGE()	(PIND & _BV(3))
//#define IR_EDGE_LOW()	!IR_GET_EDGE()
//#define IR_EDGE_HIGH()	IR_GET_EDGE()

// ------------- END HW-stuff -------------------- //

/*
 * Debugging
 */
#define IR_DBG_EN	0

/*
 * Buffer size
 */
#define IR_BUFFER_SIZE 20

#ifdef	IR_ATLAS_PROTOCOL

#define IR_PACKET_LEN	6

typedef struct {
	unsigned char data[IR_PACKET_LEN];
} IRDATA;

#if IR_DBG_EN
extern volatile unsigned int 	cnt_start,
								cnt_space,
								cnt_data1,
								cnt_break,
								cnt_rep_start,
								cnt_rep_space,
								cnt_data2;

extern volatile signed char status;

#endif

/*
 * Functions
 */
void ir_init(void);
signed char ir_has_next(void);
void ir_get_next(IRDATA *data);

#endif


#ifdef	IR_NEC_PROTOCOL


typedef struct {
	unsigned char address_low;
	unsigned char address_high;
	unsigned char command;
} IRDATA;

#if IR_DBG_EN
extern volatile unsigned int 	cnt_start,
								cnt_space,
								cnt_addr1,
								cnt_addr2,
								cnt_cmd1,
								cnt_cmd2;
#endif

/*
 * Macros
 */
#define ir_has_extended_address(ir)	((ir.address_low ^ ir.address_high) != 0xFF)

/*
 * Functions
 */
void ir_init(void);
signed char ir_has_next(void);
void ir_get_next(IRDATA *data);
unsigned char ir_get_repeats(void);

#endif

#ifdef	IR_JVC_PROTOCOL

typedef struct {
	unsigned char address_low;
	unsigned char command;
} IRDATA;

#if IR_DBG_EN
extern volatile unsigned int 	cnt_start,
								cnt_space,
								cnt_addr,
								cnt_cmd;
#endif

/*
 * Functions
 */
void ir_init(void);
signed char ir_has_next(void);
void ir_get_next(IRDATA *data);
unsigned char ir_get_repeats(void);

#endif

#ifdef	IR_RC5_PROTOCOL

// RC5 specific settings
#define IR_RC5_DISABLE_REPEATS	1

typedef struct {
	unsigned char address_low;
	unsigned char command;
} IRDATA;

#if IR_DBG_EN
extern volatile unsigned int 	cnt_start2,
								cnt_toggle,
								cnt_addr,
								cnt_cmd;
#endif

/*
 * Functions
 */
void ir_init();
signed char ir_has_next();
void ir_get_next(IRDATA *data);
unsigned char ir_get_repeats();
void ir_set_data_handler(void(*func)(IRDATA *data));
void ir_remove_data_handler();

#endif

/*
 * RC5 protocol standard addresses and commands
 */
#define RC5_ADR_TV1				0x00
#define RC5_ADR_TV2				0x01
#define RC5_ADR_TELETEXT		0x02
#define RC5_ADR_VIDEO			0x03
#define RC5_ADR_LV1				0x04
#define RC5_ADR_VCR1			0x05
#define RC5_ADR_VCR2			0x06
#define RC5_ADR_EXPERIMENTAL	0x07
#define RC5_ADR_SAT1			0x08
#define RC5_ADR_CAMERA			0x09
#define RC5_ADR_SAT2			0x0A
#define RC5_ADR_CDV				0x0C
#define RC5_ADR_CAMCORDER		0x0D
#define RC5_ADR_PREAMP			0x10
#define RC5_ADR_TUNER			0x11
#define RC5_ADR_RECORDER1		0x12
#define RC5_ADR_PREAMP2			0x13
#define RC5_ADR_CDPLAYER		0x14
#define RC5_ADR_PHONO			0x15
#define RC5_ADR_SATA			0x16
#define RC5_ADR_RECORDER2		0x17
#define RC5_ADR_CDR				0x1A
#define RC5_ADR_LIGHTING		0x1D
#define RC5_ADR_LIGHTING2		0x1E
#define RC5_ADR_PHONE			0x1F

#define RC5_CMD_0				0x00
#define RC5_CMD_1				0x01
#define RC5_CMD_2				0x02
#define RC5_CMD_3				0x03
#define RC5_CMD_4				0x04
#define RC5_CMD_5				0x05
#define RC5_CMD_6				0x06
#define RC5_CMD_7				0x07
#define RC5_CMD_8				0x08
#define RC5_CMD_9				0x09
#define RC5_CMD_MIN				0x0A
#define RC5_CMD_STANDBY			0x0C
#define RC5_CMD_MUTE			0x0D
#define RC5_CMD_VPLUS			0x10
#define RC5_CMD_VMIN			0x11
#define RC5_CMD_BPLUS			0x12
#define RC5_CMD_BMIN			0x13
#define RC5_CMD_PPLUS			0x20
#define RC5_CMD_PMIN			0x21
#define RC5_CMD_FRWD			0x32
#define RC5_CMD_FFWD			0x34
#define RC5_CMD_PLAY			0x35
#define RC5_CMD_STOP			0x36
#define RC5_CMD_RECORDING		0x37

/*
 * JVC observed commands
 */
#define JVC_CMD_10				0x2A
#define JVC_CMD_1				0x21
#define JVC_CMD_2				0x22
#define JVC_CMD_3				0x23
#define JVC_CMD_4				0x24
#define JVC_CMD_5				0x25
#define JVC_CMD_6				0x26
#define JVC_CMD_7				0x27
#define JVC_CMD_8				0x28
#define JVC_CMD_9				0x29
#define JVC_CMD_UP				0x1E
#define JVC_CMD_DOWN			0x1F
#define JVC_CMD_STANDBY			0x17
#define JVC_CMD_PREV			0x18
#define JVC_CMD_NEXT			0x19


#endif /* IR_H_ */





