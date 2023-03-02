#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
	srand(time(NULL));
	int N,M,num_bait,dd=0,var=0,var1=0,index1,index2;
	int snake=1, bait=0;
	printf("SNAKE GAME\n");
	printf("enter the number of rows of the game board\n");
	scanf("%d",&N);
	printf("enter the number of columns of the game board\n");
	scanf("%d",&M);
	while(dd==0){
		printf("enter the number of bait\n");
		scanf("%d", &num_bait);
		if(num_bait<N*M){//place for head of snake
			dd=1;
		}
		else{
			dd=0;
		}		
	}	
	char mtr[100][100];
	char snake_mtr[100];
	int i,j,k;
	//the boundaries of the game board and spaces
	for(i=0;i<M+2;i++){				
		mtr[0][i]= '_';	
		mtr[N+1][i]='_';			
	}
	for(i=0;i<N+2;i++){				
		mtr[i][0]= '|';	
		mtr[i][M+1]='|';			
	}
	for(i=1;i<N+1;i++){
		for(j=1;j<M+1;j++){		
			mtr[i][j]= ' ';			
		}
	}
	k=0;
	while(k<num_bait){//placing the baits
		i= rand() % N+1;
		j= rand() % M+1;
		if(mtr[i][j]==' '){
			mtr[i][j]= '0';
			k++;
		}		
	}
	while(var==0){//placing the snake and keeping coordinates
		i= rand() % N-1;
		j= rand() % M-1;
		if(mtr[i][j]==' '){
			mtr[i][j]='1';
			index1=i;
			index2=j;
			var=1;
		}
		else{
			var=0;
		}
	}	
	for(i=0;i<N+2;i++){//print the game board  
		for(j=0;j<M+2;j++){
			printf("%c\t",mtr[i][j]);
		}
		printf("\n");
	}
	char move;
	int snake_x[100];
	int snake_y[100];
	snake_x[0]=index1;//keeping coordinates in an array
	snake_y[0]=index2;
	int lost=0,count=0,grew=0,old_growth=0,size=1;
	snake_mtr[0]='1';
	printf("to move up: u\nto move down: d\nto move right: r\nto move left: l\n");	
	while(lost==0){
		printf("move: ");
		scanf(" %c",&move);
		if(move=='u'){
			count++;					
			if(mtr[index1-1][index2]=='0'|| mtr[index1-1][index2]==' '){//moves up if it is a space or bait above
				old_growth=grew;
				if(mtr[index1-1][index2]=='0'){						
					grew++;//keeping keeping the number of baits eaten
					mtr[index1-1][index2]=mtr[index1][index2];
					mtr[index1][index2]=' ';					
				}
				for(j=0;j<size;j++){//lengthen the tail
					snake_mtr[j]='0'+(j+1);					
				}																																			
				for(j=0;j<size;j++){
					snake_mtr[j]=snake_mtr[j+1];					
				}
				if(grew==old_growth){
					mtr[index1-1][index2]=mtr[index1][index2];
					mtr[snake_x[0]][snake_y[0]]=' ';									
				}	
				for(i=(size-1);i>0;i--){//following each other
					snake_x[i]=snake_x[i-1];
					snake_y[i]=snake_y[i-1];					
				}
				snake_x[0]=index1;//keeping indexes of the head of snake
				snake_y[0]=index2;
				index1--;
				for(i=0;i<size;i++){//placing the tail
					mtr[snake_x[i]][snake_y[i]]=snake_mtr[i];
				}																																								
				for(i=0;i<N+2;i++){
					for(j=0;j<M+2;j++){
						printf("%c\t",mtr[i][j]);
					}
					printf("\n");
				}
				printf("\nnumber of moves: %d\n",count);
				if(grew==num_bait){//if snake have eaten all baits 
					printf("You have made the snake the biggest in %d moves and you completed the game.",count);					
					lost=1;
				}
				else{
					lost=0;
				}				
				size=grew+1;
			}
			else if(mtr[index1-1][index2]=='_'){
				for(j=0;j<(size);j++){//If snake wants to move to out of border, it will disappear
					snake_mtr[j]=' ';					
				}																	
				for(j=0;j<size;j++){
					snake_mtr[j]=snake_mtr[j+1];					
				}				
				for(i=(size-1);i>0;i--){
					snake_x[i]=snake_x[i-1];
					snake_y[i]=snake_y[i-1];
				}
				snake_x[0]=index1;
				snake_y[0]=index2;
				index1--;
				for(i=0;i<size;i++){
					mtr[snake_x[i]][snake_y[i]]=snake_mtr[i];
				}
				for(i=0;i<N+2;i++){
					for(j=0;j<M+2;j++){
						printf("%c\t",mtr[i][j]);
					}
					printf("\n");
				}
				printf("\nyou have lost the game.\n");				
				printf("you have made %d moves\n",count);
				printf("size of snake: %d\n",size);
				printf("number of remaining baits: %d",num_bait-grew);				
				lost=1;
			}
			else if(old_growth==0){//If the snake wants to move to its old place when snake is only 1 
				mtr[index1-1][index2]=mtr[index1][index2];
				mtr[index1][index2]=' ';
				snake_x[0]=index1;
				snake_y[0]=index2;
				index1--;						
				for(i=0;i<N+2;i++){								
					for(j=0;j<M+2;j++){
						printf("%c\t",mtr[i][j]);
					}
					printf("\n");		
				}
			}
			else{				
				printf("\nyou have lost the game.\n");
				printf("you have made %d moves\n",count);
				printf("size of snake: %d\n",size);
				printf("number of remaining baits: %d",num_bait-grew);
				lost=1;
			}						
		}
		else if(move=='d'){
			count++;
			if(mtr[index1+1][index2]=='0' || mtr[index1+1][index2]==' '){
				old_growth=grew;
				if(mtr[index1+1][index2]=='0'){						
					grew++;
					mtr[index1+1][index2]=mtr[index1][index2];
					mtr[index1][index2]=' ';					
				}
				for(j=0;j<size;j++){
					snake_mtr[j]='0'+(j+1);					
				}																																			
				for(j=0;j<size;j++){
					snake_mtr[j]=snake_mtr[j+1];					
				}
				if(grew==old_growth){
					mtr[index1+1][index2]=mtr[index1][index2];
					mtr[snake_x[0]][snake_y[0]]=' ';
									
				}	
				for(i=(size-1);i>0;i--){
					snake_x[i]=snake_x[i-1];
					snake_y[i]=snake_y[i-1];
					
				}
				snake_x[0]=index1;
				snake_y[0]=index2;
				index1++;
				for(i=0;i<size;i++){
					mtr[snake_x[i]][snake_y[i]]=snake_mtr[i];
				}							
																																	
				for(i=0;i<N+2;i++){
					for(j=0;j<M+2;j++){
						printf("%c\t",mtr[i][j]);
					}
					printf("\n");
				}
				printf("\nnumber of moves %d\n",count);	
				if(grew==num_bait){
					printf("You have made the snake the biggest in %d moves and you completed the game.",count);					
					lost=1;
				}
				else{
					lost=0;
				}				
				size=grew+1;
			}	
			else if(mtr[index1+1][index2]=='_'){
				for(j=0;j<(size);j++){
					snake_mtr[j]=' ';					
				}																	
				for(j=0;j<size;j++){
					snake_mtr[j]=snake_mtr[j+1];					
				}				
				for(i=(size-1);i>0;i--){
					snake_x[i]=snake_x[i-1];
					snake_y[i]=snake_y[i-1];
				}
				snake_x[0]=index1;
				snake_y[0]=index2;
				index1++;
				for(i=0;i<size;i++){
					mtr[snake_x[i]][snake_y[i]]=snake_mtr[i];
				}
				for(i=0;i<N+2;i++){
					for(j=0;j<M+2;j++){
						printf("%c\t",mtr[i][j]);
					}
					printf("\n");
				}
				printf("\nyou have lost the game.\n");
				printf("you have made %d moves\n",count);
				printf("size of snake: %d\n",size);
				printf("number of remaining baits: %d",num_bait-grew);
				lost=1;
			}
			else if(old_growth==0){
				mtr[index1+1][index2]=mtr[index1][index2];
				mtr[index1][index2]=' ';
				snake_x[0]=index1;
				snake_y[0]=index2;
				index1++;						
				for(i=0;i<N+2;i++){								
					for(j=0;j<M+2;j++){
						printf("%c\t",mtr[i][j]);
					}
					printf("\n");		
				}
			}
			else{
				printf("\nyou have lost the game.\n");
				printf("you have made %d moves\n",count);
				printf("size of snake: %d\n",size);
				printf("number of remaining baits: %d",num_bait-grew);
				lost=1;
			}						
		}
		else if(move=='r'){
			count++;
			if(mtr[index1][index2+1]=='0' || mtr[index1][index2+1]==' '){
				old_growth=grew;
				if(mtr[index1][index2+1]=='0'){						
					grew++;
					mtr[index1][index2+1]=mtr[index1][index2];
					mtr[index1][index2]=' ';					
				}
				for(j=0;j<size;j++){
					snake_mtr[j]='0'+(j+1);					
				}																																			
				for(j=0;j<size;j++){
					snake_mtr[j]=snake_mtr[j+1];					
				}
				if(grew==old_growth){
					mtr[index1][index2+1]=mtr[index1][index2];
					mtr[snake_x[0]][snake_y[0]]=' ';
									
				}	
				for(i=(size-1);i>0;i--){
					snake_x[i]=snake_x[i-1];
					snake_y[i]=snake_y[i-1];
					
				}
				snake_x[0]=index1;
				snake_y[0]=index2;
				index2++;
				for(i=0;i<size;i++){
					mtr[snake_x[i]][snake_y[i]]=snake_mtr[i];
				}							
																																	
				for(i=0;i<N+2;i++){
					for(j=0;j<M+2;j++){
						printf("%c\t",mtr[i][j]);
					}
					printf("\n");
				}
				printf("\nnumber of moves %d\n",count);
				if(grew==num_bait){
					printf("You have made the snake the biggest in %d moves and you completed the game.",count);					
					lost=1;
				}
				else{
					lost=0;
				}				
				size=grew+1;
			}				
			else if(mtr[index1][index2+1]=='|'){
				for(j=0;j<size;j++){
					snake_mtr[j]=' ';					
				}																	
				for(j=0;j<size;j++){
					snake_mtr[j]=snake_mtr[j+1];					
				}				
				for(i=(size-1);i>0;i--){
					snake_x[i]=snake_x[i-1];
					snake_y[i]=snake_y[i-1];
				}
				snake_x[0]=index1;
				snake_y[0]=index2;
				index2++;
				for(i=0;i<size;i++){
					mtr[snake_x[i]][snake_y[i]]=snake_mtr[i];
				}
				for(i=0;i<N+2;i++){
					for(j=0;j<M+2;j++){
						printf("%c\t",mtr[i][j]);
					}
					printf("\n");
				}
				printf("\nyou have lost the game.\n");
				printf("you have made %d moves\n",count);
				printf("size of snake: %d\n",size);
				printf("number of remaining baits: %d",num_bait-grew);
				lost=1;
			}
			else if(old_growth==0){
				mtr[index1][index2+1]=mtr[index1][index2];
				mtr[index1][index2]=' ';
				snake_x[0]=index1;
				snake_y[0]=index2;
				index2++;						
				for(i=0;i<N+2;i++){								
					for(j=0;j<M+2;j++){
						printf("%c\t",mtr[i][j]);
					}
					printf("\n");		
				}
			}
			else{
				printf("\nyou have lost the game.\n");
				printf("you have made %d moves\n",count);
				printf("size of snake: %d\n",size);
				printf("number of remaining baits: %d",num_bait-grew);
				lost=1;
			}						
		}
		else if(move=='l'){
			count++;
			if(mtr[index1][index2-1]=='0' || mtr[index1][index2-1]==' '){
				old_growth=grew;
				if(mtr[index1][index2-1]=='0'){	
					
					grew++;
					mtr[index1][index2-1]=mtr[index1][index2];
					mtr[index1][index2]=' ';					
				}
				for(j=0;j<size;j++){
					snake_mtr[j]='0'+(j+1);					
				}																																			
				for(j=0;j<size;j++){
					snake_mtr[j]=snake_mtr[j+1];					
				}
				if(grew==old_growth){
					mtr[index1][index2-1]=mtr[index1][index2];
					mtr[snake_x[0]][snake_y[0]]=' ';
									
				}	
				for(i=(size-1);i>0;i--){
					snake_x[i]=snake_x[i-1];
					snake_y[i]=snake_y[i-1];
					
				}
				snake_x[0]=index1;
				snake_y[0]=index2;
				index2--;
				for(i=0;i<size;i++){
					mtr[snake_x[i]][snake_y[i]]=snake_mtr[i];
				}							
																																	
				for(i=0;i<N+2;i++){
					for(j=0;j<M+2;j++){
						printf("%c\t",mtr[i][j]);
					}
					printf("\n");
				}
				printf("\nnumber of moves %d\n",count);
				if(grew==num_bait){
					printf("You have made the snake the biggest in %d moves and you completed the game.",count);					
					lost=1;
				}
				else{
					lost=0;
				}				
				size=grew+1;
			}				
			else if(mtr[index1][index2-1]=='|'){
				for(j=0;j<(size);j++){
					snake_mtr[j]=' ';					
				}																	
				for(j=0;j<size;j++){
					snake_mtr[j]=snake_mtr[j+1];					
				}				
				for(i=(size-1);i>0;i--){
					snake_x[i]=snake_x[i-1];
					snake_y[i]=snake_y[i-1];
				}
				snake_x[0]=index1;
				snake_y[0]=index2;
				index2--;
				for(i=0;i<size;i++){
					mtr[snake_x[i]][snake_y[i]]=snake_mtr[i];
				}
				for(i=0;i<N+2;i++){
					for(j=0;j<M+2;j++){
						printf("%c\t",mtr[i][j]);
					}
					printf("\n");
				}
				printf("\nyou have lost the game.\n");
				printf("you have made %d moves\n",count);
				printf("size of snake: %d\n",size);
				printf("number of remaining baits: %d",num_bait-grew);
				lost=1;
			}
			else if(old_growth==0){
				mtr[index1][index2-1]=mtr[index1][index2];
				mtr[index1][index2]=' ';
				snake_x[0]=index1;
				snake_y[0]=index2;
				index2--;						
				for(i=0;i<N+2;i++){								
					for(j=0;j<M+2;j++){
						printf("%c\t",mtr[i][j]);
					}
					printf("\n");		
				}
			}
			else{			
				printf("\nyou have lost the game.\n");
				printf("you have made %d moves\n",count);
				printf("size of snake: %d\n",size);
				printf("number of remaining baits: %d",num_bait-grew);
				lost=1;
			}						
		}	
	}	
	return 0;
}
