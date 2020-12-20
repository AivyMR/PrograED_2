#include <dirent.h>
#include <fstream>
#include <limits>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "include/Trie.h"
#include "sortedarraylist.h"

using namespace std;

/*
bool fileExists(string fileName){
    fstream archivo(fileName);
    return archivo.is_open();
}

int main2(){
    setlocale(LC_ALL, "spanish");
    string fileName;
    cout<<"Bienvenido a la indizaci�n de texto con Tries :D"<<endl<<endl;
    cout<< "Por favor indique el archivo a procesar:"<< endl;
    cin >>fileName;
    if(fileExists(fileName)){// verifica si el file existe

        fstream file("scores.txt"); // abre el archivo txt y lo procesa, guardando cada linea en un indice del vector lines
        vector<string> lines;
        string line;
        file.open(fileName, ios::in);
        while(getline(file, line))
            lines.push_back(line);
        file.close();

        int choiceM=0;
        cout<< "Archivo procesado!!!"<< endl;
        cout<< "\tPresione 1 para hacer una consulta por prefijo."<< endl;
        cout<< "\tPresione 2 para hacer busqueda de palabra."<< endl;
        cout<< "\tPresione 3 para hacer por cantidad de letras."<< endl;
        cout<< "\tPresione 4 para ver las palabras mas utilizadas."<< endl;
        cout<< "\tPresione 5 para terminar el programa."<< endl;
        menu(choiceM);
        return 0;
    }
    else{
        cout<< "El archivo indicado no existe :("<< endl;
        return 0;
    }
}*/
/*
 *-------------------------------------------------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------------------------------------------------
 */


bool hasString(string signos, char caracter){
    for (unsigned int x = 0; x < signos.size(); x++){
        if (signos.at(x) == caracter)
            return true;
    }
    return false;
}

string firstWord(string linea){
    string word;
    string signos (".,: '()?!;0123456789");
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
        cout << "La palabra (" << word << ") aparece ";
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

void searchBySize(Trie * arbol, unsigned int tamano){
    cout << "Buscando palabras..." << endl;
    AVLTreeDictionary<string, int> * diccionario = arbol->searchByLen(tamano);
    List<string> * palabras = diccionario->getKeys();
    List<int> * veces = diccionario->getValues();
    cout << "Palabras encontradas!" << endl;
    veces->goToStart();
    for (palabras->goToStart(); !palabras->atEnd(); palabras->next()){
        cout << "La Palabra (" + palabras->getElement() + ") \t aparece";
        cout << veces->getElement();
        cout << "\t veces" << endl;
        veces->next();
    }
    delete diccionario;
    delete palabras;
    delete veces;
}

void showTop(Trie * arbol, int n, bool top){
    cout << "Ordenando y obteniendo palabras..." << endl;
    SortedArrayDictionary<int, string> * diccionario;
    if (top)
        diccionario = arbol->mostUsed(n);
    else
        diccionario = arbol->lessUsed(n);
    cout << "Palabras ordenadas!" << endl;
    List<string> * palabras = diccionario->getValues();
    List<int> * veces = diccionario->getKeys();
    cout << "Palabras obtenidas!" << endl;
    veces->goToStart();
    int x = 1;
    for (palabras->goToStart(); !palabras->atEnd(); palabras->next()){
        cout << "Palabra N° ";
        cout << x;
        cout << ": (" << palabras->getElement() << ")." << endl;
        cout << "Aparece ";
        cout << veces->getElement();
        cout << " en el texto." << endl;
        veces->next();
        x++;
    }
    delete diccionario;
    delete palabras;
    delete veces;
}

/*
 *-------------------------------------------------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------------------------------------------------
 */


int topMenu(Trie * arbol){
     int choiceTM=0;
    cout<<"-----------TOP MEN�-----------\t"<<endl<<endl;
    cout<< "\tPresione 1 para ver las palabras m�s utilizadas"<< endl;
    cout<< "\tPresione 2 para ver las palabras menos utilizadas"<< endl;
    cout<< "\tPresione 3 para regresar"<< endl;
    while (!(cin>>choiceTM) ||!(choiceTM==1||choiceTM==2||choiceTM==3) ){
            cout<<"Por favor ingrese una opci�n v�lida."<<endl<<endl;
            cout<<"-----------TOP MEN�-----------\t"<<endl<<endl;
            cout<< "\tPresione 1 para ver las palabras m�s utilizadas"<< endl;
            cout<< "\tPresione 2 para ver las palabras menos utilizadas"<< endl;
            cout<< "\tPresione 3 para regresar"<< endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }


    switch (choiceTM){
            case 1://palabras mas utilizadas
                break;

            case 2: //menos utilizadas
                break;

            case 3: //regresar
                return 0;
            default:
                break;
    }
    return 0;
}

int menu(int choiceM, Trie * arbol, ArrayList<string> * lineas){
    string prefijo;
    string palabra;
    unsigned int tamano;
    do{
        while (!(cin>>choiceM) ||!(choiceM==1||choiceM==2||choiceM==3||choiceM==4||choiceM==5) ){
            cout<< "Entrada inválida, por favor vuelva a intentarlo"<< endl<< endl;
            cout<<"-----------MENÚ-----------\t"<<endl<<endl;
            cout<< "\tPresione 1 para hacer una consulta por prefijo."<< endl;
            cout<< "\tPresione 2 para hacer búsqueda de palabra."<< endl;
            cout<< "\tPresione 3 para realizar un búsqueda por cantidad de letras."<< endl;
            cout<< "\tPresione 4 para ver las palabras mas utilizadas."<< endl;
            cout<< "\tPresione 5 para terminar el programa."<< endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        switch (choiceM){
            case 1: //consulta por prefijo
                cout << "Ingrese el prefijo que desea usar para realizar la consulta: ";
                cin >> prefijo;
                prefixConsult(arbol, prefijo);
                break;

            case 2: // busqueda de palabra
                cout << "Ingrese la palabra que desea buscar dentro del Trie: ";
                cin >> palabra;
                searchWord(arbol, palabra, lineas);
                break;

            case 3: //por cantidad de letras
                cout << "Ingrese la cantidad de letras para la búsqueda: ";
                cin >> tamano;
                searchBySize(arbol, tamano);
                break;

            case 4: // ver top
                topMenu(arbol);
                break;

            case 5: //salir del programa
                return 0;
                break;

            default:
                break;
        }
            cout<<"-----------MENÚ-----------\t"<<endl<<endl;
            cout<< "\tPresione 1 para hacer una consulta por prefijo."<< endl;
            cout<< "\tPresione 2 para hacer busqueda de palabra."<< endl;
            cout<< "\tPresione 3 para hacer por cantidad de letras."<< endl;
            cout<< "\tPresione 4 para ver las palabras mas utilizadas."<< endl;
            cout<< "\tPresione 5 para terminar el programa."<< endl;
        }while (true);
    return 0;
}

/*
 *-------------------------------------------------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------------------------------------------------
 */

int main() {
    setlocale(LC_ALL, "spanish");
    char raiz[80];
    char file[50];
    cout << "Bienvenido al programa que procesa textos :)" << endl;
    cout << "Este programa se encarga de procesar un archivo tipo txt y extraer todas las palabras que contiene dicho archivo." << endl;
    cout << "Podrá realizar busquedas de palabras y ver cuales son las palabras más utilizadas y las menos utilizadas." << endl;
    cout << "Para iniciar porfavor proporcione los datos solicitados:" << endl;
    cout << "---Ingrese el directorio en donde desea realizar la búsqueda: ";
    cin >> raiz;
    cout << "---Inrgese el nombre del archivo que desea buscar (incluya la extensión del archivo): ";
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
    string lineText;
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
                lineText+= linea[x];
        }
        lineas->append(lineText);
        while (lineText.size() > 0){
            string palabra = firstWord(lineText);
            if (palabra.size() >= 1)
                lineText.erase(0, palabra.size());
            else
                lineText.erase(0, 1);
            arbol->insert(palabra, lineCounter);
        }
        lineText.clear();
    }
    texto->close();

    //-------------------------------------------------------------------------------------
    //---------------------------------------menu------------------------------------------
    //-------------------------------------------------------------------------------------


    int choiceM = 0;
    cout<< "Archivo procesado!!!"<< endl;
    cout<< "\tPresione 1 para hacer una consulta por prefijo."<< endl;
    cout<< "\tPresione 2 para hacer busqueda de palabra."<< endl;
    cout<< "\tPresione 3 para hacer por cantidad de letras."<< endl;
    cout<< "\tPresione 4 para ver las palabras mas utilizadas."<< endl;
    cout<< "\tPresione 5 para terminar el programa."<< endl;
    menu(choiceM, arbol, lineas);

    delete lineas;
    delete arbol;
    return 0;
}
