QT       += core gui multimedia widgets
 
TARGET = SuperSpectrogram
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    spectrumanalyser.cpp \
    palette.cpp \
    SuperSpectrogram.cpp

HEADERS  += mainwindow.h \
    spectrumanalyser.h \
    palette.h \
    colormap.h \
    SuperSpectrogram.h
DEFINES += TITLEBAR
win32 {
message("* Windows 32 build")
LIBS += ../SuperSpectrogram/libfftw3f-3.lib
QMAKE_CXXFLAGS -= -O
QMAKE_CXXFLAGS -= -O1
QMAKE_CXXFLAGS += -O2# -fp:fast
}
android {
message("* Android build")
LIBS += ../SuperSpectrogram/libfftw3f.a
QMAKE_CXXFLAGS_RELEASE *= -DNDEBUG -ffunction-sections -fdata-sections -Ofast -ftree-vectorize
}
