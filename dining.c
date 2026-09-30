#include"header.h"
void main()
{
        int id=semget(10,5,IPC_CREAT|0664);
        if(id<0)
        {
                perror("semget");
                return;
        }
        struct sembuf v[2];
        for(int i=0;i<5;i++)
                semctl(id,i,SETVAL,0);
        for(int i=0; i<5; i++)
                printf("fork %d avaliable\n", i+1);
        if(fork()==0)
        {
                v[0].sem_num=0;
                v[0].sem_op=0;
                v[0].sem_flg=SEM_UNDO;
                v[1].sem_flg=SEM_UNDO;
                v[1].sem_num=1;
                v[1].sem_op=0;
                printf("------Philosopher 1 is waiting------\n");
                semop(id,v,2);
                semctl(id,0,SETVAL,1);
                semctl(id,1,SETVAL,1);
                printf("\033[31mPhilosopher 1 eating\n");
                printf("Philosopher 1 is using fork 5 and 1\033[0m\n");
                sleep(10);
                printf("\033[32mfork 5 and 1 are avalible\n");
                printf("Philosopher 1 done eating\033[0m\n");
                semctl(id,0,SETVAL,0);
                semctl(id,1,SETVAL,0);
                exit(0);
        }
        else
        {
                if(fork()==0)
                {
                        v[0].sem_num=1;
                        v[0].sem_op=0;
                        v[0].sem_flg=SEM_UNDO;
                        v[1].sem_flg=SEM_UNDO;
                        v[1].sem_num=2;
                        v[1].sem_op=0;
                        printf("------Philosopher 2 is waiting------\n");
                        semop(id,v,2);
                        semctl(id,1,SETVAL,1);
                        semctl(id,2,SETVAL,1);
                        printf("\033[31mPhilosopher 2 eating\n");
                        printf("Philosopher 2 is using fork 1 and 2\033[0m\n");
                        sleep(10);
                        printf("\033[32mfork 1 and 2 are avalible\n");
                        printf("Philosopher 2 done eating\033[0m\n");
                        semctl(id,1,SETVAL,0);
                        semctl(id,2,SETVAL,0);
                        exit(0);
                }
                else
                {
                        if(fork()==0)
                        {
                                v[0].sem_num=2;
                                v[0].sem_op=0;
                                v[0].sem_flg=SEM_UNDO;
                                v[1].sem_flg=SEM_UNDO;
                                v[1].sem_num=3;
                                v[1].sem_op=0;
                                printf("------Philosopher 3 is waiting------\n");
                                semop(id,v,2);
                                semctl(id,2,SETVAL,1);
                                semctl(id,3,SETVAL,1);
                                printf("\033[31mPhilosopher 3 eating\n");
                                printf("Philosopher 3 is using fork 2 and 3\033[0m\n");
                                sleep(10);
                                printf("\033[32mfork 2 and 3 are avalible\n");
                                printf("Philosopher 3 done eating\033[0m\n");
                                semctl(id,2,SETVAL,0);
                                semctl(id,3,SETVAL,0);
                                exit(0);
                        }
                        else
                        {
                                if(fork()==0)
                                {
                                        v[0].sem_num=3;
                                        v[0].sem_op=0;
                                        v[0].sem_flg=SEM_UNDO;
                                        v[1].sem_flg=SEM_UNDO;
                                        v[1].sem_num=4;
                                        v[1].sem_op=0;
                                        printf("------Philosopher 4 is waiting------\n");
                                        semop(id,v,2);
                                        semctl(id,3,SETVAL,1);
                                        semctl(id,4,SETVAL,1);
                                        printf("\033[31mPhilosopher 4 eating\n");
                                        printf("Philosopher 4 is using fork 3 and 4\033[0m\n");
                                        sleep(10);
                                        printf("\033[32mfork 3 and 4 are avalible\n");
                                        printf("Philosopher 4 done eating\033[0m\n");
                                        semctl(id,3,SETVAL,0);
                                        semctl(id,4,SETVAL,0);
                                        exit(0);
                                }
                                else
                                {
                                        if(fork()==0)
                                        {
                                                v[0].sem_num=4;
                                                v[0].sem_op=0;
                                                v[0].sem_flg=SEM_UNDO;
                                                v[1].sem_flg=SEM_UNDO;
                                                v[1].sem_num=0;
                                                v[1].sem_op=0;
                                                printf("------Philosopher 5 is waiting------\n");
                                                semop(id,v,2);
                                                semctl(id,4,SETVAL,1);
                                                semctl(id,0,SETVAL,1);
                                                printf("\033[31mPhilosopher 5 eating\n");
                                                printf("Philosopher 5 is using fork 4 and 5\033[0m\n");
                                                sleep(10);
                                                printf("\033[32mfork 4 and 5 are avalible\n");
                                                printf("Philosopher 5 done eating\n");
                                                semctl(id,4,SETVAL,0);
                                                semctl(id,0,SETVAL,0);
                                                exit(0);
                                        }
                                        else
                                        {
                                                wait(0);
                                                wait(0);
                                                wait(0);
                                                wait(0);
                                                wait(0);
                                                semctl(id, 0, IPC_RMID);
                                        }
                                }
                        }
                }
        }

}
