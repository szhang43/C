/*
 How do dictionaries based on arrays compare with dictionaries based on hash tables? 
 
 In a dictionary using an array, we are implementing the dictionary in a linear order. Meaning
 we would move to the next available index to store the key and value. We simply compute i + 1 
 in order to find our next index. If we look at a dictionary based on hash tables, that is not
 the case. In the hash table we compute the key into a hash function that tells us an index 
 to go accordinly from the key given. Then this index here is especially assigned to this key. 
 However, if the index given to us is taken already, then we would run it through our hash2 
 function to compute another index that is available for the key to be stored in. Looking at the
 timings, the hash table was 0.007202 seconds faster compared to an array dictionary. Which is 
 about 15% faster

 How does hash table performance change as a result of hash table size? 
 If we compare a smaller collection of data n, where it is closer to 0, it may be faster to use 
 an array because we can easily store the data in a ascending order without looking for indexies.
 And as well as when searching for the data, there is only n number of searches to find what we
 are looking for. So best case scenario would be when the indexing is 0, the first value, or when
 the indexing is the last value. It is not bad to look through 10 elements in an array starting at
 the first index until we find one. However, when the size of n increases, for example, in this 
 project 20,000, then it would certainly be faster if we use hashing. This is because when we are 
 using hashing, we find a random spot of an index in the table to dedicate into that index and key. 
 It is then either this key, or another key produced by the second hash function. Thus, there is no
 need to look through 1 to 20,000 indexes until we find the one we are looking for. So inconclusion, 
 array will perform better then size n is closer to 0, while a hash table will produce better results
 when the hash table has multiple inputs n. As n is smaller, hash tables will be slower, and as 
 n is greater, the hash table will be faster.
                                  
 How does hash table performance change with good hash functions vs. bad hash functions? 

 With a good hash function, the hash table will produce o(1) results because there is no 
 colisions happening with in the code, the code itself does not have to continue to look
 for indexes that are available. However, if we compared this result to a bad hash function, 
 the time complexity would be o(n) because the worst case scenario is that each index we get 
 is always taken up, and the program would have to keep looping/looking until it finds an 
 available index. So, hash tables will perform o(1) time, which is the most ideal scenario, 
 and the fastest when it is a good hash function. However, when there is a bad hash function,
 we produce o(n) time, which is not ideal, and a lot slower. There will be a lot of colision 
 happening. 
 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAX_SIZE 20000
#define A 31L;

int str_cmp(char *a, char *b){
	int result = 0;
	for(int i = 0; a[i] != '\0' || b[i] != '\0'; i++){
		if(a[i] != b[i]){
			result = 1; 
		}
	}
	return result; 
} 


typedef struct
{
    // Add data members here
    char *keys[MAX_SIZE]; 
    float values[MAX_SIZE];

} HashTable;

void Initialize(HashTable *ht)
{
   // Implement me!
   	for(int i = 0; i < MAX_SIZE; i++){
		ht->keys[i] = "-1"; 
		ht->values[i] = 0.; 
	}
}

void Store(HashTable *ht, unsigned int hash_val1, unsigned int hash_val2, char *key, float value)
{
   // Implement me
   unsigned int idx = hash_val1 % MAX_SIZE; 

   while(ht->keys[idx] != "-1"){
	   if(ht->keys[idx] == "-1"){
		   break; 
	   } 
	   idx = (idx + hash_val2) % MAX_SIZE;
   } 
   ht->keys[idx] = key; 
   ht->values[idx] = value;
   //printf("Key is %s, and value is %f\n", ht->keys[idx], ht->values[idx]); 
   return;

 }

float Fetch(HashTable *ht, char *key, unsigned int hash_val1, unsigned int hash_val2){
	unsigned int idx = hash_val1 % MAX_SIZE;
	
	while(ht->keys[idx] != "-1"){
		if(str_cmp(key, ht->keys[idx]) == 0){
			return ht->values[idx]; 
		} 
		idx = (idx + hash_val2) % MAX_SIZE; 
	} 


}

unsigned int hash1( char *key){
	unsigned int hashval = 0; 
	for(int i = 0; i < strlen(key); i++){
		hashval = 37 * hashval + key[i]; 
	} 
	hashval %= MAX_SIZE;
	return hashval; 
} 

unsigned int hash2(char *key){	
	int hashval = 0; 

	for(int i = 0; i < strlen(key); i++){
		hashval = 37 * hashval + key[i]; 
	} 
	unsigned int index = 19997 - (hashval % 19997); 
	return index; 
} 

int main()
{
  
    FILE *f = fopen("DJIA", "r");
    if (f == NULL)
    {
         fprintf(stderr, "Unable to open file \"DJIA\" ... did you copy it to the current directory?\n");
         exit(EXIT_FAILURE);
    }

    HashTable ht;
    Initialize(&ht);
    

    //
    // Step 1: parse the file and place contents in the Dictionary.
    //  The key should be the date (a char *)
    //  The value should be the closing price.  (look at DJIA for more info)

   double store_time = 0., fetch_time = 0.; 
	
   struct timeval store_startTime; 
   gettimeofday(&store_startTime, 0); 
	

    size_t size = 1024;
    char *buffer = malloc(size*sizeof(char));
    getline(&buffer, &size, f); 

    while (getline(&buffer, &size, f) > 0)
    {
      //  printf("The line is \"%s\"\n", buffer);
	fflush(stdout); // saftey  

	char *date = malloc(sizeof(char)*9); 

	float open, high, low, close;
	sscanf(buffer, "%s %f %f %f %f", date, &open, &high, &low, &close);
	
	char *str = strdup(date);
	unsigned long h1 = hash1(str); 
	unsigned long h2 = hash2(str);
	Store(&ht, h1, h2, str, close); 
	



        // Hint 1: sscanf is great.  Turn that line into numbers!

        // Hint 2: be very careful about what you send in to Store.
        //         The memory at buffer will be changing, so you can't
        //         use that.  Big hint: strdup

        //Store(&ad, str, closePrice);
    }
	struct timeval store_endTime; 
	gettimeofday(&store_endTime, 0); 

	store_time = (double)(store_endTime.tv_sec - store_startTime.tv_sec) + 
		(double)(store_endTime.tv_usec - store_startTime.tv_usec) / 100000000;	
	printf("Timing for storing data is %g, time per element is %g\n\n", store_time, store_time/20000);
    
    //
    //  For each data, do a fetch.
    //  For each returned closing price, add it to a running sum.
    //  Your goal is ultimately to get the average closing price over
    //  all of the dates in the file.

    struct timeval fetch_startTime; 
    gettimeofday(&fetch_startTime, 0); 


    char dates[91][10] = {
                 "02/19/21", "02/19/20", "12/19/19", "12/12/19", "12/02/19", "11/22/19", "11/12/19", "10/22/19", "10/02/19", 
                 "09/12/19", "08/22/19", "08/12/19", "08/02/19", "07/22/19", "07/12/19", "07/02/19", "06/12/19", "05/22/19", 
                 "05/02/19", "04/22/19", "04/12/19", "04/02/19", "03/22/19", "03/12/19", "02/22/19", "02/19/19", "02/12/19", 
                 "01/22/19", "01/02/19", "12/19/18", "12/19/17", "12/19/16", "02/19/16", "02/19/15", "12/19/14", "02/19/14", 
                 "12/19/13", "02/19/13", "12/19/12", "12/19/11", "02/19/10", "02/19/09", "12/19/08", "02/19/08", "12/19/07", 
                 "12/19/06", "12/19/05", "02/19/04", "12/19/03", "02/19/03", "12/19/02", "02/19/02", "12/19/01", "12/19/00", 
                 "02/19/99", "02/19/98", "12/19/97", "02/19/97", "12/19/96", "12/19/95", "12/19/94", "02/19/93", "02/19/92", 
                 "12/19/91", "02/19/91", "12/19/90", "12/19/89", "12/19/88", "02/19/88", "02/19/87", "12/19/86", "02/19/86", 
                 "12/19/85", "02/19/85", "12/19/84", "12/19/83", "02/19/82", "02/19/81", "12/19/80", "02/19/80", "12/19/79", 
                 "12/19/78", "12/19/77", "02/19/76", "12/19/75", "02/19/75", "12/19/74", "02/19/74", "12/19/73", "12/19/72", 
                 "02/19/71"
           };

    float sum = 0.;
    for (int i = 0 ; i < 91 ; i++)
    {
        // You will need to repeat the code from the last while loop to get the data as a "char *"
	char *date = strdup(dates[i]);	
	unsigned int h1 = hash1(date); 
	unsigned int h2 = hash2(date);
        float val = Fetch(&ht, date, h1, h2);
	//printf("Index at %d, and Value is %f, and key is %s\n", i, val, date);
	 if (val == 0.)
        {
            printf("Bad fetch!\n");
            exit(EXIT_FAILURE);
        }
	sum += val;    
     

    // Uncomment this.  Not it assumes you called your sum variable "sum"
     //printf("Over the 91 days, the average value was %d\n", (int)(sum/91.0));
    // It should print:
    //    Over the 91 days, the average value was 13209
    //
     
    }	
    
    struct timeval fetch_endTime; 
    gettimeofday(&fetch_endTime, 0); 

    fetch_time = (double)(fetch_endTime.tv_sec - fetch_startTime.tv_sec) + 
		(double)(fetch_endTime.tv_usec - fetch_startTime.tv_usec) / 100000000;	
    printf("Timing for fetching data is %g, time per element is %g\n\n", fetch_time, fetch_time/20000);
    


}
