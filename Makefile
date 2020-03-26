# Makefile for keyboarder
# ----------------------------------------------------------------------
# Written by Raph.K.
#

# Compiler preset.
GCC = gcc
GPP = g++
AR  = ar
WRC = windres

# TARGET settings
TARGET_PKG = rkkeyboarder
TARGET_DIR = ./bin
TARGET_OBJ = ./obj

# Compiler optiops
COPTS += -std=c++11
COPTS += -ffast-math -fexceptions -fopenmp -O3 -s

# FLTK configs
FCG = fltk-config --use-images
FLTKCFG_CXX := $(shell ${FCG} --cxxflags)
FLTKCFG_LFG := $(shell ${FCG} --ldflags)

# FLTK image toolkit
FLIMGTK = ../fl_imgtk/lib

# libtinydcm library
TDCML = ../libtinydicom/lib

# rawprocessor
RAWPC = ../librawprocessor/lib

# Sources
SRC_PATH = src
SRCS  = $(wildcard $(SRC_PATH)/*.cpp)
SRCS += $(wildcard $(SRC_PATH)/fl/*.cpp)

# Windows resource
WRES = res/resource.rc

# Make object targets from SRCS.
OBJS = $(SRCS:$(SRC_PATH)/%.cpp=$(TARGET_OBJ)/%.o)
WROBJ = $(TARGET_OBJ)/resource.o

# Make object targets from SRCS.
OBJS  = $(SRCS:$(SRC_PATH)/%.cpp=$(TARGET_OBJ)/%.o)
OBJS += $(SRCS:$(SRC_PATH)/fl/%.cpp=$(TARGET_OBJ/%.o)

# CC FLAG
CFLAGS  = -I$(SRC_PATH) -Ires
CFLAGS += $(FLTKCFG_CXX)
CFLAGS += -I$(FLIMGTK)
CFLAGS += $(DEFS)
CFLAGS += $(COPTS)

# LINK FLAG
LFLAGS  = -static -mwindows
LFLAGS += -L$(FLIMGTK)
LFLAGS += -lfl_imgtk
LFLAGS += -lpthread
LFLAGS += $(FLTKCFG_LFG)

.PHONY: prepare clean continue

all: prepare continue

continue: $(TARGET_DIR)/$(TARGET_PKG)

prepare:
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(TARGET_OBJ)
	@mkdir -p $(TARGET_OBJ)/fl

clean:
	@echo "Cleaning built targets ..."
	@rm -rf $(TARGET_DIR)/$(TARGET_PKG).*
	@rm -rf $(TARGET_INC)/*.h
	@rm -rf $(TARGET_OBJ)/*.o
	@rm -rf $(TARGET_OBJ)/fl/*.o

$(OBJS): $(TARGET_OBJ)/%.o: $(SRC_PATH)/%.cpp
	@echo "Building $@ ... "
	@$(GPP) $(CFLAGS) -c $< -o $@

$(WROBJ): $(WRES) res/resource.h
	@echo "Building windows resource ..."
	@$(WRC) -i $(WRES) $(WFLAGS) -o $@

$(TARGET_DIR)/$(TARGET_PKG): $(OBJS) $(MININI_OBJ) $(WROBJ)
	@echo "Generating $@ ..."
	@$(GPP) $(TARGET_OBJ)/*.o $(CFLAGS) $(LFLAGS) -o $@
	@echo "done."
    
