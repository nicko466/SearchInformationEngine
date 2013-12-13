/*------------------------------------------------------------------------------------*/
/*  Copyright (C) 2004  Georges QUENOT  CLIPS-IMAG                                    */
/*  Version 2.03 Last revision: 6 april, 2006                                         */
/*  Free use of this software is hereby granted for educational                       */
/*  and research purposes.                                                            */
/*------------------------------------------------------------------------------------*/

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------------------------------------------*/

#ifndef FAILURE
#define FAILURE 0
#define SUCCESS 1
#endif

/*------------------------------------------------------------------------------------*/

typedef struct {
  char *term;
  int next;
  int count;
} CELL;

typedef struct {
  int size;
  int *hash;
  int next;
  int len;
  CELL *cell;
} HASH;

typedef struct {
  char *term;
  int count;
} SORT;

/*------------------------------------------------------------------------------------*/

int hash_func(char *term, int size);
int hash_init(HASH *hash, int size);
int hash_test(char *term, HASH *hash);
int hash_addn(char *term, HASH *hash, int n);
int hash_add(char *term, HASH *hash);
int hash_num(char *term, HASH *hash);
int hash_entries(HASH *hash);
char *hash_term(HASH *hash, int i);
char **hash_list(HASH *hash);
int *hash_lcnt(HASH *hash);
void hash_free(HASH *hash, int terms);
int hash_sort(HASH *hash);
int hash_add2(char *term0, char *term1, HASH *hash);
int hash_num2(char *term0, char *term1, HASH *hash);
int hash_add3(char *term0, char *term1, char *term2, HASH *hash);
int hash_num3(char *term0, char *term1, char *term2, HASH *hash);

/*------------------------------------------------------------------------------------*/
