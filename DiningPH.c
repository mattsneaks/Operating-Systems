//Authors: Ronald Kauer & Matthew Kramer & Eduardo Nodarse

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//creates the threads for the philosopher and ChopStick
pthread_t philosopher[5];// = {"Aristotle", "Confucius", "RenÃ© Descartes", "Immanuel Kant","Ralph Waldo Emerson" };
pthread_mutex_t ChopStick[5];

//creates an array for the chopsticks
int status_ChopStick[5] = {1,1,1,1,1};

//function for the philosopher to get chopstick
void getChopStick(int n){
   pthread_mutex_lock(&ChopStick[n]);
   pthread_mutex_lock(&ChopStick[(n+1)%5]);
   status_ChopStick[n] = 0;
}

//function for the philosopher to put chopsticks down
void putChopStick(int n){
   pthread_mutex_unlock(&ChopStick[n]);
   pthread_mutex_unlock(&ChopStick[(n+1)%5]);
   status_ChopStick[n] = 1;
}

//here the philosopher is thinking
void thinking(int n){
   printf ("Philosopher %d is thinking very hard!\n\n",n+1);
   int rNum = rand()%10;
   sleep(rNum);
}   

//looks at status of the chopstick and prints it out
void printChopSticktatus(){
   int i;
   printf("Chopstick status:");
   for(i=0;i<5;i++){
      printf(" %d ", status_ChopStick[i] );
   }
   printf("\n\n");

}

//prints out if the philosopher is eating and gives enough time to finish eating
void eating(int n){
   printf ("Philosopher %d is eating his bowl of rice!\n\n",n+1);
   printChopSticktatus();
   int rNum = rand()%10;
   sleep(rNum);
} 

void *foods(int n){   
    while(1){
        thinking(n);
        getChopStick(n);
        eating(n);
        putChopStick(n);
    }
}

void start_foods(){
   int i;

   for(i=0;i<5;i++){
      pthread_mutex_init(&ChopStick[i],NULL);
   }
   
   for(i=0;i<5;i++){
    pthread_create(&philosopher[i],NULL,(void *)foods, (void*)(intptr_t)i);
   }
    
   for(i=0;i<5;i++){
      pthread_join(philosopher[i],NULL);
   }
}


int main()
{

  start_foods();
  return 0;

}