TEMPLATE = app
CONFIG += console c++11 sdk_no_version_check
CONFIG -= app_bundle

win32 {
    INCLUDEPATH += D:/soft/boost_1_72_0
    LIBS += -LD:/soft/boost_1_72_0/stage/lib \
}
unix:!mac {

}
freebsd {

}
mac {
    INCLUDEPATH += /Users/wujing/Workspaces/apps/boost_1_72_0
    LIBS += -L/Users/wujing/Workspaces/apps/boost_1_72_0/stage/lib \
        -lboost_filesystem -lboost_iostreams \
        -lz \
        -lbz2
}

SOURCES += \
        dictdata.cpp \
        dictentry.cpp \
        dictindex.cpp \
        dictinfo.cpp \
        main.cpp \
        tar.cpp

HEADERS += \
    dictdata.hpp \
    dictentry.hpp \
    dictindex.hpp \
    dictinfo.hpp \
    tar.hpp
