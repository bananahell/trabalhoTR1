#include "camadaAplicacao.h"

void AplicacaoTransmissora() {
  string mensagem;
  int codificacaoFisica = 0;
  int tipoDeEnquadramento = 0;
  cout << endl << "Digite uma mensagem: ";
  getline(cin, mensagem);
  cout << endl
       << "Selecione um tipo de enquadramento (camada de enlace):" << endl
       << "0: Contagem de Caracteres" << endl
       << "1: Inserção de Bytes" << endl;
  cin >> tipoDeEnquadramento;
  cout << endl
       << "Selecione um modo de codificação (camada física):" << endl
       << "0: Codificação Binária" << endl
       << "1: Codificação Manchester" << endl
       << "2: Codificação Bipolar" << endl;
  cin >> codificacaoFisica;
  CamadaDeAplicacaoTransmissora(mensagem, codificacaoFisica,
                                tipoDeEnquadramento);
}

void CamadaDeAplicacaoTransmissora(const string& mensagem,
                                   int codificacaoFisica,
                                   int tipoDeEnquadramento) {
  vector<int> quadro = TransformaStringEmASCII(mensagem);
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

void CamadaDeAplicacaoReceptora(const vector<int>& quadro) {
  string mensagem = TransformaASCIIEmString(quadro);
  AplicacaoReceptora(mensagem);
}

string TransformaASCIIEmString(vector<int> quadro) {
  string mensagem = "";
  for (unsigned i = 0; i < quadro.size(); i++) {
    mensagem.append(1, char(quadro[i]));
  }
  return mensagem;
}

void AplicacaoReceptora(const string& mensagem) {
  cout << endl << "Mensagem recebida: " << mensagem << endl << endl;
}
