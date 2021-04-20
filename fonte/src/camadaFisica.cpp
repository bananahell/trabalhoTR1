#include "camadaFisica.h"

void CamadaFisicaTransmissora(const vector<int>& quadro,
                              int codificacaoFisica, int tipoDeEnquadramento) {
  vector<int> fluxoBrutoDeBits;
  vector<int> bits = TransformaASCIIEmBits(quadro);
  switch (codificacaoFisica) {
    case CODIFICACAO_BINARIA:
      fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(bits);
      break;
    case CODIFICACAO_MANCHESTER:
      fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(bits);
      break;
    case CODIFICACAO_BIPOLAR:
      fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(bits);
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
  CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB, codificacaoFisica, tipoDeEnquadramento);
}

void CamadaFisicaReceptora(const vector<int>& fluxoBrutoDeBits,
                           int codificacaoFisica, int tipoDeEnquadramento) {
  vector<int> quadro;
  vector<int> quadroEnquadrado;
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
  quadroEnquadrado = TransformaBitsEmASCII(quadro);
  CamadaEnlaceReceptora(quadroEnquadrado, tipoDeEnquadramento);
  //CamadaDeAplicacaoReceptora(quadro);
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

vector<int> TransformaASCIIEmBits(vector<int> quadro) {
  vector<int> bits;
  for (unsigned i = 0; i < quadro.size(); i++) {  // Pega mensagem inteira
    vector<int> tempQuadro;
    int charBinario = quadro.at(i);
    for (unsigned j = 0; j < ASCII_MAX_BITS; j++) {  // 8 bits por letra
      if (charBinario % 2 == 0) {
        tempQuadro.push_back(0);
      } else {
        tempQuadro.push_back(1);
      }
      charBinario = charBinario >> 1;
    }
    for (int k = ASCII_MAX_BITS - 1; k >= 0; k--) {
      bits.push_back(tempQuadro.at(k));
    }
  }
  return bits;
}

vector<int> TransformaBitsEmASCII(vector<int> bits) {
  vector<int> quadro;
  int intChar = 0;
  for (unsigned i = 0; i < bits.size(); i++) {  // Pega mensagem inteira
    if (i != 0 && i % ASCII_MAX_BITS == 0) {
      quadro.push_back(intChar);  // Adiciona cada letra
      intChar = 0;
    }
    intChar = intChar << 1;   // Forma cada letra
    intChar += bits.at(i);  // adicionando o int e shiftando para esquerda
  }
  quadro.push_back(intChar);  // Adiciona última letra (ficou pra trás)
  return quadro;
}