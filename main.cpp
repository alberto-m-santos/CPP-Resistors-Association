#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

vector<float> Resistencias = { 100.0,200.0,330.0,470.0,680.0,1000.0,2000.0,3300.0,4700.0,6800.0,33000.0,100000.0 };
vector<float> ImpedanciasPossiveis = { 100.0,200.0,330.0,470.0,680.0,1000.0,2000.0,3300.0,4700.0,6800.0,33000.0,100000.0 };
//vector<string> Esquematico;
int Combinacoes = 0;

/* Inicializacao das funcoes */
void swap(float* xp, float* yp);
void bubbleSort(vector<float> arr, int n);
//int RemoverElementosDuplicados(vector<float> arr, int n);
int RemoverElementosSimilares(vector<float> arr, int n);
void QuatroParaleloZeroSerie();
void TresParaleloUmSerie();
void DoisParaleloDoisSerie();
void UmParaleloTresSerie();
void ZeroParaleloQuatroSerie();
float ResEquivParalelo(float res1, float res2, float res3, float res4);
float ResEquivSerie(float res1, float res2, float res3, float res4);
void ImprimeImpedanciasPossiveis();
//void ImprimeEsquematicosPossiveis();

/* Troca dois elementos num array */
void swap(float* xp, float* yp)
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/* Ordena um array por ordem crescente */
void bubbleSort(vector<float> arr, int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}

/* Remove elementos duplicados num array */
//int RemoverElementosDuplicados(vector<float> arr, int n)
//{
//    if (n == 0 || n == 1)
//        return n;
//
//    vector<float> temp;
//
//
//    int j = 0;
//    int i;
//    for (i = 0; i < n - 1; i++) {
//        if (arr.at(i) != arr.at(i + 1)) {
//            j++;
//            temp.push_back(arr.at(i));
//        }
//    }      
//    temp.at(j++) = arr.at(n - 1);
//
//    for (i = 0; i < j; i++) {
//        arr.clear();
//        arr.push_back(temp.at(i));
//    }
//        
//    return j;
//}

/* Remove elementos consecutivos que variam menos de 0.1% */
int RemoverElementosSimilares(vector<float> arr, int n)
{
    if (n == 0 || n == 1)
        return n;

    vector<float> temp;


    int j = 0;
    int i;
    for (i = 0; i < n - 1; i++) {
        if (arr[i+1] > 1.001 * arr[i]) {
            j++;
            temp.push_back(arr.at(i));
        }
    }
    temp[j++] = arr[n-1];

    for (i = 0; i < j; i++) {
        arr.clear();
        arr.push_back(temp.at(i));
    }

    return j;
}

/* Combinacao de resistencias 1 */
void QuatroParaleloZeroSerie()
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            for (int k = 0; k < 12; k++)
            {
                for (int l = 0; l < 12; l++)
                {
                    ImpedanciasPossiveis.push_back(ResEquivParalelo(Resistencias.at(i), Resistencias.at(j), Resistencias.at(k), Resistencias.at(l)));
                    //sprintf(Esquematico[Combinacoes], "(|| %f || %f || %f || %f ||)", Resistencias[i], Resistencias[j], Resistencias[k], Resistencias[l]);
                    Combinacoes++;
                }
            }
        }
    }
}

/* Combinacao de resistencias 2 */
void TresParaleloUmSerie()
{
    float res;
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            for (int k = 0; k < 12; k++)
            {
                for (int l = 0; l < 12; l++)
                {
                    res = ResEquivParalelo(Resistencias.at(i), Resistencias.at(j), Resistencias.at(k), INFINITY);
                    ImpedanciasPossiveis.push_back(ResEquivSerie(res, Resistencias.at(l), 0, 0));
                    //sprintf(Esquematico[Combinacoes], "(|| %1.f || %1.f || %1.f || - %1.f)",Resistencias[i], Resistencias[j], Resistencias[k], Resistencias[l]);
                    Combinacoes++;
                }
            }
        }
    }
}

/* Combinacao de resistencias 3 */
void DoisParaleloDoisSerie()
{
    float res;
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            for (int k = 0; k < 12; k++)
            {
                for (int l = 0; l < 12; l++)
                {
                    res = ResEquivParalelo(Resistencias.at(i), Resistencias.at(j), INFINITY, INFINITY);
                    ImpedanciasPossiveis.push_back(ResEquivSerie(res, Resistencias.at(k), Resistencias.at(l), 0));
                    //sprintf(Esquematico[Combinacoes], "(|| %1.f || %1.f || %1.f - %1.f)",Resistencias[i], Resistencias[j], Resistencias[k], Resistencias[l]);
                    Combinacoes++;
                }
            }
        }
    }
}

/* Combinacao de resistencias 4 */
void UmParaleloTresSerie()
{
    float res;
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            for (int k = 0; k < 12; k++)
            {
                for (int l = 0; l < 12; l++)
                {
                    res = ResEquivSerie(Resistencias.at(i), Resistencias.at(j), Resistencias.at(k), 0);
                    ImpedanciasPossiveis.push_back(ResEquivParalelo(res, Resistencias.at(l), INFINITY, INFINITY));
                    //sprintf(Esquematico[Combinacoes], "(|| %1.f || %1.f - %1.f - %1.f)",Resistencias[i], Resistencias[j], Resistencias[k], Resistencias[l]);
                    Combinacoes++;
                }
            }
        }
    }
}

/* Combinacao de resistencias 5 */
void ZeroParaleloQuatroSerie()
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            for (int k = 0; k < 12; k++)
            {
                for (int l = 0; l < 12; l++)
                {
                    ImpedanciasPossiveis.push_back(ResEquivSerie(Resistencias.at(i), Resistencias.at(j), Resistencias.at(k), Resistencias.at(l)));
                    //sprintf(Esquematico[Combinacoes], "(%1.f - %1.f - %1.f - %1.f)",Resistencias[i], Resistencias[j], Resistencias[k], Resistencias[l]);
                    Combinacoes++;
                }
            }
        }
    }

}

/* Calcula a resistencia equivalente em paralelo */
float ResEquivParalelo(float res1, float res2, float res3, float res4)
{
    float res = pow(res1, -1) + pow(res2, -1) + pow(res3, -1) + pow(res4, -1);
    res = 1 / res;
    return res;
}

/* Calcula a resistencia equivalente em serie */
float ResEquivSerie(float res1, float res2, float res3, float res4)
{
    return res1 + res2 + res3 + res4;
}

/* Imprime as impedancias do array de combinacoes */
void ImprimeImpedanciasPossiveis()
{
    for (int i = 0; i < Combinacoes; i++)
    {
        cout << ImpedanciasPossiveis.at(i);
    }
}

//void ImprimeEsquematicosPossiveis()
//{
//    for(int i=0; i<Combinacoes; i++)
//    {
//        cout << Esquematico.at(i);
//    }
//}

int main()
{
    cout << " Loading . . ." << endl;

    /* Carrega as 5 possiveis combinacoes de resistencias */
    QuatroParaleloZeroSerie();
    TresParaleloUmSerie();
    DoisParaleloDoisSerie();
    UmParaleloTresSerie();
    ZeroParaleloQuatroSerie();

    /* Ordena, remove duplicado e similares do array de combinacoes */

    sort(ImpedanciasPossiveis.begin(), ImpedanciasPossiveis.end());
    ImpedanciasPossiveis.erase(unique(ImpedanciasPossiveis.begin(), ImpedanciasPossiveis.end()), ImpedanciasPossiveis.end());
    //RemoverElementosDuplicados(ImpedanciasPossiveis, Combinacoes);
    RemoverElementosSimilares(ImpedanciasPossiveis, Combinacoes);

    float imp, tol;
    int i;

    system("cls");

    do
    {
        system("cls");
        cout << "-----------------------------------------------" << endl;
        cout << "* Associacao de resistencias serie e paralelo *" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Qual o valor de impedancia desejado? (Ohm)" << endl;
        cin >> imp;
        cout << "Qual o valor de tolerancia desejado? (Percentagem)" << endl;
        cin >> tol;
        tol = tol / 100;

        /* Percorre o array e encontra impedancias dentro dos limites pedidos */
        for (i = 0; i < ImpedanciasPossiveis.size(); i++) {
            if (abs(ImpedanciasPossiveis.at(i) - imp) <= tol * imp) {
                cout << "Impedancia possivel:" << ImpedanciasPossiveis.at(i) << "Ohms" << endl;
            }
        }
        printf("\n\n");
        system("pause");
    } while (imp != 0);

    return 0;
}
