# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = PPC603gnu
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := C:/windriver/workspace_2012
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/rummbletest



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = ppc
CPU = PPC603
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp  -mlongcall
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 

IDE_DEFINES = 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif


#Project Targets
PROJECT_TARGETS = rummbletest/$(MODE_DIR)/rummbletest.out \
	 rummbletest_partialImage/$(MODE_DIR)/rummbletest_partialImage.o


#Rules

# rummbletest
ifeq ($(DEBUG_MODE),1)
rummbletest/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
rummbletest/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
rummbletest/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
rummbletest/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
rummbletest/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
rummbletest/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
rummbletest/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
rummbletest/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
rummbletest/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
rummbletest/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
rummbletest/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
rummbletest/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
rummbletest/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
rummbletest/$(MODE_DIR)/% : IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 
rummbletest/$(MODE_DIR)/% : IDE_DEFINES = 
rummbletest/$(MODE_DIR)/% : PROJECT_TYPE = DKM
rummbletest/$(MODE_DIR)/% : DEFINES = 
rummbletest/$(MODE_DIR)/% : EXPAND_DBG = 0
rummbletest/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
rummbletest/$(MODE_DIR)/% : CPU = PPC603
rummbletest/$(MODE_DIR)/% : TOOL_FAMILY = gnu
rummbletest/$(MODE_DIR)/% : TOOL = gnu
rummbletest/$(MODE_DIR)/% : TOOL_PATH = 
rummbletest/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp  -mlongcall
rummbletest/$(MODE_DIR)/% : LIBPATH = 
rummbletest/$(MODE_DIR)/% : LIBS = 
rummbletest/$(MODE_DIR)/% : OBJ_DIR := rummbletest/$(MODE_DIR)

OBJECTS_rummbletest = rummbletest_partialImage/$(MODE_DIR)/rummbletest_partialImage.o

rummbletest/$(MODE_DIR)/rummbletest.out : $(OBJECTS_rummbletest)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmppc $(OBJECTS_rummbletest) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c ppc > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc -r -nostdlib -Wl,-X -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_rummbletest) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS)  $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

rummbletest/$(MODE_DIR)/rummbletest_compile_file : $(FILE) ;

_clean :: rummbletest/$(MODE_DIR)/rummbletest_clean

rummbletest/$(MODE_DIR)/rummbletest_clean : 
	$(TRACE_FLAG)if [ -d "rummbletest" ]; then cd "rummbletest"; rm -rf $(MODE_DIR); fi


# rummbletest_partialImage
ifeq ($(DEBUG_MODE),1)
rummbletest_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
rummbletest_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
rummbletest_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
rummbletest_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
rummbletest_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
rummbletest_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
rummbletest_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
rummbletest_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
rummbletest_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
rummbletest_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
rummbletest_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
rummbletest_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
rummbletest_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
rummbletest_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 
rummbletest_partialImage/$(MODE_DIR)/% : IDE_DEFINES = 
rummbletest_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
rummbletest_partialImage/$(MODE_DIR)/% : DEFINES = 
rummbletest_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
rummbletest_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
rummbletest_partialImage/$(MODE_DIR)/% : CPU = PPC603
rummbletest_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = gnu
rummbletest_partialImage/$(MODE_DIR)/% : TOOL = gnu
rummbletest_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
rummbletest_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp  -mlongcall
rummbletest_partialImage/$(MODE_DIR)/% : LIBPATH = 
rummbletest_partialImage/$(MODE_DIR)/% : LIBS = 
rummbletest_partialImage/$(MODE_DIR)/% : OBJ_DIR := rummbletest_partialImage/$(MODE_DIR)

rummbletest_partialImage/$(MODE_DIR)/Objects/rummbletest/rummbnletest.o : $(PRJ_ROOT_DIR)/rummbnletest.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


OBJECTS_rummbletest_partialImage = rummbletest_partialImage/$(MODE_DIR)/Objects/rummbletest/rummbnletest.o

rummbletest_partialImage/$(MODE_DIR)/rummbletest_partialImage.o : $(OBJECTS_rummbletest_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc -r -nostdlib -Wl,-X  -o "$@" $(OBJECTS_rummbletest_partialImage) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS)  && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

rummbletest_partialImage/$(MODE_DIR)/rummbletest_partialImage_compile_file : $(FILE) ;

_clean :: rummbletest_partialImage/$(MODE_DIR)/rummbletest_partialImage_clean

rummbletest_partialImage/$(MODE_DIR)/rummbletest_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "rummbletest_partialImage" ]; then cd "rummbletest_partialImage"; rm -rf $(MODE_DIR); fi

force : 

DEP_FILES := rummbletest_partialImage/$(MODE_DIR)/Objects/rummbletest/rummbnletest.d
-include $(DEP_FILES)



-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

main_all : external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
