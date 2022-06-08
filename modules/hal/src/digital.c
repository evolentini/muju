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

#include "digital.h"
#include "hal_soc.h"
#include <string.h>

/* === Macros definitions ====================================================================== */
#ifndef HAL_USE_STATIC_ALOCATION
    #ifndef HAL_USE_DYNAMIC_ALOCATION
        #define HAL_USE_STATIC_ALOCATION
    #endif
#endif

#ifdef HAL_USE_STATIC_ALOCATION
    #ifndef HAL_DIGITAL_INPUT_INSTANCES
        #define HAL_DIGITAL_INPUT_INSTANCES     10
    #endif

    #ifndef HAL_DIGITAL_OUTPUT_INSTANCES
        #define HAL_DIGITAL_OUTPUT_INSTANCES        10
    #endif
#endif
/* === Private data type declarations ========================================================== */

struct digital_input_s {
    struct terminal_s terminal[1];
    struct digital_input_atributes_s atributes[1];       
#ifdef HAL_USE_STATIC_ALOCATION
    bool allocated;
#endif
};

struct digital_output_s {
    struct terminal_s terminal[1];
    struct digital_output_atributes_s atributes[1];       
#ifdef HAL_USE_STATIC_ALOCATION
    bool allocated;
#endif
};

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

digital_input_t DigitalInputAllocate(void);

digital_output_t DigitalOutputAllocate(void);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

digital_input_t DigitalInputAllocate(void) {
    digital_input_t self = NULL;

#ifdef HAL_USE_STATIC_ALOCATION
    static struct digital_input_s instances[HAL_DIGITAL_INPUT_INSTANCES] =  {0};

    for(int index = 0; index < HAL_DIGITAL_INPUT_INSTANCES; index++) {
        if (!instances[index].allocated) {
            instances[index].allocated = true;
            self = &instances[index];
            break;
        }
    }
#else
    self = malloc(sizeof(struct digital_input_s instances));
#endif

    return self;
}

digital_output_t DigitalOutputAllocate(void) {
    digital_output_t self = NULL;

#ifdef HAL_USE_STATIC_ALOCATION
    static struct digital_output_s instances[HAL_DIGITAL_OUTPUT_INSTANCES] =  {0};

    for(int index = 0; index < HAL_DIGITAL_OUTPUT_INSTANCES; index++) {
        if (!instances[index].allocated) {
            instances[index].allocated = true;
            self = &instances[index];
            break;
        }
    }
#else
    self = malloc(sizeof(struct digital_output_s instances));
#endif

    return self;
}

/* === Public function implementation ========================================================= */

digital_input_t DigitalInputCreate(terminal_t terminal, digital_input_atributes_t atributes) {
    digital_input_t self = DigitalInputAllocate();
    
    if (self) {
        memcpy(self->terminal, terminal, sizeof(struct terminal_s));
        memcpy(self->atributes, atributes, sizeof(struct digital_input_atributes_s));
    }

    return self;
}

bool DigitalInputGetState(digital_input_t output) {
    bool state = HalDigitalGetState(output->terminal->port, output->terminal->pin);
    return (state ^ output->atributes->inverted);
}

digital_output_t DigitalOutputCreate(terminal_t terminal, digital_output_atributes_t atributes) {
    digital_output_t self = DigitalOutputAllocate();
    
    if (self) {
        memcpy(self->terminal, terminal, sizeof(struct terminal_s));
        memcpy(self->atributes, atributes, sizeof(struct digital_output_atributes_s));
    }

    return self;
}

bool DigitalOuputGetState(digital_output_t output) {
    bool state = HalDigitalGetState(output->terminal->port, output->terminal->pin);
    return (state ^ output->atributes->inverted);
}

void DigitalOuputSetState(digital_output_t output, bool state) {
    state = state ^ output->atributes->inverted;
    HalDigitalSetState( output->terminal->port,  output->terminal->pin, state);
}

void DigitalOuputActivate(digital_output_t output) {
    bool state = !output->atributes->inverted;
    HalDigitalSetState( output->terminal->port,  output->terminal->pin, state);
}

void DigitalOuputDeactivate(digital_output_t output) {
    bool state = output->atributes->inverted;
    HalDigitalSetState( output->terminal->port,  output->terminal->pin, state);
}

void DigitalOuputToggle(digital_output_t output) {
    HalDigitalToggle(output->terminal->port, output->terminal->pin);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
