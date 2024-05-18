arm:
	cd src && make -f arm.mk
#	cd dlltest && make -f arm.mk

linux:
	cd src && nmake
	cd dlltest && nmake

windows:
	cd src && nmake
	cd dlltest && nmake

clean: 
	cd src && nmake clean
	cd dlltest && nmake clean
	if exist build_arm rmdir build_arm /s /q
	if exist build_win32 rmdir build_win32 /s /q
#	This statment is dll exports interface, if does not define it, the dll has no entry point,
#	you can use "dumpbin /exports xxx.dll" to look the exports interface.

# 	/DZSSLOG_EXPORTS

#


