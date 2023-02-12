#ifndef FUNCTIONS_H_INCLUDED2
#define FUNCTIONS_H_INCLUDED2
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int* CamadaEnlaceDadosTransmissora (int quadro []);
int* CamadaDeEnlaceDadosTransmissoraEnquadramento (int quadro []);
int* CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres (int quadro []);
int* CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes (int quadro []);
int* CamadaDeEnlaceDadosReceptora (int quadro []);
int* CamadaDeEnlaceReceptoraEnquadramento (int quadro []);
int* CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres (int quadro []);
int* CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes (int quadro []);
int* CamadaDeEnlaceTransmissoraControleDeErro (int quadro []);
int* CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (int quadro []);
int* CamadaEnlaceDadosTransmissoraControleDeErroCRC (int quadro []);
void CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar (int quadro []);
void CamadaEnlaceDadosReceptora (int quadro []);
int* CamadaDeEnlaceReceptoraControleDeErro (int quadro []);



#endif