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

#include "RptPageObject.h"

/*!
 \class RptPageObject
 \inmodule RptPageObject.cpp
 \brief The RptPageObject class allow to construct the QtRPT report from scrutch.
 RptPageObject represent report's page. On RptPageObject the RptBandObjects are placed

  The inner structure of report is following:
  \code
  QtRPT
    RptPageObject
      RptBandObject
        RptFieldObject
  \endcode
  There are possible to have some RptPageObject in the report.
  It allows combining several reports in one Report.
*/

/*!
 \variable RptPageObject::pageNo
 \brief The number of report's page.
*/

/*!
 \variable RptPageObject::orientation
 \brief The orientation of report's page.
*/

/*!
 \variable RptPageObject::ph
 \brief The height of report's page.
*/

/*!
 \variable RptPageObject::pw
 \brief The width of report's page.
*/

/*!
 \variable RptPageObject::ml
 \brief The left's margin of report's page.
*/

/*!
 \variable RptPageObject::mr
 \brief The girht's margin of report's page.
*/

/*!
 \variable RptPageObject::mt
 \brief The top's margin of report's page.
*/

/*!
 \variable RptPageObject::mb
 \brief The buttom's margin of report's page.
*/

/*!
 \variable RptPageObject::border
 \brief Sets draw or not border arround the page. Defualt is false.
*/

/*!
 \variable RptPageObject::borderWidth
 \brief The border's width of report's page. Default value is 1px.
*/

/*!
 \variable RptPageObject::borderColor
 \brief The border's color of report's page. Default is Qt::black
*/

/*!
 \variable RptPageObject::borderStyle
 \brief The border's style of report's page. Default value is "solid"
*/

/*!
 \fn RptPageObject::RptPageObject()
    Constructs a RptPageObject object.
*/
RptPageObject::RptPageObject(QtRPT *qtrpt)
{
	this->m_qtrpt = qtrpt;
    this->orientation = 0;
    this->ph = 1188;
    this->pw = 840;
    this->ml = 40;
    this->mr = 40;
    this->mt = 40;
    this->mb = 40;
    this->border = false;
    this->borderWidth = 1;
    this->borderColor = Qt::black;
    this->borderStyle = "solid";
    this->rtpSql = nullptr;
    this->sqlConnection.active = false;
}

void RptPageObject::setProperty(QtRPT *qtrpt, QDomElement docElem)
{
    ph = docElem.attribute("pageHeight").toInt();
    pw = docElem.attribute("pageWidth").toInt();
    ml = docElem.attribute("marginsLeft").toInt();
    mr = docElem.attribute("marginsRight").toInt();
    mt = docElem.attribute("marginsTop").toInt();
    mb = docElem.attribute("marginsBottom").toInt();
    orientation = docElem.attribute("orientation").toInt();
    pageNo = docElem.attribute("pageNo").toInt();
    border = docElem.attribute("border").toInt();
    borderWidth = docElem.attribute("borderWidth").toInt();
    borderColor = colorFromString(docElem.attribute("borderColor"));
    borderStyle = docElem.attribute("borderStyle");

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement();
        if (!e.isNull() && e.tagName() == "ReportBand") {
            auto bandObject = new RptBandObject();
            bandObject->parentReportPage = this;
            bandObject->setProperty(qtrpt,e);
            bandList.append(bandObject);
        }
        n = n.nextSibling();
    }
}

/*!
 \fn void RptPageObject::addBand(RptBandObject *band)
    Add \a band to current RptBandObject object.

    \sa RptBandObject
*/
void RptPageObject::addBand(RptBandObject *band)
{
    band->parentReportPage = this;
	band->m_qtrpt = this->m_qtrpt;
    bandList.append(band);
}

/*!
 \fn RptBandObject RptPageObject::getBand(BandType type)
    Find and return \c RptBandObject on this report page the field by
    the given \a type.

    \sa RptBandObject
*/
RptBandObject *RptPageObject::getBand(BandType type, int No)
{
    for (auto &band : bandList)
        if (band->type == type && band->bandNo == No)
            return band;

    return nullptr;
}

int RptPageObject::bandsCountByType(BandType type)
{
    int count = 0;
    for (auto &band : bandList)
        if (band->type == type)
            if (band->bandNo > count)
                count = band->bandNo;

    return count;
}

/*!
 \fn RptFieldObject RptPageObject::findFieldObjectByName(QString name)
    Find and return \c RptFieldObject on this report page the field with
    the given \a name.

    \sa RptFieldObject
*/
RptFieldObject *RptPageObject::findFieldObjectByName(QString name)
{
    for (auto &band : bandList)
        for (auto &field : band->fieldList)
            if (field->name == name)
                return field;

    return nullptr;
}

/*!
 \fn RptPageObject *RptPageObject::clone()
    Clone the current page and return \c RptPageObject of the new page object
*/
RptPageObject *RptPageObject::clone()
{
    auto reportPage = new RptPageObject(m_qtrpt);
    reportPage->pageNo      = pageNo;
    reportPage->orientation = orientation;
    reportPage->ph          = ph;
    reportPage->pw          = pw;
    reportPage->ml          = ml;
    reportPage->mr          = mr;
    reportPage->mt          = mt;
    reportPage->mb          = mb;
    reportPage->border      = border;
    reportPage->borderWidth = borderWidth;
    reportPage->borderColor = borderColor;
    reportPage->borderStyle = borderStyle;
    reportPage->recordCount = recordCount;
    for (auto band : bandList) {
        auto newBand = band->clone();
        reportPage->addBand(newBand);
    }

    return reportPage;
}

/*!
  Destroys the object, deleting all its child objects.
 */
RptPageObject::~RptPageObject()
{
    qDeleteAll(bandList);
    bandList.clear();
}

QDebug operator<<(QDebug dbg, const RptPageObject &obj)
{
    dbg << "Report #" << obj.pageNo  << obj.bandList;
    return dbg;
}
