# get_next_line

Este proyecto es una implementación de la función `get_next_line` de la escuela 42 Urduliz-Bizkaia. La función lee una línea de un descriptor de archivo, incluyendo el carácter de nueva línea (`\n`), si está presente.

## Descripción

La función `get_next_line` lee texto de un descriptor de archivo (file descriptor) hasta que encuentra un carácter de nueva línea (`\n`) o hasta que llega al final del archivo (EOF). Devuelve una cadena (asignada dinámicamente) que contiene la línea leída. En llamadas sucesivas a `get_next_line` con el mismo descriptor de archivo, la función continúa leyendo desde donde se quedó la vez anterior.

Este proyecto se enfoca en el manejo de archivos, la gestión de memoria dinámica y el uso de variables estáticas en C.

## Características

* **Lectura línea por línea:** Lee archivos de texto de manera eficiente.
* **Gestión de memoria segura:** Evita fugas de memoria (memory leaks).
* **Variable estática:** Mantiene el estado de la lectura entre llamadas a la función.
* **Tamaño de buffer configurable:** Se puede modificar en tiempo de compilación mediante la macro `BUFFER_SIZE`.
* **Cumple con la Norminette:** Sigue las reglas de estilo de la escuela 42.
* **Sin bonus:** No incluye la funcionalidad de manejar múltiples descriptores de archivo simultáneamente.

## Estructura del Proyecto

El proyecto consta de tres archivos principales:

* **`get_next_line.h`** - Archivo de cabecera:
  * Define la macro `BUFFER_SIZE`.
  * Contiene los prototipos de las funciones `get_next_line`, `read_and_store`, `extract_line`, `update_stash`.
  * Contiene los prototipos de funciones auxiliares (`find_newline`, `string_length`, `string_join`, `string_sub`).

* **`get_next_line.c`** - Implementa la función principal y sus auxiliares:
  * `get_next_line(int fd)`: Lee una línea del descriptor de archivo `fd`.
  * `read_and_store(int fd, char **stash)`: Lee datos y los almacena en `stash`.
  * `extract_line(char **stash)`: Extrae la primera línea completa de `stash`.
  * `update_stash(char **stash)`: Actualiza `stash` con los datos no leídos.

* **`get_next_line_utils.c`** - Contiene funciones auxiliares:
  * `find_newline(char *stash)`: Busca `\n` en una cadena.
  * `string_length(const char *s)`: Calcula la longitud de una cadena.
  * `string_join(char *s1, char *s2)`: Concatena dos cadenas.
  * `string_sub(char *str, unsigned int start, size_t len)`: Extrae una subcadena.

## Compilación

Para compilar el proyecto, usa:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o get_next_line
```

Explicación:
- `-Wall -Wextra -Werror`: Activa advertencias y las trata como errores.
- `-D BUFFER_SIZE=42`: Define el tamaño del buffer (puedes cambiarlo).
- `get_next_line.c get_next_line_utils.c`: Archivos a compilar.
- `-o get_next_line`: Nombre del ejecutable de salida.

## Uso

Ejemplo de uso en un programa:

```c
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main() {
    int fd = open("mi_archivo.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        return 1;
    }
    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("Línea leída: %s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

## Tests

Para probar el código, usa el siguiente comando:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o tester
./tester
```

El tester creará varios archivos de prueba, ejecutará `get_next_line` y mostrará los resultados.

## Autor

Jhon Jairo Valencia Gongora

## Licencia

Este proyecto está licenciado bajo la licencia MIT - ver el archivo [LICENSE](LICENSE) para más detalles.

