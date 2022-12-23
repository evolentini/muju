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

#include "chip.h"
#include "hal.h"

/* === Macros definitions ====================================================================== */

#define LED_RGB_R  GPIO5_0
#define LED_RGB_G  GPIO5_1
#define LED_RGB_B  GPIO5_2
#define LED_RED    GPIO0_14
#define LED_YELLOW GPIO1_11
#define LED_GREEN  GPIO1_12
#define TEC_1      GPIO0_4
#define TEC_2      GPIO0_8
#define TEC_3      GPIO0_9
#define TEC_4      GPIO1_9

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
    int divisor = 0;
    bool current_state, last_state = false;

    PinSetFunction(P2_0, GPIO, false);
    GpioSetDirection(LED_RGB_R, true);
    PinSetFunction(P2_1, GPIO, false);
    GpioSetDirection(LED_RGB_G, true);
    PinSetFunction(P2_2, GPIO, false);
    GpioSetDirection(LED_RGB_B, true);

    PinSetFunction(P2_10, GPIO, false);
    GpioSetDirection(LED_RED, true);
    PinSetFunction(P2_11, GPIO, false);
    GpioSetDirection(LED_YELLOW, true);
    PinSetFunction(P2_12, GPIO, false);
    GpioSetDirection(LED_GREEN, true);

    PinSetFunction(P1_0, GPIO, true);
    GpioSetDirection(TEC_1, false);
    PinSetFunction(P1_1, GPIO, true);
    GpioSetDirection(TEC_2, false);
    PinSetFunction(P1_2, GPIO, true);
    GpioSetDirection(TEC_3, false);
    PinSetFunction(P1_6, GPIO, true);
    GpioSetDirection(TEC_4, false);

    PinSetFunction(P7_1, SCI_TX, false);
    PinSetFunction(P7_2, SCI_RX, true);
    SciSetConfig(USART2, 115200, 8, SCI_NO_PARITY);

    while (true) {
        if (GpioGetState(TEC_1) == 0) {
            GpioSetState(LED_RGB_B, true);
        } else {
            GpioSetState(LED_RGB_B, false);
        }

        current_state = (GpioGetState(TEC_2) == 0);
        if ((current_state) && (!last_state)) {
            GpioBitToogle(LED_RED);
            SciSendData(USART2, "Hola\r\n", 6);
            // Chip_UART_SendBlocking(LPC_USART2, "Hola\r\n", 6);
        }
        last_state = current_state;

        if (GpioGetState(TEC_3) == 0) {
            GpioSetState(LED_YELLOW, true);
        }
        if (GpioGetState(TEC_4) == 0) {
            GpioSetState(LED_YELLOW, false);
        }

        divisor++;
        if (divisor == 5) {
            divisor = 0;
            GpioBitToogle(LED_GREEN);
        }

        delay();
    }
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
