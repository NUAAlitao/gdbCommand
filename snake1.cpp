#include<iostream>
#include <termio.h>  
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
			if(i == 0 || i == row-1 || j == 0 || j == column-1){
				cout<<"#";
			}else if(matrix[i][j].value == 1){
				cout<<"*";	
			}else{
				cout<<" ";
			}
		}
		cout<<endl;
	}
}

void snakeRun(int &eaten, node** matrix, int foodC, int foodR, snake &head, snake &tail){
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

void controlSnake(int &eaten, node** matrix,int foodR, int foodC, int row, int column, snake &head, snake &tail){
	if(control == 'w'){
		head.row--;
		snakeRun(eaten,matrix,foodC,foodR,head,tail);
	}
	if(control == 's'){
		head.row++;
		snakeRun(eaten,matrix,foodC,foodR,head,tail);
	}
	if(control == 'a'){
		head.column--;
		snakeRun(eaten,matrix,foodC,foodR,head,tail);
	}
	if(control == 'd'){
		head.column++;
		snakeRun(eaten,matrix,foodC,foodR,head,tail);
	}
}

char scanKeyboard()  
{  
	char in;  
	struct termios new_settings;  
	struct termios stored_settings;  
	tcgetattr(0,&stored_settings);  
	new_settings = stored_settings;  
	new_settings.c_lflag &= (~ICANON);  
	new_settings.c_cc[VTIME] = 0;  
	tcgetattr(0,&stored_settings);  
	new_settings.c_cc[VMIN] = 1;  
	tcsetattr(0,TCSANOW,&new_settings);  
	  
	in = getchar();  
	  
	tcsetattr(0,TCSANOW,&stored_settings);  
	return in;  
} 


int row=20,column=35;
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
	c = (int)((float)(column-2)*rand()/(RAND_MAX+1.0))+1;
	r = (int)((float)(row-2)*rand()/(RAND_MAX+1.0))+1;
	head.snakeNode = &matrix[r][c];	
	head.row = r;
	head.column = c;
	matrix[r][c].value = 1;
	tail = head;
    int eaten = 1;
	while(1){
		if(eaten == 1){
			foodC = (int)((float)(column-2)*rand()/(RAND_MAX+1.0))+1;
			foodR = (int)((float)(row-2)*rand()/(RAND_MAX+1.0))+1;
			matrix[foodR][foodC].value = 1;
			eaten=0;
		}
		
		printSnake(matrix, row, column);
		control = scanKeyboard();
		controlSnake(eaten,matrix,foodR,foodC,row,column,head,tail);	
		sleep(0);
		system("clear");
	}
	return 0;
}
