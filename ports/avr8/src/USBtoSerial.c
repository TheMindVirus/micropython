/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Paul Sokolovsky
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org

  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Main source file for the USBtoSerial project. This file contains the main tasks of
 *  the project and is responsible for the initial application hardware configuration.
 */

#ifndef _USB_SERIAL_H_
#define _USB_SERIAL_H_

// INCLUDES
#pragma region

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/power.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Descriptors.h"

// Add LUFA Extension in Microchip Studio

#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/Peripheral/Serial.h>
#include <LUFA/Drivers/Misc/RingBuffer.h>
#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Platform/Platform.h>

// Add MicroPython Source Tree to Include Search Path

#include "py/compile.h"
#include "py/runtime.h"
#include "py/gc.h"
#include "py/stackctrl.h"

// Link to MicroPython Source Statically without using Libraries

#include "py/compile.c"
#include "py/runtime.c"
#include "py/gc.c"
#include "py/stackctrl.c"

// What other C files actually get included by MicroPython?
/*
#include "py/scope.c"
//#include "py/emit.c"
//#include "py/asmbase.c"
//#include "py/persistentcode.c"

//#include "py/argcheck.c"
//#include "py/bc.c"
//#include "py/emitcommon.c"
//#include "py/emitnative.c"

#include "py/qstr.c"
#include "py/nlr.c"
#include "py/nlrsetjmp.c"
#include "py/mpstate.c" //mp_type_SyntaxError came up again
*/

// This is that list...

#include "py/mpstate.c"
#include "py/nlr.c"
#include "py/nlrx86.c" // ???
#include "py/nlrx64.c" // ???
#include "py/nlrthumb.c" // ???
#include "py/nlraarch64.c" // ???
#include "py/nlrpowerpc.c" // ???
#include "py/nlrxtensa.c" // ???
#include "py/nlrsetjmp.c"
#include "py/malloc.c"
#include "py/gc.c"
#include "py/pystack.c"
#include "py/qstr.c"
#include "py/vstr.c"
#include "py/mpprint.c"
#include "py/unicode.c"
#include "py/mpz.c"
#include "py/reader.c"
#include "py/lexer.c"
#include "py/parse.c"
#include "py/scope.c"
#include "py/compile.c"
#include "py/emitcommon.c"
#include "py/emitbc.c"
#include "py/asmbase.c"
#include "py/asmx64.c" // ???
#include "py/emitnx64.c" // ???
#include "py/asmx86.c" // ???
#include "py/emitnx86.c" // ???
#include "py/asmthumb.c" // ???
#include "py/emitnthumb.c" // ???
#include "py/emitinlinethumb.c" // ???
#include "py/asmarm.c" // ???
#include "py/emitnarm.c" // ???
#include "py/asmxtensa.c" // ???
#include "py/emitnxtensa.c" // ???
#include "py/emitinlinextensa.c" // ???
#include "py/emitnxtensawin.c" // ???
#include "py/formatfloat.c"
#include "py/parsenumbase.c"
#include "py/parsenum.c"
#include "py/emitglue.c"
#include "py/persistentcode.c"
#include "py/runtime.c"
#include "py/runtime_utils.c"
#include "py/scheduler.c"
#include "py/nativeglue.c"
#include "py/pairheap.c"
#include "py/ringbuf.c"
#include "py/stackctrl.c"
#include "py/argcheck.c"
#include "py/warning.c"
#include "py/profile.c"
#include "py/map.c"
#include "py/obj.c"
#include "py/objarray.c"
#include "py/objattrtuple.c"
#include "py/objbool.c"
#include "py/objboundmeth.c"
#include "py/objcell.c"
#include "py/objclosure.c"
#include "py/objcomplex.c"
#include "py/objdeque.c"
#include "py/objdict.c"
#include "py/objenumerate.c"
#include "py/objexcept.c"
#include "py/objfilter.c"
#include "py/objfloat.c"
#include "py/objfun.c"
#include "py/objgenerator.c"
#include "py/objgetitemiter.c"
#include "py/objint.c"
#include "py/objint_longlong.c"
#include "py/objint_mpz.c"
#include "py/objlist.c"
#include "py/objmap.c"
#include "py/objmodule.c"
#include "py/objobject.c"
#include "py/objpolyiter.c"
#include "py/objproperty.c"
#include "py/objnone.c"
#include "py/objnamedtuple.c"
#include "py/objrange.c"
#include "py/objreversed.c"
#include "py/objset.c"
#include "py/objsingleton.c"
#include "py/objslice.c"
#include "py/objstr.c"
#include "py/objstrunicode.c"
#include "py/objstringio.c"
#include "py/objtuple.c"
#include "py/objtype.c"
#include "py/objzip.c"
#include "py/opmethods.c"
#include "py/sequence.c"
#include "py/stream.c"
#include "py/binary.c"
#include "py/builtinimport.c"
#include "py/builtinevex.c"
#include "py/builtinhelp.c"
#include "py/modarray.c"
#include "py/modbuiltins.c"
#include "py/modcollections.c"
#include "py/modgc.c"
#include "py/modio.c"
#include "py/modmath.c"
#include "py/modcmath.c"
#include "py/modmicropython.c"
#include "py/modstruct.c"
#include "py/modsys.c"
#include "py/moduerrno.c"
#include "py/modthread.c"
#include "py/vm.c"
#include "py/bc.c"
#include "py/showbc.c"
#include "py/repl.c" // !!!
#include "py/smallint.c"
#include "py/frozenmod.c"

#include "extmod/moduasyncio.c"
#include "extmod/moductypes.c"
#include "extmod/modujson.c"
#include "extmod/modure.c"
#include "extmod/moduzlib.c"
#include "extmod/moduheapq.c"
#include "extmod/modutimeq.c"
#include "extmod/moduhashlib.c"
#include "extmod/moducryptolib.c"
#include "extmod/modubinascii.c"
#include "extmod/virtpin.c"
#include "extmod/machine_bitstream.c"
#include "extmod/machine_mem.c"
#include "extmod/machine_pinbase.c"
#include "extmod/machine_signal.c"
#include "extmod/machine_pulse.c"
#include "extmod/machine_pwm.c"
#include "extmod/machine_i2c.c"
#include "extmod/machine_spi.c"
#include "extmod/modbluetooth.c"
#include "extmod/modussl_axtls.c"
#include "extmod/modussl_mbedtls.c"
#include "extmod/moduplatform.c"
#include "extmod/modurandom.c"
#include "extmod/moduselect.c"
#include "extmod/moduwebsocket.c"
#include "extmod/modwebrepl.c"
#include "extmod/modframebuf.c"
#include "extmod/vfs.c"
#include "extmod/vfs_blockdev.c"
#include "extmod/vfs_reader.c"
#include "extmod/vfs_posix.c"
#include "extmod/vfs_posix_file.c"
#include "extmod/vfs_fat.c"
#include "extmod/vfs_fat_diskio.c"
#include "extmod/vfs_fat_file.c"
#include "extmod/vfs_lfs.c"
#include "extmod/utime_mphal.c"
#include "extmod/uos_dupterm.c"

#include "shared/libc/abort_.c"
#include "shared/libc/printf.c"
/*
#include "ports/unix/main.c"
#include "ports/unix/gccollect.c"
#include "ports/unix/unix_mphal.c"
#include "ports/unix/input.c"
#include "ports/unix/modmachine.c"
#include "ports/unix/modos.c"
#include "ports/unix/moduselect.c"
#include "ports/unix/alloc.c"
#include "ports/unix/coverage.c"
#include "ports/unix/fatfs_port.c"
*/

#include "ports/minimal/uart_core.c"

#include "shared/runtime/gchelper_generic.c"

#include "shared/timeutils/timeutils.c"

// Now the problem is redeclarations of gcc-native instructions and no avr8-specific instructions...

#pragma endregion
// DEFINITIONS
#pragma region

// LED mask for the library LED driver, to indicate that the USB interface is not ready.
#define LEDMASK_USB_NOTREADY      LEDS_LED1

// LED mask for the library LED driver, to indicate that the USB interface is enumerating.
#define LEDMASK_USB_ENUMERATING  (LEDS_LED2 | LEDS_LED3)

// LED mask for the library LED driver, to indicate that the USB interface is ready.
#define LEDMASK_USB_READY        (LEDS_LED2 | LEDS_LED4)

// LED mask for the library LED driver, to indicate that an error has occurred in the USB interface.
#define LEDMASK_USB_ERROR        (LEDS_LED1 | LEDS_LED3)

void SetupHardware(void);

void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);
void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo);

// Circular buffer to hold data from the host before it is sent to the device via the serial port.
static RingBuffer_t USBtoUSART_Buffer;

// Underlying data buffer for \ref USBtoUSART_Buffer, where the stored bytes are located.
static uint8_t      USBtoUSART_Buffer_Data[128];

// Circular buffer to hold data from the serial port before it is sent to the host.
static RingBuffer_t USARTtoUSB_Buffer;

// Underlying data buffer for \ref USARTtoUSB_Buffer, where the stored bytes are located.
static uint8_t      USARTtoUSB_Buffer_Data[128];

// LUFA CDC Class driver interface configuration and state information. This structure is
// passed to all CDC Class driver functions, so that multiple instances of the same class
// within a device can be differentiated from one another.
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
{
	.Config =
	{
		.ControlInterfaceNumber     = INTERFACE_ID_CDC_CCI,
		.DataINEndpoint             =
		{
			.Address                = CDC_TX_EPADDR,
			.Size                   = CDC_TXRX_EPSIZE,
			.Banks                  = 1,
		},
		.DataOUTEndpoint            =
		{
			.Address                = CDC_RX_EPADDR,
			.Size                   = CDC_TXRX_EPSIZE,
			.Banks                  = 1,
		},
		.NotificationEndpoint       =
		{
			.Address                = CDC_NOTIFICATION_EPADDR,
			.Size                   = CDC_NOTIFICATION_EPSIZE,
			.Banks                  = 1,
		},
	},
};

static char heap[16384];

#pragma endregion

#endif //_USB_SERIAL_H_

// UTILITIES
#pragma region

// MicroPython String Parsing and Execution Method
mp_obj_t execute_from_str(const char *str)
{
	nlr_buf_t nlr;
	if (nlr_push(&nlr) == 0)
	{
		qstr src_name = 1; // MP_QSTR_
		mp_lexer_t *lex = mp_lexer_new_from_str_len(src_name, str, strlen(str), false);
		mp_parse_tree_t pt = mp_parse(lex, MP_PARSE_FILE_INPUT);
		mp_obj_t module_fun = mp_compile(&pt, src_name, false);
		mp_call_function_0(module_fun);
		nlr_pop();
		return 0;
	}
	else { return (mp_obj_t)nlr.ret_val; } // Uncaught Exception
}

//uint mp_import_stat(const char *path) { return MP_IMPORT_STAT_NO_EXIST; } //lexer.h L205

void nlr_jump_fail(void* val) { printf("FATAL: uncaught NLR %p\n", val); exit(1); }
	
#pragma endregion
// INITIALISATION
#pragma region

// Configures the board hardware and chip peripherals for the demo's functionality.
void SetupHardware(void)
{
	#if (ARCH == ARCH_AVR8)
	    // Disable watchdog if enabled by bootloader/fuses
	    MCUSR &= ~(1 << WDRF);
	    wdt_disable();

	    // Disable clock division
	    clock_prescale_set(clock_div_1);
	#endif

	// Hardware Initialization
	LEDs_Init();
	USB_Init();
	
	// MicroPython Initialization
	mp_stack_set_limit(40000 * (sizeof(void *) / 4)); // Initialized stack limit
	gc_init(heap, heap + sizeof(heap)); // Initialize heap
	mp_init(); // Initialize interpreter

	const char str[] = "print('Hello world of easy embedding!')";
	if (execute_from_str(str)) { printf("Error\n"); }
}

#pragma endregion
// MAIN LOOP
#pragma region

// Main program entry point. This routine contains the overall program flow, including initial
// setup of all components and the main program loop.
int main(void)
{
	SetupHardware();

	RingBuffer_InitBuffer(&USBtoUSART_Buffer, USBtoUSART_Buffer_Data, sizeof(USBtoUSART_Buffer_Data));
	RingBuffer_InitBuffer(&USARTtoUSB_Buffer, USARTtoUSB_Buffer_Data, sizeof(USARTtoUSB_Buffer_Data));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		// Only try to read in bytes from the CDC interface if the transmit buffer is not full
		if (!(RingBuffer_IsFull(&USBtoUSART_Buffer)))
		{
			int16_t ReceivedByte = CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);

			// Store received byte into the USART transmit buffer
			if (!(ReceivedByte < 0))
			  RingBuffer_Insert(&USBtoUSART_Buffer, ReceivedByte);
		}
		
		// !!! INSERT MICROPYTHON/CIRCUITPYTHON SUPPORT HERE !!!
		
		
		
		// !!! CONTINUE !!!

		uint16_t BufferCount = RingBuffer_GetCount(&USARTtoUSB_Buffer);
		if (BufferCount)
		{
			Endpoint_SelectEndpoint(VirtualSerial_CDC_Interface.Config.DataINEndpoint.Address);

			// Check if a packet is already enqueued to the host - if so, we shouldn't try to send more data
			// until it completes as there is a chance nothing is listening and a lengthy timeout could occur
			if (Endpoint_IsINReady())
			{
				// Never send more than one bank size less one byte to the host at a time, so that we don't block
				// while a Zero Length Packet (ZLP) to terminate the transfer is sent if the host isn't listening
				uint8_t BytesToSend = MIN(BufferCount, (CDC_TXRX_EPSIZE - 1));

				// Read bytes from the USART receive buffer into the USB IN endpoint
				while (BytesToSend--)
				{
					// Try to send the next byte of data to the host, abort if there is an error without dequeuing
					if (CDC_Device_SendByte(&VirtualSerial_CDC_Interface, RingBuffer_Peek(&USARTtoUSB_Buffer)) != ENDPOINT_READYWAIT_NoError) { break; }

					// Dequeue the already sent byte from the buffer now we have confirmed that no transmission error occurred
					RingBuffer_Remove(&USARTtoUSB_Buffer);
				}
			}
		}

		// Load the next byte from the USART transmit buffer into the USART if transmit buffer space is available
		if (Serial_IsSendReady() && !(RingBuffer_IsEmpty(&USBtoUSART_Buffer)))
		{
			Serial_SendByte(RingBuffer_Remove(&USBtoUSART_Buffer));
		}

		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		USB_USBTask();
	}
}

#pragma endregion
// EVENTS
#pragma region

// Event handler for the library USB Connection event.
void EVENT_USB_Device_Connect(void) { LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING); }

// Event handler for the library USB Disconnection event.
void EVENT_USB_Device_Disconnect(void) { LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY); }

// Event handler for the library USB Configuration Changed event.
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;
	ConfigSuccess &= CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);
	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

// Event handler for the library USB Control Request reception event.
void EVENT_USB_Device_ControlRequest(void) { CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface); }

// ISR to manage the reception of data from the serial port, placing received bytes into a circular buffer
// for later transmission to the host.
ISR(USART1_RX_vect, ISR_BLOCK)
{
	uint8_t ReceivedByte = UDR1;
	if ((USB_DeviceState == DEVICE_STATE_Configured) && !(RingBuffer_IsFull(&USARTtoUSB_Buffer)))
	{
        RingBuffer_Insert(&USARTtoUSB_Buffer, ReceivedByte);
	}
}

// Event handler for the CDC Class driver Line Encoding Changed event.
// \param[in] CDCInterfaceInfo  Pointer to the CDC class interface configuration structure being referenced
void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	uint8_t ConfigMask = 0;

	switch (CDCInterfaceInfo->State.LineEncoding.ParityType)
	{
		case (CDC_PARITY_Odd): { ConfigMask = ((1 << UPM11) | (1 << UPM10)); } break;
		case (CDC_PARITY_Even): { ConfigMask = (1 << UPM11); } break;
		default: { } break;
	}

	if (CDCInterfaceInfo->State.LineEncoding.CharFormat == CDC_LINEENCODING_TwoStopBits) { ConfigMask |= (1 << USBS1); }

	switch (CDCInterfaceInfo->State.LineEncoding.DataBits)
	{
		case (6): { ConfigMask |= (1 << UCSZ10); } break;
		case (7): { ConfigMask |= (1 << UCSZ11); } break;
		case (8): { ConfigMask |= ((1 << UCSZ11) | (1 << UCSZ10)); } break;
		default: { } break;
	}

	// Keep the TX line held high (idle) while the USART is reconfigured
	PORTD |= (1 << 3);

	// Must turn off USART before reconfiguring it, otherwise incorrect operation may occur
	UCSR1B = 0;
	UCSR1A = 0;
	UCSR1C = 0;

	// Set the new baud rate before configuring the USART
	UBRR1  = SERIAL_2X_UBBRVAL(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS);

	// Reconfigure the USART in double speed mode for a wider baud rate range at the expense of accuracy
	UCSR1C = ConfigMask;
	UCSR1A = (1 << U2X1);
	UCSR1B = ((1 << RXCIE1) | (1 << TXEN1) | (1 << RXEN1));

	// Release the TX line after the USART has been reconfigured
	PORTD &= ~(1 << 3);
}

#pragma endregion

// (V) \\/\\//\//