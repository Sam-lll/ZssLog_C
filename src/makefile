include ../MS_makefile_template

BUILD_DIR = ..\build_win32

"$(BUILD_DIR)" :
	if not exist $@ mkdir $@

# EXES = dllmain.exe
OBJS = ZssLog.obj Util.obj

# SRC_FILE = ZssLog.cpp Util.cpp

all: "$(BUILD_DIR)" $(OBJS)
	$(LINK) /DLL /OUT:$(BUILD_DIR)\ZssLog.dll $(OBJS)
#	xcopy *.dll ..\dlltest\ /y
# ZssLog.obj: ZssLog.cpp
# 	$(CPP) $(CPPFLAGS) /c ZssLog.cpp

# Util.obj: Util.cpp
# 	$(CPP) $(CPPFLAGS) /c Util.cpp

.c.obj: 
	$(CPP) $(CPPFLAGS) /c $<

.cpp.exe: 
	$(LINK) $(OBJS)

clean:
	del *.obj *.dll *.exp *.lib
