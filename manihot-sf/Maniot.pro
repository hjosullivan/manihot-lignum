TEMPLATE = subdirs
SUBDIRS =  ManiotSubdirs.pro  ManiotMain.pro 

unix{
   system(../LEngine/bin/l2c BL1.L BL1.cpp){
     SOURCES += BL1.cpp
   }
   else{
     message("unix Compiling BL1.L  failed, l2c does not yet exist")
     message("Type make, l2c will be generated from ManiotMain.pro")
   }
   system(../LEngine/bin/l2c BL2.L BL2.cpp){
     SOURCES += BL2.cpp
   }
   else{
     message("unix Compiling BL2.L  failed, l2c does not yet exist")
     message("Type make, l2c will be generated from ManiotMain.pro")
   }
   system(../LEngine/bin/l2c maniot.L maniot.cpp){
     SOURCES += maniot.cpp
   }
   else{
      message("unix Compiling maniot.L failed, l2c does not yet exist")
      message("Type make, l2c will be generated from ManiotMain.pro")
   }
}
win32{
   system(..\LEngine\bin\l2c BL1.L BL1.cpp){
     SOURCES += BL1.cpp
   }
   else{
     message("win32 Compiling BL1.L  failed, l2c does not yet exist")
     message("Type make, l2c will be generated from ManiotMain.pro")
   }
   system(..\LEngine\bin\l2c BL2.L BL2.cpp){
     SOURCES += BL2.cpp
   }
   else{
     message("win32 Compiling BL2.L  failed, l2c does not yet exist")
     message("Type make, l2c will be generated from ManiotMain.pro")
   }
   system(..\LEngine\bin\l2c maniot.L maniot.cpp){
     SOURCES += maniot.cpp
   }
   else{
      message("win32 Compiling maniot.L failed, l2c does not yet exist")
      message("Type make, l2c will be generated from ManiotMain.pro")
   }
}

