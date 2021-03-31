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
 * Entrada na camada de aplicação para recepção.
 * @param mensagem String resultado da decodificação.
 */
void AplicacaoReceptora(string);
