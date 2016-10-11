#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_


   								
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct _dictionary_ {
	int				n ;		/** Number of entries in dictionary */
	int				size ;	/** Storage size */
	char 		**	val ;	/** List of string values */
	char 		**  key ;	/** List of string keys */
	unsigned	 *	hash ;	/** List of hash values for keys */
} dictionary ;


//����KEY�Ĺ�ϣֵ
unsigned dictionary_hash(char * key);
//����һ���ֵ�
dictionary * dictionary_new(int size);

void dictionary_del(dictionary * vd);

//��ȡ��ֵ��
char * dictionary_get(dictionary * d, char * key, char * def);

//���ü�ֵ��
int dictionary_set(dictionary * vd, char * key, char * val);

void dictionary_unset(dictionary * d, char * key);

//�����ֵ�����ļ�ֵ�Ե��ļ����Ǳ�׼���
void dictionary_dump(dictionary * d, FILE * out);

#endif
