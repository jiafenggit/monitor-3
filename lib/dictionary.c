
#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXVALSZ	1024

#define DICTMINSZ	128

#define DICT_INVALID_KEY    ((char*)-1)


static void * mem_double(void * ptr, int size)
{
    void * newptr ;
 
    newptr = calloc(2*size, 1);
    if (newptr==NULL) {
        return NULL ;
    }
    memcpy(newptr, ptr, size);
    free(ptr);
    return newptr ;
}

static char * xstrdup(char * s)
{
    char * t ;
    if (!s)
        return NULL ;
    t = malloc(strlen(s)+1) ;
    if (t) {
        strcpy(t,s);
    }
    return t ;
}

unsigned dictionary_hash(char * key)
{
	int			len ;
	unsigned	hash ;
	int			i ;

	len = strlen(key);
	for (hash=0, i=0 ; i<len ; i++) {
		hash += (unsigned)key[i] ;
		hash += (hash<<10);
		hash ^= (hash>>6) ;
	}
	hash += (hash <<3);
	hash ^= (hash >>11);
	hash += (hash <<15);
	return hash ;
}

dictionary * dictionary_new(int size)
{
	dictionary	*	d ;

	if (size<DICTMINSZ) size=DICTMINSZ ;

	if (!(d = (dictionary *)calloc(1, sizeof(dictionary)))) {
		return NULL;
	}
	d->size = size ;
	d->val  = (char **)calloc(size, sizeof(char*));
	d->key  = (char **)calloc(size, sizeof(char*));
	d->hash = (unsigned int *)calloc(size, sizeof(unsigned));
	return d ;
}


void dictionary_del(dictionary * d)
{
	int		i ;

	if (d==NULL) return ;
	for (i=0 ; i<d->size ; i++) {
		if (d->key[i]!=NULL)
			free(d->key[i]);
		if (d->val[i]!=NULL)
			free(d->val[i]);
	}
	free(d->val);
	free(d->key);
	free(d->hash);
	free(d);
	return ;
}


char * dictionary_get(dictionary * d, char * key, char * def)
{
	unsigned	hash ;
	int			i ;

	hash = dictionary_hash(key);
	for (i=0 ; i<d->size ; i++) {
        if (d->key[i]==NULL)
            continue ;
     
		if (hash==d->hash[i]) {
         
            if (!strcmp(key, d->key[i])) {
				return d->val[i] ;
			}
		}
	}
	return def ;
}


int dictionary_set(dictionary * d, char * key, char * val)
{
	int			i ;
	unsigned	hash ;
	if (d==NULL || key==NULL) 
		return -1 ;
	
	/* Compute hash for this key */
	hash = dictionary_hash(key) ;
	/* Find if value is already in dictionary */
	if (d->n>0) 
	{
		for (i=0 ; i<d->size ; i++) 
		{
            		if (d->key[i]==NULL)
                		continue ;
			if (hash==d->hash[i]) 
			{ 
				if (!strcmp(key, d->key[i])) 
				{	
			
					if (d->val[i]!=NULL)
						free(d->val[i]);
                    			d->val[i] = val ? xstrdup(val) : NULL ;
                
					return 0 ;
				}
			}
		}
	}
	if (d->n==d->size) {

		d->val  = (char **)mem_double(d->val,  d->size * sizeof(char*)) ;
		d->key  = (char **)mem_double(d->key,  d->size * sizeof(char*)) ;
		d->hash = (unsigned int *)mem_double(d->hash, d->size * sizeof(unsigned)) ;
        if ((d->val==NULL) || (d->key==NULL) || (d->hash==NULL)) {
            return -1 ;
        }
		/* Double size */
		d->size *= 2 ;
	}

    for (i=0 ; i<d->size ; i++) {
        if (d->key[i]==NULL) {
            /* Add key here */
            break ;
        }
    }
	d->key[i]  = xstrdup(key);
    	d->val[i]  = val ? xstrdup(val) : NULL ;
	d->hash[i] = hash;
	d->n ++ ;
	return 0 ;
}


void dictionary_unset(dictionary * d, char * key)
{
	unsigned	hash ;
	int			i ;

	if (key == NULL) {
		return;
	}

	hash = dictionary_hash(key);
	for (i=0 ; i<d->size ; i++) 
	{
       		if (d->key[i]==NULL)
            		continue ;
		if (hash==d->hash[i]) 
		{
			if (!strcmp(key, d->key[i])) 
			{
	                	break ;
			}
		}
	}
	if (i>=d->size)
		/* Key not found */
		return ;

	free(d->key[i]);
	d->key[i] = NULL ;
	if (d->val[i]!=NULL) 
	{
		free(d->val[i]);
		d->val[i] = NULL ;
	}
	d->hash[i] = 0 ;
	d->n -- ;
    	return ;
}

void dictionary_dump(dictionary * d, FILE * out)
{
	int		i ;

	if (d==NULL || out==NULL) return ;
	if (d->n<1) {
		fprintf(out, "empty dictionary\n");
		return ;
	}
	for (i=0 ; i<d->size ; i++) {
        if (d->key[i]) {
            fprintf(out, "%20s\t[%s]\n",
                    d->key[i],
                    d->val[i] ? d->val[i] : "UNDEF");
        }
	}
	return ;
}


