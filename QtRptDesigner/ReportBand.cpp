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

#include "ReportBand.h"
#include "ui_ReportBand.h"
#include <QObject>
#include "mainwindow.h"

ReportBand::ReportBand(BandType type, int num)
{
    setFlag(QGraphicsItem::ItemIsMovable,false);
    m_menu = new QMenu;
    bandType = type;
    m_infocus = false;
    itemInTree = nullptr;
    titleHeight = 20;
    bandNo = num;

    m_groupingField = "";
    m_startNewNumeration = false;
    m_showInGroup = false;
    m_startNewPage = false;

    if (type == ReportTitle) {
        this->setObjectName(QString("RepTitleBand%1").arg(num));
        setText(QString("Report title %1").arg(num));
        setBandPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/reportTitle.png")));
    }
    if (type == ReportSummary) {
        this->setObjectName(QString("ReportSummaryBand%1").arg(num));
        setText(QString("Report summary %1").arg(num));
        setBandPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/reportFooter.png")));
    }
    if (type == PageHeader) {
        this->setObjectName(QString("PageHeaderBand%1").arg(num));
        setText(QString("Page header %1").arg(num));
        setBandPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/pageTitle.png")));
    }
    if (type == PageFooter) {
        this->setObjectName(QString("PageFooterBand%1").arg(num));
        setText(QString("Page footer %1").arg(num));
        setBandPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/pageFooter.png")));
    }
    if (type == MasterData) {
        this->setObjectName(QString("MasterDataBand%1").arg(num));
        setText(QString("Master band %1").arg(num));
        setBandPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/data.png")));
    }
    if (type == MasterFooter) {
        this->setObjectName(QString("MasterFooterBand%1").arg(num));
        setText(QString("Master footer %1").arg(num));
        setBandPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/dataFooter.png")));
    }
    if (type == MasterHeader) {
        this->setObjectName(QString("MasterHeaderBand%1").arg(num));
        setText(QString("Master header %1").arg(num));
        setBandPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/dataFooter.png")));
    }
    if (type == DataGroupHeader) {
        this->setObjectName(QString("DataGroupHeaderBand%1").arg(num));
        setText(QString("Data Group Header %1").arg(num));
        setBandPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/dataGroupingHeader.png")));
    }
    if (type == DataGroupFooter) {
        this->setObjectName(QString("DataGroupFooterBand%1").arg(num));
        setText(QString("Data Group Footer %1").arg(num));
        setBandPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/dataGroupingFooter.png")));
    }   
}

void ReportBand::setMenu(QMenu* menu)
{
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/delete.png")), QIcon::Normal, QIcon::On);

    auto actBandDel = new QAction(tr("Delete"),this);
    actBandDel->setObjectName("actBandDel");
    actBandDel->setIcon(icon);
    QObject::connect(actBandDel, SIGNAL(triggered()), this, SIGNAL(itemRemoving()));

    m_menu->actions().clear();
    m_menu->addActions(menu->actions());
    m_menu->addAction(actBandDel);
}

void ReportBand::setHeight(qreal value)
{
    GraphicsBox::setHeight(titleHeight + value);
}

QString ReportBand::getGroupingField()
{
    return m_groupingField;
}

void ReportBand::setGroupingField(QString value)
{
    m_groupingField = value;
}

int ReportBand::getStartNewNumertaion()
{
    return m_startNewNumeration;
}

void ReportBand::setStartNewNumeration(bool value)
{
    m_startNewNumeration = value;
}

bool ReportBand::getShowInGroup()
{
    return m_showInGroup;
}

void ReportBand::setShowInGroup(bool value)
{
    m_showInGroup = value;
}

bool ReportBand::getStartNewPage()
{
    return m_startNewPage;
}

void ReportBand::setStartNewPage(bool value)
{
    m_startNewPage = value;
}
