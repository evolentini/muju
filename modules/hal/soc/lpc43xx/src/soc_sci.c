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

/** \brief Digital inputs/outputs definitions
 **
 ** \addtogroup hal HAL
 ** \brief Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "soc_sci.h"
#include "chip.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

struct hal_sci_s {
    LPC_USART_T * port;
    hal_sci_event_t handler;
};

/* === Private variable declarations =========================================================== */

hal_sci_t USART0 = &(struct hal_sci_s){.port = LPC_USART0, .handler = NULL};

hal_sci_t UART1 = &(struct hal_sci_s){.port = LPC_UART1, .handler = NULL};

hal_sci_t USART2 = &(struct hal_sci_s){.port = LPC_USART2, .handler = NULL};

hal_sci_t USART3 = &(struct hal_sci_s){.port = LPC_USART3, .handler = NULL};

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================= */

void SciSetConfig(hal_sci_t sci, uint32_t baud_rate, uint8_t data_bits, sci_parity_t parity) {
    Chip_UART_Init(sci->port);
    Chip_UART_SetBaud(sci->port, baud_rate);
    Chip_UART_SetupFIFOS(sci->port, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);
    Chip_UART_TXEnable(sci->port);
}

uint16_t SciSendData(hal_sci_t sci, void const * const data, uint16_t size) {
    return Chip_UART_Send(sci->port, data, size);
}

uint16_t SciReceiveData(hal_sci_t sci, void * data, uint16_t size) {
    return Chip_UART_Read(sci->port, data, size);
}

void SciReadStatus(hal_sci_t sci, sci_status_t result, bool clear_status) {
    uint32_t status;

    status = Chip_UART_ReadLineStatus(sci->port);
    result->data_ready = status & UART_LSR_RDR;
    result->overrun = status & UART_LSR_OE;
    result->parity_error = status & UART_LSR_PE;
    result->framing_error = status & UART_LSR_FE;
    result->break_signal = status & UART_LSR_BI;
    result->fifo_empty = status & UART_LSR_THRE;
    result->tramition_completed = status & UART_LSR_TEMT;
}

void SciSetEventHandler(hal_sci_t sci, hal_sci_event_t handler) {
    sci->handler = handler;
}

static void SciHandleEvent(hal_sci_t sci) {
    struct sci_status_s status;

    SciReadStatus(sci, &status, TRUE);
    if (sci->handler) {
        sci->handler(sci, &status);
    }
}

void UART0_IRQHandler(void) {
    SciHandleEvent(USART0);
}

void UART1_IRQHandler(void) {
    SciHandleEvent(UART1);
}

void UART2_IRQHandler(void) {
    SciHandleEvent(USART2);
}

void UART3_IRQHandler(void) {
    SciHandleEvent(USART3);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
