#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <map>
using namespace std;

struct PuntoEst
{
    string nombre;
    double posicionX;
    double posicionY;
    string estadoP;
};

class PuntoF
{
    vector<PuntoEst> ListPoints;
    map<string,string> mapaEstados;

    public:
        PuntoF()
            {
            }
            
    void leerArchivo(string nombre)
        {
     
        ifstream archivo(nombre);
        
        vector<string> datos;
        string texto;
        
        while (getline(archivo,texto))
            {
                datos.push_back(texto);
            }
        
        ListPoints.clear();
        for (int i = 1; i < datos.size(); i++)
            {
            auto columnas = split(datos[i], ',');
            PuntoEst punto = {columnas[0], atof(columnas[1].c_str()), atof(columnas[2].c_str()),columnas[3]};
            ListPoints.push_back(punto);
            mapaEstados.insert(pair<string, string>(columnas[0],columnas[3]));
            }
        
        archivo.close();
        }
        
    vector <string> split(string texto, char separador)
    {
        vector<string> datos;
        string valor;
        for (auto i : texto)
            {
            if (i != separador)
                {
                valor = valor + i;
                }
            else
                {
                datos.push_back(valor);
                valor.clear();
                }
            }
        datos.push_back(valor);
        return datos;
    }

    void busquedaPorEstado(){
        map<string,string> temporal;
        for (map<string,string>::iterator it=mapaEstados.begin(); it!=mapaEstados.end(); ++it)
        {
            temporal.insert(pair<string, string>(it->second,it->first));
        }
        cout<<temporal.size();
        for (auto it: temporal)
        {
            cout << "Puntos con el estado "<<it.first <<"son :"<< endl;
            for (map<string,string>::iterator qit=mapaEstados.begin(); qit!=mapaEstados.end(); ++qit)
            {
                if(qit->second==it.first)
                cout << "    ." <<qit->first << endl;   
            
            }
        }
    }
    void busquedaPorEstado(string estado){
        cout<<"Puntos con el estado "<<estado<<"son :"<<endl;
        for (map<string,string>::iterator it=mapaEstados.begin(); it!=mapaEstados.end(); ++it)
        {
            if(it->second==estado)
            cout << "    ." <<it->first << endl;   
            
        }
        
    }

    void grabarArchivo(string nombre)
    {
        
        ofstream archivo(nombre);
        archivo << "nombre,posicion X,posicion Y,estado" << endl;
        for (auto elemento: ListPoints)
            archivo << elemento.nombre << "," << elemento.posicionX << "," << elemento.posicionY << "," << elemento.estadoP << endl;
        archivo.close();
    }

};
int menu()
{
    int opcion = 0;
    do
    {
        system ("clear");
        cout << "MENU" << endl;
        cout << string(4, '~') << endl << endl;
        cout << "1. Listar puntos por estado" << endl;
        cout << "0. Para salir" << endl << endl;
        cout << "Opcion : ";
        cin >> opcion;
    }
    while (opcion < 0 || opcion > 1);
    
    return opcion;
}
int main()
{
    PuntoF puntos;
    puntos.leerArchivo("datos.txt");
    int opcion = 0;
    do
    {
        opcion = menu(); 
        double x, y;
        int opcion2;
        string nomb;
        string est;
        switch(opcion)
        {
            case 1:     // Enlistado de estados
                cout << string(50, '\n');
                cout<<"1. Listar puntos por cada estado"<<endl;
                cout<<"2. Listar puntos por un estado especifico"<<endl;
                cin>>opcion2;
                switch(opcion2){
                    case 1:
                    cin.ignore();
                        puntos.busquedaPorEstado();
                        cin.get();
                        break;
                    case 2:
                    
                        cout<<"Ingrese el estado "<<endl;
                        cin.ignore();
                        getline(cin,est);
                        puntos.busquedaPorEstado(est);
                        cin.get();
                }
        }
        
    }
    while (opcion != 0);

    return 0;
}
