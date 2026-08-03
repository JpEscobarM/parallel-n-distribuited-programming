//
// Created by jmartins on 03/08/2026.
//
#include <assert.h>
#include <stdio.h>
#include "hashTable.h"

static void test_search_empty_table(void)
{
    init_table();

    assert(search(10) == -1);
}

static void test_insert_and_search(void)
{
    init_table();

    assert(insert(7) == 1);
    assert(search(7) == hash_function(7));
}

static void test_duplicate_value(void)
{
    init_table();

    assert(insert(12) == 1);
    assert(insert(12) == 0);
}

static void test_collision(void)
{
    init_table();

    int first = 5;
    int second = first + TAM;

    assert(hash_function(first) == hash_function(second));

    assert(insert(first) == 1);
    assert(insert(second) == 1);

    assert(search(first) == 5);
    assert(search(second) == 6);
}

static void test_wrap_around(void)
{
    init_table();

    int first = TAM - 1;
    int second = first + TAM;

    assert(insert(first) == 1);
    assert(insert(second) == 1);

    assert(search(first) == TAM - 1);
    assert(search(second) == 0);
}

static void test_full_table(void)
{
    init_table();

    for (int i = 0; i < TAM; i++) {
        assert(insert(i) == 1);
    }

    assert(insert(1000) == 0);
}

static void test_reinitialize_table(void)
{
    init_table();

    assert(insert(25) == 1);
    assert(search(25) != -1);

    init_table();

    assert(search(25) == -1);
}

int main(void)
{
    test_search_empty_table();
    test_insert_and_search();
    test_duplicate_value();
    test_collision();
    test_wrap_around();
    test_full_table();
    test_reinitialize_table();

    printf("\nAll hash table tests passed.\n");

    return 0;
}