riscem: obj/MAINFILE.o obj/Execution.o obj/Register.o obj/Arithmetic.o obj/BranchInst.o obj/Compare.o obj/DataTransfer.o obj/Logical.o obj/Shift.o
	@gcc obj/MAINFILE.o obj/Execution.o obj/Register.o obj/Arithmetic.o obj/BranchInst.o obj/Compare.o obj/DataTransfer.o  obj/Logical.o obj/Shift.o -o riscem
	@echo "use ./riscem <path/assembly filename.asm> to run an assembly program"

obj/MAINFILE.o: src/MAINFILE.c src/Execution.h obj src/Global_Variable.h
	@gcc -c src/MAINFILE.c
	@mv "MAINFILE.o" "obj"

obj/Execution.o: src/Global_Variable.h src/Execution.c src/Execution.h src/Register.h src/Arithmetic.h src/BranchInst.h src/Compare.h src/DataTransfer.h src/Logical.h src/Shift.h obj
	@gcc -c src/Execution.c
	@mv "Execution.o" "obj"

obj/Register.o: src/Register.c src/Register.h src/Global_Variable.h obj
	@gcc -c src/Register.c
	@mv "Register.o" "obj"

obj/Arithmetic.o: src/Global_Variable.h src/Arithmetic.c src/Arithmetic.h src/Register.h obj
	@gcc -c src/Arithmetic.c
	@mv "Arithmetic.o" "obj"

obj/BranchInst.o: src/Global_Variable.h src/BranchInst.c src/BranchInst.h src/Register.h obj
	@gcc -c src/BranchInst.c
	@mv "BranchInst.o" "obj"

obj/Compare.o: src/Global_Variable.h src/Compare.c src/Compare.h src/Register.h obj
	@gcc -c src/Compare.c
	@mv "Compare.o" "obj"

obj/DataTransfer.o: src/Global_Variable.h src/DataTransfer.c src/DataTransfer.h src/Register.h obj
	@gcc -c src/DataTransfer.c
	@mv "DataTransfer.o" "obj"

obj/Logical.o: src/Global_Variable.h src/Logical.c src/Logical.h src/Register.h obj
	@gcc -c src/Logical.c
	@mv "Logical.o" "obj"

obj/Shift.o: src/Global_Variable.h src/Shift.c src/Shift.h src/Register.h obj
	@gcc -c src/Shift.c
	@mv "Shift.o" "obj"
obj:
	@[ -d obj ]||mkdir obj
clean:
	@rm -rf obj
	@rm riscem