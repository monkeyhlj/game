#include<stdio.h>
#include<easyx.h>
#include<conio.h>

#define MAP_ROW 11 //��
#define MAP_COL 11 //��
#define Level 3//�ؿ�����

int Map[Level][MAP_ROW][MAP_COL] = 
{
	{
	 0,1,1,1,1,1,1,1,1,1,0,
	 0,1,0,0,0,0,0,0,0,1,0,
	 0,1,0,1,1,1,1,1,0,1,0,
	 0,1,0,1,4,3,0,0,0,1,0,
	 0,1,0,1,1,1,1,1,0,1,0,
	 0,1,0,0,0,3,4,1,0,1,0,
	 0,1,2,0,0,3,4,1,0,1,0,
	 0,1,0,1,1,1,1,1,0,1,0,
	 0,1,0,0,0,0,0,0,0,1,0,
	 0,1,1,1,1,1,1,1,1,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,
	},
	{
	 0,1,1,1,1,1,1,1,1,1,0,
	 0,1,2,0,0,0,0,0,0,1,0,
	 0,1,0,1,1,1,1,1,0,1,0,
	 0,1,0,0,0,3,4,1,0,1,0,
	 0,1,0,1,1,1,1,1,0,1,0,
	 0,1,0,1,4,3,0,0,0,1,0,
	 0,1,0,1,4,3,0,0,0,1,0,
	 0,1,0,1,1,1,1,1,0,1,0,
	 0,1,0,0,0,0,0,0,0,1,0,
	 0,1,1,1,1,1,1,1,1,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,
	},
	{
	 1,1,1,1,1,1,1,1,1,1,1,
	 1,0,0,0,0,0,0,0,0,0,1,
	 1,0,2,0,0,3,0,0,0,0,1,
	 1,0,0,0,3,3,3,0,0,0,1,
	 1,0,0,3,4,3,4,3,0,0,1,
	 1,0,0,4,4,4,4,4,0,0,1,
	 1,0,0,3,4,4,4,3,0,0,1,
	 1,0,0,0,3,4,3,0,0,0,1,
	 1,0,0,0,0,0,0,0,0,0,1,
	 1,1,1,1,1,1,1,1,1,1,1,
	},
};//0�յ� 1Χǽ 2�� 3���� 4Ŀ�ĵ� 6����Ŀ�ĵ��� 7������Ŀ�ĵ���

IMAGE img[15];//�������ͼ��
int level = 0;//������ؿ�-�������һ��
int down = 1;//����ĳ���
int flag = 0;//��ʾ��Ϸ�Ƿ����
int map[MAP_ROW][MAP_COL];//�������浱ǰ��Ĺؿ�

void LoadMap()//���ص�ͼ
{
	for(int i=0;i<MAP_ROW;i++)
	{
		for(int j=0;j<MAP_COL;j++)
		{
			map[i][j] = Map[level][i][j];
		}
	}
}

void DrawMap()//��ͼ
{
	BeginBatchDraw();//��ʼ������ͼ
	putimage(0,0,&img[0]);//����
	for(int i=0;i<MAP_ROW;i++)
	{
		for(int j=0;j<MAP_COL;j++)
		{
			switch(map[i][j])
			{
			case 1:
				putimage(j*50,i*50,&img[6]);//Χǽ  ��Ϊ�����������෴������i��j����д
				break;
			case 2://����
				switch(down)
				{
					case 1://����
						putimage(j*50,i*50,&img[9],SRCAND);
						putimage(j*50,i*50,&img[down],SRCPAINT);
						break;
					case 2://����
						putimage(j*50,i*50,&img[10],SRCAND);
						putimage(j*50,i*50,&img[down],SRCPAINT);
						break;
					case 3://����
						putimage(j*50,i*50,&img[12],SRCAND);
						putimage(j*50,i*50,&img[down],SRCPAINT);
						break;
					case 4://����
						putimage(j*50,i*50,&img[11],SRCAND);
						putimage(j*50,i*50,&img[down],SRCPAINT);
						break;
				}
				break;
				case 3:
					putimage(j*50,i*50,&img[5]);//����
					break;
				case 4://Ŀ�ĵ�
					putimage(j*50,i*50,&img[13],SRCAND);
					putimage(j*50,i*50,&img[7],SRCPAINT);
					break;
				case 6://�˽���Ŀ�ĵأ�����Ҫ��ʾ����
					switch(down)//�����Ǹ��˷�����ľ����Ǹ��������
					{
						case 1://����
							putimage(j*50,i*50,&img[9],SRCAND);
							putimage(j*50,i*50,&img[down],SRCPAINT);
							break;
						case 2://����
							putimage(j*50,i*50,&img[10],SRCAND);
							putimage(j*50,i*50,&img[down],SRCPAINT);
							break;
						case 3://����
							putimage(j*50,i*50,&img[12],SRCAND);
							putimage(j*50,i*50,&img[down],SRCPAINT);
							break;
						case 4://����
							putimage(j*50,i*50,&img[11],SRCAND);
							putimage(j*50,i*50,&img[down],SRCPAINT);
							break;
					}
					break;
				case 7://������Ŀ�ĵ���
					putimage(j*50,i*50,&img[14],SRCAND);
					putimage(j*50,i*50,&img[8],SRCPAINT);
					break;	
			}
		}
	}
	EndBatchDraw();//����������ͼ
}


void Play()//�����ƶ�
{
	int x,y;//������ȡ�˵�λ��
	for(int i=0;i<MAP_ROW;i++)
	{
		for(int j=0;j<MAP_COL;j++)
		{
			if(map[i][j]==2 || map[i][j]==6)            //0�յ� 1Χǽ 2�� 3���� 4Ŀ�ĵ� 6����Ŀ�ĵ��� 7������Ŀ�ĵ���
			{
				//��ȡ�˵�λ��
				x = i;
				y = j;
			}
		}
	}

	switch(getch())
	{
	case 'w':
	case 'W':
	case '72'://���ϵļ���
		down=1;
		if(map[x-1][y]==0 || map[x-1][y]==4)
		{
			map[x][y]-=2;
			map[x-1][y]+=2;
		}
		else if(map[x-1][y]==3 || map[x-1][y]==7)
		{
			if(map[x-2][y]==0 || map[x-2][y]==4)
			{
				map[x][y]-=2;
				map[x-1][y]-=1;
				map[x-2][y]+=3;
			}
		}
		break;
	case 's':
	case 'S':
	case '75'://���µļ���
		down=3;
		if(map[x+1][y]==0 || map[x+1][y]==4)
		{
			map[x][y]-=2;
			map[x+1][y]+=2;
		}
		else if(map[x+1][y]==3 || map[x+1][y]==7)
		{
			if(map[x+2][y]==0 || map[x+2][y]==4)
			{
				map[x][y]-=2;
				map[x+1][y]-=1;
				map[x+2][y]+=3;
			}
		}
		break;
	case 'a':
	case 'A':
	case '80'://����ļ���
		down=2;
		if(map[x][y-1]==0 || map[x][y-1]==4)
		{
			map[x][y]-=2;
			map[x][y-1]+=2;
		}
		else if(map[x][y-1]==3 || map[x][y-1]==7)
		{
			if(map[x][y-2]==0 || map[x][y-2]==4)
			{
				map[x][y]-=2;
				map[x][y-1]-=1;
				map[x][y-2]+=3;
			}
		}
		break;
	case 'd':
	case 'D':
	case '77'://���ҵļ���														 //0�յ� 1Χǽ 2�� 3���� 4Ŀ�ĵ� 6����Ŀ�ĵ��� 7������Ŀ�ĵ���
		down=4;
		if(map[x][y+1]==0 || map[x][y+1]==4)
		{
			map[x][y]-=2;
			map[x][y+1]+=2;
		}
		else if(map[x][y+1]==3 || map[x][y+1]==7)
		{
			if(map[x][y+2]==0 || map[x][y+2]==4)
			{
				map[x][y]-=2;
				map[x][y+1]-=1;
				map[x][y+2]+=3;
			}
		}
		break;
	}
}


void Win()//�ж���Ӯ
{
	int boxnumber = 0;//��¼���Ӹ���								//0�յ� 1Χǽ 2�� 3���� 4Ŀ�ĵ� 6����Ŀ�ĵ��� 7������Ŀ�ĵ���
	for(int i=0;i<MAP_ROW;i++)
	{
		for(int j=0;j<MAP_COL;j++)
		{
			if(map[i][j] == 3)
			{
				boxnumber++;
			}
		}
	}
	for(i=0;i<MAP_ROW;i++)
	{
		for(int j=0;j<MAP_COL;j++)
		{
			if(map[i][j] == 3)
			{
				if(map[i+1][j]==1 || map[i-1][j]==1)
				{
					if(map[i][j-1]==1 || map[i][j+1]==1)
					{
						flag=2;//��Ϸʧ��
					}
				}
			}
		}
	}
	if(boxnumber == 0)
	{
		flag=1;//��Ϸʤ��
	}
}


int main()
{
	initgraph(MAP_ROW * 50,MAP_COL * 50);//���ڴ�С
	loadimage(&img[0],"�ز�/����.jpg",550,550);
	loadimage(&img[1],"�ز�/������.jpg",50,50);
	loadimage(&img[2],"�ز�/������.jpg",50,50);
	loadimage(&img[3],"�ز�/������.jpg",50,50);
	loadimage(&img[4],"�ز�/������.jpg",50,50);
	loadimage(&img[5],"�ز�/����.jpg",50,50);
	loadimage(&img[6],"�ز�/Χǽ.jpg",50,50);
	loadimage(&img[7],"�ز�/Ŀ�ĵ�.jpg",50,50);
	loadimage(&img[8],"�ز�/������Ŀ�ĵ�����.jpg",50,50);
	loadimage(&img[9],"�ز�/������ͼ.jpg",50,50);
	loadimage(&img[10],"�ز�/������ͼ.jpg",50,50);
	loadimage(&img[11],"�ز�/������ͼ.jpg",50,50);
	loadimage(&img[12],"�ز�/������ͼ.jpg",50,50);
	loadimage(&img[13],"�ز�/Ŀ�ĵ�����ͼ.jpg",50,50);
	loadimage(&img[14],"�ز�/������Ŀ�ĵ���������ͼ.jpg",50,50);
	LoadMap();
	DrawMap();
	while(true)
	{
		Play();
		DrawMap();
		Win();
		if(flag==1)
		{
			if(MessageBox(GetHWnd(),"��̫������","�Ƿ�Ҫ������һ��",MB_YESNO)==IDYES)
			{
				level++;
				if(level==3)
				{
					if(MessageBox(GetHWnd(),"�Ƿ����¿�ʼ��һ��","���һ����",MB_YESNO)==IDYES)
					{
						level=0;
						LoadMap();
						DrawMap();
						flag=0;
					}
					else break;
				}
				LoadMap();
				DrawMap();
				flag=0;
			}
			else break;
		}
		if(flag==2)
		{
			if(MessageBox(GetHWnd(),"��ʧ����","�Ƿ�Ҫ����",MB_YESNO)==IDYES)
			{
				LoadMap();
				DrawMap();
				flag=0;
			}
			else break;
		}
	}

	getchar();
	closegraph();
	return 0;
}