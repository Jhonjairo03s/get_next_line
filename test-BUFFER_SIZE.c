/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:49:12 by jhvalenc          #+#    #+#             */
/*   Updated: 2025/02/07 15:39:06 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>

/*
int main()
{
	char	*str;
	char	*newline_pos;
	char	*str1;
	char	*str2;
	char	*joined_str;
	char	*str3;
	char	*substr;

	str = "Hola\nMundo";
	newline_pos = find_newline(str);
	// Prueba de find_newline
	if (newline_pos != NULL)
	{
		printf("Salto de línea encontrado e la posición %ld\n", newline_pos - str);
	}
	else
	{
		printf("No se encontró salto de línea");
	}
	// Prueba de string_length
	printf("La longitud de la cadena es %zu\n", string_length(str));
	printf("La longitud de la cadena es %zu\n", string_length(NULL));

	// Prueba de string_join
	str1 = "Hola, ";
	str2 = "Mundo!";
	joined_str = string_join(str1, str2);
	if (joined_str != NULL)
	{
		printf("Cadena unida: %s\n", joined_str);
	}
	else
	{
		printf("Error al unir las cadenas\n");
	}

	// Prueba de string_sub
	str3 = "Hola, Mundo!";
	substr = string_sub(str3, 7, 5);
	if (substr != NULL)
	{
		printf("Subcadena: %s\n", string_sub);
		free(substr);
	}
	else
	{
		printf("Error al crear la subcadena\n");
	}

	return (0);
}

int main()
{
	char	*line;
	int	fd;

	fd = open("test/first_test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("error al abrir el archivo");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}

// --------------------------------------------------------------------------------

void	test_mandatory(const char *filename)
{
	char	*line;
	int	fd;

	printf("Probando archivo: %s\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("error al abrir el archivo");
		return;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	printf("\n");
}

int main()
{
	test_mandatory("test/first_test.txt");
	test_mandatory("test/test_empty.txt");
	test_mandatory("test/test_empty_lines.txt");
	test_mandatory("test/test_long_lines.txt");
	test_mandatory("test/test_no_newline.txt");
	test_mandatory("test/test_short_lines.txt");
	return (0);
}

// --------------------------------------------------------------------------------

void	test_error_management(void)
{
	char	*line;

	printf("Probando file descriptor inválido...\n");
	line = get_next_line(-1);
	if (line == NULL)
	{
		printf("OK\n");
	}
	else
	{
		printf("Error: la función no devolvio NULL\n");
	}
}

int main()
{
	test_error_management();
}

// --------------------------------------------------------------------------------

void	test_efficiency(const char *filename, int buffer_size)
{
	int	fd;
	char	*line;
	clock_t	start, end;
	double	cpu_time_used;

	printf("Probando eficiencia con BUFFER_SIZE=%d...\n", buffer_size);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error al abrir el archivo");
		return;
	}
	start = clock();
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\nTiempo de ejecución: %f segundos\n", cpu_time_used);
	close(fd);
}

int main()
{
	test_efficiency("test/test_long_lines.txt", 1);
	test_efficiency("test/test_long_lines.txt", 42);
	test_efficiency("test/test_long_lines.txt", 9999);
}

// ---------------------------------------------------------------------------------

int main()
{
    int	fd;
    char	*line;
    char	*next;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s\n", line);
        next = get_next_line(fd);
        free(line);
        line = next;
    }
    close(fd);
    return (0);
}

// ---------------------------------------------------------------------------------

int main()
{
    int fd = open("test.txt", O_RDONLY); // Abre el archivo para solo lectura

    if (fd == -1) {
        perror("Error al abrir el archivo");
        return (1);
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        // Procesa la línea
        printf("%s", line);
        free(line); // No olvides liberar la memoria de cada línea
    }

    close(fd); // Cierra el archivo después de usarlo

    return (0);
}
*/

#include "get_next_line.h"

void test_mandatory(const char *filename)
{
    char    *line;
    int     fd;

    printf("\nProbando archivo: %s\n", filename);
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: No se pudo abrir el archivo '%s'\n", filename);
        perror("Error");
        return;
    }

    printf("File descriptor: %d\n", fd);
    int line_count = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Línea %d: %s", ++line_count, line);
        free(line);
    }

    if (line_count == 0)
        printf("El archivo está vacío o no se pudo leer correctamente\n");

    close(fd);
}

int main()
{
    // Primero verificamos si el directorio existe
    DIR *dir = opendir("test");
    if (dir == NULL) {
        printf("Error: El directorio 'test' no existe\n");
        return 1;
    }
    closedir(dir);

    // Verificamos si podemos acceder a los archivos
    const char *files[] = {
        "test/first_test.txt",
        "test/test_empty.txt",
        "test/test_empty_lines.txt",
        "test/test_long_lines.txt",
        "test/test_no_newline.txt",
        "test/test_short_lines.txt"
    };

    for (int i = 0; i < 6; i++) {
        if (access(files[i], F_OK) == -1) {
            printf("El archivo %s no existe\n", files[i]);
            continue;
        }
        if (access(files[i], R_OK) == -1) {
            printf("No hay permisos de lectura para %s\n", files[i]);
            continue;
        }
        test_mandatory(files[i]);
    }

    return 0;
}
