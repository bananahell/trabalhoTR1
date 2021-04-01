#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const int CODIFICACAO_BINARIA = 0;
const int CODIFICACAO_MANCHESTER = 1;
const int CODIFICACAO_BIPOLAR = 2;
const vector<int> CLOCK_MANCHESTER{0, 1};

/**
 * Entrada na camada física para transmissão.
 * @param fluxoBrutoDeBits Bits que vão viajar pelos sinais via cabo ou onda.
 * @param codificacaoFisica Codificação escolhida, entre Binária, Bipolar e
 * Manchester.
 */
void CamadaFisicaTransmissora(const vector<int>&, int);

/**
 * "Simulação" do meio de comunicação, transmitindo os bits.
 * @param fluxoBrutoDeBits Bits viajando pelos sinais via cabo ou onda.
 * @param codificacaoFisica Codificação escolhida, entre Binária, Bipolar e
 * Manchester.
 */
void MeioDeComunicacao(const vector<int>&, int);

/**
 * Entrada na camada física para recepção.
 * @param fluxoBrutoDeBits Bits que que viajaram pelos sinais via cabo ou onda.
 * @param codificacaoFisica Codificação escolhida, entre Binária, Bipolar e
 * Manchester.
 */
void CamadaFisicaReceptora(const vector<int>&, int);

/**
 * Ou conhecida como NRZ, simplesmente replica a sequência de bits recebida.
 * @param quadro Sequência de bits a ser codificada
 * @return Bits prestees a serem enviados ao meio de comunicação.
 */
vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int>);
/**
 * Faz a codificação Manchester do sinal, aplicando uma XOR no sinal com um
 * clock de frequência igual ao tempo dos bits.
 * @param quadro Sequência de bits a ser codificada
 * @return Bits prestees a serem enviados ao meio de comunicação.
 */
vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int>);
/**
 * Faz a codificação Bipolar do sinal, mantendo os 0's e alternando os 1's de 1
 * para -1.
 * @param quadro Sequência de bits a ser codificada
 * @return Bits prestees a serem enviados ao meio de comunicação.
 */
vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int>);

/**
 * Ou conhecida como NRZ, simplesmente replica a sequência de bits recebida.
 * @param fluxoBrutoDeBits Bits recebidos do meio de comunicação.
 * @return A sequência de bits decodificada.
 */
vector<int> CamadaFisicaReceptoraCodificacaoBinaria(vector<int>);
/**
 * Faz a decodificação Manchester do sinal, aplicando uma XOR no sinal com um
 * clock de frequência igual ao tempo dos bits.
 * @param fluxoBrutoDeBits Bits recebidos do meio de comunicação.
 * @return A sequência de bits decodificada.
 */
vector<int> CamadaFisicaReceptoraCodificacaoManchester(vector<int>);
/**
 * Faz a decodificação Bipolar do sinal, mantendo os 0's e alternando os 1's de
 * 1 para -1.
 * @param fluxoBrutoDeBits Bits recebidos do meio de comunicação.
 * @return A sequência de bits decodificada.
 */
vector<int> CamadaFisicaReceptoraCodificacaoBipolar(vector<int>);

/**
 * Entrada na camada de aplicação para recepção.
 * @param quadro Sequência de bits a ser decodificada pela camada de aplicação.
 */
void CamadaDeAplicacaoReceptora(const vector<int>&);
