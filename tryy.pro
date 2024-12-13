QT       += core gui
QT+=sql
QT += charts
QT +=serialport
#QT += core gui widgets charts

#INCLUDEPATH += C:/Users/SBS/Downloads/SmtpClient-for-Qt/src
#SOURCES += C:/Users/SBS/Downloads/SmtpClient-for-Qt/src/SmtpMime

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    connexion.cpp \
    employes.cpp \
    main.cpp \
    mainwindow.cpp
    C:/Users/SBS/Downloads/SmtpClient-for-Qt/src/SmtpMime.QMAKE_EXT_CPP

HEADERS += \
    arduino.h \
    connexion.h \
    employes.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Downloads/SmtpClient-for-Qt/build-SMTPEmail-Desktop_Qt_6_3_0_MinGW_64_bit-Debug/release/ -lSmtpMime2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Downloads/SmtpClient-for-Qt/build-SMTPEmail-Desktop_Qt_6_3_0_MinGW_64_bit-Debug/debug/ -lSmtpMime2

INCLUDEPATH += $$PWD/../../Downloads/SmtpClient-for-Qt/src
DEPENDPATH += $$PWD/../../Downloads/SmtpClient-for-Qt/src

DISTFILES += \
    ../../Downloads/image-removebg-preview (5).png \
    script.py \
    script2.py \
    script3.py
