#! /bin/bash

#NOTA: En los echo para indicar que hace por pantalla, en lugar de " comillas uso - guion ya que la " no tiene impacto, es decir, no se ve.

#a. Reemplace cada punto del archivo “breve_historia.txt” por punto y salto de línea generando un nuevo archivo.
echo Genero breve_historia_Oraciones.txt en donde los puntos del archivo breve_historia.txt son remplazados por punto y salto. Accion sin impacto en terminal.
sed -E 's/\.| \. /&\n/g' breve_historia.txt > breve_historia_Oraciones.txt 

#b. Borre todas las líneas en blanco.
echo Archivo breve_historia.txt sin líneas en blanco :
sed -r '/^\s*$/d' breve_historia.txt

#c. Cree un nuevo archivo: “breve_historia_2.txt” con el resultado de las operaciones a y b.
echo Genero un archivo breve_historia_2.txt en donde cada linea corresponda a una oracion de breve_historia.txt. Accion sin impacto en terminal.
sed -E 's/\.| \. /&\n/g' breve_historia.txt | sed -r '/^\s*$/d' > breve_historia_2.txt

#d. Del archivo “breve_historia.txt”, liste todas las oraciones que contengan la palabra “guerra” sin distinguir mayúsculas y minúsculas.
echo Oraciones que contienen la palabra -guerra- :
echo $(sed -E 's/\.| \. /&\n/g' breve_historia.txt | grep --color=always -i '.\bguerra\b.')

#e. Muestre las oraciones que empiecen con “A” y terminen con “s” o “s.” del archivo “breve_historia.txt”.
echo Oraciones que empiezan con -A- y terminan con -s.- :
echo $(sed -E 's/\.| \. /&\n/g' breve_historia.txt | grep --color=always -E '^A.*(s|s\.)$')

#f. Indique en cuántas oraciones aparece la palabra “peronismo”. 
echo Numero de oraciones que contienen la palabra -peronismo- :
sed -E 's/\.| \. /&\n/g' breve_historia.txt | grep -i -c '\bperonismo\b'

#g. Muestre la cantidad de oraciones que tienen la palabra “Sarmiento” y “Rosas”.
echo Oraciones que contienen la palabra -Sarmiento- y/o -Rosas- :
echo $(sed -E 's/\.| \. /&\n/g' breve_historia.txt | grep --color=always -E '\bRosas\b|\bSarmiento\b')

#h. Muestre las oraciones que tengan fechas referidas al siglo XIX.
echo Oraciones que contienen fechas referidas al siglo XIX :
echo $(sed -E 's/\.| \. /&\n/g' breve_historia.txt | grep --color=always -E '18[0-9][1-9]')

#i. Borre la primera palabra de cada línea. Utilice substitución con sed. La sintaxis para sustituir la primera palabra de cada línea por “nada” sería:$sed “s/^[[a-zA-Z]]*\b//g” nombre_archivo 
echo Archivo breve_historia.txt sin la primera palabra de cada linea :
sed 's/^[a-zA-Z]*\b//g' breve_historia.txt

#j. Enumere todos los archivos de una carpeta que contengan extensión “.txt”.(tip: pipe con el comando ls).
echo Lista de los archivos .txt que se encuentran en el directorio ordenados del mas antiguo al mas reciente :
#NOTA: Los ordene de una forma a mi preferencia, esto no lo pedia la consigna.
ls -ltr *.txt

