inst: move
	alias riscem=./riscem.exe
	echo "use riscem <assemblyfile> to run"
move: obj
	mv "MAINFILE.o" "obj"
obj: riscem
	if [ -d obj ]; then rm -rf obj; fi
	mkdir obj

riscem: MAINFILE.o
	gcc -o riscem.exe MAINFILE.o
MAINFILE.o:
	gcc -c MAINFILE.c
	
	
	