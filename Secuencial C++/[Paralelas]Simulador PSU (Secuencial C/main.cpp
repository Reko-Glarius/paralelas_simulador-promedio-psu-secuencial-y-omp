#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    std::string rut,nem,ranking,matematicas,lenguaje,ciencias,historia; ///Variable tipo string; son utilizadas para guardar datos
    int nemn,rankingn,matematicasn,lenguajen,cienciasn,historian; ///Variables tipo int; son para almacenar los datos unas vez pasados a entero
    float promedio; //Variable tipo float; es para almacenar el resultado del calculo del promedio
    
    if(argc==1) //If que verifica que se envio almenos un argumento; en caso de que no se enviase ningun, cierra el programa
    {
        cout<<"Error. Direccion del archivo no enviada\n\nCerrando APP por motivos de seguridad"<<endl;
        exit(1); ///Funcion interna de C/C++; permite cerrar el programa si recibe un entero 1
    }
    
    ifstream archivo(argv[1]); ///Funcion para abrir el archivo de texto, en funcion de la direccion enviada por argumento
    if(!archivo.good()) ///Funcion de los archivos; permite reconocer si el archivo se abri de manera exitosa; el if es para que, en caso de no abrirse correctamente, se cierre el programa
    {
        cout<<"Archivo ingresado de manera erronea, recuerde que debe enviarse con doble '\' para reconocer la direccion"<<endl;
        exit(1);
    }
    std::ofstream archivo_salida("promedios.csv"); ///Funcion para abrir/crear un archivo; en este caso se creara un archivo llamado "promedio.csv"

    while(!archivo.eof()) ///Ciclo while con funcion propia de los archivos; la funcion detecta si termino el archivo o no; el while permite sacar linea por linea hasta llegar al final del documento
    {
        ///Funciones para poder obtener cada fragmento de cada linea del archivo; en cada uno se guarda su respectivo dato en una variable string
        getline(archivo,rut,';');
        getline(archivo,nem,';');
        getline(archivo,ranking,';');
        getline(archivo,matematicas,';');
        getline(archivo,lenguaje,';');
        getline(archivo,ciencias,';');
        getline(archivo,historia,'\n');

        ///Funciones para poder obtener el valor como entero de un string
        std::istringstream(nem) >> nemn;
        std::istringstream(ranking) >> rankingn;
        std::istringstream(matematicas) >> matematicasn;
        std::istringstream(lenguaje) >> lenguajen;
        std::istringstream(ciencias) >> cienciasn;
        std::istringstream(historia) >> historian;

        promedio=((nemn+rankingn+matematicasn+lenguajen+cienciasn+historian)/6); ///Se calcula y almacena el valor promedio de los puntajes

        //En caso de que el promedio sea 0, mostrara el rut y la expresion "PROMEDIO" (pensado para casos en los que exista un banner con los nombres de los datos)
        if(promedio==0)
        {
            archivo_salida<<rut<<";"<<"PROMEDIO"<<std::endl;
        }
        else ///En caso contrario, directamente guardara el rut y el promedio
        {
            archivo_salida<<rut<<";"<<promedio<<std::endl;
        }

    }
    archivo.close(); ///Se cierra el documento desde el cual se saca la informacion
    archivo_salida.close(); ///Se cierra el documento donde se estan guardando los datos; con esto oficialmente se guardan los datos
}
