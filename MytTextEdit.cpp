#include "MytTextEdit.h"

MytTextEdit::MytTextEdit(QWidget* parent):QTextEdit(parent)
{
}
MytTextEdit::~MytTextEdit()
{
}

void MytTextEdit::keyPressEvent(QKeyEvent* e)
{
	if ((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_S))
	{
		emit this->saveEvent();
	}
	else if ((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_Minus))//��
	{
		emit this->addDown(false);
		qDebug() << "-";
	}
	else if ((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_Equal))//����
	{
		emit this->addDown(true);
		qDebug() << "+";
	}
	QTextEdit::keyPressEvent(e);
	
}
void MytTextEdit::mousePressEvent(QMouseEvent* e)
{
	emit this->mousepress();
	QTextEdit::mousePressEvent(e);
}

//Qt::Key_Minus -
//Qt::Key_Plus +