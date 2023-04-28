@echo off
windres rsc\resources.rc -O coff -o rsc\resources.res
g++ src\*.cpp^
	src\syntree\blocks\*.cpp^
	src\syntree\pieces\*.cpp^
	src\syntree\statics\*.cpp^
	rsc\resources.res^
	-finput-charset=UTF-8^
	-static^
	-o cosmica.exe