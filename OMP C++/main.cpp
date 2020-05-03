#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <omp.h>

using namespace std;

int main(int argc, char *argv[])
{

    std::string rut,nem,ranking,matematicas,lenguaje,ciencias,historia,linea; ///Variable tipo string; son utilizadas para guardar datos, y linea para poder operar cada linea, una a la vez
    int nemn,rankingn,matematicasn,lenguajen,cienciasn,historian; ///Variables tipo int; son para almacenar los datos unas vez pasados a entero
    int promedio,i,total=5015750; //Variable tipo int; son para almacenar resultado del promedio, para for y el total de ruts para el for
    
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
#pragma omp parallel ///Inicio del metodo OMP para paralelismo
    {
        #pragma omp for  private(rut,nem,ranking,matematicas,lenguaje,ciencias,historia,linea,nemn,rankingn,matematicasn,lenguajen,cienciasn,historian,promedio,i)
        ///activacion del for para paralelismo; se utiliza el metodo private para reducir la posibilidad de corte entre datos y casos similares
            for(i=0;i<5015750;i++) ///Ciclo for para el paralelismo; en funcion de la cantidad de ruts a analizar, es la cantidad usada en el for para la paralelisacion
            {
                ///Funciones para poder obtener cada fragmento de cada linea del archivo; en cada uno se guarda su respectivo dato en una variable string
            	getline(archivo,linea);
                stringstream line(linea);
                getline(line,rut,';');
                getline(line,nem,';');
                getline(line,ranking,';');
                getline(line,matematicas,';');
                getline(line,lenguaje,';');
                getline(line,ciencias,';');
                getline(line,historia,'\n');

                ///Funciones para poder obtener el valor como entero de un string
                std::istringstream(nem) >> nemn;
                std::istringstream(ranking) >> rankingn;
                std::istringstream(matematicas) >> matematicasn;
                std::istringstream(lenguaje) >> lenguajen;
                std::istringstream(ciencias) >> cienciasn;
                std::istringstream(historia) >> historian;

                promedio=((nemn+rankingn+matematicasn+lenguajen+cienciasn+historian)/6); ///Se calcula y almacena el valor promedio de los puntajes
        #pragma omp critical ///Punto critico del paralelismo; sirve para ejecutar la accion corespondiente una vez las acciones paralelas se han completado
                if(promedio==0) //En caso de que el promedio sea 0, mostrara el rut y la expresion "PROMEDIO" (pensado para casos en los que exista un banner con los nombres de los datos)
                {
                    archivo_salida<<rut<<";"<<"PROMEDIO"<<std::endl;
                }
                else ///En caso contrario, directamente guardara el rut y el promedio
                {
                    archivo_salida<<rut<<";"<<promedio<<std::endl;
                    promedio=0;
                }
            }
        }
    archivo.close(); ///Se cierra el documento desde el cual se saca la informacion
    archivo_salida.close(); ///Se cierra el documento donde se estan guardando los datos; con esto oficialmente se guardan los datos
}
