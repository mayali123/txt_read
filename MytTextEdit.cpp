#include "MytTextEdit.h"

MytTextEdit::MytTextEdit(QWidget* parent):QTextEdit(parent)
{
}
MytTextEdit::~MytTextEdit()
{
}
//��д���̰����¼�
void MytTextEdit::keyPressEvent(QKeyEvent* e)
{
	if ((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_S))
	{
		emit this->saveEvent();//����������ź�
	}
	else if ((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_Minus))//�� "-"
	{
		emit this->addDown(false);//������С���ź�
		qDebug() << "-";
	}
	else if ((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_Equal))//���� "="
	{
		emit this->addDown(true);//�����Ŵ���ź�
		qDebug() << "=";
	}
	QTextEdit::keyPressEvent(e);//���¼��������ദ��
	
}
