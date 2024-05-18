include ../MS_makefile_template

EXES = dlltest.exe

OBJS = dlltest.obj

LIB_DIR = ..\build_win32

all: $(OBJS)
	$(LINK) /OUT:$(LIB_DIR)\$(EXES) $(OBJS) /LIBPATH:$(LIB_DIR) ZssLog.lib

.cpp.obj: 
	$(CPP) $(CPPFLAGS) /c $<

clean:
	del *.obj *.exe *.dll
