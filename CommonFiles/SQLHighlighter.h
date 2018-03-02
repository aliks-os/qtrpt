// $Id: SQLHighlighter.cpp 20 2006-10-10 08:24:36Z tb $
// Copyright 2006 Timo Bingmann
// Modified 2011 Aleksey Osipov
// SQL syntax highlight plugin for QTextEdit
//

#ifndef _SQLHighlighter_H_
#define _SQLHighlighter_H_

#include <QtCore/QVector>
#include <QtCore/QRegExp>

#include <QtGui/QSyntaxHighlighter>
#include <QtGui/QTextCharFormat>
#include <QSettings>

enum FontHihgligth {Comment=0,
                    QuotedString=1,
                    PrimaryKeyword=2,
                    TypeKeyword=3,
                    ExoticKeywords=4};
Q_DECLARE_FLAGS(FontHihgligths, FontHihgligth)
Q_DECLARE_METATYPE(FontHihgligth)

struct FontHihgligthParam{
    FontHihgligth type;
    QString remark;
    QString color;
    bool bold;
    bool italic;
};
Q_DECLARE_METATYPE(FontHihgligthParam)

class SQLHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
    Q_ENUMS(FontHihgligth)

public:
    SQLHighlighter(class QTextDocument *parent = nullptr, QSettings *settings = 0);
    FontHihgligthParam getFontColor(int type);
    void saveSettings(QSettings *settings);

protected:
    virtual void highlightBlock(const QString &text);

private:
    struct Rule {
        QRegExp 	pattern;
        QTextCharFormat format;
        inline Rule() { }
        inline Rule(QString p, QTextCharFormat f) : pattern(p, Qt::CaseInsensitive), format(f) { }
    };
    void fillArray();

    QVector<Rule> 	rules;
    QRegExp 		commentStartExpression;
    QRegExp 		commentEndExpression;
    QTextCharFormat commentFormat;
    QList<FontHihgligthParam> lst;
};

#endif // _SQLHighlighter_H_
