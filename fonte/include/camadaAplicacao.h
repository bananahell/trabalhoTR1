#include "camadaFisica.h"

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
 */
void AplicacaoReceptora();
