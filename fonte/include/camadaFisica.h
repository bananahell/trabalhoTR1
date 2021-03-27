#include <iostream>

using namespace std;

const int CODIFICACAO_BINARIA = 0;
const int CODIFICACAO_MANCHESTER = 1;
const int CODIFICACAO_BIPOLAR = 2;

/**
 * Entrada na camada física para transmissão.
 * @param fluxoBrutoDeBits Bits que vão viajar pelos sinais via cabo ou onda.
 */
void CamadaFisicaTransmissora(int*);

/**
 * "Simulação" do meio de comunicação, transmitindo os bits.
 * @param fluxoBrutoDeBits Bits viajando pelos sinais via cabo ou onda.
 */
void MeioDeComunicacao(int*);

/**
 * Entrada na camada física para recepção.
 * @param fluxoBrutoDeBits Bits que que viajaram pelos sinais via cabo ou onda.
 */
void CamadaFisicaReceptora(int*);

int* CamadaFisicaTransmissoraCodificacaoBinaria(int*);
int* CamadaFisicaTransmissoraCodificacaoManchester(int*);
int* CamadaFisicaTransmissoraCodificacaoBipolar(int*);

int* CamadaFisicaReceptoraCodificacaoBinaria(int*);
int* CamadaFisicaReceptoraCodificacaoManchester(int*);
int* CamadaFisicaReceptoraCodificacaoBipolar(int*);

/**
 * Entrada na camada de aplicação para recepção.
 * @param mensagem Mensagem que foi decodificada na camada física.
 */
void CamadaDeAplicacaoReceptora(string);
