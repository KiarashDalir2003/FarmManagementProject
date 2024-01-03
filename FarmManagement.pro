QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    barlay.cpp \
    captcha.cpp \
    cow.cpp \
    gamepage.cpp \
    hen.cpp \
    main.cpp \
    loginpage.cpp \
    rankingpage.cpp \
    sheep.cpp \
    wheat.cpp

HEADERS += \
    barlay.h \
    captcha.h \
    cow.h \
    gamepage.h \
    hen.h \
    loginpage.h \
    rankingpage.h \
    sheep.h \
    wheat.h

FORMS += \
    gamepage.ui \
    loginpage.ui \
    rankingpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
