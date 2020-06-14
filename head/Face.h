#ifndef _FACE_H_
#define _FACE_H_

/*初始界面函数

功能：展示初始交互界面 

返回：无*/
void Face();
/*初始界面的选择函数

功能：规定交互界面的内容以及规格，创建并展示初始交互界面 

返回：无*/
int Face_Click_Choose( int key ,int WIDTH_C ,int HEIGHT_C );
/*初始界面的反应函数

参数：按照获取的参数调用界面

功能：根据整数而调用不同的界面

返回：无*/
void Choose_Face( int i );

#endif
