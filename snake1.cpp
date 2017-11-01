#include<iostream>
#include<time.h>
#include<unistd.h>
using namespace std;

typedef struct Node{
	int value;
	struct Node *precede;
} node;

typedef struct{
	int row,column;
	node *snakeNode;
} snake;

char control;

void printSnake(node **matrix, int row, int column){
	int i,j;
	for(i=0; i<row; i++){
		for(j=0; j<column; j++){
			if(matrix[i][j].value == 1){
				cout<<"*";	
			}else{
				cout<<" ";
			}
		}
		cout<<endl;
	}
}


void controlSnake(int &eaten, node** matrix,int foodR, int foodC, int row, int column, snake &head, snake &tail){
	if(control == 'w'){
		head.row--;
		matrix[head.row][head.column].value = 1;
		head.snakeNode->precede = &matrix[head.row][head.column];	
		head.snakeNode = head.snakeNode->precede;
		if(foodC != head.column || foodR != head.row){
			tail.snakeNode->value = 0;
			tail.snakeNode = tail.snakeNode->precede;
		}else{
			eaten = 1;
		}
	}
	if(control == 's'){
		head.row++;
		matrix[head.row][head.column].value = 1;
		head.snakeNode->precede = &matrix[head.row][head.column];	
		head.snakeNode = head.snakeNode->precede;
		if(foodC != head.column || foodR != head.row){
			tail.snakeNode->value = 0;
			tail.snakeNode = tail.snakeNode->precede;
		}else{
			eaten = 1;
		}
	}
	if(control == 'a'){
		head.column--;
		matrix[head.row][head.column].value = 1;
		head.snakeNode->precede = &matrix[head.row][head.column];	
		head.snakeNode = head.snakeNode->precede;
		if(foodC != head.column || foodR != head.row){
			tail.snakeNode->value = 0;
			tail.snakeNode = tail.snakeNode->precede;
		}else{
			eaten = 1;
		}
	}
	if(control == 'd'){
		head.column++;
		matrix[head.row][head.column].value = 1;
		head.snakeNode->precede = &matrix[head.row][head.column];	
		head.snakeNode = head.snakeNode->precede;
		if(foodC != head.column || foodR != head.row){
			tail.snakeNode->value = 0;
			tail.snakeNode = tail.snakeNode->precede;
		}else{
			eaten = 1;
		}
	}
	
}

int row=15,column=15;
int main(){
	int foodR, foodC;
	node **matrix;
	snake head, tail;
	matrix = new node*[row];
	for(int i=0; i<row; i++){
		matrix[i] = new node[column];
	}
	int r,c; 
	srand((int)time(0));
	c = (int)((float)column*rand()/(RAND_MAX+1.0));
	r = (int)((float)row*rand()/(RAND_MAX+1.0));
	head.snakeNode = &matrix[r][c];	
	head.row = r;
	head.column = c;
	matrix[r][c].value = 1;
	tail = head;
    int eaten = 1;
	while(1){
		if(eaten == 1){
			foodC = (int)((float)column*rand()/(RAND_MAX+1.0));
			foodR = (int)((float)row*rand()/(RAND_MAX+1.0));
			matrix[foodR][foodC].value = 1;
			eaten=0;
		}
		
		printSnake(matrix, row, column);
		cin>>control;
		controlSnake(eaten,matrix,foodR,foodC,row,column,head,tail);	
		sleep(0);
		system("clear");
	}
	return 0;
}
