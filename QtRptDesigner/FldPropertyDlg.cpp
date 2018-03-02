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

#include "FldPropertyDlg.h"
#include "ui_FldPropertyDlg.h"
#include "ReportBand.h"

FldPropertyDlg::FldPropertyDlg(QWidget *parent)
: QDialog(parent), ui(new Ui::FldPropertyDlg)
{
    ui->setupUi(this);
}

QString FldPropertyDlg::showThis(int index, GraphicsBox *widget, QString value)
{
    QIcon iconFolder(QPixmap(QString::fromUtf8(":/new/prefix1/images/folder.png")));
    QIcon iconVariable(QPixmap(QString::fromUtf8(":/new/prefix1/images/variable.png")));
    QIcon iconFunction(QPixmap(QString::fromUtf8(":/new/prefix1/images/function1.png")));
    if (index == 3)
        ui->stackedWidget->setCurrentIndex(0);
    else
        ui->stackedWidget->setCurrentIndex(index);

    switch(index) {
        case 0:
        case 3: {
            QTreeWidgetItem *rootItem = new QTreeWidgetItem(ui->treeWidget,0);
            rootItem->setIcon(0,iconFolder);
            rootItem->setExpanded(true);

            QTreeWidgetItem *f1 = new QTreeWidgetItem(rootItem);
            f1->setIcon(0,iconFolder);
            f1->setExpanded(true);
            rootItem->addChild(f1);

            QTreeWidgetItem *item;
            if (index == 0) {   // Variables
                rootItem->setText(0,tr("Variables"));
                f1->setText(0,tr("System variables"));

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconVariable);
                item->setText(0,"Date");
                item->setData(0,Qt::UserRole,"<Date>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconVariable);
                item->setText(0,"Time");
                item->setData(0,Qt::UserRole,"<Time>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconVariable);
                item->setText(0,"Page");
                item->setData(0,Qt::UserRole,"<Page>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconVariable);
                item->setText(0,"TotalPages");
                item->setData(0,Qt::UserRole,"<TotalPages>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconVariable);
                item->setText(0,"LineNo");
                item->setData(0,Qt::UserRole,"<LineNo>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconVariable);
                item->setText(0,"LineCount");
                item->setData(0,Qt::UserRole,"<LineCount>");
                f1->addChild(item);

                this->setWindowTitle(tr("Variables"));
                this->setWindowIcon(iconVariable);
            }
            if (index == 3) {   // Functions
                rootItem->setText(0,tr("Functions"));

                //------------------Aggregate functions----------------------
                f1->setText(0,tr("Aggregate functions"));

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setText(0,"Sum");
                item->setData(0,Qt::UserRole,"<Sum([])>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setText(0,"Avg");
                item->setData(0,Qt::UserRole,"<Avg([])>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setText(0,"Count");
                item->setData(0,Qt::UserRole,"<Count([])>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setText(0,"Max");
                item->setData(0,Qt::UserRole,"<Max([])>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setText(0,"Min");
                item->setData(0,Qt::UserRole,"<Min([])>");
                f1->addChild(item);

                //------------------Text functions----------------------
                f1 = new QTreeWidgetItem(rootItem);
                f1->setIcon(0,iconFolder);
                f1->setText(0,tr("Text functions"));
                f1->setExpanded(true);
                rootItem->addChild(f1);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setToolTip(0,tr("Replace"));
                item->setText(0,"Replace");
                item->setData(0,Qt::UserRole,"<Replace(String, OldStr, NewStr)>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setToolTip(0,tr("To upper case"));
                item->setText(0,"To Upper");
                item->setData(0,Qt::UserRole,"<ToUpper(Word)>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setToolTip(0,tr("To lower case"));
                item->setText(0,"To Lower");
                item->setData(0,Qt::UserRole,"<ToLower(Word)>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setToolTip(0,tr("English"));
                item->setText(0,"NumberToWords (ENG)");
                item->setData(0,Qt::UserRole,"<NumberToWords('ENG', )>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setToolTip(0,tr("German"));
                item->setText(0,"NumberToWords (GER)");
                item->setData(0,Qt::UserRole,"<NumberToWords('GER', )>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setToolTip(0,tr("Ukrainian"));
                item->setText(0,"NumberToWords (UKR)");
                item->setData(0,Qt::UserRole,"<NumberToWords('UKR', )>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setToolTip(0,tr("Spanish"));
                item->setText(0,"NumberToWords (ESP)");
                item->setData(0,Qt::UserRole,"<NumberToWords('ESP', )>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setToolTip(0,tr("French"));
                item->setText(0,"NumberToWords (FR_FR)");
                item->setData(0,Qt::UserRole,"<NumberToWords('FR', )>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setToolTip(0,tr("French(BE)"));
                item->setText(0,"NumberToWords (FR_BE)");
                item->setData(0,Qt::UserRole,"<NumberToWords('FR_BE', )>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setToolTip(0,tr("French(CH)"));
                item->setText(0,"NumberToWords (FR_CH)");
                item->setData(0,Qt::UserRole,"<NumberToWords('FR_CH', )>");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setToolTip(0,tr("Italian"));
                item->setText(0,"NumberToWords (ITA)");
                item->setData(0,Qt::UserRole,"<NumberToWords('ITA', )>");
                f1->addChild(item);

                //------------------Math functions----------------------
                f1 = new QTreeWidgetItem(rootItem);
                f1->setIcon(0,iconFolder);
                f1->setText(0,tr("Math functions"));
                f1->setExpanded(true);
                rootItem->addChild(f1);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setText(0,"Frac");
                item->setData(0,Qt::UserRole,"Frac()");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setText(0,"Floor");
                item->setData(0,Qt::UserRole,"Floor()");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setText(0,"Ceil");
                item->setData(0,Qt::UserRole,"Ceil()");
                f1->addChild(item);

                item = new QTreeWidgetItem(f1);
                item->setIcon(0,iconFunction);
                item->setText(0,"Round");
                item->setData(0,Qt::UserRole,"Round()");
                f1->addChild(item);

                this->setWindowTitle(tr("Functions"));
                this->setWindowIcon(iconFunction);
            }
            break;
        }
        case 1: {
            this->setWindowTitle(tr("Data Group property"));
            ReportBand *band = qgraphicsitem_cast<ReportBand *>(widget);
            ui->edtFiledGrouping->setText(band->getGroupingField());
            ui->chkStartLineNum->setChecked(band->getStartNewNumertaion());
            ui->chkStartNewPage->setChecked(band->getStartNewPage());
            break;
        }
        case 2: {
            this->setWindowTitle(tr("Formatting"));
            QObject::connect(ui->lstCategory, SIGNAL(currentRowChanged(int)), this, SLOT(changeCategory(int)));
            QObject::connect(ui->lstFormat, SIGNAL(currentRowChanged(int)), this, SLOT(changeFormat(int)));

            QObject::connect(ui->spnPrecision, SIGNAL(valueChanged(int)), this, SLOT(precisionChanged(int)));
            //QString value = "N#,###.##8";
            ui->edtFornatString->setText(value);
            if (value.isEmpty()) {
                ui->spnPrecision->setValue(2);
                ui->lstCategory->setCurrentRow(0);
                ui->lstFormat->setCurrentRow(-1);
            } else {
                if (value.at(0) == 'N') {
                    ui->lstCategory->setCurrentRow(0);
                    ui->spnPrecision->setValue( value.mid(value.size()-1,1).toInt() );
                    if ( value.mid(1,value.size()-2) == "# ###.##")
                        ui->lstFormat->setCurrentRow(0);
                    if ( value.mid(1,value.size()-2) == "#,###.##")
                        ui->lstFormat->setCurrentRow(1);
                    if ( value.mid(1,value.size()-2) == "# ###,##")
                        ui->lstFormat->setCurrentRow(2);
                    if ( value.mid(1,value.size()-2) == "#.###,##")
                        ui->lstFormat->setCurrentRow(3);
                }
            }

            ui->lstCategory->item(0)->setData(Qt::UserRole,"N");
            break;
        }
    }

    if (this->exec()) {
        switch(index) {
            case 0:
            case 3: {
                return ui->treeWidget->selectedItems().at(0)->data(0,Qt::UserRole).toString();
                break;
            }
            case 1: {
                ReportBand *band = qgraphicsitem_cast<ReportBand *>(widget);
                band->setGroupingField(ui->edtFiledGrouping->text());
                band->setStartNewNumeration(ui->chkStartLineNum->checkState());
                band->setStartNewPage(ui->chkStartNewPage->checkState());
                return "";
                break;
            }
            case 2: {
                return ui->edtFornatString->text();
                break;
            }
            default:
                return "";
        }
    } else {
        return "";
    }
}

void FldPropertyDlg::changeCategory(int row)
{
    if (row == 0) {
        ui->lstFormat->clear();
        QListWidgetItem *item;
        item = new QListWidgetItem("1 234.00", ui->lstFormat);
        item->setData(Qt::UserRole,"# ###.##");
        ui->lstFormat->addItem(item);
        item = new QListWidgetItem("1,234.00", ui->lstFormat);
        item->setData(Qt::UserRole,"#,###.##");
        ui->lstFormat->addItem(item);
        item = new QListWidgetItem("1 234,00", ui->lstFormat);
        item->setData(Qt::UserRole,"# ###,##");
        ui->lstFormat->addItem(item);
        item = new QListWidgetItem("1.234,00", ui->lstFormat);
        item->setData(Qt::UserRole,"#.###,##");
        ui->lstFormat->addItem(item);

        ui->lstFormat->setCurrentRow(0);
    }
}

void FldPropertyDlg::changeFormat(int row)
{
    if (row >= 0) {
        ui->edtFornatString->setText(
            ui->lstCategory->item(ui->lstCategory->currentRow())->data(Qt::UserRole).toString()+
            ui->lstFormat->item(row)->data(Qt::UserRole).toString()+
            ui->spnPrecision->text()
        );
    } else {
        ui->edtFornatString->setText("");
    }
}

void FldPropertyDlg::precisionChanged(int row)
{
    Q_UNUSED(row);
    changeFormat(ui->lstFormat->currentRow());
}

FldPropertyDlg::~FldPropertyDlg()
{
    delete ui;
}
