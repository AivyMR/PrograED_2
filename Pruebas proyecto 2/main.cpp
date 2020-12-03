#include <iostream>
#include "include/Trie.h"

using namespace std;

int main() {
    cout << "Diay maes, sinceramente no puedo hacer mucho sin el AVL, pero esto es lo que pienso que iría bien" << endl;
    /*
    El trie que trae todas las palabras, cada palabra tiene una lista
    con las lineas en las que aparece, esta lista se actualiza cada vez
    que se inserta una palabra, de esta forma si inserta una repetida lo
    que hace es agregar la linea en la que encontró la palabra dentro de
    la lista de lineas de dicha palabra...

    Lo único que faltaría es que cuando busque las palabras indique en la
    linea que está del documento, ya que se necesita ese dato para que se
    pueda realizar la inserción de una palabra...

    Si se elimina una palabra ese sistema se va a la mierda BTW...
    No hay necesidad de eliminar palabras BTW....
    */
    Trie * ListaDePalabras = new Trie();
    /*
    #####################---NOTAS---########################

    Se necesita leer el archivo y tener la posibilidad de leer cada linea
    por separado, es decir, abre el archivo y lee la línea x y solo esa.

    La clase Trie tiene una función llamada getLines, esta función recibe
    un string por parámetro (una palabra) y regresa la lista de lines en las
    que aparece, esta sería una ArrayList de enteros. Esta función puede
    servir mucho para las funciones del menú.

    Pienso que lo mejor sería que Keres investigue lo de leer archivos y lupus
    siga con la interfaz, ahí yo voy a estar toqueteando la clase trie y demás
    para ver que sea eficiente y por si falta algo en la parte de "controlador"
    por así decirlo... igual puede ayudar en cualquier otra cosa que ocupen, supongo.
    */
    return 0;
}
