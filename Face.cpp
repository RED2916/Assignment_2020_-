#include "stdafx.h"
#include <graphics.h>
#include <iostream>
#include "Face.h"
#include "Game.h"
#include "ChooseGame.h"
#include "Editor.h"

#define WIDTH 1000
#define HEIGHT 600

void Face();
int Face_Click_Choose(int WIDTH_C ,int HEIGHT_C );
void Choose_Face( int i );

using namespace std;

MOUSEMSG move_face;//获取鼠标位置,最好不要用move为名，似乎有冲突
/*初始界面函数

功能：展示初始交互界面 

返回：无*/
void Face() 
{
	extern MOUSEMSG move_face;
	int judge;

	int key=0;

	initgraph(WIDTH,HEIGHT);//长宽

	setbkcolor(RGB(251,248,241));//背景

	settextcolor(RGB(150,126,104));

	cleardevice();//清屏



	settextstyle(70,0, _T("方正行黑简体"));//字体设置

	RECT r1={0,0,WIDTH,HEIGHT/3};

	drawtext(_T("欢迎游玩连连看！"),&r1,DT_CENTER|DT_VCENTER|DT_SINGLELINE);



	settextstyle(30,0,_T("微软雅黑"));

	RECT r2={WIDTH/2-45,HEIGHT/3,WIDTH/2+45,HEIGHT/3+30};

	drawtext(_T("开始游玩"),&r2,DT_CENTER|DT_VCENTER|DT_SINGLELINE);



	RECT r3={WIDTH/2-45,HEIGHT/3+30,WIDTH/2+45,HEIGHT/3+60};

	drawtext(_T("编辑关卡"),&r3,DT_CENTER|DT_VCENTER|DT_SINGLELINE);



	RECT r4={WIDTH/2-45,HEIGHT/3+60,WIDTH/2+45,HEIGHT/3+90};

	drawtext(_T("退出程序"),&r4,DT_CENTER|DT_VCENTER|DT_SINGLELINE);





	setbkcolor(RGB(251,248,241));

	settextcolor(RGB(150,126,104));//字体颜色

	settextstyle(30,0,_T("Microsoft Yahei Ul Boid"));

	BeginBatchDraw();

	EndBatchDraw();

	while(1)

	{

		;//批量绘图

		judge=-1;

		move_face=GetMouseMsg();

		if(move_face.uMsg==WM_LBUTTONDOWN)

		{

			judge=Face_Click_Choose( WIDTH, HEIGHT );

			if(judge==0)

			{

				exit(0);//结束批量绘图

				break;

			}

			else if(judge>0)

			{
				if( judge == 1 ){
					Choose_Face(judge);
					break;
				}
				else{
					Editor_Face();
					break;
				}

			}
			
		}

	}

}

/*初始界面的选择函数

功能：规定交互界面的内容以及规格，创建并展示初始交互界面 

返回：无*/

int Face_Click_Choose( int WIDTH_C ,int HEIGHT_C ) //注意变量名
{

	//extern MOUSEMSG move_face,m ; /*鼠标移动*/
	extern MOUSEMSG move_face;
	if(move_face.x>WIDTH_C/2-45&&move_face.x<WIDTH_C/2+45&&move_face.y>HEIGHT_C/3&&move_face.y<HEIGHT_C/3+30)

	{

		return 1;
	}		
	else if(move_face.x>WIDTH_C/2-45&&move_face.x<WIDTH_C/2+45&&move_face.y>HEIGHT_C/3+30&&move_face.y<HEIGHT_C/3+60)
	{

		return 2;

	}

	else if(move_face.x>WIDTH_C/2-45&&move_face.x<WIDTH_C/2+45&&move_face.y>HEIGHT_C/3+60&&move_face.y<HEIGHT_C/3+90)
	{

		return 0;

	}

	else return -1;

}



/*初始界面的反应函数

参数：按照获取的参数调用界面

功能：根据整数而调用不同的界面

返回：无*/

void Choose_Face( int i )

{

	if( i==1 )//待完善

	{
		Choose_Game_Face();
	}

	if( i==2 )//待完善

	{


	}

}
