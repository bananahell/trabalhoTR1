#include "camadaFisica.h"

const int CONTAGEM_DE_CHAR = 0;
const int INSERCAO_DE_BYTE = 1;

const int BIT_PARIDADE_PAR = 0;
const int CRC = 1;

const int CONTAGEM_HEADER = 4;
const int FLAG = int('a');  // Usamos caracteres muito usados para
const int ESC = int('b');   // testar se o programa funciona bem

extern int codificacaoFisica;
extern int tipoDeEnquadramento;
extern int tipoDeErro;

/**
 * Entrada na camada de enlace para transmissão.
 * São realizados o Enquadramento, o Controle de Erros, e o envio à Camada
 * Física.
 * @param quadro Bits que vão viajar pelos sinais via cabo ou onda.
 * @param tipoDeEnquadramento Protocolo de enquadramento escolhido, entre
 * Contagem de Caracteres ou Inserção de Bytes.
 */
void CamadaEnlaceTransmissora(const vector<int>&);

/**
 * Função de seleção do tipo de Enquadramento.
 * @param quadro Bits que vão viajar pelos sinais via cabo ou onda.
 * @param tipoDeEnquadramento Protocolo de enquadramento escolhido, entre
 * Contagem de Caracteres ou Inserção de Bytes.
 */
vector<int> CamadaEnlaceTransmissoraEnquadramento(const vector<int>&);

/**
 * Entrada na camada de enlace para recepção.
 * @param quadro Bits que vão viajar pelos sinais via cabo ou onda.
 * @param tipoDeEnquadramento Protocolo de enquadramento escolhido, entre
 * Contagem de Caracteres ou Inserção de Bytes.
 */
void CamadaEnlaceReceptora(vector<int>&);

vector<int> CamadaEnlaceReceptoraEnquadramento(const vector<int>&);

vector<int> CamadaEnlaceTransmissoraControleDeErro(const vector<int>&);

vector<int> CamadaEnlaceReceptoraControleDeErro(const vector<int>&);

/**
 * Enquadramento do tipo Contagem de Caracteres.
 * @param quadro Bits que vão viajar pelos sinais via cabo ou onda.
 */
vector<int> CamadaEnlaceTransmissoraEnquadramentoContagemDeCaracteres(
    vector<int>);

/**
 * Enquadramento do tipo Inserção de Bytes.
 * @param quadro Bits que vão viajar pelos sinais via cabo ou onda.
 */
vector<int> CamadaEnlaceTransmissoraEnquadramentoInsercaoDeBytes(
    const vector<int>&);

vector<int> CamadaEnlaceReceptoraEnquadramentoContagemDeCaracteres(vector<int>);

vector<int> CamadaEnlaceReceptoraEnquadramentoInsercaoDeBytes(
    const vector<int>&);

vector<int> TransformaASCIIEmBits(vector<int>);

vector<int> TransformaBitsEmASCII(vector<int>);

/**
 * Entrada na camada de aplicação para recepção.
 * @param quadro Um vetor com os bits em binário da string em ASCII.
 */
void CamadaDeAplicacaoReceptora(const vector<int>&);
