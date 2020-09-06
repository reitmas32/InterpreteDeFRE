APP 	:= app
MAIN 	:= main.cpp
CCFLAGS := -Wall -pedantic -ggdb -std=c++2a
CFLAGS 	:= -Wall -pedantic -std=c99
CC 		:= clang++
C 		:= gcc
MKDIR	:= mkdir -p
SRC 	:= src
OBJ 	:= obj
BIN		:= bin
INCL	:= include
LIBDIR	:= lib
LIBS	:= -pthread
INCDIRS	:= -I$(SRC) -I$(LIBDIR)

# define standard colors
#Black
BLACK        := \e[30m
BLACK_SUB	 := \e[4;30m
BLACK_WEIGHT := \e[1;30m
BLACK_ITALIC := \e[3;30m
BLACK_ITA_WEI:= \e[1;3;30m
BLACK_FLUSH	 := \e[5;30m
BLACK_BACK	 := \e[7;30m
BLACK_STRIKE := \e[9;30m
#Red
RED        	:= \e[31m
RED_SUB	 	:= \e[4;31m
RED_WEIGHT 	:= \e[1;31m
RED_ITALIC 	:= \e[3;31m
RED_ITA_WEI := \e[1;3;31m
RED_FLUSH	:= \e[5;31m
RED_BACK	:= \e[7;31m
RED_STRIKE 	:= \e[9;31m
#Blue
BLUE        := \e[34m
BLUE_SUB	:= \e[4;34m
BLUE_WEIGHT := \e[1;34m
BLUE_ITALIC := \e[3;34m
BLUE_ITA_WEI:= \e[1;3;34m
BLUE_FLUSH	:= \e[5;34m
BLUE_BACK	:= \e[7;34m
BLUE_STRIKE := \e[9;34m
#Green
GREEN        := \e[32m
GREEN_SUB	 := \e[4;32m
GREEN_WEIGHT := \e[1;32m
GREEN_ITALIC := \e[3;32m
GREEN_ITA_WEI:= \e[1;3;32m
GREEN_FLUSH	 := \e[5;32m
GREEN_BACK	 := \e[7;32m
GREEN_STRIKE := \e[9;32m
#Cyan
CYAN        := \e[36m
CYAN_SUB	:= \e[4;36m
CYAN_WEIGHT := \e[1;36m
CYAN_ITALIC := \e[3;36m
CYAN_ITA_WEI:= \e[1;3;36m
CYAN_FLUSH	:= \e[5;36m
CYAN_BACK	:= \e[7;36m
CYAN_STRIKE := \e[9;36m
#WHITE
WHITE        := \e[37m
WHITE_SUB	 := \e[4;37m
WHITE_WEIGHT := \e[1;37m
WHITE_ITALIC := \e[3;37m
WHITE_ITA_WEI:= \e[1;3;37m
WHITE_FLUSH	 := \e[5;37m
WHITE_BACK	 := \e[7;37m
WHITE_STRIKE := \e[9;37m
#PURPLE
PURPLE        	:= \e[35m
PURPLE_SUB	 	:= \e[4;35m
PURPLE_WEIGHT 	:= \e[1;35m
PURPLE_ITALIC 	:= \e[3;35m
PURPLE_ITA_WEI	:= \e[1;3;35m
PURPLE_FLUSH	:= \e[5;35m
PURPLE_BACK	 	:= \e[7;35m
PURPLE_STRIKE 	:= \e[9;35m
#RED          := 
#GREEN        := 
#YELLOW       := 
#LIGHTPURPLE  := 
#PURPLE       := 
#BLUE         := 
#WHITE        := 

# Colors
COMPILER_COLOR  := $(GREEN_ITA_WEI)
BUILD_COLOR		:= $(BLUE_SUB)
OBJ_COLOR   	:= $(CYAN)
SRC_COLOR   	:= $(RED_ITA_WEI)
FLAGS_COLOR		:= $(GREEN_SUB)
INCDIRS_COLOR	:= $(BLUE_ITALIC)
LIBS_COLOR		:= $(GREEN_WEIGHT)
RM_COLOR		:= $(RED_BACK)
MKDIR_COLOR		:= $(GREEN_BACK)
OK_COLOR    	:= \033[0;32m
ERROR_COLOR 	:= \033[0;31m
WARN_COLOR  	:= \033[0;33m
NO_COLOR    	:= \033[m

RESET := $(shell tput -Txterm sgr0)

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

# Print
PRINT_CXX_COMPILER 	:= $(COMPILER_COLOR)$(CC)$(NO_COLOR)
PRINT_C_COMPILER 	:= $(COMPILER_COLOR)$(C)$(NO_COLOR)
PRINT_BUILD		:= $(BUILD_COLOR)$(BIN)/$(APP)$(NO_COLOR)
PRINT_OBJS_ALL	:= $(OBJ_COLOR)$(ALLCPPSOBJ) $(ALLCSOBJ)$(NO_COLOR)

define PRINT_OBJ
$(OBJ_COLOR)$(1)$(NO_COLOR)
endef

define PRINT_SRC
$(SRC_COLOR)$(1)$(NO_COLOR)
endef

define PRINT_FLAGS
$(FLAGS_COLOR)$(1)$(NO_COLOR)
endef

define PRINT_INCDIRS
$(INCDIRS_COLOR)$(1)$(NO_COLOR)
endef

define PRINT_LIBS
$(LIBS_COLOR)$(1)$(NO_COLOR)
endef

$(APP) : $(OBJSUBDIRS) $(BIN) $(ALLCSOBJ) $(ALLCPPSOBJ)
	@echo "$(PRINT_CXX_COMPILER) -o $(PRINT_BUILD) $(PRINT_OBJS_ALL) $(call PRINT_LIBS,$(LIBS))"
	@$(CC) -o $(BIN)/$(APP) $(ALLCPPSOBJ) $(ALLCSOBJ) $(LIBS)

$(OBJ)/%.o : $(SRC)/%.c
	@echo "$(PRINT_C_COMPILER) -o $(call PRINT_OBJ, $(patsubst $(SRC)%,$(OBJ)%,$@)) -c $(call PRINT_SRC,$^) \
	$(call PRINT_FLAGS,$(CFLAGS)) \
	$(call PRINT_INCDIRS,$(INCDIRS)) \
	$(call PRINT_LIBS,$(LIBS))"
	@$(C) -o $(patsubst $(SRC)%,$(OBJ)%,$@) -c $^ $(CFLAGS) $(INCDIRS) $(LIBS)

$(OBJ)/%.o : $(SRC)/%.cpp
	@echo "$(PRINT_CXX_COMPILER) -o $(call PRINT_OBJ, $(patsubst $(SRC)%,$(OBJ)%,$@)) -c $(call PRINT_SRC,$^) \
	$(call PRINT_FLAGS,$(CCFLAGS)) \
	$(call PRINT_INCDIRS,$(INCDIRS)) \
	$(call PRINT_LIBS,$(LIBS))"
	@$(CC) -o $(patsubst $(SRC)%,$(OBJ)%,$@) -c $^ $(CCFLAGS) $(INCDIRS) $(LIBS)

info:
	$(info $(ALLCSOBJ))
	$(info $(ALLCPPSOBJ))
	$(info $(ALLHPPS))
	$(info $(ALLHS))
	$(info $(patsubst %.cpp,%.hpp,$(MAIN)))
	$(info $(patsubst %.c,%.h,$(MAIN)))

$(OBJSUBDIRS) :
	@@echo "$(MKDIR_COLOR)$(MKDIR) $(OBJSUBDIRS)$(NO_COLOR)"
	@$(MKDIR) $(OBJSUBDIRS)

$(BIN) :
	@echo "$(MKDIR_COLOR)$(MKDIR) $(BIN)$(NO_COLOR)"
	@$(MKDIR) $(BIN)

clean:
	@echo "$(RM_COLOR)$(RM) -r "./$(OBJ)"$(NO_COLOR)"
	@$(RM) -r "./$(OBJ)"

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
