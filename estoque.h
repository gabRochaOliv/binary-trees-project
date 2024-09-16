#ifndef ESTOQUE_H
#define ESTOQUE_H

typedef struct medicamento Medicamento;
typedef struct arvore Arvore;

/* Cria um novo medicamento */
Medicamento* CriaMedicamento(char* nome, int codigo, float valor, int* data_de_validade);

/* Cria uma nova �rvore bin�ria vazia */
Arvore* CriaArvore();

/* Insere um medicamento em uma �rvore */
Arvore* InsereArvoreMedicamento(Arvore* a, Medicamento* m);

/* Retira um medicamento de uma �rvore */
Arvore* RetiraArvoreMedicamento(Arvore* a, int id_medicamento);

/* Verifica se um medicamento est� presente em uma �rvore */
int VerificaArvoreMedicamento(Arvore* a, int id_medicamento);

/* Verifica se existe um medicamento vencido em uma �rvore */
int VerificaArvoreValidade(Arvore* a, int* data);

/* Imprime todos os medicamentos de uma �rvore em ordem crescente */
void ImprimeArvoreMedicamentos(Arvore* a);

/* Ordena uma �rvore pela data de vencimento do medicamento (j� ocorre pela pr�pria natureza da �rvore bin�ria) */

/* Libera a mem�ria da �rvore */
void LiberaArvore(Arvore* a);

#endif // ESTOQUE_H
