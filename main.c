#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*
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
*/

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
	if (line == NULL)
	{
		printtf("OK\N");
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
	printf("Tiempo de ejecución: %f segundos", cpu_time_used);
	close(fd);
}

int main()
{
	test_efficiency("test/test_long_lines.txt", 1);
	test_efficiency("test/test_long_lines.txt", 42);
	test_efficiency("test/test_long_lines.txt", 9999);
}
