#include "camadaFisica.h"

void CamadaFisicaTransmissora(const vector<int>& quadro, int codificacaoFisica,
                              int tipoDeEnquadramento) {
  vector<int> fluxoBrutoDeBits;
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
  MeioDeComunicacao(fluxoBrutoDeBits, codificacaoFisica, tipoDeEnquadramento);
}

void MeioDeComunicacao(const vector<int>& fluxoBrutoDeBits,
                       int codificacaoFisica, int tipoDeEnquadramento) {
  vector<int> fluxoBrutoDeBitsPontoA;
  vector<int> fluxoBrutoDeBitsPontoB;
  fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
  for (unsigned i = 0; i < fluxoBrutoDeBitsPontoA.size(); i++) {
    fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA.at(i));
  }
  CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB, codificacaoFisica,
                        tipoDeEnquadramento);
}

void CamadaFisicaReceptora(const vector<int>& fluxoBrutoDeBits,
                           int codificacaoFisica, int tipoDeEnquadramento) {
  vector<int> quadro;
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
  CamadaEnlaceReceptora(quadro, tipoDeEnquadramento);
}

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro) {
  cout << endl << "Codificação Binária:";
  for (unsigned i = 0; i < quadro.size(); i++) {
    if (i % 8 == 0) {  // Para cada caracter (que tem 8 bits cada)...
      cout << endl;
    }
    cout << quadro.at(i);
  }
  cout << endl;
  return quadro;
}

vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro) {
  vector<int> manchesterBits;
  cout << endl << "Codificação Manchester:";
  for (unsigned i = 0; i < quadro.size(); i++) {
    manchesterBits.push_back(quadro.at(i) ^ CLOCK_MANCHESTER.at(0));
    manchesterBits.push_back(quadro.at(i) ^ CLOCK_MANCHESTER.at(1));
    if (i % 8 == 0) {  // Para cada caracter (que tem 8 bits cada)...
      cout << endl;
    }
    cout << (quadro.at(i) ^ CLOCK_MANCHESTER.at(0));
    cout << (quadro.at(i) ^ CLOCK_MANCHESTER.at(1));
  }  // CLOCK_MANCHESTER = [0,1] e só existe para padronizar a codificação
  cout << endl;
  return manchesterBits;
}

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro) {
  bool umNegativo = false;  // Meu bipolar começa com 1 positivo
  cout << endl << "Codificação Bipolar:";
  for (unsigned i = 0; i < quadro.size(); i++) {
    if (i % 8 == 0) {  // Para cada caracter (que tem 8 bits cada)...
      cout << endl;
    }
    if (quadro.at(i) == 1) {
      if (umNegativo) {
        quadro.at(i) = -1;
        cout << "-1";
      } else {
        cout << " 1";
      }
      umNegativo = !umNegativo;
    } else {
      cout << " 0";
    }
    cout << " ";
  }
  cout << endl;
  return quadro;
}

vector<int> CamadaFisicaReceptoraCodificacaoBinaria(
    vector<int> fluxoBrutoDeBits) {
  return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaReceptoraCodificacaoManchester(
    vector<int> fluxoBrutoDeBits) {
  vector<int> bitsDecodificados;
  for (unsigned i = 0; i < fluxoBrutoDeBits.size(); i += 2) {  // Sinal original
    bitsDecodificados.push_back(fluxoBrutoDeBits.at(i));  // está na xor com 0
  }
  return bitsDecodificados;
}

vector<int> CamadaFisicaReceptoraCodificacaoBipolar(
    vector<int> fluxoBrutoDeBits) {
  for (unsigned i = 0; i < fluxoBrutoDeBits.size(); i++) {  // Só faz módulo
    fluxoBrutoDeBits.at(i) = fabs(fluxoBrutoDeBits.at(i));  // de tudo
  }
  return fluxoBrutoDeBits;
}
