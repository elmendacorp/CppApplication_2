//
// Created by Fran on 25/10/2016.
//

#include "Gitcode.h"
#include <fstream>
#include <iostream>


Commit Gitcode::getCommit(std::string &commi) {
    Nodo<Commit>  *ini = commits.inicio();
    while (ini!=commits.final()){
        if(ini->GetElemento().getCodigo()==commi){
            return ini->GetElemento();
        }else{
            ini=ini->GetSiguiente();
        }

    }

}

ListaDEnlazada<Commit> Gitcode::getCommitFechas(const Fecha &inicio, const Fecha &fin) {
    ListaDEnlazada<Commit>temporal= ListaDEnlazada<Commit>();
    Nodo<Commit> *temp = commits.inicio();
    while(temp!=commits.final()){
        if(temp->GetElemento().getMarcaDeTiempo()<fin&&temp->GetElemento().getMarcaDeTiempo()>inicio){
            Commit t=temp->GetElemento();
            temporal.insertarFinal(t);
        }
        temp=temp->GetSiguiente();
    }

    return temporal;
}

ListaDEnlazada<Commit> Gitcode::getCommitFichero(std::string fichero) {
    ListaDEnlazada<Commit>temporal= ListaDEnlazada<Commit>();
    Nodo<Commit> *tempo = commits.inicio();
    while(tempo!=commits.final()){
        Fichero t=tempo->GetElemento().buscaFichero(fichero);
        if(t.getTamaBytes()!=0){
            Commit d=tempo->GetElemento();
            temporal.insertarFinal(d);
        }
        tempo=tempo->GetSiguiente();
    }

    return temporal;
}

Gitcode::Gitcode(const std::string & fich,const std::string & commi) {
    commits= ListaDEnlazada<Commit>();
    ficheros= vDinamico<Fichero*>();
    std::string lineaActual;
    try {
        std::ifstream inputStream;
        inputStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        inputStream.open(fich);

        inputStream >> lineaActual;

        while (!inputStream.eof()) {
            Fichero * f;
            std::getline(inputStream >> ws, lineaActual);

            auto pos = lineaActual.find(';');
            auto ruta = lineaActual.substr(0, pos);
            auto tama = lineaActual.substr(pos + 1, ruta.length()-1);

            pos = ruta.find_last_of('/');
            auto ubicacion = ruta.substr(0, pos + 1);
            auto nombre = ruta.substr(pos + 1, ruta.length());
            auto tamaBytes = std::stoi(tama);
            f = new Fichero(nombre, ubicacion, tamaBytes);
            ficheros.aumenta(f);



        }
        inputStream.close();
    } catch (exception &e) {
        std::cerr << "Excepcion leyendo el fichero: " << e.what() << std::endl;
    }

    int ref;
    try {
        std::ifstream inputStream;

        inputStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        inputStream.open(commi);
        inputStream >> lineaActual;

        while (!inputStream.eof()) {
            std::getline(inputStream >> ws, lineaActual);

            auto pos = lineaActual.find_last_of(';');
            auto indice = lineaActual.substr(pos + 1, lineaActual.size());
            auto substr1 = lineaActual.substr(0, pos);
            pos = substr1.find_last_of(';');
            auto mensaje = lineaActual.substr(pos + 1, substr1.size());
            substr1 = substr1.substr(0, pos);
            pos = substr1.find_last_of(';');
            auto marcaTiempo = substr1.substr(pos + 1, substr1.size());

            Fecha fch=Fecha();
            fch.anadirAnios(std::stoi(marcaTiempo.substr(0,4)));
            fch.anadirMeses(std::stoi(marcaTiempo.substr(4,6)));
            fch.anadirDias(std::stoi(marcaTiempo.substr(6,8)));
            fch.anadirHoras(std::stoi(marcaTiempo.substr(8,10)));
            fch.anadirMin(std::stoi(marcaTiempo.substr(10,12)));

            auto codigo = substr1.substr(0, pos);
            Commit inserta= Commit(codigo,fch,mensaje);

            pos = 0;
            indice = indice.substr(0,(indice.size()-1));
            while (pos != indice.find_first_of(',')) {
                pos = indice.find_last_of(',');
                ref = std::stoi(indice.substr(pos + 1, substr1.size()));
                inserta.anadeFichero(ficheros[ref]);
                indice = indice.substr(0, pos);
            }
            commits.insertarFinal(inserta);

        }
        inputStream.close();
    } catch (exception &e) {
        std::cerr << "Excepcion leyendo el fichero: " << e.what() << std::endl;
    }
}

void Gitcode::eliminaFichero(Fichero &fichero) {
    Nodo<Commit>* temp= commits.inicio();
    while(temp!=commits.final()){
        temp->GetElemento().borraFichero(fichero);
        temp= temp->GetSiguiente();
    }
}

