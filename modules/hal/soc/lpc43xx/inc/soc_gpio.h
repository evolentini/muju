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

#ifndef SOC_GPIO_H
#define SOC_GPIO_H

/** \brief Digital inputs/outputs declarations
 **
 ** \addtogroup hal HAL
 ** \brief Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include "hal_gpio.h"
#include "soc_pin.h"

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

extern const hal_gpio_bit_t GPIO0_0;
extern const hal_gpio_bit_t GPIO0_1;
extern const hal_gpio_bit_t GPIO0_2;
extern const hal_gpio_bit_t GPIO0_3;
extern const hal_gpio_bit_t GPIO0_4;
extern const hal_gpio_bit_t GPIO0_5;
extern const hal_gpio_bit_t GPIO0_7;
extern const hal_gpio_bit_t GPIO0_8;
extern const hal_gpio_bit_t GPIO0_9;
extern const hal_gpio_bit_t GPIO0_10;
extern const hal_gpio_bit_t GPIO0_11;
extern const hal_gpio_bit_t GPIO0_12;
extern const hal_gpio_bit_t GPIO0_13;
extern const hal_gpio_bit_t GPIO0_14;
extern const hal_gpio_bit_t GPIO0_15;

extern const hal_gpio_bit_t GPIO1_8;
extern const hal_gpio_bit_t GPIO1_9;
extern const hal_gpio_bit_t GPIO1_11;
extern const hal_gpio_bit_t GPIO1_12;

extern const hal_gpio_bit_t GPIO2_0;
extern const hal_gpio_bit_t GPIO2_1;
extern const hal_gpio_bit_t GPIO2_2;
extern const hal_gpio_bit_t GPIO2_3;
extern const hal_gpio_bit_t GPIO2_4;
extern const hal_gpio_bit_t GPIO2_5;
extern const hal_gpio_bit_t GPIO2_6;

extern const hal_gpio_bit_t GPIO3_0;
extern const hal_gpio_bit_t GPIO3_1;
extern const hal_gpio_bit_t GPIO3_2;
extern const hal_gpio_bit_t GPIO3_3;
extern const hal_gpio_bit_t GPIO3_4;
extern const hal_gpio_bit_t GPIO3_5;
extern const hal_gpio_bit_t GPIO3_6;
extern const hal_gpio_bit_t GPIO3_7;
extern const hal_gpio_bit_t GPIO3_8;
extern const hal_gpio_bit_t GPIO3_12;
extern const hal_gpio_bit_t GPIO3_13;
extern const hal_gpio_bit_t GPIO3_14;
extern const hal_gpio_bit_t GPIO3_15;

extern const hal_gpio_bit_t GPIO4_11;

extern const hal_gpio_bit_t GPIO5_0;
extern const hal_gpio_bit_t GPIO5_1;
extern const hal_gpio_bit_t GPIO5_2;
extern const hal_gpio_bit_t GPIO5_3;
extern const hal_gpio_bit_t GPIO5_4;
extern const hal_gpio_bit_t GPIO5_8;
extern const hal_gpio_bit_t GPIO5_9;
extern const hal_gpio_bit_t GPIO5_12;
extern const hal_gpio_bit_t GPIO5_13;
extern const hal_gpio_bit_t GPIO5_14;
extern const hal_gpio_bit_t GPIO5_15;
extern const hal_gpio_bit_t GPIO5_16;
extern const hal_gpio_bit_t GPIO5_18;

/* === Public function declarations ============================================================ */

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* SOC_GPIO_H */