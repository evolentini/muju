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

/** \brief Simple sample of use LPC HAL gpio functions
 **
 ** \addtogroup samples Sample projects
 ** \brief Sample projects to use as a starting point
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "saio.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

static void delay(void);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

static void delay(void) {
    for (int index = 0; index < 100; index++) {
        for (int delay = 0; delay < 25000; delay++) {
            __asm("NOP");
        }
    }
}

/* === Public function implementation ========================================================= */

int main(void) {
    static const struct digital_output_atributes_s LED_OUTPUT = {
        .inverted = false,
        .high_current = false,
        .open_colector = false,
    };

    static const struct digital_input_atributes_s BUTTON_INPUT = {
        .inverted = true,
        .pullup = true,
        .pulldown = false,
    };

    int divisor = 0;

    // digital_output_t led_rgb_r;
    // digital_output_t led_rgb_g;
    digital_output_t led_rgb_b;
    digital_output_t led_red;
    digital_output_t led_yellow;
    digital_output_t led_green;

    digital_input_t tec_1;
    digital_input_t tec_2;
    digital_input_t tec_3;
    digital_input_t tec_4;

    // led_rgb_r = DigitalOutputCreate(GPIO5_0, &LED_OUTPUT);
    // led_rgb_g = DigitalOutputCreate(GPIO5_1, &LED_OUTPUT);
    led_rgb_b = DigitalOutputCreate(GPIO5_2, &LED_OUTPUT);
    led_red = DigitalOutputCreate(GPIO0_14, &LED_OUTPUT);
    led_yellow = DigitalOutputCreate(GPIO1_11, &LED_OUTPUT);
    led_green = DigitalOutputCreate(GPIO1_12, &LED_OUTPUT);

    tec_1 = DigitalInputCreate(GPIO0_4, &BUTTON_INPUT);
    tec_2 = DigitalInputCreate(GPIO0_8, &BUTTON_INPUT);
    tec_3 = DigitalInputCreate(GPIO0_9, &BUTTON_INPUT);
    tec_4 = DigitalInputCreate(GPIO1_9, &BUTTON_INPUT);

    while (true) {
        if (DigitalInputGetState(tec_1)) {
            DigitalOutputActivate(led_rgb_b);
        } else {
            DigitalOutputDeactivate(led_rgb_b);
        }

        if (DigitalInputHasActivated(tec_2)) {
            DigitalOutputToggle(led_red);
        }

        if (DigitalInputGetState(tec_3)) {
            DigitalOutputActivate(led_yellow);
        }
        if (DigitalInputGetState(tec_4)) {
            DigitalOutputDeactivate(led_yellow);
        }

        divisor++;
        if (divisor == 5) {
            divisor = 0;
            DigitalOutputToggle(led_green);
        }
        delay();
    }
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
