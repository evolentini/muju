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

/** \brief Abstract circular queue tests
 **
 ** Implements a circular queue following the Abstract Data Type pattern.
 **
 ** \addtogroup utils Utils
 ** \brief Utilities as abstract data types
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "queues.h"
#include "unity.h"
#include <string.h>

/* === Macros definitions ====================================================================== */

#define QUEUE_SIZE 16

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================= */

void test_queue_create_and_destroy(void) {
    queue_t queue = QueueCreate(QUEUE_SIZE);
    TEST_ASSERT_NOT_NULL(queue);
    TEST_ASSERT_EQUAL(QUEUE_SIZE, QueueSize(queue));
    QueueDestroy(queue);
}

void test_invalid_descriptor(void) {
    TEST_ASSERT_EQUAL(0, QueueSize(NULL));
    TEST_ASSERT_EQUAL(0, QueueUsed(NULL));
    TEST_ASSERT_EQUAL(0, QueueAvaiable(NULL));
    TEST_ASSERT_EQUAL(0, QueuePut(NULL, NULL, 0));
    TEST_ASSERT_EQUAL(0, QueueGet(NULL, NULL, 0));
    QueueDestroy(NULL);
}

void test_invalid_pointers_and_sizes(void) {
    static const char DATA[] = "1234";
    char data[4];

    queue_t queue = QueueCreate(QUEUE_SIZE);
    TEST_ASSERT_EQUAL(0, QueuePut(queue, NULL, 4));
    TEST_ASSERT_EQUAL(0, QueueGet(queue, NULL, 4));
    TEST_ASSERT_EQUAL(0, QueuePut(queue, DATA, 0));
    TEST_ASSERT_EQUAL(0, QueueGet(queue, data, 0));
    QueueDestroy(queue);
}

void test_queue_put_and_get_data(void) {
    static const char DATA[] = "1234";
    char data[4];

    queue_t queue = QueueCreate(QUEUE_SIZE);
    TEST_ASSERT_EQUAL(4, QueuePut(queue, DATA, 4));
    TEST_ASSERT_EQUAL(4, QueueUsed(queue));
    TEST_ASSERT_EQUAL(QUEUE_SIZE - 4, QueueAvaiable(queue));
    TEST_ASSERT_EQUAL(4, QueueGet(queue, data, 4));
    TEST_ASSERT_EQUAL_CHAR_ARRAY(DATA, data, 4);
}

void test_queue_put_and_get_data_twice(void) {
    static const char DATA[] = "12345678";
    char data[8];

    queue_t queue = QueueCreate(QUEUE_SIZE);
    TEST_ASSERT_EQUAL(4, QueuePut(queue, DATA, 4));
    TEST_ASSERT_EQUAL(4, QueuePut(queue, &DATA[4], 4));
    TEST_ASSERT_EQUAL(4, QueueGet(queue, data, 4));
    TEST_ASSERT_EQUAL(4, QueueGet(queue, &data[4], 4));
    TEST_ASSERT_EQUAL_CHAR_ARRAY(DATA, data, 8);
}

void test_queue_put_data_to_full(void) {
    static const char DATA[] = "1234567890AB";
    char data[24];

    queue_t queue = QueueCreate(QUEUE_SIZE);
    TEST_ASSERT_EQUAL(12, QueuePut(queue, DATA, 12));
    TEST_ASSERT_EQUAL(4, QueuePut(queue, DATA, 12));
    TEST_ASSERT_EQUAL(16, QueueGet(queue, data, 24));
    TEST_ASSERT_EQUAL_CHAR_ARRAY("1234567890AB1234", data, 16);
}

void test_queue_put_and_get_data_to_turn_arround_pointers(void) {
    static const char DATA[] = "1234567890AB";
    char data[12];

    queue_t queue = QueueCreate(QUEUE_SIZE);
    TEST_ASSERT_EQUAL(12, QueuePut(queue, DATA, 12));
    TEST_ASSERT_EQUAL(12, QueueGet(queue, data, 12));

    memset(data, 0, sizeof(data));
    TEST_ASSERT_EQUAL(8, QueuePut(queue, DATA, 8));
    TEST_ASSERT_EQUAL(8, QueueGet(queue, data, 8));
    TEST_ASSERT_EQUAL_CHAR_ARRAY(DATA, data, 8);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
