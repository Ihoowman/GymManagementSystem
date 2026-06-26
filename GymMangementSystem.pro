QT += core gui
QT += network
QT += charts
#INCLUDEPATH += D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/emailaddress.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimeattachment.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimebase64encoder.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimebase64formatter.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimebytearrayattachment.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimecontentencoder.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimecontentformatter.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimefile.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimehtml.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimeinlinefile.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimemessage.cpp \
#   D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimemultipart.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimepart.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimeqpencoder.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimeqpformatter.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimetext.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/quotedprintable.cpp \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/smtpclient.cpp \
    clientseditdialog.cpp \
    contactusdialog.cpp \
    editmemberdialog.cpp \
    fakedialog.cpp \
    main.cpp \
    mainwindow.cpp \
    membermaindialog.cpp \
    memberpage.cpp \
    otpdialog.cpp \
    logindialog.cpp \
    receptionistdialog.cpp \
    receptionistpagedialog.cpp \
    renewmembershipdialog.cpp \
    sgnupdonedialog.cpp \
    signupdialog.cpp \
    trainerdialog.cpp \
    trainerdialog2.cpp \
    trainerpagedialog.cpp \
    welcomedialog.cpp \
    welcomereceptionistdialog.cpp \
    welcometrainerdialog.cpp

HEADERS += \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/emailaddress.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimeattachment.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimebase64encoder.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimebase64formatter.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimebytearrayattachment.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimecontentencoder.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimecontentformatter.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimefile.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimehtml.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimeinlinefile.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimemessage.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimemultipart.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimepart.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimeqpencoder.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimeqpformatter.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/mimetext.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/quotedprintable.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/smtpclient.h \
#    D:/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/smtpmime_global.h \
    AuthManager.h \
    GymController.h \
    Member.h \
    Person.h \
    clientseditdialog.h \
    contactusdialog.h \
    copylabel.h \
    editmemberdialog.h \
    fakedialog.h \
    logindialog.h \
    mainwindow.h \
    membermaindialog.h \
    memberpage.h \
    membership.h \
    otpdialog.h \
    receptionistdialog.h \
    receptionistpagedialog.h \
    renewmembershipdialog.h \
    sgnupdonedialog.h \
    signupdialog.h \
    trainerdialog.h \
    trainerdialog2.h \
    trainerpagedialog.h \
    welcomedialog.h \
    welcomereceptionistdialog.h \
    person.h \
    member.h \
    authmanager.h \
    gymcontroller.h \
    welcometrainerdialog.h
FORMS += \
    clientseditdialog.ui \
    contactusdialog.ui \
    editmemberdialog.ui \
    fakedialog.ui \
    mainwindow.ui \
    membermaindialog.ui \
    memberpage.ui \
    otpdialog.ui \
    logindialog.ui \
    receptionistdialog.ui \
    receptionistpagedialog.ui \
    renewmembershipdialog.ui \
    sgnupdonedialog.ui \
    signupdialog.ui \
    trainerdialog.ui \
    trainerdialog2.ui \
    trainerpagedialog.ui \
    welcomedialog.ui \
    welcomereceptionistdialog.ui \
    welcometrainerdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    files.qrc
