#pragma once

#include <utility>
#include <QString>

class Person
{
public:
    Person(QString firstName, int age)
        : m_firstName(std::move(firstName))
        , m_age(age)
    {}
    QString firstName() const {
        return m_firstName;
    }
    int age() const {
        return m_age;
    }
private:
    QString m_firstName;
    int m_age;
};

bool operator==(const Person &p1, const Person &p2)
{
    return p1.firstName() == p2.firstName() && p1.age() == p2.age();
}
