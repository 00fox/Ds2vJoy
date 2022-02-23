@echo *** windres 2.16.91 or later is needed, dated August 2005
@echo *** get it from mingw.org/download.shtml
@echo ***

\mingw\bin\windres -o simpleres.o simple.rc
\mingw\bin\c++ -o simple.exe simple.cpp simpleres.o ..\..\zip.cpp ..\..\unzip.cpp -lgdi32
