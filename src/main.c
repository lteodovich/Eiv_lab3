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

/** @file main.c
 ** @brief Punto de entrada de la aplicacion
 **/

/* === Headers files inclusions ================================================================ */

#include "alumno.h"

#include <stdio.h>
#include <stdbool.h>

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private function declarations =========================================================== */

/* === Private variable definitions ============================================================ */

/* === Public variable definition  ============================================================= */

/* === Private function definitions ============================================================ */

/* === Public function implementation ========================================================== */

/**
 * @brief Ejecuta el flujo principal del programa.
 * @return int Retorna 0 cuando la ejecucion finaliza correctamente.
 */
int main(void) {

    /** @brief Instancia local con los datos del alumno de ejemplo. */    
    alumno_t puntero_alum = AlumnoCreate("Perez", "Pedro", (uint32_t)(123456789));

    char serial_json[256];
    //char serial_json[10];
    
    int len = AlumnoSerializar(puntero_alum, serial_json, sizeof(serial_json));

    if (len > 0) {
        printf("JSON serializado: %s\n", serial_json);
    } else {
        if (len == -1) {
            printf("Error: Espacio insuficiente para serializar el alumno.\n");
        }
        if (len == -2) {
            //codigos de caracteres especiales en octal
            //á: \240, é: \202, í: \241, ó: \242, ú: \243
            //ñ (minúscula): \244, Ñ (mayúscula): \245, ü	\201
            printf("Error: Datos del alumno no v\240lidos para serializaci\242n.\n");
        }
    }

    return 0;
}

/* === End of documentation ==================================================================== */
