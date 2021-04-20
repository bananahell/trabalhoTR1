#include "camadaAplicacao.h"

void AplicacaoTransmissora() {
  string mensagem;
  int codificacaoFisica = 0;
  int tipoDeEnquadramento = 0;
  cout << endl << "Digite uma mensagem: " << endl;
  getline(cin, mensagem);
  cout << endl
       << "Selecione um modo de codificação:" << endl
       << "0: Codificação Binária" << endl
       << "1: Codificação Manchester" << endl
       << "2: Codificação Bipolar" << endl;
  cin >> codificacaoFisica;
  cout << endl
       << "Selecione um tipo de enquadramento:" << endl
       << "0: Contagem de Caracteres" << endl
       << "1: Inserção de Bytes" << endl;
  cin >> tipoDeEnquadramento;
  CamadaDeAplicacaoTransmissora(mensagem, codificacaoFisica, tipoDeEnquadramento);
}

void CamadaDeAplicacaoTransmissora(const string& mensagem,
                                   int codificacaoFisica, int tipoDeEnquadramento) {
  vector<int> quadro = TransformaStringEmASCII(mensagem);
  //CamadaFisicaTransmissora(quadro, codificacaoFisica);
  CamadaEnlaceTransmissora(quadro, codificacaoFisica, tipoDeEnquadramento);
}

vector<int> TransformaStringEmASCII(string mensagem) {
  vector<int> quadro;
  cout << endl << "Mensagem em ASCII caracter por caracter:" << endl;
  for (unsigned i = 0; i < mensagem.size(); i++) {
    quadro.push_back(int(mensagem.at(i)));
    cout << mensagem.at(i) << " - " << quadro.at(i) << endl;
  }
  return quadro;
}

/*vector<int> TransformaStringEmASCII(string mensagem) {
  vector<int> quadro;
  cout << endl << "Mensagem em ASCII caracter por caracter:" << endl;
  for (unsigned i = 0; i < mensagem.size(); i++) {  // Pega mensagem inteira
    vector<int> tempQuadro;
    int charBinario = int(mensagem.at(i));
    for (unsigned j = 0; j < ASCII_MAX_BITS; j++) {  // 8 bits por letra
      if (charBinario % 2 == 0) {
        tempQuadro.push_back(0);
      } else {
        tempQuadro.push_back(1);
      }
      charBinario = charBinario >> 1;
    }
    cout << mensagem.at(i) << " - ";
    for (int k = ASCII_MAX_BITS - 1; k >= 0; k--) {
      quadro.push_back(tempQuadro.at(k));  // Adiciona letra ao vetor maior
      cout << tempQuadro.at(k);
    }
    cout << endl;
  }
  return quadro;
}*/

void CamadaDeAplicacaoReceptora(const vector<int>& quadro) {
  string mensagem = TransformaASCIIEmString(quadro);
  AplicacaoReceptora(mensagem);
}

string TransformaASCIIEmString(vector<int> quadro) {
  string mensagem = "";
  for (unsigned i = 0; i < quadro.size(); i++) {
    mensagem.append(1, char(quadro[i]));
    /*if(quadro[i] <= 4) {
      cout << quadro[i] << endl;
    }*/
  }
  return mensagem;
}

/*string TransformaASCIIEmString(vector<int> quadro) {
  string mensagem = "";
  int intChar = 0;
  for (unsigned i = 0; i < quadro.size(); i++) {  // Pega mensagem inteira
    if (i != 0 && i % ASCII_MAX_BITS == 0) {
      mensagem.append(1, char(intChar));  // Adiciona cada letra
      intChar = 0;
    }
    intChar = intChar << 1;   // Forma cada letra
    intChar += quadro.at(i);  // adicionando o int e shiftando para esquerda
  }
  mensagem.append(1, char(intChar));  // Adiciona última letra (ficou pra trás)
  return mensagem;
}*/

void AplicacaoReceptora(const string& mensagem) {
  cout << endl << "Mensagem recebida: " << mensagem << endl << endl;
}
