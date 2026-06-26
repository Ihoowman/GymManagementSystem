#include "membership.h"

Membership::Membership()
{
    planName = "";
    totalSessions = 0;
    price = 0;
}

QString Membership::getPlanName() const
{
    return planName;
}

int Membership::getTotalSessions() const
{
    return totalSessions;
}

int Membership::getPrice() const
{
    return price;
}

void Membership::setPlanName(const QString &plan)
{
    planName = plan;
}

void Membership::setTotalSessions(int sessions)
{
    totalSessions = sessions;
}

void Membership::setPrice(int p)
{
    price = p;
}
