#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define ROW 15
#define COLUMN 30

typedef struct node{
	int row,column;
} stackNode; 

typedef struct Stack{
	stackNode capacity[200];
	int top;
	int bottom;
} stack;

void init(stack &walkStack){
	walkStack.top=0;
	walkStack.bottom=0;
}

void push(stack &walkStack,stackNode stacknode){
	walkStack.capacity[walkStack.top++] = stacknode;
}

void pop(stack &walkStack){
	walkStack.top--;
}

stackNode top(stack &walkStack){
	return walkStack.capacity[walkStack.top-1];
}

int isEmpty(stack &walkStack){
	if(walkStack.top == walkStack.bottom){
		return 1;
	}
	return 0;
}

void walk(char matrix[ROW][COLUMN], struct Stack &walkStack){
	stackNode currentAddr = top(walkStack);
	if((currentAddr.row == ROW-2) && (currentAddr.column == COLUMN-1)){
		printf("successed\n");
		exit(0);
	}
	if(matrix[currentAddr.row+1][currentAddr.column] == '1'){
		stackNode nextAddr;
		nextAddr.row = currentAddr.row+1;
		nextAddr.column = currentAddr.column;
		push(walkStack,nextAddr);
		matrix[currentAddr.row][currentAddr.column] = '2';
		matrix[nextAddr.row][nextAddr.column] = '3';
	}else if(matrix[currentAddr.row-1][currentAddr.column] == '1'){
		stackNode nextAddr;
		nextAddr.row = currentAddr.row-1;
		nextAddr.column = currentAddr.column;
		push(walkStack,nextAddr);
		matrix[currentAddr.row][currentAddr.column] = '2';
		matrix[nextAddr.row][nextAddr.column] = '3';
	}else if(matrix[currentAddr.row][currentAddr.column+1] == '1'){
		stackNode nextAddr;
		nextAddr.row = currentAddr.row;
		nextAddr.column = currentAddr.column+1;
		push(walkStack,nextAddr);
		matrix[currentAddr.row][currentAddr.column] = '2';
		matrix[nextAddr.row][nextAddr.column] = '3';
	}else if(matrix[currentAddr.row][currentAddr.column-1] == '1'){
		stackNode nextAddr;
		nextAddr.row = currentAddr.row;
		nextAddr.column = currentAddr.column-1;
		push(walkStack,nextAddr);
		matrix[currentAddr.row][currentAddr.column] = '2';
		matrix[nextAddr.row][nextAddr.column] = '3';
	}else {
		matrix[currentAddr.row][currentAddr.column] = '2';
		pop(walkStack);
		currentAddr = top(walkStack);
		matrix[currentAddr.row][currentAddr.column] = '3';
	}
}


int main(){
 	char matrix[ROW][COLUMN] = {
		{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
		{'3','1','0','0','1','0','1','0','0','0','1','0','0','0','0','1','0','0','1','1','0','1','0','0','0','1','0','0','0','0'},
		{'0','1','0','1','1','0','1','1','1','0','1','0','0','0','0','1','0','1','1','1','0','1','1','1','0','1','0','0','0','0'},
		{'0','1','1','1','1','0','1','0','1','0','1','1','1','1','0','1','1','1','1','1','0','1','0','1','0','1','1','1','1','0'},
		{'0','1','1','1','1','0','1','0','1','0','1','1','1','1','0','1','1','1','1','1','0','1','0','1','0','1','1','1','1','0'},
		{'0','0','1','1','1','1','1','0','1','0','0','0','0','1','0','0','1','1','0','1','1','1','0','1','0','0','0','0','1','0'},
		{'0','0','1','1','1','1','1','0','1','0','0','0','0','1','0','0','1','1','0','1','1','1','0','1','0','0','0','0','1','0'},
		{'0','0','0','1','1','1','0','0','1','0','1','1','0','1','0','0','0','1','0','1','1','0','0','1','0','1','1','0','1','0'},
		{'0','0','0','1','1','1','0','0','1','0','1','1','0','1','0','0','0','1','0','1','1','0','0','1','0','1','1','0','1','0'},
		{'0','0','0','1','1','0','0','0','1','1','1','1','0','1','0','0','0','1','0','1','0','0','0','1','1','1','1','0','1','0'},
		{'0','0','1','1','1','1','1','0','1','0','0','0','0','1','0','1','1','1','0','1','1','1','0','1','0','0','0','0','1','0'},
		{'0','0','0','1','1','1','0','0','1','0','1','1','0','1','0','1','0','1','0','1','1','0','0','1','0','1','1','0','1','0'},
		{'0','0','0','1','1','0','0','0','1','1','1','1','0','1','0','1','0','1','0','1','0','0','0','1','1','1','1','0','1','0'},
		{'0','0','0','0','0','0','0','0','0','0','0','1','1','1','1','1','0','0','0','0','0','0','0','0','0','0','1','1','1','1'},
		{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}
	};

	stack walkStack;
	init(walkStack);
	stackNode currentAddr;
	currentAddr.row = 1;
	currentAddr.column = 0;
	push(walkStack,currentAddr);
	while(isEmpty(walkStack) == 0){
		system("clear");
		int i,j;		
		for(i=0; i<ROW; i++){
			for(j=0; j<COLUMN; j++){
				if(matrix[i][j] == '0'){
					printf("#");
				}else if(matrix[i][j] == '1' || matrix[i][j] == '2'){
					printf(" ");
				}else if(matrix[i][j] == '3'){
					printf("*");
				}
			}
		putchar('\n');
		}
		usleep(300000);
		walk(matrix,walkStack);
	}
	if(isEmpty(walkStack) == 1){
		printf("\n There are no route \n");
	}
}
