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

#include "hal_soc.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable definitions ============================================================ */

static bool states[8][32] = {0};

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private function implementation ========================================================= */

void Mostrar(int fila, int columna, bool puerto[8]) {
    const char * FORMATO = "B%d=%d";
    const int ESPACIOS = 5;
    for (int indice = 7; indice >= 0; indice--) {
        mvprintw(fila, 5 * indice + columna, FORMATO, indice, puerto[indice] );
    }
}

/* === Public function implementation ========================================================= */

void HalBoardInit(void) {
    WINDOW * pantalla;
    if ((pantalla = initscr()) == NULL ) {
        fprintf(stderr, "Error al configurar ncurses.\n");
        exit(EXIT_FAILURE);
    }

     // No mostrar lo que se escribe
    noecho();
    // Ocultar el cursor
    curs_set(0);
    // Esperar solo medio segundo por una tecla
    timeout(100);

    BoardInit();
} 

bool HalDigitalGetState(uint8_t port, uint8_t pin) {
    return states[port][pin];
}

void HalDigitalSetState(uint8_t port, uint8_t pin, bool state) {
    static const char format[] = "Digital output %d of port %d has chaged its state, now are %s\r\n";

    states[port][pin] = state;
    printf(format, pin, port, state ? "true" : "flase");

    Mostrar(0, 2, states[0]);

}

void HalDigitalToggle(uint8_t port, uint8_t pin) {
    HalDigitalSetState(port, pin, !HalDigitalGetState(port, pin));
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
