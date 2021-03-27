#include "camadaFisica.h"

void CamadaDeAplicacaoTransmissora(string mensagem) {
  string quadro = mensagem;
  CamadaFisicaTransmissora(quadro);
}

void CamadaFisicaTransmissora(string quadro) {
  cout << "Quadro = " << quadro << endl;
}
