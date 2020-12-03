QT       += core gui sql network
QT += printsupport
CONFIG += console
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connexion.cpp \
    emailaddress.cpp \
    enseigniant.cpp \
    livraison.cpp \
    main.cpp \
    mainwindow.cpp \
    mimeattachment.cpp \
    mimecontentformatter.cpp \
    mimefile.cpp \
    mimehtml.cpp \
    mimeinlinefile.cpp \
    mimemessage.cpp \
    mimemultipart.cpp \
    mimepart.cpp \
    mimetext.cpp \
    produit.cpp \
    quotedprintable.cpp \
    smtpclient.cpp \
    stati.cpp

HEADERS += \
    SmtpMime \
    connexion.h \
    emailaddress.h \
    enseigniant.h \
    livraison.h \
    mainwindow.h \
    mimeattachment.h \
    mimecontentformatter.h \
    mimefile.h \
    mimehtml.h \
    mimeinlinefile.h \
    mimemessage.h \
    mimemultipart.h \
    mimepart.h \
    mimetext.h \
    produit.h \
    quotedprintable.h \
    smtpclient.h \
    smtpexports.h \
    stati.h

FORMS += \
    mainwindow.ui \
    stati.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
