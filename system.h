#define MAX_CPU_USE 0.8
#define MAX_MEMORY_USE 0.8
#define MAX_FLASH_USE 0.6
/*

user 
 ��ϵͳ������ʼ�ۼƵ���ǰʱ�̣��û�̬��CPUʱ�䣬������ niceֵΪ�����̡�
 
nice 
 ��ϵͳ������ʼ�ۼƵ���ǰʱ�̣�niceֵΪ���Ľ�����ռ�õ�CPUʱ��
 
system 
 ��ϵͳ������ʼ�ۼƵ���ǰʱ�̣�����ʱ��
 
idle 
 ��ϵͳ������ʼ�ۼƵ���ǰʱ�̣���IO�ȴ�ʱ�����������ȴ�ʱ��
 
iowait
 ��ϵͳ������ʼ�ۼƵ���ǰʱ�̣�IO�ȴ�ʱ��
 
irq 
 ��ϵͳ������ʼ�ۼƵ���ǰʱ�̣�Ӳ�ж�ʱ��
 
softirq 
 ��ϵͳ������ʼ�ۼƵ���ǰʱ�̣����ж�ʱ��

*/

typedef struct{
	unsigned int user;
	unsigned int system;
	unsigned int nice;
	unsigned int idle;
	unsigned int iowait;
	unsigned int hardirq;
	unsigned int softirq;
	unsigned int st;
}proc_stat_t;

typedef struct tag_cmts_system{
	unsigned char cpu;
	unsigned char memory;
	unsigned char flash;
	unsigned char reserved;
/*
    unsigned char min_mem;
    unsigned char max_mem;
    unsigned int min_mem_time;
    unsigned int max_mem_time;

    unsigned char min_cpu;
    unsigned char max_cpu;
    unsigned int min_cpu_time;
    unsigned int max_cpu_time;

    unsigned char min_flash;
    unsigned char max_flash;
    unsigned int min_flash_time;
    unsigned int max_flash_time;
 */
}cmts_system;

int check_system(cmts_system *sys);




