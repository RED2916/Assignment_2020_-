#include "stdafx.h"
#include <graphics.h>
#include <iostream>
#include <string>
#include <atlstr.h>//引入CString，从而使用UNICODE字符串
#include "Face.h"
#include "Game.h"
#include "RectStack.h"
#include <Windows.h>
#include <time.h>
#include "ChooseGame.h"

#define WIDTH 800
#define HEIGHT 800

#define COLSIZE 10
#define ROWSIZE 10

#define RCSIZE 8
#define RRSIZE 8

using namespace std;


/*class game_rect{
public:
	game_rect(){
		colortype=-100;//-100代表无,-1代表边界
	}//必须设置，否则难以初始化
	game_rect( int num1, bool v_judge){
		colortype=num1;
		visible=v_judge;
	}
	//game_rect( int num1, bool v_judge, int num2, int num3 ){
		//colortype=num1;
		//visible=v_judge;
		//x=num2;
		//y=num3;
	//}//构造函数
	int colortype;
	bool visible;
	int x;
	int y;//记录逻辑坐标
	int x1,x2;//记录色块位置
	int y1,y2;//记录色块位置
};//用于记录色块的类//类需要放在函数前！*/

//函数声明
void Game_Face() ;
void Deal_game_data(game_rect game_data[RCSIZE][RRSIZE],game_rect game_real_data[COLSIZE][ROWSIZE],int p_col_num,int p_row_num);
void paint_game( int p_col_num,int p_row_num, game_rect game_data[RCSIZE][RRSIZE]);
int Game_Click_Choose( game_rect *target,game_rect game_data[RCSIZE][RRSIZE],int p_col_num,int p_row_num);
bool matchDirect(game_rect a,game_rect b);
bool matchOneCorner(game_rect a,game_rect b);
bool matchTwoCorner(game_rect a,game_rect b);
int judge_end_game( game_rect game_real_data[COLSIZE][ROWSIZE],int p_col_num,int p_row_num );

//引用外部变量,必须写，否则会算作重复定义报错
extern CString game_name;
extern CString game_author;
extern int p_col_num,p_row_num;
extern game_rect game_data[RCSIZE][RRSIZE];

//全局变量声明
int g_colors[8]={0,0xFF5555,0xAAAAAA,0x55FF55,0x0000AA,0xFFFF55,0xFF55FF,0x55FFFF};//颜色的常数,共八种
MOUSEMSG move_game;
game_rect game_real_data[COLSIZE][ROWSIZE];//负责记录处理后的数据，负责在逻辑判断时使用


/*
int p_col_num=col_num,p_row_num=row_num;//此处会在编译时处理！会直接变成0，且不会更改
CString game_name=input_game_name;
CString game_author=input_game_author;
*/



/*游戏界面函数

功能：规定游戏界面的内容以及规格，创建并展示游戏界面 

返回：无*/

void Game_Face() 
{
	//外部变量区

	//extern CString game_name;
	//extern CString game_author;
	//extern int p_col_num,p_row_num;

	extern MOUSEMSG move_game;
	extern int g_colors[];
	extern game_rect game_real_data[COLSIZE][ROWSIZE];

	//本地变量区

	//待完善
	//string game_name="t1";//字符解码错误
	//string game_author="a1";

	//int game_name=123;//关卡名
	//int game_author=123;//关卡作者名

	

	long game_time;
	//int p_col_num=3,p_row_num=3;
	RectStack game_stack;

	//数据记录及处理
	/*//初始化已在ChooseGame模块中完成
	game_rect game_data[RCSIZE][RRSIZE]={{game_rect(0,true),game_rect(0,true),game_rect(1,true),game_rect(0,true)},
										{game_rect(2,true),game_rect(1,true),game_rect(2,true),game_rect(7,true)},
										{game_rect(3,true),game_rect(3,true),game_rect(7,true),game_rect(0,true)}};//用于初步记录关卡数据,并不是最终用于生成图片的数据；用于画图和点击时的判断
										*/
	//game_data[0]={ game_rect(0,TRUE),game_rect(0,TRUE),game_rect(1,TRUE)};//无法使用
	//game_rect game_real_data[COLSIZE][ROWSIZE];//负责记录处理后的数据，负责在逻辑判断时使用
	Deal_game_data( game_data, game_real_data,p_col_num,p_row_num);


	initgraph(WIDTH,HEIGHT);//长宽

	setbkcolor(RGB(251,248,241));//背景

	settextcolor(RGB(150,126,104));

	cleardevice();//清屏


	settextstyle(120,0, _T("微软雅黑"));//字体设置

	RECT r0={0,0,WIDTH,HEIGHT};

	drawtext(_T("游戏开始！"),&r0,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	Sleep(1000);

	cleardevice();//清屏

	/*settextstyle(70,0, _T("微软雅黑"));//字体设置

	RECT r1={WIDTH*1/5,HEIGHT*1/16,WIDTH*4/5,HEIGHT*1/4};

	drawtext(_T("游戏开始！"),&r1,DT_CENTER|DT_VCENTER|DT_SINGLELINE);*/


	clock_t time_start=clock();//开始计时

	BeginBatchDraw();

	settextstyle(30,0, _T("微软雅黑"));//字体设置

	RECT r1={WIDTH*1/2-90,0,WIDTH*1/2,HEIGHT*1/8};

	drawtext(_T("耗时："),&r1,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	settextstyle(30,0,_T("微软雅黑"));

	RECT r2={WIDTH*1/5,HEIGHT*1/8,WIDTH*4/5,HEIGHT*1/4};
	//drawtext(_T("关卡名：%s||关卡设计人：%s",&game_name,&game_author),&r2,DT_CENTER|DT_VCENTER|DT_SINGLELINE);//注意
	CString s1=_T("");//为了UNICODE编码
	s1.Format(_T("关卡名：%s||关卡设计人：%s"),game_name,game_author);//插入变量
	//s1.Format(_T("关卡名：%s||关卡设计人：%s"),game_name,game_author);//转化存在问题，作者和关卡名显示出错
	drawtext(s1,&r2,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	RECT r3={WIDTH/2-45,HEIGHT*7/8,WIDTH/2+45,HEIGHT};

	drawtext(_T("返回首页"),&r3,DT_CENTER|DT_VCENTER|DT_SINGLELINE);


	setbkcolor(RGB(251,248,241));

	settextcolor(RGB(150,126,104));//字体颜色

	settextstyle(30,0,_T("Microsoft Yahei Ul Boid"));

	//开始画色块


	EndBatchDraw();
	while(1)
	{
		//批量绘图
		int click_judge=0;//0代表无意义的点击
		int rect_judge=-1;//-1代表未进行判断
		game_rect r_a,r_b;
		//game_rect t_a,t_b;
		//int *target1,*target2;
		//int target1[2],target2[2];
		game_rect input;//初始化输入的色块
		int judge_end;

		//中途计时
		clock_t time_mid=clock();
		long mid_time=(time_mid-time_start)/1000;//计算时间:秒
		CString s3=_T("");//为了UNICODE编码
		s3.Format(_T("%ld秒"),mid_time);//插入变量

		settextstyle(30,0, _T("微软雅黑"));//字体设置
		RECT r5={WIDTH*1/2,0,WIDTH*1/2+90,HEIGHT*1/8};
		drawtext(s3,&r5,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

		move_game=GetMouseMsg();
		

		BeginBatchDraw();//注意
		paint_game(p_col_num,p_row_num,game_data);
		EndBatchDraw();

		if( move_game.uMsg==WM_LBUTTONDOWN)
		{
			click_judge=Game_Click_Choose( &input,game_data,p_col_num,p_row_num);//对点击进行判断
			if( click_judge == 2 ){
				Face();
				break;
			}
			if( click_judge == 1 ){
				rect_judge=game_stack.rect_insert(input);
				if( rect_judge == 1 ){
					r_a=game_real_data[game_stack.target[0].y][game_stack.target[0].x];//更新数据
					r_b=game_real_data[game_stack.target[1].y][game_stack.target[1].x];
					game_real_data[game_stack.target[0].y][game_stack.target[0].x].visible=false;
					game_real_data[game_stack.target[1].y][game_stack.target[1].x].visible=false;
					game_data[r_a.y_m][r_a.x_m].visible=false;
					game_data[r_b.y_m][r_b.x_m].visible=false;
					game_stack.rect_init();
				}
			}
		}
		if( judge_end_game( game_real_data,p_col_num,p_row_num )){
			break;
		}
		/*if(move_game.uMsg==WM_LBUTTONDOWN)
		{
			
			Game_Click_Choose( target1,game_data,p_col_num,p_row_num );//注意
			if(target1[0] < 0)//判断是否调用了“返回首页”
			{
				if( target1[1] == -1 )
				{
					//exit(0);//结束批量绘图
					Face();
					break;     
				}
			}
		}
		if(move_game.uMsg==WM_LBUTTONDOWN)
		{
			Game_Click_Choose( target2,game_data,p_col_num,p_row_num );
			if(target1[0] < 0)//待完善！
			{
				if( target1[1] == -1 )
				{
					//exit(0);//结束批量绘图
					Face();
					break;     
				}
			}
		}
		if(target1[0] >=0 ){
				r_a=game_data[target1[1]][target1[0]];
				r_b=game_data[target2[1]][target2[0]];
				t_a=game_real_data[r_a.y][r_a.x];
				t_b=game_real_data[r_b.y][r_b.x];
				if( matchDirect(t_a,t_b) || matchOneCorner(t_a,t_b) || matchTwoCorner( t_a,t_b ) )
				{
					game_data[target1[1]][target1[0]].visible = FALSE;
					game_data[target2[1]][target2[0]].visible= FALSE;
					game_real_data[r_a.y][r_a.x].visible=FALSE;
					game_real_data[r_b.y][r_b.x].visible=FALSE;
				}
			}
		if( judge_end_game( game_real_data,p_col_num,p_row_num )==1 ){
			Face();
		}*/

	}
	cleardevice();//清屏
	clock_t time_end=clock();//结束计时
	game_time=(time_end-time_start)/1000;

	settextstyle(70,0, _T("微软雅黑"));//字体设置

	RECT r_end={0,0,WIDTH,HEIGHT};

	CString s2=_T("");//为了UNICODE编码
	s2.Format(_T("恭喜通关！耗时：%ld秒"),game_time);//插入变量

	drawtext(s2,&r_end,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	Sleep(2000);
	Face();
}

/*游戏数据处理函数

功能：为关卡数据添加“边界”，用于逻辑判断

返回：无*/

void Deal_game_data(game_rect game_data[RCSIZE][RRSIZE],game_rect game_real_data[COLSIZE][ROWSIZE],int p_col_num,int p_row_num){//二维数组不需要传引用！
	for( int i=0;i< p_row_num+2;i++)//初始化并添加边界
	{
		for( int j=0; j<p_col_num+2;j++ )
		{
			game_real_data[i][j]=game_rect(-1,false);
			game_real_data[i][j].x=j;
			game_real_data[i][j].y=i;//全部数据给予坐标
		}
	}
	for( int i=0;i< p_row_num;i++)//添加数据
	{
		for( int j=0; j<p_col_num;j++ )
		{
			game_real_data[i+1][j+1]=game_data[i][j];//此处可能出bug，注意！
			game_data[i][j].x=j;
			game_data[i][j].y=i;
			game_real_data[i+1][j+1].x=j+1;
			game_real_data[i+1][j+1].y=i+1;
			game_real_data[i+1][j+1].x_m=j;
			game_real_data[i+1][j+1].y_m=i;
			game_data[i][j].x_m=j+1;
			game_data[i][j].y_m=i+1;//记录彼此间对应的坐标
		}//逻辑数据中，从（1，1）开始才是色块
	}
}

/*游戏画图函数

功能：画出矩形

返回：无*/

void paint_game( int p_col_num,int p_row_num, game_rect game_data[RCSIZE][RRSIZE]){
	extern int g_colors[];
	int border_left=WIDTH*1/5;
	int gap_WIDTH=(WIDTH*3/5)/p_col_num;
	int border_up=HEIGHT*1/4;
	int gap_HEIGHT=(HEIGHT*5/8)/p_row_num;
	for( int i=0 ; i<p_row_num; i++ )
	{
		for( int j=0;j<p_col_num;j++ )
		{
			if( game_data[i][j].visible == TRUE )
			{
				setfillcolor( g_colors[ game_data[i][j].colortype ] );
				solidrectangle( border_left+j*gap_WIDTH+10,border_up+i*gap_HEIGHT+10,border_left+(j+1)*gap_WIDTH-10,border_up+(i+1)*gap_HEIGHT-10);
				game_data[i][j].x1=border_left+j*gap_WIDTH+10;//记录色块坐标区域
				game_data[i][j].x2=border_left+(j+1)*gap_WIDTH-10;
				game_data[i][j].y1=border_up+i*gap_HEIGHT+10;
				game_data[i][j].y2=border_up+(i+1)*gap_HEIGHT-10;
			}
			else{
				setfillcolor( RGB(251,248,241) );//遮住已经不可见的色块
				solidrectangle( border_left+j*gap_WIDTH+10,border_up+i*gap_HEIGHT+10,border_left+(j+1)*gap_WIDTH-10,border_up+(i+1)*gap_HEIGHT-10);
			}
		}
	}
}

/*游戏界面的选择函数

功能：对鼠标的点击做出反应

返回：无*/

int Game_Click_Choose( game_rect *target,game_rect game_data[RCSIZE][RRSIZE],int p_col_num,int p_row_num) //注意变量名
{
	extern MOUSEMSG move_game ; //鼠标移动
	extern game_rect game_real_data[COLSIZE][ROWSIZE];
	if( move_game.x>WIDTH*1/5 && move_game.x < WIDTH*4/5 && move_game.y>HEIGHT*1/4 && move_game.y<HEIGHT*7/8)//在游戏区域内
	{
		int judge1=0;
		for( int i=0; i<p_row_num; i++)
		{
			for( int j=0 ; j<p_col_num; j++ )
			{
				if( move_game.x >game_data[i][j].x1 && move_game.x < game_data[i][j].x2 && move_game.y>game_data[i][j].y1 && move_game.y <game_data[i][j].y2)
				{
					judge1=1;//用于中断循环、提高效率
					*target=game_real_data[game_data[i][j].y_m][game_data[i][j].x_m];
					//break;
					return 1;
				}	
			}
			/*if( judge1 == 1)//用于中断循环、提高效率
			{
				return 1;//1代表点击了游戏区域
				break;
			}*/
		}
	}
	else if(move_game.x>WIDTH/2-45&&move_game.x<WIDTH/2+45&&move_game.y>HEIGHT*7/8 && move_game.y<HEIGHT)
	{
		return 2;//2代表了返回首页
	}
	else{
		return 0;//0代表了未进行正确的点击
	}
}

/*void Game_Click_Choose( int * target,game_rect game_data[RCSIZE][RRSIZE],int p_col_num,int p_row_num) //注意变量名
{
	int output[2];
	extern MOUSEMSG move_game ; //鼠标移动
	if( move_game.x>WIDTH*1/5 && move_game.x < WIDTH*4/5 && move_game.y>HEIGHT*1/4 && move_game.y<HEIGHT*7/8)//在游戏区域内
	{
		int judge1=0;
		for( int i=0; i<p_row_num; i++)
		{
			for( int j=0 ; j<p_col_num; j++ )
			{
				if( move_game.x>game_data[i][j].x1 && move_game.x < game_data[i][j].x2 && move_game.y>game_data[i][j].y1 && move_game.y<game_data[i][j].y2)
				{
					judge1=1;//待完善
					output[0]=game_data[i][j].x;
					output[1]=game_data[i][j].y;
					target = output;
					break;
				}	
			}
			if( judge1 == 1)//待完善
			{
				break;
			}
		}
	}
	else if(move_game.x>WIDTH/2-45&&move_game.x<WIDTH/2+45&&move_game.y>HEIGHT*7/8 && move_game.y<HEIGHT)
	{
		output[0]=-1;
		output[1]=-1;
		target = output;
	}
	else{
		output[0]=-1;
		output[1]=-2;
		target = output;
	}

}*/

/*判断结束函数

功能：判断是否游戏完成了

返回：游戏结束则返回1，为结束返回0*/


int judge_end_game( game_rect game_real_data[COLSIZE][ROWSIZE],int p_col_num,int p_row_num ){
	int judge=1;
	for( int i=0 ; i< p_row_num+1 ; i++ )
	{
		for( int j=0; j< p_col_num+1; j++ )
		{
			if( game_real_data[i][j].visible == TRUE )//一旦有一块仍是“可见的”，则未完成
			{
				judge=0;
			}
		}
	}
	return judge;
}




/*判断连接函数
功能：判断两个色块间能否用直线直接连接
返回：可则TRUE，不可则FALSE1*/

/*判断能否用直线相连*/
bool matchDirect(game_rect a,game_rect b){
	extern int p_col_num,p_row_num;
	extern game_rect game_real_data[COLSIZE][ROWSIZE];
	if( a.x == b.x && a.y == b.y ){//防止双击
		return false;
	}
	if(!(a.x == b.x || a.y == b.y)){
		return false;
	}
	 //a、b的横坐标相同时
	bool yMatch = false;
	bool xMatch = false;
	if(a.x == b.x)
	{
		yMatch = true;
		if(a.y > b.y)
		{
			for(int i = b.y + 1;i < a.y;++i)
			{
				if(game_real_data[a.x][i].visible == true){
					yMatch = false;
				}
			}
		}
		if(b.y > a.y)
		{
			for(int i = a.y + 1;i < b.y;++i)
			{
				if(game_real_data[a.x][i].visible == true){
				yMatch = false;
				}
			}
		}
	}
	 //a、b的纵坐标相同时
	if(a.y == b.y)
	{
		xMatch = true;
		if(a.x > b.x)
		{
			for(int i = b.x + 1;i < a.x;++i)
			{
				if(game_real_data[i][a.y].visible == true)
				{
					 xMatch = false;
				}
			 }
		 }
		if(b.x > a.x)
		{
			for(int i = a.x + 1;i < b.x;++i)
			{
				 if(game_real_data[i][a.y].visible == true)
				 {
					xMatch = false;
				 }
			}
		}
	}
	 return (xMatch || yMatch);
}

/*判断一个折角可否用相连*/
bool matchOneCorner(game_rect a,game_rect b)
{
	//连传两次二维数组会编译通不过
	extern int p_col_num,p_row_num;
	extern game_rect game_real_data[COLSIZE][ROWSIZE];
	if (game_real_data[b.y][a.x].visible == false && matchDirect(a,game_real_data[b.y][a.x]) && matchDirect(game_real_data[b.y][a.x],b))
	{
		//drawLine(a,p[a.x][b.y]);
		//drawLine(p[a.x][b.y],b);
		return true;
	}
	if (game_real_data[a.y][b.x].visible == false && matchDirect(a,game_real_data[a.y][b.x]) && matchDirect(game_real_data[a.y][b.x],b))
	{
		//drawLine(a,p[b.x][a.y]);
		//drawLine(p[b.x][a.y],b);
		return true;
	}
	return false;
}

/*判断拐两下是否可以*/
bool matchTwoCorner(game_rect a,game_rect b)
{
	extern int p_col_num,p_row_num; 
	extern game_rect game_real_data[COLSIZE][ROWSIZE];
	int i,j;
	for(i = a.y,j = a.x - 1;j >= 0;--j)
	{
		if(game_real_data[i][j].visible == true){
			break;
		}
		else if(matchOneCorner(b,game_real_data[i][j]))
		{
			//drawLine(a,p[i][j]);
			return true;
		}
	}
	for (i = a.y,j = a.x + 1;j < p_col_num;++j)
	{
		if(game_real_data[i][j].visible == true){
			break;
		}
		else if(matchOneCorner(b,game_real_data[i][j]))
		{
			 //drawLine(a,p[i][j]);
			 return true;
		}
	}
	for(i = a.y - 1,j =a.x ;i >= 0;--i)
	{
		if(game_real_data[i][j].visible == true){
			 break;
		}
		else if(matchOneCorner(b,game_real_data[i][j]))
		{
			//drawLine(a,p[i][j]);
			return true;
		}
	}
	for(i =b.y + 1 ,j = b.x;i < p_row_num;++i)
	{
		 if(game_real_data[i][j].visible == true){
		 break;
		 }
		else if(matchOneCorner(b,game_real_data[i][j]))
		{
			//drawLine(a,p[i][j]);
			return true;
		}
	}
	return false;
}

/*画线函数
功能：画连接线
参数：需要连接的两个*/
