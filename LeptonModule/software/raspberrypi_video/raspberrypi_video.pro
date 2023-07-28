CONFIG += link_pkgconfig
PKGCONFIG += opencv4

TEMPLATE = app
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = raspberrypi_video

RPI_LIBS = ../raspberrypi_libs
LEPTONSDK = leptonSDKEmb32PUB

PRE_TARGETDEPS += sdk
QMAKE_EXTRA_TARGETS += sdk sdkclean
sdk.commands = make -C $${RPI_LIBS}/$${LEPTONSDK}
sdkclean.commands = make -C $${RPI_LIBS}/$${LEPTONSDK} clean

DEPENDPATH += .
CONFIG += link_pkgconfig
PKGCONFIG += opencv4

DESTDIR=.
OBJECTS_DIR=gen_objs
MOC_DIR=gen_mocs

HEADERS += *.h

SOURCES += *.cpp

# Add the ROS include directory to the INCLUDEPATH variable
unix: INCLUDEPATH += /opt/ros/noetic/include

# Set LD_LIBRARY_PATH in QMAKE_LFLAGS
unix: QMAKE_LFLAGS += -Wl,-rpath,/opt/ros/noetic/lib

unix: LIBS += -L$${RPI_LIBS}/$${LEPTONSDK}/Debug -lLEPTON_SDK -L/opt/ros/noetic/lib -lroscpp -lrosconsole -lroscpp_serialization -lrostime -lpthread -lopencv_core -lopencv_imgproc -lopencv_highgui -lcv_bridge

unix:QMAKE_CLEAN += -r $(OBJECTS_DIR) $${MOC_DIR}

