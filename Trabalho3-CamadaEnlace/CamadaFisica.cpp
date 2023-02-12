#include <iostream>
#include <string>
#include <bitset>
#include <algorithm> 
#include <vector> 
#include <sstream>
#include <cstring>
#include <time.h>
#include <math.h>
#include <ctime>
#include "CamadaFisica.hpp"
#include "CamadaEnlace.cpp"

using namespace std;

int TipoDeCodificacao = 0;
int PorcentagemDeErros = 0; //Erros de 0 a 100

int main2 (int tipoDeCodificacao, int controleDeErro, int porcentagemDeErros) {
  TipoDeCodificacao = tipoDeCodificacao;
  PorcentagemDeErros = porcentagemDeErros;
  TipoDeControleDeErro = controleDeErro;
  AplicacaoTransmissora();

  return 0;
}

void AplicacaoTransmissora (void) {
  string mensagem;
  cout << "Digite uma mensagem" << endl;
  cin >> mensagem;

  CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora (string mensagem){
  string stringDaMensagemEmBits = StringToBits(mensagem);

  int quadro [stringDaMensagemEmBits.length()];

  //Coloca cada bit na lista de inteiros "quadro"
  for (int i = 0; i < stringDaMensagemEmBits.length(); i++){
    quadro[i] = stringDaMensagemEmBits[i] - '0'; //Subtrai por '0' para encontrar o equivalente da string em inteiro Ex.: '0' - '0' = 0
  }

  //CamadaFisicaTransmissora(quadro);
  CamadaEnlaceDadosTransmissora(quadro);
}

void CamadaFisicaTransmissora (int quadro[]){
  int tipoDeCodificacao = TipoDeCodificacao;
  int* fluxoBrutoDeBits;

  switch (tipoDeCodificacao)
  {
  case 0:
    fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
    break;
  case 1:
    fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
    break;
  case 2:
    fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
    break;
  default:
    break;
  }

  MeioDeComunicacao(fluxoBrutoDeBits);
}

int* CamadaFisicaTransmissoraCodificacaoBinaria (int quadro []) {
  int* fluxoBrutoDeBits;
  fluxoBrutoDeBits = quadro;

  return fluxoBrutoDeBits;
}

int* CamadaFisicaTransmissoraCodificacaoManchester (int quadro []) {
  int* fluxoBrutoDeBitsComClock;
  string stringDoFluxoBrutoDeBitsComClock;

  //Atribui 01 ao fluxo de bits, caso seja o bit 0, e 10, caso seja o bit 1.
  int i = 0;
  while (quadro[i] == 0 || quadro[i] == 1){
    if (quadro[i] == 0){
      stringDoFluxoBrutoDeBitsComClock += "01";
    }
    else {
      stringDoFluxoBrutoDeBitsComClock += "10";
    }
    i++;
  }

  //Altera o valor e tamanho de quadro para suportar a quantidade nova de bits (2x mais)
  int* newArray = new int[stringDoFluxoBrutoDeBitsComClock.length()];
  quadro = newArray;

  //Coloca cada bit na lista de inteiros "quadro"
  for (int i = 0; i < stringDoFluxoBrutoDeBitsComClock.length(); i++){
    quadro[i] = stringDoFluxoBrutoDeBitsComClock[i] - '0';
  }
  
  fluxoBrutoDeBitsComClock = quadro;

  return fluxoBrutoDeBitsComClock;
}

int* CamadaFisicaTransmissoraCodificacaoBipolar (int quadro []) {
  int* fluxoBrutoDeBitsBipolar;
  string stringFluxoBrutoDeBitsBipolar;
  bool anteriorFoi1Positivo = false;

  //Atribui 01 ao fluxo de bits, caso seja o bit 0, e alterna entre 00 e 01, caso seja 1.
  int i = 0;
  while (quadro[i] == 0 || quadro[i] == 1){
    if (quadro[i] == 0){
      stringFluxoBrutoDeBitsBipolar += "01";
    }
    else {
      if (anteriorFoi1Positivo){
        stringFluxoBrutoDeBitsBipolar += "00";
        anteriorFoi1Positivo = false;
      }
      else {
        stringFluxoBrutoDeBitsBipolar += "10";
        anteriorFoi1Positivo = true;
      }
    }
    i += 1;
  }

  //Altera o valor e tamanho de quadro para suportar a quantidade nova de bits (2x mais)
  int* newArray = new int[stringFluxoBrutoDeBitsBipolar.length()];
  quadro = newArray;

  //Coloca cada bit na lista de inteiros "quadro"
  for (int i = 0; i < stringFluxoBrutoDeBitsBipolar.length(); i++){
    quadro[i] = stringFluxoBrutoDeBitsBipolar[i] - '0';
  }
  
  fluxoBrutoDeBitsBipolar = quadro;

  return fluxoBrutoDeBitsBipolar;
}

void MeioDeComunicacao (int fluxoBrutoDeBitsPontoA []){
  int* fluxoBrutoDeBitsPontoB;
  string stringFluxoBrutoDeBitsPontoB;
  int porcentagemDeErros = PorcentagemDeErros;

  //Atribui 01 ao fluxo de bits, caso seja o bit 0, e alterna entre 00 e 01, caso seja 1.
  //Transfere os bits
  int i = 0;
  while (fluxoBrutoDeBitsPontoA[i] == 0 || fluxoBrutoDeBitsPontoA[i] == 1){
  srand(time(0));
    if (fluxoBrutoDeBitsPontoA[i] == 0){
      if (rand() % 100 < porcentagemDeErros) {
        stringFluxoBrutoDeBitsPontoB += "1";
      }
      else {
        stringFluxoBrutoDeBitsPontoB += "0";
      }
    }
    else {
      if (rand() % 100 < porcentagemDeErros) {
        stringFluxoBrutoDeBitsPontoB += "0";
      }
      else {
        stringFluxoBrutoDeBitsPontoB += "1";
      }
    }
    i++;
  }

  //Define o tamanho da array do fluxo
  int* newArray = new int[stringFluxoBrutoDeBitsPontoB.length()];
  fluxoBrutoDeBitsPontoB = newArray;

  //Coloca cada bit na lista de inteiros "quadro"
  for (int i = 0; i < stringFluxoBrutoDeBitsPontoB.length(); i++){
    fluxoBrutoDeBitsPontoB[i] = stringFluxoBrutoDeBitsPontoB[i] - '0';
  }

  CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
} 

void CamadaFisicaReceptora (int quadro []){
  int tipoDeCodificacao = TipoDeCodificacao;
  int* fluxoBrutoDeBits;

  switch (tipoDeCodificacao)
  {
  case 0:
    fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBinaria(quadro);
    break;
  case 1:
    fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoManchester(quadro);
    break;
  case 2:
    fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBipolar(quadro);
    break;
  default:
    break;
  }

  CamadaEnlaceDadosReceptora(fluxoBrutoDeBits);
}

int* CamadaFisicaReceptoraCodificacaoBinaria (int quadro []) {
  int* fluxoBrutoDeBits;
  fluxoBrutoDeBits = quadro;

  return fluxoBrutoDeBits;
}

int* CamadaFisicaReceptoraCodificacaoManchester (int quadro []) {
  int* fluxoBrutoDeBits;
  string stringFluxoBrutoDeBits;

  //Atribui 1 ao fluxo de bits, caso seja o bit 01, e 1, caso contrário.
  int i = 0;
  while (quadro[i] == 0 || quadro[i] == 1){
    if (quadro[i] == 0 && quadro[i+1] == 1){
      stringFluxoBrutoDeBits += "0";
    }
    else {
      stringFluxoBrutoDeBits += "1";
    }
    i += 2;
  }

  //Altera o valor e tamanho de quadro para suportar a quantidade nova de bits (2x mais)
  int* newArray = new int[stringFluxoBrutoDeBits.length()];
  quadro = newArray;

  //Coloca cada bit na lista de inteiros "quadro"
  for (int i = 0; i < stringFluxoBrutoDeBits.length(); i++){
    quadro[i] = stringFluxoBrutoDeBits[i] - '0';
  }
  
  fluxoBrutoDeBits = quadro;

  return fluxoBrutoDeBits;
}

int* CamadaFisicaReceptoraCodificacaoBipolar (int quadro []) {
  int* fluxoBrutoDeBits;
  string stringFluxoBrutoDeBits;
  
  int i = 0;
  while (quadro[i] == 0 || quadro[i] == 1){
    if (quadro[i] == 0 && quadro[i+1] == 1){
      stringFluxoBrutoDeBits += "0";
    }
    else {
      stringFluxoBrutoDeBits += "1";
    }
    i += 2;
  }

  //Altera o valor e tamanho de quadro para suportar a quantidade nova de bits (2x mais)
  int* newArray = new int[stringFluxoBrutoDeBits.length()];
  quadro = newArray;

  //Coloca cada bit na lista de inteiros "quadro"
  for (int i = 0; i < stringFluxoBrutoDeBits.length(); i++){
    quadro[i] = stringFluxoBrutoDeBits[i] - '0';
  }
  
  fluxoBrutoDeBits = quadro;

  return fluxoBrutoDeBits;
}

void CamadaDeAplicacaoReceptora (int quadro []){
  string mensagem = BitToString(quadro);

  AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora (string mensagem){
  cout << "A mensagem recebida foi: " << mensagem << endl;
}

string StringToBits (string mensagem)
{
    int mensagemLenght = mensagem.length();
    string stringMensagemEmBits = "";
 
    for (int i = 0; i < mensagemLenght; i++)
    {
        string stringLetra = "";

        // Converte cada caracter pelo seu ASCII
        int asciiDaLetra = int(mensagem[i]);
 
        // Converte cada ASCII para binário
        while (asciiDaLetra > 0)
        {
            (asciiDaLetra % 2)? stringLetra.push_back('1') :
                       stringLetra.push_back('0');
            asciiDaLetra /= 2;
        }

        //Se o tamanho for menor que 8, é completado com zeros.
        while (stringLetra.length() < 8) {
          stringLetra.push_back('0');
        }

        //A string é invertida para ficar no sentido correto
        reverse(stringLetra.begin(), stringLetra.end());

        stringMensagemEmBits += stringLetra;
    }

    return stringMensagemEmBits;
}

string BitToString(int quadro[]){
  string stringMensagem;
  string stringMensagemEmBits;
	int asciiDaLetra = 0;
  int contador = 0;
  char letra;

  //Converte a lista de inteiros 'quadro' para uma string de bits
  int i = 0;
  while (quadro[i] == 0 || quadro[i] == 1){
    contador += 1;
    if (quadro[i] == 0 ){
      stringMensagemEmBits += "0";
    }
    else {
      stringMensagemEmBits += "1";
    }

    //Quando tiver 8 bits acumulados, é feito a conversão para inteiro (ASCII) e caracter
    if (contador == 8){
      //Converte de bits para inteiro
      asciiDaLetra = stoi(stringMensagemEmBits, 0, 2);

      //Converte o inteiro (ASCII) para caracter
      letra = char(asciiDaLetra);

      stringMensagem += letra;

      contador = 0;
      stringMensagemEmBits = "";
    } 
    i++;
  }

  return stringMensagem;
}
