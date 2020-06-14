#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <atlstr.h>
#include <string>
#include <graphics.h>
#include "Editor.h"

using namespace std;

int Editor_Face(void);
/*
编辑关卡界面函数
功能：关闭图形界面，调用控制台并启动关卡编辑程序
参数：无
*/
int Editor_Face(void){
	closegraph();
	ifstream read_num( "./GameData/num.txt",ios::in );//读取记录关卡数的txt文件的文件输出流
	//ofstream update_num( "./GameData/num.txt",ios::out);//用于更新关卡数的文件输出流//不可放前！会清空！
	if( !read_num.is_open()){//防止文件打开失败
		cout << "关卡数文件打开失败！";
		Sleep(2000);
		return 0;
	}
	int game_num;
	read_num >> game_num;
	game_num++;//推移一关
	CString FileName;
	FileName.Format(_T("./GameData/%d.dat"),game_num);//_T是必要的！
	ofstream CreateGame(FileName,ios::out);
	cout << "***********************关卡编辑模块**************************" << endl;
	cout << "*************************************************************" << endl;
	cout << "请输入关卡名：" << endl;
	string game_name;
	cin >> game_name;
	CreateGame << game_name << endl;
	cout <<  "请输入作者名：" << endl;
	string game_author;
	cin >> game_author;
	CreateGame << game_author << endl;
	cout << "请输入行数:（不大于8）" << endl;
	int row_number;
	cin >> row_number;
	if( row_number < 0 || row_number > 8 ){
				cout << "输入错误！创建失败！";
				Sleep(2000);
				exit(EXIT_FAILURE);//错误退出
			}
	CreateGame << row_number << endl;
	cout << "请输入列数:（不大于8）" << endl;
	int col_number;
	cin >> col_number;
	if( col_number < 0 || col_number > 8 ){
				cout << "输入错误！创建失败！";
				Sleep(2000);
				exit(EXIT_FAILURE);//错误退出
			}
	CreateGame << col_number << endl;
	cout << "请输入0~7的整数，不同整数代表不同的色块:" << endl;
	for( int i = 0; i< row_number ; i++ ){
		cout << "请输入第" << i << "行的数据：" << endl;
		for( int j = 0 ; j< col_number ; j++ ){
			int input = -1;//用于判断输入是否正确的整数
			cin >> input;
			if( input < 0 || input > 7 ){
				cout << "输入错误！创建失败！";
				Sleep(2000);
				exit(EXIT_FAILURE);//错误退出
			}
			else{
				CreateGame << input << "\t" ;
			}
			cin.clear();//清空输入流
		}
		CreateGame << endl;
	}
	cout << "关卡编辑完成！" << endl;
	cout << "是否完成并保存关卡？(y确定）";
	string make_sure;
	cin >> make_sure;
	ofstream update_num( "./GameData/num.txt",ios::out);//用于更新关卡数的文件输出流
	if( make_sure == "y" ){
		cout << "保存成功！" << endl;
		update_num << game_num;
		read_num.close();
		update_num.close();
		CreateGame.close();//关闭流
		system("pause");
		return 1;
	}
	else{
		cout << "保存失败！" << endl;
		game_num--;
		update_num << game_num;//变回原样
		read_num.close();
		update_num.close();
		CreateGame.close();//关闭流
		system("pause");
		return 0;
	}
}
