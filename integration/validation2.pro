QT       += core gui sql printsupport
QT += network multimedia
QT       +=serialport

QT += core gui charts
QT += core gui network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    carte.cpp \
    client.cpp \
    commandes.cpp \
    connexion.cpp \
    contrat.cpp \
    employee.cpp \
    fournisseur.cpp \
    historique.cpp \
    livraison.cpp \
    main.cpp \
    mainwindow.cpp \
    notification.cpp \
    notification1.cpp \
    produit.cpp \
    promotion.cpp \
    publicite.cpp \
    scenario1.cpp \
    smtp.cpp \
    stati.cpp

HEADERS += \
    arduino.h \
    carte.h \
    client.h \
    commandes.h \
    connexion.h \
    contrat.h \
    employee.h \
    fournisseur.h \
    historique.h \
    livraison.h \
    mainwindow.h \
    notification.h \
    notification1.h \
    produit.h \
    promotion.h \
    publicite.h \
    scenario1.h \
    smtp.h \
    stati.h

FORMS += \
    mainwindow.ui \
    stati.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




#linguist
TRANSLATIONS += validation2_en.ts

DISTFILES += \
    1497553283-108_84845.png \
    1497553309-101_84843.png \
    Rihanna - Umbrella (LESSI Remix) (Bass Boosted) - YouTube.mkv \
    Rihanna - Where Have You Been (SENSE Remix) (Bass Boosted) - YouTube.mkv \
    YouTube_logo_(2013-2015).png \
    fdaffiche.jpg \
    instagram.png \
    validation2_en.qm \
    validation2_en.ts
