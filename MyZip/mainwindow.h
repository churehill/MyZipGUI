#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "quazip/JlCompress.h"
#include "rendialog.h"
#include <QString>
#include <QStringList>
#include <QDir>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
    
private slots:
    void on_pushButton_find_clicked();

    void on_action_E_triggered();

    void on_action_U_triggered();

    void on_action_UT_triggered();

    void on_pushButton_rectrl_clicked();

    void on_action_V_triggered();

    void on_action_B_triggered();


    void on_action_D_triggered();

    void on_action_Q_triggered();


private:
    Ui::MainWindow *ui;
    //QFileDialog fileDialog;
    QStringList filesToCtrl;
    QString firstFile;
    QString dirToCtrl;
    QString targetDir;
    bool isFiles;
    //bool isComp;

    bool checkString();
    void exCompress(bool isNative);
    void showFileInfo();
};

#endif // MAINWINDOW_H
