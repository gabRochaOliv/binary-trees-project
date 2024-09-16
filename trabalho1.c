#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

int main() {
    FILE* entrada = fopen("entrada.txt", "r");
    FILE* saida = fopen("saida.txt", "w");
    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    Arvore* estoque = CriaArvore(); // Cria a árvore binária vazia
    char comando[30], nome[20]; // Buffer para comandos e nome do medicamento
    int codigo, dia, mes, ano;
    float valor;

    // Loop de leitura de comandos
    while (fscanf(entrada, "%s", comando) != EOF) {
        if (strcmp(comando, "MEDICAMENTO") == 0) {
            fscanf(entrada, "%s %d %f %d %d %d", nome, &codigo, &valor, &dia, &mes, &ano);
            int data[] = {dia, mes, ano};
            Medicamento* m = CriaMedicamento(nome, codigo, valor, data);
            estoque = InsereArvoreMedicamento(estoque, m);
            fprintf(saida, "MEDICAMENTO %s %d ADICIONADO\n", nome, codigo);
        }
        else if (strcmp(comando, "RETIRA") == 0) {
            fscanf(entrada, "%d", &codigo);
            estoque = RetiraArvoreMedicamento(estoque, codigo);
            fprintf(saida, "MEDICAMENTO %d RETIRADO\n", codigo);
        }
        else if (strcmp(comando, "IMPRIME_ARVORE") == 0) {
            fprintf(saida, "ESTOQUE ATUAL:\n");
            ImprimeArvoreMedicamentos(estoque);
        }
        else if (strcmp(comando, "VERIFICA_VALIDADE") == 0) {
            fscanf(entrada, "%d %d %d", &dia, &mes, &ano);
            int data[] = {dia, mes, ano};
            if (VerificaArvoreValidade(estoque, data)) {
                fprintf(saida, "MEDICAMENTO VENCIDO ENCONTRADO\n");
            } else {
                fprintf(saida, "NENHUM MEDICAMENTO VENCIDO ENCONTRADO\n");
            }
        }
    }

    // Liberação da árvore e fechamento dos arquivos
    LiberaArvore(estoque);
    fclose(entrada);
    fclose(saida);

    return 0;
}
