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

#include "exampledlg6.h"
#include "ui_exampledlg6.h"
#include <QDir>
#include <QDebug>

ExampleDlg6::ExampleDlg6(QWidget *parent, int mode)
: QDialog(parent),  ui(new Ui::ExampleDlg6)
{
    ui->setupUi(this);

    m_mode = mode;
    ui->tableWidget->setRowCount(27);
    QObject::connect(ui->btnPrint, SIGNAL(clicked()), this, SLOT(print()));

    QTableWidgetItem *newItem;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        switch (i){
            case 0:
            case 3:
            case 7:
            case 8:
            case 25:{
                newItem = new QTableWidgetItem("US");
                break;
            }
            case 1:
            case 9:
            case 5:
            case 14: {
                newItem = new QTableWidgetItem("Europe");
                break;
            }
            case 2:
            //case 5:
            case 10:
            case 12: {
                newItem = new QTableWidgetItem("Ukraine");
                break;
            }
            case 4:
            case 6:
            case 11:
            case 13: {
                newItem = new QTableWidgetItem("Georgia");
                break;
            }
            default: {
                newItem = new QTableWidgetItem("Other");
                break;
            }
        }

        ui->tableWidget->setItem(i,0,newItem);

        newItem = new QTableWidgetItem("Goods "+QString::number(i));
        ui->tableWidget->setItem(i,1,newItem);

        newItem = new QTableWidgetItem(QString::number(i*10));
        ui->tableWidget->setItem(i,2,newItem);

        newItem = new QTableWidgetItem(QString::number(i*100));
        ui->tableWidget->setItem(i,3,newItem);

        newItem = new QTableWidgetItem(QString::number(i*1000));
        ui->tableWidget->setItem(i,4,newItem);
    }
}

void ExampleDlg6::setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage)
{
    Q_UNUSED(reportPage);

    if ((paramName == "sampleId") && (reportPage >= 1)) {
        int id;
        if (recNo < 6) id = 1;
        else id = 2;
        QString strLeft = "Sample" + QString::number(id);
        qDebug() << "Group: " << strLeft << " " << recNo;
        paramValue = strLeft;
    }
    else if (paramName == "sNameLeft") {
        QString strLeft = "sNameLeft " + QString::number(recNo);
        paramValue = strLeft;
    }
    else if (paramName == "sNameRight") {
        QString strLeft = "sNameRight " + QString::number(recNo);
        paramValue = strLeft;
    }
    else if (paramName == "sValueLeft") {
        QString strLeft = "svalLeft " + QString::number(recNo);
        paramValue = strLeft;
    }
    else if (paramName == "sValueRight") {
        QString strLeft = "svalLeft " + QString::number(recNo);
        paramValue = strLeft;
    }
    else if (paramName == "nameLeft") {
        QString strLeft = "nameLeft " + QString::number(recNo);
        paramValue = strLeft;
    }
    else if (paramName == "nameRight") {
        QString strLeft = "nameRight " + QString::number(recNo);
        paramValue = strLeft;
    }
    else if (paramName == "valueLeft") {
        QString strLeft = "valLeft " + QString::number(recNo);
        paramValue = strLeft;
    }
    else if (paramName == "valueRight") {
        QString strLeft = "valLeft " + QString::number(recNo);
        paramValue = strLeft;
    }

    if (paramName == "Market") {
        if (ui->tableWidget->item(recNo,0) == 0) return;
        paramValue = ui->tableWidget->item(recNo,0)->text();
    }
    if (paramName == "Goods") {
        if (ui->tableWidget->item(recNo,1) == 0) return;
        paramValue = ui->tableWidget->item(recNo,1)->text();
    }
    if (paramName == "Quantity") {
        if (ui->tableWidget->item(recNo,2) == 0) return;
        paramValue = ui->tableWidget->item(recNo,2)->text();
    }
    if (paramName == "Price") {
        if (ui->tableWidget->item(recNo,3) == 0) return;
        paramValue = ui->tableWidget->item(recNo,3)->text();
    }
    if (paramName == "Sum") {
        if (ui->tableWidget->item(recNo,4) == 0) return;
        paramValue = ui->tableWidget->item(recNo,4)->text();
    }
}

void ExampleDlg6::print()
{
    QDir dir(qApp->applicationDirPath());
    #if defined(Q_OS_MAC)
        dir.cd(QFile::decodeName("../Resources"));
    #endif

    QString fileName;
    if (m_mode == 1)
        fileName = dir.absolutePath()+"/examples_report/example6a.xml";
    if (m_mode == 2)
        fileName = dir.absolutePath()+"/examples_report/example6b.xml";
    report = new QtRPT(this);

    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report file not found";
    }
    QObject::connect(report, SIGNAL(setValue(const int, const QString, QVariant&, const int)),
                     this, SLOT(setValue(const int, const QString, QVariant&, const int)));
    QObject::connect(report, SIGNAL(setRecordCount(const int, int &)),
                     this, SLOT(setRecordCount(const int, int &)));
    report->printExec();
}

void ExampleDlg6::setRecordCount(const int reportPage, int &recordCount)
{
    recordCount = ui->tableWidget->rowCount();
}

ExampleDlg6::~ExampleDlg6()
{
    delete ui;
}

