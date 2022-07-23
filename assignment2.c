/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* declare global variables including a table structure to hold scheduling information */
struct node {
int id;
int arrival;
int total_cpu;
int total_remaining;
int done;
int start_time;
int already_started;
int end_time;
int turnaround_time;
}
*table = NULL;
typedef struct node table_type;
int num_process;

/* optional: define a function that finds the maximum of two integers */
#define max(a,b) (a > b ? a : b)

/***************************************************************/
void printing() {
	
	/* declare local variables */
   
   int process1 = num_process;
	/* print table header */	
   printf("\nID\tArrival\tTotal\tStart\tEnd\tTurnaround\n");
   printf("--------------------------------------------------------------------- \n");
	/* for each process */
		/* print the contents (id, arrival time, total_cycles) of each field of the table's index */
   for (int i=0; i < process1; i++) {
      printf("%d\t%d\t%d\t", table[i].id, table[i].arrival, table[i].total_cpu);
      
		/* if process has been scheduled ("done" field is 1, print other contents (start time, end time, turnaround time) */
      if (table[i].done==1) {
         printf("%d\t%d\t%d", table[i].start_time, table[i].end_time, table[i].turnaround_time);

         
     
      } 
      printf("\n");
      }

	return;
}


/***************************************************************/
void option1() {
	
	/* declare local variables */
   

	/* prompt for total number of processes */	
   printf("Enter total number of processes:  ");
   scanf("%d", &num_process);
	
	/* allocate memory for table to hold process parameters */
   table = (table_type*)malloc(num_process*sizeof(table_type));

	/* for each process */
		/* prompt for process id, arrival time, and total cycle time */	
   for (int i=0; i < num_process; i++) {

      printf("Enter process id:  ");
      scanf("%d", &table[i].id );
     
      printf("Enter arrival time:  ");
      scanf("%d", &table[i].arrival);
     
      printf("total cycle time:  ");
      scanf("%d", &table[i].total_cpu);
     
  }

	/* print contents of table */
    printing();

	return;		
}	
		

/***************************************************************/
void option2() {

	/* declare (and initilize when appropriate) local variables */
	
	int min_value;
	int current_cycle=0;
	int local_num = num_process;
	int min_index;

	/* for each process, reset "done" field to 0 */
	for (int i=0; i < num_process; i++) {
	     
            table[i].done=0;
       }


	/* while there are still processes to schedule */	
		/* initilize the earliest arrival time to INT_MAX (largest integer value) */
    while (local_num != 0) {
        min_value= INT_MAX;
    
		/* for each process not yet scheduled */
			/* check if process has earlier arrival time than current earliest and update */
		for (int i=0; i < num_process; i++) {

		   if (table[i].done==0) {
		       if (table[i].arrival < min_value) {
		          min_value= table[i].arrival;
		          min_index=i;
		        
		    }
		}
		    
		}

		/* set start time, end time, turnaround time, done fields for unscheduled process with earliest arrival time */  
		table[min_index].start_time = max(current_cycle, min_value);
		table[min_index].end_time = table[min_index].start_time + table[min_index].total_cpu;
		table[min_index].turnaround_time = table[min_index].end_time - table[min_index].arrival;
		table[min_index].done = 1;

		/* update current cycle time and increment number of processes scheduled */
		current_cycle = table[min_index].end_time;
		local_num -=1;
      }

	/* print contents of table */
	 printing();
	

	 return;		
}	


/***************************************************************/
void option3() {

	/* declare (and initilize when appropriate) local variables */
   int num_done=0;
   int min_value;
   int min_index;
   int current_cycle=0; 
   int local_num = num_process;

	/* for each process, reset "done" field to 0 */
   for (int i=0; i < num_process; i++) {
       table[i].done=0;
   }
	/* while there are still processes to schedule */	
   while (local_num != 0) {
		/* initilize the lowest total cycle time to INT_MAX (largest integer value) */
      min_value = INT_MAX;
		/* for each process not yet scheduled */
	   for (int i=0; i < num_process; i++) {

		   if (table[i].done==0) {      
			/* check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update */	
            if ((table[i].total_cpu < min_value) && (table[i].arrival <= current_cycle)) {
            min_value = table[i].total_cpu;
            min_index = i;
            
            }}}

		/* set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time */
        table[min_index].start_time = current_cycle;
		table[min_index].end_time = table[min_index].start_time + table[min_index].total_cpu;
		table[min_index].turnaround_time = table[min_index].end_time - table[min_index].arrival;
		table[min_index].done =1;
       	

		/* update current cycle time and increment number of processes scheduled */
      current_cycle = table[min_index].end_time;
      local_num -=1;
}
	/* print contents of table */
	printing();

	return;		
}
	
        	

/***************************************************************/
void option4() {

	/* declare (and initilize when appropriate) local variables */
   /*int num_done=0; */
   int min_value;
   int min_index;
   int current_cycle=0;
   int local_num = num_process;

	/* for each process, reset "done", "total_remaining" and "already_started" fields to 0 */
   for (int i=0; i < num_process; i++) {
       table[i].done = 0;
       table[i].total_remaining = table[i].total_cpu;
       table[i].already_started = 0;
   }
	/* while there are still processes to schedule */	
   while (local_num !=0) {
		/* initilize the lowest total remaining time to INT_MAX (largest integer value) */
      min_value = INT_MAX;

		/* for each process not yet scheduled */
	   for (int i=0; i < num_process; i++) {   
			/* check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update */	
         if (table[i].done == 0) {
             if ( (table[i].total_remaining < min_value) && (table[i].arrival <= current_cycle)) {
                min_value = table[i].total_remaining;
                min_index = i;
                }}}
		/* check if process already partially-scheduled */
			/* if so, set "start time", "already_started" fields of process with lowest (and available) total remaining cycle time */       	
		if (table[min_index].already_started ==0) {
           table[min_index].start_time = current_cycle;
		     table[min_index].already_started =1;
      }
     
		/* set end time, turnaround time of process with lowest (and available) total remaining cycle time */
        table[min_index].end_time = current_cycle + 1;
        table[min_index].turnaround_time = table[min_index].end_time - table[min_index].arrival;
           

		/* decrement total remaining time of process with lowest (and available) total remaining cycle time */
        table[min_index].total_remaining--;
        current_cycle ++;
		/* if remaining time is 0, set done field to 1, increment cycle time and number of scheduled processes*/
      if (table[min_index].total_remaining == 0) {
         table[min_index].done = 1;
         local_num -= 1;
      }}
	/* print contents of table */
   printing();

	return;		
}	
        	

/***************************************************************/
void option5() {

	/* free the schedule table if not NULL */
   if (table != NULL) {
      free(table);
   }
   return;
   }


/***************************************************************/
int main() {
	/* declare local vars */

	/* while user has not chosen to quit */
		/* print menu of options */
		/* prompt for menu selection */

		/* call appropriate procedure based on choice--use switch statement or series of if, else if, else statements */	
	 /* while loop */
  int choice = 0;
  
  while (choice != 5) {
     printf("\nBatch scheduling\n");
     printf("--------------------------------\n");
     printf("1) Enter parameters\n");
     printf("2) Schedule processes with FIFO algorithm\n");
     printf("3) Schedule processes with SJF algorithm\n");
     printf("4) Schedule processes with SRT algorithm\n");
     printf("5) Quit and free memory\n");

     printf("\nEnter selection: ");
     scanf("%d", &choice);
    
     switch(choice) {
        case 1: option1();
        break;
        case 2:option2();
        break;
        case 3:option3(); 
        break;
        case 4:option4(); 
        break;
        case 5:option5;
        printf("\nQuitting program\n");
        break;
        default: 
        printf("Invalid option!\n"); 
        break;
     }    
   }    

	 return 1; /* indicates success */
} /* end of procedure */

