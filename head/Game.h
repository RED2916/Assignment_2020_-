#ifndef _GAME_H_
#define _GAME_H_

#define WIDTH 800
#define HEIGHT 1000

#define COLSIZE 10
#define ROWSIZE 10

#define RCSIZE 8
#define RRSIZE 8

class game_rect{
public:
	game_rect(){
		colortype=-100;//-100代表无,-1代表边界
	}//必须设置，否则难以初始化
	game_rect( int num1, bool v_judge){
		colortype=num1;
		visible=v_judge;
	}
	/*game_rect( int num1, bool v_judge, int num2, int num3 ){
		colortype=num1;
		visible=v_judge;
		x=num2;
		y=num3;
	}//构造函数*/
	/*void operator=( game_rect target )//重载赋值语句,防止出现问题,似乎没有必要
	{
		colortype=target.colortype;
		visible=target.visible;
		x=target.x;
		y=target.y;
		x1=target.x1;
		x2=target.x2;
		y1=target.y1;
		y2=target.y2;
	}*/
	int colortype;
	bool visible;
	int x;
	int y;//记录逻辑坐标
	int x_m;
	int y_m;//记录匹配的坐标
	int x1,x2;//记录色块位置
	int y1,y2;//记录色块位置
};//用于记录色块的类//类需要放在函数前！

void Game_Face();
void Deal_game_data(game_rect game_data[RCSIZE][RRSIZE],game_rect game_real_data[COLSIZE][ROWSIZE],int p_col_num,int p_row_num);
void paint_game( int p_col_num,int p_row_num, game_rect game_data[RCSIZE][RRSIZE]);
int Game_Click_Choose( game_rect *target,game_rect game_data[RCSIZE][RRSIZE],int p_col_num,int p_row_num);
bool matchDirect(game_rect a,game_rect b);
bool matchOneCorner(game_rect a,game_rect b);
bool matchTwoCorner(game_rect a,game_rect b);
int judge_end_game( game_rect game_real_data[COLSIZE][ROWSIZE],int p_col_num,int p_row_num );

#endif
