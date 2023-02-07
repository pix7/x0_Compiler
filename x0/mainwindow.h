#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QAction* newAction;
    QAction* openAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* runAction;
    QString currentPath;
private:
    Ui::MainWindow *ui;

public slots:
    //void on_pushButton_clicked();
    void open();
    void save();
    void saveInputFile();
    //void comp();
    void run();
};
#endif // MAINWINDOW_H
