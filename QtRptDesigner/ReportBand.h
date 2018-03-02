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

#ifndef REPORTBAND_H
#define REPORTBAND_H

#include <QTreeWidgetItem>
#include "GraphicsLine.h"
#include "GraphicsBox.h"

class ReportBand : public GraphicsBox
{
    
public:
    explicit ReportBand(BandType type, int num);
    int type() const Q_DECL_OVERRIDE { return ItemType::GBand; }
    void setMenu(QMenu *menu);
    qreal scale;
    void setHeight(qreal value);
    QString getGroupingField();
    void setGroupingField(QString value);
    int getStartNewNumertaion();
    void setStartNewNumeration(bool value);
    bool getShowInGroup();
    void setShowInGroup(bool value);
    bool getStartNewPage();
    void setStartNewPage(bool value);
    BandType bandType;
    int titleHeight;
    int bandNo;

private:
    bool m_infocus;
    QString m_groupingField;
    bool m_startNewNumeration;
    bool m_showInGroup;
    bool m_startNewPage;


protected:
    QPoint position;
    QPointF mousePos;

};

#endif // REPORTBAND_H
