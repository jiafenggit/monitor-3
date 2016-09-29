#ifndef _PROCESS_H_
#define _PROCESS_H_
#define PROCES "/proc"
#define MAX_SIZE 256
#define DEBUG 0

#include "vns_list.h"

#if DEBUG
#define myprintf(fmt, args...)    printf("%s,%s(),%d:" fmt "\n", __FILE__,__FUNCTION__,__LINE__, ##args)
#else 
#define myprintf(fmt, args...)    
#endif



//���̽ṹ�嶨��
struct process_info
{
 	char name[MAX_SIZE];//��������
 	char cmdline[MAX_SIZE];//�����У�ִ�������ַ���
 	int pid;
	struct list_head list;
};

int check_proc(struct process_info* array);
int proc_find(struct process_info* src,struct process_info* dest);
int get_proc(struct list_head* ghead, char* file);
int startProc(struct process_info* proc);
int creat_and_run_moniter(char *file);
static  int IsDigit(char a[]);
#endif

