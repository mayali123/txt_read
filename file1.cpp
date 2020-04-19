#include "file1.h"

file1::file1(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->num = 0;		//��ͳ�����ֽ��г�ʼ��
	isSave = true;		//�����Ƿ񱣴�Ϊtrue
	this->setFixedSize(800, 600);			//���ù̶���С
	this->setWindowTitle("�ļ���ȡ��");
	this->setWindowIcon(QIcon(":/file1/Resources/12.jpg"));	//����ͼƬ


	//�˵���
	QMenuBar* bar = menuBar();
	setMenuBar(bar);

	QMenu* file = bar->addMenu("�ļ�");
	QMenu* format = bar->addMenu("��ʽ");
	QMenu* look = bar->addMenu("�鿴");
	QAction* newFile = file->addAction("�½�");
	QAction* open = file->addAction("��");
	QAction* saveAction = file->addAction("����   Ctrl+s");
	QAction* close = file->addAction("�ر� ");
	QAction* setcolor = format->addAction("������ɫ");
	QAction* setfont = format->addAction("��������");
	QAction* add = look->addAction("�Ŵ�       Ctrl+�Ⱥ�");
	QAction* down = look->addAction("��С       Ctrl+����");
	//״̬��
	bar2 = statusBar();
	setStatusBar(bar2);
	text = new QLabel(QString("����%1").arg(this->num));
	label = new QLabel(this);
	bar2->addWidget(text);					//��ʾ����
	bar2->addWidget(label);					//��ʾ�Ƿ񱣴�




	//��ʾ���ֿ�
	text2 = new MytTextEdit(this);
	text2->move(0, bar->height() + 50);			//�������ֿ��λ��
	text2->resize(this->width(), this->height() - bar2->height() - bar->height() - 50);//�������ֿ�Ĵ�С
	

	//��"�ر�"�Ĵ����ʹ��ڵĹر�������һ��
	connect(close, &QAction::triggered, [=]() {
		this->close();
		});
	//��"��"�Ĵ������ļ��Ĵ򿪵ĺ���������һ��
	connect(open, &QAction::triggered, [=]() {
		this->openFile();
		});
	//�����ļ��İ�ť�ĵ�����ļ��Ĵ򿪵ĺ���������һ��
	connect(ui.pushButton, &QPushButton::clicked, [=]() {
		this->openFile();
		});
	//��"����"�Ĵ������ļ�����ĺ���������һ��
	connect(saveAction, &QAction::triggered, [=]() {
		savefile();
		label->setText("�ѱ���");		
		isSave = true;						//���Ƿ񱣴���Ϊtrue
		});
	//����ǽ���ݼ�Ctrl+s���¼����ļ�����ĺ���������һ��
	connect(text2, &MytTextEdit::saveEvent, [=]() {
		savefile();
		label->setText("�ѱ���");
		isSave = true;
		});
	//����鵽TextEdit�ĸı����Զ������ļ�������һ��
	connect(text2, &MytTextEdit::textChanged, [=]() {
		qDebug() << "δ����";
		save();
		this->num = wordNumber(text2->toPlainText());		//�������
		text->setText(QString("����%1").arg(this->num));	//��������
		label->setText("δ����");							//��label��Ϊδ����
		isSave = false;										//���Ƿ񱣴���Ϊfalse
		});
	//��"�½�"����ʱ
	connect(newFile, &QAction::triggered, [=]() {
		QTextStream out(&saveFile);					//��������ø���saveFile��һ���µ��ļ�������Ҫ��saveFile�ÿ�
		out << "";									//��saveFile�ÿ�
		text2->setText("");							//����ʾ��Ҳ�ÿ�
		filename = QFileDialog::getSaveFileName(this, "�½�", "./�½��ı��ļ�", "(*.txt)");//�ļ��Ի���
		saveFile.copy(saveFile.fileName(), filename);//����
		ui.lineEdit->setText(filename);				//���ý��ļ����������õ���ʾ�ļ����Ŀ�
		});
	//��"��������"����ʱ
	connect(setfont, &QAction::triggered, [=]() {
		bool ok;				//���boolûʲô���壬��Ҫ��getFont()��Ҫһ��boolֵ
		font=QFontDialog::getFont(&ok,this);//��������
		readfile(saveFile.fileName(),false);//������ʾ����
		});
	//��"��������"����ʱ
	connect(setcolor, &QAction::triggered, [=]() {
		color =  QColorDialog::getColor(QColor(255,0,0),this);//������ɫ��������Ĭ��ѡ�е���ɫ��ɫ
		readfile(saveFile.fileName(), false);//������ʾ����
		});
	//��Ctrl+ =(�Ŵ�)��Ctrl+ -(��С)������ʱ������adddown�ۺ���
	connect(text2,&MytTextEdit::addDown,this,&file1::adddown);
	//��"�Ŵ�"����ʱ
	connect(add, &QAction::triggered, [=]() {
		adddown(true);
		});
	//��"��С"����ʱ
	connect(down, &QAction::triggered, [=]() {
		adddown(false);
		});
}

//���ļ��Ի���
void file1::openFile()
{
	filename= QFileDialog::getOpenFileName(this,"���ļ�","/","(*.txt)");//�ļ��Ի���
	readfile(filename);													//��ʾ�ļ�
}

//��������
int  file1::wordNumber(QString p)
{
	p += '\0';				//��������Ĵ����˼�ǹ�����ʼ�Ŀո�Ȼ�����33(!)<=p[i]��ASC��ֵ<=125(})
	//qDebug() << p;		//��  ��һ�������������Ǹ���Χ������ǿո�,��count++
	int i = 0, count = 0;	//���  33(!)<=p[i]��ASC��ֵ<=125(}) ������ �� ���ǿո�
	while (p[i] == ' ')		//���ģ��WPS,�Գ����ģ�˵���˶�����(�i�n�i)
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
		//qDebug() << "�����"<<count << endl;
	}
	qDebug() << count << endl;
	return count;
	
}

//�Զ������ļ�
void  file1::save()
{

	//QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	saveFile.setFileName("./a.txt");				//���ļ����浽��ǰ�ļ�·����
	
	if (saveFile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream out(&saveFile);
		out << text2->toPlainText();				//����ʾ�ֵĿ��ϵ�����д�뵽saveFileȥ
	}
	qDebug() << "����";
	
}


//ת�������ʽ
QString file1::GetCorrectUnicode(const QByteArray& ba)
{
	QTextCodec::ConverterState state;		//���������https://blog.csdn.net/weixin_30512089/article/details/96186976
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

//��д�ر��¼�
void  file1::closeEvent(QCloseEvent * event)
{	//����Ƿ񱣴��ļ���false,����Ҫ��ʾ�Ƿ�Ҫ�����ļ�
	if (isSave == false)
	{	//��������Ի����ṩ���棬�����棬ȡ������ѡ��
		int i=QMessageBox::question(this, "�˳�", QString("����Ҫ�����ı��浽%1��?").arg(filename), QMessageBox::Save, QMessageBox::No, QMessageBox::Cancel);
		if (QMessageBox::Save == i)
		{
			fileOpen.close();								//�����ļ�
			if (saveFile.remove(filename))
				saveFile.copy(saveFile.fileName(), filename);
		}
		else if (QMessageBox::No==i)
		{
			this->close();					//�رմ���
			qDebug() << "NO";
		}
		else if (QMessageBox::Cancel==i)
		{
			event->ignore();				//��������¼�
		}
	}
	else//ֱ�ӹر�
		this->close();
}

//��ȡ�ļ������ļ���ʾ���� ���Ǹ�bool�������ж��Ƿ�Ҫ�ı���ʾ���ļ�����Ĭ��Ϊtrue
void file1::readfile(QString filename, bool isChangeFileName)
{
	QByteArray a;
	this->num = 0;						//��ʼ������
	fileOpen.setFileName(filename);
	fileOpen.open(QIODevice::ReadOnly);	//��ֻ�ķ�ʽ�򿪶��ļ�

	while (!fileOpen.atEnd())			//���������δ
	{
		a += fileOpen.readLine();		//��ȡһ������
	}
	this->num += wordNumber(a);			//�������
	text2->setFont(font);				//��������
	text2->setTextColor(color);			//������ɫ
	text2->setText(GetCorrectUnicode(a));//ת��
	if(isChangeFileName)				//���Ҫ�ı���ʾ���ļ���
		ui.lineEdit->setText(filename);
	text->setText(QString("����%1").arg(this->num));//��������
	bar2->addWidget(text);					
	isSave = true;						//���Ƿ񱣴��ļ���Ϊtrue
}

//д���ļ�
void file1::savefile()
{
	fileOpen.close();
	qDebug() << "���";
	if (filename.isEmpty())		//����ļ���Ϊ���Ŵ���һ���µ�
	{
		qDebug() << "�ļ��ǿ�";
		filename = QFileDialog::getSaveFileName(this, "�½�", "./�½��ı��ļ�", "(*.txt)");
		saveFile.copy(saveFile.fileName(), filename);
		ui.lineEdit->setText(filename);		//�����ļ���
		qDebug() << "123";
	}
	else if (saveFile.remove(filename))//�Ƴ�ԭ�����ļ������Զ�������ļ����ƹ�ȥ���Ǹ�·����
	{
		saveFile.copy(saveFile.fileName(), filename);
		qDebug() << "ɾ��";
	}
}
//�Ŵ����С��true���ǷŴ�
void file1::adddown(bool num)
{
	QTextCursor cursor;								//���
	cursor = text2->textCursor();			//��ʾ���ֵ����
	qDebug() << "λ�ã�"<<text2->textCursor().position();
	int i=text2->textCursor().position();//���濪ʼ����λ��
	if (num)			
	{
		font.setPointSize(font.pointSize()+5);	//���ֱ��
		readfile(saveFile.fileName(), false);	//��������ʾ����
	}
	else
	{
		font.setPointSize(font.pointSize() - 5);//���ֱ�С
		readfile(saveFile.fileName(), false);	//��������ʾ����
	}
	cursor.setPosition(i);
	text2->setTextCursor(cursor);		//����ʾ������õ���ʼ��λ��
}

