#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <dir.h>
#include <QQueue>
#include <string>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->startPushButton, SIGNAL(clicked()), this,
            SLOT(startClicked()));
    connect(ui->pathClickButton, SIGNAL(clicked()), this,
            SLOT(pathClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 选择父文件
void MainWindow::pathClicked()
{
    QString mFolderPath = QFileDialog::getExistingDirectory(NULL, "Open Folder", "C:\\");
    ui->pathName->setText(mFolderPath);
}

// 开始搜索替换
void MainWindow::startClicked()
{
    int sum = 0;
    qDebug() << "strarClicked";
    QString pathName = ui->pathName->text();
    int depth;
    if(ui->textDepth->text().size() > 0)
        depth = ui->textDepth->text().toInt();
    else depth = -1;

    qDebug() << pathName << " " << depth;

    // 开始bfs搜索
    QDir fatherDir(pathName);
    if (pathName.size() == 0 || !fatherDir.exists())
    {
        QMessageBox::information(NULL, "路径不合法", "请重新输入路径");
    }

    QQueue<QString> queue;
    queue.push_back(pathName);
    while (queue.size())
    {
        // 超出了最大深度 退出
        if (depth == 0)
            break;
        // 没有设置深度就 while(1)
        if (depth < 0)
            depth = -1;
        int len = queue.size();
        while (len --)
        {
            QString fileOrDirName = queue.front();
            queue.pop_front();
            // qDir是文件夹 qFile是文件
            QFileInfo fileinfo(fileOrDirName);
            // 如果路径是Dir，bfs该文件夹下的所有string，加入队列
            if(fileinfo.isDir())
            {
                QDir dir(fileOrDirName);
                QString mFolderPath = dir.fromNativeSeparators(fileOrDirName);//  "\\"转为"/"
                // 处理该文件夹下的所有文件夹
                dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
                dir.setSorting(QDir::Name);
                QStringList mImgNames = dir.entryList();
                for (int i = 0; i < mImgNames.size(); i ++)
                {
                    qDebug() << "entryList: " << i << "-" << mFolderPath + "/" +mImgNames[i];
                    QString aNewName = mFolderPath + "\\" + mImgNames[i];
                    queue.push_back(aNewName);
                }

                // 处理该文件夹下的所有文件
                dir.setFilter(QDir::Files);
                dir.setSorting(QDir::Name);
                mImgNames = dir.entryList();
                for (int i = 0; i < mImgNames.size(); i ++)
                {
                    qDebug() << "entryList: " << i << "-" << mFolderPath + "/" +mImgNames[i];
                    QString aNewName = mFolderPath + "\\" + mImgNames[i];
                    queue.push_back(aNewName);
                }

            }
            // 如果路径是普通文件，替换
            else
            {
                QFile file(fileOrDirName);
                QString oldName = fileOrDirName;
                QString A(ui->textA->text());
                QString B(ui->textB->text());
                oldName.replace(A, B);
                file.rename(oldName);
                qDebug() << oldName << " ok!";
                sum ++;
            }
        }
        depth --;
    }

    QString Ssum = QString::number(sum);
    QMessageBox::information(NULL, "成功！", "一共为您替换 " + Ssum + " 个文件！");
}
