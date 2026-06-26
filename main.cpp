#include "mainwindow.h"
#include <QApplication>
#include "gymcontroller.h"
//#include <QSslSocket> //movaghat
//#include <QDebug> //movaghat
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GymController gymController;

    gymController.loadMembers("users.json");


//    qDebug() << "SSL Supported =" << QSslSocket::supportsSsl(); //movaghat
//    qDebug() << "Build SSL =" << QSslSocket::sslLibraryBuildVersionString();   //movaghat
//    qDebug() << "Run SSL =" << QSslSocket::sslLibraryVersionString();   //movaghat
//    qDebug() << QSslSocket::sslLibraryBuildVersionString();//movaghat
//    qDebug() << QSslSocket::sslLibraryVersionString();//movaghat
//    qDebug() << QSslSocket::supportsSsl();//movaghat

    MainWindow w;
    w.show();
    return a.exec();
}
