//
// Created by jmartins on 03/08/2026.
//

#ifndef HASH_REVIEW_HASHTABLE_H
#define HASH_REVIEW_HASHTABLE_H
#include <stdio.h>

#define EMPTY_VALUE -1 // REPRESENTA UM VALOR VAZIO
#define TAM 31 // 2 * qtdElementos e seleciona o numero primo mais proximo


void init_table();

int hash_function(int key);

int insert( int value);

int search( int value);

void print_table();

#endif //HASH_REVIEW_HASHTABLE_H