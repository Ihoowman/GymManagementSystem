#include "person.h"

Person::Person()
{

}

QString Person::getFullName() const
{
    return fullName;
}

QString Person::getEmail() const
{
    return email;
}

QString Person::getPhoneNumber() const
{
    return phoneNumber;
}

void Person::setFullName(const QString &name)
{
    fullName = name;
}

void Person::setEmail(const QString &mail)
{
    email = mail;
}

void Person::setPhoneNumber(const QString &phone)
{
    phoneNumber = phone;
}
