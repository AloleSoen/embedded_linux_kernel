#include <stdio.h>
#include <pthread.h>

//global variables
int sum = 0;
pthread_mutex_t sum_lock1;
pthread_mutex_t sum_lock2 = PTHREAD_MUTEX_INITIALIZER;
char name[25] = {0};
//Function to be executed by the new thread 
void *sum_thread(void* ptr) {
    int i = 0;
    int n = 50000;
    for(i = 1; i <= n; i++)
    {
        pthread_mutex_lock(&sum_lock1);
        pthread_mutex_lock(&sum_lock2);  

        sum  = sum + i;
        pthread_mutex_unlock(&sum_lock1);
        pthread_mutex_unlock(&sum_lock2);
    }
}
void *sum_thread2(void* ptr) {
    int i = 50000;
    int n = 100000;
    for(i = 50000; i <= n; i++)
    {
        pthread_mutex_lock(&sum_lock1);
        pthread_mutex_lock(&sum_lock2);
        sum  = sum + i;
        pthread_mutex_unlock(&sum_lock1);
        pthread_mutex_unlock(&sum_lock2);
    }
}
void *input_name(void* ptr){
    printf("Nhap ten");
    scanf("%s", name);
}
int main()

{   
    pthread_t thread1, thread2, thread3;
    pthread_mutex_init(&sum_lock1, NULL);
    pthread_mutex_init(&sum_lock2, NULL);
    pthread_create(&thread1, NULL, sum_thread, NULL);
    pthread_create(&thread2, NULL, input_name, NULL);
    pthread_create(&thread3, NULL, sum_thread2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    pthread_mutex_destroy(&sum_lock1);
    pthread_mutex_destroy(&sum_lock2);

    printf("Sum = %d\n", sum);
    return 0;
}