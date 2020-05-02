#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    std::string rut,nem,ranking,matematicas,lenguaje,ciencias,historia;
    int nemn,rankingn,matematicasn,lenguajen,cienciasn,historian;
    float promedio;
    
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

    while(!archivo.eof())
    {
        getline(archivo,rut,';');
        getline(archivo,nem,';');
        getline(archivo,ranking,';');
        getline(archivo,matematicas,';');
        getline(archivo,lenguaje,';');
        getline(archivo,ciencias,';');
        getline(archivo,historia,'\n');

        std::istringstream(nem) >> nemn;
        std::istringstream(ranking) >> rankingn;
        std::istringstream(matematicas) >> matematicasn;
        std::istringstream(lenguaje) >> lenguajen;
        std::istringstream(ciencias) >> cienciasn;
        std::istringstream(historia) >> historian;

        promedio=((nemn+rankingn+matematicasn+lenguajen+cienciasn+historian)/6);

        if(promedio==0)
        {
            archivo_salida<<rut<<";"<<"PROMEDIO"<<std::endl;
        }
        else
        {
            archivo_salida<<rut<<";"<<promedio<<std::endl;
        }

    }
    archivo.close();
    archivo_salida.close();
}
