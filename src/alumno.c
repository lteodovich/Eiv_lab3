/*********************************************************************************************************************
Copyright 2016-2026, Electrónica IV
Facultad de Ciencias Exactas y Tecnologia
Universidad Nacional de Tucuman
https://facetvirtual.facet.unt.edu.ar/course/view.php?id=165

Copyright 2016-2026, Esteban Volentini <evolentini@herrera.unt.edu.ar>

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

/** @file alumno.c
 ** @brief Declaraciones publicas del tipo alumno
 **/

/* === Headers files inclusions ==================================================================================== */
#include "alumno.h"
#include "config.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

struct alumno_s {
    char apellido[30];  /**< Apellido del alumno en formato de cadena C. */
    char nombre[30];    /**< Nombre del alumno en formato de cadena C. */
    char documento[13]; /**< Documento del alumno en formato de cadena C. */
};

#ifndef CREATE_MALLOC_ON

/** @brief Asigna una instancia de alumno de un pool predefinido.
 * @return Un puntero a una instancia de alumno, o NULL si no hay instancias disponibles.
 */
alumno_t AlumnoAllocate(void){
    static struct alumno_s inst_alumnos[ALUMNO_MAX_INSTANCES] = {0};
    alumno_t resultado = NULL;
    int ind;
    for (ind = 0; ind < ALUMNO_MAX_INSTANCES; ind++) {
        if (inst_alumnos[ind].documento[0] == '\0') { // Verifica si la instancia está libre
            resultado = &inst_alumnos[ind];
            break;
        }
    }
    return resultado;
}

#endif

/** @brief Crea una nueva instancia de alumno con los datos proporcionados.
 * @param apellido Apellido del alumno.
 * @param nombre Nombre del alumno.
 * @param documento Documento del alumno como número entero sin formato.
 * @return Un puntero a la nueva instancia de alumno creada, o NULL si hubo un error en la creación.
 */
alumno_t AlumnoCreate(const char * apellido, const char * nombre, const uint32_t documento){
    if (apellido == NULL || nombre == NULL) {
        return NULL;
    }

    #ifdef CREATE_MALLOC_ON

    alumno_t self = malloc(sizeof(struct alumno_s));

    #else

    alumno_t self = AlumnoAllocate();

    #endif

    if (self == NULL) {
        return NULL; // Error al asignar memoria
    }

    // Copia segura de las cadenas con límite de tamaño
    strncpy(self->apellido, apellido, sizeof(self->apellido) - 1);
    self->apellido[sizeof(self->apellido) - 1] = '\0'; // Asegura terminación nula

    strncpy(self->nombre, nombre, sizeof(self->nombre) - 1);
    self->nombre[sizeof(self->nombre) - 1] = '\0'; // Asegura terminación nula
        
    snprintf(self->documento, sizeof(self->documento), "%u", documento); // Convierte el número a cadena

    return self;
}

/** @brief Valida que una cadena contenga solo letras y espacios.
 * @param texto Cadena a validar.
 * @return 1 si la cadena es válida, 0 en caso contrario.
 */
static int es_texto_valido(const char *texto) {
    if (texto == NULL || strlen(texto) == 0) return 0;

    int tam_texto = strlen(texto);
    int i;// para mas compatibilidad
    for (i = 0; i < tam_texto; i++) {
        // Permite letras (a-z, A-Z) y espacios
        // El cast a (unsigned char) es necesario para isalpha e isspace y evitar comportamientos indefinidos con caracteres acentuados
        if (!isalpha((unsigned char)texto[i]) && !isspace((unsigned char)texto[i])) {
            return 0;
        }
    }

    return 1;
}

/** @brief Valida que el documento contenga solo dígitos numéricos.
 * @param numero Cadena del documento a validar.
 * @return 1 si el documento es válido, 0 en caso contrario.
 */
static int es_numero_entero_valido(const char *numero) {
    if (numero == NULL || strlen(numero) == 0) return 0;

    int tam_num = strlen(numero);
    int i;// para mas compatibilidad
    for (i = 0; i < tam_num; i++) {
        if (!isdigit((unsigned char)numero[i])) {
            return 0;
        }
    }

    // verifica que sea un entero >0 sin múltiples ceros al unicio
    // se pemite un solo 0 (en caso que sea el cero)
    if (tam_num > 1 && numero[0] == '0') {
        return 0;
    }

    return 1;
}

/** @brief Serializa un campo de texto en formato JSON.
 * @param cadena Puntero a la cadena donde se guardará el resultado.
 * @param espacio Tamaño disponible en la cadena.
 * @param campo Nombre del campo a serializar.
 * @param valor Valor del campo a serializar.
 * @return El número de caracteres escritos, o un valor negativo en caso de error.
 */
static int SerializaTexto(char * cadena, const int espacio, const char * campo, const char * texto) {
    if (cadena == NULL || campo == NULL || texto == NULL || espacio <= 0) return -1;

    int escrito = snprintf(cadena, espacio, "\"%s\":\"%s\"", campo, texto);
    if (escrito < 0 || escrito >= espacio) {
        return -1; // Error o espacio insuficiente
    }
    return escrito;
}

/** @brief Serializa un número en la cadena en formato JSON.
 * @param cadena Puntero a la cadena donde se guardará el número.
 * @param espacio Tamaño disponible en la cadena.
 * @param campo Nombre del campo JSON para el número.
 * @param numero Cadena que representa el número a serializar.
 * @return El número de caracteres escritos, o un valor negativo en caso de error.
 */
static int SerializaNumero(char * cadena, const int espacio, const char * campo, const char * numero) {
    if (cadena == NULL || campo == NULL || numero == NULL || espacio <= 0) return -1;

    int escrito = snprintf(cadena, espacio, "\"%s\":%s", campo, numero);
    if (escrito < 0 || escrito >= espacio) {
        return -1; // Error o espacio insuficiente
    }
    return escrito;
}

/** @brief Serializa una coma en la cadena.
 * @param cadena Puntero a la cadena donde se guardará la coma.
 * @param espacio Tamaño disponible en la cadena.
 * @return El número de caracteres escritos (1 para la coma), o un valor negativo en caso de error.
 */
static int SerializaComa(char * cadena, const int espacio) {
    if (cadena == NULL || espacio <= 0) return -1;

    int escrito = snprintf(cadena, espacio, ",");
    if (escrito < 0 || escrito >= espacio) {
        return -1; // Error o espacio insuficiente
    }
    return escrito;
}

/** @brief Agrega una cadena en formato JSON a la cadena principal.
 * @param ... Cadena en formato printf para agregar.
 */
#define AGREGAR_JSON(...) \
    do { \
        int escrito = snprintf(cadena + offset, espacio - offset, __VA_ARGS__); \
        if (escrito < 0 || escrito >= espacio - offset) return -1; \
        offset += escrito; \
    } while(0)

/** @brief Serializa los datos de un alumno en formato JSON.
 * @param self Puntero al alumno a serializar.
 * @param cadena Puntero a la cadena donde se guardará el JSON.
 * @param espacio Tamaño disponible en la cadena.
 * @return El número de caracteres escritos en la cadena, o un valor negativo en caso de error.
 */
int AlumnoSerializar(const alumno_t self, char * cadena, int espacio) {
    // Validaciones de punteros y espacio
    if (self == NULL || cadena == NULL || espacio <= 0) return 0;

    // Validación de contenido de los campos
    if (!es_texto_valido(self->nombre) || 
        !es_texto_valido(self->apellido) || 
        !es_numero_entero_valido(self->documento)) {
        return -2; // Retorna -2 si los datos no son válidos
    }
  
    int offset = 0;  // Cantidad de caracteres escritos hasta el momento
    int escrito = 0; // Resultado temporal de cada snprintf

    AGREGAR_JSON("{");
    
    escrito = SerializaTexto(cadena + offset, espacio - offset, "apellido", self->apellido);
    if (escrito < 0) return -1;
    offset += escrito;

    AGREGAR_JSON(",");

    escrito = SerializaTexto(cadena + offset, espacio - offset, "nombre", self->nombre);
    if (escrito < 0) return -1;
    offset += escrito;

    AGREGAR_JSON(",");

    escrito = SerializaNumero(cadena + offset, espacio - offset, "documento", self->documento);
    if (escrito < 0) return -1;
    offset += escrito;

    AGREGAR_JSON("}");

    return offset;
}

/* === End of documentation ==================================================================== */
