#-------------------------------------------------
#
# Project created by QtCreator 2014-06-18T19:58:57
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

QMAKE_CXXFLAGS += -Wno-deprecated

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisualGPSqt
TEMPLATE = app
# Windows Icon
RC_FILE = VisualGPSQt.rc
# Mac Icon
ICON = Resources/icon.icns

SOURCES += main.cpp\
        MainWindow.cpp \
    NMEAParserQt.cpp \
    ConnectDlg.cpp \
    AboutDlg.cpp \
    GPSStatusWnd.cpp \
    SignalQuality.cpp \
    AzimuthElevationWnd.cpp \
    PositionStatusWnd.cpp \
    LEDWnd.cpp \
    ../../NMEAParser/Software/NMEAParserLib/NMEAParser.cpp \
    ../../NMEAParser/Software/NMEAParserLib/NMEAParserPacket.cpp \
    ../../NMEAParser/Software/NMEAParserLib/NMEASentenceBase.cpp \
    ../../NMEAParser/Software/NMEAParserLib/NMEASentenceGGA.cpp \
    ../../NMEAParser/Software/NMEAParserLib/NMEASentenceGSA.cpp \
    ../../NMEAParser/Software/NMEAParserLib/NMEASentenceGSV.cpp \
    ../../NMEAParser/Software/NMEAParserLib/NMEASentenceRMC.cpp

HEADERS  += MainWindow.h \
    NMEAParserQt.h \
    ConnectDlg.h \
    AboutDlg.h \
    GPSStatusWnd.h \
    SignalQuality.h \
    AzimuthElevationWnd.h \
    PositionStatusWnd.h \
    LEDWnd.h \
    ../../NMEAParser/Software/NMEAParserLib/NMEAParser.h \
    ../../NMEAParser/Software/NMEAParserLib/NMEAParserData.h \
    ../../NMEAParser/Software/NMEAParserLib/NMEAParserPacket.h \
    ../../NMEAParser/Software/NMEAParserLib/NMEASentenceBase.h \
    ../../NMEAParser/Software/NMEAParserLib/NMEASentenceGGA.h \
    ../../NMEAParser/Software/NMEAParserLib/NMEASentenceGSA.h \
    ../../NMEAParser/Software/NMEAParserLib/NMEASentenceGSV.h \
    ../../NMEAParser/Software/NMEAParserLib/NMEASentenceRMC.h

INCLUDEPATH += ../../NMEAParser/Software/NMEAParserLib

FORMS    += MainWindow.ui \
    ConnectDlg.ui \
    AboutDlg.ui

RESOURCES += \
    Images.qrc
