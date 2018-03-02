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

#include "SettingDlg.h"
#include "ui_SettingDlg.h"
#include <QMessageBox>
#include <QProcess>

SettingDlg::SettingDlg(QWidget *parent)
: QDialog(parent),  ui(new Ui::SettingDlg)
{
    ui->setupUi(this);
    QSettings settings(QCoreApplication::applicationDirPath()+"/setting.ini",QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    ui->dsp1->setValue(settings.value("GridStep",1).toDouble());
    ui->chShowGrid->setChecked(settings.value("ShowGrid",true).toBool());
    ui->chkUpdates->setChecked(settings.value("CheckUpdates",true).toBool());

    settings.beginGroup("language");

    QString language = settings.value("language").toString();
    if (language == "")  // Default system language
        ui->cmbLanguage->setCurrentIndex(0);
    else if (language == "Arabic")
        ui->cmbLanguage->setCurrentIndex(1);
    else if (language == "en_US")  // English United states
        ui->cmbLanguage->setCurrentIndex(2);
    else if (language == "zh_CN")  // Chinese
        ui->cmbLanguage->setCurrentIndex(3);
    else if (language == "nl_BE")  // Dutch
        ui->cmbLanguage->setCurrentIndex(4);
    else if (language == "fr_FR")  // French
        ui->cmbLanguage->setCurrentIndex(5);
    else if (language == "ka_GE")  // Georgian
        ui->cmbLanguage->setCurrentIndex(6);
    else if (language == "de_DE")  // German
        ui->cmbLanguage->setCurrentIndex(7);
    else if (language == "it_IT")  // Italian
        ui->cmbLanguage->setCurrentIndex(8);
    else if (language == "pt_PT")  // Portuguese
        ui->cmbLanguage->setCurrentIndex(9);
    else if (language == "ru_RU")  // russian
        ui->cmbLanguage->setCurrentIndex(10);
    else if (language == "sr_RS")  // serbian cyrilic
        ui->cmbLanguage->setCurrentIndex(11);
    else if (language == "sr_RS@latin")
        ui->cmbLanguage->setCurrentIndex(12);
    else if (language == "es_ES")
        ui->cmbLanguage->setCurrentIndex(13);
    else if (language == "ta_IN")
        ui->cmbLanguage->setCurrentIndex(14);
    else if (language == "uk_UA")
        ui->cmbLanguage->setCurrentIndex(15);


    langIndex = ui->cmbLanguage->currentIndex();

    QString measurement = settings.value("measurement").toString();
    if (measurement == "")
        ui->rbCm->setChecked(true);
    else if (measurement == "Cm")
        ui->rbCm->setChecked(true);
    else if (measurement == "Inch")
        ui->rbInch->setChecked(true);
    settings.endGroup();
}

void SettingDlg::showThis()
{
    if (exec() == QDialog::Accepted) {
        QSettings settings(QCoreApplication::applicationDirPath()+"/setting.ini",QSettings::IniFormat);
        settings.setIniCodec("UTF-8");
        settings.setValue("GridStep", ui->dsp1->value());
        settings.setValue("ShowGrid", ui->chShowGrid->checkState());
        settings.setValue("CheckUpdates", ui->chkUpdates->checkState());

        settings.beginGroup("language");
        if (ui->cmbLanguage->currentIndex() != langIndex) {
            switch(ui->cmbLanguage->currentIndex()) {
                case 0:  // system default
                    settings.setValue("language", "");
                    break;
                case 1:  // Arabic
                    settings.setValue("language", "ar");
                    break;
                case 2:  // American english
                    settings.setValue("language", "en_US");
                    break;
                case 3:  // Chinese
                    settings.setValue("language", "zh_CN");
                    break;
                case 4:  // Dutch
                    settings.setValue("language", "nl_BE");
                    break;
                case 5:  // French
                    settings.setValue("language", "fr_FR");
                    break;
                case 6:  // Georgian
                    settings.setValue("language", "ka_GE");
                    break;
                case 7:  // German
                    settings.setValue("language", "de_DE");
                    break;
                case 8:  // Italian
                    settings.setValue("language", "it_IT");
                    break;
                case 9:  // Portuguese
                    settings.setValue("language", "pt_PT");
                    break;
                case 10:  // russian
                    settings.setValue("language", "ru_RU");
                    break;
                case 11:  // serbian
                    settings.setValue("language", "sr_RS");
                    break;
                case 12:  // serbian latin
                    settings.setValue("language", "sr_RS@latin");
                    break;
                case 13:  // Sspanish
                    settings.setValue("language", "es_ES");
                    break;
                case 14:  // Tamil
                    settings.setValue("language", "ta_IN");
                    break;
                case 15:  // Ukraine
                    settings.setValue("language", "uk_UA");
                    break;
            }
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, tr("Message QtRptDesigner"),
                                          tr("The language for this application has been changed.\n"
                                             "The change will take effect the next time the application is started.\n"
                                             "Restart application?"),
                                             QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                this->parentWidget()->close();
                QProcess::startDetached(QApplication::applicationFilePath());
            }
        }

        if (ui->rbCm->isChecked())
            settings.setValue("measurement", "Cm");
        else if (ui->rbInch->isChecked())
            settings.setValue("measurement", "Inch");
        else
            settings.setValue("measurement", "Cm");

        settings.endGroup();
    }
}

SettingDlg::~SettingDlg()
{
    delete ui;
}
