#include <iostream>
#include <vector>

using namespace std;

const int CODIFICACAO_BINARIA = 0;
const int CODIFICACAO_MANCHESTER = 1;
const int CODIFICACAO_BIPOLAR = 2;

/**
 * Entrada na camada física para transmissão.
 * @param fluxoBrutoDeBits Bits que vão viajar pelos sinais via cabo ou onda.
 */
void CamadaFisicaTransmissora(vector<int>);

/**
 * "Simulação" do meio de comunicação, transmitindo os bits.
 * @param fluxoBrutoDeBits Bits viajando pelos sinais via cabo ou onda.
 */
void MeioDeComunicacao(vector<int>);

/**
 * Entrada na camada física para recepção.
 * @param fluxoBrutoDeBits Bits que que viajaram pelos sinais via cabo ou onda.
 */
void CamadaFisicaReceptora(vector<int>);

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int>);
vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int>);
vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int>);

vector<int> CamadaFisicaReceptoraCodificacaoBinaria(vector<int>);
vector<int> CamadaFisicaReceptoraCodificacaoManchester(vector<int>);
vector<int> CamadaFisicaReceptoraCodificacaoBipolar(vector<int>);

/**
 * Entrada na camada de aplicação para recepção.
 * @param quadro Sequência de bits a ser decodificada pela camada de aplicação.
 */
void CamadaDeAplicacaoReceptora(vector<int>);
