#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
struct process{
   	int process_number,arrival_time,burst_time,priority;
};
static struct process process_queue[10],Ready_queue[10];
int x=0,GanttChart[2][100];
int front=0,rear=-1,no_of_process;

void arrive_process(int time){

           for(int i=0;i<no_of_process;i++)
            if(time==0){
            if(process_queue[i].arrival_time<=time){
            	rear++;
           	Ready_queue[rear]=process_queue[i];
		   }}
			else{
           	if(x<process_queue[i].arrival_time && process_queue[i].arrival_time<=time){
           	rear++;
			   Ready_queue[rear]=process_queue[i];
		   }}
		   x=time;
}


void sort_on_priority(){
	int i, j,max;  
	struct process temp;

for (i = front; i <=rear-1; i++)  {
	max=i;  
    for (j =i+1; j <=rear; j++) 
        if (Ready_queue[j].priority>Ready_queue[max].priority) {
        	max=j;
		} 
            if(max!=i){
            temp=Ready_queue[i];
			Ready_queue[i]=Ready_queue[max]	;
			  Ready_queue[max]=temp; 
					}}

}

int process_Execution(int quantum,int total){
	int clock=0,p=0,index=0;
	while( p<total){
		if(front>rear){
		arrive_process(index);
		sort_on_priority();
		}
   if(Ready_queue[front].process_number==0){		
    index=index+1;
	}
		
	else if(Ready_queue[front].burst_time<=quantum){
		GanttChart[0][clock]=Ready_queue[front].process_number;
		index=index+Ready_queue[front].burst_time;
		p=p+Ready_queue[front].burst_time;
		GanttChart[1][clock]=index;
		front++;
		}
		else{		
		GanttChart[0][clock]=Ready_queue[front].process_number;
		index=index+quantum;
		p=p+quantum;
		GanttChart[1][clock]=index;
		Ready_queue[front].burst_time=Ready_queue[front].burst_time-quantum;
		arrive_process(index);
		rear++;
		Ready_queue[rear]=Ready_queue[front];
		front++;	
		sort_on_priority();
		}
		clock++;
	}
return clock;	
}



int main(){
   static int i,quantum,total=0,j,p=0,completion_time[10],arrival[10],turnaround_t[10],waiting_t[10],burst_t[10];
   float avg=0;
	struct process user;
	printf("Enter the detail of process:\n");
	printf("Enter the no of process:");
	scanf("%d",&no_of_process);
	printf("Enter the quantum time:");
	scanf("%d",&quantum);
	for(i=0;i<no_of_process;i++){
	user.process_number=i+1;
	printf("Enter the arrival_time of process N. %d :",i+1);
	scanf("%d",&user.arrival_time);
	printf("Enter the burst_time:");
	scanf("%d",&user.burst_time);
	total=total+user.burst_time;
	printf("Enter the priority:");
	scanf("%d",&user.priority);
	process_queue[i]=user;	
	}
	p=process_Execution(quantum,total);
	
	for(i=0;i<no_of_process;i++){
	for (j = 0; j <p; j++)
		if(GanttChart[0][j]==i+1)		
	completion_time[i]=GanttChart[1][j];
	
	arrival[i]=process_queue[i].arrival_time;	
	burst_t[i]=process_queue[i].burst_time;
      }	
	for(i=0;i<no_of_process;i++){		
	turnaround_t[i]=completion_time[i] - arrival[i];
	waiting_t[i]=turnaround_t[i] - burst_t[i];
	avg=avg+waiting_t[i];}
	
printf("Process ID \t Completion Time \t Turnaround Time \t Waiting Time\n");	
	for(i=0;i<no_of_process;i++)
	printf("\t%d\t\t%d\t\t\t%d\t\t\t%d\n",i+1,completion_time[i],turnaround_t[i],waiting_t[i]);

	avg=avg/no_of_process;
	printf("\n\nSequence of Execution:");
for (j = 0; j <p; j++)	
	printf("--> %d",GanttChart[0][j]);
printf("\n\n\nAverage Waiting Time: %.2f\n",avg);	
		
}
