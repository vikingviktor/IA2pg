#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <string>
#include <math.h>
#include <fstream>
#include <ctime>

int ncoinMax = 0;

class Individuo {

public: std::string frase; 
                double fitness; 
                double fitnessNorm;
public:
        Individuo(std::string frase, double fitness) {
                this->frase = frase;
                this->fitness = fitness;
        }
public: void setFitnessNorm(double fitnessNorm) {
        this->fitnessNorm = fitnessNorm;
}
};
class Poblacion {
public:
        std::vector <Individuo> individuos = {};
public:
        void addIndividuo(Individuo ind) {
                this->individuos.push_back(ind);
        };
};


class Configuracion {
public:
    int NPOB;
    int NGEN;
    int NRES;
    int NTOTAL;
    float Q;
    int ncoinMax;

public:

    void setNcoinMax(int ncoinMax) {
        this->ncoinMax = ncoinMax;
    }
public:

    Configuracion(int NPOB, int NGEN, int NRES, int NTOTAL, float Q) {
        this->NPOB = NPOB;
        this->NGEN = NGEN;
        this->NRES = NRES;
        this->NTOTAL = NTOTAL;
        this->Q = Q;
    }
};

using namespace std;


Poblacion generatePob(string target, int ltar, int NPOB);
double calculateFitness(string target, int ltar, string fraseInd);
double fitnessNormalizado(double fitness, int ltar);
void writeFile(string nameFile, string target, int ltar, Configuracion c);
Configuracion readFile(string nameFile);

int main(int argc, char const *argv[])
{
        Poblacion POB;
        int NPOB = 20;
        int NGEN = 3;
        int NRES = 1;
        int NTOTAL = 2;
        int ltar = 0;
        float Q;
        string target;
        string nameFile;
    
    cout << "\n Introduce su frase: ";
    getline(cin, target, '\n');
    cout << "\n target --> " << target << "\n";
    ltar = target.size();
    cout << "Introduzca el nombre del fichero de configuracion (sin extension) \n";
    cin>>nameFile;
    cout << "Tu tamanio es: " << ltar << "\n";
    Configuracion c = readFile(nameFile);
    writeFile(nameFile, target, ltar, c);
    
    POB = generatePob(target, ltar, NPOB);
        for (int i = 0; i < NPOB; i++)
        {
                POB.individuos[i];
        }
        system("pause");
        return 0;
}

Poblacion generatePob(string target, int ltar, int NPOB) {
        string ABC[27] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", " "};
        string frase_i;
        int i, character;
        int j;
        Poblacion POB;
        double fitness, fitnessNorm;
        srand(time(NULL));
        for (j = 0; j < NPOB; j++) {
                for (i = 0; i<ltar; i++) {
                        character = rand() % 27 + 1;
                        
                        frase_i += ABC[character];
                }
                fitness = calculateFitness(target, ltar, frase_i);
                Individuo i (frase_i, fitness);
                fitnessNorm = fitnessNormalizado(fitness, ltar);
                i.setFitnessNorm(fitnessNorm);
                POB.addIndividuo(i);
                frase_i = "";

        }
        return POB;
}

double calculateFitness(string target, int ltar, string fraseInd)
{
        int ncoin = 0;
        double fitness;
        double e = 2.718281828459045235360;

        for (int i = 0; i<ltar; i++) {
                if (target[i] == fraseInd[i]) {
                        ncoin += 1;
                }
                
        }
        fitness = pow(e, (ncoin - ltar)) - pow(e, (-ltar));
        cout << "\n el fitness es: " << fitness;
        if (ncoin > ncoinMax) {
                ncoinMax = ncoin;
        }

        return fitness;
}

double fitnessNormalizado(double fitness, int ltar)
{
        double e = 2.718281828459045235360;

        double fitnessNorm = (fitness) / pow(e, (ncoinMax - ltar)) - pow(e, (-ltar));
        return fitnessNorm;
}


void writeFile(string nameFile, string target, int ltar, Configuracion c) {
    time_t now = time(0);
    char* dt = ctime(&now);
    nameFile = nameFile + "-S.txt";

    ofstream exitFile;
    exitFile.open(nameFile.c_str());
    exitFile << "-----------------------------------------------" << "\n";
    exitFile << "Fecha de Ejecucion --> " << dt << "\n";
    exitFile << "-----------------------------------------------" << "\n\n";

    exitFile << "--------------------" << "\n";
    exitFile << "--------------------" << "\n";
    exitFile << "PRACTICA 02" << "\n";
    exitFile << "Algoritmos Geneticos" << "\n";
    exitFile << "--------------------" << "\n";
    exitFile << "--------------------" << "\n\n";

    exitFile << "--------------------" << "\n";
    exitFile << "--------------------" << "\n";
    exitFile << "Miembros del grupo 3" << "\n";
    exitFile << "\tFrancisco Lopez Valero \n\tAlvaro Llorente Esteban \n\tVictor Rubio" << "\n";
    exitFile << "--------------------" << "\n";
    exitFile << "--------------------" << "\n\n";

    exitFile << "--------------------" << "\n";
    exitFile << "--------------------" << "\n";
    exitFile << "\tVariables" << "\n";
    exitFile << "--------------------" << "\n";
    exitFile << "--------------------" << "\n";
    exitFile << " Target --> " << target << "\n LTar --> " << ltar << "\n NPOB --> " << c.NPOB << "\n Q --> " << c.Q << "\n NGEN --> " << c.NGEN << "\n";
    exitFile << "--------------------" << "\n";
    exitFile << "--------------------" << "\n\n";


}

Configuracion readFile(string nameFile) {
    nameFile += ".txt";
    ifstream read;
    read.open(nameFile.c_str());
    int npob = 0;
    int ngen = 0;
    int nres = 0;
    int ntotal = 0;
    float q = 0;

    read >> npob >> ngen >> nres >> ntotal >> q;
    //read >> Configuracion.NPOB >> Configuracion.NGEN >> Configuracion.NRES >> Configuracion.NTOTAL >> Configuracion.Q;
    cout << "\n\n Valores de las variables: " << npob << " " << ngen << "\n";

    Configuracion c(npob, ngen, nres, ntotal, q);
    if (read.fail()) {
        cout << "El archivo no ha sido encontrado" << "\n";
        exit(1);
    }
    cout << "El valor de sus variables son: " << " " << c.NGEN << "";
    // cout<<" NPOB --> "<<Configuracion.NPOB<<"\n NGEN --> "<<Configuracion.NGEN<<"\n NRES --> "<<Configuracion.NGEN<<"\n NTOTAL --> "<<Configuracion.NTOTAL<<"\n Q --> "<<Configuracion.Q;
    return c;
}
