/*********************************************************************************************************************
Copyright 2016-2026, Electrónica IV
Facultad de Ciencias Exactas y Tecnologia
Universidad Nacional de Tucuman
https://facetvirtual.facet.unt.edu.ar/course/view.php?id=165

Copyright 2016-2025, Esteban Volentini <evolentini@herrera.unt.edu.ar>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

#ifndef ALUMNO_H_
#define ALUMNO_H_

/** @file alumno.h
 ** @brief Declaraciones publicas del tipo alumno
 **/

/* === Headers files inclusions ==================================================================================== */
#include <stdio.h>
#include <stdint.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/** tipo de dato sin estructura que modela al objeto alumno. */
typedef struct alumno_s * alumno_t;

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Crea una nueva instancia del objeto alumno con los datos.
 * @param apellido Apellido del alumno como cadena C.
 * @param nombre Nombre del alumno como cadena C.
 * @param documento Documento del alumno como número entero sin signo de 32 bits.
 * @return Puntero a la nueva instancia de alumno o NULL en caso de error.
 */
alumno_t AlumnoCreate(const char * apellido, const char * nombre, const uint32_t documento);

/**
 * @brief Serializa la estructura alumno a un formato JSON.
 * @param alumno Puntero a la instancia del alumno.
 * @param cadena Búfer donde se guardará el JSON resultante.
 * @param espacio Tamaño máximo del búfer.
 * @return Cantidad de caracteres escritos o -1 si el espacio es insuficiente o -2 si los datos no son válidos.
 */
int AlumnoSerializar(const alumno_t self, char * cadena, int espacio);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ALUMNO_H_ */

/* === End of documentation ==================================================================== */
