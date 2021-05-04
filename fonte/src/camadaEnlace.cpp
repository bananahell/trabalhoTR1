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
  cout << endl << "Enquadramento por contagem de caracteres:";
  while (tamanho > 0) {
    if (i == 0) {
      quadroEnquadrado.push_back(header);
      cout << endl << header << " - ";
      i++;
    } else {
      quadroEnquadrado.push_back(quadro.at(j));
      cout << quadro.at(j) << " ";
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
  cout << endl;
  return quadroEnquadrado;
}

vector<int> CamadaEnlaceTransmissoraEnquadramentoInsercaoDeBytes(
    const vector<int>& quadro) {
  vector<int> quadroEnquadrado;
  int i = 0;
  int j = 0;
  int tamanho = quadro.size();
  srand(time(0));
  int max_enquadro = 5;
  int min_enquadro = 2;
  int bytes_enquadro =
      (rand() % max_enquadro) + min_enquadro;  // quantidade de bytes por quadro
  quadroEnquadrado.push_back(FLAG);
  cout << endl
       << "Enquadramento por inserção de bytes." << endl
       << "Cada pedaço terá um tamanho aleatório entre 2 e 5 caracteres e será"
       << endl
       << "    impresso em uma linha." << endl
       << char(FLAG) << " e " << char(ESC)
       << " foram escolhidos como caracteres especiais nesse protocolo, então "
       << "será" << endl
       << "    impresso uma \\ atrás de cada " << char(FLAG) << " e "
       << char(ESC) << " na mensagem):" << endl
       << endl;
  while (i < tamanho) {
    if (quadro.at(i) == FLAG || quadro.at(i) == ESC) {
      cout << "\\";
      quadroEnquadrado.push_back(ESC);
    }
    quadroEnquadrado.push_back(quadro.at(i));
    cout << char(quadro.at(i));
    i++;
    j++;
    if (i == tamanho) {
      quadroEnquadrado.push_back(FLAG);
      cout << endl;
    } else {
      if (j == bytes_enquadro) {
        j = 0;
        bytes_enquadro = (rand() % max_enquadro) + min_enquadro;
        quadroEnquadrado.push_back(FLAG);
        cout << endl;
        quadroEnquadrado.push_back(FLAG);
      }
    }
  }
  return quadroEnquadrado;
}

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
  vector<int> quadro;
  int tamanho = quadroEnquadrado.size();
  int i = 0;
  bool escape = false;
  while (i < tamanho) {
    if (quadroEnquadrado.at(i) == FLAG) {
      if (escape) {
        quadro.push_back(quadroEnquadrado.at(i));
        escape = false;
      }
    } else if (quadroEnquadrado.at(i) == ESC) {
      if (escape) {
        quadro.push_back(quadroEnquadrado.at(i));
        escape = false;
      } else {
        escape = true;
      }
    } else {
      quadro.push_back(quadroEnquadrado.at(i));
    }
    i++;
  }

  return quadro;
}

void CamadaEnlaceReceptoraControleDeErro(const vector<int>& quadro) {}
