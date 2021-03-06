TEMPLATE = app
FORMS = func_edit.ui qt_wb.ui viz_config.ui xml_viewer.ui console_window.ui help.ui
TARGET = LignumWb 
# Input
HEADERS += LGMPolygonTree.h GLDrawer.h BSPPolygon.h BSPTree.h SceneObject.h BSPPolygonMaterial.h VisualizationParameters.h LignumWB.h VisualizationConfig.h GenericCfTree.h GenericHwTree.h FunctionEditor.h FunctionPainter.h XMLViewer.h XMLViewerWindow.h XMLViewerWidget.h BSPLoaderThread.h ConsoleWindow.h ConsoleWidget.h LGMPolygonDomBuilder.h HelpDialog.h
SOURCES += GLDrawer.cpp main.cpp BSPPolygon.cpp BSPTree.cpp SceneObject.cpp BSPPolygonMaterial.cpp VisualizationParameters.cpp LignumWB.cpp VisualizationConfig.cpp FunctionEditor.cpp FunctionPainter.cpp XMLViewer.cpp XMLViewerWindow.cpp XMLViewerWidget.cpp BSPLoaderThread.cpp ConsoleWindow.cpp ConsoleWidget.cpp LGMPolygonDomBuilder.cpp HelpDialog.cpp

#../SugarMaple/src/SugarMapleSegmentMetabolism.cc

INCLUDEPATH += . ../stl-lignum/include ../c++adt/include ../Firmament/include ../XMLTree ../LEngine/include /usr/include/GL
#This path musst be set to begin with the QtSDK installation directory on Windows 
win32: INCLUDEPATH += C:\prog\QtSDK\mingw\include\GL
DEPENDPATH = $$INCLUDEPATH

RESOURCES = resources.qrc
CONFIG += qt warn_off no-exceptions 
QT += opengl xml  
macx: RC_FILE = LignumWb.icns
LIBS	+= -framework OpenGL -L../c++adt/lib -L../stl-lignum/lib -L../Firmament/lib -L../LEngine/lib -lL -lsky -lLGM  -lcxxadt 
#This path must be set to begin with the QtSDK installation directory on Windows
win32: LIBS += -LC:\prog\QtSDK\mingw\lib -lglu32
