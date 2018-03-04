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

#include "exampledlg7.h"
#include "ui_exampledlg7.h"
#include <QDir>
#include <QDebug>

ExampleDlg7::ExampleDlg7(QWidget *parent)
: QDialog(parent), ui(new Ui::ExampleDlg7)
{
    ui->setupUi(this);

    QObject::connect(ui->btnPrint, SIGNAL(clicked()), this, SLOT(print()));

    ui->tableWidget->setRowCount(12);
    QTableWidgetItem *newItem;

    newItem = new QTableWidgetItem("January");
    ui->tableWidget->setItem(0,0,newItem);

    newItem = new QTableWidgetItem("February");
    ui->tableWidget->setItem(1,0,newItem);

    newItem = new QTableWidgetItem("March");
    ui->tableWidget->setItem(2,0,newItem);

    newItem = new QTableWidgetItem("April");
    ui->tableWidget->setItem(3,0,newItem);

    newItem = new QTableWidgetItem("May");
    ui->tableWidget->setItem(4,0,newItem);

    newItem = new QTableWidgetItem("June");
    ui->tableWidget->setItem(5,0,newItem);

    newItem = new QTableWidgetItem("July");
    ui->tableWidget->setItem(6,0,newItem);

    newItem = new QTableWidgetItem("August");
    ui->tableWidget->setItem(7,0,newItem);

    newItem = new QTableWidgetItem("September");
    ui->tableWidget->setItem(8,0,newItem);

    newItem = new QTableWidgetItem("October");
    ui->tableWidget->setItem(9,0,newItem);

    newItem = new QTableWidgetItem("November");
    ui->tableWidget->setItem(10,0,newItem);

    newItem = new QTableWidgetItem("December");
    ui->tableWidget->setItem(11,0,newItem);  //qrand()

    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        for (int j = 1; j < ui->tableWidget->columnCount(); ++j) {
            newItem = new QTableWidgetItem(QString::number((long)(32767 * (float)qrand() / RAND_MAX)));
            ui->tableWidget->setItem(i,j,newItem);
        }
    }
}

void ExampleDlg7::setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage)
{
    Q_UNUSED(reportPage);
    if (paramName == "month") {
        if (ui->tableWidget->item(recNo,0) == 0) return;
        paramValue = ui->tableWidget->item(recNo,0)->text();
    }
    if (paramName == "eur") {
        if (ui->tableWidget->item(recNo,1) == 0) return;
        paramValue = ui->tableWidget->item(recNo,1)->text();
    }
    if (paramName == "us") {
        if (ui->tableWidget->item(recNo,2) == 0) return;
        paramValue = ui->tableWidget->item(recNo,2)->text();
    }
    if (paramName == "ukraine") {
        if (ui->tableWidget->item(recNo,3) == 0) return;
        paramValue = ui->tableWidget->item(recNo,3)->text();
    }
    if (paramName == "georgia") {
        if (ui->tableWidget->item(recNo,4) == 0) return;
        paramValue = ui->tableWidget->item(recNo,4)->text();
    }
    if (paramName == "other") {
        if (ui->tableWidget->item(recNo,5) == 0) return;
        paramValue = ui->tableWidget->item(recNo,5)->text();
    }
}

void ExampleDlg7::setValueDiagram(Chart &chart)
{
    if (chart.objectName() == "diagram1") {
        GraphParam param;

        param.color = colorFromString("rgba(255,255,0,255)");
        param.valueReal = 150;
        param.caption = "Graph 1";
        chart.setData(param);

        param.color = colorFromString("rgba(0,0,255,255)");
        param.valueReal = 70;
        param.caption = "Graph 2";
        chart.setData(param);

        param.color = colorFromString("rgba(255,0,0,255)");
        param.valueReal = 220;
        param.caption = "Graph 3";
        chart.setData(param);

        param.color = colorFromString("rgba(0,128,128,255)");
        param.valueReal = 30;
        param.caption = "Graph 4";
        chart.setData(param,150);
    }
}

void ExampleDlg7::print()
{
    QDir dir(qApp->applicationDirPath());
    #if defined(Q_OS_MAC)
        dir.cd(QFile::decodeName("../Resources"));
    #endif

    QString fileName = dir.absolutePath()+"/examples_report/example19.xml";
    auto report = QtRPT::createSPtr(this);

    if (report->loadReport(fileName) == false)
        qDebug()<<"Report file not found";

    QObject::connect(report.data(), SIGNAL(setDSInfo(DataSetInfo &)),
                     this, SLOT(setDSInfo(DataSetInfo &)));

    //QObject::connect(report.data(), SIGNAL(setValue(const int, const QString, QVariant&, const int)),
    //                 this, SLOT(setValue(const int, const QString, QVariant&, const int)));
    //QObject::connect(report.data(), SIGNAL(setValueDiagram(Chart&)),this,SLOT(setValueDiagram(Chart&)));
    report->printExec();

    /*QString fileName = dir.absolutePath()+"/examples_report/example7.xml";
    auto report = QtRPT::createSPtr(this);
    report->recordCount = ui->tableWidget->rowCount();
    if (report->loadReport(fileName) == false)
        qDebug()<<"Report file not found";

    QObject::connect(report.data(), SIGNAL(setValue(const int, const QString, QVariant&, const int)),
                     this, SLOT(setValue(const int, const QString, QVariant&, const int)));
    QObject::connect(report.data(), SIGNAL(setValueDiagram(Chart&)),this,SLOT(setValueDiagram(Chart&)));
    report->printExec();*/
}

void ExampleDlg7::setDSInfo(DataSetInfo &dsInfo)
{
    dsInfo.recordCount = ui->tableWidget->rowCount();
}

ExampleDlg7::~ExampleDlg7()
{
    delete ui;
}
