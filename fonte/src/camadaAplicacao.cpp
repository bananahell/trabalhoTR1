#include "camadaAplicacao.h"

void AplicacaoTransmissora() {
  string mensagem;
  int codificacaoFisica = 0;
  cout << "Digite uma mensagem: " << endl;
  getline(cin, mensagem);
  cout << "Selecione um modo de codificação:" << endl
       << "0: Codificação Binária" << endl
       << "1: Codificação Manchester" << endl
       << "2: Codificação Bipolar" << endl;
  cin >> codificacaoFisica;
  CamadaDeAplicacaoTransmissora(mensagem, codificacaoFisica);
}

void CamadaDeAplicacaoTransmissora(string mensagem, int codificacaoFisica) {
  // int quadro [] = mensagem;
  vector<int> quadro = TransformaStringEmASCII(mensagem);
  CamadaFisicaTransmissora(quadro, codificacaoFisica);
}

vector<int> TransformaStringEmASCII(string mensagem) {
  vector<int> quadro;
  for (unsigned i = 0; i < mensagem.size(); i++) {
    vector<int> tempQuadro;
    int charBinario = int(mensagem.at(i));
    for (unsigned j = 0; j < ASCII_MAX_BITS; j++) {
      if (charBinario % 2 == 0) {
        tempQuadro.push_back(0);
      } else {
        tempQuadro.push_back(1);
      }
      charBinario = charBinario >> 1;
    }
    for (int k = ASCII_MAX_BITS - 1; k >= 0; k--) {
      quadro.push_back(tempQuadro.at(k));
    }
  }
  return quadro;
}

void CamadaDeAplicacaoReceptora(vector<int> quadro) {
  // string mensagem = quadro [];
  string mensagem = TransformaASCIIEmString(quadro);
  AplicacaoReceptora(mensagem);
}

string TransformaASCIIEmString(vector<int> quadro) {
  string mensagem = "";
  int intChar = 0;
  for (unsigned i = 0; i < quadro.size(); i++) {
    if (i != 0 && i % ASCII_MAX_BITS == 0) {
      mensagem.append(1, char(intChar));
      intChar = 0;
    }
    intChar = intChar << 1;
    intChar += quadro.at(i);
  }
  mensagem.append(1, char(intChar));
  return mensagem;
}

void AplicacaoReceptora(string mensagem) {
  cout << "A mensagem recebida foi: " << mensagem << endl;
}
