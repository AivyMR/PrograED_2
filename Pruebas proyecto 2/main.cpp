#include <iostream>
#include <string>
#include <dirent.h>
#include <fstream>
#include <limits>
#include "include/Trie.h"
#include "sortedarraylist.h"

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

/*
 *-------------------------------------------------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------------------------------------------------
 */

void prefixConsult(Trie * arbol, string prefijo){
    cout << "Buscando Palabras..." << endl;
    List<string> * palabras = arbol->getMatches(prefijo);
    cout << "Se encontraron " << palabras->getSize() << " palabras que coinciden!" << endl;
    cout << "Palabras encontradas:" << endl << endl;
    for (palabras->goToStart(); !palabras->atEnd(); palabras->next()){
        string word = palabras->getElement();
        ArrayList<int> * lineas = arbol->getLines(word);
        cout << "La palabra (" << word << "): aparece ";
        cout << lineas->getSize() << " veces." << endl;
    }
    cout << endl;
}

void searchWord(Trie * arbol, string palabra, ArrayList<string> * lineas){
    cout << "Buscando palabra..." << endl;
    if (!arbol->containsWord(palabra)){
        cout << "Palabra no encontrada." << endl;
        return;
    }
    cout << "Palabra encontrada!" << endl;
    cout << "Lineas en las que aparece la palabra (" << palabra << "):" << endl;
    ArrayList<int> * repeatLines = arbol->getLines(palabra);
    for (repeatLines->goToStart(); !repeatLines->atEnd(); repeatLines->next()){
        int line = repeatLines->getElement();
        lineas->goToPos(line-1);
        cout << line << ": " << lineas->getElement() << endl;
    }
    cout << endl;
}

/*
 *-------------------------------------------------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------------------------------------------------
 */

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
    ArrayList<string> * lineas = new ArrayList<string>(60000);
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
        lineas->append(word);
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
    cout << "Palabras extraídas!" << endl << endl;

    //-------------------------------------------------------------------------------------
    //---------------------------------------menu------------------------------------------
    //-------------------------------------------------------------------------------------

    delete lineas;
    delete arbol;
    return 0;
}
