#include <QApplication>
#include <QUuid>
#include <QStringList>
#include <qtrpt.h>
#include <QDebug>
#include <iostream>

using namespace std;

/*
argv 1 - file name of the xml file
argv 2 - sql query string if data takes from DB
*/
int main(int argc, char *argv[]) {
    QUuid uid = QUuid::createUuid();
    QString uidStr = uid.toString();
    QApplication a(argc, argv, false);
    QStringList args = a.arguments();
    if (args.count() < 1) {
       std::cerr << "first argument required" << endl;
       return 1;
    }

    QString fileName = args[1];
    QtRPT *report = new QtRPT(0);
    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report's file not found";
    }

    if (args.count() > 1) {
        QString sqlQuery = args[2];
        report->setSqlQuery(sqlQuery);
    }

    report->printPDF(uidStr,false);
    delete report;

    FILE *in;
    if ((in = fopen(uidStr.toStdString().c_str(),"rt")) == NULL) {
        std::cout << "file not open";
    }
    while (!feof(in))
        putc(fgetc(in), stdout);
    fclose(in);
    remove(uidStr.toStdString().c_str());

    a.exit();
}

