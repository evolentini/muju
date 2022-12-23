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

#ifndef HAL_SCI_H
#define HAL_SCI_H

/** \brief Digital inputs/outputs declarations
 **
 ** \addtogroup hal HAL
 ** \brief Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include <stdbool.h>
#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

typedef enum {
    SCI_NO_PARITY,
    SCI_ODD_PARITY,
    SCI_EVEN_PARITY,
    SCI_MARK_PARITY,
    SCI_SPACE_PARITY,
} sci_parity_t;

typedef struct sci_status_s {
    bool data_ready : 1;
    bool overrun : 1;
    bool parity_error : 1;
    bool framing_error : 1;
    bool break_signal : 1;
    bool fifo_empty : 1;
    bool tramition_completed;
} * sci_status_t;

typedef struct hal_sci_s * const hal_sci_t;

typedef void (*hal_sci_event_t)(hal_sci_t sci, sci_status_t status);

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

void SciSetConfig(hal_sci_t sci, uint32_t baud_rate, uint8_t data_bits, sci_parity_t parity);

uint16_t SciSendData(hal_sci_t sci, void const * const data, uint16_t size);

uint16_t SciReceiveData(hal_sci_t sci, void * data, uint16_t size);

void SciReadStatus(hal_sci_t sci, sci_status_t result, bool clear_status);

void SciSetEventHandler(hal_sci_t sci, hal_sci_event_t handler);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* HAL_SCI_H */