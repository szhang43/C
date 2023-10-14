#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int my_strlen(char *s)
{
    /** Return the length of string s using the C convention of
     * being terminated by the NULL character. 
     * Do not call any other functions whatsoever.
     * Even my_strlen -- no solutions involving recursion. i*/ 

	int count = 0;
	while(*s != '\0'){
		count++; 
		s++; 
	}
	return count; 
}

void str_reverse(char *str)
{
    /* Modify s to be the reverse string.
     * If s is "hello" when the function is called, then it
     * should be "olleh" when the function is completed. 
     * The only function you can call is my_strlen.
     * Do not call malloc.  */


	int length = my_strlen(str); 

	for(int i = 0; i < (length / 2); i++){
		char temp = str[i];
		str[i] = str[length - i - 1]; 	
		str[length - i - 1] = temp;

	}
	
}

int main()
{

	/*char *str = "Helloword"; 
	str_reverse(str); 

	printf("%s", str);
    */
    char *str = malloc(strlen("hello world")+1);
    strcpy(str, "hello world");
    str_reverse(str);
    
    if (strcmp(str, "dlrow olleh") == 0)
    {
        printf("Congrats!  You have successfully reversed \"hello world\" to \"%s\"\n", str);
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Project does not work yet.  You reversed \"hello world\" to \"%s\"\n", str);
        exit(EXIT_FAILURE);
    }
    }
