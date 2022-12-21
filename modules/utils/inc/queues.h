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

#ifndef QUEUE_H
#define QUEUE_H

/** \brief Abstract circular queue declarations
 **
 ** Implements a circular queue following the Abstract Data Type pattern.
 **
 ** \addtogroup utils Utils
 ** \brief Utilities as abstract data types
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

//! Referencia a un descriptor para gestionar un puerto serial
typedef struct queue_s * queue_t;

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Metodo para crear una cola circular
 *
 * @remark El parametro size solo es válido si las colas se utilizan creando memoria dinamica
 * lo que se controla con el macro
 *
 * @param   size        Cantidad de datos maxima a almacenar en la cola
 * @return  queue_t     Puntero al descriptor de la cola creada
 */
queue_t QueueCreate(uint16_t size);

/**
 * @brief Metodo para agregar datos a una cola circular
 *
 * @param   queue       Puntero al descriptor de la cola circular
 * @param   buffer      Vector que contiene la cadena de bytes a encolar
 * @param   size        Cantidad de datos que se quieren ingresar a la cola
 * @return  uint16_t    Cantidad de bytes efectivamente encolados
 */
uint16_t QueuePut(queue_t queue, const void * buffer, uint16_t size);

/**
 * @brief Metodo para obtener datos a una cola circular
 *
 * @param   queue       Puntero al descriptor de la cola circular
 * @param   buffer      Vector donde se almacenara la cadena de bytes a recuperar
 * @param   size        Cantidad de datos que se quieren recuperar de la cola
 * @return  uint16_t    Cantidad de bytes efectivamente recuperados
 */
uint16_t QueueGet(queue_t queue, void * buffer, uint16_t size);

/**
 * @brief Metodo para destruir una cola circular
 *
 * @param   queue   Puntero al descriptor de la cola a destruir
 */
void QueueDestroy(queue_t queue);

/**
 * @brief Metodo para obtener el tamaño de una cola circular
 * 
 * @param   queue       Puntero al descriptor de la cola circular
 * @return  uint16_t    Cantidad de byte que puede almacenar la cola
 */
uint16_t QueueSize(queue_t queue);

/**
 * @brief Metodo para obtener el espacio disponible en una cola circular
 * 
 * @param   queue       Puntero al descriptor de la cola circular
 * @return  uint16_t    Cantidad de bytes diponibles en la cola
 */
uint16_t QueueAvaiable(queue_t queue);

/**
 * @brief Metodo para obtener el espacio ocupado en una cola circular
 * 
 * @param   queue       Puntero al descriptor de la cola circular
 * @return  uint16_t    Cantidad de bytes ocupados en la cola
 */
uint16_t QueueUsed(queue_t queue);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* QUEUE_H */