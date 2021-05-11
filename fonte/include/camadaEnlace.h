#include "camadaFisica.h"

const int CONTAGEM_DE_CHAR = 0;
const int INSERCAO_DE_BYTE = 1;

const int BIT_PARIDADE_PAR = 0;
const int CRC = 1;
const int HAMMING = 2;

const int CONTAGEM_HEADER = 4;
const int FLAG = int('a');  // Usamos caracteres muito usados para
const int ESC = int('b');   // testar se o programa funciona bem

const int NUM_COL = 8;
const vector<int> GERADOR_CRC{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
                              0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1};

const int HAMMING_BITS_DADOS = 8;

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
void CamadaEnlaceTransmissora(vector<int>&);

/**
 * Função de seleção do tipo de Enquadramento.
 * @param quadro Bits que vão viajar pelos sinais via cabo ou onda.
 * @param tipoDeEnquadramento Protocolo de enquadramento escolhido, entre
 * Contagem de Caracteres ou Inserção de Bytes.
 */
vector<int> CamadaEnlaceTransmissoraEnquadramento(vector<int>&);

/**
 * Entrada na camada de enlace para recepção.
 * @param quadro Bits que vão viajar pelos sinais via cabo ou onda.
 * @param tipoDeEnquadramento Protocolo de enquadramento escolhido, entre
 * Contagem de Caracteres ou Inserção de Bytes.
 */
void CamadaEnlaceReceptora(vector<int>&);

vector<int> CamadaEnlaceReceptoraEnquadramento(vector<int>&);

vector<int> CamadaEnlaceTransmissoraControleDeErro(vector<int>&);

vector<int> CamadaEnlaceReceptoraControleDeErro(vector<int>&);

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
vector<int> CamadaEnlaceTransmissoraEnquadramentoInsercaoDeBytes(vector<int>&);

vector<int> CamadaEnlaceReceptoraEnquadramentoContagemDeCaracteres(vector<int>);

vector<int> CamadaEnlaceReceptoraEnquadramentoInsercaoDeBytes(vector<int>&);

vector<int> CamadaEnlaceTransmissoraControleDeErroBitParidade(vector<int>&);

vector<int> CamadaEnlaceReceptoraControleDeErroBitParidade(vector<int>&);

vector<int> CamadaEnlaceTransmissoraControleDeErroCRC(vector<int>&);

vector<int> CamadaEnlaceReceptoraControleDeErroCRC(const vector<int>&);

vector<int> CamadaEnlaceTransmissoraControleDeErroHamming(vector<int>&);

vector<int> CamadaEnlaceReceptoraControleDeErroHamming(vector<int>&);

vector<int> TransformaASCIIEmBits(vector<int>);

vector<int> TransformaBitsEmASCII(vector<int>);

/**
 * Entrada na camada de aplicação para recepção.
 * @param quadro Um vetor com os bits em binário da string em ASCII.
 */
void CamadaDeAplicacaoReceptora(const vector<int>&);

vector<int> DivideVetoresDeIntPorGerador(vector<int>&);
