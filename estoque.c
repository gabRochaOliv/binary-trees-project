#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

// Definição da estrutura Medicamento
struct medicamento {
    char nome[20];
    int codigo;
    float valor;
    int data[3];
};

// Definição da estrutura Arvore
struct arvore {
    Medicamento* m;
    Arvore* esquerda;
    Arvore* direita;
};

// Função para criar um novo medicamento
Medicamento* CriaMedicamento(char* nome, int codigo, float valor, int* data_de_validade) {
    Medicamento* m = (Medicamento*)malloc(sizeof(Medicamento));
    strcpy(m->nome, nome);
    m->codigo = codigo;
    m->valor = valor;
    memcpy(m->data, data_de_validade, 3 * sizeof(int));
    return m;
}

// Função para criar uma árvore vazia
Arvore* CriaArvore() {
    return NULL; // Árvore inicializada como vazia
}

// Função para inserir um medicamento na árvore
Arvore* InsereArvoreMedicamento(Arvore* a, Medicamento* m) {
    if (a == NULL) { // Posição encontrada
        a = (Arvore*)malloc(sizeof(Arvore));
        a->m = m;
        a->esquerda = a->direita = NULL;
    } else if (m->codigo < a->m->codigo) { // Inserir à esquerda
        a->esquerda = InsereArvoreMedicamento(a->esquerda, m);
    } else { // Inserir à direita
        a->direita = InsereArvoreMedicamento(a->direita, m);
    }
    return a;
}

// Função para remover um medicamento da árvore
Arvore* RetiraArvoreMedicamento(Arvore* a, int id_medicamento) {
    if (a == NULL) return NULL; // Árvore vazia ou não encontrado
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
            // Substituição pelo sucessor
            Arvore* temp = a->direita;
            while (temp->esquerda != NULL) temp = temp->esquerda;
            a->m = temp->m;
            a->direita = RetiraArvoreMedicamento(a->direita, temp->m->codigo);
        }
    }
    return a;
}

// Função para verificar se um medicamento está na árvore
int VerificaArvoreMedicamento(Arvore* a, int id_medicamento) {
    if (a == NULL) return 0;
    if (id_medicamento == a->m->codigo) return 1;
    if (id_medicamento < a->m->codigo) return VerificaArvoreMedicamento(a->esquerda, id_medicamento);
    else return VerificaArvoreMedicamento(a->direita, id_medicamento);
}

// Função para verificar se há medicamentos vencidos na árvore
int VerificaArvoreValidade(Arvore* a, int* data) {
    if (a == NULL) return 0;
    if (a->m->data[2] < data[2] ||
        (a->m->data[2] == data[2] && a->m->data[1] < data[1]) ||
        (a->m->data[2] == data[2] && a->m->data[1] == data[1] && a->m->data[0] < data[0])) {
        return 1;
    }
    return VerificaArvoreValidade(a->esquerda, data) || VerificaArvoreValidade(a->direita, data);
}

// Função para imprimir a árvore em ordem crescente
void ImprimeArvoreMedicamentos(Arvore* a) {
    if (a != NULL) {
        ImprimeArvoreMedicamentos(a->esquerda);
        printf("%s %d %.2f %02d/%02d/%04d\n", a->m->nome, a->m->codigo, a->m->valor, a->m->data[0], a->m->data[1], a->m->data[2]);
        ImprimeArvoreMedicamentos(a->direita);
    }
}

// Função para liberar a árvore
void LiberaArvore(Arvore* a) {
    if (a != NULL) {
        LiberaArvore(a->esquerda);
        LiberaArvore(a->direita);
        free(a->m);
        free(a);
    }
}
