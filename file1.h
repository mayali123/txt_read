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
	void openFile();								//打开文件对话框
	int wordNumber( QString p);						//计算字数
	void save();									//写入文件
	int num;										//保存字数
	MytTextEdit*text2;								//显示文字框
	QLabel* text,*label;							//显示文件路径和是否保存
	QString filename;								//保存文件路径
	QStatusBar* bar2;								//打开文件的按钮
	bool isSave;									//用于检查是否保存
	QFile fileOpen, saveFile;						//用于打开文件和保存文件
	QString GetCorrectUnicode(const QByteArray& ba);//转化编码格式
	void  closeEvent(QCloseEvent* event);			//关闭文件
	void readfile(QString filenam,bool isChangeFileName=true);					//读取文件并把文件显示出来
	bool dddd;
	QFont font;										//保存设置好的字体
	QColor color;									//保存设置好的颜色
	void savefile();								//保存文件
	int cursorPosition;								//保存鼠标的位置
	QTextCursor cursor;								//鼠标
public slots:
	void adddown(bool num);							//放大和缩小
private:
	Ui::file1Class ui;
};
