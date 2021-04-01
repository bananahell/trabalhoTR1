#include "camadaFisica.h"

void CamadaFisicaTransmissora(const vector<int>& quadro,
                              int codificacaoFisica) {
  vector<int> fluxoBrutoDeBits;  // trabalhar com bits!!!!
  switch (codificacaoFisica) {
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
  MeioDeComunicacao(fluxoBrutoDeBits, codificacaoFisica);
}

void MeioDeComunicacao(const vector<int>& fluxoBrutoDeBits,
                       int codificacaoFisica) {
  vector<int> fluxoBrutoDeBitsPontoA;  // sempre usando bits, não bytes!!!!
  vector<int> fluxoBrutoDeBitsPontoB;
  fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
  for (unsigned i = 0; i < fluxoBrutoDeBitsPontoA.size(); i++) {
    fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA.at(i));
  }
  CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB, codificacaoFisica);
}

void CamadaFisicaReceptora(const vector<int>& fluxoBrutoDeBits,
                           int codificacaoFisica) {
  vector<int> quadro;  // biiiiiits!!!!
  switch (codificacaoFisica) {
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
  return quadro;
}

vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro) {
  vector<int> manchesterBits;
  for (unsigned i = 0; i < quadro.size(); i++) {
    manchesterBits.push_back(quadro.at(i) ^ CLOCK_MANCHESTER.at(0));
    manchesterBits.push_back(quadro.at(i) ^ CLOCK_MANCHESTER.at(1));
  }
  return manchesterBits;
}

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro) {
  int unsAchados = 0;
  for (unsigned i = 0; i < quadro.size(); i++) {
    if (quadro.at(i) == 1) {
      if (unsAchados % 2 == 1) {
        quadro.at(i) = -1;
      }
      unsAchados++;
    }
  }
  return quadro;
}

vector<int> CamadaFisicaReceptoraCodificacaoBinaria(
    vector<int> fluxoBrutoDeBits) {
  return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaReceptoraCodificacaoManchester(
    vector<int> fluxoBrutoDeBits) {
  vector<int> bitsDecodificados;
  for (unsigned i = 0; i < fluxoBrutoDeBits.size(); i += 2) {
    bitsDecodificados.push_back(fluxoBrutoDeBits.at(i));
  }
  return bitsDecodificados;
}

vector<int> CamadaFisicaReceptoraCodificacaoBipolar(
    vector<int> fluxoBrutoDeBits) {
  for (unsigned i = 0; i < fluxoBrutoDeBits.size(); i++) {
    fluxoBrutoDeBits.at(i) = fabs(fluxoBrutoDeBits.at(i));
  }
  return fluxoBrutoDeBits;
}
