#include "hash.h"

#define HEAD 77
#define TAIL 2

void minuscules(char *s)
{
    int i;
    for (i = 0; i < strlen(s); i++) {
        if (((s[i] >=  65) && (s[i] <=  90))
         || ((s[i] >= -64) && (s[i] <= -33))) s[i] += 32;
    }
}

void majuscules(char *s)
{
    int i;
    for (i = 0; i < strlen(s); i++) {
        if (((s[i] >=  97) && (s[i] <= 122))
         || ((s[i] >= -32) && (s[i] <=  -1))) s[i] -= 32;
    }
}

void apostrophe(char *s)
{
    /* supprime les l' d' etc... */
}

char *getTerm(char *term)
{
    /* minuscules(term); */
    /* apostrophe(term); */
    return(strdup(term));
}

int main(int argc, char *argv[])
{
    int i,j,n,nl,nt;
    char term[256],line[256],*p,**list,*prec,*nterm;
    FILE *fp;
    HASH terms;

    /*----------------------*/
    /* On compte les lignes */
    /*----------------------*/
    if ((fp = fopen(argv[1],"rb")) == NULL) exit(1);
    nl = 0;
    while ((!feof(fp)) && (fgets(line,256,fp) == line)) nl++;
    nl -= HEAD+TAIL;
    printf("%d lignes\n",nl);

    /*------------------------------------------*/
    /* On revient au début et on saute l'entête */
    /*------------------------------------------*/
    rewind(fp);
    for (n = 0; n < HEAD; n++) fgets(line,256,fp);

    /*----------------------*/
    /* On compte les termes */
    /*----------------------*/
    nt = 0;
    for (n = 0; n < nl; n++) {
        fgets(line,256,fp);
        p = line;
        while (p[0] == ' ') p++;
        while (sscanf(p,"%s",term) == 1) {
            p += strlen(term);
            while (p[0] == ' ') p++;
            nt++;
        }
    }
    printf("%d termes\n",nt);

    /*----------------------------------------------------*/
    /* On initialise une table de hachage pour les termes */
    /*----------------------------------------------------*/
    hash_init(&terms,nt);
    
    /*------------------------------------------*/
    /* On revient au début et on saute l'entête */
    /*------------------------------------------*/
    rewind(fp);
    for (n = 0; n < HEAD; n++) fgets(line,256,fp);
    
    /*------------------------*/
    /* On récupère les termes */
    /*------------------------*/
    for (n = 0; n < nl; n++) {
        fgets(line,256,fp);
        p = line;
        while (p[0] == ' ') p++;
        while (sscanf(p,"%s",term) == 1) {
            p += strlen(term);
            while (p[0] == ' ') p++;
            nterm = getTerm(term);
            if (nterm[0]) hash_add(nterm,&terms);	    
        }
    }
    
    /*----------------------------*/
    /* On trie la table de termes */
    /*----------------------------*/
    hash_sort(&terms);
    
    /*---------------------------------*/
    /* On récupère la liste des termes */
    /*---------------------------------*/
    nt = hash_entries(&terms);
    list = hash_list(&terms);

    printf("%d termes uniques\n",nt);
    for (i = 0; i < nt; i++) printf("%s\n",list[i]);

    fclose(fp);
    exit(0);
}

