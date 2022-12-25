PRJ="scheduling"
INC=./header
LIB=./lib
OBJ=./obj
SRC=./src

CC=g++
CC_FLAGS1=-W -Wall
CC_FLAGS2=-W -Wall -c

sources=$(wildcard ./src/*.cpp)
objects=$(subst $(SRC), $(OBJ), $(patsubst %.cpp,%.o,$(sources)))

all: folders $(PRJ)
	@echo "Finished!"

folders:
	@ mkdir -p $(OBJ) $(INC) $(SRC) $(LIB)

$(PRJ): $(objects)
	$(CC) $(CC_FLAGS1) -I $(INC) -L $(LIB) -o ./$(PRJ) $(objects)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CC_FLAGS2) -I $(INC) -L $(LIB) -o $@ $<

.PHONY : all clean

clean:
	-@rm -f ./$(PRJ)  $(OBJ)/*.o  ./*~ $(INC)/*~ $(LIB)/*~ $(OBJ)/*~ $(SRC)/*~ 