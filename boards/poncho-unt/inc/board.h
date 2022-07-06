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

#ifndef BOARD_H
#define BOARD_H

/** \brief Digital inputs/outputs declarations
 **
 ** \addtogroup hal HAL
 ** \brief Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include <chip.h>
#include <board_api.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

#define LED_R_PORT          2
#define LED_R_PIN           0
#define LED_R_GPIO          5
#define LED_R_BIT           0

#define LED_G_PORT          2
#define LED_G_PIN           1
#define LED_G_GPIO          5
#define LED_G_BIT           1

#define LED_B_PORT          2
#define LED_B_PIN           2
#define LED_B_GPIO          5
#define LED_B_BIT           2

#define LED_1_PORT          2
#define LED_1_PIN           10
#define LED_1_GPIO          0
#define LED_1_BIT           14

#define LED_2_PORT          2
#define LED_2_PIN           11
#define LED_2_GPIO          1
#define LED_2_BIT           11

#define LED_3_PORT          2
#define LED_3_PIN           12
#define LED_3_GPIO          1
#define LED_3_BIT           12

#define TEC_1_PORT          1
#define TEC_1_PIN           0
#define TEC_1_GPIO          0
#define TEC_1_BIT           4

#define TEC_2_PORT          1
#define TEC_2_PIN           1
#define TEC_2_GPIO          0
#define TEC_2_BIT           8

#define TEC_3_PORT          1
#define TEC_3_PIN           2
#define TEC_3_GPIO          0
#define TEC_3_BIT           9

#define TEC_4_PORT          1
#define TEC_4_PIN           6
#define TEC_4_GPIO          1
#define TEC_4_BIT           9

#define SEGMENT_A_PORT      4
#define SEGMENT_A_PIN       0
#define SEGMENT_A_GPIO      2
#define SEGMENT_A_BIT       0

#define SEGMENT_B_PORT      4
#define SEGMENT_B_PIN       1
#define SEGMENT_B_GPIO      2
#define SEGMENT_B_BIT       1

#define SEGMENT_C_PORT      4
#define SEGMENT_C_PIN       2
#define SEGMENT_C_GPIO      2
#define SEGMENT_C_BIT       2

#define SEGMENT_D_PORT      4
#define SEGMENT_D_PIN       3
#define SEGMENT_D_GPIO      2
#define SEGMENT_D_BIT       3

#define SEGMENT_E_PORT      4
#define SEGMENT_E_PIN       4
#define SEGMENT_E_GPIO      2
#define SEGMENT_E_BIT       4

#define SEGMENT_F_PORT      4
#define SEGMENT_F_PIN       5
#define SEGMENT_F_GPIO      2
#define SEGMENT_F_BIT       5

#define SEGMENT_G_PORT      4
#define SEGMENT_G_PIN       6
#define SEGMENT_G_GPIO      2
#define SEGMENT_G_BIT       6

#define SEGMENT_DP_PORT     6
#define SEGMENT_DP_PIN      8
#define SEGMENT_DP_GPIO     5
#define SEGMENT_DP_BIT      16

#define DIGIT_1_PORT        0
#define DIGIT_1_PIN         0
#define DIGIT_1_GPIO        0
#define DIGIT_1_BIT         0

#define DIGIT_2_PORT        0
#define DIGIT_2_PIN         1
#define DIGIT_2_GPIO        0
#define DIGIT_2_BIT         1

#define DIGIT_3_PORT        1
#define DIGIT_3_PIN         15
#define DIGIT_3_GPIO        0
#define DIGIT_3_BIT         2

#define DIGIT_4_PORT        1
#define DIGIT_4_PIN         17
#define DIGIT_4_GPIO        0
#define DIGIT_4_BIT         3

#define KEY_F1_PORT         4
#define KEY_F1_PIN          8
#define KEY_F1_GPIO         5
#define KEY_F1_BIT          12

#define KEY_F2_PORT         4
#define KEY_F2_PIN          9
#define KEY_F2_GPIO         5
#define KEY_F2_BIT          13

#define KEY_F3_PORT         4
#define KEY_F3_PIN          10
#define KEY_F3_GPIO         5
#define KEY_F3_BIT          14

#define KEY_F4_PORT         6
#define KEY_F4_PIN          7
#define KEY_F4_GPIO         5
#define KEY_F4_BIT          15

#define KEY_ACCEPT_PORT     3
#define KEY_ACCEPT_PIN      2
#define KEY_ACCEPT_GPIO     5
#define KEY_ACCEPT_BIT      9

#define KEY_CANCEL_PORT     3
#define KEY_CANCEL_PIN      1
#define KEY_CANCEL_GPIO     5
#define KEY_CANCEL_BIT      8

#define TEC_1_TERMINAL     &(const struct terminal_s){.port = TEC_1_GPIO, .pin = TEC_1_BIT}
#define TEC_2_TERMINAL     &(const struct terminal_s){.port = TEC_2_GPIO, .pin = TEC_2_BIT}
#define TEC_3_TERMINAL     &(const struct terminal_s){.port = TEC_3_GPIO, .pin = TEC_3_BIT}
#define TEC_4_TERMINAL     &(const struct terminal_s){.port = TEC_4_GPIO, .pin = TEC_4_BIT}

#define KEY_F1_TERMINAL     &(const struct terminal_s){.port = KEY_F1_GPIO, .pin = KEY_F1_BIT}
#define KEY_F2_TERMINAL     &(const struct terminal_s){.port = KEY_F2_GPIO, .pin = KEY_F2_BIT}
#define KEY_F3_TERMINAL     &(const struct terminal_s){.port = KEY_F3_GPIO, .pin = KEY_F3_BIT}
#define KEY_F4_TERMINAL     &(const struct terminal_s){.port = KEY_F4_GPIO, .pin = KEY_F4_BIT}

#define KEY_ACCEPT_TERMINAL &(const struct terminal_s){.port = KEY_ACCEPT_GPIO, .pin = KEY_ACCEPT_BIT}
#define KEY_CANCEL_TERMINAL &(const struct terminal_s){.port = KEY_CANCEL_GPIO, .pin = KEY_CANCEL_BIT}

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Function to configure board devices
 */
void BoardInit(void);

/**
 * @brief 
 * 
 * @param value 
 */
void DelayMs(uint32_t value);

/**
 * @brief 
 * 
 */
void SegmentsTurnOff(void);

/**
 * @brief 
 * 
 * @param value 
 */
void SegmentsSetState(uint8_t segments);

/**
 * @brief 
 * 
 * @param digit 
 */
void DigitsTurnOn(uint8_t digit);

uint32_t BoardGetSystemCoreClock(void);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif   /* BOARD_H */
