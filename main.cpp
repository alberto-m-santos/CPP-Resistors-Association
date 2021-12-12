#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

vector<long> resistencias = {100, 200, 330, 470, 680, 1000, 2000, 3300, 4700, 6800, 33000, 100000};
vector<string> impedanciaTextual;
float impedanciasPossiveis[3];

/* Calcula a resistencia equivalente em paralelo */
float ResEquivParalelo(long res1, long res2, long res3, long res4) {
    float res = pow(res1, -1) + pow(res2, -1) + pow(res3, -1) + pow(res4, -1);
    res = 1 / res;
    return res;
}

/* Calcula a resistencia equivalente em serie */
float ResEquivSerie(long res1, long res2, long res3, long res4) {
    return res1 + res2 + res3 + res4;
}

void colocarResistencia() {
    for (int i = 0; i < resistencias.size(); i++) {
        if (resistencias.at(i) > impedanciasPossiveis[0] && resistencias.at(i) < impedanciasPossiveis[1]) {
            impedanciaTextual.push_back(to_string(impedanciasPossiveis[2]) + " = " + to_string(resistencias.at(i)));
        }
    }
}

/* Combinacao de resistencias 1 */
void quatroParaleloZeroSerie() {
    for (int i = 0; i < resistencias.size(); i++) {
        for (int j = 0; j < resistencias.size(); j++) {
            for (int k = 0; k < resistencias.size(); k++) {
                for (int l = 0; l < resistencias.size(); l++) {

                    float res = ResEquivParalelo(resistencias.at(i), resistencias.at(j), resistencias.at(k),
                                                 resistencias.at(l));
                    if (res > impedanciasPossiveis[0] && res < impedanciasPossiveis[1]) {

                        impedanciaTextual.push_back(
                                to_string(res) + " = " + to_string(resistencias.at(i)) + " || " +
                                to_string(resistencias.at(j)) + " || " +
                                to_string(resistencias.at(k)) + " || " +
                                to_string(resistencias.at(l)));
                    }
                }
            }
        }
    }
}

/* Combinacao de resistencias 2 */
void tresParaleloUmSerie() {
    float res;
    for (int i = 0; i < resistencias.size(); i++) {
        for (int j = 0; j < resistencias.size(); j++) {
            for (int k = 0; k < resistencias.size(); k++) {
                for (int l = 0; l < resistencias.size(); l++) {
                    res = ResEquivParalelo(resistencias.at(i), resistencias.at(j), resistencias.at(k), INFINITY);
                    res = ResEquivSerie(res, resistencias.at(l), 0, 0);
                    if (res > impedanciasPossiveis[0] && res < impedanciasPossiveis[1]) {
                        impedanciaTextual.push_back(
                                to_string(res) + " = " + to_string(resistencias.at(l)) + " + ( " +
                                to_string(resistencias.at(i)) + " || " +
                                to_string(resistencias.at(j)) + " || " +
                                to_string(resistencias.at(k)) + " )");
                    }
                }
            }
        }
    }
}

/* Combinacao de resistencias 3 */
void doisParaleloDoisSerie() {
    float res;
    for (int i = 0; i < resistencias.size(); i++) {
        for (int j = 0; j < resistencias.size(); j++) {
            for (int k = 0; k < resistencias.size(); k++) {
                for (int l = 0; l < resistencias.size(); l++) {
                    res = ResEquivParalelo(resistencias.at(i), resistencias.at(j), INFINITY, INFINITY);
                    res = ResEquivSerie(res, resistencias.at(k), resistencias.at(l), 0);
                    if (res > impedanciasPossiveis[0] && res < impedanciasPossiveis[1]) {
                        impedanciaTextual.push_back(
                                to_string(res) + " = " + to_string(resistencias.at(l)) + " + " +
                                to_string(resistencias.at(k)) + " ( " +
                                to_string(resistencias.at(i)) + " || " +
                                to_string(resistencias.at(j)) + " )");
                    }
                }
            }
        }
    }
}

/* Combinacao de resistencias 4 */
void umParaleloTresSerie() {
    float res;
    for (int i = 0; i < resistencias.size(); i++) {
        for (int j = 0; j < resistencias.size(); j++) {
            for (int k = 0; k < resistencias.size(); k++) {
                for (int l = 0; l < resistencias.size(); l++) {
                    res = ResEquivSerie(resistencias.at(i), resistencias.at(j), resistencias.at(k), 0);
                    res = ResEquivParalelo(res, resistencias.at(l), INFINITY, INFINITY);
                    if (res > impedanciasPossiveis[0] && res < impedanciasPossiveis[1]) {
                        impedanciaTextual.push_back(
                                to_string(res) + " = ( " + to_string(resistencias.at(i)) + " + " +
                                to_string(resistencias.at(j)) + " + " +
                                to_string(resistencias.at(k)) + " ) || " +
                                to_string(resistencias.at(l)));
                    }
                }
            }
        }
    }
}

/* Combinacao de resistencias 5 */
void zeroParaleloQuatroSerie() {
    for (int i = 0; i < resistencias.size(); i++) {
        for (int j = 0; j < resistencias.size(); j++) {
            for (int k = 0; k < resistencias.size(); k++) {
                for (int l = 0; l < resistencias.size(); l++) {
                    long res =
                            ResEquivSerie(resistencias.at(i), resistencias.at(j), resistencias.at(k),
                                          resistencias.at(l));
                    if (res > impedanciasPossiveis[0] && res < impedanciasPossiveis[1]) {
                        impedanciaTextual.push_back(
                                to_string(res) + " = ( " + to_string(resistencias.at(i)) + " + " +
                                to_string(resistencias.at(j)) + " + " +
                                to_string(resistencias.at(k)) + " + " +
                                to_string(resistencias.at(l)) + " )");
                    }
                }
            }
        }
    }

}

void doisSerie() {
    for (int i = 0; i < resistencias.size(); i++) {
        for (int j = 0; j < resistencias.size(); j++) {
            long res =
                    ResEquivSerie(resistencias.at(i), resistencias.at(j), 0, 0);
            if (res > impedanciasPossiveis[0] && res < impedanciasPossiveis[1]) {
                impedanciaTextual.push_back(
                        to_string(res) + " = " + to_string(resistencias.at(i)) + " + " +
                        to_string(resistencias.at(j)));
            }
        }
    }
}

void doisParalelo() {
    for (int i = 0; i < resistencias.size(); i++) {
        for (int j = 0; j < resistencias.size(); j++) {
            long res =
                    ResEquivParalelo(resistencias.at(i), resistencias.at(j), INFINITY, INFINITY);
            if (res > impedanciasPossiveis[0] && res < impedanciasPossiveis[1]) {
                impedanciaTextual.push_back(
                        to_string(res) + " = " + to_string(resistencias.at(i)) + " || " +
                        to_string(resistencias.at(j)));
            }
        }
    }
}

void calcula() {
    colocarResistencia();
    quatroParaleloZeroSerie();
    tresParaleloUmSerie();
    doisParaleloDoisSerie();
    umParaleloTresSerie();
    zeroParaleloQuatroSerie();
    doisSerie();
    doisParalelo();
}

void imprimeSequenciasPossiveis() {
    for (int i = 0; i < impedanciaTextual.size(); i++) {
        cout << impedanciaTextual.at(i) << endl;
    }
}

int main() {


    float imp, tol;
    do {
        cout << "-----------------------------------------------" << endl;
        cout << "* Associacao de resistencias serie e paralelo *" << endl;
        cout << "-----------------------------------------------" << endl;

        cout << "Qual o valor de impedancia desejado? (Ohm)" << endl;
        cin >> imp;
        do {
            cout << "Qual o valor de tolerancia desejado? (Percentagem)" << endl;
            cin >> tol;
        } while (tol < 0.1 || tol > 5);
        tol = tol / 100;
        impedanciasPossiveis[0] = imp - imp * tol;
        impedanciasPossiveis[1] = imp + imp * tol;
        impedanciasPossiveis[2] = imp;
        cout << "Impedancias possiveis: " + to_string(impedanciasPossiveis[0]) +
                " - " + to_string(impedanciasPossiveis[1]) + "\n" << endl;
        calcula();
        imprimeSequenciasPossiveis();
        impedanciaTextual.clear();//apaga as impedancias possiveis
    } while (imp != 0);

    return 0;
}
