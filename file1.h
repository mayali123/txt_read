#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QtWidgets/QMainWindow>
#include "ui_file1.h"
#include"MytTextEdit.h"
#include<QMenuBar>
#include <QFileDialog>
#include<QFile>
#include<QStatusBar>
#include<QLabel>
#include<QTextEdit>
#include<QDebug>
#include<QKeyEvent>
#include<QTextCodec>
#include<QMessageBox>
#include <QColorDialog>
#include <QFontDialog> 
#include<QFont>
#include <QTextCursor>
class file1 : public QMainWindow
{
	Q_OBJECT

public:
	file1(QWidget *parent = Q_NULLPTR);
	void openFile();								//���ļ��Ի���
	int wordNumber( QString p);						//��������
	void save();									//�Զ������ļ�
	int num;										//��������
	MytTextEdit*text2;								//��ʾ���ֿ�
	QLabel* text,*label;							//��ʾ�������Ƿ񱣴�
	QString filename;								//�����ļ�·��
	QStatusBar* bar2;								//״̬��
	bool isSave;									//���ڼ���Ƿ񱣴�
	QFile fileOpen, saveFile;						//���ڴ��ļ��ͱ����ļ�
	QString GetCorrectUnicode(const QByteArray& ba);//ת�������ʽ
	void  closeEvent(QCloseEvent* event);			//��д�ر��¼�
	void readfile(QString filenam,bool isChangeFileName=true);					//��ȡ�ļ������ļ���ʾ����
	QFont font;										//�������úõ�����
	QColor color;									//�������úõ���ɫ
	void savefile();								//д���ļ�
	int cursorPosition;								//��������λ��
	
public slots:
	void adddown(bool num);							//�Ŵ����С�Ĳۺ���
private:
	Ui::file1Class ui;
};
