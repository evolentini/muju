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

#ifndef DIGITAL_H
#define DIGITAL_H

/** \brief Digital inputs/outputs declarations
 **
 ** \addtogroup hal HAL
 ** \brief Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include "terminal.h"
#include <stdint.h>
#include <stdbool.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */
 
/* === Public data type declarations =========================================================== */

typedef struct digital_input_atributes_s {
    bool inverted:1;
    bool pullup:1;
    bool puldown:1;
} const * digital_input_atributes_t;

//!
typedef struct digital_input_s * digital_input_t;

typedef struct digital_output_atributes_s {
    bool inverted:1;
    bool high_current:1;
    bool open_colector:1;
} const * digital_output_atributes_t;

//!  
typedef struct digital_output_s * digital_output_t;


/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief 
 * 
 * @param terminal 
 * @param atributes 
 * @return digital_input_t 
 */
digital_input_t DigitalInputCreate(terminal_t terminal, digital_input_atributes_t atributes);

/**
 * @brief 
 * 
 * @param output 
 * @return true 
 * @return false 
 */
bool DigitalInputGetState(digital_input_t output);

/**
 * @brief 
 * 
 * @param terminal 
 * @return digital_output_t 
 */
digital_output_t DigitalOutputCreate(terminal_t terminal, digital_output_atributes_t atributes);

/**
 * @brief 
 * 
 * @param output 
 * @return true 
 * @return false 
 */
bool DigitalOuputGetState(digital_output_t output);


/**
 * @brief 
 * 
 * @param output 
 * @param state 
 */
void DigitalOuputSetState(digital_output_t output, bool state);

/**
 * @brief 
 * 
 * @param output 
 */
void DigitalOuputActivate(digital_output_t output);

/**
 * @brief 
 * 
 * @param output 
 */
void DigitalOuputDeactivate(digital_output_t output);

/**
 * @brief 
 * 
 * @param output 
 */
void DigitalOuputToggle(digital_output_t output);


/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif   /* DIGITAL_H */