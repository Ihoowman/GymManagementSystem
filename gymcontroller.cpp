#include "gymcontroller.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>

GymController::GymController(QObject *parent)
    : QObject(parent)
{
}

// ================= LOAD / SAVE =================

QJsonArray GymController::loadUsers()
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return QJsonArray();

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    return doc.array();
}

bool GymController::saveUsers(const QJsonArray &users)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    file.write(QJsonDocument(users).toJson());
    file.close();
    return true;
}

// ================= GET MEMBER =================

Member GymController::getMember(const QString &email)
{
    QJsonArray users = loadUsers();

    for (const QJsonValue &v : users)
    {
        QJsonObject o = v.toObject();

        if (o["EMAIL"].toString() == email)
        {
            Member m;
            m.email = email;
            m.fullName = o["FULL NAME"].toString();

            m.hasMembership = o["HAS_MEMBERSHIP"].toBool();
            m.membershipType = o["MEMBERSHIP_TYPE"].toString();

            m.totalSessions = o["TOTAL_SESSIONS"].toInt();
            m.usedSessions = o["SESSIONS_USED"].toInt();
            m.leftSessions = o["SESSIONS_LEFT"].toInt();

            m.trainer = o["TRAINER_NAME"].toString();
            m.memberSince = o["MEMBER_SINCE"].toString();

            return m;
        }
    }

    return Member();
}

// ================= APPLY MEMBERSHIP =================

void GymController::applyMembership(const QString &email, const QString &plan)
{
    QJsonArray users = loadUsers();

    int sessions = 0;

    if (plan.contains("Gold")) sessions = 30;
    else if (plan.contains("Silver")) sessions = 20;
    else if (plan.contains("Basic")) sessions = 10;

    for (int i = 0; i < users.size(); i++)
    {
        QJsonObject u = users[i].toObject();

        if (u["EMAIL"].toString() == email)
        {
            u["HAS_MEMBERSHIP"] = true;
            u["MEMBERSHIP_TYPE"] = plan;

            u["TOTAL_SESSIONS"] = sessions;
            u["SESSIONS_USED"] = 0;
            u["SESSIONS_LEFT"] = sessions;

            users[i] = u;
            break;
        }
    }

    saveUsers(users);
}

// ================= USE SESSION =================

void GymController::useSession(const QString &email)
{
    QJsonArray users = loadUsers();

    for (int i = 0; i < users.size(); i++)
    {
        QJsonObject u = users[i].toObject();

        if (u["EMAIL"].toString() == email)
        {
            int used = u["SESSIONS_USED"].toInt();
            int left = u["SESSIONS_LEFT"].toInt();

            if (left > 0)
            {
                used++;
                left--;
            }

            u["SESSIONS_USED"] = used;
            u["SESSIONS_LEFT"] = left;

            users[i] = u;
            break;
        }
    }

    saveUsers(users);
}

// ================= ACTIVITY LOG =================

void GymController::addLog(const QString &email, const QString &text)
{
    QJsonArray users = loadUsers();

    for (int i = 0; i < users.size(); i++)
    {
        QJsonObject u = users[i].toObject();

        if (u["EMAIL"].toString() == email)
        {
            QJsonArray log = u["ACTIVITY_LOG"].toArray();

            log.append(
                QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
                + " - " + text
            );

            u["ACTIVITY_LOG"] = log;
            users[i] = u;
            break;
        }
    }

    saveUsers(users);
}
