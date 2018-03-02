#ifndef ECHOPLUGIN_H
#define ECHOPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include "CustomInterface.h"

class EchoPlugin : public QObject, CustomInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.Examples.CustomInterface" FILE "echoplugin.json")
    Q_INTERFACES(CustomInterface)
    Q_CLASSINFO("PluginName", "Echo Plugin")
    Q_CLASSINFO("AddToMenu", "true")
    Q_CLASSINFO("RunOnLoading", "true")

public:
    explicit EchoPlugin(QObject *parent = 0);
    QString echo(const QString &message) override;
    void execute();

private:
    QString test;

};

#endif
