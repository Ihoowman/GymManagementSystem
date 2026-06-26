#ifndef GYMCONTROLLER_H
#define GYMCONTROLLER_H

#include <QVector>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "member.h"
#include "authmanager.h"

class GymController
{
private:

    QVector<Member*> members;

    AuthManager authManager;

public:

    GymController()
    {

    }

    ~GymController()
    {
        qDeleteAll(members);
    }

    int memberCount() const
    {
        return members.size();
    }

    AuthManager& getAuthManager()
    {
        return authManager;
    }
    void loadMembers(const QString& filePath)
    {
        QFile file(filePath);

        if(!file.open(QIODevice::ReadOnly))
            return;

        QByteArray data = file.readAll();

        file.close();

        QJsonDocument doc =
                QJsonDocument::fromJson(data);

        QJsonArray users =
                doc.array();

        qDeleteAll(members);
        members.clear();

        int counter = 1;

        for(const QJsonValue &value : users)
        {
            QJsonObject obj = value.toObject();

            members.append(
                new Member(
                    counter++,
                    obj["FULL NAME"].toString(),
                    obj["NUMBER"].toString(),
                    obj["EMAIL"].toString(),
                    obj["MEMBER_ID"].toString()
                )
            );
        }
    }
    Member* findMemberByEmail(
            const QString& email)
    {
        for(Member* member : members)
        {
            if(member->getEmail() == email)
                return member;
        }

        return nullptr;
    }
};

#endif
