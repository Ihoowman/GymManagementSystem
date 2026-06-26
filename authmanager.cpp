#include "authmanager.h"
#include <QDebug>

AuthManager::AuthManager(QObject *parent)
    : QObject(parent) {}

bool AuthManager::login(QString email, QString password) {
    qDebug() << "Login attempt:" << email;
    return true;
}

bool AuthManager::signup(Member m) {
    qDebug() << "Signup:" << m.fullName;
    return true;
}

void AuthManager::sendOTP(QString email) {
    qDebug() << "OTP sent to:" << email;
}

bool AuthManager::verifyOTP(QString code) {
    return code == "1234";
}
