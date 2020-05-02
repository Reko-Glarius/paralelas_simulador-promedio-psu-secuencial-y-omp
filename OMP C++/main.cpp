#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <omp.h>

using namespace std;

int main(int argc, char *argv[])
{
    std::string rut,nem,ranking,matematicas,lenguaje,ciencias,historia,linea; 
    int nemn,rankingn,matematicasn,lenguajen,cienciasn,historian;
    int promedio, total_ruts=;
    
    if(argc==1)
    {
        cout<<"Error. Direccion del archivo no enviada\n\nCerrando APP por motivos de seguridad"<<endl;
        exit(1);

    }
    
    ifstream archivo(argv[1]);
    if(!archivo.good())
    {
        cout<<"Archivo ingresado de manera erronea, recuerde que debe enviarse con doble '\' para reconocer la direccion"<<endl;
        exit(1);
    }
    std::ofstream archivo_salida("promedios.csv");
#pragma omp parallel
    {
        #pragma omp for private(rut,nem,ranking,matematicas,lenguaje,ciencias,historia,linea,nemn,rankingn,matematicasn,lenguajen,cienciasn,historian,promedio,i)
            for(i=0;i<5015750;i++)
            {
                stringstream line(linea);
                getline(line,rut,';');
                getline(line,nem,';');
                getline(line,ranking,';');
                getline(line,matematicas,';');
                getline(line,lenguaje,';');
                getline(line,ciencias,';');
                getline(line,historia,'\n');

                std::istringstream(nem) >> nemn;
                std::istringstream(ranking) >> rankingn;
                std::istringstream(matematicas) >> matematicasn;
                std::istringstream(lenguaje) >> lenguajen;
                std::istringstream(ciencias) >> cienciasn;
                std::istringstream(historia) >> historian;

                promedio=((nemn+rankingn+matematicasn+lenguajen+cienciasn+historian)/6);
        #pragma omp critical
                if(promedio==0)
                {
                    archivo_salida<<rut<<";"<<"PROMEDIO"<<std::endl;
                }
                else
                {
                    archivo_salida<<rut<<";"<<promedio<<std::endl;
                    promedio=0;
                }
            }
        }
    archivo.close();
    archivo_salida.close();
}
