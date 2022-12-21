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

/** \brief Abstract circular queue definitions
 **
 ** Implements a circular queue following the Abstract Data Type pattern.
 **
 ** \addtogroup utils Utils
 ** \brief Utilities as abstract data types
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "queues.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* === Macros definitions ====================================================================== */

//! Macro to convert the argument string to a constant string
#define STR(x) #x

//! Macro to convert the argument value to a constant string
#define XSTR(x) STR(x)

//! Include global project config file if it's defined
#ifdef CONFIG_FILE
#include XSTR(CONFIG_FILE)
#endif

//! Include queue  config file if it's defined
#ifdef QUEUE_CONFIG
#include XSTR(QUEUE_CONFIG)
#endif

#ifdef USE_FREERTOS
#include "FreeRTOS.h"
#include "semphr.h"
#define USE_MUTEX
#define mutex_t SemaphoreHandle_t
#define MutexCreate(mutex) mutex = xSemaphoreCreateMutex()
#define MutexIsValid(mutex) (mutex = !NULL)
#define MutexAdquire(mutex) xSemaphoreTake(mutex, portMAX_DELAY)
#define MutexRelease(mutex) xSemaphoreGive(mutex)
#define MutexDestroy(mutex) vSemaphoreDelete(mutex)
#endif

#ifdef USE_MUTEX
#ifndef mutex_t
#error "To use mutex functions you must define a mutex data type mutex_t"
#endif

#ifndef MutexCreate
#error "To use mutex functions you must define a function to create the mutex"
#endif

#ifndef MutexIsValid
#error "To use mutex functions you must define a function to test if the mutex is valid"
#endif

#ifndef MutexAdquire
#error "To use mutex functions you must define a function to adquire the mutex"
#endif

#ifndef MutexRelease
#error "To use mutex functions you must define a function to release the mutex"
#endif

#ifndef MutexDestroy
#error "To use mutex functions you must define a function to destroy the mutex"
#endif
#else
#define MutexCreate(mutex)
#define MutexIsValid(mutex)
#define MutexAdquire(mutex)
#define MutexRelease(mutex)
#define MutexDestroy(mutex)
#endif

#if defined(USE_STATIC_MEMORY) && defined(USE_MUTEX) && !defined(USE_SINGLE_MUTEX)
#define USE_SINGLE_MUTEX
#endif

#ifdef USE_SINGLE_MUTEX
#define QueueMutexAdquire(queue) MutexAdquire(global_mutex)
#define QueueMutexRelease(queue) MutexRelease(global_mutex)
#define QueueMutexDestroy(queue)
#else
#define QueueMutexAdquire(queue) MutexAdquire(queue->mutex)
#define QueueMutexRelease(queue) MutexRelease(queue->mutex)
#define QueueMutexDestroy(queue) MutexDestroy(queue->mutex)
#endif

//! Defines the maximum number of instances when using static memory
#ifndef QUEUE_INSTANCES
#define QUEUE_INSTANCES 4
#endif

//! Defines the size of the queue when using static memory
#ifndef QUEUE_SIZE
#define QUEUE_SIZE 128
#endif

/* === Private data type declarations ========================================================== */

struct queue_s {
    uint16_t head;  //!< Index of first data stored, used to get data
    uint16_t tail;  //!< Index of first space avaiable, used to put data
    uint16_t count; //!< Number of bytes stored in the queue
#if defined(USE_STATIC_MEMORY)
    bool allocated;            //!< Flag to indicate that the descriptor is in use
    uint8_t bytes[QUEUE_SIZE]; //!< Statically allocated queue storage
#else
    uint16_t size; //!< Dynamically allocated queue size
    void *bytes;   //!< Pointer to dynamically allocated queue storage
#if defined(USE_MUTEX) && !defined(USE_SINGLE_MUTEX)
    mutex_t mutex;
#endif
#endif
};

/* === Private variable declarations =========================================================== */

#if defined(USE_MUTEX) && defined(USE_SINGLE_MUTEX)
mutex_t global_mutex;
#endif

/* === Private function declarations =========================================================== */

// Function para asignar un descriptor para crear un nuevo puerto serial
static queue_t CreateDescriptor(uint16_t size);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

#if USE_SINGLE_MUTEX
static bool CreateGlobalMutex(void) {
    static bool mutex_created = false;

    if (!mutex_created) {
        MutexCreate(global_mutex);
        mutex_created = MutexIsValid(global_mutex);
    }
    return mutex_created;
}
#define CreatePrivateMuex(queue)
#else
#define CreateGlobalMutex()
queue_t CreatePrivateMuex(queue_t queue) {
    MutexCreate(queue->mutex);
    if (!MutexIsValid(descriqueueptor->mutex)) {
        free(queue->bytes);
        free(queue);
        queue = NULL;
    }
    return queue
}
#endif

static queue_t CreateDescriptor(uint16_t size) {
    queue_t descriptor = NULL;

#ifdef USE_STATIC_MEMORY
    static struct queue_s instances[QUEUE_INSTANCES] = {0};

    if (CreateGlobalMutex()) {
        MutexAdquire(global_mutex);
        for (int index = 0; index < QUEUE_INSTANCES; index++) {
            if (!instances[index].allocated) {
                instances[index].allocated = true;
                descriptor = &instances[index];
                break;
            }
        }
        MutexRelease(global_mutex);
    }
#else
    descriptor = malloc(sizeof(struct queue_s));
    if (descriptor) {
        descriptor->bytes = malloc(size);
    }
    if (descriptor->bytes) {
        descriptor->size = size;
    } else {
        free(descriptor);
        descriptor = NULL;
    }
#if defined(USE_MUTEX) && !defined(USE_SINGLE_MUTEX)
#endif
#endif
    return descriptor;
}

/* === Public function implementation ========================================================= */

queue_t QueueCreate(uint16_t size) {
    queue_t queue;

    queue = CreateDescriptor(size);
    if (queue != NULL) {
        queue->head = 0;
        queue->tail = 0;
        queue->count = 0;
    }
    return queue;
}

uint16_t QueueSize(queue_t queue) {
    uint16_t result = 0;

    if (queue != NULL) {
#if defined(USE_STATIC_MEMORY)
        result = QUEUE_SIZE;
#else
        result = queue->size;
#endif
    }
    return result;
}

uint16_t QueueUsed(queue_t queue) {
    uint16_t result = 0;

    if (queue != NULL) {
        result = queue->count;
    }
    return result;
}

uint16_t QueueAvaiable(queue_t queue) {
    uint16_t result = 0;

    if (queue != NULL) {
        result = QueueSize(queue) - queue->count;
    }
    return result;
}

uint16_t QueuePut(queue_t queue, const void *buffer, uint16_t size) {
    uint16_t remaining;
    uint16_t count = 0;

    if ((queue != NULL) && (buffer != NULL) && (size != 0)) {
        QueueMutexAdquire(queue);

        count = QueueAvaiable(queue);
        if (count > size) {
            count = size;
        }

        remaining = QueueSize(queue) - queue->tail;
        if (remaining >= count) {
            memcpy(queue->bytes + queue->tail, buffer, count);
            queue->tail = queue->tail + count;
        } else {
            memcpy(queue->bytes + queue->tail, buffer, remaining);
            queue->tail = count - remaining;
            memcpy(queue->bytes, buffer + remaining, queue->tail);
        }
        queue->count = queue->count + count;

        QueueMutexRelease(queue);
    }
    return count;
}

uint16_t QueueGet(queue_t queue, void *buffer, uint16_t size) {
    uint16_t remaining;
    uint16_t count = 0;

    if ((queue != NULL) && (buffer != NULL) && (size != 0)) {
        QueueMutexAdquire(queue);

        count = QueueUsed(queue);
        if (count > size) {
            count = size;
        }

        remaining = QueueSize(queue) - queue->head;
        if (remaining >= count) {
            memcpy(buffer, queue->bytes + queue->head, count);
            queue->head = queue->head + count;
        } else {
            memcpy(buffer, queue->bytes + queue->head, remaining);
            queue->head = count - remaining;
            memcpy(buffer + remaining, queue->bytes, queue->head);
        }
        queue->count = queue->count - count;

        QueueMutexRelease(queue);
    }
    return count;
}

void QueueDestroy(queue_t queue) {
    if (queue != NULL) {
#if defined(USE_STATIC_MEMORY)
        queue->allocated = false;
#else
        QueueMutexDestroy(queue);
        free(queue->bytes);
        free(queue);
#endif
    }
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
