#ifndef PERSON_H
#define PERSON_H

#include <QString>

class Person
{
protected:
    QString name;
    QString phone;

public:
    Person(QString n = "", QString p = "")
        : name(n), phone(p)
    {
    }

    virtual ~Person()
    {
    }

    QString getName() const
    {
        return name;
    }

    QString getPhone() const
    {
        return phone;
    }
    void setName(const QString& value)
    {
        name = value;
    }

    void setPhone(const QString& value)
    {
        phone = value;
    }
};

#endif
