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

#include "soc_gpio.h"
#include "chip.h"

/* === Macros definitions ====================================================================== */

#define GPIO_NAME(PORT, BIT) GPIO##PORT##_##BIT

#define GPIO_BIT(PORT, BIT)                                                                        \
    GPIO_NAME(PORT, BIT) = &(struct hal_gpio_bit_s) {                                              \
        .gpio = PORT, .bit = BIT                                                                   \
    }

/* === Private data type declarations ========================================================== */

struct hal_gpio_bit_s {
    uint8_t gpio : 3;
    uint8_t bit : 5;
};

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

const hal_gpio_bit_t GPIO_BIT(0, 0);
const hal_gpio_bit_t GPIO_BIT(0, 1);
const hal_gpio_bit_t GPIO_BIT(0, 2);
const hal_gpio_bit_t GPIO_BIT(0, 3);
const hal_gpio_bit_t GPIO_BIT(0, 4);
const hal_gpio_bit_t GPIO_BIT(0, 5);
const hal_gpio_bit_t GPIO_BIT(0, 7);
const hal_gpio_bit_t GPIO_BIT(0, 8);
const hal_gpio_bit_t GPIO_BIT(0, 9);
const hal_gpio_bit_t GPIO_BIT(0, 10);
const hal_gpio_bit_t GPIO_BIT(0, 11);
const hal_gpio_bit_t GPIO_BIT(0, 12);
const hal_gpio_bit_t GPIO_BIT(0, 13);
const hal_gpio_bit_t GPIO_BIT(0, 14);
const hal_gpio_bit_t GPIO_BIT(0, 15);

const hal_gpio_bit_t GPIO_BIT(1, 8);
const hal_gpio_bit_t GPIO_BIT(1, 9);
const hal_gpio_bit_t GPIO_BIT(1, 11);
const hal_gpio_bit_t GPIO_BIT(1, 12);

const hal_gpio_bit_t GPIO_BIT(2, 0);
const hal_gpio_bit_t GPIO_BIT(2, 1);
const hal_gpio_bit_t GPIO_BIT(2, 2);
const hal_gpio_bit_t GPIO_BIT(2, 3);
const hal_gpio_bit_t GPIO_BIT(2, 4);
const hal_gpio_bit_t GPIO_BIT(2, 5);
const hal_gpio_bit_t GPIO_BIT(2, 6);

const hal_gpio_bit_t GPIO_BIT(3, 0);
const hal_gpio_bit_t GPIO_BIT(3, 1);
const hal_gpio_bit_t GPIO_BIT(3, 2);
const hal_gpio_bit_t GPIO_BIT(3, 3);
const hal_gpio_bit_t GPIO_BIT(3, 4);
const hal_gpio_bit_t GPIO_BIT(3, 5);
const hal_gpio_bit_t GPIO_BIT(3, 6);
const hal_gpio_bit_t GPIO_BIT(3, 7);
const hal_gpio_bit_t GPIO_BIT(3, 8);
const hal_gpio_bit_t GPIO_BIT(3, 12);
const hal_gpio_bit_t GPIO_BIT(3, 13);
const hal_gpio_bit_t GPIO_BIT(3, 14);
const hal_gpio_bit_t GPIO_BIT(3, 15);

const hal_gpio_bit_t GPIO_BIT(4, 11);

const hal_gpio_bit_t GPIO_BIT(5, 0);
const hal_gpio_bit_t GPIO_BIT(5, 1);
const hal_gpio_bit_t GPIO_BIT(5, 2);
const hal_gpio_bit_t GPIO_BIT(5, 3);
const hal_gpio_bit_t GPIO_BIT(5, 4);
const hal_gpio_bit_t GPIO_BIT(5, 8);
const hal_gpio_bit_t GPIO_BIT(5, 9);
const hal_gpio_bit_t GPIO_BIT(5, 12);
const hal_gpio_bit_t GPIO_BIT(5, 13);
const hal_gpio_bit_t GPIO_BIT(5, 14);
const hal_gpio_bit_t GPIO_BIT(5, 15);
const hal_gpio_bit_t GPIO_BIT(5, 16);
const hal_gpio_bit_t GPIO_BIT(5, 18);

/*
const hal_gpio_bit_t GPIO0_0 =
    &(struct hal_gpio_s){.port = 0, .pin = 0, .function = 0, .gpio = 0, .bit = 0};
const hal_gpio_bit_t GPIO0_1 =
    &(struct hal_gpio_s){.port = 0, .pin = 1, .function = 0, .gpio = 0, .bit = 1};
const hal_gpio_bit_t GPIO0_2 =
    &(struct hal_gpio_s){.port = 1, .pin = 15, .function = 0, .gpio = 0, .bit = 2};
const hal_gpio_bit_t GPIO0_3 =
    &(struct hal_gpio_s){.port = 1, .pin = 16, .function = 0, .gpio = 0, .bit = 3};
const hal_gpio_bit_t GPIO0_4 =
    &(struct hal_gpio_s){.port = 1, .pin = 0, .function = 0, .gpio = 0, .bit = 4};
const hal_gpio_bit_t GPIO0_5 =
    &(struct hal_gpio_s){.port = 6, .pin = 6, .function = 0, .gpio = 0, .bit = 5};
const hal_gpio_bit_t GPIO0_7 =
    &(struct hal_gpio_s){.port = 2, .pin = 7, .function = 0, .gpio = 0, .bit = 7};
const hal_gpio_bit_t GPIO0_8 =
    &(struct hal_gpio_s){.port = 1, .pin = 1, .function = 0, .gpio = 0, .bit = 8};
const hal_gpio_bit_t GPIO0_9 =
    &(struct hal_gpio_s){.port = 1, .pin = 2, .function = 0, .gpio = 0, .bit = 9};
const hal_gpio_bit_t GPIO0_10 =
    &(struct hal_gpio_s){.port = 1, .pin = 3, .function = 0, .gpio = 0, .bit = 10};
const hal_gpio_bit_t GPIO0_11 =
    &(struct hal_gpio_s){.port = 1, .pin = 4, .function = 0, .gpio = 0, .bit = 11};
const hal_gpio_bit_t GPIO0_12 =
    &(struct hal_gpio_s){.port = 1, .pin = 17, .function = 0, .gpio = 0, .bit = 12};
const hal_gpio_bit_t GPIO0_13 =
    &(struct hal_gpio_s){.port = 1, .pin = 18, .function = 0, .gpio = 0, .bit = 13};
const hal_gpio_bit_t GPIO0_14 =
    &(struct hal_gpio_s){.port = 2, .pin = 10, .function = 0, .gpio = 0, .bit = 14};
const hal_gpio_bit_t GPIO0_15 =
    &(struct hal_gpio_s){.port = 1, .pin = 20, .function = 0, .gpio = 0, .bit = 15};

const hal_gpio_bit_t GPIO1_8 =
    &(struct hal_gpio_s){.port = 1, .pin = 5, .function = 0, .gpio = 1, .bit = 8};
const hal_gpio_bit_t GPIO1_9 =
    &(struct hal_gpio_s){.port = 1, .pin = 6, .function = 0, .gpio = 1, .bit = 9};
const hal_gpio_bit_t GPIO1_11 =
    &(struct hal_gpio_s){.port = 2, .pin = 11, .function = 0, .gpio = 1, .bit = 11};
const hal_gpio_bit_t GPIO1_12 =
    &(struct hal_gpio_s){.port = 2, .pin = 12, .function = 0, .gpio = 1, .bit = 12};

const hal_gpio_bit_t GPIO2_0 =
    &(struct hal_gpio_s){.port = 4, .pin = 0, .function = 0, .gpio = 2, .bit = 0};
const hal_gpio_bit_t GPIO2_1 =
    &(struct hal_gpio_s){.port = 4, .pin = 1, .function = 0, .gpio = 2, .bit = 1};
const hal_gpio_bit_t GPIO2_2 =
    &(struct hal_gpio_s){.port = 4, .pin = 2, .function = 0, .gpio = 2, .bit = 2};
const hal_gpio_bit_t GPIO2_3 =
    &(struct hal_gpio_s){.port = 4, .pin = 3, .function = 0, .gpio = 2, .bit = 3};
const hal_gpio_bit_t GPIO2_4 =
    &(struct hal_gpio_s){.port = 4, .pin = 4, .function = 0, .gpio = 2, .bit = 4};
const hal_gpio_bit_t GPIO2_5 =
    &(struct hal_gpio_s){.port = 4, .pin = 5, .function = 0, .gpio = 2, .bit = 5};
const hal_gpio_bit_t GPIO2_6 =
    &(struct hal_gpio_s){.port = 4, .pin = 6, .function = 0, .gpio = 2, .bit = 6};

const hal_gpio_bit_t GPIO3_0 =
    &(struct hal_gpio_s){.port = 6, .pin = 1, .function = 0, .gpio = 2, .bit = 0};
const hal_gpio_bit_t GPIO3_1 =
    &(struct hal_gpio_s){.port = 6, .pin = 2, .function = 0, .gpio = 2, .bit = 1};
const hal_gpio_bit_t GPIO3_2 =
    &(struct hal_gpio_s){.port = 6, .pin = 3, .function = 0, .gpio = 2, .bit = 2};
const hal_gpio_bit_t GPIO3_3 =
    &(struct hal_gpio_s){.port = 6, .pin = 4, .function = 0, .gpio = 2, .bit = 3};
const hal_gpio_bit_t GPIO3_4 =
    &(struct hal_gpio_s){.port = 6, .pin = 5, .function = 0, .gpio = 2, .bit = 4};
const hal_gpio_bit_t GPIO3_5 =
    &(struct hal_gpio_s){.port = 6, .pin = 9, .function = 0, .gpio = 2, .bit = 5};
const hal_gpio_bit_t GPIO3_6 =
    &(struct hal_gpio_s){.port = 6, .pin = 10, .function = 0, .gpio = 2, .bit = 6};
const hal_gpio_bit_t GPIO3_7 =
    &(struct hal_gpio_s){.port = 6, .pin = 11, .function = 0, .gpio = 2, .bit = 7};
const hal_gpio_bit_t GPIO3_8 =
    &(struct hal_gpio_s){.port = 6, .pin = 12, .function = 0, .gpio = 2, .bit = 8};
const hal_gpio_bit_t GPIO3_12 =
    &(struct hal_gpio_s){.port = 7, .pin = 4, .function = 0, .gpio = 2, .bit = 12};
const hal_gpio_bit_t GPIO3_13 =
    &(struct hal_gpio_s){.port = 7, .pin = 5, .function = 0, .gpio = 2, .bit = 13};
const hal_gpio_bit_t GPIO3_14 =
    &(struct hal_gpio_s){.port = 7, .pin = 6, .function = 0, .gpio = 2, .bit = 14};
const hal_gpio_bit_t GPIO3_15 =
    &(struct hal_gpio_s){.port = 7, .pin = 7, .function = 0, .gpio = 2, .bit = 15};

const hal_gpio_bit_t GPIO4_11 =
    &(struct hal_gpio_s){.port = 9, .pin = 6, .function = 0, .gpio = 4, .bit = 11};

const hal_gpio_bit_t GPIO5_0 =
    &(struct hal_gpio_s){.port = 2, .pin = 0, .function = 4, .gpio = 5, .bit = 0};
const hal_gpio_bit_t GPIO5_1 =
    &(struct hal_gpio_s){.port = 2, .pin = 1, .function = 4, .gpio = 5, .bit = 1};
const hal_gpio_bit_t GPIO5_2 =
    &(struct hal_gpio_s){.port = 2, .pin = 2, .function = 4, .gpio = 5, .bit = 2};
const hal_gpio_bit_t GPIO5_3 =
    &(struct hal_gpio_s){.port = 2, .pin = 3, .function = 4, .gpio = 5, .bit = 3};
const hal_gpio_bit_t GPIO5_4 =
    &(struct hal_gpio_s){.port = 2, .pin = 4, .function = 4, .gpio = 5, .bit = 4};
const hal_gpio_bit_t GPIO5_8 =
    &(struct hal_gpio_s){.port = 3, .pin = 1, .function = 4, .gpio = 5, .bit = 8};
const hal_gpio_bit_t GPIO5_9 =
    &(struct hal_gpio_s){.port = 3, .pin = 2, .function = 4, .gpio = 5, .bit = 9};
const hal_gpio_bit_t GPIO5_12 =
    &(struct hal_gpio_s){.port = 4, .pin = 8, .function = 4, .gpio = 5, .bit = 12};
const hal_gpio_bit_t GPIO5_13 =
    &(struct hal_gpio_s){.port = 4, .pin = 9, .function = 4, .gpio = 5, .bit = 13};
const hal_gpio_bit_t GPIO5_14 =
    &(struct hal_gpio_s){.port = 4, .pin = 10, .function = 4, .gpio = 5, .bit = 14};
const hal_gpio_bit_t GPIO5_15 =
    &(struct hal_gpio_s){.port = 6, .pin = 7, .function = 4, .gpio = 5, .bit = 15};
const hal_gpio_bit_t GPIO5_16 =
    &(struct hal_gpio_s){.port = 6, .pin = 8, .function = 4, .gpio = 5, .bit = 16};
const hal_gpio_bit_t GPIO5_18 =
    &(struct hal_gpio_s){.port = 9, .pin = 5, .function = 4, .gpio = 5, .bit = 18};
*/

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================= */

void GpioSetDirection(hal_gpio_bit_t gpio, bool otuput) {
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, gpio->gpio, gpio->bit, otuput);
}

bool GpioGetState(hal_gpio_bit_t gpio) {
    return Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, gpio->gpio, gpio->bit);
}

void GpioSetState(hal_gpio_bit_t gpio, bool state) {
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpio->gpio, gpio->bit, state);
}

void GpioBitSet(hal_gpio_bit_t gpio) {
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpio->gpio, gpio->bit, true);
}

void GpioBitClear(hal_gpio_bit_t gpio) {
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpio->gpio, gpio->bit, false);
}

void GpioBitToogle(hal_gpio_bit_t gpio) {
    Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, gpio->gpio, gpio->bit);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
