#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
// Hecha por Aivy
//Detalles por Samuel
//menú con validaciones y con menús internos para que se
//escojan como se quiere buscar las palabras y para indicar  el nombre del archivo de texto

int topMenu(){
     int choiceTM=0;
    cout<<"-----------TOP MENÚ-----------\t"<<endl<<endl;
    cout<< "\tPresione 1 para ver las palabras más utilizadas"<< endl;
    cout<< "\tPresione 2 para ver las palabras menos utilizadas"<< endl;
    cout<< "\tPresione 3 para regresar"<< endl;
    while (!(cin>>choiceTM) ||!(choiceTM==1||choiceTM==2||choiceTM==3) ){
            cout<<"Por favor ingrese una opción válida."<<endl<<endl;
            cout<<"-----------TOP MENÚ-----------\t"<<endl<<endl;
            cout<< "\tPresione 1 para ver las palabras más utilizadas"<< endl;
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

int menu(int choiceM){
    do{
        while (!(cin>>choiceM) ||!(choiceM==1||choiceM==2||choiceM==3||choiceM==4||choiceM==5) ){
            cout<< "Entrada inválida, por favor vuelva a intentarlo"<< endl<< endl;
            cout<<"-----------MENÚ-----------\t"<<endl<<endl;
            cout<< "\tPresione 1 para hacer una consulta por prefijo."<< endl;
            cout<< "\tPresione 2 para hacer busqueda de palabra."<< endl;
            cout<< "\tPresione 3 para hacer por cantidad de letras."<< endl;
            cout<< "\tPresione 4 para ver las palabras mas utilizadas."<< endl;
            cout<< "\tPresione 5 para terminar el programa."<< endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        switch (choiceM){
            case 1: //consulta por prefijo
                break;

            case 2: // busqueda de palabra
                break;

            case 3: //por cantidad de letras
                break;

            case 4: // ver top
                break;

            case 5: //salir del programa
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

bool fileExists(string fileName){
    fstream archivo(fileName);
    return archivo.is_open();
}

int main(){
    setlocale(LC_ALL, "spanish");
    string fileName;
    cout<<"Bienvenido a la indización de texto con Tries :D"<<endl<<endl;
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
}
