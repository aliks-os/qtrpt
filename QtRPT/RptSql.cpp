/*
Name: QtRpt
Version: 2.0.1
Web-site: http://www.qtrpt.tk
Programmer: Aleksey Osipov
E-mail: aliks-os@ukr.net
Web-site: http://www.aliks-os.tk

Copyright 2012-2017 Aleksey Osipov

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "RptSql.h"
#include <QTextCodec>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QImage>

RptSql::RptSql(RptSqlConnection connection, QObject *parent)
: QObject(parent)
{
    /*#ifdef QT_DEBUG
      qDebug() << "Running a debug build";
    #else
      qDebug() << "Running a release build";
    #endif*/

    db = QSqlDatabase::addDatabase(connection.dbType, connection.dbConnectionName.isEmpty() ? QLatin1String(QSqlDatabase::defaultConnection) : connection.dbConnectionName);
    db.setDatabaseName(connection.dbName);
    db.setHostName(connection.dbHost);
    db.setUserName(connection.dbUser);
    db.setPassword(connection.dbPassword);
    if (connection.dbPort)
        db.setPort(connection.dbPort);

    this->setObjectName(connection.dsName);
}

bool RptSql::openQuery(QString sql, QString dbCoding, QString charsetCoding)
{
    db.open();
    if (!db.isOpen())
        qDebug() << "Failed open DB" << db.lastError().text();
    else
        qDebug() << "open DB";

    query = new QSqlQuery(db);
    if (!dbCoding.isEmpty())
        if (db.driverName().contains("MYSQL"))
            query->exec("set names '"+dbCoding+"'");

    if (!charsetCoding.isEmpty()) {
        auto codec = QTextCodec::codecForName( QString(charsetCoding).toLocal8Bit().constData() );
        QTextCodec::setCodecForLocale(codec);
    }

    if (!query->exec(sql)) {
        qDebug() << query->lastError().text();
        return false;
    }

    return true;
}

QString RptSql::getFieldValue(QString fieldName, int recNo)
{
    if (query->isActive()) {
        if (recNo >= getRecordCount()) {
            qDebug() << "recNo more than recordCount";
            return "";
        } else {
            query->seek(recNo);
            int fieldNo = query->record().indexOf(fieldName);
            return query->value(fieldNo).toString();
        }
    } else {
        qDebug() << "Query is not active";
        return "";
    }
}

QImage RptSql::getFieldImage(QString fieldName, int recNo)
{
    if (query->isActive()) {
        if (recNo >= getRecordCount()) {
            qDebug() << "recNo more than recordCount";
            return QImage();
        } else {
            query->seek(recNo);
            int fieldNo = query->record().indexOf(fieldName);
            return QImage::fromData(query->value(fieldNo).toByteArray());
        }
    } else {
        qDebug() << "Query is not active";
        return QImage();
    }
}

int RptSql::getRecordCount()
{
    if (query->isActive()) {
        query->last();
        return query->at()+1;
    }

    return 0;
}
