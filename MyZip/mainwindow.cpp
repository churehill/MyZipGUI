#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMaximumSize(this->width(),this->height());
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    //ui->comboBox_dir->setVisible(false);
    //ui->pushButton_rectrl->setVisible(false);
            //filesToCtrl = QFileDialog::getOpenFileNames(this,tr("选择一个或多个文件"),
            //                                          QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation),
            //                                            tr("所有文件 (*.*)"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_find_clicked()
{
    //fileDialog(this);
    if(ui->radioButton_file->isChecked())
    {
//        QFileDialog fileDialog(this,tr("选择一个或多个文件"),QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation),
//                               tr("所有文件 (*.*)"));
//        fileDialog.setFileMode(QFileDialog::ExistingFiles);
//        fileDialog.setViewMode(QFileDialog::Detail);
//        if(fileDialog.exec())
//        {
//            filesToCtrl = fileDialog.selectedFiles();
//            QString files = filesToCtrl.join(";");
//            ui->comboBox_fileToCtrl->setEditText(files);
//            ui->comboBox_fileToCtrl->addItem(files);
//            isFiles = true;
//        }
        filesToCtrl = QFileDialog::getOpenFileNames(this,tr("选择一个或多个文件"),
                                                    QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation),
                                                    tr("所有文件 (*.*)"));
        if(filesToCtrl.count())
        {
            QString files = filesToCtrl.join(";");
            ui->comboBox_fileToCtrl->setEditText(files);
            ui->comboBox_fileToCtrl->addItem(files);
            isFiles = true;
            showFileInfo();
        }
    }
    else
    {
        dirToCtrl = QFileDialog::getExistingDirectory(this,tr("选择文件夹"),
                                                      QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation),
                                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if(dirToCtrl!=NULL)
        {
            ui->comboBox_fileToCtrl->setEditText(dirToCtrl);
            ui->comboBox_fileToCtrl->addItem(dirToCtrl);
            isFiles=false;
            showFileInfo();
        }

    }    

}



void MainWindow::on_action_E_triggered()
{
    if(!checkString())
        return;
    targetDir = QFileDialog::getSaveFileName(this,tr("保存为zip文件"),
                                               QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation),
                                               tr("压缩文件 (*.zip)"));
    if(targetDir!=NULL)
     {
        bool isSuccess;
        if(isFiles)
            isSuccess = JlCompress::compressFiles(targetDir,filesToCtrl);
        else
            isSuccess = JlCompress::compressDir(targetDir,dirToCtrl,true);
        if(isSuccess)
        {
            ui->comboBox_dir->addItem(targetDir);
            ui->comboBox_dir->setEditText(targetDir);
            ui->textBrowser_compInfo->clear();
            ui->textBrowser_compInfo->append(tr("压缩文件创建成功：")+targetDir+tr("\n"));
            QFileInfo tempfileinfo2(targetDir);
            ui->textBrowser_compInfo->append(tr("压缩后文件大小: %1KB\n").arg(tempfileinfo2.size()/1024));
            showFileInfo();
        }
        else
        {
            QMessageBox::warning(this,tr("MyZip"),
                                 tr("压缩文件创建失败，请重试"),
                                     QMessageBox::Ok);
        }
     }

}

bool MainWindow::checkString()
{
    if(ui->comboBox_fileToCtrl->currentIndex()==-1)
    {
        QMessageBox::warning(this,tr("MyZip"),
                             tr("您还没选择或输入要操作的文件或文件夹"),
                                 QMessageBox::Ok);
        return 0;
    }
    QString tempstring = ui->comboBox_fileToCtrl->currentText();
    QStringList tempstrlist = tempstring.split(";");
    tempstring=tempstrlist.at(0);
    if(!tempstring.contains('.'))
    {
        QDir tempdir(tempstring);
        if(!tempdir.exists())
        {
            QMessageBox::warning(this,tr("MyZip"),tempstring+tr("目录不存在！"),QMessageBox::Ok);
            return 0;
        }
        else
        {
            dirToCtrl = tempstring;
            isFiles =0;
            return 1;
        }
    }
    else
    {
        for(int i=0;i<tempstrlist.size();i++)
        {
            if(!QFile::exists(tempstrlist.at(i)))
            {
                QMessageBox::warning(this,tr("MyZip"),tempstrlist.at(i)+tr("文件不存在！"),QMessageBox::Ok);
                return 0;
            }
        }
        filesToCtrl = tempstrlist;
        firstFile = tempstrlist.at(0);
        isFiles =1;
        return 1;
    }

}

void MainWindow::exCompress(bool isNative)
{
    if(!checkString())
        return;
    if(!(isFiles&&filesToCtrl.size()==1&&firstFile.endsWith(".zip")))
    {
        QMessageBox::warning(this,tr("MyZip"),tr("请选择或输入一个zip文件名"),QMessageBox::Ok);
        return;
    }
    if(isNative)
    {
        QFileInfo zipinfo(firstFile);
        targetDir = zipinfo.absolutePath();
    }
    else
    {
        targetDir = QFileDialog::getExistingDirectory(this,tr("选择解压的路径"),
                                                      QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation),
                                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if(targetDir==NULL)
            return ;
    }
    if(JlCompress::extractDir(firstFile,targetDir)==QStringList())
    {
        QMessageBox::warning(this,tr("MyZip"),
                             tr("解压文件失败，请重试"),
                                 QMessageBox::Ok);
    }
    else
    {
        ui->comboBox_dir->addItem(targetDir);
        ui->comboBox_dir->setEditText(targetDir);
        ui->textBrowser_compInfo->clear();
        ui->textBrowser_compInfo->append(tr("解压文件成功：")+firstFile+tr("\n"));
        showFileInfo();
    }
}

void MainWindow::on_action_U_triggered()
{
    exCompress(true);
//    if(!checkString())
//        return;
//    if(!(isFiles&&filesToCtrl.size()==1&&firstFile.endsWith(".zip")))
//    {
//        QMessageBox::warning(this,tr("MyZip"),tr("请选择或输入一个zip文件名"),QMessageBox::Ok);
//        return;
//    }
//    QFileInfo zipinfo(firstFile);
//    targetDir = zipinfo.absolutePath();
//    if(JlCompress::extractDir(firstFile,targetDir)==QStringList())
//    {
//        QMessageBox::warning(this,tr("MyZip"),
//                             tr("解压文件失败，请重试"),
//                                 QMessageBox::Ok);
//    }
//    else
//    {
//        ui->comboBox_dir->addItem(targetDir);
//        ui->comboBox_dir->setEditText(targetDir);
//        ui->textBrowser_compInfo->clear();
//        ui->textBrowser_compInfo->append(tr("解压文件成功：")+firstFile+tr("\n"));
//    }
}

void MainWindow::on_action_UT_triggered()
{
    exCompress(false);
//    if(!checkString())
//        return;
//    if(!(isFiles&&filesToCtrl.size()==1&&firstFile.endsWith(".zip")))
//    {
//        QMessageBox::warning(this,tr("MyZip"),tr("请选择或输入一个zip文件名"),QMessageBox::Ok);
//        return;
//    }
//    targetDir = QFileDialog::getExistingDirectory(this,tr("选择解压的路径"),
//                                                  QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation),
//                                                  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
//    if(targetDir !=NULL)
//    {
//        if(JlCompress::extractDir(firstFile,targetDir)==QStringList())
//        {
//            QMessageBox::warning(this,tr("MyZip"),
//                                 tr("解压文件失败，请重试"),
//                                     QMessageBox::Ok);
//        }
//        else
//        {
//            ui->comboBox_dir->addItem(targetDir);
//            ui->comboBox_dir->setEditText(targetDir);
//            ui->textBrowser_compInfo->clear();
//            ui->textBrowser_compInfo->append(tr("解压文件成功：")+firstFile+tr("\n"));
//        }
//    }
}

void MainWindow::on_pushButton_rectrl_clicked()
{
    if(ui->comboBox_dir->currentIndex()==-1)
    {
        QMessageBox::warning(this,tr("MyZip"),
                             tr("您还没选择或输入要操作的文件或文件夹"),
                                 QMessageBox::Ok);
        return ;
    }
    QString tempstr3 = ui->comboBox_dir->currentText();
    ui->comboBox_fileToCtrl->addItem(tempstr3);
    ui->comboBox_fileToCtrl->setEditText(tempstr3);
    showFileInfo();
}

void MainWindow::showFileInfo()
{
    if(!checkString())
        return;
    ui->textBrowser_fileInfo->clear();
    if(isFiles)
    {
        ui->textBrowser_fileInfo->append(tr("已选择%1个文件:\n").arg(filesToCtrl.size()));
        for(int i=0;i<filesToCtrl.size();i++)
        {
            QFileInfo tempinfo(filesToCtrl.at(i));
            ui->textBrowser_fileInfo->append(tempinfo.fileName()+tr("   大小: %1KB\n").arg(tempinfo.size()/1024));
        }
    }
    else
    {
        QDir tempDir(dirToCtrl);
        QFileInfoList tempinfolist = tempDir.entryInfoList();
        ui->textBrowser_fileInfo->append(tr("已选择1个目录:%1\n目录包含以下文件:\n").arg(tempDir.dirName()));
        for(int i=0;i<tempinfolist.size();i++)
        {
            ui->textBrowser_fileInfo->append(tempinfolist.at(i).fileName()+tr("   大小: %1KB\n").arg(tempinfolist.at(i).size()/1024));
        }
    }
}

void MainWindow::on_action_V_triggered()
{
    showFileInfo();
}

void MainWindow::on_action_B_triggered()
{
    QMessageBox::about(this,tr("关于MyZip"),tr("MyZip\n          卢鑫畅制作 for C语言大作业\n   一款简易但实用的zip压缩小程序，利用Qt与开源库kuazip制作\n              邮箱:churehill@163.com"));

}

//void MainWindow::on_action_R_triggered()
//{
//    if(!checkString())
//        return;
//    if(isFiles)
//    {
//        for(int i=0;i<filesToCtrl.size();i++)
//        {
//            QFileInfo tempinfo(filesToCtrl.at(i));
//        }
//    }

//}

void MainWindow::on_action_D_triggered()
{
    if(!checkString())
        return;
    if(isFiles)
    {
        QString tempstr4 = filesToCtrl.join("\n");
        if(QMessageBox::question(this,tr("确认"),tr("是否确认删除以下文件:\n")+tempstr4,QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
        {
            QDir tempdir3;
            for(int i=0;i<filesToCtrl.size();i++)
            {
                tempdir3.remove(filesToCtrl.at(i));
            }
            ui->textBrowser_compInfo->clear();
            ui->textBrowser_compInfo->append(tr("以下文件已删除成功：\n")+tempstr4);
            //ui->comboBox_fileToCtrl->clearEditText();
            ui->textBrowser_fileInfo->clear();
            ui->textBrowser_fileInfo->append(tr("文件已删除：\n")+tempstr4);
        }

    }
}

void MainWindow::on_action_Q_triggered()
{
    qApp->quit();
}
