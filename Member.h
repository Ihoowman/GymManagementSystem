#ifndef MEMBER_H
#define MEMBER_H

#include "person.h"
#include <QVariant>

enum MemberStatus
{
    Active,
    Suspended,
    Expired,
    Pending,
    VIP
};

class Member : public Person
{
private:
    int id;
    QString email;
    QString memberId;
    QString address;
    QString memberSince;
//    MemberStatus status;

public:

    Member(
            int idValue,
            QString memberName,
            QString memberPhone,
            QString emailValue = "",
            QString memberIdValue = "",
            QString address= "",
            QString memberSince = ""/*,
            MemberStatus memberStatus = Active*/)
        : Person(memberName, memberPhone),
          id(idValue),
          email(emailValue),
          memberId(memberIdValue),
          address(address),
          memberSince(memberSince)/*,
          status(memberStatus)*/
    {
    }

    int getId() const
    {
        return id;
    }

//    MemberStatus getStatus() const
//    {
//        return status;
//    }
    QString getEmail() const
    {
        return email;
    }

    QString getMemberId() const
    {
        return memberId;
    }
    QString getAddress() const
    {
        return address;
    }
    QString getMemberSince() const
    {
        return memberSince;
    }
    void setEmail(const QString& value)
    {
        email = value;
    }

    void setAddress(const QString& value)
    {
        address = value;
    }

    void setMemberId(const QString& value)
    {
        memberId = value;
    }

    void setMemberSince(const QString& value)
    {
        memberSince = value;
    }
};
Q_DECLARE_METATYPE(Member*);

#endif
