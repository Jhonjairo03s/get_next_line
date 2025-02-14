/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_claude.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:15:00 by jhvalenc          #+#    #+#             */
/*   Updated: 2025/02/06 16:15:44 by jhvalenc         ###   ########.fr       */
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
#define RESET "\x1b[0m"

typedef struct s_test {
    char *name;
    char *content;
    char **expected;
    int num_lines;
} t_test;

void create_test_file(char *filename, char *content) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf(RED "Error creating test file %s\n" RESET, filename);
        exit(1);
    }
    fputs(content, fp);
    fclose(fp);
}

int test_gnl(char *filename, char **expected, int num_lines, int buffer_size) {
    (void)buffer_size;
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        printf(RED "Error opening file %s\n" RESET, filename);
        return 1;
    }

    char *line;
    int i = 0;
    int errors = 0;

    while (i < num_lines) {
        line = get_next_line(fd);
        if (!line && expected[i]) {
            printf(RED "Line %d: Expected '%s', got NULL\n" RESET, i + 1, expected[i]);
            errors++;
        } else if (line && !expected[i]) {
            printf(RED "Line %d: Expected NULL, got '%s'\n" RESET, i + 1, line);
            errors++;
        } else if (line && strcmp(line, expected[i]) != 0) {
            printf(RED "Line %d: Expected '%s', got '%s'\n" RESET, i + 1, expected[i], line);
            errors++;
        }
        free(line);
        i++;
    }

    // Test EOF
    line = get_next_line(fd);
    if (line) {
        printf(RED "Expected EOF, got '%s'\n" RESET, line);
        free(line);
        errors++;
    }

    close(fd);
    return errors;
}

int main(void) {
    // Define test cases
    t_test tests[] = {
        {
            "empty.txt",
            "",
            (char *[]){NULL},
            0
        },
        {
            "single_char.txt",
            "a",
            (char *[]){"a"},
            1
        },
        {
            "single_line.txt",
            "Hello World!\n",
            (char *[]){"Hello World!\n"},
            1
        },
        {
            "multiple_nl.txt",
            "\n\n\n\n",
            (char *[]){"\n", "\n", "\n", "\n"},
            4
        },
        {
            "no_nl.txt",
            "This is a line without newline",
            (char *[]){"This is a line without newline"},
            1
        },
        {
            "mixed.txt",
            "Line1\nLine2\n\nLine4\nLine5",
            (char *[]){"Line1\n", "Line2\n", "\n", "Line4\n", "Line5"},
            5
        },
        {
            "long_lines.txt",
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"
            "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n",
            (char *[]){
                "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n",
                "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n"
            },
            2
        }
    };

    int num_tests = sizeof(tests) / sizeof(t_test);
    int buffer_sizes[] = {1, 2, 3, 4, 5, 10, 32, 42, 64, 128, 512, 1024, BUFFER_SIZE};
    int num_sizes = sizeof(buffer_sizes) / sizeof(int);
    int total_errors = 0;

    printf(YELLOW "Starting get_next_line tests...\n" RESET);

    // Create test files
    for (int i = 0; i < num_tests; i++) {
        create_test_file(tests[i].name, tests[i].content);
    }

    // Run tests with different buffer sizes
    for (int i = 0; i < num_sizes; i++) {
        printf(YELLOW "\nTesting with BUFFER_SIZE = %d\n" RESET, buffer_sizes[i]);
        
        for (int j = 0; j < num_tests; j++) {
            printf("Testing %s: ", tests[j].name);
            int errors = test_gnl(tests[j].name, tests[j].expected, tests[j].num_lines, buffer_sizes[i]);
            total_errors += errors;
            if (errors == 0)
                printf(GREEN "OK\n" RESET);
        }
    }

    // Additional edge cases
    printf(YELLOW "\nTesting edge cases:\n" RESET);
    
    // Invalid fd
    char *line = get_next_line(-1);
    if (line) {
        printf(RED "Invalid fd test failed\n" RESET);
        free(line);
        total_errors++;
    } else {
        printf(GREEN "Invalid fd test passed\n" RESET);
    }

    // Closed fd
    int fd = open("empty.txt", O_RDONLY);
    close(fd);
    line = get_next_line(fd);
    if (line) {
        printf(RED "Closed fd test failed\n" RESET);
        free(line);
        total_errors++;
    } else {
        printf(GREEN "Closed fd test passed\n" RESET);
    }

    // Clean up test files
    for (int i = 0; i < num_tests; i++) {
        remove(tests[i].name);
    }

    // Final results
    printf(YELLOW "\nFinal Results:\n" RESET);
    if (total_errors == 0) {
        printf(GREEN "All tests passed! 🎉\n" RESET);
    } else {
        printf(RED "Failed with %d errors\n" RESET, total_errors);
    }

    return total_errors;
}
