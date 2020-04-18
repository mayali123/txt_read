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
	void keyPressEvent(QKeyEvent* e);
	void mousePressEvent(QMouseEvent* e);
signals:
	void saveEvent();
	void mousepress();
	void addDown(bool i);
};
