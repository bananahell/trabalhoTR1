#include "camadaAplicacao.h"

#include <iostream>

using namespace std;

void AplicacaoTransmissora() {
  string mensagem;
  cout << "Digite uma mensagem: " << endl;
  cin >> mensagem;
  CamadaDeAplicacaoTransmissora(mensagem);
}
