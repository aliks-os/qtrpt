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

#ifndef RPTCROSSTABOBJECT_H
#define RPTCROSSTABOBJECT_H

#include <QDebug>
#include <QMetaType>
#include <RptFieldObject.h>

#if QT_VERSION >= 0x50000
    #ifdef QXLSX_LIBRARY
        #include "xlsxdocument.h"
    #endif
#endif

using namespace QtRptName;

class RptFieldObject;

struct RptTabElement
{
    RptFieldObject *fieldObject;
    QVariant value;
    quint32 left;
    quint32 top;
    quint32 height;
    quint32 width;
    quint32 col;
    quint32 row;
};

class RptCrossTabObject
{
    friend class QtRPT;
    friend class RptFieldObject;

public:
    RptCrossTabObject();
    ~RptCrossTabObject();
    QString name;
    QRect rect;
    int colCount() const;
    void setColCount(int value);
    int rowCount() const;
    void setRowCount(int value);
    int rowHeight();
    void setRowHeight(int height);
    int processedCount();
    void setProcessedCount(int value);
    int fieldRow(RptFieldObject *field, bool realNr = false);
    int fieldCol(RptFieldObject *field);
    int visibleRowCount();
    bool isTotalByRowVisible();
    void setTotalByRowVisible(bool value);
    bool isTotalByColumnVisible();
    void setTotalByColumnVisible(bool value);
    bool isSubTotalVisible();
    void setSubTotalVisible(bool value);
    bool isHeaderVisible();
    void setHeaderVisible(bool value);
    void loadParamFromXML(QDomElement e);
    void saveParamToXML(QDomElement &e);

    void buildMatrix();
    QList<RptFieldObject*> fieldList;
    RptFieldObject *parentField;
    QList<QString> headers;

    QColor totalBackgroundColor;
    QColor headerBackgroundColor;

    void addElement(RptTabElement element);
    #ifdef QXLSX_LIBRARY
        void buildXlsx(QXlsx::Document *xlsx);
    #endif

private:
    quint32 m_colCount;
    quint32 m_rowCount;
    quint32 m_rowHeight;
    quint32 m_processedCount;
    bool m_totalByRowVisible;
    bool m_totalByColumnVisible;
    bool m_subTotalVisible;
    bool m_headerVisible;
    bool isTotalField(RptFieldObject *field);
    void total(RptFieldObject *field);
    bool isHeaderField(RptFieldObject *field);
    void header(RptFieldObject *field);

    void addField(RptFieldObject *field);

    QVector<RptTabElement> m_elements;

};

using SPtrCrossTab = QSharedPointer<RptCrossTabObject>;

Q_DECLARE_METATYPE(RptCrossTabObject)

QDebug operator<<(QDebug dbg, const RptCrossTabObject &obj);
QDebug operator<<(QDebug dbg, const RptCrossTabObject *obj);

#endif // RPTCROSSTABOBJECT_H
