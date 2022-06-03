# Funcionamiento

Un proyecto que utilice esta plantilla debe contener un archivo `makefile` en la carpeta principal del proyecto, en el cual se deben realizar, como mínimo, las definicion de las siguientes variables

`MODULES` = define una lista de directorios con el codigo fuente de modulos que seran compilados como librerias estáticas (archivos `.a`) antes de compilar el proyecto principal

`BOARD` = define el nombre de la placa para la cual se debe compilar el proyecto.

`PROJECT` = define el directorio principal del proyecto que se desea compilar.

# Compilación de los modulos como librerias estáticas

Para cada directorio definido en la variable `MODULES` se definen las siguientes variables

`CARPETA_MODULO_INC` = define la lista de directorios donde deben buscarse los archivos de cabecera `.h`

`CARPETA_MODULO_SRC` = define la lista de directorios donde deben buscarse los archivos fuentes `.c` y `.s` del modulo.

`CARPETA_MODULO_OBJ` = define la lista de archivos objeto `.o` que deben enlazarse para completar el modulo.
