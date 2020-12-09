#include <iostream>
#include <string>
#include <dirent.h>
#include <fstream>
#include "include/Trie.h"

using namespace std;

char * foundFile(char raiz[], DIR * directorio, struct dirent * localizador, const char * palabra){
    char backup[500];
    strcpy(backup, raiz);
    directorio = opendir(raiz);
    if(directorio){
        while ((localizador = readdir(directorio)) != NULL){
            const char * childe = localizador->d_name;
            strcat(raiz, "/");
            strcat(raiz, childe);
            if (strcmp(childe, palabra) == 0){
                closedir(directorio);
                return raiz;
            }
            if (strcmp(childe, ".") != 0 && strcmp(childe, "..") != 0){
                char * path = foundFile(raiz, directorio, localizador, palabra);
                if (path!=nullptr){
                    closedir(directorio);
                    return path;
                }
            }
            memset(raiz, 0, 80);
            strcpy(raiz, backup);
        }
        closedir(directorio);
        return nullptr;
    }
    return nullptr;
}

int main() {
    setlocale(LC_ALL, "spanish");
    cout << "Bienvenido al buscador de archivos de Aldokler Ü" << endl;
    cout << "Buscando archivo..." << endl;
    DIR directorio;
    struct dirent localizador;
    char raiz[80];
    strcpy(raiz, "C:/Libros");
    const char * archivo = "Confesiones.txt";
    char * ruta = foundFile(raiz, &directorio, &localizador, archivo);
    if (ruta!=nullptr){
        cout << ruta << endl;
        cout << "Archivo encontrado!" << endl;
    }
    else
        cout << "Bro, no existe esa vaina..." << endl;
    /*
        Por diversas razones esa vara no acepta cins...

        igual sirve, pueden cambiar el main.png por el nombre del archivo que quieren buscar
    */
    ifstream * texto = new ifstream();
    texto->open(ruta, ifstream::in);
    int lineCounter = 0;
    char linea[10000];
    while (texto->good()){
        texto->getline(linea, 10000, '\n');
        lineCounter++;
        cout << lineCounter << ":   ";
        cout << linea << endl;
        /*
            Aquí vendría la llamada a la función que extrae las palabras y las va metiendo en el arbol
            lineCounter se deja así, nada más saca la última línea que leyó

            pa que sepan, lo voy a ir haciendo :)
        */
    }
    texto->close();
    return 0;
}
