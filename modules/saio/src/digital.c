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
#include <string.h>

/* === Macros definitions ====================================================================== */
#ifndef HAL_USE_STATIC_ALOCATION
#ifndef HAL_USE_DYNAMIC_ALOCATION
#define HAL_USE_STATIC_ALOCATION
#endif
#endif

#ifdef HAL_USE_STATIC_ALOCATION
#ifndef HAL_DIGITAL_INPUT_INSTANCES
#define HAL_DIGITAL_INPUT_INSTANCES 10
#endif

#ifndef HAL_DIGITAL_OUTPUT_INSTANCES
#define HAL_DIGITAL_OUTPUT_INSTANCES 10
#endif
#endif
/* === Private data type declarations ========================================================== */

struct digital_input_s {
    struct hal_gpio_bit_s * gpio;
    struct digital_input_atributes_s atributes[1];
    bool last_state;
#ifdef HAL_USE_STATIC_ALOCATION
    bool allocated;
#endif
};

struct digital_output_s {
    struct hal_gpio_bit_s * gpio;
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
    static struct digital_input_s instances[HAL_DIGITAL_INPUT_INSTANCES] = {0};

    for (int index = 0; index < HAL_DIGITAL_INPUT_INSTANCES; index++) {
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
    static struct digital_output_s instances[HAL_DIGITAL_OUTPUT_INSTANCES] = {0};

    for (int index = 0; index < HAL_DIGITAL_OUTPUT_INSTANCES; index++) {
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

digital_input_t DigitalInputCreate(hal_gpio_bit_t gpio, digital_input_atributes_t atributes) {
    digital_input_t self = DigitalInputAllocate();

    if (self) {
        self->gpio = gpio;
        memcpy(self->atributes, atributes, sizeof(struct digital_input_atributes_s));
        self->last_state = DigitalInputGetState(self);
    }

    return self;
}

bool DigitalInputGetState(digital_input_t input) {
    bool state = GpioGetState(input->gpio);
    return (state ^ input->atributes->inverted);
}

bool DigitalInputHasChanged(digital_input_t input) {
    bool result = false;

    if (input) {
        bool state = DigitalInputGetState(input);
        result = state != input->last_state;
        input->last_state = state;
    }
    return result;
}

bool DigitalInputHasActivated(digital_input_t input) {
    bool result = false;

    if (input) {
        bool state = DigitalInputGetState(input);
        result = state && !input->last_state;
        input->last_state = state;
    }
    return result;
}

bool DigitalInputHasDeactivated(digital_input_t input) {
    bool result = false;

    if (input) {
        bool state = DigitalInputGetState(input);
        result = !state && !input->last_state;
        input->last_state = state;
    }
    return result;
}

digital_output_t DigitalOutputCreate(hal_gpio_bit_t gpio, digital_output_atributes_t atributes) {
    digital_output_t self = DigitalOutputAllocate();

    if (self) {
        self->gpio = gpio;
        memcpy(self->atributes, atributes, sizeof(struct digital_output_atributes_s));
    }

    return self;
}

bool DigitalOutputGetState(digital_output_t output) {
    bool state = GpioGetState(output->gpio);
    return (state ^ output->atributes->inverted);
}

void DigitalOutputSetState(digital_output_t output, bool state) {
    state = state ^ output->atributes->inverted;
    GpioSetState(output->gpio, state);
}

void DigitalOutputActivate(digital_output_t output) {
    bool state = !output->atributes->inverted;
    GpioSetState(output->gpio, state);
}

void DigitalOutputDeactivate(digital_output_t output) {
    bool state = output->atributes->inverted;
    GpioSetState(output->gpio, state);
}

void DigitalOutputToggle(digital_output_t output) {
    GpioBitToogle(output->gpio);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
