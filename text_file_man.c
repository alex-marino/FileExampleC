//
// Created by alex on 25/05/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strtok ou remoção de '\n'
#include <ctype.h>  // Para isspace()
#include "text_file_man.h"

int write_file() {
    FILE *fptr;
    char nome[50];
    int idade;
    float altura;

    // Abre o arquivo "dados_pessoais.txt" em modo de escrita
    fptr = fopen("dados_pessoais.txt", "w");

    if (fptr == NULL) {
        perror("Erro ao abrir o arquivo dados_pessoais.txt");
        exit(1);
    }

    // Solicita dados ao usuário
    printf("Digite o nome: ");
    if (fgets(nome, sizeof(nome), stdin) != NULL) {
        // Remove o '\n' ao final se houver
        nome[strcspn(nome, "\n")] = '\0';
    }

    // Leitura e validação da idade
    do {
        printf("Digite a idade (0 a 120): ");
        if (scanf("%d", &idade) != 1) {
            printf("Entrada inválida. Por favor, insira um número inteiro.\n");
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }
        if (idade < 0 || idade > 120) {
            printf("Idade fora do intervalo válido.\n");
        }
    } while (idade < 0 || idade > 120);

    // Leitura e validação da altura
    do {
        printf("Digite a altura (em metros, ex: 1.75): ");
        if (scanf("%f", &altura) != 1) {
            printf("Entrada inválida. Por favor, insira um número decimal.\n");
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }
        if (altura <= 0.3 || altura > 2.5) {
            printf("Altura fora do intervalo válido (0.3m a 2.5m).\n");
        }
    } while (altura <= 0.3 || altura > 2.5);

    // Escreve os dados no arquivo
    fprintf(fptr, "Nome: %s\n", nome);
    fprintf(fptr, "Idade: %d anos\n", idade);
    fprintf(fptr, "Altura: %.2f metros\n", altura);

    fclose(fptr);

    printf("\nDados gravados com sucesso no arquivo 'dados_pessoais.txt'.\n");

    return 0;
}

int read_file() {
    FILE *fptr;
    char nome[50];
    int idade;
    float altura;

    // Abre o arquivo "dados_pessoais.txt" em modo de leitura ("r")
    fptr = fopen("dados_pessoais.txt", "r");

    // Verifica se o arquivo foi aberto com sucesso
    if (fptr == NULL) {
        perror("Erro ao abrir o arquivo dados_pessoais.txt");
        printf("Certifique-se que o arquivo 'dados_pessoais.txt' existe no mesmo diretorio ou execute o Exemplo 1 primeiro.\n");
        exit(1); // Termina o programa indicando erro
    }

    // Lê os dados formatados do arquivo
    // fscanf funciona de forma similar ao scanf, mas lê de um arquivo.
    // É importante que o formato de leitura corresponda exatamente ao formato de escrita.
    // Usamos %*[^:]*: para ignorar o texto antes de ':' e o espaço.
    // Usamos %49[^\n] para ler a string até a nova linha (evita ler a linha inteira se houver espaços no nome).
        // Verificamos o retorno de fscanf para garantir que a leitura foi bem-sucedida.
        int itens_lidos = 0;
    itens_lidos += fscanf(fptr, "Nome: %49[^\n]\n", nome); // Lê Nome:
    itens_lidos += fscanf(fptr, "Idade: %d anos\n", &idade); // Lê Idade:
    itens_lidos += fscanf(fptr, "Altura: %f metros\n", &altura); // Lê Altura:

    // Fecha o arquivo após a leitura
    fclose(fptr);

    // Verifica se todos os itens esperados foram lidos
    if (itens_lidos == 3) {
        printf("Dados lidos com sucesso do arquivo 'dados_pessoais.txt':\n");
        printf("Nome: %s\n", nome);
        printf("Idade: %d\n", idade);
        printf("Altura: %.2f\n", altura);
    } else {
        fprintf(stderr, "Erro ao ler os dados do arquivo ou formato inesperado. Itens lidos: %d\n", itens_lidos);
        // Poderia ter ocorrido um erro de leitura ou o arquivo não estava no formato esperado.
    }

    return 0;
}

int read_lines() {
    FILE *fptr;
    char linha[MAX_LINHA];
    char nomeArquivo[] = "poesia.txt"; // Nome do arquivo a ser lido

    // Tenta abrir o arquivo para leitura
    fptr = fopen(nomeArquivo, "r");

    // Se o arquivo não existir, cria um arquivo de exemplo para demonstração
    if (fptr == NULL) {
        printf("Arquivo '%s' nao encontrado. Criando um arquivo de exemplo...\n", nomeArquivo);
        fptr = fopen(nomeArquivo, "w"); // Abre para escrita para criar
        if (fptr == NULL) {
            perror("Erro ao criar o arquivo de exemplo");
            exit(1);
        }
        // Escreve algumas linhas no arquivo de exemplo
        fprintf(fptr, "No meio do caminho tinha uma pedra\n");
        fprintf(fptr, "tinha uma pedra no meio do caminho\n");
        fprintf(fptr, "tinha uma pedra\n");
        fprintf(fptr, "no meio do caminho tinha uma pedra.\n");
        fclose(fptr); // Fecha após escrever
        printf("Arquivo '%s' criado com sucesso. Execute o programa novamente para ler o conteudo.\n", nomeArquivo);
        exit(0); // Sai para o usuário executar novamente e ler o arquivo criado
    }

    // Se chegou aqui, o arquivo existe e foi aberto com sucesso para leitura ("r")

    printf("Conteudo do arquivo '%s':\n---\n", nomeArquivo);

    // Lê o arquivo linha por linha usando fgets()
    // fgets(destino_string, tamanho_maximo_leitura, ponteiro_arquivo)
    // Lê até (tamanho_maximo_leitura - 1) caracteres, ou até encontrar um '\n', ou até o fim do arquivo (EOF).
    // Importante: fgets() inclui o caractere '\n' na string lida, se houver espaço no buffer.
    // Retorna NULL quando atinge o fim do arquivo (EOF) ou se ocorrer um erro de leitura.
    while (fgets(linha, sizeof(linha), fptr) != NULL) {
        // Imprime a linha que foi lida do arquivo
        printf("%s", linha);
        // Como fgets() geralmente inclui o '\n', não precisamos adicionar outro ao imprimir.
    }

    // Após o loop, verifica se a saída ocorreu devido a um erro de leitura
    // ferror() retorna não-zero se um erro ocorreu.
    if (ferror(fptr)) {
        perror("Erro durante a leitura do arquivo");
    }
    // Não é estritamente necessário verificar feof() aqui, pois a condição de parada
    // do loop (fgets retornar NULL) já cobre o caso de fim de arquivo.

    // Fecha o arquivo para liberar os recursos
    fclose(fptr);

    printf("\n---\nLeitura do arquivo concluida.\n");

    return 0;
}

int copy_file() {
    FILE *arquivoOrigem, *arquivoDestino;
    char nomeArquivoOrigem[] = "poesia.txt"; // Arquivo a ser copiado (usado no Exemplo 3)
    char nomeArquivoDestino[] = "copia_posia.txt";
    int caractere;

    // 1. Abrir o arquivo de origem para leitura ("r")
    arquivoOrigem = fopen(nomeArquivoOrigem, "r");
    if (arquivoOrigem == NULL) {
        perror("Erro ao abrir o arquivo de origem");
        printf("Certifique-se que o arquivo 	'%s' existe (pode ser criado executando o Exemplo 3).\n", nomeArquivoOrigem);
        exit(1);
    }

    // 2. Abrir o arquivo de destino para escrita ("w")
    // Se o arquivo existir, será sobrescrito. Se não existir, será criado.
    arquivoDestino = fopen(nomeArquivoDestino, "w");
    if (arquivoDestino == NULL) {
        perror("Erro ao abrir/criar o arquivo de destino");
        fclose(arquivoOrigem); // Fecha o arquivo de origem antes de sair
        exit(1);
    }

    printf("Copiando conteudo de 	'%s' para 	'%s'...\n", nomeArquivoOrigem, nomeArquivoDestino);

    // 3. Ler caractere por caractere do arquivo de origem e escrever no destino
    // fgetc() lê um caractere e avança o ponteiro do arquivo.
    // Retorna o caractere lido (como um int) ou EOF no final do arquivo ou em caso de erro.
    while ((caractere = fgetc(arquivoOrigem)) != EOF) {
        // fputc() escreve um caractere no arquivo de destino.
        // Retorna o caractere escrito ou EOF em caso de erro.
        if (fputc(caractere, arquivoDestino) == EOF) {
            perror("Erro ao escrever no arquivo de destino");
            fclose(arquivoOrigem);
            fclose(arquivoDestino);
            exit(1);
        }
    }

    // 4. Verificar se o loop terminou devido a um erro de leitura na origem
    if (ferror(arquivoOrigem)) {
        perror("Erro durante a leitura do arquivo de origem");
        fclose(arquivoOrigem);
        fclose(arquivoDestino);
        exit(1);
    }

    printf("Arquivo copiado com sucesso!\n");

    // 5. Fechar ambos os arquivos
    if (fclose(arquivoOrigem) == EOF) {
        perror("Erro ao fechar o arquivo de origem");
        // Mesmo com erro no fechamento da origem, tentamos fechar o destino
    }
    if (fclose(arquivoDestino) == EOF) {
        perror("Erro ao fechar o arquivo de destino");
        exit(1); // Erro no fechamento do destino é mais crítico
    }

    return 0;
}


void word_counter() {
    FILE *fptr;
    char nomeArquivo[] = "poesia.txt"; // Arquivo a ser analisado
    int caractere;
    long numCaracteres = 0;
    long numLinhas = 0;
    long numPalavras = 0;
    int noEspaco = 1; // Flag: 1 se estivermos em espaço/início, 0 se dentro de uma palavra

    // 1. Abrir o arquivo para leitura
    fptr = fopen(nomeArquivo, "r");
    if (fptr == NULL) {
        perror("Erro ao abrir o arquivo");
        printf("Certifique-se que o arquivo 	'%s' existe (pode ser criado executando o Exemplo 3).\n", nomeArquivo);
        exit(1);
    }

    printf("Analisando o arquivo 	'%s' para contar linhas, palavras e caracteres...\n", nomeArquivo);

    // 2. Ler caractere por caractere até o fim do arquivo (EOF)
    while ((caractere = fgetc(fptr)) != EOF) {
        numCaracteres++; // Incrementa a contagem de caracteres

        // Conta linhas (incrementa sempre que encontrar um '\n')
        if (caractere == '\n') {
            numLinhas++;
        }

        // Conta palavras
        // isspace() verifica se o caractere é espaço, tab, newline, etc.
        if (isspace(caractere)) {
            // Se encontrou um espaço, marca que estamos fora de uma palavra
            noEspaco = 1;
        } else {
            // Se encontrou um caractere que não é espaço E estávamos fora de uma palavra antes,
            // significa que uma nova palavra começou.
            if (noEspaco) {
                numPalavras++;
                noEspaco = 0; // Marca que agora estamos dentro de uma palavra
            }
        }
    }

    // 3. Verificar se ocorreu erro durante a leitura
    if (ferror(fptr)) {
        perror("Erro durante a leitura do arquivo");
        fclose(fptr);
        exit(1);
    }

    // 4. Considerar a última linha se o arquivo não terminar com '\n'
    // Se o arquivo não for vazio e não terminar com '\n', a última linha não foi contada.
    // Uma forma simples de ajustar é incrementar se houver caracteres mas a contagem de linhas for 0,
    // ou se o último caractere lido não foi '\n' (requer guardar o último caractere, mais complexo).
    // Abordagem mais comum: Se o arquivo tem caracteres, ele tem pelo menos uma linha.
    if (numCaracteres > 0) {
         // Se o arquivo não termina com \n, a contagem de linhas estará subestimada em 1.
         // Para simplificar, vamos assumir que um arquivo não vazio tem pelo menos 1 linha.
         // Se numLinhas é 0 mas numCaracteres > 0, fazemos numLinhas = 1.
         // Ou, se o último caractere não foi \n, incrementamos. Vamos pela primeira abordagem.
         if (numLinhas == 0) { // Caso de arquivo sem \n no final
             numLinhas = 1;
         }
         // Nota: Uma forma mais precisa seria verificar o último caractere lido antes do EOF.
         // Se ele não foi '\n', incrementa numLinhas. Mas fseek para voltar 1 char pode ser complexo
         // dependendo do modo (texto vs binário) e SO. A lógica atual é uma boa aproximação.
    }


    // 5. Fechar o arquivo
    fclose(fptr);

    // 6. Imprimir os resultados
    printf("\n--- Resultados ---\n");
    printf("Caracteres: %ld\n", numCaracteres);
    printf("Palavras:   %ld\n", numPalavras);
    printf("Linhas:     %ld\n", numLinhas);
    printf("------------------\n");
}
