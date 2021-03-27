#include "camadaFisica.h"

void CamadaFisicaTransmissora(int* quadro) {
  int tipoDeCodificacao = 0;
  int* fluxoBrutoDeBits;  // trabalhar com bits!!!!
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

void MeioDeComunicacao(int* fluxoBrutoDeBits) {
  int* fluxoBrutoDeBitsPontoA;  // sempre usando bits, não bytes!!!!
  int* fluxoBrutoDeBitsPontoB;
  fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
  while (fluxoBrutoDeBitsPontoB.length != fluxoBrutoDeBitsPontoA) {
    fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA;  // bits, não bytes!!!!
  }
  CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}

void CamadaFisicaReceptora(int* quadro) {
  int tipoDeDecodificacao = 0;
  int* fluxoBrutoDeBits;  // biiiiiits!!!!
  string mensagem = "teste";
  switch (tipoDeDecodificacao) {
    case CODIFICACAO_BINARIA:
      fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBinaria(quadro);
      break;
    case CODIFICACAO_MANCHESTER:
      fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoManchester(quadro);
      break;
    case CODIFICACAO_BIPOLAR:
      fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBipolar(quadro);
      break;
    default:
      cout << "Tipo de decodificação não reconhecido..." << endl;
      break;
  }
  CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}

int* CamadaFisicaTransmissoraCodificacaoBinaria(int* quadro) {}

int* CamadaFisicaTransmissoraCodificacaoManchester(int* quadro) {}

int* CamadaFisicaTransmissoraCodificacaoBipolar(int* quadro) {}

int* CamadaFisicaReceptoraCodificacaoBinaria(int* quadro) {}

int* CamadaFisicaReceptoraCodificacaoManchester(int* quadro) {}

int* CamadaFisicaReceptoraCodificacaoBipolar(int* quadro) {}
