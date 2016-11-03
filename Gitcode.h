//
// Created by Fran on 25/10/2016.
//

#ifndef CPPAPPLICATION_2_GITCODE_H
#define CPPAPPLICATION_2_GITCODE_H

#include "Fichero.h"
#include "Commit.h"
#include "fecha.h"
#include "ListaDEnlazada2.h"
#include "vDinamico.h"

class Gitcode {
private:
    ListaDEnlazada<Commit> commits;
    vDinamico<Fichero*> ficheros;
    std::string fileFichero;
    std::string fileCommits;
    Fecha *fecha;
public:
    Commit getCommit(std::string &commi);

    ListaDEnlazada<Commit> getCommitFechas(const Fecha &inicio, const Fecha &fin);

    ListaDEnlazada<Commit> getCommitFichero(std::string fichero);

    Gitcode(const std::string & fich,const std::string & commi);

    void eliminaFichero(Fichero &fichero);
};


#endif //CPPAPPLICATION_2_GITCODE_H
