QT += widgets

HEADERS = code/sound.h code/window.h

SOURCES = code/qSound.cpp code/sound.cpp code/window.cpp 

LIBS += -lfmod -lfmodL

OBJECTS_DIR = tmp
MOC_DIR = tmp

#install
target.path = ./code
INSTALLS += target
