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

#include "board.h"
#include "chip.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

typedef struct clock_states_s {
    CHIP_CGU_BASE_CLK_T clk; /* Base clock */
    CHIP_CGU_CLKIN_T clkin;  /* Base clock source, see UM for allowable souorces per base clock */
    bool autoblock_enab;     /* Set to true to enable autoblocking on frequency change */
    bool powerdn;            /* Set to true if the base clock is initially powered down */
} clock_states_t;

typedef struct gpio_pins_config_s {
	uint8_t port:4;		/* Pin group */
	uint8_t pin:5;		/* Pin number */
    uint8_t gpio:3;
    uint8_t bit:5;
    bool output:1;
	uint16_t mode:12;	/* Pin mode and function for SCU */
} gpio_pins_config_t;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

// CHIP module configuration. Edu-CIAA clock is based on a 12 Mhz crystal.
const uint32_t ExtRateIn = 0;
const uint32_t OscRateIn = 12000000;

/* === Private variable definitions ============================================================ */

static const gpio_pins_config_t INIT_PIN_MUXING[] = {
        /* Board LEDs */
        { 
            .port = LED_R_PORT, .pin = LED_R_PIN, .gpio = LED_R_GPIO, .bit = LED_R_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC4)
        }, { 
            .port = LED_G_PORT, .pin = LED_G_PIN, .gpio = LED_G_GPIO, .bit = LED_G_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC4)
        }, { 
            .port = LED_B_PORT, .pin = LED_B_PIN, .gpio = LED_B_GPIO, .bit = LED_B_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC4)
        }, { 
            .port = LED_1_PORT, .pin = LED_1_PIN, .gpio = LED_1_GPIO, .bit = LED_1_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC0)
        }, { 
            .port = LED_2_PORT, .pin = LED_2_PIN, .gpio = LED_2_GPIO, .bit = LED_2_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC0)
        }, { 
            .port = LED_3_PORT, .pin = LED_3_PIN, .gpio = LED_3_GPIO, .bit = LED_3_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC0)
        },

        /* Board Buttons */
        { 
            .port = TEC_1_PORT, .pin = TEC_1_PIN, .gpio = TEC_1_GPIO, .bit = TEC_1_BIT,
            .output = false, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | SCU_MODE_FUNC0)
        }, { 
            .port = TEC_2_PORT, .pin = TEC_2_PIN, .gpio = TEC_2_GPIO, .bit = TEC_2_BIT,
            .output = false, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | SCU_MODE_FUNC0)
        }, { 
            .port = TEC_3_PORT, .pin = TEC_3_PIN, .gpio = TEC_3_GPIO, .bit = TEC_3_BIT,
            .output = false, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | SCU_MODE_FUNC0)
        }, { 
            .port = TEC_4_PORT, .pin = TEC_4_PIN, .gpio = TEC_4_GPIO, .bit = TEC_4_BIT,
            .output = false, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | SCU_MODE_FUNC0)
        },

        /* Segments rows */
        { 
            .port = SEGMENT_A_PORT, .pin = SEGMENT_A_PIN, .gpio = SEGMENT_A_GPIO, .bit = SEGMENT_A_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC0)
        }, { 
            .port = SEGMENT_B_PORT, .pin = SEGMENT_B_PIN, .gpio = SEGMENT_B_GPIO, .bit = SEGMENT_B_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC0)
        }, { 
            .port = SEGMENT_C_PORT, .pin = SEGMENT_C_PIN, .gpio = SEGMENT_C_GPIO, .bit = SEGMENT_C_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC0)
        }, { 
            .port = SEGMENT_D_PORT, .pin = SEGMENT_D_PIN, .gpio = SEGMENT_D_GPIO, .bit = SEGMENT_D_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC0)
        }, { 
            .port = SEGMENT_E_PORT, .pin = SEGMENT_E_PIN, .gpio = SEGMENT_E_GPIO, .bit = SEGMENT_E_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC0)
        }, { 
            .port = SEGMENT_F_PORT, .pin = SEGMENT_F_PIN, .gpio = SEGMENT_F_GPIO, .bit = SEGMENT_F_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC0)
        }, { 
            .port = SEGMENT_G_PORT, .pin = SEGMENT_G_PIN, .gpio = SEGMENT_G_GPIO, .bit = SEGMENT_G_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC0)
        }, { 
            .port = SEGMENT_DP_PORT, .pin = SEGMENT_DP_PIN, .gpio = SEGMENT_DP_GPIO, .bit = SEGMENT_DP_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC4)
        },

        /* Digits cols */
        { 
            .port = DIGIT_1_PORT, .pin = DIGIT_1_PIN, .gpio = DIGIT_1_GPIO, .bit = DIGIT_1_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC0)
        }, { 
            .port = DIGIT_2_PORT, .pin = DIGIT_2_PIN, .gpio = DIGIT_2_GPIO, .bit = DIGIT_2_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC0)
        }, { 
            .port = DIGIT_3_PORT, .pin = DIGIT_3_PIN, .gpio = DIGIT_3_GPIO, .bit = DIGIT_3_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC0)
        }, { 
            .port = DIGIT_4_PORT, .pin = DIGIT_4_PIN, .gpio = DIGIT_4_GPIO, .bit = DIGIT_4_BIT,
            .output = true, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC0)
        },

        /* Keyboard Functions 1 to 4 */
        { 
            .port = KEY_F1_PORT, .pin = KEY_F1_PIN, .gpio = KEY_F1_GPIO, .bit = KEY_F1_BIT,
            .output = false, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC4)
        }, { 
            .port = KEY_F2_PORT, .pin = KEY_F2_PIN, .gpio = KEY_F2_GPIO, .bit = KEY_F2_BIT,
            .output = false, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC4)
        }, { 
            .port = KEY_F3_PORT, .pin = KEY_F3_PIN, .gpio = KEY_F3_GPIO, .bit = KEY_F3_BIT,
            .output = false, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC4)
        }, { 
            .port = KEY_F4_PORT, .pin = KEY_F4_PIN, .gpio = KEY_F4_GPIO, .bit = KEY_F4_BIT,
            .output = false, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC4)
        },

        /* Acept and Cancel keys */
        { 
            .port = KEY_ACCEPT_PORT, .pin = KEY_ACCEPT_PIN, .gpio = KEY_ACCEPT_GPIO, .bit = KEY_ACCEPT_BIT,
            .output = false, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC4)
        }, { 
            .port = KEY_CANCEL_PORT, .pin = KEY_CANCEL_PIN, .gpio = KEY_CANCEL_GPIO, .bit = KEY_CANCEL_BIT,
            .output = false, .mode = (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC4)
        }
};


/* Initial base clock states are mostly on */
static const clock_states_t INIT_CLK_STATES[] = {
        /* Clocks derived from dividers */
        {CLK_BASE_USB0, CLKIN_IDIVD, true, true}
};

/* === Private function implementation ========================================================= */

void Board_SetupMuxing(void) {
	for (int index = 0; index < sizeof(INIT_PIN_MUXING) / sizeof(gpio_pins_config_t); index++ ) {
        const gpio_pins_config_t * config = &INIT_PIN_MUXING[index];
		Chip_SCU_PinMuxSet(config->port, config->pin, config->mode);
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, config->gpio, config->bit, false);
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, config->gpio, config->bit, config->output);
	}
}

void Board_SetupClocking(void) {
    Chip_CREG_SetFlashAcceleration(MAX_CLOCK_FREQ);
    Chip_SetupCoreClock(CLKIN_CRYSTAL, MAX_CLOCK_FREQ, true);

    /* Setup system base clocks and initial states. This won't enable and
       disable individual clocks, but sets up the base clock sources for
       each individual peripheral clock. */
    for (uint32_t i = 0; i < (sizeof(INIT_CLK_STATES) / sizeof(clock_states_t)); ++i) {
        const clock_states_t *c = &INIT_CLK_STATES[i];
        Chip_Clock_SetBaseClock(c->clk, c->clkin, c->autoblock_enab,
                                c->powerdn);
    }

    /* Reset and enable 32Khz oscillator */
    LPC_CREG->CREG0 &= ~((1 << 3) | (1 << 2));
    LPC_CREG->CREG0 |= (1 << 1) | (1 << 0);
}

/* === Public function implementation ========================================================= */

/* Set up and initialize hardware prior to call to main */
void Board_SystemInit(void)
{
    /* Setup system clocking and memory. This is done early to allow the
       application and tools to clear memory and use scatter loading to
       external memory. */
    Board_SetupMuxing();
    Board_SetupClocking();
}

void Board_Init(void) {
    SystemCoreClockUpdate();
}

void BoardInit(void) {

}

void DelayMs(uint32_t value) {
    for(int index = 0; index < value; index++) {
        for(int delay = 0; delay < 25000; delay++) {
            __asm ("NOP");
        }
    }
}

void SegmentsTurnOff(void) {
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 0, 0x0F);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 2, 0x7F);
}

void SegmentsSetState(uint8_t segments) {
    Chip_GPIO_SetValue(LPC_GPIO_PORT, 2, (segments) & 0x7F);
}

void DigitsTurnOn(uint8_t digit) {
    Chip_GPIO_SetValue(LPC_GPIO_PORT, 0, (1 << (digit)) & 0x0F);
}

uint32_t BoardGetSystemCoreClock(void) {
    return SystemCoreClock;
}

#if USE_FREERTOS
    #include "FreeRTOSConfig.h"
    __attribute__ ((section(".data.$RAM2"))) uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
#endif

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
