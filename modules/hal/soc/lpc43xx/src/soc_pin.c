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

#include "soc_pin.h"
#include "chip.h"

/* === Macros definitions ====================================================================== */

#define PIN_NAME(PORT, PIN) P##PORT##_##PIN

#define PIN(PORT, PIN, ...)                                                                        \
    PIN_NAME(PORT, PIN) = &(struct hal_pin_s) {                                                    \
        .port = PORT, .pin = PIN, .functions = { __VA_ARGS__ }                                     \
    }

/* === Private data type declarations ========================================================== */

struct hal_pin_s {
    uint8_t port : 4;
    uint8_t pin : 5;
    hal_pin_function_t functions[8];
};

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

const hal_pin_t PIN(1, 0, GPIO);
const hal_pin_t PIN(1, 1, GPIO);
const hal_pin_t PIN(1, 2, GPIO);
const hal_pin_t PIN(1, 6, GPIO);

const hal_pin_t PIN(1, 15, GPIO, SCI_TX, RESERVED, RESERVED, TIMER_OUTPUT);
const hal_pin_t PIN(1, 16, GPIO, SCI_RX, RESERVED, RESERVED, TIMER_OUTPUT);
const hal_pin_t PIN(1, 17, GPIO, SCI_CLK, RESERVED, RESERVED, TIMER_INPUT);

const hal_pin_t PIN(2, 0, RESERVED, SCI_TX, RESERVED, RESERVED, GPIO, RESERVED, TIMER_INPUT);
const hal_pin_t PIN(2, 1, RESERVED, SCI_RX, RESERVED, RESERVED, GPIO, RESERVED, TIMER_INPUT);
const hal_pin_t PIN(2, 2, RESERVED, SCI_CLK, RESERVED, RESERVED, GPIO, RESERVED, TIMER_INPUT);
const hal_pin_t PIN(2, 10, GPIO, RESERVED, SCI_TX);
const hal_pin_t PIN(2, 11, GPIO, RESERVED, SCI_RX);
const hal_pin_t PIN(2, 12, GPIO);

const hal_pin_t PIN(6, 4, GPIO, RESERVED, SCI_TX);

const hal_pin_t PIN(7, 1, GPIO, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, SCI_TX);
const hal_pin_t PIN(7, 2, GPIO, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, SCI_RX);

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================= */

void PinSetFunction(hal_pin_t pin, hal_pin_function_t function, bool pullup) {
    uint8_t index;
    uint32_t value;

    for (index = 0; index < 8; index++) {
        if (pin->functions[index] == function) {
            if (pullup) {
                value = SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;
            } else {
                value = SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;
            }
            Chip_SCU_PinMux(pin->port, pin->pin, value, index);
            break;
        }
    }
}

void PinSetPullUp(hal_pin_t pin, bool enabled) {
    uint32_t current;

    current = LPC_SCU->SFSP[pin->port][pin->pin];
    if (enabled) {
        current &= ~(1 << 3);
    } else {
        current |= (1 << 3);
    }
    Chip_SCU_PinMuxSet(pin->port, pin->pin, current);
}

void PinSetPullDown(hal_pin_t pin, bool enabled) {
    uint32_t current;

    current = LPC_SCU->SFSP[pin->port][pin->pin];
    if (enabled) {
        current |= (1 << 4);
    } else {
        current &= ~(1 << 4);
    }
    Chip_SCU_PinMuxSet(pin->port, pin->pin, current);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
