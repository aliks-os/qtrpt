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

#include "GraphicsScene.h"
#include <QApplication>
#include <QSettings>
#include "mainwindow.h"
#include <QDebug>

GraphicsScene::GraphicsScene(QObject *parent)
: QGraphicsScene(parent)
{
    sceneMode = SelectObject;
    m_trackingMoves = false;

    //m_backgroundItem = 0;
    m_undoStack = new QUndoStack(this);
}

//void GraphicsScene::setBackground(QString path) {
//    if (m_backgroundItem != 0 ) {
//        this->removeItem(m_backgroundItem);
//        m_backgroundItem = 0;
//    }

//    m_backgroundItem = new QGraphicsPixmapItem();
//    this->addItem(m_backgroundItem);
//    m_backgroundPath = path;
//    QPixmap pixmap(path);
//    m_backgroundItem->setPixmap(pixmap);
//}

void GraphicsScene::addItem(QGraphicsItem *item)
{
    auto helper = dynamic_cast<GraphicsHelperClass*>(item);
    QObject::connect(helper, SIGNAL(itemRemoving()), this, SLOT(itemRemoving()));

    QGraphicsScene::addItem(item);
}

void GraphicsScene::setMode(Mode mode)
{
    sceneMode = mode;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sceneClick();
    m_movedItems.clear();
    m_trackingMoves = true;

    auto pItem = itemAt(event->scenePos(), this->views().at(0)->transform() );
    if (pItem == nullptr)
        return;
    if (pItem->type() == ItemType::GBox)
        pItem = pItem->parentItem();

    QPointF origPoint = pItem->mapFromScene(event->scenePos());

    if (sceneMode == Mode::DrawLine) {
        QPointF startPoint(0,0);
        auto newLine = new GraphicsLine();
        newLine->setFieldType(m_newFieldType);
        newLine->setArrow(QtRptName::ArrowStart, newLineArrowStart);
        newLine->setArrow(QtRptName::ArrowEnd, newLineArrowEnd);
        newLine->setPos(startPoint);
        newLine->addPoint(origPoint);
        newLine->addPoint(origPoint);
        //addItem(newLine);
        //newLine->setParentItem(pItem);
        //band->newFieldTreeItem(newLine);
        m_undoStack->push(new AddCommand(newLine, this, pItem));
        newLine->setSelected(true);
        emit itemAdded(newLine);
        emit sceneModeChanged(newLine, Mode::SelectObject);
        setMode(Mode::SelectObject);
        m_trackingMoves = false;
    }
    if(sceneMode == DrawContainer) {
        auto graphicsBox = new GraphicsBox();
        graphicsBox->setFieldType(m_newFieldType);
        graphicsBox->setPos(origPoint);
        graphicsBox->setMenu(m_newFieldMenu);
        //addItem(graphicsBox);
        //graphicsBox->setParentItem(pItem);
        //band->newFieldTreeItem(graphicsBox);
        m_undoStack->push(new AddCommand(graphicsBox, this, pItem));
        graphicsBox->setSelected(true);
        emit itemAdded(graphicsBox);
        emit sceneModeChanged(graphicsBox, Mode::SelectObject);
        setMode(Mode::SelectObject);
        m_trackingMoves = false;
    }

    //Added to prevent lost focus on right click on the item
    if (event->button() != Qt::LeftButton) {
        event->accept();
        return;
    }

    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit mousePos(event->scenePos());
    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setMode(Mode::SelectObject);
    QApplication::restoreOverrideCursor();

    if (sceneMode == Mode::SelectObject && QApplication::keyboardModifiers() != Qt::ControlModifier) {
        if (!itemAt(event->scenePos(), this->views().at(0)->transform())) {
            this->clearSelection();
            emit itemSelected(0);
            return;
        }
    }

    for (auto &itm : m_movedItems) {
        if (itm.item->type() == ItemType::GBox) {
            auto box = static_cast<GraphicsBox*>(itm.item);
            itm.newHeight = box->getHeight();
            itm.newWidth = box->getWidth();
            itm.newPos = box->pos();
            m_undoStack->push(new MoveGItemCommand(itm));
        }
        if (itm.item->type() == ItemType::GLine) {
            auto line = static_cast<GraphicsLine*>(itm.item);
            itm.newPointList = line->getPointList();
            itm.newPos = line->pos();
            m_undoStack->push(new MoveLineCommand(itm));
        }
    }

    QGraphicsScene::mouseReleaseEvent(event);
    m_trackingMoves = false;
}

void GraphicsScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        m_undoStack->push(new DelItemCommand(this));
        update();
        return;
    }

    for (auto &item : this->items()) {
        bool isSelected = false;
        GraphicsBox *box = nullptr;
        if (item->type() == ItemType::GBox || item->type() == ItemType::GBand) {
            box = static_cast<GraphicsBox*>(item);
            isSelected = box->isSelected();
        }
        GraphicsLine *line = nullptr;
        if (item->type() == ItemType::GLine) {
            line = static_cast<GraphicsLine*>(item);
            isSelected = line->isSelected();
        }

        if (item->type() == ItemType::GBox || item->type() == ItemType::GLine || item->type() == ItemType::GBand) {
            if (isSelected) {
                if(event->key() == Qt::Key_Left && item->type() != ItemType::GBand) {
                    if (QApplication::keyboardModifiers() == Qt::ControlModifier) {
                        if (box != nullptr)
                            box->setPos(box->pos().x()-1, box->pos().y());
                        if (line != nullptr)
                            line->setPos(line->pos().x()-1, line->pos().y());
                    }
                    if (QApplication::keyboardModifiers() == Qt::ShiftModifier) {
                        if (box != nullptr)
                            box->setWidth(box->getWidth()-1);
                        if (line != nullptr)
                            line->setLength(line->getLength()-1);
                    }
                }
                if(event->key() == Qt::Key_Up) {
                    if (QApplication::keyboardModifiers() == Qt::ControlModifier && item->type() != ItemType::GBand) {
                        if (box != nullptr)
                            box->setPos(box->pos().x(), box->pos().y()-1);
                        if (line != nullptr)
                            line->setPos(line->pos().x(), line->pos().y()-1);
                    }
                    if (QApplication::keyboardModifiers() == Qt::ShiftModifier) {
                        if (box != nullptr)
                            box->setHeight(box->getHeight()-1);
                    }
                }
                if(event->key() == Qt::Key_Right && item->type() != ItemType::GBand) {
                    if (QApplication::keyboardModifiers() == Qt::ControlModifier) {
                        if (box != nullptr)
                            box->setPos(box->pos().x()+1, box->pos().y());
                        if (line != nullptr)
                            line->setPos(line->pos().x()+1, line->pos().y());
                    }
                    if (QApplication::keyboardModifiers() == Qt::ShiftModifier) {
                        if (box != nullptr)
                            box->setWidth(box->getWidth()+1);
                        if (line != nullptr)
                            line->setLength(line->getLength()+1);
                    }
                }
                if(event->key() == Qt::Key_Down) {
                    if (QApplication::keyboardModifiers() == Qt::ControlModifier && item->type() != ItemType::GBand) {
                        if (box != nullptr)
                            box->setPos(box->pos().x(), box->pos().y()+1);
                        if (line != nullptr)
                            line->setPos(line->pos().x(), line->pos().y()+1);
                    }
                    if (QApplication::keyboardModifiers() == Qt::ShiftModifier) {
                        if (box != nullptr)
                            box->setHeight(box->getHeight()+1);
                    }
                }
            }
        }

        if (isSelected
            && (QApplication::keyboardModifiers() == Qt::ControlModifier || QApplication::keyboardModifiers() == Qt::ShiftModifier)
            && (event->key() == Qt::Key_Left || event->key() == Qt::Key_Up || event->key() == Qt::Key_Right || event->key() == Qt::Key_Down))
        {
            emit itemResized(item);
            auto mw = MainWindow::instance();
            mw->setReportChanged();
        }
    }
}

void GraphicsScene::itemRemoving()
{
    //Из поп-апа
    //GraphicsHelperClass *helper = qobject_cast<GraphicsHelperClass*>(sender());
    //QGraphicsItem *item = static_cast<QGraphicsItem*>(helper->graphicsItem);
    //removeItem(item);
    m_undoStack->push(new DelItemCommand(this));
    update();
}

void GraphicsScene::removeItem(QGraphicsItem* item)
{
    auto helper = dynamic_cast<GraphicsHelperClass*>(item);
    if (helper == nullptr)
        return;

    if (helper->itemInTree != nullptr) {
        auto mw = MainWindow::instance();
        auto treeWidget = mw->findChild<QTreeWidget*>("treeWidget");
        auto actSaveReport = mw->findChild<QAction*>("actSaveReport");

        auto treeItem = helper->itemInTree;

        auto itemAbove = treeWidget->itemAbove(treeItem);
        if (itemAbove == nullptr)
            return;

        auto parent = treeItem->parent();
        while (treeItem->childCount() > 0) {
            auto tmp = treeItem->takeChild(0);
            tmp = nullptr;
            delete tmp;
        }
        int index = parent->indexOfChild(treeItem);
        delete parent->takeChild(index);

        treeWidget->setCurrentItem(itemAbove);
        actSaveReport->setEnabled(true);

        //Корректируем расположение бэндов
        auto reportBand = qgraphicsitem_cast<ReportBand *>(item);
        if (reportBand == nullptr)
            return;

        auto repPage = qobject_cast<RepScrollArea *>(this->parent());
        repPage->correctBandGeom(reportBand);

        if (reportBand->bandType == ReportTitle) mw->actRepTitle->setEnabled(true);
        if (reportBand->bandType == ReportSummary) mw->actReportSummary->setEnabled(true);
        if (reportBand->bandType == PageHeader) mw->actPageHeader->setEnabled(true);
        if (reportBand->bandType == PageFooter) mw->actPageFooter->setEnabled(true);
        if (reportBand->bandType == MasterData) mw->actMasterData->setEnabled(true);
        if (reportBand->bandType == MasterFooter) mw->actMasterFooter->setEnabled(true);
        if (reportBand->bandType == MasterHeader) mw->actMasterHeader->setEnabled(true);
        if (reportBand->bandType == DataGroupHeader) mw->actDataGroupingHeader->setEnabled(true);
        if (reportBand->bandType == DataGroupFooter) mw->actDataGroupingFooter->setEnabled(true);
    }

    QGraphicsScene::removeItem(item);
}

void GraphicsScene::itemResizing(QGraphicsItem *item)
{
    emit itemResized(item);
}

void GraphicsScene::itemMoving(QGraphicsItem *item)
{
    if (m_trackingMoves) {
        bool founded = false;
        QList<ItemsAndParams>::iterator i;
        for (i = m_movedItems.begin(); i != m_movedItems.end(); ++i)
            if ((*i).item == item)
                founded = true;

        if (!founded) {
            ItemsAndParams param;
            param.item = item;
            param.oldPos = item->pos();
            if (item->type() == ItemType::GBox) {
                GraphicsBox *box = static_cast<GraphicsBox*>(item);
                param.oldHeight = box->getHeight();
                param.oldWidth = box->getWidth();
            }
            if (item->type() == ItemType::GLine) {
                GraphicsLine *line = static_cast<GraphicsLine*>(item);
                param.oldPointList = line->getPointList();
            }
            m_movedItems.append(param);
        }
    }
}

void GraphicsScene::unselectAll()
{
    for (auto item : this->items()) {
        if (item->type() == ItemType::GLine) {
            auto line = static_cast<GraphicsLine*>(item);
            line->setSelected(false);
        } else if (item->type() == ItemType::GBox) {
            auto box = static_cast<GraphicsBox*>(item);
            box->setSelected(false);
        } else if (item->type() == ItemType::GBand) {
            auto box = static_cast<GraphicsBox*>(item);
            box->setSelected(false);
        } else {
            item->setSelected(false);
        }
    }
}

void GraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter,rect);

    if (isShowGrid == false)
        return;

    QColor c(200,200,255,125);
    painter->setPen(c);
    const int gridSize = m_koef*m_gridStep;
    QRectF rectView = this->sceneRect();

    qreal left = rectView.left() + m_leftM;
    qreal top = rectView.top() + m_topM;
    qreal bottom = rectView.height() - m_bottomM;
    qreal right = rectView.width() - m_rightM;

    QVarLengthArray<QLineF, 100> lines;
	painter->drawRect(left, top,
                     rectView.width()-m_rightM-m_leftM,
                     rectView.height()-m_topM-m_bottomM);

    //vertical lines
    for (qreal x = left; x <= right; x += gridSize)
        lines.append(QLineF(x, top, x, bottom));
    //horizontal lines
    for (qreal y = top; y <= bottom; y += gridSize)
        lines.append(QLineF(left, y, right, y));

    painter->drawLines(lines.data(), lines.size());
}
