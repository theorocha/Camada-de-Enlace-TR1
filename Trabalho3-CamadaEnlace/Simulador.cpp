#include <iostream>
#include <string>
#include <bitset>
#include <algorithm> 
#include <vector> 
#include <sstream>
#include <cstring>
#include <math.h>
#include <future>
#include "CamadaFisica.cpp"

using namespace std;

string buffer;

int main (void) {
  int tipoDeCodificacao = 1;
  int controleDeErro = 1;
  int porcentagemDeErro = 0;

  cout << endl;

  cout << "Escolha a codificacao: " << endl << endl;
  cout << "1 - Codificacao Binaria" << endl;
  cout << "2 - Codificacao Manchester" << endl;
  cout << "3 - Codificacao Bipolar" << endl << endl;
  cin >> tipoDeCodificacao;

  cout << endl;

  cout << "Escolha o controle de erro: " << endl << endl;
  cout << "1 - Bit de paridade" << endl;
  cout << "2 - CRC" << endl;
  cin >> controleDeErro;

  cout << endl;

  cout << "Escolha a porcentagem de erro (0 a 99): " << endl;
  cin >> porcentagemDeErro;

  cout << endl;

  main2(tipoDeCodificacao - 1, controleDeErro - 1, porcentagemDeErro);

  return 0;
}