#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_SIZE 10
struct stack{
	int member; 
	double array[STACK_SIZE];
}; 
typedef struct stack Stack; 

void initialize(Stack *s){
	s->member = -1; 
} 

void push(double num, Stack *s){
	if(s->member == STACK_SIZE - 1){
		exit(EXIT_FAILURE); 
	}
	s->member++;  
	s->array[s->member] = num; 
	
} 

double pop(Stack *s){
	if(s->member ==  -1){
		exit(EXIT_FAILURE);
	}
	double num  = s->array[s->member]; 
	--s->member;
	return num; 
} 

typedef enum
{
   ADD,
   MULT,
   SUBTRACT,
   DIV,
   UNSUPPORTED
} MathOperation;

void IssueBadNumberError()
{
    printf("The string does not represent a floating point number.\n");
    exit(EXIT_FAILURE);
}
void IssueBadOperationError()
{
    printf("The string does not represent a valid operation.\n");
    exit(EXIT_FAILURE);
}

MathOperation GetOperation(char *op)
{

	/* Implement me! */
	int count = 0;
	if (op[1] != '\0'){
		IssueBadOperationError();
	}

	while(*op != '\0'){
		
		count++;
		if(count > 1){
			return UNSUPPORTED;
		}

		if(*op == '+'){
			return ADD;
		}

		else if(*op == '-'){
			return SUBTRACT;
		}

		else if(*op == 'x'){
			return MULT;
		}

		else if(*op == '/'){
			return DIV;
		}

		else{
			return UNSUPPORTED;
		}

		*op++;
		
	}
}


double CalculateFraction(char *str){

	int count = 0;
	double end_result2 = 0.; 

	while(*str != '\0'){
		int result = *str - 48;

		if(*str == '-'){
			IssueBadOperationError();
		}

		else if(*str == '.'){
			IssueBadNumberError();
		}

		else if(0 > result || result > 9){
			IssueBadNumberError();
		}
		else if(0 < result || result < 9){
			end_result2 = (end_result2 * 10) + (*str - '0');
		}
		*str++;
		count++;

	}
	//printf("End result is %f", end_result2);

	for(int i = 0; i < count; i++){
		//printf("loop %f", end_result2);
		end_result2 = end_result2 * 0.1;
	}
	//printf("Final value of calcfrac is %f\n", end_result2);

	return end_result2;


}

double StringToDouble(char *str)
{
    //Implement me! 
	
	double end_result = 0.;
	int count_neg = 0;
	double dec_sum = 0;

	int neg = 0;
	char str0 = str[0]; 
	
	
	
	while(*str != '\0'){

		int result = *str - 48;
		
		if(*str == '-'){
			count_neg++;
			if(count_neg > 1){
				IssueBadOperationError();
			}
		}

		else if(*str == '.'){
			*str++;
			double result = CalculateFraction(str);
			end_result = end_result + result;
			break;
		}
		
		else if( 0 > result || result > 9){
			IssueBadNumberError();
		}
		else if( 0 < result || result < 9){
			end_result = (end_result * 10) + (*str - '0');
		}
	
		*str++;
	}

	if(str0 == '-'){
		end_result = end_result * -1;
	}
	

	return end_result;
}


int main(int argc, char *argv[])
{
	struct stack *s = malloc(sizeof(struct stack));
	initialize(s);
//	printf("hi\n");
	double result = 0.;
	int j;
	for(int i = 1; i <  argc; i++){
		char *input = argv[i];
		if(argv[i][0] == '+' || argv[i][0] == '/' || argv[i][0] == 'x' || argv[i][0] == '-'){
				MathOperation op = GetOperation(input);
				double v = pop(s); 
				double v2 = pop(s); 
    			switch (op)
				    {	
						case ADD:
							result = v + v2;
							break;

						case MULT:
							result = v * v2; 
							break;
		
						case SUBTRACT:
							result = v2 - v;
							break;

						case DIV:
							result = v2 / v; 
							break;
						
					}
				push(result, s);
			}
			else{
				double num = StringToDouble(input);
				push(num, s);
			}
	} 
	printf("The total is %d\n", (int) result);
    return 0;
}


