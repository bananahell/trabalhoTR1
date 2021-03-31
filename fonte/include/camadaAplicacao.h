#include "camadaFisica.h"

const int ASCII_MAX_BITS = 8;

/**
 * Entrada na camada de aplicação para transmissão.
 */
void AplicacaoTransmissora();

/**
 * Parte da camada de aplicação que transmite dados chamando a camada física.
 * @param mensagem Mensagem que vai ser codificada na camada física.
 */
void CamadaDeAplicacaoTransmissora(string);

/**
 * Recebe string e retorna um vetor de inteiros dos valores binários em ASCII de
 * cada caracter.
 * @param mensagem String a ser convertida.
 * @return Um vetor com os bits em binário da string em ASCII.
 */
vector<int> TransformaStringEmASCII(string);

/**
 * Recebe vetor de bits em ASCII e converte em string.
 * @param quadro Um vetor com os bits em binário da string em ASCII.
 * @return A string convertida.
 */
string TransformaASCIIEmString(vector<int>);

/**
 * Entrada na camada de aplicação para recepção.
 * @param mensagem String resultado da decodificação.
 */
void AplicacaoReceptora(string);
