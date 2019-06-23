#https://www.gnu.org/software/make/manual/html_node/make-Deduces.html
#OBJS specifies which .o files to create as part of the project
OBJS = main.o Countdown.o ItemDisplay.o Menu.o Messages.o Validation.o

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -std=c++11

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS =

#EXE_NAME specifies the name of our exectuable
EXE_NAME = MinutesToMidnight 

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXE_NAME) $(OBJS)

main.o : Menu.hpp
Countdown.o : Countdown.hpp
ItemDisplay.o : ItemDisplay.hpp
Menu.o : Menu.hpp Validation.hpp
Messages.o : Messages.hpp
Validation.o : Validation.hpp

.PHONY : clean

#removes all .o files from current directory
clean :
	rm *.o

