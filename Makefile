APP 	:= app
MAIN 	:= main.cpp
CCFLAGS := -Wall -pedantic -ggdb -std=c++17
CFLAGS 	:= -Wall -pedantic -std=c99
CC 		:= g++
C 		:= gcc
MKDIR	:= mkdir -p
SRC 	:= src
OBJ 	:= obj
BIN		:= bin
INCL	:= include
LIBDIR	:= lib
LIBS	:=  -L. -lX11 -lXext #-pthread `sdl2-config --cflags --libs`
INCDIRS	:= -I$(SRC) -I$(LIBDIR)

ifdef DEBUG
	CCFLAGS += -g
	CFLAGS += -g
else
	CCFLAGS += -O3
	CFLAGS += -O3
endif

ALLCPPS		:= $(shell find $(SRC)/ -type f -iname *.cpp)
ALLCPPSOBJ	:= $(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(ALLCPPS)))
ALLHPPS		:= $(patsubst %$(patsubst %.cpp,%.hpp,$(MAIN)),,$(patsubst %.cpp,%.hpp,$(patsubst $(SRC)%,$(INCL)%,$(ALLCPPS))))

ALLCS		:= $(shell find $(SRC)/ -type f -iname *.c)
ALLCSOBJ	:= $(patsubst %.c,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(ALLCS)))
ALLHS		:= $(patsubst %$(patsubst %.c,%.h,$(MAIN)),,$(patsubst %.c,%.h,$(patsubst $(SRC)%,$(INCL)%,$(ALLCS))))

SUBDIRS 	:= $(shell find $(SRC) -type d)
OBJSUBDIRS 	:= $(patsubst $(SRC)%,$(OBJ)%, $(SUBDIRS))

.PHONY: info clean cleanall

$(APP) : $(OBJSUBDIRS) $(BIN) $(ALLCSOBJ) $(ALLCPPSOBJ)
	$(CC) -o $(BIN)/$(APP) $(ALLCPPSOBJ) $(ALLCSOBJ) $(LIBS)

$(OBJ)/%.o : $(SRC)/%.c
	$(C) -o $(patsubst $(SRC)%,$(OBJ)%,$@) -c $^ $(CFLAGS) $(INCDIRS) $(LIBS)

$(OBJ)/%.o : $(SRC)/%.cpp
	$(CC) -o $(patsubst $(SRC)%,$(OBJ)%,$@) -c $^ $(CCFLAGS) $(INCDIRS) $(LIBS)

info:
	$(info $(ALLCSOBJ))
	$(info $(ALLCPPSOBJ))
	$(info $(ALLHPPS))
	$(info $(ALLHS))
	$(info $(patsubst %.cpp,%.hpp,$(MAIN)))
	$(info $(patsubst %.c,%.h,$(MAIN)))

$(OBJSUBDIRS) :
	$(MKDIR) $(OBJSUBDIRS)

$(BIN) :
	$(MKDIR) $(BIN)

clean:
	$(RM) -r "./$(OBJ)"

cleanall:
	$(RM) -r "./$(OBJ)"
	$(RM) -r "./$(BIN)"

run: $(APP)
	cd $(BIN) && ./$(APP)

libs:
	$(MAKE) -C $(LIBDIR)

libsclean:
	$(MAKE) -C $(LIBDIR) clean

libscleanall:
	$(MAKE) -C $(LIBDIR) cleanall
