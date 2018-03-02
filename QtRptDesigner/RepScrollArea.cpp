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

#include "RepScrollArea.h"
#include "ui_RepScrollArea.h"
#include <QGraphicsDropShadowEffect>
#include <QSettings>
#include <QScrollBar>

RepScrollArea::RepScrollArea(QTreeWidgetItem* rootItem, QWidget *parent)
: QScrollArea(parent), ui(new Ui::RepScrollArea)
{
    ui->setupUi(this);
    m_mainWindow = parent;
    m_rootItem = rootItem;

    auto bar = verticalScrollBar();
    QObject::connect(bar, SIGNAL(valueChanged(int)), this, SLOT(vScrolling(int)));

    scene = new GraphicsScene(this);
    scene->setSceneRect(0,0,800,800);
    QObject::connect(scene, SIGNAL(sceneClick()), m_mainWindow, SLOT(sceneClick()));
    QObject::connect(scene, SIGNAL(itemAdded(QGraphicsItem *)), m_mainWindow, SLOT(sceneItemAdded(QGraphicsItem *)));
    QObject::connect(scene, SIGNAL(itemSelected(QGraphicsItem *)), m_mainWindow, SLOT(sceneItemSelectionChanged(QGraphicsItem *)));

    QObject::connect(scene, SIGNAL(itemResized(QGraphicsItem *)), m_mainWindow, SLOT(itemResizing(QGraphicsItem *)));
    QObject::connect(scene, SIGNAL(mousePos(QPointF)), m_mainWindow, SLOT(mousePos(QPointF)));

    auto actShowGrid = m_mainWindow->findChild<QAction*>("actShowGrid");
    QObject::connect(actShowGrid, SIGNAL(triggered(bool)), this, SLOT(showGrid(bool)));

    auto actUndo = m_mainWindow->findChild<QAction*>("actUndo");
    QObject::connect(scene->m_undoStack, SIGNAL(canUndoChanged(bool)), actUndo, SLOT(setEnabled(bool)));

    auto actRedo = m_mainWindow->findChild<QAction*>("actRedo");
    QObject::connect(scene->m_undoStack, SIGNAL(canRedoChanged(bool)), actRedo, SLOT(setEnabled(bool)));

    ui->graphicsView->setContentsMargins(0,0,0,0);
    ui->graphicsView->setScene(scene);
    //ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    //ui->graphicsView->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);

    pageSetting.marginsLeft     = 40;
    pageSetting.marginsRight    = 40;
    pageSetting.marginsTop      = 40;
    pageSetting.marginsBottom   = 40;
    pageSetting.pageWidth       = 840;
    pageSetting.pageHeight      = 1188;
    pageSetting.pageOrientation = 0;
    pageSetting.border          = false;
    pageSetting.borderWidth     = 1;
    pageSetting.watermark       = false;

    this->setMouseTracking(true);
    this->installEventFilter(parent);
    scene->installEventFilter(parent);
    
    ui->horRuler->installEventFilter(this);
    ui->verRuler->installEventFilter(this);

    this->setVisible(true);
    m_scale = 1;
    setPaperSize(0);

    setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(5);
    ui->graphicsView->setGraphicsEffect(effect);

    QSettings settings(QCoreApplication::applicationDirPath()+"/setting.ini",QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    bool isShowGrid = settings.value("ShowGrid",true).toBool();
    showGrid(isShowGrid);
}

void RepScrollArea::vScrolling(int value)
{
    Q_UNUSED(value);
    scene->update();
}

double RepScrollArea::setPaperSize(qreal scale)
{
    if (scale == 0) {
        m_scale = 1;
    } else {
        if (qFabs(scale) > 1) {  //Change zoom from combobox
            m_scale = scale/100;
            if (m_scale < 0.5) return -1;
        } else {  //Change zoom from wheel or click mouse
            if (scale>0)
                m_scale += 0.25;
            else
                m_scale += -0.25;
        }

        if (m_scale < 0.5) {  //Not allow zoom less than 50%
            m_scale = 0.5;
            return -1;
        }
    }

    scene->setMargins(pageSetting.marginsLeft,
                      pageSetting.marginsRight,
                      pageSetting.marginsTop,
                      pageSetting.marginsBottom);

    scene->setSceneRect(0, 0, pageSetting.pageWidth, pageSetting.pageHeight);

    correctBandGeom();

    ui->graphicsView->setMinimumWidth(pageSetting.pageWidth*m_scale);
    ui->graphicsView->setMinimumHeight(pageSetting.pageHeight*m_scale);
    ui->graphicsView->resize(pageSetting.pageWidth*m_scale, pageSetting.pageHeight*m_scale);
    ui->leftMarginsSpacer->changeSize(pageSetting.marginsLeft*m_scale+26,
                                      ui->leftMarginsSpacer->sizeHint().height(),
                                      QSizePolicy::Fixed,
                                      QSizePolicy::Fixed);
    ui->verticalLayout_10->invalidate();
    ui->topMarginsSpacer->changeSize(ui->topMarginsSpacer->sizeHint().width(),pageSetting.marginsTop*m_scale,QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->verticalLayout_52->invalidate();

    getKoef();

    return m_scale;
}

void RepScrollArea::setScale(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() ;/// 100.0;
    setPaperSize(newScale);

    QMatrix oldMatrix = ui->graphicsView->matrix();
    ui->graphicsView->resetMatrix();
    ui->graphicsView->translate(oldMatrix.dx(), oldMatrix.dy());
    ui->graphicsView->scale(newScale/100, newScale/100);
}

qreal RepScrollArea::getScale()
{
    return m_scale;
}

void RepScrollArea::clearReport()
{
    m_scale = 1;
    setPaperSize(100);
    scene->clear();
    scene->update();
}

bool RepScrollArea::allowField()
{
    for (const auto &item : scene->items())
        if (item->type() == ItemType::GBand)
            return true;

    return false;
}

void RepScrollArea::showGrid(bool value)
{
    QSettings settings(QCoreApplication::applicationDirPath()+"/setting.ini",QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.setValue("ShowGrid", value);
    scene->isShowGrid = value;
    scene->setGridStep(settings.value("GridStep",1).toDouble());
    scene->setMargins(pageSetting.marginsLeft,
                      pageSetting.marginsRight,
                      pageSetting.marginsTop,
                      pageSetting.marginsBottom);
    getKoef();
    scene->setMesKoef(m_koef);
    scene->update();
}

void RepScrollArea::getKoef()
{
    QSettings settings(QCoreApplication::applicationDirPath()+"/setting.ini",QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    settings.beginGroup("language");
    QString measurement = settings.value("measurement").toString();
    settings.endGroup();

    if (measurement == "")
        m_koef = 40;
    else if (measurement == "Cm")
        m_koef = 40;
    else if (measurement == "Inch")
        m_koef = 101.59;
    m_koef = m_koef * m_scale;
}

void RepScrollArea::paintHorRuler()
{
    getKoef();
    QPainter painter(ui->horRuler);
    double x_ = 0 ;
    bool showNum = false;
    while ( x_ < ui->horRuler->width() ) {
        x_ = x_ + m_koef/2;
        if (showNum) {
            if (this->isLeftToRight()) {
                const QString rt = QString::number(x_/m_koef);
                painter.drawText(x_,15,rt);
            }
            if (this->isRightToLeft()) {
                const QString rt = QString::number(x_/m_koef);
                painter.drawText(ui->horRuler->width() - x_,15,rt);
            }
        } else {
            if (m_scale > 0.5) {
                if (this->isLeftToRight())
                    painter.drawText(x_,15,"-");
                if (this->isRightToLeft())
                    painter.drawText(ui->horRuler->width() - x_,15,"-");
            }
        }
        showNum=!showNum;
    }
}

void RepScrollArea::paintVerRuler()
{
    getKoef();
    QPainter painter(ui->verRuler);
    double y_ = 0 ;
    painter.rotate(-90);
    bool showNum = false;
    while ( y_ < ui->verRuler->height() ) {
        y_ = y_ + m_koef/2;
        if (showNum) {
            const QString rt = QString::number(y_/m_koef);
            painter.drawText(-y_,15,rt);
        } else {
            if (m_scale > 0.5)
                painter.drawText(-y_,15,"-");
        }
        showNum=!showNum;
    }
}

ReportBand* RepScrollArea::m_addBand(BandType type, QMenu *bandMenu, int m_height, QString objName, int bandNo)
{
    QMenu m_bandMenu;
    for (auto &action : bandMenu->actions()) {
        if (type == DataGroupHeader) {
            m_bandMenu.addAction(action);
        } else {
            if (action->objectName() != "actGroupProperty")
                m_bandMenu.addAction(action);
        }
    }

    int cnt = 1;
    if (objName.isEmpty()) {
        for (auto &band : getReportBands()) {
            if (band->bandType == type)
                cnt++;
        }
    } else {
        cnt = bandNo;
    }

    auto reportBand = new ReportBand(type, cnt);
    reportBand->setMenu(&m_bandMenu);
    reportBand->setZValue(10);
    if (!objName.isEmpty())
        reportBand->setObjectName(objName);

    reportBand->setWidth(pageSetting.pageWidth - pageSetting.marginsLeft - pageSetting.marginsRight);
    if (m_height != 0)
        reportBand->setHeight(m_height);
    else
        reportBand->setHeight(200);
    scene->addItem(reportBand);
    this->newFieldTreeItem(reportBand);
    reportBand->setSelected(true);

    QPointF p = ui->graphicsView->mapToScene(0,0);
    p.setX( p.x() + pageSetting.marginsLeft  ) ;
    p.setY( p.y() + pageSetting.marginsTop  ) ;
    reportBand->setPos(p);

    correctBandGeom();

    return reportBand;
}

void RepScrollArea::newFieldTreeItem(QGraphicsItem* item)
{
    ReportBand *gBand = nullptr;
    GraphicsBox *gItem = nullptr;
    GraphicsLine *gLine = nullptr;

    if (item->type() == ItemType::GBand)
        gBand = static_cast<ReportBand *>(item);
    if (item->type() == ItemType::GBox)
        gItem = static_cast<GraphicsBox *>(item);
    if (item->type() == ItemType::GLine)
        gLine = static_cast<GraphicsLine *>(item);

    QIcon icon;
    if (gBand != nullptr) {
        m_rootItem->treeWidget()->clearSelection();

        auto t_item = new QTreeWidgetItem(m_rootItem);
        icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/bands.png")), QIcon::Normal, QIcon::On);
        t_item->setIcon(0,icon);
        gBand->itemInTree = t_item;

        t_item->setText(0,gBand->objectName());
        t_item->setSelected(true);
        m_rootItem->setExpanded(true);

        for (const auto &child : gBand->childItems())
            newFieldTreeItem(child);
    }
    if (gItem != nullptr) {
        auto bandItem = static_cast<GraphicsBox*>(gItem->parentItem())->itemInTree;

        m_rootItem->treeWidget()->clearSelection();
        auto item = new QTreeWidgetItem(bandItem);
        gItem->itemInTree = item;
        if (gItem->getFieldType() == Text || gItem->getFieldType() == TextImage || gItem->getFieldType() == DatabaseImage)
            icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/field.png")), QIcon::Normal, QIcon::On);
        if (gItem->getFieldType() == Image)
            icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/picture.png")), QIcon::Normal, QIcon::On);
        if (gItem->getFieldType() == Diagram)
            icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/diagram.png")), QIcon::Normal, QIcon::On);
        if (QtRPT::getDrawingFields().contains(gItem->getFieldType()))
            icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/drawing.png")), QIcon::Normal, QIcon::On);
        if (gItem->getFieldType() == Barcode)
            icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/barcode.png")), QIcon::Normal, QIcon::On);
        if (gItem->getFieldType() == TextRich)
            icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/richText.png")), QIcon::Normal, QIcon::On);
        if (gItem->getFieldType() == CrossTab)
            icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/crossTab.png")), QIcon::Normal, QIcon::On);
        item->setIcon(0,icon);
        item->setText(0,gItem->objectName());
        item->setSelected(true);
        m_rootItem->addChild(item);
        bandItem->setExpanded(true);
    }
    if (gLine != nullptr) {
        auto bandItem = static_cast<GraphicsBox*>(gLine->parentItem())->itemInTree;

        m_rootItem->treeWidget()->clearSelection();
        auto item = new QTreeWidgetItem(bandItem);
        gLine->itemInTree = item;

        icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/line2.png")), QIcon::Normal, QIcon::On);
        item->setIcon(0,icon);
        item->setText(0,gLine->objectName());
        item->setSelected(true);
        m_rootItem->addChild(item);
        bandItem->setExpanded(true);
    }
}

//Correct band position after inserting, deleteing or changing margins
void RepScrollArea::correctBandGeom(ReportBand *rep)
{
    QPointF p = ui->graphicsView->mapToScene(0,0);
    int top_ = p.y()+pageSetting.marginsTop;
    int left_ = p.x()+pageSetting.marginsLeft;
    int width_ = pageSetting.pageWidth - pageSetting.marginsLeft - pageSetting.marginsRight;

    auto allReportBand = getReportBands();
    if (!allReportBand.isEmpty())
        std::sort(allReportBand.begin(), allReportBand.end(), [](ReportBand* p1, ReportBand* p2) {
//            Undefined = 0,
//            ReportTitle = 1,
//            PageHeader = 2,
//            DataGroupHeader = 3,
//            MasterHeader = 4,
//            MasterData = 5,
//            MasterFooter = 6,
//            DataGroupFooter = 7,
//            ReportSummary = 8,
//            PageFooter = 9

            int v1 = 0;
            int v2 = 0;

            if (p1->bandType < MasterHeader)
                v1 = p1->bandType;
            else if (p1->bandType < ReportSummary)
                v1 = QString(QString::number(p1->bandNo) + QString::number(p1->bandType)).toInt();
            else
                v1 = p1->bandType * 100;

            if (p2->bandType < MasterHeader)
                v2 = p2->bandType;
            else if (p2->bandType < ReportSummary)
                v2 = QString(QString::number(p2->bandNo) + QString::number(p2->bandType)).toInt();
            else
                v2 = p2->bandType * 100;

            return v1 < v2;

        });

    for (auto &band : allReportBand) {
        if (band == rep)
            continue;

        band->setPos( QPointF(left_, top_) );
        band->setWidth( width_ );
        top_ += band->getHeight()+15;
    }
}

bool RepScrollArea::eventFilter(QObject *obj, QEvent *e)
{
    if (obj==ui->horRuler && e->type()==QEvent::Paint) {
        paintHorRuler();
        return true;
    }
    if (obj==ui->verRuler && e->type()==QEvent::Paint) {
        paintVerRuler();        
        return true;
    }

    return QWidget::eventFilter(obj,e);
}

QList<ReportBand*> RepScrollArea::getReportBands()
{
    QList<ReportBand*> allReportBand;
    for (const auto &item : scene->items())
        if (item->type() == ItemType::GBand)
            allReportBand << qgraphicsitem_cast<ReportBand*>(item);

    return allReportBand;
}

RepScrollArea::~RepScrollArea()
{
    delete ui;
}
