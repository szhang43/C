/* CS 212 Project: Donations (2022)
   ~Always appreciated, never expected, non-refundable~

   Author: S. Isaac Geronimo Anderson (Fall 2022)
   */

#include <stdio.h>   /* printf */
#include <stdlib.h>  /* malloc */
#include <string.h>  /* strcmp */

/* Do not change these values for your submission. */
#define QUEUE_SIZE 12  /* Note: Works with 12 on 3C-input.txt */
#define BLOOD_TYPES 4
#define LINE_LENGTH 80

/* Your code goes below this line. */

char *types[BLOOD_TYPES] = {"AB", "B", "A", "O"};

struct queue
{
	int front; 
	int back; 
	int population; 
	char strings[QUEUE_SIZE][LINE_LENGTH];
};
typedef struct queue Queue;

void initializeQueue(Queue *q){
	q->front = 0; 
	q->back = 0; 
	q->population = 0; 
}

void enqueue(char *str, Queue *q){
	if(q->population == QUEUE_SIZE){
		exit(EXIT_FAILURE);
	}
	strcpy(q->strings[q->back], str);
	q->population++; 
	q->back = (q->back + 1) % QUEUE_SIZE; 
} 

char *dequeue(Queue *q){
	if(q->population == 0){
		exit(EXIT_FAILURE); 
	}
	char *str = q->strings[q->front]; 
	--q->population; 
	q->front = (q->front + 1) % QUEUE_SIZE; 
	return str;
} 

char *getBlood(char *string){
	string+=2;
	char *blood = malloc(sizeof(char)*3);
	int i = 0;
	for(i = 0; string[i] != ':'; ++i){
		blood[i] = string[i];
	}
	blood[i] = '\0';
	return blood;

} 

char *getName(char *string){	
	char *name = malloc(sizeof(char)*30); 
	int i;
	if(strcmp(getBlood(string),  "AB") == 0){
		string += 5;
	}else{
		string += 4;
	}
	for(i = 0; string[i] != '\0'; ++i){
		name[i] = string[i];
	}
	name[i-1] = '\0'; 
	return name;
	
} 

char *getSurgeon(char *string){
	string += 2;
	char *name = malloc(sizeof(char)*30); 
	int i = 0; 
	for(i = 0; string[i] != '\0'; ++i){
		name[i] = string[i]; 
	}
	name[i-1] = '\0';
	return name;
}
	



/* Your code goes above this line. */


/* Here is a suggested helper function for checking blood type
   compatibility. */
int isDonorToRecipient(char *donor, char *recipient)
{
  if (strcmp(donor, "O") == 0 || strcmp(donor, recipient) == 0)
    return 1;
  if (strcmp(donor, "A") == 0 && strcmp(recipient, "AB") == 0)
    return 1;
  if (strcmp(donor, "B") == 0 && strcmp(recipient, "AB") == 0)
    return 1;
  return 0;
}

int getQueue(char *type){
	for(int i = 0; i < BLOOD_TYPES; i++){
		if(strcmp(types[i], type) == 0){
//			printf("Matched type is %s, and recipients blood is %s\n", types[i], recipients);
			return i;
		}
	}
	return 0;
}
			
int SurgeonIsMatch(char *surgeon, Queue **donors, Queue **recipients){
	
	for(int d = 0; d < BLOOD_TYPES; d++){
		for(int r = 0; r < BLOOD_TYPES; r++){
			if(isDonorToRecipient(types[d], types[r])){
				if(donors[d]->population > 0 && (recipients[r]->population > 0)){
					printf("MATCH: %s donates to %s via Dr. %s\n", dequeue(donors[d]), dequeue(recipients[r]), surgeon);
					return 1;
				}
			}
		}
	}
	return 0;
}

int DonorIsMatch(char *blood, char *name, Queue *surgeons, Queue **recipients){
	for(int i = 0; i < BLOOD_TYPES; i++){
		if(isDonorToRecipient(blood, types[i])){
				if(recipients[i]->population > 0 && surgeons->population > 0){
						printf("MATCH: %s donates to %s via Dr. %s\n",
							name, dequeue(recipients[i]), dequeue(surgeons));
						return 1;
				}
		}
	}
	return 0; 
}

int RecipientIsMatch(char *recipient, char *name, Queue *surgeons, Queue **donors){
	for(int i = 0; i < BLOOD_TYPES; i++){
		if(isDonorToRecipient(types[i], recipient)){
			if(donors[i]->population > 0 && surgeons->population > 0){
				printf("MATCH: %s donates to %s via Dr. %s\n", 
					dequeue(donors[i]), name, dequeue(surgeons)); // change recipient blood to recipient name,
				return 1;
			}
		}	
	}
	return 0;
}

/* Uncomment printQueue and prettyPrintQueue when your queue struct
   and functions are implemented. */

void printQueue(struct queue *q)
{
  printf("Printing queue %p\n", q);
  printf("\tThe index for the front of the queue is %d\n", q->front);
  printf("\tThe index for the back of the queue is %d\n", q->back);
  if (q->population == 0)
  {
    printf("\tThe queue is empty.\n");
  }
  else
  {
    for (int i = 0; i < q->population; i++)
    {
      int index = (q->front + i) % QUEUE_SIZE;
      printf("\t\tEntry[%d]: \"%s\"\n", index, q->strings[index]);
    }
  }
}


void prettyPrintQueue(struct queue *q, char *label, char *type)
{
  if (q->population == 0)
  {
    printf("No unmatched entries for %s (%s)\n", label, type);
  }
  else
  {
    printf("Unmatched %s (%s):\n", label, type);
    for (int i = 0; i < q->population; i++)
    {
      int index = (q->front + i) % QUEUE_SIZE;
      printf("%s\n", q->strings[index]);
    }
  }
}


int main(int argc, char **argv)
{
  /***  STEP #1: Implement your queue code and test it.  ***/

  /* This test code: */
 /* 
  struct queue *q = malloc(sizeof (struct queue));
  initializeQueue(q);
  printQueue(q);
  enqueue("hello", q);
  printQueue(q);
  enqueue("world", q);
  printQueue(q);
  printf("Dequeue: %s\n", dequeue(q));
  printQueue(q);
  free(q);
  
   Gives this output (with different pointers):

Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 0
	The queue is empty.
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 1
		Entry[0] = "hello"
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 2
		Entry[0] = "hello"
		Entry[1] = "world"
Dequeue: hello
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 1
	The index for the back of the queue is 2
		Entry[1] = "world"
  */

  /***
    STEP #2: Open the input file (argc/argv stuff).
             You should read the file line-by-line in the next step
             using fgets (or fscanf or getline).
             Note: You must not hard-code the input file name.
             You must not use fread.
             You should exit with an error if file opening fails.
  ***/

  /***
    STEP #3: After your queue code works and after you can read the
             file, implement the prompt.
             Note: Here is the print statement to use for a match:

  printf(
      "MATCH: %s donates to %s via Dr. %s\n",
      donor,
      recipient,
      surgeon);

    You will need four queues for recipients, and four queus for
    donors, so using arrays seems sensible. Suggested declarations
    for these arrays are included below this comment.

  ***/

  /* Here is a suggested helper array for facilitating matching as
    described in the prompt. The blood types are listed from most
    rare to least rare. */

    struct queue *donors[BLOOD_TYPES];
    struct queue *recipients[BLOOD_TYPES];
    struct queue *surgeons = malloc(sizeof (struct queue));

    for(int i = 0; i < BLOOD_TYPES; i++){
	  donors[i] = malloc(sizeof(struct queue)); 
	  recipients[i] = malloc(sizeof(struct queue)); 
    }
	
	FILE *f = fopen(argv[1], "r"); 
	if(f == NULL){
		fprintf(stderr, "Unable to open file %s ... did you copy it to the current directory?\n"); 
		exit(EXIT_FAILURE); 
	} 

	size_t size = LINE_LENGTH; 
	char *buffer = malloc(sizeof(char)*size);
	
	while(getline(&buffer, &size, f) > 0){
		char *string = buffer;
		char type = string[0];
		if(type == 'S'){
			char *name = getSurgeon(string);
			
			if(SurgeonIsMatch(name, donors, recipients) == 0){
				enqueue(name, surgeons);
					
			}

		}
		else if(type == 'R'){
			char *name = getName(string);
			char *blood = getBlood(string); 
			
			if(RecipientIsMatch(blood, name, surgeons, donors) == 0){
				int index = getQueue(blood);
				enqueue(name, recipients[index]);
			}
		}

		else if(type == 'D'){
			char *name = getName(string);
			char *blood = getBlood(string);
		
			if(DonorIsMatch(blood, name, surgeons, recipients) == 0){
				int index = getQueue(blood);	
				enqueue(name, donors[index]);
			}
		}
	}
/*
    STEP #4: After your matching code is done, add prettyPrintQueue
             calls for each of your recipient queues, your donor
             queues, and your surgeon queue. If you used the
             suggested "recipients" and "donors" arrays, and the
             "types" array, then you can use these print statements:
*/
  for (int r = 0; r < BLOOD_TYPES; r++)
    prettyPrintQueue(recipients[r], "recipients", types[r]);
  for (int d = 0; d < BLOOD_TYPES; d++)
    prettyPrintQueue(donors[d], "donors", types[d]);
  prettyPrintQueue(surgeons, "surgeons", "type-agnostic");
/*
             If you did not use arrays for your recipient and donor
             queues, then you should print your recipient queues in
             this order, for example:

  prettyPrintQueue(recipients_AB, "recipients", "AB");
  prettyPrintQueue(recipients_A, "recipients", "B");
  prettyPrintQueue(recipients_B, "recipients", "A");
  prettyPrintQueue(recipients_O, "recipients", "O");

             Then, print your donor queues in the same order, then
             print your surgeon queue.
  ***/

  /* If you have time, be sure to free any memory you allocated. */
  free(surgeons);

  return EXIT_SUCCESS;
}


/* End. */
