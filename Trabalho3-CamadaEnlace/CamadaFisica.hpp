#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void AplicacaoTransmissora (void);
void CamadaDeAplicacaoTransmissora (string mensagem);
void CamadaFisicaTransmissora (int quadro[]);
void MeioDeComunicacao (int fluxoBrutoDeBits []);
int* CamadaFisicaTransmissoraCodificacaoBinaria (int quadro []);
int* CamadaFisicaTransmissoraCodificacaoManchester (int quadro []);
int* CamadaFisicaTransmissoraCodificacaoBipolar (int quadro []);
void CamadaDeAplicacaoReceptora (int quadro []);
void CamadaFisicaReceptora (int quadro[]);
int* CamadaFisicaReceptoraCodificacaoBinaria (int quadro []);
int* CamadaFisicaReceptoraCodificacaoManchester (int quadro []);
int* CamadaFisicaReceptoraCodificacaoBipolar (int quadro []);


void AplicacaoReceptora (string mensagem);

//funções adicionais
string StringToBits (string message);
string BitToString(int quadro []);

#endif