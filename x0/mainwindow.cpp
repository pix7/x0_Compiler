#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "global.h"
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include<QDebug>
#include<QPushButton>
#include <QValidator>
#include <QGridLayout>
#include <QFileDialog>
#include<QTextEdit>
#include <QInputDialog>
#include <QDialog>
#include <string>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->runAction, SIGNAL(triggered()), this, SLOT(run()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* 打开文件 */
void MainWindow::open() {
    QTextEdit* textEdit = new QTextEdit(this);
    QString path = QFileDialog::getOpenFileName(this,
        tr("Open File"),
        ".",
        tr("Text Files(*.txt)"));
    if (!path.isEmpty()) {
        QFile file(path);
        currentPath = path;
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Read File"),
                tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
    }
    else {
        QMessageBox::warning(this, tr("Path"),
            tr("You did not select any file."));
    }
//    init();
}

/* 保存文件 */
void MainWindow::save()
{
    QTextEdit* textEdit = new QTextEdit(this);
    QString path = currentPath;
    if (!path.isEmpty()) {
        QFile file(path);
        currentPath = path;
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write File"),
                tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << ui->textEdit->toPlainText();
        file.close();
    }
    else {
        QMessageBox::warning(this, tr("Path"),
            tr("You did not select any file."));
    }
}

/* 运行前保存输入文件 */
void  MainWindow::saveInputFile()
{
    //QTextEdit* textEdit = new QTextEdit(this);
    QString path = "D:/Users/DELL/Desktop/build-x0-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/finput.txt";
    if (!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write File"),
                tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << ui->textEdit_2->toPlainText();
        file.close();
    }
    else {
        QMessageBox::warning(this, tr("Path"),
            tr("You did not select any file."));
    }
}

void MainWindow::run()
{
save();			 /* 保存当前代码至文件创建或打开的路径 */
saveInputFile();     /* 保存输入文件 */
errornum=0;

QString file_name = QFileInfo(currentPath).fileName();
//string tempFileName = "./inputFiles/" +file_name.toStdString();
string tempFileName = file_name.toStdString();
const char* argFileName = tempFileName.c_str();
strcpy(fileName, argFileName);
char file[MAX_LEN_FILENAME + 1];
strcpy(file, argFileName);				/* 获取当前文件名 */

//strcpy (fileName, "./inputFiles/OddXor.txt");

printf("%s",file);
/* 打开代码文件 输出文件 中间代码文件 符号表文件 和输入文件*/
if ((fin = fopen (file, "r")) == NULL)  /* 文件无法打开 */
{
    QMessageBox::warning(this, tr("Run"),
        tr("Cannot open input file\n"));
    return ;
}
if ((fout = fopen("./fout.txt", "w")) == NULL)
{
    QMessageBox::warning(this, tr("Run"),
        tr("Cannot open output file\n"));
    return;
}
if ((fcode = fopen("./fcode.txt", "w")) == NULL)
{
    QMessageBox::warning(this, tr("Run"),
        tr("Cannot open intermediate code file\n"));
    return;
}
if ((ftable = fopen("./ftable.txt", "w")) == NULL)
{
    QMessageBox::warning(this, tr("Run"),
        tr("Cannot open table file\n"));
    return;
}
if ((finput = fopen("./finput.txt", "r")) == NULL)
{
    QMessageBox::warning(this, tr("Run"),
        tr("Cannot open finput file\n"));
    return;
}
/*if ((fstack = fopen("./fstack.txt", "w")) == NULL)
{
    QMessageBox::warning(this, tr("Run"),
        tr("Cannot open stack file\n"));
    return;
}
*/


/* 重置指针至文件开始 */
char temp;
temp = fgetc (finput);
rewind (finput);
temp  = fgetc(fin);
rewind(fin);

init();					/* 初始化 */
if (compile())			/* 编译，成功则运行解释程序 */
{
    Interpret();
}


//fclose(fstack);
fclose(finput);
fclose(ftable);
fclose(fcode);
fclose(fout);
fclose(fin);

/* 显示运行结果到界面 */
QString path = "./fout.txt";
if (!path.isEmpty()) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("output File"),
            tr("Cannot open file:\n%1").arg(path));
        return;
    }
    QTextStream in(&file);
    ui->textBrowser->setText(in.readAll());
    file.close();
}
path = "./fcode.txt";
if (!path.isEmpty()) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("code File"),
            tr("Cannot open file:\n%1").arg(path));
        return;
    }
    QTextStream in(&file);
    ui->textBrowser_2->setText(in.readAll());
    file.close();
}
path = "./ftable.txt";
if (!path.isEmpty()) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("table File"),
            tr("Cannot open file:\n%1").arg(path));
        return;
    }
    QTextStream in(&file);
    ui->textBrowser_3->setText(in.readAll());
    file.close();
}
//ui->textBrowser->setText("");
//ui->textBrowser_4->setText("");
}



