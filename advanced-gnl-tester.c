/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced-gnl-tester.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:44:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2025/02/06 16:44:04 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"

typedef struct s_test_case {
    char *name;
    char *content;
    char **expected;
    int lines;
} t_test_case;

void create_test_file(const char *name, const char *content) {
    FILE *fp = fopen(name, "w");
    if (!fp) {
        printf(RED "Error al crear archivo %s\n" RESET, name);
        exit(1);
    }
    fputs(content, fp);
    fclose(fp);
}

// Función test_multiple_fds ELIMINADA o COMENTADA

int test_gnl(const char *filename, char **expected, int num_lines) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) return 1;

    int errors = 0;
    char *line;

    for (int i = 0; i < num_lines; i++) {
        line = get_next_line(fd);
        if ((!line && expected[i]) || (line && !expected[i]) ||
            (line && expected[i] && strcmp(line, expected[i]) != 0)) {
            printf(RED "Error en %s, línea %d\n" RESET, filename, i + 1);
            printf("Esperado: %s\n", expected[i] ? expected[i] : "NULL");
            printf("Obtenido: %s\n", line ? line : "NULL");
            errors++;
        }
        free(line);
    }

    line = get_next_line(fd);
    if (line) {
        printf(RED "Error: se esperaba EOF en %s\n" RESET, filename); // Mensaje original
        // Opcional: Mensaje alternativo para el caso sin bonus:
        // printf(YELLOW "Nota: No se esperaba más salida después de esta línea (comportamiento normal sin bonus)\n" RESET);
        free(line);
        errors++;
    }

    close(fd);
    return errors;
}

int main(void) {
    t_test_case tests[] = {
        {
            "special_chars.txt",
            "ñÑáéíóúÁÉÍÓÚ\n€∞≠≈\n\x01\x02\x03\n",
            (char *[]){"ñÑáéíóúÁÉÍÓÚ\n", "€∞≠≈\n", "\x01\x02\x03\n"},
            3
        },
        {
            "very_long.txt",
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n",
            (char *[]){"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"},
            1
        },
        {
            "only_nl.txt",
            "\n\n\n\n\n",
            (char *[]){"\n", "\n", "\n", "\n", "\n"},
            5
        },
        {
            "mixed_empty.txt",
            "Línea 1\n\nLínea 3\n\nLínea 5",
            (char *[]){"Línea 1\n", "\n", "Línea 3\n", "\n", "Línea 5"},
            5
        }
    };

    int num_tests = sizeof(tests) / sizeof(t_test_case);
    int total_errors = 0;

    printf(YELLOW "Iniciando pruebas avanzadas de get_next_line...\n" RESET);

    // Create test files
    for (int i = 0; i < num_tests; i++) {
        create_test_file(tests[i].name, tests[i].content);
    }


    for (int i = 0; i < num_tests; i++) {
        printf("Probando %s: ", tests[i].name);

        int errors = test_gnl(tests[i].name, tests[i].expected, tests[i].lines);
        total_errors += errors;

        if (errors == 0)
            printf(GREEN "OK\n" RESET);
        else
            printf(RED "Failed (%d errors)\n" RESET, errors);
    }

    // total_errors += test_multiple_fds(); // ELIMINADA o COMENTADA

    printf(BLUE "\nProbando casos extremos:\n" RESET);

    char *line = get_next_line(-1);
    if (line) {
        printf(RED "Error: FD inválido debería retornar NULL\n" RESET);
        free(line);
        total_errors++;
    } else {
        printf(GREEN "Invalid fd test passed\n" RESET);
    }

    int fd = open("empty.txt", O_RDONLY); // Usamos empty.txt, que ya existe
    close(fd);
    line = get_next_line(fd);
    if (line) {
        printf(RED "Error: FD cerrado debería retornar NULL\n" RESET);
        free(line);
        total_errors++;
    } else {
        printf(GREEN "Closed fd test passed\n" RESET);
    }
    // Clean up test files
    for (int i = 0; i < num_tests; i++) {
        remove(tests[i].name);
    }
    remove("test1.txt"); // Ya no se usan
    remove("test2.txt"); // Ya no se usan
    remove("test3.txt"); // Ya no se usan

    printf(YELLOW "\nResultados finales:\n" RESET);
    if (total_errors == 0) {
        printf(GREEN "¡Todas las pruebas pasaron! 🎉\n" RESET);
    } else {
        printf(RED "Fallaron %d pruebas\n" RESET, total_errors);
    }

    return total_errors;
}
