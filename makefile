#=============================================================================================================================================================================

VR_FLAGS = -D _DEBUG -g -ggdb3 -std=c++17 -O0

# ASSAN = -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

DOP = -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE

DIRECTORIES =  -IEXTRA -IEXTRA/STACK -IEXTRA/LIST -I$(VR_NAME)_F -IMEDIA

VR_FLAGS += $(ASSAN)

VR_FLAGS += $(DIRECTORIES)

VR_FLAGS += $(DOP)

# VR_VLAGS += -DTRACY_ENABLE

# DIRECTORIES += -Itracy -Itracy/public -Itracy/public/tracy

#=============================================================================================================================================================================

VR_COMPILER = g++

VR_LIBS 	=

VR_NAME		= HASH

VR_MAIN		= m_hash

VR_FUNCS	= hash

#=============================================================================================================================================================================

DO: FOLDERS DO_COMPILE

FOLDERS:
	mkdir -p OBJECTS $(VR_NAME)_F


# OBJECTS/TracyClient.o
# OBJECTS/TracyClient.o
DO_COMPILE: OBJECTS/$(VR_MAIN).o OBJECTS/$(VR_FUNCS).o
	$(VR_COMPILER) OBJECTS/$(VR_MAIN).o OBJECTS/$(VR_FUNCS).o -o $(VR_NAME) $(VR_LIBS) $(VR_FLAGS)

#=============================================================================================================================================================================

OBJECTS/$(VR_MAIN).o:  $(VR_NAME)_F/$(VR_MAIN).cpp
	$(VR_COMPILER) -c -o OBJECTS/$(VR_MAIN).o  $(VR_NAME)_F/$(VR_MAIN).cpp $(VR_FLAGS)

OBJECTS/$(VR_FUNCS).o:  $(VR_NAME)_F/$(VR_FUNCS).cpp
	$(VR_COMPILER) -c -o OBJECTS/$(VR_FUNCS).o $(VR_NAME)_F/$(VR_FUNCS).cpp $(VR_FLAGS)

# OBJECTS/TracyClient.o: tracy/public/TracyClient.cpp
# 	$(VR_COMPILER) -c -o OBJECTS/TracyClient.o tracy/public/TracyClient.cpp $(VR_FLAGS)

#=============================================================================================================================================================================

.PHONY: clean
clean:
	@rm -rf OBJECTS/$(VR_FUNCS).o OBJECTS/$(VR_MAIN).o

.PHONY: run
run:	DO
	@./$(VR_NAME)
	@python3 DATA/HistoBuilder.py

.PHONY: trace
trace:
	@sudo ./tracy/profiler/build/unix/Tracy-release

#=============================================================================================================================================================================

# vg:
# 	colour-valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(VR_NAME)

#=============================================================================================================================================================================

# python3 DATA/HistoBuilder.py

# make -Bnw | compiledb

# beer
