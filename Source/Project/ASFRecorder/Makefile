
# ASFRecorder Makefile for compilation with GCC 2.95.2 on Cygwin32

# This Makefile is for the Windows platform ONLY!
# For compilation on other platforms, see the header of the
# asfrecorder.c source file.

# You will need the Win32 headers/libraries for compilation!
# See the README.TXT for details on how to obtain these.

# This compiles both the GUI-Version and the console version.

all:     GUI console
GUI:     ASFRecorder.exe
console: ASFRecorder_Console.exe


# the GCC 2.95.2 that comes with the latest CygWin B20.1 release
# doesn't automaticly use the mingw includes when the -mno-cygwin
# flag is specified. So this has to be excplicitly defined here.

include=-I /include/mingw

srcdir=source
guidir=source/wingui
define=-D NDEBUG -D _WINDOWS -D _MBCS


### build ASFRecorder shell and GUI version ###

all: ASFRecorder_Console.exe ASFRecorder.exe


### Create distribution package ###

distrib:
	rm ../ASFRecorder.zip ; cd .. ; zip -9 ASFRecorder.zip ASFRecorder/README.TXT ASFRecorder/ASFRecorder.exe ASFRecorder/ASFRecorder_Console.exe ASFRecorder/Makefile ASFRecorder/NMAKEFILE ASFRecorder/source/asfrecorder.c ASFRecorder/source/wingui/CmdLine.c ASFRecorder/source/wingui/CmdLine.h ASFRecorder/source/wingui/global.h ASFRecorder/source/wingui/msimg32.h ASFRecorder/source/wingui/resource.h ASFRecorder/source/wingui/wingui.c ASFRecorder/source/wingui/wingui.rc ASFRecorder/source/wingui/wingui.ico ASFRecorder/source/wingui/inactive.bmp ASFRecorder/source/wingui/pressed.bmp ASFRecorder/source/wingui/notpressed.bmp  ASFRecorder/source/wingui/asfrecorder.bmp ASFRecorder/source/wingui/directshow_headers/* ASFRecorder/source/wingui/directshow_libs/*


### Cleanup ###

clean:
	rm *.plg *.pdb *.ilk Debug/* Release/* $(srcdir)/asfrecorder.obj $(guidir)/CmdLine.obj $(guidir)/wingui.obj $(guidir)/wingui.res ; rm -R Debug Release $(srcdir)/Debug $(srcdir)/Release $(guidir)/Debug $(guidir)/Release


### Console version (networking module only) ###

ASFRecorder_Console.exe: $(srcdir)/asfrecorder.c

	gcc -mno-cygwin -Wl,-s source/asfrecorder.c -o ASFRecorder_Console.exe -lws2_32


### Networking module (with GUI flag defined) ###

$(srcdir)/asfrecorder.obj: $(srcdir)/asfrecorder.c

	gcc -mno-cygwin $(include) $(define) -D GUI -c -o $(srcdir)/asfrecorder.obj $(srcdir)/asfrecorder.c


### CommandLine and main code for GUI ###

$(guidir)/CmdLine.obj: $(guidir)/CmdLine.c $(guidir)/CmdLine.h

	gcc -mno-cygwin $(include) $(define) -c -o $(guidir)/CmdLine.obj $(guidir)/CmdLine.c

$(guidir)/wingui.obj: $(guidir)/wingui.c $(guidir)/global.h $(guidir)/resource.h

	gcc -mno-cygwin $(include) $(define) -c -o $(guidir)/wingui.obj $(guidir)/wingui.c -I $(guidir)/directshow_headers


### GUI resources ###

$(guidir)/wingui.res: $(guidir)/wingui.rc $(guidir)/resource.h

	windres --include-dir $(guidir) $(guidir)/wingui.rc $(guidir)/wingui.res --output-format coff --target pe-i386


### Linkage ###

ASFRecorder.exe: $(srcdir)/asfrecorder.obj $(guidir)/CmdLine.obj $(guidir)/wingui.obj $(guidir)/wingui.res

	gcc -mno-cygwin -mwindows -Wl,-e,_WinMainCRTStartup -Wl,-s $(srcdir)/asfrecorder.obj $(guidir)/CmdLine.obj $(guidir)/wingui.obj $(guidir)/wingui.res -o ASFRecorder.exe -ladvapi32 -lversion -llargeint -luser32 -lgdi32 -lcomctl32 -lcomdlg32 -lshell32 -lole32 -loleaut32 -lws2_32 -L $(guidir)/directshow_libs -lstrmbase -lquartz
