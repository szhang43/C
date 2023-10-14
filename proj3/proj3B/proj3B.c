/* 
 * Based on the performance analysis while comparing dictionary and hash tables, 
 * it seem that the hash table was significantly faster. If we look at the run time, 
 * the dictionary has a run time of average 2.07e-05 while the hash table has a time of 8.00e-08. 
 * The time complexity for a hash table coule either be o(1), which is the best case scenario, but 
 * it could also be o(n). o(1) happens when there are little amounts of collisions going on while the 
 * table is trying to get the values stored. And o(N) is the worst case scenario, this happens when there 
 * is a lot of collisions while trying store. In a dictionary, we would look through the array in order which means, 
 * we would have to look through every index until we find the index we are looking for. The worst case for this is 
 * if the index we are looking for is all the way at the end, and the best is if it is the first element of the 
 * array. This would mean that it would have to look through n number of indexes before it finds out where the 
 * seach element is located. But if we look at a hash table, it seems like we are given the indexs from 
 * out hash functions. First it gives us an index, which would be the first hash value, if the value of the this index
 * matches the key, then we have it. But it not, we then use our second index from our hash2 function to find the index. 
 * This means that we really only have to do two searches when looking for a specific value. Comparably to an array, we have 
 * to look through 1 to n number of elements. This will of course take a significant time faster if we put dictionary arrays and ha * tables side by side. But I think the store functions may varies just a little bit. This is because in an array, we are almost gu * guarantee a index for the next key to be stored in because we jsut simply move on into the next i + 1 index. But if we 
 * look at the storing for the hash table, it can either be very fast or slow depending on the situation. We have to look 
 * at how much collision is happening. If we continue to have collisions, it means that the function can not find 
 * a place for the key to be stored in and it has to loop through over and over again. Chances of this happening entirely 
 * depends on the hash functions. 
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
   for(int i = 1; i < MAX_SIZE; i++){
	unsigned int idx_2 = (hash_val1 + (i * hash_val2)) % MAX_SIZE; 
	if(ht->keys[idx] == "-1"){
		   ht->keys[idx] = key;
		   ht->values[idx] = value; 
		  return; 
	 }
	else if(ht->keys[idx] != "-1"){
		 //unsigned int idx_2 = (idx + (i * hash_val2)) % MAX_SIZE; 
	  	 ht->keys[idx_2] = key; 
	  	 ht->values[idx_2] = value;
	   	 return;
	}

   }
   printf("Failed to store\n");
 }

void print_table(HashTable *ht){
	int count = 0;
	for(int i = 0; i < MAX_SIZE; i++){
		//printf("Key is %s, and value is %f\n", ht->keys[i], ht->values[i]); 
		count++;
	} 
	printf("Count is %d\n", count);
} 

float Fetch(HashTable *ht, char *key, unsigned int hash_val1, unsigned int hash_val2){
	
	unsigned int idx = hash_val1 % MAX_SIZE;
	for(int i = 1; i < MAX_SIZE; i++){
		unsigned int idx_2 = (hash_val1 + (i * hash_val2)) % MAX_SIZE; 
		if(strcmp(key, ht->keys[idx]) == 0){
			return ht->values[idx]; 
		} 
		else if(strcmp(key, ht->keys[idx_2]) == 0){
			return ht->values[idx_2]; 
		} 
	}
	return 5.0;
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
    //
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

    print_table(&ht);
    //
    //  For each data, do a fetch.
    //  For each returned closing price, add it to a running sum.
    //  Your goal is ultimately to get the average closing price over
    //  all of the dates in the file.
    //
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
	printf("Index at %d, and Value is %f, and key is %s\n", i, val, date);
	 if (val == 0.)
        {
            printf("Bad fetch!\n");
            exit(EXIT_FAILURE);
        }
	sum += val; 

    }  

    // Uncomment this.  Not it assumes you called your sum variable "sum"
     printf("Over the 91 days, the average value was %d\n", (int)(sum/91.0));
    // It should print:
    //    Over the 91 days, the average value was 13209
}
