#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define ROW 30
#define COLUMN 80
#define COUNT ((ROW-2)*(COLUMN-3))

typedef struct node{
	int row,column;
} stackNode; 

typedef struct Stack{
	stackNode capacity[400];
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

stackNode front(stack &walkStack){
	return walkStack.capacity[walkStack.bottom++];
}

int isEmpty(stack &walkStack){
	if(walkStack.top == walkStack.bottom){
		return 1;
	}
	return 0;
}

void walk(char** matrix, struct Stack &walkStack, int &findPath){
	stackNode currentAddr = top(walkStack);
	if((currentAddr.row == ROW-2) && (currentAddr.column == COLUMN-1)){
		findPath = 1;
		return;
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

void randomPath(char **matrix){
	int row,column;
	srand((int)time(0));
	for(int i=0; i<COUNT; i++){
		row = (int)(rand()%(ROW-2)+1);
		column = (int)(rand()%(COLUMN-2)+1);
		matrix[row][column] = '1';
	}
	matrix[1][0] = '1';
	matrix[1][1] = '1';
	matrix[1][3] = '1';
	matrix[1][4] = '1';
	matrix[1][5] = '1';
	matrix[ROW-2][COLUMN-5] = '1';
	matrix[ROW-2][COLUMN-4] = '1';
	matrix[ROW-2][COLUMN-3] = '1';
	matrix[ROW-2][COLUMN-2] = '1';
	matrix[ROW-2][COLUMN-1] = '1';
}


int main(){
 	char **matrix;
	matrix = (char**)malloc(ROW*sizeof(char*));
	int i,j;
	for(i=0; i<=COLUMN; i++){
		matrix[i] = (char*)malloc(COLUMN*sizeof(char));
	}
	for(i=0; i<ROW; i++){
		for(j=0; j<COLUMN; j++){
			matrix[i][j] = '0';
		}
	}
	randomPath(matrix);

	stack walkStack;
	init(walkStack);
	stackNode currentAddr;
	currentAddr.row = 1;
	currentAddr.column = 0;
	push(walkStack,currentAddr);
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

	int findPath = 0;
	while(isEmpty(walkStack) == 0){
		walk(matrix,walkStack, findPath);
		if(findPath == 1){
			break;
		}

		
		system("clear");
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

		usleep(30000);
	}
	if(isEmpty(walkStack) == 1){
		printf("\n There are no route \n");
		return 0;
	}
	
	while(isEmpty(walkStack) == 0){
		system("clear");
		puts("The route is:");
		currentAddr = front(walkStack);
		matrix[currentAddr.row][currentAddr.column] = '3';
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
		usleep(500000);
	}
}
