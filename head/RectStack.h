#ifndef RECTSTACK_H
#define RECTSTACK_H

#include "stdafx.h"
#include "Game.h"
#include <iostream>

class RectStack{
private:
	//int rect_num;
	int rect_num;//必须初始化！
	int rect_judge();
public:
	RectStack(){
		rect_num=0;
	}
	int rect_insert(game_rect input);//插入函数
	void rect_init();//初始化函数
	game_rect target[2];//用于判断的栈
};

void RectStack::rect_init(){
	this->target[0]=game_rect();
	this->target[1]=game_rect();
	rect_num=0;
}

int RectStack::rect_insert(game_rect input){
	int judge=-1;
	this->target[this->rect_num]=input;//进入栈
	this->rect_num++;//栈后移一位
	if( this->rect_num==2 )
	{
		judge=this->rect_judge();
		return judge;//返回判断结果.1为相同，0为不同，-1为未进行判断
	}
	return judge;
}

int RectStack::rect_judge(){
	if( this->target[0].colortype == this->target[1].colortype && ( matchDirect(target[0],target[1]) || matchOneCorner(target[0],target[1]) || matchTwoCorner( target[0],target[1] ) ) ){
		//this.rect_init();
		return 1;//判断为相同则返回1
	}
	else{
		this->rect_init();//判断失败，初始化
		return 0;//判断为不同则返回0
	}
}
#endif
