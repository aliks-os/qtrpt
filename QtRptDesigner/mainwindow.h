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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#if QT_VERSION >= 0x50000
    #include <QtWidgets>
#else
    #include <QtGui>
#endif
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDomDocument>
#include <QAction>
#include "aboutDlg.h"
#include "RepScrollArea.h"
#include "SettingDlg.h"
#include <XYZ_DownloadManager.h>
#include "SqlDesigner.h"
#include "GraphicsBox.h"
#include <QGraphicsItem>
#include <QPointer>

namespace Ui {
    class MainWindow;
}

class EditorDelegate: public QItemDelegate
{
    Q_OBJECT
public:
    EditorDelegate(QObject *parent);
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const {
        Q_UNUSED(option);
        Q_UNUSED(index);
        return QSize(50,20);
    }
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

protected:
    void paint( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

private slots:
    void commitAndCloseEditor();
    void editorClose_(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);

signals:
    void editorClose(QItemDelegate *item);
    void btnClicked();
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    friend class GraphicsScene;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static MainWindow* instance() {
        return mw;
    }

    void setReportChanged();

protected:
    bool eventFilter(QObject *obj, QEvent *e);
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    static MainWindow* mw;
    QListWidget *listFrameStyle;
    QSharedPointer<QDomDocument> xmlDoc;
    QTreeWidgetItem *rootItem;
    QList<QGraphicsItem*> *cloneContList;
    QFontComboBox *cbFontName;
    QComboBox *cbZoom;
    QComboBox *cbFontSize;
    QComboBox *cbFrameWidth;
    bool pasteCopy;
    QIcon icon;
    QString fileName;
    QMenu *contMenu;
    QMenu *bandMenu;
    QLabel *m_status1;
    QLabel *m_status2;
    QLabel *m_status3;

    QAction *actRepTitle;
    QAction *actReportSummary;
    QAction *actPageHeader;
    QAction *actPageFooter;
    QAction *actMasterData;
    QAction *actMasterFooter;
    QAction *actMasterHeader;
    QAction *separatorAct;
    QAction *actDataGroupingHeader;
    QAction *actDataGroupingFooter;

    SqlDesigner *sqlDesigner;

    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];

    QGraphicsItem *selectedGItem();
    GraphicsHelperClass *gItemToHelper(QGraphicsItem *item);
    bool setXMLProperty(QDomElement *repElem, void *ptr, int type);
    void selectItemInTree(QTreeWidgetItem *item);
    void showParamState();
    Command getCommand(QObject *obj);
    void execButtonCommand(Command command, QVariant value);
    void processCommand(Command command, QVariant value, QGraphicsItem *item);
    QTreeWidgetItem *findItemInTree(Command command);

    void setParamTree(Command command, QVariant value = 0, bool child = false);
    void updateRecentFileActions();
    void setCurrentFile(const QString &fileName);
    QDomElement getDataSourceElement(QDomNode n);
    void enableAdding();
    QGraphicsItemList getSelectedItems();
    GraphicsHelperList getSelectedHelperItems();

    QList<QObject*> plugins;
    bool loadPlugin();

private slots:
    void showAbout();
    void openFile();
    void newReport();
    void saveReport();
    void showPageSetting();
    void clickOnTBtn();
    void addBand();
    void addField(FieldType type);
    void addDraw();
    void setSelectionMode();
    void sceneItemSelectionChanged(QGraphicsItem *item);
    void selTree(QTreeWidgetItem *tItem, int);
    void itemChanged(QTreeWidgetItem *item, int column);
    void closeEditor();
    void changeTextFont();
    void setGroupingField();
    void clipBoard();
    void chooseColor();
    void showFrameStyle(QPoint pos);
    void setFrameStyle(QListWidgetItem * item);
    void changeFrameWidth();
    void itemResizing(QGraphicsItem *item);
    void reportPageChanged(int index);
    void newReportPage();
    void deleteReportPage();
    void alignFields();
    void openRecentFile();
    void closeProgram();
    void showSetting();
    void changeZoom();
    void openDBGroupProperty();
    void checkUpdates();
    void showPreview();
    void showDataSource();
    void undo();
    void redo();
    void mousePos(QPointF pos);
    void sceneClick();
    void sceneItemAdded(QGraphicsItem *mItem);
    void generateName(QGraphicsItem *mItem);
};

#endif // MAINWINDOW_H
