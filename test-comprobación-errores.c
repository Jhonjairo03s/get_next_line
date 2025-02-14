/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gemini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:42:42 by jhvalenc          #+#    #+#             */
/*   Updated: 2025/02/06 15:58:38 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h> // Para INT_MAX

#define TEST_FILE_COUNT 7  // Número de archivos de prueba

// Función para comparar cadenas y mostrar errores
int compare_strings(const char *expected, const char *actual, int line_num, const char *filename) {
    if ((expected == NULL && actual != NULL) || (expected != NULL && actual == NULL) || (expected != NULL && strcmp(expected, actual) != 0)) {
        printf("Error en %s, línea %d:\n", filename ,line_num);
        printf("  Esperado: '%s'\n", expected ? expected : "(null)");
        printf("  Obtenido: '%s'\n", actual ? actual : "(null)");
        return 1; // Error
    }
    return 0; // Éxito
}

// Función principal de prueba
int test_get_next_line(const char *filename, const char *expected_lines[], int num_lines, int buffer_size) {
    int fd;
    char *line;
    int line_num = 1;
    int errors = 0;

    printf("Probando archivo: %s (BUFFER_SIZE=%d)\n", filename, buffer_size);

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        return 1; // Error
    }

    while (line_num <= num_lines) {
        line = get_next_line(fd);
        errors += compare_strings(expected_lines[line_num - 1], line, line_num, filename);
        free(line); // Liberar la memoria SIEMPRE
        line_num++;
    }

    // Comprobar si get_next_line devuelve NULL al final del archivo
    line = get_next_line(fd);
    errors += compare_strings(NULL, line, line_num, filename);
    free(line);

    close(fd);

    if (errors == 0) {
        printf("  %s: OK\n", filename);
    } else {
        printf("  %s: %d errores\n", filename, errors);
    }

    return errors;
}

int main() {
    int total_errors = 0;
    // int original_buffer_size = BUFFER_SIZE; // ELIMINADA

    const char *filenames[TEST_FILE_COUNT] = {
        "test_empty.txt",
        "test_one_line.txt",
        "test_multiple_lines.txt",
        "test_long_line.txt",
        "test_no_newline.txt",
        "test_mixed.txt",
        "test_very_long_lines.txt"
    };

    // Contenido esperado de cada archivo
    const char *expected_lines[][10] = {  // Ajusta el 10 si necesitas más líneas
        {}, // test_empty.txt
        {"This is a single line."}, // test_one_line.txt
        {"Line 1", "Line 2", "Line 3", ""}, // test_multiple_lines.txt
        {"This is a very long line that exceeds the buffer size by a significant amount.  It should still be read correctly by get_next_line, even if it requires multiple calls to read()."}, // test_long_line.txt
        {"This file has no newline at the end."}, // test_no_newline.txt
        {"Line 1\n", "Line 2", "", "Line 4 with trailing spaces   \n", "  Line 5 with leading spaces", ""}, // test_mixed.txt
        {"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
         "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
         "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"} //test_very_long_lines.txt
    };

    int num_lines[] = {0, 1, 4, 1, 1, 6, 3}; // Número de líneas esperadas


    // Crear los archivos de prueba
    FILE *fp;
    const char* file_contents[TEST_FILE_COUNT] = {
        "", //test_empty
        "This is a single line.\n", //test_one_line
        "Line 1\nLine 2\nLine 3\n", //test_multiple_lines
        "This is a very long line that exceeds the buffer size by a significant amount.  It should still be read correctly by get_next_line, even if it requires multiple calls to read().\n", //test_long_line
        "This file has no newline at the end.", //test_no_newline
        "Line 1\n\nLine 2\n\nLine 4 with trailing spaces   \n  Line 5 with leading spaces\n", //test_mixed
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\nBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\nCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n"
    };
    for (int i = 0; i < TEST_FILE_COUNT; i++) {
        fp = fopen(filenames[i], "w");
        if (fp == NULL) {
            perror("Error creando archivo de prueba");
            return 1;
        }
        fprintf(fp, "%s", file_contents[i]);
        fclose(fp);
    }



    // Pruebas con diferentes BUFFER_SIZE
    int buffer_sizes[] = {1, 2, 5, 10, 42, 100, 1024, 4096, INT_MAX}; // Casos de prueba
    int num_buffer_sizes = sizeof(buffer_sizes) / sizeof(buffer_sizes[0]);

    for (int j = 0; j < num_buffer_sizes; j++) {
      char define_buffer_size[100];
      sprintf(define_buffer_size, "-D BUFFER_SIZE=%d", buffer_sizes[j]);
      char compile_command[512];

      // Compila get_next_line con el BUFFER_SIZE actual
      snprintf(compile_command, sizeof(compile_command), "gcc -Wall -Wextra -Werror %s get_next_line.c get_next_line_utils.c -o get_next_line", define_buffer_size);
      if (system(compile_command) != 0)
      {
        printf("Error compilando con BUFFER_SIZE=%d\n", buffer_sizes[j]);
        total_errors++;
        continue; // Pasar al siguiente BUFFER_SIZE
      }

        //Si la compilación fue exitosa, ejecuta las pruebas
        printf("Ejecutando pruebas con BUFFER_SIZE=%d\n", buffer_sizes[j]);
        for (int i = 0; i < TEST_FILE_COUNT; i++) {
            total_errors += test_get_next_line(filenames[i], (const char **)expected_lines[i], num_lines[i], buffer_sizes[j]);
        }
    }


    printf("\n------------------------------\n");
    if (total_errors == 0) {
        printf("TODAS LAS PRUEBAS PASADAS!\n");
    } else {
        printf("Total de errores: %d\n", total_errors);
    }
    printf("------------------------------\n");


    return total_errors;
}
