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

#ifndef RPTBANDOBJECT_H
#define RPTBANDOBJECT_H

#include <RptFieldObject.h>

using namespace QtRptName;

class QtRPT;
class RptPageObject;
class RptFieldObject;

class RptBandObject
{
    friend class QtRPT;
    friend class RptPageObject;

public:
    RptBandObject() {}
    ~RptBandObject();
    QString name;
    QString groupingField;
    bool showInGroup;
    bool startNewPage;
    bool startNewNumeration;
    int realHeight;
    int height;
    int width;
    int left;
    int right;
    BandType type;
    int bandNo;
    void addField(RptFieldObject *field);
    QList<RptFieldObject*> fieldList;
    RptPageObject *parentReportPage;
    RptBandObject *clone();

private:
	QtRPT *m_qtrpt;
    void setProperty(QtRPT *qtrpt, QDomElement docElem);

};

Q_DECLARE_METATYPE(RptBandObject)
QDebug operator<<(QDebug dbg, const RptBandObject &obj);


#endif // RPTBANDOBJECT_H
