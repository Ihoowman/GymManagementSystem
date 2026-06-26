#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QString>

class AuthManager
{
public:

    bool login(QString username,
               QString password)
    {
        return !username.isEmpty()
                && !password.isEmpty();
    }
    bool isValidEmail(const QString& email)
    {
        return email.contains("@")
                && email.contains(".");
    }
};

#endif
