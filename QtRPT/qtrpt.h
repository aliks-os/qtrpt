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

#ifndef QTRPT_H
#define QTRPT_H

#include <QtCharts>
#include <QPainter>
#include <QDomDocument>
#include <QScriptEngine>
#include <QPrintPreviewWidget>
#include <QTextDocument>
#include <qtrptnamespace.h>
#include <RptFieldObject.h>
#include <RptBandObject.h>
#include <RptPageObject.h>
#include <RptSql.h>

#if QT_VERSION >= 0x50000
    #ifdef QXLSX_LIBRARY
        #include "xlsxdocument.h"
    #endif
#endif

using namespace QtRptName;
using namespace QtCharts;

enum HiType
{
    FntBold,
    FntItalic,
    FntUnderline,
    FntStrikeout,
    FntColor,
    BgColor
};

struct AggregateValues
{
    QString paramName;
    QVariant paramValue;
    int lnNo;
    int pageReport;
};

class Chart;
class RptSql;
class RptPageObject;
class RptBandObject;
class RptFieldObject;
class RptCrossTabObject;

QScriptValue funcAggregate(QScriptContext *context, QScriptEngine *engine);
QScriptValue funcReplace(QScriptContext *context, QScriptEngine *engine);
QScriptValue funcToUpper(QScriptContext *context, QScriptEngine *engine);
QScriptValue funcToLower(QScriptContext *context, QScriptEngine *engine);
QScriptValue funcNumberToWords(QScriptContext *context, QScriptEngine *engine);
QScriptValue funcFrac(QScriptContext *context, QScriptEngine *engine);
QScriptValue funcFloor(QScriptContext *context, QScriptEngine *engine);
QScriptValue funcCeil(QScriptContext *context, QScriptEngine *engine);
QScriptValue funcRound(QScriptContext *context, QScriptEngine *engine);

static QList<AggregateValues> listOfPair;
static QList<int> listIdxOfGroup;

struct DataSetInfo {
   int reportPage;
   int dataSetNo;
   int recordCount;
};
typedef QList<DataSetInfo> DataSetInfoList;



#ifndef QTRPT_LIBRARY
    class QtRPT : public QObject
#else
    #include <qtrpt_global.h>
    class QTRPTSHARED_EXPORT QtRPT : public QObject
#endif

{
    Q_OBJECT

    friend class RptFieldObject;
    friend class RptBandObject;

public:
    using SPtrQtRPT = QSharedPointer<QtRPT>;

    explicit QtRPT(QObject *parent = 0);
    static SPtrQtRPT createSPtr(QObject *parent = 0)
    {
        SPtrQtRPT sptr= SPtrQtRPT(new QtRPT(parent));
        return sptr;
    }

    bool setPainter(QPainter *painter);
    bool setPrinter(QPrinter *printer);
    void setResolution(QPrinter::PrinterMode resolution);
    bool loadReport(QString fileName);
    bool loadReport(QDomDocument xmlDoc);
    void clearObject();
    void printExec(bool maximum = false, bool direct = false, QString printerName = QString());
    //void setCallbackFunc(void (*func)(int &recNo, QString &paramName, QVariant &paramValue));
    void setBackgroundImageOpacity(float opacity);
    void setBackgroundImage(QPixmap &image);
    void setBackgroundImage(QPixmap image);
    void printPDF(const QString &filePath, bool open = true);
    void printHTML(const QString &filePath, bool open = true);
    void printXLSX(const QString &filePath, bool open = true);
    void setSqlQuery(QString sqlString);
    static FieldType getFieldType(QDomElement e);
    static QString getFieldTypeName(FieldType type);
    static QSet<FieldType> getDrawingFields();
    static Qt::PenStyle getPenStyle(QString value);
    QList<RptPageObject*> pageList;    

    ~QtRPT();
    static QString getFormattedValue(QString value, QString formatString);

    void setUserSqlConnection(int pageReport, QString dsName, QString dbType, QString dbName, QString dbHost, QString dbUser, QString dbPassword, int dbPort, QString dbConnectionName, QString sql, QString dbCoding = "UTF8", QString charsetCoding = "UTF8");
    void activateUserSqlConnection(int pageReport, bool bActive);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    QPixmap *m_backgroundImage;
    QPrinter *printer;
    QPainter *painter;
    int m_recNo;
    int mg_recNo;
    int m_pageReport;
    float koefRes_h;
    float koefRes_w;
    int ph;
    int pw;
    int ml;
    int mr;
    int mt;
    int mb;
    int curPage;
    int totalPage;
    int m_orientation;
    float m_backgroundOpacity;
    QPrintPreviewWidget *pr;
    QList<QAction*> lst;
    QDomDocument xmlDoc;
    QDomNode getBand(BandType type, QDomElement docElem);
    void drawBandRow(RptBandObject *band, int bandTop, bool allowDraw = true);
    void fillListOfValue(RptBandObject *bandObject);
    QString sectionField(RptBandObject *band, QString value, bool exp, bool firstPass = false, QString formatString = "");
    QStringList splitValue(QString value);
    QImage sectionFieldImage(QString value);
    QVariant processFunctions(QString value);
    QString sectionValue(QString paramName);
    QImage sectionValueImage(QString paramName);
    void newPage(QPrinter *printer, int &y, bool draw, bool newReportPage = false);
    void processPHeader(int &y, bool draw);
    void processPFooter(bool draw);
    void processMFooter(QPrinter* printer, int &y, int dsNo, bool draw);
    void processRSummary(QPrinter* printer, int &y, bool draw);
    //void (*callbackFunc)(int &recNo, QString &paramName, QVariant &paramValue);
    void processReport(QPrinter *printer, bool draw, int pageReport);
    void processRTitle(int &y, bool draw);
    void processMHeader(int &y, int dsNo, bool draw);
    void processMasterData(QPrinter* printer, int &y, bool draw, int pageReport, int dsNo);
    void processGroupHeader(QPrinter* printer, int &y, bool draw, int pageReport);
    void setPageSettings(QPrinter* printer, int pageReport);
    void drawBackground(bool draw);
    bool isFieldVisible(RptFieldObject* fieldObject);
    QVariant processHighligthing(RptFieldObject* field, HiType type);
    bool allowPrintPage(bool draw, int curPage_);
    bool allowNewPage(bool draw, int curPage_);
    int fromPage;
    int toPage;
    QStringList listOfGroup;
    void setFont(RptFieldObject *fieldObject);
    static Qt::Alignment getAligment(QDomElement e);
    QPen getPen(RptFieldObject *fieldObject);
    void drawFields(RptFieldObject *fieldObject, int bandTop, bool firstPass);
    void drawLines(RptFieldObject *fieldObject, int bandTop);
    void openDataSource(int pageReport);
    int getRecCount(int reportPage, int dsSetNo);
    void setRecCount(int reportPage, int dsSetNo, int recCount);
    void setUserSqlConnection(int pageReport, const RptSqlConnection &sqlConnection);
    void getUserSqlConnection(int pageReport, RptSqlConnection &sqlConnection);

    DataSetInfoList m_dataSetInfoList;

    QString m_sqlQuery;
    QString m_HTML;
    RptCrossTabObject *crossTab;

    #ifdef QXLSX_LIBRARY
        QXlsx::Document *m_xlsx;
    #endif

    void makeReportObjectStructure();
    enum PrintMode
    {
        Printer = 0,
        Pdf     = 1,
        Html    = 2,
        Xlsx    = 3
    };
    PrintMode m_printMode;
    QPrinter::PrinterMode m_resolution;

signals:
    void setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage);
    void setField(RptFieldObject &fieldObject);
    void setValueImage(const int recNo, const QString paramName, QImage &paramValue, const int reportPage);
    void setValueDiagram(Chart &chart);
    void setChart(RptFieldObject &fieldObject, QChart &chart);
    void newPage(int page);
    void setDSInfo(DataSetInfo &dsInfo);

public slots:
    void printPreview(QPrinter *printer);

private slots:
    void exportTo();

};


#ifdef QTRPT_LIBRARY
    extern "C" QTRPTSHARED_EXPORT QtRPT* createQtRPT();
#endif

#endif // QTRPT_H

