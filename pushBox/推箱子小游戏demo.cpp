#include<stdio.h>
#include<easyx.h>
#include<conio.h>

#define MAP_ROW 11 //行
#define MAP_COL 11 //列
#define Level 3//关卡数量

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
};//0空地 1围墙 2人 3箱子 4目的地 6人在目的地上 7箱子在目的地上

IMAGE img[15];//用来存地图的
int level = 0;//用来存关卡-玩的是哪一关
int down = 1;//人物的朝向
int flag = 0;//表示游戏是否继续
int map[MAP_ROW][MAP_COL];//用来保存当前玩的关卡

void LoadMap()//加载地图
{
	for(int i=0;i<MAP_ROW;i++)
	{
		for(int j=0;j<MAP_COL;j++)
		{
			map[i][j] = Map[level][i][j];
		}
	}
}

void DrawMap()//贴图
{
	BeginBatchDraw();//开始批量贴图
	putimage(0,0,&img[0]);//背景
	for(int i=0;i<MAP_ROW;i++)
	{
		for(int j=0;j<MAP_COL;j++)
		{
			switch(map[i][j])
			{
			case 1:
				putimage(j*50,i*50,&img[6]);//围墙  因为矩阵与坐标相反，所以i与j反着写
				break;
			case 2://人物
				switch(down)
				{
					case 1://向上
						putimage(j*50,i*50,&img[9],SRCAND);
						putimage(j*50,i*50,&img[down],SRCPAINT);
						break;
					case 2://向左
						putimage(j*50,i*50,&img[10],SRCAND);
						putimage(j*50,i*50,&img[down],SRCPAINT);
						break;
					case 3://向下
						putimage(j*50,i*50,&img[12],SRCAND);
						putimage(j*50,i*50,&img[down],SRCPAINT);
						break;
					case 4://向右
						putimage(j*50,i*50,&img[11],SRCAND);
						putimage(j*50,i*50,&img[down],SRCPAINT);
						break;
				}
				break;
				case 3:
					putimage(j*50,i*50,&img[5]);//箱子
					break;
				case 4://目的地
					putimage(j*50,i*50,&img[13],SRCAND);
					putimage(j*50,i*50,&img[7],SRCPAINT);
					break;
				case 6://人进了目的地，还是要显示的人
					switch(down)//看是那个人方向进的就贴那个方向的人
					{
						case 1://向上
							putimage(j*50,i*50,&img[9],SRCAND);
							putimage(j*50,i*50,&img[down],SRCPAINT);
							break;
						case 2://向左
							putimage(j*50,i*50,&img[10],SRCAND);
							putimage(j*50,i*50,&img[down],SRCPAINT);
							break;
						case 3://向下
							putimage(j*50,i*50,&img[12],SRCAND);
							putimage(j*50,i*50,&img[down],SRCPAINT);
							break;
						case 4://向右
							putimage(j*50,i*50,&img[11],SRCAND);
							putimage(j*50,i*50,&img[down],SRCPAINT);
							break;
					}
					break;
				case 7://箱子在目的地上
					putimage(j*50,i*50,&img[14],SRCAND);
					putimage(j*50,i*50,&img[8],SRCPAINT);
					break;	
			}
		}
	}
	EndBatchDraw();//结束批量贴图
}


void Play()//人物移动
{
	int x,y;//用来获取人的位置
	for(int i=0;i<MAP_ROW;i++)
	{
		for(int j=0;j<MAP_COL;j++)
		{
			if(map[i][j]==2 || map[i][j]==6)            //0空地 1围墙 2人 3箱子 4目的地 6人在目的地上 7箱子在目的地上
			{
				//获取人的位置
				x = i;
				y = j;
			}
		}
	}

	switch(getch())
	{
	case 'w':
	case 'W':
	case '72'://向上的键码
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
	case '75'://向下的键码
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
	case '80'://向左的键码
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
	case '77'://向右的键码														 //0空地 1围墙 2人 3箱子 4目的地 6人在目的地上 7箱子在目的地上
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


void Win()//判断输赢
{
	int boxnumber = 0;//记录箱子个数								//0空地 1围墙 2人 3箱子 4目的地 6人在目的地上 7箱子在目的地上
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
						flag=2;//游戏失败
					}
				}
			}
		}
	}
	if(boxnumber == 0)
	{
		flag=1;//游戏胜利
	}
}


int main()
{
	initgraph(MAP_ROW * 50,MAP_COL * 50);//窗口大小
	loadimage(&img[0],"素材/背景.jpg",550,550);
	loadimage(&img[1],"素材/人物上.jpg",50,50);
	loadimage(&img[2],"素材/人物左.jpg",50,50);
	loadimage(&img[3],"素材/人物下.jpg",50,50);
	loadimage(&img[4],"素材/人物右.jpg",50,50);
	loadimage(&img[5],"素材/箱子.jpg",50,50);
	loadimage(&img[6],"素材/围墙.jpg",50,50);
	loadimage(&img[7],"素材/目的地.jpg",50,50);
	loadimage(&img[8],"素材/箱子在目的地上面.jpg",50,50);
	loadimage(&img[9],"素材/上掩码图.jpg",50,50);
	loadimage(&img[10],"素材/左掩码图.jpg",50,50);
	loadimage(&img[11],"素材/右掩码图.jpg",50,50);
	loadimage(&img[12],"素材/下掩码图.jpg",50,50);
	loadimage(&img[13],"素材/目的地掩码图.jpg",50,50);
	loadimage(&img[14],"素材/箱子在目的地上面掩码图.jpg",50,50);
	LoadMap();
	DrawMap();
	while(true)
	{
		Play();
		DrawMap();
		Win();
		if(flag==1)
		{
			if(MessageBox(GetHWnd(),"你太厉害了","是否要进入下一关",MB_YESNO)==IDYES)
			{
				level++;
				if(level==3)
				{
					if(MessageBox(GetHWnd(),"是否重新开始第一关","最后一关了",MB_YESNO)==IDYES)
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
			if(MessageBox(GetHWnd(),"你失败了","是否要继续",MB_YESNO)==IDYES)
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