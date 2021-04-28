#include "camadaEnlace.h"

void CamadaEnlaceTransmissora(const vector<int>& quadro, int codificacaoFisica,
                              int tipoDeEnquadramento) {
  vector<int> quadroEnquadrado =
      CamadaEnlaceTransmissoraEnquadramento(quadro, tipoDeEnquadramento);
  // CamadaEnlaceTransmissoraControleDeErro(quadroEnquadrado);
  CamadaFisicaTransmissora(quadroEnquadrado, codificacaoFisica,
                           tipoDeEnquadramento);
}

vector<int> CamadaEnlaceTransmissoraEnquadramento(const vector<int>& quadro,
                                                  int tipoDeEnquadramento) {
  vector<int> quadroEnquadrado;
  switch (tipoDeEnquadramento) {
    case CONTAGEM_DE_CHAR:
      quadroEnquadrado =
          CamadaEnlaceTransmissoraEnquadramentoContagemDeCaracteres(quadro);
      break;
    case INSERCAO_DE_BYTE:
      quadroEnquadrado =
          CamadaEnlaceTransmissoraEnquadramentoInsercaoDeBytes(quadro);
      break;
    default:
      cout << "Tipo de enquadramento não reconhecido..." << endl;
      break;
  }
  return quadroEnquadrado;
}

vector<int> CamadaEnlaceTransmissoraEnquadramentoContagemDeCaracteres(
    vector<int> quadro) {
  // vector<int> quadroEnquadrado = quadro;
  vector<int> quadroEnquadrado;
  int tamanho = quadro.size();
  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int header = 0;
  if (tamanho >= CONTAGEM_HEADER) {
    header = CONTAGEM_HEADER;
  } else if (tamanho != 0) {
    header = tamanho + 1;
  }
  while (tamanho > 0) {
    if (i == 0) {
      quadroEnquadrado.push_back(header);
      i++;
    } else {
      quadroEnquadrado.push_back(quadro.at(j));
      i++;
      j++;
      tamanho--;
      if (i == header) {
        i = 0;
        if (tamanho < CONTAGEM_HEADER) {
          header = tamanho + 1;
        }
      }
    }
  }
  cout << endl << "Enquadramento por contagem de caracteres:" << endl;
  for (i = 0; i < quadroEnquadrado.size(); i++) {
    cout << quadroEnquadrado.at(i) << " ";
  }
  cout << endl;
  return quadroEnquadrado;
}

vector<int> CamadaEnlaceTransmissoraEnquadramentoInsercaoDeBytes(
    const vector<int>& quadro) {
  vector<int> quadroEnquadrado = quadro;
  return quadroEnquadrado;
}

/* Próxima etapa do trabalho */
void CamadaEnlaceTransmissoraControleDeErro(const vector<int>& quadro) {}

void CamadaEnlaceReceptora(const vector<int>& quadroEnquadrado,
                           int tipoDeEnquadramento) {
  vector<int> quadro =
      CamadaEnlaceReceptoraEnquadramento(quadroEnquadrado, tipoDeEnquadramento);
  // CamadaEnlaceReceptoraControleDeErro(quadro);
  CamadaDeAplicacaoReceptora(quadro);
}

vector<int> CamadaEnlaceReceptoraEnquadramento(
    const vector<int>& quadroEnquadrado, int tipoDeEnquadramento) {
  // int tipoDeEnquadramento = 0;
  vector<int> quadro;

  switch (tipoDeEnquadramento) {
    case CONTAGEM_DE_CHAR:
      quadro = CamadaEnlaceReceptoraEnquadramentoContagemDeCaracteres(
          quadroEnquadrado);
      break;
    case INSERCAO_DE_BYTE:
      quadro =
          CamadaEnlaceReceptoraEnquadramentoInsercaoDeBytes(quadroEnquadrado);
      break;
    default:
      cout << "Tipo de desenquadramento não reconhecido..." << endl;
      break;
  }
  return quadro;
}

vector<int> CamadaEnlaceReceptoraEnquadramentoContagemDeCaracteres(
    vector<int> quadroEnquadrado) {
  // vector<int> quadro = quadroEnquadrado;
  vector<int> quadro;
  unsigned int i = 0;
  while (i < quadroEnquadrado.size()) {
    unsigned int j = 0;
    unsigned int header = 0;
    header = quadroEnquadrado.at(i);
    j = i + 1;
    i += header;
    while (j < i) {
      quadro.push_back(quadroEnquadrado.at(j));
      j++;
    }
  }
  return quadro;
}

vector<int> CamadaEnlaceReceptoraEnquadramentoInsercaoDeBytes(
    const vector<int>& quadroEnquadrado) {
  vector<int> quadro = quadroEnquadrado;
  return quadro;
}

/* Próxima etapa do trabalho */
void CamadaEnlaceReceptoraControleDeErro(const vector<int>& quadro) {}