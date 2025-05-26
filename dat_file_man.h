//
// Created by alex on 25/05/25.
//

// Define a estrutura de dados que será gravada no arquivo
typedef struct {
    int codigo;
    char nome[50];
    float preco;
} Produto;


#ifndef DAT_FILE_MAN_H
#define DAT_FILE_MAN_H
int write_array();
int read_array();
int write_struct();
int read_struct();
int write_array_of_structs();
int read_all_structs();
int append_array_of_structs(Produto *array, int numProdutos);
#endif //DAT_FILE_MAN_H
