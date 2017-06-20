#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <cctype>

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
    
    void listarPuntos()
    {
        int cantidad=ListPoints.size();
        if(cantidad>=100) cantidad=100;
        
        for(int i=0;i<cantidad;i++)
        {
            cout << ListPoints[i].nombre << " , " << ListPoints[i].posicionX <<" , " <<ListPoints[i].posicionY<<" , "<<ListPoints[i].estadoP<<endl;
        }
    }

    void maximaDistancia()
    {
        if(ListPoints.size() == 0||ListPoints.size() == 1) cout<<"No hay suficientes elementos para determinar una distancia";
        double maxi = sqrt(pow(ListPoints[0].posicionX-ListPoints[1].posicionX,2)+pow(ListPoints[0].posicionY-ListPoints[1].posicionY,2));
        int inicial=0;
        int final=1;
        for(int i=0;i<ListPoints.size()-1;i++){
            for(int j=i+1;j<ListPoints.size();j++){
                double distancia =sqrt(pow(ListPoints[i].posicionX-ListPoints[j].posicionX,2)+pow(ListPoints[i].posicionY-ListPoints[j].posicionY,2));
                if(distancia>maxi){
                    maxi=distancia;
                    inicial=i;
                    final=j;
                }
            }
        }
        cout<<"La distancia maxima es de "<<maxi<<" metros entre "<<ListPoints[inicial].nombre<<" y "<<ListPoints[final].nombre<<endl;
    }
    
    void minimaDistancia()
    {
        if(ListPoints.size() == 0||ListPoints.size() == 1) cout<<"No hay suficientes elementos para determinar una distancia";
        double min = sqrt(pow(ListPoints[0].posicionX-ListPoints[1].posicionX,2)+pow(ListPoints[0].posicionY-ListPoints[1].posicionY,2));
        int inicial=0;
        int final=1;
        for(int i=0;i<ListPoints.size()-1;i++){
            for(int j=i+1;j<ListPoints.size();j++){
                double distancia =sqrt(pow(ListPoints[i].posicionX-ListPoints[j].posicionX,2)+pow(ListPoints[i].posicionY-ListPoints[j].posicionY,2));
                if(distancia<min){
                    min=distancia;
                    inicial=i;
                    final=j;
                }
            }
        }
        cout<<"La distancia minima es de "<<min<<" metros entre "<<ListPoints[inicial].nombre<<" y "<<ListPoints[final].nombre<<endl;
    }
    
    void menos10()
    {
        cout<<"Puntos ubicados a menos de 10 metros:"<<endl;
        if(ListPoints.size() == 0) cout<<"No hay elementos";
        int control=0;
        for(int i=0;i<ListPoints.size()-1;i++){
            for(int j=i+1;j<ListPoints.size();j++){
                double distancia =sqrt(pow(ListPoints[i].posicionX-ListPoints[j].posicionX,2)+pow(ListPoints[i].posicionY-ListPoints[j].posicionY,2));
                if(distancia<10){
                    cout<<ListPoints[i].nombre<<" , "<<ListPoints[j].nombre<<endl;
                    control++;
                }
            }
        }
        if(control==0) cout<<"No hay puntos a menos de 10 metros";
    }
    
    double distanciaPromedio()
    {
        if(ListPoints.size() == 0||ListPoints.size() == 1) return 0;
        double totalDistancia = 0;
        for(int i=0;i<ListPoints.size()-1;i++){
            for(int j=i+1;j<ListPoints.size();j++){
                double distancia =sqrt(pow(ListPoints[i].posicionX-ListPoints[j].posicionX,2)+pow(ListPoints[i].posicionY-ListPoints[j].posicionY,2));
                totalDistancia+=distancia;
                
                
            }
        }
        return totalDistancia/ListPoints.size();
    }
    
    void puntosCercanos(string opcion, double radio)
    {
        int control=-1;
        int elegido;
        for (int i = ListPoints.size() - 1; i >= 0; i--)
        {
            if (ListPoints[i].nombre == opcion){
                control=i;
            }
        }
        if(control==-1) cout<<"No existe "<<opcion<<" elija otro punto o agreguelo";
        else{
        cout<<"Puntos cerca a "<<opcion<<" a "<<radio<<" metros:"<<endl;
            for(int j=0;j<ListPoints.size();j++){
                double distancia =sqrt(pow(ListPoints[control].posicionX-ListPoints[j].posicionX,2)+pow(ListPoints[control].posicionY-ListPoints[j].posicionY,2));
                if(distancia<radio){
                    if(ListPoints[j].nombre==opcion){
                    }
                    else{
                        cout<<"      ."<<ListPoints[j].nombre<<endl;
                    }
                }
            }
        }
    }
    
    void agregarPunto(string nom,double x, double y,string estado)
    {
        char minuscula;
        int control=0;
        string estado2="";
        string nom2="";
        while(estado[control]){
           minuscula =tolower(estado[control]);
           estado2+=minuscula;
           control++;
        }
        control=0;
        while(nom[control]){
           minuscula =tolower(nom[control]);
           nom2+=minuscula;
           control++;
        }
        ListPoints.push_back({nom2,x,y,estado2});
        grabarArchivo("datos.txt");
    }
    
    void busquedaPorEstado(){
        vector<PuntoEst> temporal;
        vector<string> estadosBuscados;
        for(auto elemento: ListPoints)
        {
            temporal.push_back(elemento);
        }
        while(temporal.size()!=0){
            string borrar=temporal[0].estadoP;
            estadosBuscados.push_back(borrar);
            for (int i = ListPoints.size() - 1; i >= 0; i--)
            {
                if (temporal[i].estadoP == borrar)
                    temporal.erase(temporal.begin() + i);
            }
        }
        for(int i=0;i<estadosBuscados.size();i++){
            cout<<"Puntos con el estado "<<estadosBuscados[i]<<" : "<<endl;
            for (int j = ListPoints.size() - 1; j >= 0; j--)
            {
                if (ListPoints[j].estadoP == estadosBuscados[i])
                    cout<<"        ."<<ListPoints[j].nombre<<endl;
            }
        }
    }
    
    void busquedaPorEstado(string estado){
            string prueba=estado[0]+estado;
            cout<<"Puntos con el estado "<<estado<<" : "<<endl;
            for (int j = ListPoints.size() - 1; j >= 0; j--)
            {
                if (ListPoints[j].estadoP == estado)
                    cout<<"        ."<<ListPoints[j].nombre<<endl;
            }
        
        
    }
    
    void eliminarPorNombre(string x)
    {
        for (int i = ListPoints.size() - 1; i >= 0; i--)
        {
            if (ListPoints[i].nombre == x)
                ListPoints.erase(ListPoints.begin() + i);
        }
        grabarArchivo("datos.txt");
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
        
        cout << "1. Agregar una nueva posicion." << endl;
        cout << "2. Eliminar una posición por nombre." << endl;
        cout << "3. Listar 100 primeros puntos." << endl;
        cout << "4. Listar los puntos ubicados a menos de 10 metros." << endl;
        cout << "5. Calcular la distancia promedio entre cada punto." << endl;
        cout << "6. Determinar la distancia entre los puntos más lejanos." << endl;
        cout << "7. Determinar la distancia más corta entre los puntos." << endl;
        cout << "8. Buscar puntos cercanos a un punto especifico" << endl;
        cout << "9. Listar puntos por estado" << endl;
        cout << "0. Para salir" << endl << endl;
        cout << "Opcion : ";
        cin >> opcion;
    }
    while (opcion < 0 || opcion > 9);
    
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
            case 1:     // Insertar Puntos
                cout << string(50, '\n');
                cin.ignore();
                cout<< "Todas las letras seran pasadas a minusculas"<<endl;
                cout << "Ingrese el nombre: "; 
                getline (cin,nomb);
                cout << "Ingrese el valor de X: "; 
                cin >> x;
                cout << "Ingrese el valor de Y: "; 
                cin >> y;
                cin.ignore();
                cout << "Ingrese el estado del punto: "; 
                getline (cin,est);
                puntos.agregarPunto(nomb,x, y,est);
                break;
            case 2:     // Eliminar Puntos
                cout << string(50, '\n');
                cout << "Ingrese el nombre del punto que desea eliminar :";
                cin.ignore();
                getline(cin,nomb);
                puntos.eliminarPorNombre(nomb);

                break;
            case 3:     // Listar 100 Puntos
                cout << string(50, '\n');
                cin.ignore();
                puntos.listarPuntos();
                cin.get();
                
                break;
            case 4:     // 10 metros
                cout << string(50, '\n');
                cin.ignore();
                puntos.menos10();
                cin.get();
                break;
            case 5:     // Distancia promedio
                cout << string(50, '\n');
                cin.ignore();
                cout<<"La distancia promedio es : "<<puntos.distanciaPromedio()<<" metros"<<endl;
                cin.get();
                break;
            case 6:     // mas lejanos
                cout << string(50, '\n');
                cin.ignore();
                puntos.maximaDistancia();
                cin.get();
                break;
            case 7:     // mas cercanos
                cout << string(50, '\n');
                cin.ignore();
                puntos.minimaDistancia();
                cin.get();
                break;
            case 8:     // Buscador por cercania
                
                cout << string(50, '\n');
                cout << "Ingrese nombre del punto :"<<endl;
                cin.ignore();
                getline (cin,nomb);
                cout << "Ingrese el radio :"<<endl;
                cin >>x;
                cin.ignore();
                puntos.puntosCercanos(nomb,x);
                cin.get();
                break;
            case 9:     // Enlistado de estados
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
