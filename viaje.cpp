#include <iostream>
#include <stdlib.h>

using namespace std;

struct Pasajero {
    char nombre[45];
    Pasajero* sig;
};

struct Embarcacion {
    char nombreEmbarcacion[25];
    int dia, mes, year;
    char destino[35];
    int capacidad;
    char identificador[15]; 
    char matricula[10];
    float precio;
    Embarcacion* izq;
    Embarcacion* der;
    int altura;
    Pasajero* inicioPasajeros;
    Pasajero* finPasajeros;
    int numPasajeros;
};

Embarcacion* raiz = NULL;

int obtenerAltura(Embarcacion* n) {
    if (n == NULL) return 0;
    return n->altura;
}

int mayor(int a, int b) {
    return (a > b) ? a : b;
}

int obtenerBalance(Embarcacion* n) {
    if (n == NULL) return 0;
    return obtenerAltura(n->izq) - obtenerAltura(n->der);
}

Embarcacion* rotarDerecha(Embarcacion* y) {
    Embarcacion* x = y->izq;
    Embarcacion* T2 = x->der;

    x->der = y;
    y->izq = T2;

    y->altura = mayor(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;
    x->altura = mayor(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;

    return x;
}

Embarcacion* rotarIzquierda(Embarcacion* x) {
    Embarcacion* y = x->der;
    Embarcacion* T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->altura = mayor(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;
    y->altura = mayor(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;

    return y;
}

Embarcacion* crearNodo() {
    Embarcacion* nuevo = (Embarcacion*)malloc(sizeof(Embarcacion));
    cout << "Cual es el nombre de la embarcacion: ";
    cin >> nuevo->nombreEmbarcacion;
    cout << "Ingrese el año: ";
    cin >> nuevo->year;
    cout << "Ingrese el mes: ";
    cin >> nuevo->mes;
    cout << "Ingrese el dia: ";
    cin >> nuevo->dia;
    cout << "Ingrese el destino de la embarcacion: ";
    cin >> nuevo->destino;
    cout << "Ingrese la capacidad de la embarcacion: ";
    cin >> nuevo->capacidad;
    cout << "Ingrese la matricula de la embarcacion: ";
    cin >> nuevo->matricula;
    cout << "Ingrese el precio del viaje: ";
    cin >> nuevo->precio;
    cout << "Ingrese el identificador: ";
    

    (nuevo->identificador, 15, "%.2s%04d%02d%02d", nuevo->matricula, nuevo->year, nuevo->mes, nuevo->dia);
    
    nuevo->izq = NULL;
    nuevo->der = NULL;
    nuevo->altura = 1;
    nuevo->inicioPasajeros = NULL;
    nuevo->finPasajeros = NULL;
    nuevo->numPasajeros = 0;

    return nuevo;
}

Embarcacion* insertar(Embarcacion* nodo, Embarcacion* nuevo) {
    if (nodo == NULL) {
        return nuevo;
    }

    if ((nuevo->identificador, nodo->identificador) < 0) {
        nodo->izq = insertar(nodo->izq, nuevo);
    } else if ((nuevo->identificador, nodo->identificador) > 0) {
        nodo->der = insertar(nodo->der, nuevo);
    } else {
        return nodo;
    }

    nodo->altura = 1 + mayor(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && (nuevo->identificador, nodo->izq->identificador) < 0) {
        return rotarDerecha(nodo);
    }

    if (balance < -1 && (nuevo->identificador, nodo->der->identificador) > 0) {
        return rotarIzquierda(nodo);
    }

    if (balance > 1 && (nuevo->identificador, nodo->izq->identificador) > 0) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && (nuevo->identificador, nodo->der->identificador) < 0) {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

void inOrden(Embarcacion* nodo) {
    if (nodo != NULL) {
        inOrden(nodo->izq);
        cout << "Nombre: " << nodo->nombreEmbarcacion << ", Identificador: " << nodo->identificador << endl;
        inOrden(nodo->der);
    }
}

Embarcacion* buscarEmbarcacion(Embarcacion* nodo, const char* identificadorBusqueda) {
    if (nodo == NULL || (nodo->identificador, identificadorBusqueda) == 0) {
        return nodo;
    }

    if ((identificadorBusqueda, nodo->identificador) < 0) {
        return buscarEmbarcacion(nodo->izq, identificadorBusqueda);
    } else {
        return buscarEmbarcacion(nodo->der, identificadorBusqueda);
    }
}

void registrarPasajero(Embarcacion* viaje) {
    if (viaje->numPasajeros >= viaje->capacidad) {
        cout << "La embarcacion ha alcanzado su capacidad maxima." << endl;
        return;
    }

    Pasajero* nuevoPasajero = (Pasajero*)malloc(sizeof(Pasajero));
    cout << "Ingrese el nombre del pasajero: ";
    cin >> nuevoPasajero->nombre;
    nuevoPasajero->sig = NULL;

    if (viaje->inicioPasajeros == NULL) {
        viaje->inicioPasajeros = nuevoPasajero;
        viaje->finPasajeros = nuevoPasajero;
    } else {
        viaje->finPasajeros->sig = nuevoPasajero;
        viaje->finPasajeros = nuevoPasajero;
    }

    viaje->numPasajeros++;
    cout << "Pasajero registrado exitosamente." << endl;
}

void listarPasajeros(Embarcacion* viaje) {
    if (viaje->inicioPasajeros == NULL) {
        cout << "No hay pasajeros registrados en este viaje." << endl;
        return;
    }

    Pasajero* temp = viaje->inicioPasajeros;
    int count = 1;
    while (temp != NULL) {
        cout << count << ". " << temp->nombre << endl;
        temp = temp->sig;
        count++;
    }
}

Embarcacion* eliminarNodo(Embarcacion* raiz, const char* identificador) {
    if (raiz == NULL) {
        return raiz;
    }

    if ((identificador, raiz->identificador) < 0) {
        raiz->izq = eliminarNodo(raiz->izq, identificador);
    } else if ((identificador, raiz->identificador) > 0) {
        raiz->der = eliminarNodo(raiz->der, identificador);
    } else {
        if ((raiz->izq == NULL) || (raiz->der == NULL)) {
            Embarcacion* temp = raiz->izq ? raiz->izq : raiz->der;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            Embarcacion* temp = raiz->der;
            while (temp->izq != NULL) {
                temp = temp->izq;
            }

            (raiz->identificador, temp->identificador);
            raiz->der = eliminarNodo(raiz->der, identificador);
        }
    }

    if (raiz == NULL) {
        return raiz;
    }

    raiz->altura = 1 + mayor(obtenerAltura(raiz->izq), obtenerAltura(raiz->der));

    int balance = obtenerBalance(raiz);

    if (balance > 1 && obtenerBalance(raiz->izq) >= 0) {
        return rotarDerecha(raiz);
    }

    if (balance > 1 && obtenerBalance(raiz->izq) < 0) {
        raiz->izq = rotarIzquierda(raiz->izq);
        return rotarDerecha(raiz);
    }

    if (balance < -1 && obtenerBalance(raiz->der) <= 0) {
        return rotarIzquierda(raiz);
    }

    if (balance < -1 && obtenerBalance(raiz->der) > 0) {
        raiz->der = rotarDerecha(raiz->der);
        return rotarIzquierda(raiz);
    }

    return raiz;
}

int main() {
    int opcion;
    do {
        cout << "Menu de opciones" << endl;
        cout << "1. Registrar un nuevo viaje" << endl;
        cout << "2. Buscar un viaje por identificador" << endl;
        cout << "3. Listar todos los viajes" << endl;
        cout << "4. Eliminar un viaje por identificador" << endl;
        cout << "5. Registrar un pasajero en un viaje" << endl;
        cout << "6. Listar todos los pasajeros de un viaje" << endl;
        cout << "7. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        char identificador[15];
        Embarcacion* viaje = NULL;

        switch (opcion) {
            case 1:
                raiz = insertar(raiz, crearNodo());
                break;
            case 2:
                cout << "Ingrese el identificador del viaje: ";
                cin >> identificador;
                viaje = buscarEmbarcacion(raiz, identificador);
                if (viaje != NULL) {
                    cout << "Viaje encontrado: " << endl;
                    cout << "Nombre: " << viaje->nombreEmbarcacion << ", Identificador: " << viaje->identificador << endl;
                } else {
                    cout << "Viaje no encontrado." << endl;
                }
                break;
            case 3:
                cout << "Lista de todos los viajes:" << endl;
                inOrden(raiz);
                break;
            case 4:
                cout << "Ingrese el identificador del viaje a eliminar: ";
                cin >> identificador;
                raiz = eliminarNodo(raiz, identificador);
                cout << "Viaje eliminado." << endl;
                break;
            case 5:
                cout << "Ingrese el identificador del viaje: ";
                cin >> identificador;
                viaje = buscarEmbarcacion(raiz, identificador);
                if (viaje != NULL) {
                    registrarPasajero(viaje);
                } else {
                    cout << "Viaje no encontrado." << endl;
                }
                break;
            case 6:
                cout << "Ingrese el identificador del viaje: ";
                cin >> identificador;
                viaje = buscarEmbarcacion(raiz, identificador);
                if (viaje != NULL) {
                    listarPasajeros(viaje);
                } else {
                    cout << "Viaje no encontrado." << endl;
                }
                break;
            case 7:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida. Por favor, intente nuevamente." << endl;
        }
    } while (opcion != 7);

    return 0;
}
