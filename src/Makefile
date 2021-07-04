inst: move
	@echo "use ./riscem <assemblyfilename> to run assembly program"
move: obj
	@mv "MAINFILE.o" "obj"
obj: riscem
	@if [ -d obj ]; then rm -rf obj; fi
	@mkdir obj

riscem: MAINFILE.o
	@gcc -o riscem.exe MAINFILE.o
MAINFILE.o:
	@gcc -c MAINFILE.c
	
	
	