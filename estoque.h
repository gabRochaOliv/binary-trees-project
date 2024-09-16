#ifndef ESTOQUE_H
#define ESTOQUE_H

typedef struct medicamento Medicamento;
typedef struct arvore Arvore;

/* Cria um novo medicamento */
Medicamento* CriaMedicamento(char* nome, int codigo, float valor, int* data_de_validade);

/* Cria uma nova árvore binária vazia */
Arvore* CriaArvore();

/* Insere um medicamento em uma árvore */
Arvore* InsereArvoreMedicamento(Arvore* a, Medicamento* m);

/* Retira um medicamento de uma árvore */
Arvore* RetiraArvoreMedicamento(Arvore* a, int id_medicamento);

/* Verifica se um medicamento está presente em uma árvore */
int VerificaArvoreMedicamento(Arvore* a, int id_medicamento);

/* Verifica se existe um medicamento vencido em uma árvore */
int VerificaArvoreValidade(Arvore* a, int* data);

/* Imprime todos os medicamentos de uma árvore em ordem crescente */
void ImprimeArvoreMedicamentos(Arvore* a);

/* Ordena uma árvore pela data de vencimento do medicamento (já ocorre pela própria natureza da árvore binária) */

/* Libera a memória da árvore */
void LiberaArvore(Arvore* a);

#endif // ESTOQUE_H
