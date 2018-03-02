QT       += gui xml script sql charts

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets printsupport
    DEFINES += HAVE_QT5
}


#DEFINES += QTRPT_LIBRARY    #Un-remark this line, if you want to build QtRPT as a library
#DEFINES += NO_BARCODE       #Un-remark this line, if you want to build QtRPT without BARCODE support
#DEFINES += QXLSX_LIBRARY    #Remark this line, if you want to build QtRPT without XLSX support

include(../CommonFiles/CommonFiles_QtRpt.pri)

INCLUDEPATH += $$PWD

SOURCES += $$PWD/qtrpt.cpp \
           $$PWD/RptSql.cpp \
           $$PWD/RptFieldObject.cpp \
           $$PWD/RptBandObject.cpp \
           $$PWD/RptPageObject.cpp \
           $$PWD/RptCrossTabObject.cpp
HEADERS += $$PWD/qtrpt.h \
           $$PWD/qtrptnamespace.h \
           $$PWD/RptSql.h \
           $$PWD/RptFieldObject.h \
           $$PWD/RptBandObject.h \
           $$PWD/RptPageObject.h \
           $$PWD/RptCrossTabObject.h

RESOURCES += \
    $$PWD/../QtRPT/imagesRpt.qrc
