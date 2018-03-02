#pragma once

#include <QString>


class CustomInterface
{
public:
    virtual ~CustomInterface() {}
    virtual void execute() = 0;
    virtual QString echo(const QString &message) = 0;
};


Q_DECLARE_INTERFACE(CustomInterface,
                    "org.qt-project.Qt.Examples.CustomInterface")

