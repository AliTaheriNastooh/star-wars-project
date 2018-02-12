#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include<dos.h>
#include<time.h>
#include <conio.h>
#include<TermMgr.h>
///
void game(int,int,int,int,int,int);

//#define xGame 50
//#define yGame 60
int xGame=30;
int yGame=40;
int color_backg=240;

struct shot{
	int x;
	int y;
	int color;
};


struct list_shot{
	shot* arr[100];
	int n;
};


struct enemy{
	int x;
	int y;
	int color;
};


struct list_enemy{
enemy* arr[100];
int n;
};


struct ship{
int x[15];
int y[15];
};

struct bomb{
int x,y,color,exist;
};

struct list_bomb{
bomb arr[10];
int n;
int len;
};


void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
}

void print(int i , int j , char c,int color){
gotoxy(j,i);
HANDLE  hConsole;
hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, color);
printf("%c",c);
}

void set_time(){
time_t t;
time(&t);
srand(t);
}

void print2(int i , int j , char* c,int color){
gotoxy(j,i);
HANDLE  hConsole;
hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, color);
printf("%s",c);
}

int random(int start,int end){
	return(rand()%(end-start+1))+start;
}


void limit_menu(){
int color=random(16,55);
int i=5;
for(int j=yGame/2-5 ; j<=yGame/2+46 ; j++,color++){
print(i,j,'$',color);
}
i=30;
for(int j=yGame/2-5 ; j<yGame/2+46 ; j++,color++){
print(i,j,'$',color);
}
int j=yGame/2-5;
for(int i=5 ; i<=30 ; i++,color++){
print(i,j,'$',color);
}
j=yGame/2+46;
for(int i=5 ; i<=30 ; i++,color++){
print(i,j,'$',color);
}
}


int select(int choice,int max){
	int key;
	key=getch();
		if(key==0||key==224){
			int key2=getch();
			if(key2==72){
			if(choice==0)
				choice=max-1;
			else
				choice--;
			}

			else{
			if(key2==80){
			if(choice==max-1)
				choice=0;
			else
				choice++;
			}
			}
		}
		else{
			if(key==13){
			return -1;
			}
			else{
				if(key==27){
					return -2;
				}
			}
		}
			return choice;
}
int* setting_menu(){
	static int list2[3]={252,253,0};//1-color level1--------2-color level2----------3-speed
	int choice=0,key;
	int x=10,y=yGame/2;
	int  j=x;
	print(1,1,' ',1);
	system("cls");
	char list[4][45]={{"1-color of level 1(between 0 - 9)"},{"2-color of level 2(between 0 - 9)"},{"3-speed game for all level(between 0 - 9)"},{"4-width and lenght of game"}};
	limit_menu();
	for(int i=0 ; i<4 ; i++,j=j+3){
		if(i==choice){
			print2(j,y,list[i],172);
		}
		else{
			print2(j,y,list[i],12);
		}
	}
	while(1){
	if(kbhit()){
		int temp=select(choice,4);
			if(temp>=0){
			choice=temp;
			print(1,1,' ',1);
			system("cls");
			limit_menu();
			int  j=x;
			y=yGame/2;
		for(int i=0 ; i<4 ; i++,j=j+3){
		if(i==choice){
			print2(j,y,list[i],172);
		}
		else{
			print2(j,y,list[i],12);
		}
	}
			}
			else{
				if(temp==-1){
				char n='0';
				if(temp==-1){
					if(choice==3){
					print(x,y+2,' ',1);
					system("cls");
					limit_menu();
					print2(x,y,"enter width and lenght between 30-50",172);
					print(x+2,y,' ',172);
					scanf("%d%d",&xGame,&yGame);
					}
					else{
					print(x+(3*choice),y+45,n,172);
					while(1){
						if(kbhit()){
								key=getch();
								if(key==0||key==224){
									key=getch();
									if(key==72){
										if(n<'9')
											n++;
									}
									else{
										if(key==80){
											if(n>'0'){
												n--;
											}
											}
									}
									print(x+(3*choice),y+45,n,172);
						}
								else{
									if(key==13){
									break;
									}

								}
					}
				}
			if(choice==2)
				list2[choice]=n-'0';
			else
				list2[choice]=n-'0'+240;
			}
				}
				else{
					if(temp==27){
					break;
					}
				}
	}
				else{
				if(temp==-2)
					break;
				}
			print(1,1,' ',1);
			system("cls");
			limit_menu();
			int  j=x;
			y=yGame/2;
		for(int i=0 ; i<4 ; i++,j=j+3){
		if(i==choice){
			print2(j,y,list[i],172);
		}
		else{
			print2(j,y,list[i],12);
		}
	}
			}

	}
	}
	return list2;
}
void level_menu(int* list2){
	print(1,1,' ',1);
	system("cls");
	int choice=0;
	int x=10,y=yGame/2;
	int  j=x,temp;
	char list[4][45]={{"1-level 1"},{"2-level 2"},{"3-level 3"},{"4-level 4"}};
	limit_menu();
	for(int i=0 ; i<4 ; i++,j=j+3){
		if(i==choice){
			print2(j,y,list[i],172);
		}
		else{
			print2(j,y,list[i],12);
		}
	}
		while(1){
			if(kbhit()){
			temp=select(choice,4);
			if(temp>=0){
			choice=temp;
			print(1,1,' ',1);
			system("cls");
			limit_menu();
			int  j=x;
			y=yGame/2;
		for(int i=0 ; i<4 ; i++,j=j+3){
		if(i==choice){
			print2(j,y,list[i],172);
		}
		else{
			print2(j,y,list[i],12);
		}

	}
			}
			else{
			if(temp==-1){
				switch(choice){
					case 0:
						game(1,list2[2],list2[0],list2[1],0,1);
						break;
					case 1:
						game(2,list2[2],list2[0],list2[1],0,1);
						break;
					case 2:
						game(3,list2[2],list2[0],list2[1],0,1);
						break;
					case 3:
					game(4,list2[2],list2[0],list2[1],0,1);
						break;


				}
	int  j=x;
	print(1,1,' ',1);
	system("cls");
	limit_menu();
	y=yGame/2;
	for(int i=0 ; i<5 ; i++,j=j+3){
		if(i==choice){
			print2(j,y,list[i],172);
		}
		else{
			print2(j,y,list[i],12);
		}

	}
			}
			else{
			if(temp==-2)
				break;
			}
			}

			}


		}
}
void menu(){
	char list[6][30]={{"1-continue"},{"2-new game"},{"3-new game in one level"},{"3-setting"},{"4-structure"},{"5-exit"}};
	int choice=0,key,temp;
	int list2[3]={252,253,0};
	int x=10,y=yGame/2;
	int  j=x;
	print(1,1,' ',1);
	system("cls");
	limit_menu();
	for(int i=0 ; i<6 ; i++,j=j+3){
		if(i==choice){
			print2(j,y,list[i],172);
		}
		else{
			print2(j,y,list[i],12);
		}

	}
	while(1){
	if(kbhit()){
			temp=select(choice,6);
			if(temp>=0){
			choice=temp;
			print(1,1,' ',1);
			system("cls");
			limit_menu();
			int  j=x;
		for(int i=0 ; i<6 ; i++,j=j+3){
		if(i==choice){
			print2(j,y,list[i],172);
		}
		else{
			print2(j,y,list[i],12);
		}

	}
			}
			else{
			if(temp==-1){
				switch(choice){
					case 0:
						game(1,list2[2],list2[0],list2[1],1,0);
						break;
					case 1:
						game(1,list2[2],list2[0],list2[1],0,0);
						break;
					case 2:
						level_menu(list2);
						break;
					case 3:
					int* temp;
					temp=setting_menu();
					list2[0]=temp[0];
					list2[1]=temp[1];
					list2[2]=temp[2];
						break;

					case 4:
						print(1,1,' ',1);
						system("cls");
						limit_menu();
						print2(x+1,y-4,"you can move your spacecraft by arrow key.",8);
						print2(x+4,y-4,"if you enter the e key the change the hape of shot",8);
						print2(x+6,y-4,"if you enter the r or w key you leave a bomb that",8);
						print2(x+8,y-4,"destory a same enemy color whit bomb.",8);
						print2(x+10,y-4,"if you enter scap key you exite game but  you",8);
						print2(x+12,y-4,"can continiue the game on same time you exit..",8);
						print2(x+14,y-4,"you can change setting of game --color,speed... ",8);
						Sleep(5000);
						break;
					case 5:
						return;
				}
	int  j=x;
	print(1,1,' ',1);
	system("cls");
	limit_menu();
	for(int i=0 ; i<6 ; i++,j=j+3){
		if(i==choice){
			print2(j,y,list[i],172);
		}
		else{
			print2(j,y,list[i],12);
		}

	}
			}
			else{
			if(temp==-2)
				break;
			}
			}


	}
	}

}
void set_enemy(list_enemy* arr_enemy,int color){
	arr_enemy->arr[arr_enemy->n++]=(enemy*)malloc(sizeof(enemy));
	arr_enemy->arr[arr_enemy->n-1]->x=0;
	int temp=random(1,yGame-1);
	arr_enemy->arr[arr_enemy->n-1]->y=temp;
	arr_enemy->arr[arr_enemy->n-1]->color=color;
}

void initial_sat(ship* sat){
/*
	 0 1 2
	 3 4 5 6 7
  9 10 11 12 13 14 8



*/

			/* /O\
			  //O\\
			 //OOO\\

			*/
		sat->y[0]=yGame/2-1;
		sat->x[0]=xGame-3;
		sat->y[1]=yGame/2;
		sat->x[1]=xGame-3;
		sat->y[2]=yGame/2+1;
		sat->x[2]=xGame-3;
		sat->y[3]=yGame/2-2;
		sat->x[3]=xGame-2;
		sat->y[4]=yGame/2-1;
		sat->x[4]=xGame-2;
		sat->y[5]=yGame/2;
		sat->x[5]=xGame-2;
		sat->y[6]=yGame/2+1;
		sat->x[6]=xGame-2;
		sat->y[7]=yGame/2+2;
		sat->x[7]=xGame-2;
		sat->y[8]=yGame/2+3;
		sat->x[8]=xGame-1;
		sat->y[9]=yGame/2-3;
		sat->x[9]=xGame-1;
		sat->y[10]=yGame/2-2;
		sat->x[10]=xGame-1;
		sat->y[11]=yGame/2-1;
		sat->x[11]=xGame-1;
		sat->y[12]=yGame/2;
		sat->x[12]=xGame-1;
		sat->y[13]=yGame/2+1;
		sat->x[13]=xGame-1;
		sat->y[14]=yGame/2+2;
		sat->x[14]=xGame-1;
}
void print_sat(ship* sat,int flag) {
	int color_sat=240;
	if(flag){
print(sat->x[0],sat->y[0],'/',color_sat);
print(sat->x[1],sat->y[1],'O',color_sat);
print(sat->x[2],sat->y[2],'\\',color_sat);
print(sat->x[3],sat->y[3],'/',color_sat);
print(sat->x[4],sat->y[4],'/',color_sat);
print(sat->x[5],sat->y[5],'O',color_sat);
print(sat->x[6],sat->y[6],'\\',color_sat);
print(sat->x[7],sat->y[7],'\\',color_sat);
print(sat->x[9],sat->y[9],'/',color_sat);
print(sat->x[10],sat->y[10],'/',color_sat);
print(sat->x[11],sat->y[11],'O',color_sat);
print(sat->x[12],sat->y[12],'O',color_sat);
print(sat->x[13],sat->y[13],'O',color_sat);
print(sat->x[14],sat->y[14],'\\',color_sat);
print(sat->x[8],sat->y[8],'\\',color_sat);
	}
	else{
		for(int i=0 ; i< 15 ; i++){
		print(sat->x[i],sat->y[i],' ',color_sat);
		}
	}

}
void initial_shot(list_shot* arr_shot,int i,int j,int color){
	arr_shot->arr[arr_shot->n]=(shot*)malloc(sizeof(shot));
	arr_shot->arr[arr_shot->n]->x=i-1;
	arr_shot->arr[arr_shot->n]->y=j;
	arr_shot->arr[arr_shot->n]->color=color;
	arr_shot->n++;
}

void move_enemy(list_enemy* arr_enemy,int flag){
	enemy* temp;
	for(int i=0 ; i<arr_enemy->n ; i++){
		if(arr_enemy->arr[i]->x==xGame||arr_enemy->arr[i]->y>=yGame||arr_enemy->arr[i]->x<0){
		if(flag==0){
		arr_enemy->n--;
		temp=arr_enemy->arr[i];
		arr_enemy->arr[i]=arr_enemy->arr[arr_enemy->n];
		arr_enemy->arr[arr_enemy->n]=temp;
		free(arr_enemy->arr[arr_enemy->n]);
		}
		else{
			if(i%2==0){
		int temp1=arr_enemy->n-2;
		temp=arr_enemy->arr[i];
		arr_enemy->arr[i]=arr_enemy->arr[temp1];
		arr_enemy->arr[temp1]=temp;
		arr_enemy->arr[temp1]->x=-100;
			}
			else{
				int temp1=arr_enemy->n-1;
				while(temp1>0){
					if(arr_enemy->arr[temp1]->x>0)
						break;
					else
						temp1=temp1-2;
				}
		temp=arr_enemy->arr[i];
		arr_enemy->arr[i]=arr_enemy->arr[temp1];
		arr_enemy->arr[temp1]=temp;
		arr_enemy->arr[temp1]->x=-100;
			}
			if(arr_enemy->n>2){
			if(arr_enemy->arr[arr_enemy->n-2]->x<0 &&arr_enemy->arr[arr_enemy->n-1]->x<0){
			free(arr_enemy->arr[arr_enemy->n-1]);
			free(arr_enemy->arr[arr_enemy->n-2]);
			arr_enemy->n=arr_enemy->n-2;
			}
			}
		}
		}
		else{
			if(flag==0 || i%2==0){
			arr_enemy->arr[i]->x++;
			}
			else{
				arr_enemy->arr[i]->x++;
				arr_enemy->arr[i]->y=arr_enemy->arr[i]->y+2;
			}
		}
			}

}


void move_shot(list_shot* arr_shot,int flag){
	int i ;
	switch(flag){
		case 0:
			i=0;
			break;
		case 1:
			i=0;
			break;
		case 2:
			i=1;
			break;
		case 3:
			i=2;
			break;
	}
	while(i<arr_shot->n){
		if((arr_shot->arr[i]->x<=0 ) || (arr_shot->arr[i]->y<=0 ) || arr_shot->arr[i]->y >=yGame){
			int temp1=arr_shot->n;
		switch(flag){
		case 0:
			arr_shot->n=arr_shot->n-1;
			break;
		case 1:
			arr_shot->n=arr_shot->n-3;
			break;
		case 2:
			arr_shot->n=arr_shot->n-2;
			break;
		case 3:
			arr_shot->n=arr_shot->n-1;
			break;
	}
			shot* temp;
		temp=arr_shot->arr[i];
		arr_shot->arr[i]=arr_shot->arr[arr_shot->n];
		arr_shot->arr[arr_shot->n]=temp;
		arr_shot->arr[arr_shot->n]->x=-12;
		arr_shot->n=temp1;
		if(arr_shot->n>3){
		if(arr_shot->arr[arr_shot->n-1]->x<=-10 && arr_shot->arr[arr_shot->n-2]->x<=-10 && arr_shot->arr[arr_shot->n-3]->x<=-10){
		free(arr_shot->arr[arr_shot->n-1]);
		free(arr_shot->arr[arr_shot->n-2]);
		free(arr_shot->arr[arr_shot->n-3]);
		arr_shot->n=arr_shot->n-3;
		}
		}
		}

			if(flag==2){
				arr_shot->arr[i]->x-=3;
				arr_shot->arr[i]->y-=2;
			}
			else{
				if(flag==3){
					arr_shot->arr[i]->x-=3;
					arr_shot->arr[i]->y+=2;
				}
				else{
					if(flag==1){
				arr_shot->arr[i]->x-=3;
					}
					else{
					arr_shot->arr[i]->x-=2;
					}
				}
			}
		if(flag)
			i=i+3;
		else
			i=i+1;
		}

}


int check_shot(list_enemy* arr_enemy,list_shot* arr_shot,int flag){
	shot* temp1;
	enemy* temp2;
	for(int i=0 ; i< arr_shot->n ;i++){
			for(int j=0 ; j<arr_enemy->n ; j++){
				if( (flag==0 && arr_shot->arr[i]->x <= arr_enemy->arr[j]->x && arr_shot->arr[i]->y==arr_enemy->arr[j]->y && arr_shot->arr[i]->color==arr_enemy->arr[j]->color)|| (flag>0 && arr_shot->arr[i]->x <= arr_enemy->arr[j]->x && arr_shot->arr[i]->y==arr_enemy->arr[j]->y && arr_shot->arr[i]->color==arr_enemy->arr[j]->color) ){
					print(arr_enemy->arr[j]->x,arr_enemy->arr[j]->y,' ',color_backg);
					arr_enemy->n--;
					temp2=arr_enemy->arr[j];
					arr_enemy->arr[j]=arr_enemy->arr[arr_enemy->n];
					arr_enemy->arr[arr_enemy->n]=temp2;
					free(arr_enemy->arr[arr_enemy->n]);
					if(flag){
					for(int j=i ; j>=0 ; j=j-3){
							if(j==0)
								flag=1;
							if(j==1)
								flag=2;
							if(j==2)
								flag=3;
						}
					}
			int temp1=arr_shot->n;
		switch(flag){
		case 0:
			arr_shot->n=arr_shot->n-1;
			break;
		case 1:
			arr_shot->n=arr_shot->n-3;
			break;
		case 2:
			arr_shot->n=arr_shot->n-2;
			break;
		case 3:
			arr_shot->n=arr_shot->n-1;
			break;
	}
			shot* temp;
		temp=arr_shot->arr[i];
		arr_shot->arr[i]=arr_shot->arr[arr_shot->n];
		arr_shot->arr[arr_shot->n]=temp;
		arr_shot->arr[arr_shot->n]->x=-12;
		arr_shot->n=temp1;
		if(arr_shot->arr[arr_shot->n-1]->x<=-10 && arr_shot->arr[arr_shot->n-2]->x<=-10 && arr_shot->arr[arr_shot->n-3]->x<=-10){
		free(arr_shot->arr[arr_shot->n-1]);
		free(arr_shot->arr[arr_shot->n-2]);
		free(arr_shot->arr[arr_shot->n-3]);
		arr_shot->n=arr_shot->n-3;
		}

					return 1;
				}
			}
	}
			return 0;
}


int check_sat(ship* sat, list_enemy* arr_enemy)
	{
		for(int i=0 ; i<15 ; i++){
			for(int j=0 ; j<arr_enemy->n ; j++){
				if(sat->x[i]==arr_enemy->arr[j]->x && sat->y[i]==arr_enemy->arr[j]->y ){
					return 1;
				}
			}
		}


	return 0;
}
void move_sat(ship* sat,int position){
switch(position){
	case 72://up
	if(sat->x[0] !=0){
		for(int i=0 ; i<15 ; i++){
			sat->x[i]--;
		}
	}
	break;
	case 80://down
		if(sat->x[9] !=xGame){
		for(int i=0 ; i<15 ; i++){
			sat->x[i]++;
		}
	}
	break;
	case 75://left
		if(sat->y[9] !=0){
		for(int i=0 ; i<15 ; i++){
			sat->y[i]--;
		}
	}
	break;
	case 77://right
		if(sat->y[8] !=yGame){
		for(int i=0 ; i<15 ; i++){
			sat->y[i]++;
		}
	}
	break;
	}

}

void mahdodeh(void){
for(int i=1 ; i<xGame+1 ; i++)
	print(i,yGame+2,'|',29);
for(int j=1 ; j<yGame+1 ; j++)
	print(xGame+1,j,'-',29);

}

void game(int level,int speed_limit,int color_lvl1,int color_lvl2,int continu,int flag_level){
	if(continu==0){
	system("cls");
	print2(15,15,"level",152);
	print(15,22,level+'0',152);
	Sleep(1000);
	}
	print2(1,1," ",color_backg);
	system("cls");
	speed_limit=speed_limit*(5);
	int tse,tss,tme,tms,tmb;
	int color_enemy,color_shot,color_bomb;
	list_bomb arr_bomb;
	int score;
	list_shot arr_shot;
	int key,condition=1;
	int flag_shot;
	int win;
	ship sat;
	list_enemy arr_enemy;
	if(continu==0){
	win=5;
	arr_bomb.n=0;
	score=0;
	flag_shot=0;
	arr_shot.n=0;
	arr_enemy.n=0;
	initial_sat(&sat);
	}
	else{
	FILE* pf=fopen("data.txt","rb");
	fread(&win,sizeof(int),1,pf);
	if(win==1){
	gotoxy(20,20);
	print2(20,20,"you last win game",250);
	Sleep(1000);
	return;
	}
	if(win==0){
	gotoxy(20,20);
	print2(20,20,"you lose last  game",250);
	Sleep(1000);
	return;
	}
	fread(&xGame,sizeof(int),1,pf);
	fread(&yGame,sizeof(int),1,pf);
	fread(&arr_shot.n,sizeof(int),1,pf);
	for(int i=0 ; i<arr_shot.n ;i++){
	arr_shot.arr[i]=(shot*)malloc(sizeof(shot));
	fread(arr_shot.arr[i],sizeof(shot),1,pf);
	}

	fread(&arr_bomb.n,sizeof(int),1,pf);
	for(int i=0 ; i<arr_bomb.n ;i++){
	fread(&arr_bomb.arr[i],sizeof(bomb),1,pf);
	}
	fread(&sat,sizeof(ship),1,pf);
	fread(&arr_enemy.n,sizeof(int),1,pf);
	for(int i=0 ; i<arr_enemy.n ;i++){
		arr_enemy.arr[i]=(enemy*)malloc(sizeof(enemy));
	fread(arr_enemy.arr[i],sizeof(enemy),1,pf);
	}
	fread(&level,sizeof(int),1,pf);
	fread(&score,sizeof(int),1,pf);
	fread(&flag_shot,sizeof(int),1,pf);
	fread(&flag_level,sizeof(int),1,pf);

	fclose(pf);
	}
	switch(level){
	case 1:
		tse=1500-speed_limit;
		tme=1500-speed_limit;
		tss=300-speed_limit;
		tms=200-speed_limit;
		tmb=600-speed_limit;
		color_enemy=color_lvl1;
		color_shot=color_lvl1;
		color_bomb=color_lvl1;
		arr_bomb.len=4;
		break;
	case 2:
		tse=2000-speed_limit;
		tme=1500-speed_limit;
		tss=250-speed_limit;
		tms=150-speed_limit;
		tmb=450-speed_limit;
		color_enemy=color_lvl2;
		color_shot=color_lvl2;
		color_bomb=color_lvl2;
		arr_bomb.len=5;
		break;
	case 3:
		tse=1500-speed_limit;
		tme=1000-speed_limit;
		tss=200-speed_limit;
		tms=80-speed_limit;
		tmb=250-speed_limit;
		arr_bomb.len=9;
		break;
	case 4:
		tse=1900-speed_limit;
		tme=800-speed_limit;
		tss=200-speed_limit;
		tms=60-speed_limit;
		tmb=250-speed_limit;
		arr_bomb.len=9;
		break;
	}
	int flag_enemy=0;
	if(level==4)
		flag_enemy=1;
	mahdodeh();
	set_time();
	time_t time_shot;
	time_t pt_shot;
	time_t t_enemy;
	time_t pt_enemy;
	print_sat(&sat,1);
	time_t temp;
	temp=clock();
	time_t time_bomb=clock();
	time_shot=clock();
	t_enemy=clock();
	pt_shot=clock();
	pt_enemy=clock();
	print2(2,2," ",color_backg);
	gotoxy(1,xGame+2);
	printf("the number of your bomb=%d  ",arr_bomb.len-arr_bomb.n);
	print2(2,2," ",color_backg);
	gotoxy(1,xGame+3);
	printf("your score : %d   ",score);
	while(condition){
		if(clock()-t_enemy>tse){
			if(level>=3){
			color_enemy=random(249,252);
			}
			if(level==4){
			set_enemy(&arr_enemy,color_enemy);
			}
			set_enemy(&arr_enemy,color_enemy);
			t_enemy=clock();
		}
		if(clock()-pt_enemy>tme){
		pt_enemy=clock();
		for(int i=0 ; i<arr_enemy.n ;i++){
			if(arr_enemy.arr[i]->x>0 && arr_enemy.arr[i]->y<yGame)
		print(arr_enemy.arr[i]->x,arr_enemy.arr[i]->y,' ',arr_enemy.arr[i]->color);

		}
		if(level==4){
		move_enemy(&arr_enemy,1);
		}
		else
			move_enemy(&arr_enemy,0);
		for(int i=0 ; i<arr_enemy.n ;i++){
			if(arr_enemy.arr[i]->x>0&& arr_enemy.arr[i]->y<yGame)
			print(arr_enemy.arr[i]->x,arr_enemy.arr[i]->y,'*',arr_enemy.arr[i]->color);
		}
		}
		if(clock()-time_shot>tss){
		time_shot=clock();
		if(level>=3)
			color_shot=random(249,252);
		if(flag_shot==1){
		initial_shot(&arr_shot,sat.x[1],sat.y[1],color_shot);
		initial_shot(&arr_shot,sat.x[1],sat.y[1],color_shot);
		initial_shot(&arr_shot,sat.x[1],sat.y[1],color_shot);
		}
		else{
		initial_shot(&arr_shot,sat.x[1],sat.y[1],color_shot);
		}
		}
		if(clock()-pt_shot>tms){
			pt_shot=clock();
			for(int i=0 ; i<arr_shot.n ; i++){
				if(arr_shot.arr[i]->x>0 && arr_shot.arr[i]->y>0){
			print(arr_shot.arr[i]->x,arr_shot.arr[i]->y,' ',color_backg);
				}
			}
			if(check_shot(&arr_enemy,&arr_shot,flag_shot)){
			score++;
			if(flag_level==0){
			if(score>=20){
				if(level==4){
					win=1;
					condition=0;
				}
				else{
				game(level+1,speed_limit,color_lvl1,color_lvl2,0,0);
				return;
				}
			}
			}
			print2(2,2," ",color_backg);
			gotoxy(1,xGame+3);
			printf("your score : %d",score);
			}
			if(flag_shot==0){
			move_shot(&arr_shot,0);
			}
			else{

				move_shot(&arr_shot,1);
				move_shot(&arr_shot,2);
				move_shot(&arr_shot,3);


			}
			for(int i=0 ; i<arr_shot.n ; i++){
				if(arr_shot.arr[i]->x>0 && arr_shot.arr[i]->y>0)
					print(arr_shot.arr[i]->x,arr_shot.arr[i]->y,94,arr_shot.arr[i]->color);
			}
		}

		if(clock()-time_bomb>tmb){
			time_bomb=clock();
			for(int i = 0 ; i <arr_bomb.n ; i++){
				if(arr_bomb.arr[i].exist){
				print(arr_bomb.arr[i].x,arr_bomb.arr[i].y,' ',arr_bomb.arr[i].color);
				arr_bomb.arr[i].x=arr_bomb.arr[i].x-2;
				print(arr_bomb.arr[i].x,arr_bomb.arr[i].y,'!',arr_bomb.arr[i].color);
				if(arr_bomb.arr[i].x<xGame/2){
					print(arr_bomb.arr[i].x,arr_bomb.arr[i].y,' ',arr_bomb.arr[i].color);
					arr_bomb.arr[i].exist=0;
					for(int i=0 ; i<arr_shot.n ; i++){
						if(arr_shot.arr[i]->x>0)
						print(arr_shot.arr[i]->x,arr_shot.arr[i]->y,' ',arr_shot.arr[i]->color);
						free(arr_shot.arr[i]);
						}
						arr_shot.n=0;
				for(int j=0 ; j<arr_enemy.n ; j++){
				if( arr_enemy.arr[j]->color==arr_bomb.arr[i].color ){
					enemy* temp2;
					if(arr_enemy.arr[j]->x >= 0){
						print(arr_enemy.arr[j]->x,arr_enemy.arr[j]->y,' ',arr_bomb.arr[i].color);
					}
						free(arr_enemy.arr[j]);
					score++;

				}
				}
					if(flag_level==0){
					if(score>=20){
						if(level==4){
							win==1;
							condition=0;
							break;
						}
						else{
						game(level+1,speed_limit,color_lvl1,color_lvl2,0,0);
						return;
						}
					}
					}
					print2(2,2," ",color_backg);
					gotoxy(1,xGame+3);
					printf("your score : %d",score);
				int temp1=0;
				for(int j=0 ; j<arr_enemy.n ; j++){
					if(arr_enemy.arr[j]->x>0){
						arr_enemy.arr[temp1]=arr_enemy.arr[j];
						temp1++;
					}
				}
				arr_enemy.n=temp1;
				}
			}
			}
		}

		if(_kbhit()){
			if((key = getch()) != 27){
				if(key==0 || key== 224){
					print_sat(&sat,0);
					move_sat(&sat,getch());
					print_sat(&sat,1);
				}
				else{
					if(key=='e'){
						for(int i=0 ; i<arr_shot.n ; i++){
						print(arr_shot.arr[i]->x,arr_shot.arr[i]->y,' ',arr_shot.arr[i]->color);
						free(arr_shot.arr[i]);
						}
						arr_shot.n=0;
						if(flag_shot==1){
						flag_shot=0;
						}
						else{
						flag_shot=1;
						}
					}

					else{
						if(key=='w'){
							if(arr_bomb.n<arr_bomb.len){
								if(level==3||level==4){
								arr_bomb.arr[arr_bomb.n].color=random(249,252);
								}
								else{
									arr_bomb.arr[arr_bomb.n].color=color_bomb;
								}
								arr_bomb.arr[arr_bomb.n].x=sat.x[3]-1;
								arr_bomb.arr[arr_bomb.n].y=sat.y[3];
								arr_bomb.arr[arr_bomb.n].exist=1;
							arr_bomb.n++;

							}
							print2(2,2," ",color_backg);
							gotoxy(1,xGame+2);
							printf("the number of your bomb=%d",arr_bomb.len-arr_bomb.n);
						}
						else{
							if(key=='r'){
								if(arr_bomb.n<arr_bomb.len){
								if(level==3||level==4){
								arr_bomb.arr[arr_bomb.n].color=random(249,252);
								}
								else{
									arr_bomb.arr[arr_bomb.n].color=color_bomb;
								}
								arr_bomb.arr[arr_bomb.n].x=sat.x[7]-1;
								arr_bomb.arr[arr_bomb.n].y=sat.y[7];
								arr_bomb.n++;
								arr_bomb.arr[arr_bomb.n].exist=1;
							}
						print2(2,2," ",color_backg);
						gotoxy(1,xGame+2);
						printf("the number of your bomb=%d",arr_bomb.len-arr_bomb.n);
						}


					}
				}
				}
				}

			else{
				win=-2;
				break;
			}
		}
		if(check_sat(&sat,&arr_enemy)){
			win=0;
			break;
		}




}
	if(win==0)
	{
	print(15,15,' ',202);
	system("cls");
	print2(15,15," you lose",202);
	Sleep(1000);
	}
	if(win==1){
	print(15,15,' ',172);
	system("cls");
	print2(15,15," you win",172);
	Sleep(1000);
	}
	FILE* pf=fopen("data.txt","wb");
	fwrite(&win,sizeof(int),1,pf);
	fwrite(&xGame,sizeof(int),1,pf);
	fwrite(&yGame,sizeof(int),1,pf);
	fwrite(&arr_shot.n,sizeof(int),1,pf);
	for(int i=0 ; i<arr_shot.n ;i++){
	fwrite(arr_shot.arr[i],sizeof(shot),1,pf);
	}
	fwrite(&arr_bomb.n,sizeof(int),1,pf);
	for(int i=0 ; i<arr_bomb.n ;i++){
	fwrite(&arr_bomb.arr[i],sizeof(bomb),1,pf);
	}
	fwrite(&sat,sizeof(ship),1,pf);
	fwrite(&arr_enemy.n,sizeof(int),1,pf);
	for(int i=0 ; i<arr_enemy.n ;i++){
	fwrite(arr_enemy.arr[i],sizeof(enemy),1,pf);
	}
	fwrite(&level,sizeof(int),1,pf);
	fwrite(&score,sizeof(int),1,pf);
	fwrite(&flag_shot,sizeof(int),1,pf);
	fwrite(&flag_level,sizeof(int),1,pf);
	fclose(pf);

}

int main(){
	menu();
	return 0;
}
