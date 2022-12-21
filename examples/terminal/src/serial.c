/* Copyright 2022, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2022, Esteban Volentini <evolentini@herrera.unt.edu.ar>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \brief Serial asynconous port definitions
 **
 ** \addtogroup hal HAL
 ** \brief Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "serial.h"
#include "chip.h"
#include "cmsis_43xx.h"
#include <string.h>

/* === Macros definitions ====================================================================== */

#ifndef SERIAL_INSTANCES
#define SERIAL_INSTANCES 2
#endif

#ifndef SERIAL_TX_BUFFER_SIZE
#define SERIAL_TX_BUFFER_SIZE 8
#endif

#ifndef SERIAL_RX_BUFFER_SIZE
#define SERIAL_RX_BUFFER_SIZE 8
#endif

/* === Private data type declarations ========================================================== */

//! Estructura para almacenar el descriptor de puerto serial asincronico
struct serial_port_s {
    LPC_USART_T * port;
    IRQn_Type interupt;
    serial_event_t handler;
    struct {
        char data[SERIAL_TX_BUFFER_SIZE];
        uint8_t count;
        uint8_t sent;
    } tx[1];
    struct {
        char data[SERIAL_RX_BUFFER_SIZE];
        uint8_t count;
    } rx[1];
    bool allocated;
};

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

// Function para asignar un descriptor para crear una nuevo puerto serial asincronico
static serial_port_t SerialPortAllocate(void);

static void InteruptEvent(serial_port_t port);

/* === Public variable definitions ============================================================= */

static serial_port_t handlers[4];

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

static serial_port_t SerialPortAllocate(void) {
    serial_port_t port = NULL;

    static struct serial_port_s instances[SERIAL_INSTANCES] = {0};

    for (int index = 0; index < SERIAL_INSTANCES; index++) {
        if (!instances[index].allocated) {
            instances[index].allocated = true;
            port = &instances[index];
            break;
        }
    }
    return port;
}

static void InteruptEvent(serial_port_t port) {
    uint8_t eventos;

    eventos = Chip_UART_ReadLineStatus(port->port);

    if (eventos & UART_LSR_THRE) {
        Chip_UART_SendByte(port->port, port->tx->data[port->tx->sent]);
        port->tx->sent++;

        if (port->tx->sent == port->tx->count) {
            port->tx->count = 0;
            Chip_UART_IntDisable(port->port, UART_IER_THREINT);
            if (port->handler) {
                port->handler(port);
            }
        }
    }
}

/* === Public function implementation ========================================================= */

serial_port_t SerialPortCreate(uint8_t port, uint32_t bitrate) {
    serial_port_t self = SerialPortAllocate();

    if (self) {
        switch (port) {
        case 0:
            Chip_SCU_PinMux(9, 5, MD_PDN, FUNC7);                  /* P9_5: UART0_TXD */
            Chip_SCU_PinMux(9, 6, MD_PLN | MD_EZI | MD_ZI, FUNC7); /* P9_6: UART0_RXD */
            Chip_SCU_PinMux(6, 2, MD_PDN, FUNC2);                  /* P6_2: UART0_DIR */
            handlers[0] = self;
            self->port = LPC_USART0;
            self->interupt = USART0_IRQn;
            break;
        case 1:
            handlers[1] = self;
            self->port = LPC_UART1;
            self->interupt = UART1_IRQn;
            break;
        case 2:
            handlers[2] = self;
            Chip_SCU_PinMux(7, 1, MD_PDN, FUNC6);                  /* P7_1: UART2_TXD */
            Chip_SCU_PinMux(7, 2, MD_PLN | MD_EZI | MD_ZI, FUNC6); /* P7_2: UART2_RXD */
            self->port = LPC_USART2;
            self->interupt = USART2_IRQn;
            break;
        case 3:
            handlers[3] = self;
            Chip_SCU_PinMux(2, 3, MD_PDN, FUNC2);                  /* P2_3: UART3_TXD */
            Chip_SCU_PinMux(2, 4, MD_PLN | MD_EZI | MD_ZI, FUNC2); /* P2_4: UART3_RXD */
            self->port = LPC_USART3;
            self->interupt = USART3_IRQn;
            break;
        default:
            self->allocated = false;
            self = NULL;
            break;
        }
    }

    if (self) {
        Chip_UART_Init(self->port);
        Chip_UART_SetBaud(self->port, bitrate);
        Chip_UART_SetupFIFOS(self->port, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);
        Chip_UART_TXEnable(self->port);
        if (self->port == LPC_USART0) {
            Chip_UART_SetRS485Flags(self->port, UART_RS485CTRL_DCTRL_EN | UART_RS485CTRL_OINV_1);
        }
        NVIC_EnableIRQ(self->interupt);
        NVIC_SetPriority(self->interupt, 5);
    }
    return self;
}

uint8_t SerialPortTransmit(serial_port_t port, void const * const data, uint8_t size) {
    uint8_t count = 0;

    if (port->tx->count == 0) {
        count = size;
        if (count > SERIAL_TX_BUFFER_SIZE) {
            count = SERIAL_TX_BUFFER_SIZE;
        }
        memcpy(port->tx->data, data, count);
        port->tx->count = count;
        port->tx->sent = 0;

        Chip_UART_IntEnable(port->port, UART_IER_THREINT);
        InteruptEvent(port);
    }
    return count;
}

uint8_t SerialPortReceive(serial_port_t port, void const * const data, uint8_t size) {
    return 0;
}

void SerialPortOnTransmited(serial_port_t port, serial_event_t handler) {
    port->handler = handler;
}

void UART0_IRQHandler(void) {
    InteruptEvent(handlers[0]);
}

void UART1_IRQHandler(void) {
    InteruptEvent(handlers[1]);
}

void UART2_IRQHandler(void) {
    InteruptEvent(handlers[2]);
}

void UART3_IRQHandler(void) {
    InteruptEvent(handlers[3]);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
