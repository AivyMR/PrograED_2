#include <iostream>
#include <string>
#include <dirent.h>
#include <fstream>
#include "include/Trie.h"

using namespace std;

bool hasString(string signos, char caracter){
    for (unsigned int x = 0; x < signos.size(); x++){
        if (signos.at(x) == caracter)
            return true;
    }
    return false;
}

string firstWord(string linea){
    string word;
    string signos (".,: '()?¡¿!;0123456789  ");
    string comillas (1, '"');
    for (unsigned int x = 0; x < linea.size(); x++){
        if (hasString(signos, linea.front())){
            linea.erase(0,1);
            return word;
        }
        else if (hasString(comillas, linea.front())){
            linea.erase(0,1);
            return word;
        }
        word.append(linea, 0, 1);
        linea.erase(0,1);
    }
    return word;
}

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
    char raiz[80];
    char file[50];
    cout << "Bienvenido al buscador de archivos de Aldokler Ü" << endl;
    cout << "Ingrese el directorio en donde desea realizar la búsqueda: ";
    cin >> raiz;
    cout << "Inrgese el nombre del archivo que desea buscar (incluya la extensión del archivo): ";
    cin >> file;
    DIR directorio;
    struct dirent localizador;
    const char * archivo = file;
    cout << "Buscando archivo..." << endl;
    char * ruta = foundFile(raiz, &directorio, &localizador, archivo);
    if (ruta == nullptr){
        cout << "Archivo no encontrado" << endl;
        return 1;
    }
    cout << "Archivo encontrado!" << endl;
    ifstream * texto = new ifstream();
    texto->open(ruta, ifstream::in);
    int lineCounter = 0;
    char linea[10000];
    string word;
    Trie * arbol = new Trie();
    cout << "Extrayendo palabras..." << endl;
    while (texto->good()){
        texto->getline(linea, 10000, '\n');
        lineCounter++;
        for (int x = 0; x < 10000; x++){
            if (linea[x] == *"\0")
                break;
            else
                word+= linea[x];
        }
        while (word.size() > 0){
            string palabra = firstWord(word);
            if (palabra.size() >= 1)
                word.erase(0, palabra.size());
            else
                word.erase(0, 1);
            arbol->insert(palabra, lineCounter);
        }
        word.clear();
    }
    texto->close();
    cout << "Palabras extraídas!" << endl;
    /*
        Menú aquí
    */
    delete arbol;
    return 0;
}
