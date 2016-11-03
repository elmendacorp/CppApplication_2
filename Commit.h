//
// Created by Fran on 25/10/2016.
//

#ifndef CPPAPPLICATION_2_COMMIT_H
#define CPPAPPLICATION_2_COMMIT_H

#include "Fichero.h"
#include <cassert>
#include "ListaDEnlazada2.h"
#include "vDinamico.h"
#include "fecha.h"

class Commit {
private:
    std::string codigo;
    Fecha marcaDeTiempo;
    std::string mensaje;
    vDinamico<Fichero*>  MisFicheros;
public:
    Commit() {
        codigo = "";
        marcaDeTiempo= Fecha();
    }

    Commit(const std::string &codigo, Fecha marcaDeTiempo, const std::string &mensaje)
            : codigo(codigo), marcaDeTiempo(marcaDeTiempo), mensaje(mensaje){
        MisFicheros=vDinamico<Fichero*>();
    }

    const std::string &getCodigo() const {
        return codigo;
    }

    Fecha getMarcaDeTiempo() const {
        return marcaDeTiempo;
    }

    const std::string &getMensaje() const {
        return mensaje;
    }

    void anadeFichero(Fichero * fichero) {
        MisFicheros.aumenta(fichero);
    }

    bool borraFichero(Fichero &fichero) {


    }
    Fichero buscaFichero(std::string &fichero){
        for(unsigned i=0;i<MisFicheros.tama();++i){
            if(MisFicheros[i]->getNombre()==fichero){
                return *MisFicheros[i];
            }
        }
    }
    bool operator ==(const Commit & orig){
        return ((this->codigo==orig.codigo));
    }
    bool operator !=(const Commit & orig){
        return ((this->codigo!=orig.codigo));
    }
};


#endif //CPPAPPLICATION_2_COMMIT_H
