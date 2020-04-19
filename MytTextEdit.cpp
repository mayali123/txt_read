#include "MytTextEdit.h"

MytTextEdit::MytTextEdit(QWidget* parent):QTextEdit(parent)
{
}
MytTextEdit::~MytTextEdit()
{
}
//重写键盘按下事件
void MytTextEdit::keyPressEvent(QKeyEvent* e)
{
	if ((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_S))
	{
		emit this->saveEvent();//发出保存的信号
	}
	else if ((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_Minus))//减 "-"
	{
		emit this->addDown(false);//发出缩小的信号
		qDebug() << "-";
	}
	else if ((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_Equal))//等于 "="
	{
		emit this->addDown(true);//发出放大的信号
		qDebug() << "=";
	}
	QTextEdit::keyPressEvent(e);//将事件交给父类处理
	
}
