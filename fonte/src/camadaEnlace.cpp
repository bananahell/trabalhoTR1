#include "camadaEnlace.h"

void CamadaEnlaceTransmissora(vector<int>& quadro) {
  vector<int> quadroEnquadrado = CamadaEnlaceTransmissoraEnquadramento(quadro);
  quadroEnquadrado = TransformaASCIIEmBits(quadroEnquadrado);
  quadroEnquadrado = CamadaEnlaceTransmissoraControleDeErro(quadroEnquadrado);
  CamadaFisicaTransmissora(quadroEnquadrado);
}

vector<int> CamadaEnlaceTransmissoraEnquadramento(vector<int>& quadro) {
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

void CamadaEnlaceReceptora(vector<int>& quadroEnquadrado) {
  quadroEnquadrado = CamadaEnlaceReceptoraControleDeErro(quadroEnquadrado);
  if (quadroEnquadrado.size() == 1) {
    cout << "Houve um erro na transmissão da mensagem!" << endl;
    return;
  }
  quadroEnquadrado = TransformaBitsEmASCII(quadroEnquadrado);
  vector<int> quadro = CamadaEnlaceReceptoraEnquadramento(quadroEnquadrado);
  CamadaDeAplicacaoReceptora(quadro);
}

vector<int> CamadaEnlaceReceptoraEnquadramento(vector<int>& quadroEnquadrado) {
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

vector<int> CamadaEnlaceTransmissoraControleDeErro(vector<int>& quadro) {
  vector<int> quadroControlado;

  switch (tipoDeErro) {
    case BIT_PARIDADE_PAR:
      quadroControlado =
          CamadaEnlaceTransmissoraControleDeErroBitParidade(quadro);
      break;
    case CRC:
      quadroControlado = CamadaEnlaceTransmissoraControleDeErroCRC(quadro);
      break;
    case HAMMING:
      quadroControlado = CamadaEnlaceTransmissoraControleDeErroHamming(quadro);
      break;
    default:
      cout << "Tipo de erro não reconhecido..." << endl;
      break;
  }
  return quadroControlado;
}

vector<int> CamadaEnlaceReceptoraControleDeErro(vector<int>& quadro) {
  vector<int> quadroVerificado;

  switch (tipoDeErro) {
    case BIT_PARIDADE_PAR:
      quadroVerificado = CamadaEnlaceReceptoraControleDeErroBitParidade(quadro);
      break;
    case CRC:
      quadroVerificado = CamadaEnlaceReceptoraControleDeErroCRC(quadro);
      break;
    case HAMMING:
      quadroVerificado = CamadaEnlaceReceptoraControleDeErroHamming(quadro);
      break;
    default:
      cout << "Tipo de erro não reconhecido..." << endl;
      break;
  }
  return quadroVerificado;
}

vector<int> CamadaEnlaceTransmissoraControleDeErroBitParidade(
    vector<int>& quadro) {
  vector<int> quadroChecado = quadro;
  bool par = true;
  for (unsigned i = 0; i < NUM_COL; i++) {
    for (unsigned j = i; j < quadro.size(); j += NUM_COL) {
      if (quadro.at(j) == 1) {
        par = !par;
      }
    }
    if (par) {
      quadroChecado.push_back(1);
    } else {
      quadroChecado.push_back(0);
    }
  }
  return quadroChecado;
}

vector<int> CamadaEnlaceTransmissoraControleDeErroCRC(vector<int>& quadro) {
  vector<int> quadroChecado = quadro;
  vector<int> quadroChecado1;

  for (unsigned i = 0; i < GERADOR_CRC.size()-1; i++) {
    quadroChecado.push_back(0);
  }
 
  quadroChecado1=quadroChecado;
  vector<int> crcAchado = DivideVetoresDeIntPorGerador(quadroChecado1);

  for (unsigned i = 0; i < crcAchado.size(); i++) {
    quadroChecado.at(quadroChecado.size()-1-i)=crcAchado.at(crcAchado.size()-1-i);
  }
  return quadroChecado;
}

vector<int> CamadaEnlaceTransmissoraControleDeErroHamming(
    vector<int>& quadro) {
  vector<int> quadroChecado;
  vector<int> buffer;
  int i;
  int j;
  int k;
  int index_paridade;
  int paridade;

  cout << endl << "Codigo de Hamming enviado: " << endl;
  for (i = 0; i < quadro.size(); i += HAMMING_BITS_DADOS) {
    buffer.clear();
    j = i;
    k = 0;
    index_paridade = 1;
    while (j < i + HAMMING_BITS_DADOS) { //insere os bits de mensagem e os bits de verificação no buffer
      if (k == (index_paridade - 1)) {
        buffer.push_back(0);
        index_paridade = index_paridade << 1;
        k++;
      }
      else {
        buffer.push_back(quadro.at(j));
        j++;
        k++;
      }
    }
    
    index_paridade = 1;
    paridade = 0;
    for (j = 0; j < buffer.size(); j++) { //calcula os bits de verificação pelo método XOR
      if (j == (index_paridade - 1)) {
        index_paridade = index_paridade << 1;
        j++;
      }
      else if (buffer.at(j) == 1) {
        paridade = paridade ^ (j + 1);
      }
    }

    index_paridade = 1;
    cout << "[" << (i/HAMMING_BITS_DADOS) + 1 << "]: ";
    for (j = 0; j < buffer.size(); j++) { //insere os bits de verificação e a mensagem no quadro de saída
      if (j == (index_paridade - 1)) {
        if (paridade % 2) {
          quadroChecado.push_back(1);
          cout << 1;
        }
        else {
          quadroChecado.push_back(0);
          cout << 0;
        }
        paridade = paridade >> 1;
        index_paridade = index_paridade << 1;
      }
      else {
        quadroChecado.push_back(buffer.at(j));
          cout << buffer.at(j);
      }
    }
    cout << endl;
  }
  return quadroChecado;
}

vector<int> CamadaEnlaceReceptoraControleDeErroHamming(
    vector<int>& quadro) {
  vector<int> quadroChecado;
  vector<int> buffer;
  int i = HAMMING_BITS_DADOS;
  int j;
  int index_paridade;
  int paridade;
  int bits_paridade = 0;

  while(i != 0) { //calcula o número de bits de verificação
    i = i >> 1;
    bits_paridade++;
  }
  cout << endl << "Codigo de Hamming recebido: " << endl;
  for (i = 0; i < quadro.size(); i += HAMMING_BITS_DADOS + bits_paridade) {
    buffer.clear();
    j = i;
    while (j < i + HAMMING_BITS_DADOS + bits_paridade) { //preenche o buffer com a mensagem
      buffer.push_back(quadro.at(j));
      j++;
    }
    cout << "[" << (i/(HAMMING_BITS_DADOS + bits_paridade)) + 1 << "]: ";
    paridade = 0;
    for (j = 0; j < buffer.size(); j++) { //verifica a paridade para verificar se há erro
      if (buffer.at(j) == 1) {
        paridade = paridade ^ (j + 1);
      }
      cout << buffer.at(j);
    }
    if (paridade) {
      cout << " - ERRO - bit " << paridade << " corrigido " << endl;
      if (buffer.at(paridade - 1)) {
        buffer.at(paridade - 1) = 0;
      }
      else {
        buffer.at(paridade - 1) = 1;
      }
    }
    else {
      cout << " - OK" << endl;
    }

    index_paridade = 1;
    for (j = 0; j < buffer.size(); j++) { //Insere os bits de dados no quadro de saída
      if (j == (index_paridade - 1)) {
        index_paridade = index_paridade << 1;
      }
      else {
        quadroChecado.push_back(buffer.at(j));
      }
    }
  }
  return quadroChecado;
}

vector<int> CamadaEnlaceReceptoraControleDeErroBitParidade(
    vector<int>& quadro) {
  vector<int> quadroChecado;
  bool par = true;
  for (unsigned i = 0; i < NUM_COL; i++) {
    for (unsigned j = i; j < quadro.size() - NUM_COL; j += NUM_COL) {
      if (quadro.at(j) == 1) {
        par = !par;
      }
    }
    if (quadro.at(quadro.size() - NUM_COL + i) != par) {
      quadroChecado.clear();
      quadroChecado.push_back(0);
      return quadroChecado;
    }
  }
  quadroChecado = quadro;
  for (unsigned i = 0; i < NUM_COL; i++) {
    quadroChecado.pop_back();
  }
  return quadroChecado;
}

vector<int> CamadaEnlaceReceptoraControleDeErroCRC(const vector<int>& quadro) {
  vector<int> quadroChecado = quadro;
  vector<int> resultadoDivisao;
  vector<int> quadro1 = quadro;
  resultadoDivisao = DivideVetoresDeIntPorGerador(quadroChecado);

  for (unsigned i = 0; i < resultadoDivisao.size(); i++) {
    if (resultadoDivisao.at(i) == 1) {
      quadroChecado.clear();
      quadroChecado.push_back(0);
      return quadroChecado;
    }
  }

  for (unsigned i = 0; i < GERADOR_CRC.size() - 1; i++) {
    quadro1.pop_back();
  }
  return quadro1;
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
    vector<int>& quadro) {
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
    vector<int>& quadroEnquadrado) {
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
    intChar = intChar << 1;  // Forma cada letra
    intChar += bits.at(i);   // adicionando o int e shiftando para esquerda
  }
  quadro.push_back(intChar);  // Adiciona última letra (ficou pra trás)
  return quadro;
}

vector<int> DivideVetoresDeIntPorGerador(vector<int>& bits) {
  vector<int> crcAchado;
  for (unsigned i = 0; i < bits.size() - GERADOR_CRC.size() + 1; i++) {
    if (bits.at(i) == 1) {
      for (unsigned j = 0; j < GERADOR_CRC.size(); j++) {
        bits.at(i + j) = bits.at(i + j) ^ GERADOR_CRC.at(j);
      }
    }
  }
  cout << "na divisao, crcAchado = ";
  for (unsigned i = 0; i < GERADOR_CRC.size() - 1; i++) {
    crcAchado.push_back(bits.at(bits.size() - GERADOR_CRC.size() + 1 + i));
    cout << crcAchado.at(i);
  }
  cout << endl;
  return crcAchado;
}
