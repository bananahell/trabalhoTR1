#include "camadaFisica.h"

void CamadaFisicaTransmissora(vector<int> quadro) {
  int tipoDeCodificacao = 0;
  vector<int> fluxoBrutoDeBits;  // trabalhar com bits!!!!
  switch (tipoDeCodificacao) {
    case CODIFICACAO_BINARIA:
      fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
      break;
    case CODIFICACAO_MANCHESTER:
      fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
      break;
    case CODIFICACAO_BIPOLAR:
      fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
      break;
    default:
      cout << "Tipo de codificação não reconhecido..." << endl;
      break;
  }
  MeioDeComunicacao(fluxoBrutoDeBits);
}

void MeioDeComunicacao(vector<int> fluxoBrutoDeBits) {
  vector<int> fluxoBrutoDeBitsPontoA;  // sempre usando bits, não bytes!!!!
  vector<int> fluxoBrutoDeBitsPontoB;
  fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
  for (unsigned i = 0; i < fluxoBrutoDeBitsPontoA.size(); i++) {
    fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA.at(i));
  }
  CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}

void CamadaFisicaReceptora(vector<int> fluxoBrutoDeBits) {
  int tipoDeDecodificacao = 0;
  vector<int> quadro;  // biiiiiits!!!!
  switch (tipoDeDecodificacao) {
    case CODIFICACAO_BINARIA:
      quadro = CamadaFisicaReceptoraCodificacaoBinaria(fluxoBrutoDeBits);
      break;
    case CODIFICACAO_MANCHESTER:
      quadro = CamadaFisicaReceptoraCodificacaoManchester(fluxoBrutoDeBits);
      break;
    case CODIFICACAO_BIPOLAR:
      quadro = CamadaFisicaReceptoraCodificacaoBipolar(fluxoBrutoDeBits);
      break;
    default:
      cout << "Tipo de decodificação não reconhecido..." << endl;
      break;
  }
  CamadaDeAplicacaoReceptora(quadro);
}

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro) {
  /*
  TODO
  Isso tá COMPLETAMENTE ERRADO.... só to colocando pra fazer alguma coisa rodar!
  */
  return quadro;
}

vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro) {}

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro) {}

vector<int> CamadaFisicaReceptoraCodificacaoBinaria(
    vector<int> fluxoBrutoDeBits) {
  /*
  TODO
  Isso tá COMPLETAMENTE ERRADO.... só to colocando pra fazer alguma coisa rodar!
  */
  return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaReceptoraCodificacaoManchester(
    vector<int> fluxoBrutoDeBits) {}

vector<int> CamadaFisicaReceptoraCodificacaoBipolar(
    vector<int> fluxoBrutoDeBits) {}
