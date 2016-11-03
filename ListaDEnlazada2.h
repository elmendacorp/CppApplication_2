/* 
 * File:   ListaDEnlazada.
 * Author: Fran
 *
 * Created on 19 de octubre de 2016, 17:05
 */

#ifndef LISTADENLAZADA_
#define    LISTADENLAZADA_

#include "cassert"

template<typename T>
class Nodo {
private:
    T elemento;
    Nodo<T> *anterior;
    Nodo<T> *siguiente;
public:

    Nodo() : anterior(0), siguiente(0) {
    };

    Nodo(const T &elem, Nodo *ant, Nodo *sig) : elemento(elem), anterior(ant), siguiente(sig) {
    }

    bool operator==(const Nodo<T> &orig) {
        return *this == orig;
    }

    Nodo(const Nodo<T> &orig) {
        elemento = orig.elemento;
        anterior = orig.anterior;
        siguiente = orig.siguiente;
    }

    void SetSiguiente(Nodo<T> *sig) {
        siguiente = sig;
    }

    Nodo *GetSiguiente() const {
        return siguiente;
    }

    void SetAnterior(Nodo *ant) {
        this->anterior = ant;
    }

    Nodo *GetAnterior() const {
        return anterior;
    }

    void SetElemento(T &elemento) {
        this->elemento = elemento;
    }

    T GetElemento() {
        return elemento;
    }

    bool operator!=(const Nodo<T> &orig) {
        return *this != orig;
    }
};

template<typename T>
class Iterador {
private:
    Nodo<T> *nodo;

    friend class ListaDEnlazada;

public:
    Iterador(Nodo<T> *aNodo) : nodo(aNodo) {}

    bool hayAnterior() { return nodo->GetAnterior() != 0; }

    bool haySiguiente() { return nodo->GetSiguiente() != 0; }

    void anterior() { nodo = nodo->GetAnterior(); }

    void siguiente() { nodo = nodo->GetSiguiente(); }

    bool operator!=(const Iterador<T> &orig) { return this->nodo != orig.nodo; }

    T dato() { return nodo->GetElemento(); }


};

/**Clase Lista enlazada
 */
template<typename T>
class ListaDEnlazada {
private:
    Nodo<T> *cabecera, *cola;
public:

    ListaDEnlazada();

    ~ListaDEnlazada();

    ListaDEnlazada(const ListaDEnlazada &orig);

    ListaDEnlazada operator=(const ListaDEnlazada &orig);

    Iterador<T> iteradorInicio() { return Iterador<T>(cabecera); };

    Iterador<T> iteradorFin() { return Iterador<T>(cola); };

    void insertarInicio(T &dato);

    void insertarFinal(T &dato);

    void insertar(Iterador<T> &i, T &dato);

    void borrarInicio();

    void borrarFinal();

    void borrar(Iterador<T> &i);

    Nodo<T> *inicio() {
        return cabecera;
    }

    Nodo<T> *final() {
        return cola;
    }

};


template<typename T>
void ListaDEnlazada<T>::borrarFinal() {
    if (cola != 0) {
        cola = cola->GetAnterior();
        delete cola->GetSiguiente();
        cola->SetSiguiente(0);
    }
}

template<typename T>
void ListaDEnlazada<T>::borrarInicio() {
    if (cabecera != 0) {
        cabecera = cabecera->GetSiguiente();
        delete cabecera->GetAnterior();
    }
}

template<typename T>
void ListaDEnlazada<T>::insertarFinal(T &dato) {
    Nodo<T> *temporal = new Nodo<T>();
    temporal->SetElemento(dato);
    temporal->SetAnterior(cola);
    cola->SetSiguiente(temporal);
    if (cabecera == 0) {
        cabecera = temporal;
    }
    cola = temporal;

}

template<typename T>
void ListaDEnlazada<T>::insertarInicio(T &dato) {
    Nodo<T> *temporal = new Nodo<T>();
    temporal->SetElemento(dato);
    if(cabecera!=0){
        temporal->SetSiguiente(cabecera);
    }
    temporal->SetAnterior(0);
    cabecera = temporal;
    if (cola == 0) {
        cola = cabecera;
    }
}

template<typename T>
void ListaDEnlazada<T>::insertar(Iterador<T> &i, T &dato) {
    assert(i.nodo != 0);
    Nodo<T> *temporal = new Nodo<T>();
    temporal->SetElemento(dato);
    if (i.haySiguiente()) {
        temporal->SetSiguiente(i.nodo->GetSiguiente());
        i.nodo->SetAnterior(temporal);
    }
    if (i.hayAnterior()) {
        temporal->SetAnterior(i.nodo->GetAnterior());
        i.nodo->SetSiguiente(temporal);
    }
    if (i.nodo == cabecera) {
        temporal->SetAnterior(0);
        cabecera = temporal;
    }
    if (i.nodo == cola) {
        temporal->SetSiguiente(0);
        cola = temporal;
    }
}

template<typename T>
void ListaDEnlazada<T>::borrar(Iterador<T> &i) {
    Nodo<T> *temporal(i.nodo);
    assert(temporal != 0);
    temporal->GetAnterior()->SetSiguiente(temporal->GetSiguiente());
    temporal->GetSiguiente()->SetAnterior(temporal->GetAnterior());

}


template<typename T>
ListaDEnlazada<T> ListaDEnlazada<T>::operator=(const ListaDEnlazada &orig) {
    cabecera = orig.cabecera;
    cola = orig.cola;
    return *this;
}


template<typename T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada &orig) {
    cabecera = orig.cabecera;
    cola = orig.cola;
}

template<typename T>
ListaDEnlazada<T>::~ListaDEnlazada() {
    while (cabecera != cola) {
        cabecera = cabecera->GetSiguiente();
        delete cabecera->GetAnterior();
    }
    delete cabecera;
}


template<typename T>
ListaDEnlazada<T>::ListaDEnlazada() {
    cabecera = 0;
    cola = 0;
}


#endif	/* LISTADENLAZADA_ */