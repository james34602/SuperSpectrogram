QT       += core gui multimedia widgets
 
TARGET = SuperSpectrogram
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    spectrogram.cpp \
    spectrumanalyser.cpp \
    palette.cpp

HEADERS  += mainwindow.h \
    spectrogram.h \
    spectrumanalyser.h \
    palette.h \
    colormap.h
#DEFINES += TITLEBAR
win32 {
message("* Windows 32 build")
LIBS += ../SuperSpectrogram/libfftw3-3.lib
QMAKE_CXXFLAGS -= -O
QMAKE_CXXFLAGS -= -O1
QMAKE_CXXFLAGS += -O2# -fp:fast
}
android {
message("* Android build")
LIBS += ../SuperSpectrogram/libfftw3.a
QMAKE_CXXFLAGS_RELEASE *= -DNDEBUG -ffunction-sections -fdata-sections -Ofast -ftree-vectorize
}
