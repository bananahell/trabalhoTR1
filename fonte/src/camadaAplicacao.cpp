#include "camadaAplicacao.h"

void AplicacaoTransmissora() {
  string mensagem;
  cout << "Digite uma mensagem: " << endl;
  cin >> mensagem;
  CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(string mensagem) {
  // int quadro [] = mensagem;
  int quadro[3] = {1, 0, 1};
  CamadaFisicaTransmissora(quadro);
}

void CamadaDeAplicacaoReceptora(int* quadro) {
  // string mensagem = quadro [];
  string mensagem = "huebr";
  AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(string mensagem) {
  cout << "A mensagem recebida foi: " << mensagem << endl;
}
