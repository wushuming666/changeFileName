#include "mainwindow.h"
#include <QApplication>

#include <QFileDialog>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

/*
    qDebug() << "start";
    QString mFolderPath = QFileDialog::getExistingDirectory(NULL, "Open Folder", "D:\\C++\\极客");
    QStringList mImgNames;
    // 获取所有文件夹名
    QDir dir(mFolderPath);
    mFolderPath = dir.fromNativeSeparators(mFolderPath);//  "\\"转为"/"
    if (!dir.exists()) mImgNames = QStringList("");
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Name);
    mImgNames = dir.entryList();
    for (int i = 0; i < mImgNames.size(); ++i)
    {
        qDebug() << "entryList: " << i << "-" << mFolderPath + "/" +mImgNames[i];
        // 打开二级文件夹
        QString dirname = mFolderPath + "\\" + mImgNames[i];
        QStringList  filelists;
        QDir filedir(dirname);
        dirname = filedir.fromNativeSeparators(dirname);
        if (!filedir.exists())
        {
            qDebug() << dirname + "为空!";
            filelists = QStringList("");
        }
        filedir.setFilter(QDir::Files);
        filedir.setSorting(QDir::Name);
//        filedir.setNameFilters(QString("*.jpg"));
        filelists = filedir.entryList();
        qDebug() << filelists.size();

        // "D:/C++/极客/042-趣谈Linux操作系统/images/99553/1ef05750bc9ff87a3330104802965335【海量资源：666java.com】.jpeg"
        for (int j = 0; j < filelists.size(); j ++)
        {
            qDebug() << dirname + "/" + filelists[j];
            QString oldname = dirname + "/" + filelists[j];
            QString newname = oldname;
            newname.replace("【海量资源：666java.com】", "");

            QFile file(oldname);
            file.rename(newname);
            qDebug() << newname << " ok!";
        }
    }

*/
    return a.exec();
}
