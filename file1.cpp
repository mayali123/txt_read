#include "file1.h"

file1::file1(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->num = 0;		//对统计数字进行初始化
	isSave = true;		//设置是否保存为true
	this->setFixedSize(800, 600);			//设置固定大小
	this->setWindowTitle("文件读取器");
	this->setWindowIcon(QIcon(":/file1/Resources/12.jpg"));	//加载图片


	//菜单栏
	QMenuBar* bar = menuBar();
	setMenuBar(bar);

	QMenu* file = bar->addMenu("文件");
	QMenu* format = bar->addMenu("格式");
	QMenu* look = bar->addMenu("查看");
	QAction* newFile = file->addAction("新建");
	QAction* open = file->addAction("打开");
	QAction* saveAction = file->addAction("保存   Ctrl+s");
	QAction* close = file->addAction("关闭 ");
	QAction* setcolor = format->addAction("设置颜色");
	QAction* setfont = format->addAction("设置字体");
	QAction* add = look->addAction("放大       Ctrl+等号");
	QAction* down = look->addAction("缩小       Ctrl+减号");
	//状态栏
	bar2 = statusBar();
	setStatusBar(bar2);
	text = new QLabel(QString("字数%1").arg(this->num));
	label = new QLabel(this);
	bar2->addWidget(text);					//显示字数
	bar2->addWidget(label);					//显示是否保存




	//显示文字框
	text2 = new MytTextEdit(this);
	text2->move(0, bar->height() + 50);			//设置文字框的位置
	text2->resize(this->width(), this->height() - bar2->height() - bar->height() - 50);//设置文字框的大小
	

	//将"关闭"的触发和窗口的关闭连接在一起
	connect(close, &QAction::triggered, [=]() {
		this->close();
		});
	//将"打开"的触发和文件的打开的函数连接在一起
	connect(open, &QAction::triggered, [=]() {
		this->openFile();
		});
	//将打开文件的按钮的点击和文件的打开的函数连接在一起
	connect(ui.pushButton, &QPushButton::clicked, [=]() {
		this->openFile();
		});
	//将"保存"的触发和文件保存的函数连接在一起
	connect(saveAction, &QAction::triggered, [=]() {
		savefile();
		label->setText("已保存");		
		isSave = true;						//将是否保存设为true
		});
	//这个是将快捷键Ctrl+s的事件与文件保存的函数连接在一起
	connect(text2, &MytTextEdit::saveEvent, [=]() {
		savefile();
		label->setText("已保存");
		isSave = true;
		});
	//将检查到TextEdit的改变与自动保存文件函数在一起
	connect(text2, &MytTextEdit::textChanged, [=]() {
		qDebug() << "未保存";
		save();
		this->num = wordNumber(text2->toPlainText());		//检测字数
		text->setText(QString("字数%1").arg(this->num));	//设置字数
		label->setText("未保存");							//将label设为未保存
		isSave = false;										//将是否保存设为false
		});
	//当"新建"触发时
	connect(newFile, &QAction::triggered, [=]() {
		QTextStream out(&saveFile);					//这个就是用复制saveFile创一个新的文件，所以要将saveFile置空
		out << "";									//将saveFile置空
		text2->setText("");							//将显示框也置空
		filename = QFileDialog::getSaveFileName(this, "新建", "./新建文本文件", "(*.txt)");//文件对话框
		saveFile.copy(saveFile.fileName(), filename);//复制
		ui.lineEdit->setText(filename);				//设置将文件的名字设置到显示文件名的框
		});
	//当"设置字体"触发时
	connect(setfont, &QAction::triggered, [=]() {
		bool ok;				//这个bool没什么意义，主要是getFont()需要一个bool值
		font=QFontDialog::getFont(&ok,this);//设置字体
		readfile(saveFile.fileName(),false);//重新显示文字
		});
	//当"设置字体"触发时
	connect(setcolor, &QAction::triggered, [=]() {
		color =  QColorDialog::getColor(QColor(255,0,0),this);//设置颜色，并设置默认选中的颜色红色
		readfile(saveFile.fileName(), false);//重新显示文字
		});
	//当Ctrl+ =(放大)和Ctrl+ -(减小)被按下时，触发adddown槽函数
	connect(text2,&MytTextEdit::addDown,this,&file1::adddown);
	//当"放大"触发时
	connect(add, &QAction::triggered, [=]() {
		adddown(true);
		});
	//当"缩小"触发时
	connect(down, &QAction::triggered, [=]() {
		adddown(false);
		});
}

//打开文件对话框
void file1::openFile()
{
	filename= QFileDialog::getOpenFileName(this,"打开文件","/","(*.txt)");//文件对话框
	readfile(filename);													//显示文件
}

//计算字数
int  file1::wordNumber(QString p)
{
	p += '\0';				//这个函数的大概意思是过掉开始的空格，然后如果33(!)<=p[i]的ASC码值<=125(})
	//qDebug() << p;		//且  下一个不是在上面那个范围里面或是空格,则count++
	int i = 0, count = 0;	//如果  33(!)<=p[i]的ASC码值<=125(}) 不满足 且 不是空格
	while (p[i] == ' ')		//这个模仿WPS,试出来的，说多了都是泪(╥﹏╥)
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

//自动保存文件
void  file1::save()
{

	//QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	saveFile.setFileName("./a.txt");				//将文件保存到当前文件路径下
	
	if (saveFile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream out(&saveFile);
		out << text2->toPlainText();				//将显示字的框上的文字写入到saveFile去
	}
	qDebug() << "保存";
	
}


//转化编码格式
QString file1::GetCorrectUnicode(const QByteArray& ba)
{
	QTextCodec::ConverterState state;		//这个是来自https://blog.csdn.net/weixin_30512089/article/details/96186976
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
{	//如果是否保存文件是false,则需要提示是否要保存文件
	if (isSave == false)
	{	//弹出问题对话框，提供保存，不保存，取消三个选项
		int i=QMessageBox::question(this, "退出", QString("你想要将更改保存到%1吗?").arg(filename), QMessageBox::Save, QMessageBox::No, QMessageBox::Cancel);
		if (QMessageBox::Save == i)
		{
			fileOpen.close();								//保存文件
			if (saveFile.remove(filename))
				saveFile.copy(saveFile.fileName(), filename);
		}
		else if (QMessageBox::No==i)
		{
			this->close();					//关闭窗口
			qDebug() << "NO";
		}
		else if (QMessageBox::Cancel==i)
		{
			event->ignore();				//忽略这个事件
		}
	}
	else//直接关闭
		this->close();
}

//读取文件并把文件显示出来 ，那个bool是用来判断是否要改变显示的文件名，默认为true
void file1::readfile(QString filename, bool isChangeFileName)
{
	QByteArray a;
	this->num = 0;						//初始化字数
	fileOpen.setFileName(filename);
	fileOpen.open(QIODevice::ReadOnly);	//以只的方式打开读文件

	while (!fileOpen.atEnd())			//如果不在文未
	{
		a += fileOpen.readLine();		//读取一段文字
	}
	this->num += wordNumber(a);			//检测字数
	text2->setFont(font);				//设置字体
	text2->setTextColor(color);			//设置颜色
	text2->setText(GetCorrectUnicode(a));//转码
	if(isChangeFileName)				//如果要改变显示的文件名
		ui.lineEdit->setText(filename);
	text->setText(QString("字数%1").arg(this->num));//设置字数
	bar2->addWidget(text);					
	isSave = true;						//将是否保存文件设为true
}

//写入文件
void file1::savefile()
{
	fileOpen.close();
	qDebug() << "点击";
	if (filename.isEmpty())		//如果文件名为空着创建一个新的
	{
		qDebug() << "文件是空";
		filename = QFileDialog::getSaveFileName(this, "新建", "./新建文本文件", "(*.txt)");
		saveFile.copy(saveFile.fileName(), filename);
		ui.lineEdit->setText(filename);		//设置文件名
		qDebug() << "123";
	}
	else if (saveFile.remove(filename))//移除原来的文件，将自动保存的文件复制过去到那个路径下
	{
		saveFile.copy(saveFile.fileName(), filename);
		qDebug() << "删除";
	}
}
//放大和缩小，true则是放大
void file1::adddown(bool num)
{
	QTextCursor cursor;								//鼠标
	cursor = text2->textCursor();			//显示文字的鼠标
	qDebug() << "位置："<<text2->textCursor().position();
	int i=text2->textCursor().position();//保存开始光标的位置
	if (num)			
	{
		font.setPointSize(font.pointSize()+5);	//将字变大
		readfile(saveFile.fileName(), false);	//再重新显示文字
	}
	else
	{
		font.setPointSize(font.pointSize() - 5);//将字变小
		readfile(saveFile.fileName(), false);	//再重新显示文字
	}
	cursor.setPosition(i);
	text2->setTextCursor(cursor);		//把显示光标设置到开始的位置
}

