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

#include <QSettings>
#include <QtDebug>
#include <QColorDialog>
#include "PageSettingDlg.h"
#include "ui_PageSettingDlg.h"
#include "CommonClasses.h"

PageSettingDlg::PageSettingDlg(QWidget *parent)
: QDialog(parent), ui(new Ui::PageSettingDlg)
{
    ui->setupUi(this);

    QObject::connect(ui->rLandscape, SIGNAL(clicked()), this, SLOT(changeOrientation()));
    QObject::connect(ui->rPortrait, SIGNAL(clicked()), this, SLOT(changeOrientation()));
    QObject::connect(ui->cbPageSize, SIGNAL(currentIndexChanged(int)), this, SLOT(pageSizeChanged(int)));
    QObject::connect(ui->btnBorderColor, SIGNAL(clicked()), this, SLOT(selectColor()));
    ui->chkDrawBorder->setChecked(false);
    ui->spnBorderWidth->setValue(1);
    ui->lblBorderColor->setStyleSheet("QLabel {background-color: black}");
    
    for (quint32 i = 1; i < 7; i++) {
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/fs%1.png").arg(i)), QIcon::Normal, QIcon::On);
        ui->cmbBorderStyle->addItem(icon,"", i);
    }
}

void PageSettingDlg::showThis(PageSetting pageSetting)
{
    QSettings settings(QCoreApplication::applicationDirPath()+"/setting.ini",QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.beginGroup("language");
    QString measurement = settings.value("measurement").toString();
    settings.endGroup();
    QString meas_label;

    if (measurement == "" || measurement == "Cm") {
        meas_label = tr("Cm");
        koef = 40;
    } else if (measurement == "Inch") {
        meas_label = tr("Inch");
        koef = 101.59;
    }

    if (pageSetting.pageWidth == w_A3 && pageSetting.pageHeight == h_A3) ui->cbPageSize->setCurrentIndex(0);
    else if (pageSetting.pageWidth == w_A4 && pageSetting.pageHeight == h_A4) ui->cbPageSize->setCurrentIndex(1);
    else if (pageSetting.pageWidth == w_A5 && pageSetting.pageHeight == h_A5) ui->cbPageSize->setCurrentIndex(2);
    else if (pageSetting.pageWidth == w_Lt && pageSetting.pageHeight == h_Lt) ui->cbPageSize->setCurrentIndex(3);
    else ui->cbPageSize->setCurrentIndex(1);

    ui->label->setText(meas_label);
    ui->label_2->setText(meas_label);
    ui->label_3->setText(meas_label);
    ui->label_4->setText(meas_label);
    ui->label_12->setText(meas_label);
    ui->label_13->setText(meas_label);

    ui->edtLeft->setText(QString::number(pageSetting.marginsLeft/koef, 'f', 2));
    ui->edtRight->setText(QString::number(pageSetting.marginsRight/koef, 'f', 2));
    ui->edtTop->setText(QString::number(pageSetting.marginsTop/koef, 'f', 2));
    ui->edtBottom->setText(QString::number(pageSetting.marginsBottom/koef, 'f', 2));
    ui->edtWidth->setText(QString::number(pageSetting.pageWidth/koef, 'f', 2));
    ui->edtHeight->setText(QString::number(pageSetting.pageHeight/koef, 'f', 2));

    if (pageSetting.pageOrientation == 0)
        ui->rPortrait->setChecked(true);
    if (pageSetting.pageOrientation == 1)
        ui->rLandscape->setChecked(true);
    if (ui->rLandscape->isChecked())
        ui->lblOrientation->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/landscape.png")));
    if (ui->rPortrait->isChecked())
        ui->lblOrientation->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/portrait.png")));

    ui->chkDrawBorder->setChecked(pageSetting.border);
    ui->spnBorderWidth->setValue(pageSetting.borderWidth);
    ui->lblBorderColor->setStyleSheet("QLabel {background-color: "+pageSetting.borderColor+"}");
    strColor = pageSetting.borderColor;

    ui->chckWatermark->setChecked(pageSetting.watermark);

    if (pageSetting.borderStyle == "solid") ui->cmbBorderStyle->setCurrentIndex(0);
    if (pageSetting.borderStyle == "dashed") ui->cmbBorderStyle->setCurrentIndex(1);
    if (pageSetting.borderStyle == "dotted") ui->cmbBorderStyle->setCurrentIndex(2);
    if (pageSetting.borderStyle == "dot-dash") ui->cmbBorderStyle->setCurrentIndex(3);
    if (pageSetting.borderStyle == "dot-dot-dash") ui->cmbBorderStyle->setCurrentIndex(4);
    if (pageSetting.borderStyle == "double") ui->cmbBorderStyle->setCurrentIndex(5);

    if (exec() == QDialog::Accepted)
        saveSettings();
}

void PageSettingDlg::pageSizeChanged(int index)
{
    switch(index) {
    case 0: //A3
        ui->edtWidth->setText(QString::number(w_A3/koef,'f',2));
        ui->edtHeight->setText(QString::number(h_A3/koef,'f',2));
        break;
    case 1: //A4
        ui->edtWidth->setText(QString::number(w_A4/koef,'f',2));
        ui->edtHeight->setText(QString::number(h_A4/koef,'f',2));
        break;
    case 2: //A5
        ui->edtWidth->setText(QString::number(w_A5/koef,'f',2));
        ui->edtHeight->setText(QString::number(h_A5/koef,'f',2));
        break;
    case 3: //Letter
        ui->edtWidth->setText(QString::number(w_Lt/koef,'f',2));
        ui->edtHeight->setText(QString::number(h_Lt/koef,'f',2));
        break;
    }
}

void PageSettingDlg::changeOrientation()
{
    QString str = ui->edtHeight->text();
    ui->edtHeight->setText(ui->edtWidth->text());
    ui->edtWidth->setText(str);
    if (ui->rLandscape->isChecked())
        ui->lblOrientation->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/landscape.png")));
    if (ui->rPortrait->isChecked())
        ui->lblOrientation->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/portrait.png")));
}

void PageSettingDlg::saveSettings()
{
    pageSetting.marginsLeft   = QString::number(ui->edtLeft->text().toFloat()*koef,'f',0).toFloat();
    pageSetting.marginsRight  = QString::number(ui->edtRight->text().toFloat()*koef,'f',0).toFloat();
    pageSetting.marginsTop    = QString::number(ui->edtTop->text().toFloat()*koef,'f',0).toFloat();
    pageSetting.marginsBottom = QString::number(ui->edtBottom->text().toFloat()*koef,'f',0).toFloat();
    pageSetting.pageWidth     = QString::number(ui->edtWidth->text().toFloat()*koef,'f',0).toFloat();
    pageSetting.pageHeight    = QString::number(ui->edtHeight->text().toFloat()*koef,'f',0).toFloat();
    pageSetting.border        = ui->chkDrawBorder->isChecked();
    pageSetting.borderWidth   = ui->spnBorderWidth->value();
    pageSetting.borderColor   = strColor;
    pageSetting.watermark     = ui->chckWatermark->isChecked();

    if (ui->rLandscape->isChecked())
        pageSetting.pageOrientation = 1;
    if (ui->rPortrait->isChecked())
        pageSetting.pageOrientation = 0;

    switch(ui->cmbBorderStyle->currentIndex()) {
    case 0:
        pageSetting.borderStyle = "solid";
        break;
    case 1:
        pageSetting.borderStyle = "dashed";
        break;
    case 2:
        pageSetting.borderStyle = "dotted";
        break;
    case 3:
        pageSetting.borderStyle = "dot-dash";
        break;
    case 4:
        pageSetting.borderStyle = "dot-dot-dash";
        break;
    case 5:
        pageSetting.borderStyle = "double";
        break;
    default: break;
    }
}

void PageSettingDlg::selectColor()
{
    QColor color;
    QScopedPointer<QColorDialog> dlg(new QColorDialog(color, this));
    if (dlg->exec() == QDialog::Accepted)
        color = dlg->selectedColor();
    else
        return;

    strColor = colorToString(color);
    pageSetting.borderColor = strColor;
    ui->lblBorderColor->setStyleSheet("QLabel {background-color: "+strColor+"}");
}

PageSettingDlg::~PageSettingDlg()
{
    delete ui;
}
