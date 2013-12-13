/*------------------------------------------------------------------------------------*/
/*  Copyright (C) 2004  Georges QUENOT  CLIPS-IMAG                                    */
/*  Version 2.03 Last revision: 6 april, 2006                                         */
/*  Free use of this software is hereby granted for educational                       */
/*  and research purposes.                                                            */
/*------------------------------------------------------------------------------------*/

#include "hash.h"

/*------------------------------------------------------------------------------------*/

int hash_func(char *term, int size)
{
  unsigned long long h;
  for (h = 0; *term; term++) h =1664525*h+1013904223+((unsigned) (*term));
  return((int) (h % size));
}

int hash_init(HASH *hash, int size)
{
  int i;
  hash->size = size;
  if ((hash->hash = (int *) malloc(size*sizeof(int))) == NULL) {
    fprintf(stderr,"Error: malloc failed for hash_init\n");
    return(FAILURE);
  }
  for (i = 0; i < size; i++) hash->hash[i] = -1;
  hash->next = 0;
  hash->len = 0;
  hash->cell = NULL;
  return(SUCCESS);
}

int hash_test(char *term, HASH *hash)
{
  int *i;
  i = hash->hash+hash_func(term,hash->size);
  while ((*i >= 0) && strcmp(term,hash->cell[*i].term)) i = &(hash->cell[*i].next);
  return ((*i < 0) ? 0 : hash->cell[*i].count);
}

int hash_addn(char *term, HASH *hash, int n)
{
  int *i;
  i = hash->hash+hash_func(term,hash->size);
  while ((*i >= 0) && strcmp(term,hash->cell[*i].term)) i = &(hash->cell[*i].next);
  if (*i < 0) {
    if (hash->next >= hash->len) {
      hash->cell = (CELL *) realloc(hash->cell,(hash->len += 256)*sizeof(CELL));
      if (hash->cell == NULL) {
        fprintf(stderr,"Error: malloc failed for hash_new\n");
        return(FAILURE);
      }
      i = hash->hash+hash_func(term,hash->size);
      while ((*i >= 0) && strcmp(term,hash->cell[*i].term)) i = &(hash->cell[*i].next);
    }
    hash->cell[hash->next].term = strdup(term);
    hash->cell[hash->next].next = -1;
    hash->cell[hash->next].count = 0;
    *i = hash->next;
    hash->next += 1;
  }
  hash->cell[*i].count += n;
  return(SUCCESS);
}

int hash_add(char *term, HASH *hash)
{
  int *i;
  i = hash->hash+hash_func(term,hash->size);
  while ((*i >= 0) && strcmp(term,hash->cell[*i].term)) i = &(hash->cell[*i].next);
  if (*i < 0) {
    if (hash->next >= hash->len) {
      hash->cell = (CELL *) realloc(hash->cell,(hash->len += 256)*sizeof(CELL));
      if (hash->cell == NULL) {
        fprintf(stderr,"Error: malloc failed for hash_new\n");
        return(FAILURE);
      }
      i = hash->hash+hash_func(term,hash->size);
      while ((*i >= 0) && strcmp(term,hash->cell[*i].term)) i = &(hash->cell[*i].next);
    }
    hash->cell[hash->next].term = strdup(term);
    hash->cell[hash->next].next = -1;
    hash->cell[hash->next].count = 0;
    *i = hash->next;
    hash->next += 1;
  }
  hash->cell[*i].count += 1;
  return(SUCCESS);
}

int hash_num(char *term, HASH *hash)
{
  int *i;
  i = hash->hash+hash_func(term,hash->size);
  while ((*i >= 0) && strcmp(term,hash->cell[*i].term)) i = &(hash->cell[*i].next);
  return (*i);
}

int hash_entries(HASH *hash)
{
  return(hash->next);
}

char *hash_term(HASH *hash, int i)
{
  return(hash->cell[i].term);
}

char **hash_list(HASH *hash)
{
  int i,m;
  char **list;
  if ((m = hash->next) == 0) return(NULL);
  if ((list = (char **) malloc(m*sizeof(char *))) == NULL) return(NULL);
  for (i = 0; i < hash->next; i++) list[i] = hash_term(hash,i);
  return(list);
}

int *hash_lcnt(HASH *hash)
{
  int i,m,*lcnt;
  if ((m = hash->next) == 0) return(NULL);
  if ((lcnt = (int *) malloc(m*sizeof(int))) == NULL) return(NULL);
  for (i = 0; i < hash->next; i++) lcnt[i] = hash->cell[i].count;
  return(lcnt);
}

void hash_free(HASH *hash, int terms)
{
  int i;
  if (terms) for (i = 0; i < hash->next; i++) free(hash->cell[i].term);
  if (hash->cell) free(hash->cell); hash->cell = NULL;
  free(hash->hash); hash->hash = NULL;
}

int termCompare(const void *t1, const void *t2)
{
  return(strcmp(((SORT *)t1)->term,((SORT *)t2)->term));
}

int hash_sort(HASH *hash)
{
  int i,size,entries;
  SORT *sort;
  size = hash->size;
  entries = hash_entries(hash);
  if ((sort = (SORT *) malloc(entries*sizeof(SORT))) == FAILURE) return(FAILURE);
  for (i = 0; i < entries; i++) {
    sort[i].term = hash_term(hash,i);
    sort[i].count = hash_test(hash_term(hash,i),hash);
  }
  hash_free(hash,0);
  qsort(sort,entries,sizeof(SORT),termCompare);
  hash_init(hash,size);
  for (i = 0; i < entries; i++) {
    hash_addn(sort[i].term,hash,sort[i].count);
    free(sort[i].term);
  }
  free (sort);
  return(SUCCESS);
}

/*------------------------------------------------------------------------------------*/

char *hash_term2(char *term0, char *term1)
{
  char *term;
  term = (char *) malloc((strlen(term0)+strlen(term1)+2)*sizeof(char));
  if (term) sprintf(term,"%s_%s",term0,term1);
  return(term);
}

int hash_add2(char *term0, char *term1, HASH *hash)
{
  char *term;
  if ((term = hash_term2(term0,term1)) == NULL) return(FAILURE);
  if (hash_add(term,hash) == FAILURE) return(FAILURE);
  free(term);
  return(SUCCESS);
}

int hash_num2(char *term0, char *term1, HASH *hash)
{
  int k;
  char *term;
  if ((term = hash_term2(term0,term1)) == NULL) return(-1);
  k = hash_num(term,hash);
  free(term);
  return(k);
}

/*------------------------------------------------------------------------------------*/

char *hash_term3(char *term0, char *term1, char *term2)
{
  char *term;
  term = (char *) malloc((strlen(term0)+strlen(term1)+strlen(term2)+3)*sizeof(char));
  if (term) sprintf(term,"%s_%s_%s",term0,term1,term2);
  return(term);
}

int hash_add3(char *term0, char *term1, char *term2, HASH *hash)
{
  char *term;
  if ((term = hash_term3(term0,term1,term2)) == NULL) return(FAILURE);
  if (hash_add(term,hash) == FAILURE) return(FAILURE);
  free(term);
  return(SUCCESS);
}

int hash_num3(char *term0, char *term1, char *term2, HASH *hash)
{
  int k;
  char *term;
  if ((term = hash_term3(term0,term1,term2)) == NULL) return(-1);
  k = hash_num(term,hash);
  free(term);
  return(k);
}

/*------------------------------------------------------------------------------------*/
