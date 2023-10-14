#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>



int SearchForWord(char *buffer, char *searchword){
	
	int word_count = 0;
	for(int i = 0; i < strlen(buffer); i++){
		int count = 0;
		

		for(int j = 0; j < strlen(searchword) ; j++){

			if( (i + j) >= strlen(buffer)){break;}
			
			char ch = buffer[i+j];
			char b_ch = buffer[i - 1];
		
			if(b_ch == ' ' || b_ch == ',' || b_ch == '.' || b_ch == '!' || b_ch == '?' || b_ch == '\n'){
				if(ch == searchword[j]){
					count++; 
				}

				else{break;}
			}

			if(count == strlen(searchword)){
				char a_ch = buffer[i + strlen(searchword)];
				if(a_ch == ' ' || a_ch == '.' || a_ch == ',' || a_ch == '?' || 
						a_ch == '!' || a_ch == '\n'){

					word_count++; 
				}
				else{break;}
			}
		}
	}

	return word_count; 
}	

					
int main(int argc, char *argv[]){
	FILE *f_in; 
	int buff_size; 
	char *buffer; 
	
	f_in = fopen(argv[1], "r");
	fseek(f_in, 0, SEEK_END); 
	buff_size = ftell(f_in); 
	fseek(f_in, 0, SEEK_SET); 

	buffer = malloc(buff_size + 1); 
	//buffer = malloc(sizeof(char)*strlen(buffer)+1);
	fread(buffer, sizeof(char), buff_size, f_in); 
	buffer[buff_size] = '\0';

	if(f_in == NULL){

		printf("Invalid File"); 
		return 1; 
	}

	// counts the number of arguments 
	int arg_count = 0;
	for(int i = 0; i < (argc - 2); i++){
		arg_count++;
	}
	
	int *count = malloc(sizeof(int)*argc);

	for(int i = 2; i < argc ; i++){	
		count[i] = SearchForWord(buffer, argv[i]);		
		printf("The word \"%s\" occurs %d times.\n", argv[i], count[i]);
	}
			
	free(buffer);
	free(count);
	fclose(f_in); 

	return 0; 

}
