#include "file1.h"

file1::file1(QWidget* parent)
	: QMainWindow(parent)
{
	this->num = 0;
	isSave = true;
	ui.setupUi(this);
	this->setFixedSize(800, 600);
	this->setWindowTitle("文件读取器");
	this->setWindowIcon(QIcon(":/file1/Resources/12.jpg"));

	//bool isOpen=false;
	dddd = true;
	//菜单栏
	QMenuBar* bar = menuBar();
	setMenuBar(bar);

	QMenu* file = bar->addMenu("文件");
	QMenu* format = bar->addMenu("格式");
	QMenu* look = bar->addMenu("查看");
	QAction* newFile = file->addAction("新建");
	QAction* open = file->addAction("打开");
	QAction* close = file->addAction("关闭 ");
	QAction* saveAction = file->addAction("保存   Ctrl+s");
	QAction* setcolor = format->addAction("设置颜色");
	QAction* setfont = format->addAction("设置字体");
	QAction* add = look->addAction("放大       Ctrl+等号");
	QAction* down = look->addAction("缩小       Ctrl+减号");
	//状态栏
	bar2 = statusBar();
	setStatusBar(bar2);
	text = new QLabel(QString("字数%1").arg(this->num));
	label = new QLabel(this);
	bar2->addWidget(text);
	bar2->addWidget(label);




	//显示文字框
	text2 = new MytTextEdit(this);
	text2->move(0, bar->height() + 50);
	text2->resize(this->width(), this->height() - bar2->height() - bar->height() - 50);
	


	connect(close, &QAction::triggered, [=]() {
		this->close();
		});
	connect(open, &QAction::triggered, [=]() {
		this->openFile();
		});
	connect(ui.pushButton, &QPushButton::clicked, [=]() {
		this->openFile();
		});

	connect(saveAction, &QAction::triggered, [=]() {
		savefile();
		label->setText("已保存");
		isSave = true;
		});
	connect(text2, &MytTextEdit::saveEvent, [=]() {
		savefile();
		label->setText("已保存");
		isSave = true;
		});
	connect(text2, &MytTextEdit::textChanged, [=]() {
		qDebug() << "未保存";
		save();
		this->num = wordNumber(text2->toPlainText());
		text->setText(QString("字数%1").arg(this->num));
		label->setText("未保存");
		isSave = false;
		});

	connect(newFile, &QAction::triggered, [=]() {
		QTextStream out(&saveFile);
		out << "";
		text2->setText("");
		filename = QFileDialog::getSaveFileName(this, "新建", "./新建文本文件", "(*.txt)");
		saveFile.copy(saveFile.fileName(), filename);
		ui.lineEdit->setText(filename);
		});

	connect(setfont, &QAction::triggered, [=]() {
		bool ok;
		font=QFontDialog::getFont(&ok,this);
		readfile(saveFile.fileName(),false);
		});
	connect(setcolor, &QAction::triggered, [=]() {
		color =  QColorDialog::getColor(QColor(255,0,0),this);
		readfile(saveFile.fileName(), false);
		});

	connect(text2,&MytTextEdit::addDown,this,&file1::adddown);
	
	connect(add, &QAction::triggered, [=]() {
		adddown(true);
		});
	connect(down, &QAction::triggered, [=]() {
		adddown(false);
		});
}

//打开文件对话框
void file1::openFile()
{
	if(dddd)
		filename= QFileDialog::getOpenFileName(this,"打开文件","/","(*.txt)");
	dddd = true;
	readfile(filename);
}

//计算字数
int  file1::wordNumber(QString p)
{
	p += '\0';
	//qDebug() << p;
	int i = 0;
	double count = 0;
	while (p[i] == ' ')
		i++;
	while (p[i] != '\0')
	{
		if (p[i] >= 33 && p[i] <= 125)
		{
			if ((p[i + 1] == ' ') || !(p[i + 1] >= 33 && p[i + 1] <= 125))
				count++; 
		}
		else if (p[i] != ' ')
		{
			count +=1;			
			//qDebug() << i <<" ";
		}
		i++;
		//qDebug() << "里面的"<<count << endl;
	}
	qDebug() << count << endl;
	return count;
	
}

//保存文件
void  file1::save()
{

	//QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	saveFile.setFileName("./a.txt");
	
	if (saveFile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream out(&saveFile);
		out << text2->toPlainText().toUtf8();
	}
	qDebug() << "保存";
	
}


//转化编码格式
QString file1::GetCorrectUnicode(const QByteArray& ba)
{
	QTextCodec::ConverterState state;
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QString text = codec->toUnicode(ba.constData(), ba.size(), &state);
	if (state.invalidChars > 0)
	{
		text = QTextCodec::codecForName("GBK")->toUnicode(ba);
	}
	else
	{
		text = ba;
	}
	return text;
}

//重写关闭事件
void  file1::closeEvent(QCloseEvent * event)
{
	if (isSave == false)
	{
		int i=QMessageBox::question(this, "退出", QString("你想要将更改保存到%1吗?").arg(filename), QMessageBox::Save, QMessageBox::No, QMessageBox::Cancel);
		if (QMessageBox::Save == i)
		{
			fileOpen.close();
			if (saveFile.remove(filename))
				saveFile.copy(saveFile.fileName(), filename);
		}
		else if (QMessageBox::No==i)
		{
			this->close();
			qDebug() << "NO";
		}
		else if (QMessageBox::Cancel==i)
		{
			event->ignore();
		}
	}
	else
		this->close();
}

//读取文件并把文件显示出来
void file1::readfile(QString filename, bool isChangeFileName)
{
	QByteArray a;
	this->num = 0;
	fileOpen.setFileName(filename);
	fileOpen.open(QIODevice::ReadOnly);

	while (!fileOpen.atEnd())
	{
		a += fileOpen.readLine();
	}
	this->num += wordNumber(a);
	text2->setFont(font);
	text2->setTextColor(color);
	text2->setText(GetCorrectUnicode(a));
	if(isChangeFileName)
		ui.lineEdit->setText(filename);
	text->setText(QString("字数%1").arg(this->num));
	bar2->addWidget(text);
	isSave = true;
}

//保存文件
void file1::savefile()
{
	fileOpen.close();
	qDebug() << "点击";
	if (filename.isEmpty())
	{
		qDebug() << "文件是空";
		filename = QFileDialog::getSaveFileName(this, "新建", "./新建文本文件", "(*.txt)");
		saveFile.copy(saveFile.fileName(), filename);
		ui.lineEdit->setText(filename);
		qDebug() << "123";
	}
	else if (saveFile.remove(filename))
	{
		saveFile.copy(saveFile.fileName(), filename);
		qDebug() << "删除";
	}
}
//放大和缩小
void file1::adddown(bool num)
{
	QTextCursor cursor;
	cursor = text2->textCursor();
	if (num)
	{
		font.setPointSize(font.pointSize()+5);
		readfile(saveFile.fileName(), false);
		
	}
	else
	{
		font.setPointSize(font.pointSize() - 5);
		readfile(saveFile.fileName(), false);

	}
	text2->setTextCursor(cursor);
}

