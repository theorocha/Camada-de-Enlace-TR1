#include <iostream>
#include <string>
#include <bitset>
#include <algorithm> 
#include <vector> 
#include <sstream>
#include <cstring>
#include <math.h>
#include "CamadaEnlace.hpp"

using namespace std;

int TipoDeEnquadramento = 1;
int TipoDeControleDeErro = 1;
int TamanhoDaString = 0;
int TamanhoDoCRC = 0;
int GeradorCRC = 13;
string BitParidadeRecebido;
string BitParidadeEnviado;

int* CamadaEnlaceDadosTransmissora (int quadro []) {
  int* quadroEnquadrado;
  quadroEnquadrado = CamadaDeEnlaceDadosTransmissoraEnquadramento(quadro);

  quadroEnquadrado = CamadaDeEnlaceTransmissoraControleDeErro(quadroEnquadrado);

  CamadaFisicaTransmissora(quadroEnquadrado);
}

int* CamadaDeEnlaceDadosTransmissoraEnquadramento (int quadro []) {
  int tipoDeEnquadramento = TipoDeEnquadramento;
  int* quadroEnquadrado;

  switch (tipoDeEnquadramento)
  {
  case 0:
    quadroEnquadrado = 
    CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(quadro);
    break;

  case 1:
    quadroEnquadrado = 
    CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes(quadro);
    break;
  
  default:
    break;
  }

  return quadroEnquadrado;
}

int* CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres (int quadro []){
  int* fluxoBrutoDeBitsComContagemDeCaracteres;
  string stringContagemDeCaracteres;
  string stringDoContadorEmBits;

  //Obtem o tamanho do quadro
  int contador = 0;
  while (quadro[contador] == 0 || quadro[contador] == 1){
    contador++;
  }

  //Número de caracteres
  contador = contador/8;

  //Converte o número de caracteres em binario 
  stringDoContadorEmBits = bitset<8>(contador).to_string();
  stringContagemDeCaracteres = stringDoContadorEmBits;

  //Coloca o quadro em uma string
  int i = 0;
  while (quadro[i] == 0 || quadro[i] == 1){
    if (quadro[i] == 0){
      stringContagemDeCaracteres += "0";
    }
    else {
      stringContagemDeCaracteres += "1";
    }
    i++;
  }

  TamanhoDaString = (stringContagemDeCaracteres.length()/8);

  //Altera o valor e tamanho de quadro para suportar a quantidade nova de bits (2x mais)
  int* newArray = new int[stringContagemDeCaracteres.length()];
  quadro = newArray;

  //Coloca cada bit na lista de inteiros "quadro"
  for (int i = 0; i < stringContagemDeCaracteres.length(); i++){
    quadro[i] = stringContagemDeCaracteres[i] - '0';
  }
  
  fluxoBrutoDeBitsComContagemDeCaracteres = quadro;

  return fluxoBrutoDeBitsComContagemDeCaracteres;
}

int* CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes (int quadro []){
  int* fluxoBrutoDeBitsComContagemDeCaracteres;
  string stringInsercaoDeBytes;
  //Flag
  stringInsercaoDeBytes = "11111111";

  //Obtem o tamanho do quadro
  int contador = 0;
  while (quadro[contador] == 0 || quadro[contador] == 1){
    contador++;
  }
  
  //Número de caracteres
  contador = contador/8;

  //Coloca o quadro em uma string e adiciona a flag no inicio e fim de cada byte
  int i = 0;
  while (quadro[i] == 0 || quadro[i] == 1){
    if (quadro[i] == 0){
      stringInsercaoDeBytes += "0";
    }
    else {
      stringInsercaoDeBytes += "1";
    }
    i++;
    if (i % 8 == 0){
      contador--;
      if (contador == 0) {
        //Flag fim
        stringInsercaoDeBytes += "11111111";
      }
      else {
        //Flag fim
        stringInsercaoDeBytes += "11111111";
        //Flag inicio
        stringInsercaoDeBytes += "11111111";
      }
    }
  }

  TamanhoDaString = (stringInsercaoDeBytes.length()/8);

  //Altera o valor e tamanho de quadro para suportar a quantidade nova de bits (2x mais)
  int* newArray = new int[stringInsercaoDeBytes.length()];
  quadro = newArray;

  //Coloca cada bit na lista de inteiros "quadro"
  for (int i = 0; i < stringInsercaoDeBytes.length(); i++){
    quadro[i] = stringInsercaoDeBytes[i] - '0';
  }
  
  fluxoBrutoDeBitsComContagemDeCaracteres = quadro;

  return fluxoBrutoDeBitsComContagemDeCaracteres;
}

int* CamadaDeEnlaceDadosReceptora (int quadro []) {
  int* quadroDesenquadrado;
  quadroDesenquadrado = CamadaDeEnlaceReceptoraEnquadramento(quadro);

  return quadroDesenquadrado;
}

int* CamadaDeEnlaceReceptoraEnquadramento (int quadro []) {
  int tipoDeEnquadramento = TipoDeEnquadramento;
  int* quadroDesenquadrado;

  switch (tipoDeEnquadramento)
  {
  case 0:
    quadroDesenquadrado = 
    CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres(quadro);
    break;

  case 1:
    quadroDesenquadrado = 
    CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes(quadro);
    break;
  
  default:
    break;
  }

  return quadroDesenquadrado;
}

int* CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres (int quadro []) {
  int* fluxoBrutoDeBitsComContagemDeCaracteres;
  string stringContagemDeCaracteres;
  string stringContagemDeCaracteresFinal;

  //Obtem o primeiro byte
  int i = 0;
  int contagemDeQuadros = 0;
  while (i != 8){
    if (quadro[i] == 0){
      stringContagemDeCaracteres += "0";
    }
    else {
      stringContagemDeCaracteres += "1";
    }
    i++;
  }

  //Transforma o primeiro byte em inteiro
  contagemDeQuadros = stoi(stringContagemDeCaracteres, 0, 2);
  
  while (contagemDeQuadros != 0){
    if (quadro[i] == 0){
      stringContagemDeCaracteresFinal += "0";
    }
    else {
      stringContagemDeCaracteresFinal += "1";
    }

    i++;

    if (i%8 == 0){
    contagemDeQuadros--;
    }
  }

  if (TipoDeControleDeErro == 0){
    int u = 0;
    while (u != 8){
      if (quadro[i] == 0){
        BitParidadeRecebido += "0";
      }
      else {
        BitParidadeRecebido += "1";
      }
      i++;
      u++;
  }
  }

  //Altera o valor e tamanho de quadro para suportar a quantidade nova de bits (2x mais)
  int* newArray = new int[stringContagemDeCaracteresFinal.length()];
  quadro = newArray;

  //Coloca cada bit na lista de inteiros "quadro"
  for (int i = 0; i < stringContagemDeCaracteresFinal.length(); i++){
    quadro[i] = stringContagemDeCaracteresFinal[i] - '0';
  }
  
  fluxoBrutoDeBitsComContagemDeCaracteres = quadro;

  return fluxoBrutoDeBitsComContagemDeCaracteres;
}

int* CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes (int quadro []) {
  int* fluxoBrutoDeBitsComContagemDeCaracteres;
  string stringInsercaoDeBytes;
  string stringInsercaoDeBytesFinal;
  string flag = "11111111";
  string flag2 = "1111111111111111";
  bool inicio = false;
  bool fim = false;
  bool conectado = true;
  bool dadoLido = false;

  int i = 0;
  int contagemDeQuadros = 0;
  while (i != 8){
    if (quadro[i] == 0){
      stringInsercaoDeBytes += "0";
    }
    else {
      stringInsercaoDeBytes += "1";
    }
    i++;
  }

  inicio = true;

  stringInsercaoDeBytes = "";

  int contador = 0;

  while (conectado){
    if (quadro[i] == 0){
      stringInsercaoDeBytes += "0";
    }
    else {
      stringInsercaoDeBytes += "1";
    }
    i++;

    if (i % 8 == 0){
      if (contador < 2){ 
        contador++;
      }

      if (contador == 2 && stringInsercaoDeBytes.length() == 16) {
        if (stringInsercaoDeBytes == flag2) {
          dadoLido = false;
        }
        else {
          conectado = false;
        }
        stringInsercaoDeBytes = "";
        contador = 0;
      }
      else if (contador == 1 ) {
        if (!dadoLido && stringInsercaoDeBytes != flag){
          stringInsercaoDeBytesFinal += stringInsercaoDeBytes;
          dadoLido = true;
        }
        else {     
          conectado = false;
        }
        stringInsercaoDeBytes = "";
      }
    }
  }

  if (TipoDeControleDeErro == 0){
    int u = 0;
    i = i - 8;
    while (u != 8){
      if (quadro[i] == 0){
        BitParidadeRecebido += "0";
      }
      else {
        BitParidadeRecebido += "1";
      }
      i++;
      u++;
  }
  }

  //Altera o valor e tamanho de quadro para suportar a quantidade nova de bits (2x mais)
  int* newArray = new int[stringInsercaoDeBytesFinal.length()];
  quadro = newArray;

  //Coloca cada bit na lista de inteiros "quadro"
  for (int i = 0; i < stringInsercaoDeBytesFinal.length(); i++){
    quadro[i] = stringInsercaoDeBytesFinal[i] - '0';
  }
  
  fluxoBrutoDeBitsComContagemDeCaracteres = quadro;

  return fluxoBrutoDeBitsComContagemDeCaracteres;
}

int* CamadaDeEnlaceTransmissoraControleDeErro (int quadro []){
  int tipoDeControleDeErro = TipoDeControleDeErro;
  int* quadroComErro;

  switch (tipoDeControleDeErro)
  {
  case 0:
    quadroComErro = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
    break;
  case 1:
    quadroComErro = CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
    break;
  default:
    break;
  }

  return quadroComErro;
}

int* CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (int quadro []){
  int i = 0;
  int u = 0;
  int contadorDe1s = 0;
  string bitParidade;
  int* fluxoBrutoDeBitsComContagemDeCaracteres;
  string fluxoAntigo;
  string fluxoComControleDeErro;

  while (u != 8) {
    while (i <= TamanhoDaString*8 - 1){
      if (quadro[i] == 1){
        contadorDe1s += 1;
      }
      i += 8;
    }
    if (contadorDe1s % 2 == 0 ){
      bitParidade += "0";
    }
    else {
      bitParidade += "1";
    }
    u++;
    i = u;
  }

  i = 0;
  while (i <= TamanhoDaString*8 - 1){
    if (quadro[i] == 0){
      fluxoAntigo += "0";
    }
    else {
      fluxoAntigo += "1";
    }
    i++;
  }

  BitParidadeEnviado = bitParidade;

  fluxoComControleDeErro = fluxoAntigo + bitParidade;
  //Altera o valor e tamanho de quadro para suportar a quantidade nova de bits (2x mais)
  int* newArray = new int[fluxoComControleDeErro.length()];
  quadro = newArray;

  for (int i = 0; i < fluxoComControleDeErro.length(); i++){
    quadro[i] = fluxoComControleDeErro[i] - '0';
  }
  
  fluxoBrutoDeBitsComContagemDeCaracteres = quadro;

  return fluxoBrutoDeBitsComContagemDeCaracteres;
}

int* CamadaEnlaceDadosTransmissoraControleDeErroCRC (int quadro []){
  int* fluxoBrutoDeBitsComContagemDeCaracteres;
  string stringControleDeErro;
  string stringControleDeErroFinal;
  int crc = 0;
  int gerador = GeradorCRC; //1101

  //Atribui 01 ao fluxo de bits, caso seja o bit 0, e 10, caso seja o bit 1.
  int i = 0;
  while (i <= TamanhoDaString*8 - 1){
    if (quadro[i] == 0){
      stringControleDeErro += "0";
    }
    else {
      stringControleDeErro += "1";
    }
    i++;

    if (i % 8 == 0){
      crc += stoi(stringControleDeErro, 0, 2);
      stringControleDeErroFinal += stringControleDeErro;
      stringControleDeErro = "";
    }
  }

  crc = crc % gerador;
  
  string crcInBinary = bitset<8>(crc).to_string();

  TamanhoDaString += crcInBinary.length();

  stringControleDeErroFinal += crcInBinary;

  //Altera o valor e tamanho de quadro para suportar a quantidade nova de bits (2x mais)
  int* newArray = new int[stringControleDeErroFinal.length()];
  quadro = newArray;

  for (int i = 0; i < stringControleDeErroFinal.length(); i++){
    quadro[i] = stringControleDeErroFinal[i] - '0';
  }
  
  fluxoBrutoDeBitsComContagemDeCaracteres = quadro;

  return fluxoBrutoDeBitsComContagemDeCaracteres;
}

void CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar (int quadro []) {
  if (BitParidadeEnviado != BitParidadeRecebido) {
    cout << endl << "Houve Erro na transmissao! (Bit de paridade)" << endl;
  }
  else {
    cout << endl << "Sem Erros na transmissao! (Bit de paridade)" << endl;
  }
}

void CamadaEnlaceDadosReceptoraControleDeErroCRC (int quadro []) {
  int* fluxoBrutoDeBitsComContagemDeCaracteres;
  string stringControleDeErro;
  string stringControleDeErroFinal;
  int crc = 0;
  int gerador = GeradorCRC; //1101

  //Atribui 01 ao fluxo de bits, caso seja o bit 0, e 10, caso seja o bit 1.
  int i = 0;
  while (i <= TamanhoDaString*8 - 1){
    if (quadro[i] == 0){
      stringControleDeErro += "0";
    }
    else {
      stringControleDeErro += "1";
    }
    i++;

    if (i % 8 == 0){
      crc += stoi(stringControleDeErro, 0, 2);
      stringControleDeErroFinal += stringControleDeErro;
      stringControleDeErro = "";
    }
  }

  crc = crc % gerador;
  
  if (crc != 0){
    cout << endl << "Houve Erro na transmissao! (CRC)" << endl;
  }
  else {
    cout << endl << "Sem Erros na transmissao! (CRC)" << endl;
  }
}

int* CamadaDeEnlaceReceptoraControleDeErro (int quadro []){
  int tipoDeControleDeErro = TipoDeControleDeErro;
  int* quadroComErro;

  switch (tipoDeControleDeErro)
  {
  case 0:
    CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(quadro);
    break;
  case 1:
    CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
    break;
  default:
    break;
  }
}

void CamadaEnlaceDadosReceptora (int quadro []) {
  int* fluxoDeBits;
  fluxoDeBits = CamadaDeEnlaceReceptoraEnquadramento(quadro);

  CamadaDeEnlaceReceptoraControleDeErro(fluxoDeBits);

  CamadaDeAplicacaoReceptora(fluxoDeBits);
}