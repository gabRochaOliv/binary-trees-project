#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

// Defini��o da estrutura Medicamento
struct medicamento {
    char nome[20];
    int codigo;
    float valor;
    int data[3];
};

// Defini��o da estrutura Arvore
struct arvore {
    Medicamento* m;
    Arvore* esquerda;
    Arvore* direita;
};

// Fun��o para criar um novo medicamento
Medicamento* CriaMedicamento(char* nome, int codigo, float valor, int* data_de_validade) {
    Medicamento* m = (Medicamento*)malloc(sizeof(Medicamento));
    strcpy(m->nome, nome);
    m->codigo = codigo;
    m->valor = valor;
    memcpy(m->data, data_de_validade, 3 * sizeof(int));
    return m;
}

// Fun��o para criar uma �rvore vazia
Arvore* CriaArvore() {
    return NULL; // �rvore inicializada como vazia
}

// Fun��o para inserir um medicamento na �rvore
Arvore* InsereArvoreMedicamento(Arvore* a, Medicamento* m) {
    if (a == NULL) { // Posi��o encontrada
        a = (Arvore*)malloc(sizeof(Arvore));
        a->m = m;
        a->esquerda = a->direita = NULL;
    } else if (m->codigo < a->m->codigo) { // Inserir � esquerda
        a->esquerda = InsereArvoreMedicamento(a->esquerda, m);
    } else { // Inserir � direita
        a->direita = InsereArvoreMedicamento(a->direita, m);
    }
    return a;
}

// Fun��o para remover um medicamento da �rvore
Arvore* RetiraArvoreMedicamento(Arvore* a, int id_medicamento) {
    if (a == NULL) return NULL; // �rvore vazia ou n�o encontrado
    if (id_medicamento < a->m->codigo) {
        a->esquerda = RetiraArvoreMedicamento(a->esquerda, id_medicamento);
    } else if (id_medicamento > a->m->codigo) {
        a->direita = RetiraArvoreMedicamento(a->direita, id_medicamento);
    } else { // Medicamento encontrado
        if (a->esquerda == NULL && a->direita == NULL) {
            free(a->m);
            free(a);
            return NULL;
        } else if (a->esquerda == NULL) {
            Arvore* temp = a->direita;
            free(a->m);
            free(a);
            return temp;
        } else if (a->direita == NULL) {
            Arvore* temp = a->esquerda;
            free(a->m);
            free(a);
            return temp;
        } else {
            // Substitui��o pelo sucessor
            Arvore* temp = a->direita;
            while (temp->esquerda != NULL) temp = temp->esquerda;
            a->m = temp->m;
            a->direita = RetiraArvoreMedicamento(a->direita, temp->m->codigo);
        }
    }
    return a;
}

// Fun��o para verificar se um medicamento est� na �rvore
int VerificaArvoreMedicamento(Arvore* a, int id_medicamento) {
    if (a == NULL) return 0;
    if (id_medicamento == a->m->codigo) return 1;
    if (id_medicamento < a->m->codigo) return VerificaArvoreMedicamento(a->esquerda, id_medicamento);
    else return VerificaArvoreMedicamento(a->direita, id_medicamento);
}

// Fun��o para verificar se h� medicamentos vencidos na �rvore
int VerificaArvoreValidade(Arvore* a, int* data) {
    if (a == NULL) return 0;
    if (a->m->data[2] < data[2] ||
        (a->m->data[2] == data[2] && a->m->data[1] < data[1]) ||
        (a->m->data[2] == data[2] && a->m->data[1] == data[1] && a->m->data[0] < data[0])) {
        return 1;
    }
    return VerificaArvoreValidade(a->esquerda, data) || VerificaArvoreValidade(a->direita, data);
}

// Fun��o para imprimir a �rvore em ordem crescente
void ImprimeArvoreMedicamentos(Arvore* a) {
    if (a != NULL) {
        ImprimeArvoreMedicamentos(a->esquerda);
        printf("%s %d %.2f %02d/%02d/%04d\n", a->m->nome, a->m->codigo, a->m->valor, a->m->data[0], a->m->data[1], a->m->data[2]);
        ImprimeArvoreMedicamentos(a->direita);
    }
}

// Fun��o para liberar a �rvore
void LiberaArvore(Arvore* a) {
    if (a != NULL) {
        LiberaArvore(a->esquerda);
        LiberaArvore(a->direita);
        free(a->m);
        free(a);
    }
}
