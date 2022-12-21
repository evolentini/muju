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

#ifndef SERIAL_H
#define SERIAL_H

/** \brief Serial asynconous port declarations
 **
 ** \addtogroup hal HAL
 ** \brief Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include <stdbool.h>
#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

//! Referencia a un descriptor para gestionar puerto serial asincronico
typedef struct serial_port_s * serial_port_t;

typedef void (*serial_event_t)(serial_port_t);

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Metodo para crear un puerto serial asincronico
 *
 * @param   port            Puerto serial aseincrónico que se utiliza
 * @param   bitrate         Velocidad de transmisión del puerto
 * @return  serial_port_t   Puntero al descriptor de la salida creada
 */
serial_port_t SerialPortCreate(uint8_t port, uint32_t bitrate);

/**
 * @brief Metodo para enviar datos por un puerto serial
 *
 * @param   port    Puntero al descriptor de la entrada
 * @return  true    La entrada esta activa
 * @return  false   La entrada esta inactiva
 */
uint8_t SerialPortTransmit(serial_port_t port, void const * const data, uint8_t size);

/**
 * @brief Metodo para consultar cambios en el estado de una entrada digital
 *
 * @param   input   Puntero al descriptor de la entrada
 * @return  true    La entrada tuvo cambios desde la ultima llamada
 * @return  false   La entrada no tuvo cambios desde la ultima llamada
 */
uint8_t SerialPortReceive(serial_port_t port, void const * const data, uint8_t size);

void SerialPortOnTransmited(serial_port_t port, serial_event_t handler);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* SERIAL_H */