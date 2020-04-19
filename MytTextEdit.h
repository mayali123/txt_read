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
	void keyPressEvent(QKeyEvent* e);				//��д���̰����¼�	
signals:
	void saveEvent();								//������ź�								
	void addDown(bool i);							//�Ŵ����С���ź�
};
