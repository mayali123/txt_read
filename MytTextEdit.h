#pragma once
#include<QObject>
#include<QTextEdit>
#include<QKeyEvent>
#include<QDebug>
class MytTextEdit : public QTextEdit
{
	Q_OBJECT

public:
	MytTextEdit(QWidget*parent);
	~MytTextEdit();
	void keyPressEvent(QKeyEvent* e);				//重写键盘按下事件	
signals:
	void saveEvent();								//保存的信号								
	void addDown(bool i);							//放大和缩小的信号
};
