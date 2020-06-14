#include "stdafx.h"
#include <iostream>
#include <string>
#include "ChooseGame.h"
#include <graphics.h>
#include <fstream>
#include <atlstr.h>
#include "Game.h"

#define COLSIZE 10
#define ROWSIZE 10

#define RCSIZE 8
#define RRSIZE 8

using namespace std;

/*//引用外部变量
extern CString input_game_name;
extern CString input_game_author;
extern int col_num,row_num;
*/
CString game_name;
CString game_author;
int p_col_num,p_row_num;
game_rect game_data[RRSIZE][RCSIZE];

void Choose_Game_Face();

void Choose_Game_Face(){
	//应用全局变量
	//extern CString game_name;
	//extern int p_col_num,p_row_num;
	closegraph();
	ifstream game_num_input("./GameData/num.txt",ios::in);
	if( !game_num_input.is_open()){//防止文件打开失败
		cout << "关卡数文件打开失败！";
		Sleep(2000);
		exit(1);
	}
	int game_num;
	game_num_input >> game_num;//读取存在的关卡数量
	game_num_input.close();//关闭流，防止误操作
	cout << "**********************关卡选择模块*************************"<<endl;
	cout << "***********************************************************"<<endl;
	cout << "您好，亲爱的玩家：" << endl;
	cout << "目前我们拥有的关卡数为：" << game_num << endl;
	cout << "请输入对应整数，选择您希望游玩的关卡。"<< endl;

	int choose_num=-1;//记录选择的关卡
	while( true ){
		cout << "请输入你希望选择的关卡:" ;
		choose_num=-1;//初始化，防止遗留，且方便判断
		cin >> choose_num;
		if( choose_num < 0 || choose_num > game_num ){//防止误输入
			cout << "输入错误！请重新输入！" << endl;
			cin.clear();
		}
		else{
			break;
		}
	}

	CString file_name;
	file_name.Format(_T("./GameData/%d.dat"),choose_num);
	ifstream open_game_data(file_name,ios::in);//打开关卡数据

	if( !open_game_data.is_open()){//防止文件打开失败
		cout << "关卡数据打开失败！";
		Sleep(2000);
		exit(1);
	}

	string game_name_s,game_author_s;//临时记录，用于转换
	open_game_data >> game_name_s;
	game_name=game_name_s.c_str();
	//game_name.Format(_T("%s"),game_name_s.c_str());//失败//char *与CString间可以直接赋值！
	open_game_data >> game_author_s;
	game_author=game_author_s.c_str();
	//game_author.Format(_T("%s"),game_author_s.c_str());
	open_game_data >> p_col_num;
	open_game_data >> p_row_num;

	//cout << game_name.GetString()<< endl;//无法验证，此处存疑！
	//cout << game_author.GetString();

	for( int i=0 ; i< p_row_num ; i++ )
	{
		for( int j=0; j< p_col_num ;j++ )
		{
			int color_input=-100;
			open_game_data >> color_input;
			game_data[i][j]=game_rect(color_input,true);
		}
	}
	cout << "数据传输成功！准备开始游戏！" << endl;
	open_game_data.close();//关闭流
	Sleep(1000);
	Game_Face();
}
