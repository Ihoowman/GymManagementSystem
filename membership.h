#ifndef MEMBERSHIP_H
#define MEMBERSHIP_H

#include <QString>

class Membership
{
private:
    QString planName;
    int totalSessions;
    int price;

public:
    Membership();

    QString getPlanName() const;
    int getTotalSessions() const;
    int getPrice() const;

    void setPlanName(const QString &plan);
    void setTotalSessions(int sessions);
    void setPrice(int p);
};

#endif // MEMBERSHIP_H
