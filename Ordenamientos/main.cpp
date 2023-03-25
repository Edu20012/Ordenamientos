#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Definición de la estructura para representar la solicitud de ingreso
struct Solicitud {
    string nombre;
    string carrera;
    string preparatoria;
    double promedio;
};

// Definición de la clase lista que permite la inserción de una solicitud al final de la lista
class Lista {
private:
    vector<Solicitud> solicitudes;

public:
    void agregarSolicitud(Solicitud solicitud) {
        solicitudes.push_back(solicitud);
    }

    vector<Solicitud> obtenerSolicitudes() {
        return solicitudes;
    }
};

// Implementación de la función de búsqueda binaria que busca una solicitud dada en la lista utilizando el campo de promedio general obtenido
int buscarSolicitud(Lista lista, double promedio) {
    vector<Solicitud> solicitudes = lista.obtenerSolicitudes();
    int izquierda = 0;
    int derecha = solicitudes.size() - 1;

    while (izquierda <= derecha) {
        int medio = (izquierda + derecha) / 2;
        if (solicitudes[medio].promedio == promedio) {
            return medio;
        } else if (solicitudes[medio].promedio < promedio) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }

    return -1;
}

// Implementación del algoritmo de ordenamiento Quicksort para ordenar la lista por orden de promedio general obtenido
void quicksort(vector<Solicitud>& solicitudes, int izquierda, int derecha) {
    int i = izquierda;
    int j = derecha;
    double pivote = solicitudes[(izquierda + derecha) / 2].promedio;

    while (i <= j) {
        while (solicitudes[i].promedio < pivote) {
            i++;
        }
        while (solicitudes[j].promedio > pivote) {
            j--;
        }
        if (i <= j) {
            swap(solicitudes[i], solicitudes[j]);
            i++;
            j--;
        }
    }

    if (izquierda < j) {
        quicksort(solicitudes, izquierda, j);
    }
    if (i < derecha) {
        quicksort(solicitudes, i, derecha);
    }
}

// Función principal del programa
int main() {
    Lista lista;
    bool continuar = true;

    // Solicitar al usuario que ingrese los datos de una solicitud y agregarlo a la lista utilizando la función de inserción de la clase lista
    while (continuar) {
        Solicitud solicitud;
        cout << "Ingrese el nombre del alumno: ";
        getline(cin, solicitud.nombre);
        cout << "Ingrese la carrera a cursar: ";
        getline(cin, solicitud.carrera);
        cout << "Ingrese la preparatoria procedente: ";
        getline(cin, solicitud.preparatoria);
        cout << "Ingrese el promedio general obtenido: ";
        cin >> solicitud.promedio;
        cin.ignore();

        lista.agregarSolicitud(solicitud);

        char respuesta;
        cout << "¿Desea agregar otra solicitud? (S/N): ";
        cin >> respuesta;
        cin.ignore();

        continuar = respuesta == 'S' || respuesta == 's';
    }

    // Utilizar el algoritmo de ordenamiento Quicksort para ordenar la lista por orden de promedio general obtenido
vector<Solicitud> solicitudes = lista.obtenerSolicitudes();
quicksort(solicitudes, 0, solicitudes.size() - 1);

// Solicitar al usuario que ingrese el nombre del alumno para buscar la solicitud correspondiente en la lista utilizando la función de búsqueda binaria
string nombreBusqueda;
cout << "Ingrese el nombre del alumno a buscar: ";
getline(cin, nombreBusqueda);

int posicion = -1;
int izquierda = 0;
int derecha = solicitudes.size() - 1;

while (izquierda <= derecha) {
    int medio = (izquierda + derecha) / 2;
    if (solicitudes[medio].nombre == nombreBusqueda) {
        posicion = medio;
        break;
    } else if (solicitudes[medio].nombre < nombreBusqueda) {
        izquierda = medio + 1;
    } else {
        derecha = medio - 1;
    }
}

if (posicion == -1) {
    cout << "No se encontró la solicitud del alumno. Debe dar de alta una solicitud." << endl;
} else {
    // Si se encuentra la solicitud, mostrar todos los datos de la solicitud y su posición en la lista en función del promedio general obtenido
    cout << "Solicitud encontrada:" << endl;
    cout << "Nombre: " << solicitudes[posicion].nombre << endl;
    cout << "Carrera: " << solicitudes[posicion].carrera << endl;
    cout << "Preparatoria: " << solicitudes[posicion].preparatoria << endl;
    cout << "Promedio: " << solicitudes[posicion].promedio << endl;

    int posicionOrdenada = 0;
    for (int i = 0; i < solicitudes.size(); i++) {
        if (solicitudes[i].promedio < solicitudes[posicion].promedio) {
            posicionOrdenada++;
        } else {
            break;
        }
    }
    cout << "Posición en la lista ordenada por promedio: " << (posicionOrdenada + 1) << endl;
}

return 0;
}
