//
// Created by alex on 25/05/25.
//
#include <stdio.h>
#include <stdlib.h> // Para exit()
#include <string.h> // Para strcpy()

#include "dat_file_man.h"

#define MAX_NUMEROS 10 // Define o número máximo de inteiros que esperamos ler (igual ao escrito no Exemplo 5)

int write_array() {
    FILE *fptr;
    char nomeArquivo[] = "numeros.bin";
    int numeros[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    int numElementos = sizeof(numeros) / sizeof(int);

    // Abrir o arquivo binário para escrita
    fptr = fopen(nomeArquivo, "wb");
    if (fptr == NULL) {
        perror("Erro ao abrir/criar o arquivo binario");
        exit(1);
    }

    printf("Gravando array de %d inteiros no arquivo binario '%s'...\n", numElementos, nomeArquivo);

    size_t itensEscritos = fwrite(numeros, sizeof(int), numElementos, fptr);

    if (itensEscritos != numElementos) {
        fprintf(stderr, "Erro ao escrever no arquivo binario! Esperado: %d, Escrito: %zu\n", numElementos, itensEscritos);
        fclose(fptr);
        exit(1);
    }

    printf("Array de inteiros gravado com sucesso! (%zu itens escritos)\n", itensEscritos);

    if (fclose(fptr) == EOF) {
        perror("Erro ao fechar o arquivo binario");
    }

    return 0;
}

int read_array() {
    FILE *fptr;
    char nomeArquivo[] = "numeros.bin";
    int numerosLidos[MAX_NUMEROS];
    int numElementosEsperados = MAX_NUMEROS;

    // Abrir o arquivo binário para leitura
    fptr = fopen(nomeArquivo, "rb");
    if (fptr == NULL) {
        perror("Erro ao abrir o arquivo binario para leitura");
        printf("Certifique-se que o arquivo '%s' existe e foi criado anteriormente.\n", nomeArquivo);
        exit(1);
    }

    printf("Lendo array de inteiros do arquivo binario '%s'...\n", nomeArquivo);

    size_t itensLidos = fread(numerosLidos, sizeof(int), numElementosEsperados, fptr);

    if (itensLidos == 0 && !feof(fptr)) {
        fprintf(stderr, "Erro ao ler do arquivo binario! Nenhum item lido.\n");
        if (ferror(fptr)) {
            perror("Detalhe do erro de leitura");
        }
        fclose(fptr);
        exit(1);
    } else if (itensLidos < numElementosEsperados) {
        printf("Aviso: Foram lidos apenas %zu de %d elementos esperados. Fim do arquivo alcançado ou arquivo menor?\n", itensLidos, numElementosEsperados);
    } else {
        printf("Array de inteiros lido com sucesso! (%zu itens lidos)\n", itensLidos);
    }

    // Imprimir os números lidos
    printf("Numeros lidos do arquivo:\n");
    for (size_t i = 0; i < itensLidos; i++) {
        printf("%d ", numerosLidos[i]);
    }
    printf("\n");

    if (fclose(fptr) == EOF) {
        perror("Erro ao fechar o arquivo binario");
    }

    return 0;
}

int write_struct() {
    FILE *fptr;
    char nomeArquivo[] = "produto.bin";
    Produto meuProduto;

    // Preencher os dados da struct
    meuProduto.codigo = 101;
    strcpy(meuProduto.nome, "Caneta Azul");
    meuProduto.preco = 1.99;

    // Abrir o arquivo binário para escrita
    fptr = fopen(nomeArquivo, "wb");
    if (fptr == NULL) {
        perror("Erro ao abrir/criar o arquivo binario");
        exit(1);
    }

    printf("Gravando a struct Produto no arquivo binario '%s'...\n", nomeArquivo);

    // Escrever a struct inteira no arquivo
    size_t itensEscritos = fwrite(&meuProduto, sizeof(Produto), 1, fptr);

    if (itensEscritos != 1) {
        fprintf(stderr, "Erro ao escrever a struct no arquivo binario! Esperado: 1, Escrito: %zu\n", itensEscritos);
        fclose(fptr);
        exit(1);
    }

    printf("Struct Produto gravada com sucesso!\n");
    printf("Dados gravados: Codigo=%d, Nome='%s', Preco=%.2f\n", meuProduto.codigo, meuProduto.nome, meuProduto.preco);

    if (fclose(fptr) == EOF) {
        perror("Erro ao fechar o arquivo binario");
    }

    return 0;
}

int read_struct() {
    FILE *fptr;
    char nomeArquivo[] = "produto.bin";
    Produto meuProduto;

    // Abrir o arquivo binário para leitura
    fptr = fopen(nomeArquivo, "rb");
    if (fptr == NULL) {
        perror("Erro ao abrir o arquivo binario para leitura");
        printf("Certifique-se que o arquivo '%s' existe e foi criado anteriormente.\n", nomeArquivo);
        exit(1);
    }

    printf("Lendo a struct Produto do arquivo binario '%s'...\n", nomeArquivo);

    // Ler a struct do arquivo
    size_t itensLidos = fread(&meuProduto, sizeof(Produto), 1, fptr);

    if (itensLidos != 1) {
        fprintf(stderr, "Erro ao ler a struct do arquivo binario! Esperado: 1, Lido: %zu\n", itensLidos);
        fclose(fptr);
        exit(1);
    }

    printf("Struct Produto lida com sucesso!\n");
    printf("Dados lidos: Codigo=%d, Nome='%s', Preco=%.2f\n", meuProduto.codigo, meuProduto.nome, meuProduto.preco);

    if (fclose(fptr) == EOF) {
        perror("Erro ao fechar o arquivo binario");
    }

    return 0;
}

int write_array_of_structs() {
    FILE *fptr;
    char nomeArquivo[] = "produto.bin";

    // Criar e inicializar um array de structs Produto
    Produto estoque[] = {
        {110, "Caneta Azul", 1.99},
        {102, "Borracha Branca", 0.50},
        {205, "Caderno 96 fls", 7.80},
        {310, "Lapiseira 0.7mm", 5.25},
        {400, "Caixa Lapis Cor", 15.00}
    };

    int numProdutos = sizeof(estoque) / sizeof(Produto);

    // Abrir o arquivo binário para escrita
    fptr = fopen(nomeArquivo, "wb");
    if (fptr == NULL) {
        perror("Erro ao abrir/criar o arquivo binario para o estoque");
        exit(1);
    }

    printf("Gravando array de %d structs Produto no arquivo binario '%s'...\n", numProdutos, nomeArquivo);

    // Escrever o array de structs inteiro no arquivo
    size_t itensEscritos = fwrite(estoque, sizeof(Produto), numProdutos, fptr);

    if (itensEscritos != numProdutos) {
        fprintf(stderr, "Erro ao escrever o array de structs! Esperado: %d, Escrito: %zu\n", numProdutos, itensEscritos);
        fclose(fptr);
        exit(1);
    }

    printf("Array de structs Produto gravado com sucesso! (%zu itens escritos)\n", itensEscritos);

    if (fclose(fptr) == EOF) {
        perror("Erro ao fechar o arquivo binario do estoque");
    }

    return 0;
}

int read_all_structs() {
    FILE *fptr;
    char nomeArquivo[] = "produto.bin";
    Produto meuProduto;

    // Abrir o arquivo binário para leitura
    fptr = fopen(nomeArquivo, "rb");
    if (fptr == NULL) {
        perror("Erro ao abrir o arquivo binario para leitura");
        printf("Certifique-se que o arquivo '%s' existe e foi criado anteriormente.\n", nomeArquivo);
        exit(1);
    }

    printf("Lendo todas as structs Produto do arquivo binario '%s':\n\n", nomeArquivo);

    size_t itensLidos;
    int count = 0;

    // Ler enquanto conseguir ler uma struct completa
    while ((itensLidos = fread(&meuProduto, sizeof(Produto), 1, fptr)) == 1) {
        count++;
        printf("Registro %d:\n", count);
        printf("  Codigo: %d\n", meuProduto.codigo);
        printf("  Nome:   %s\n", meuProduto.nome);
        printf("  Preco:  %.2f\n\n", meuProduto.preco);
    }

    if (ferror(fptr)) {
        perror("Erro ao ler do arquivo binario");
        fclose(fptr);
        exit(1);
    }

    if (count == 0) {
        printf("Nenhum registro foi lido do arquivo.\n");
    } else {
        printf("Leitura concluída. Total de registros lidos: %d\n", count);
    }

    if (fclose(fptr) == EOF) {
        perror("Erro ao fechar o arquivo binario");
    }

    return 0;
}

int append_array_of_structs(Produto *array, int numProdutos) {
    FILE *fptr;
    char nomeArquivo[] = "produto.bin";

    // Abrir o arquivo binário para append ("ab")
    fptr = fopen(nomeArquivo, "ab");
    if (fptr == NULL) {
        perror("Erro ao abrir o arquivo binario para append");
        exit(1);
    }

    printf("Adicionando array de %d structs Produto ao arquivo binario '%s'...\n", numProdutos, nomeArquivo);

    // Escrever o array de structs no final do arquivo
    size_t itensEscritos = fwrite(array, sizeof(Produto), numProdutos, fptr);

    if (itensEscritos != numProdutos) {
        fprintf(stderr, "Erro ao adicionar structs ao arquivo binario! Esperado: %d, Escrito: %zu\n", numProdutos, itensEscritos);
        fclose(fptr);
        exit(1);
    }

    printf("Array de structs Produto adicionado com sucesso! (%zu itens escritos)\n", itensEscritos);

    if (fclose(fptr) == EOF) {
        perror("Erro ao fechar o arquivo binario");
    }

    return 0;
}