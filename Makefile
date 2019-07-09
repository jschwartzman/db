#############################################################################
#	Makefile for db
# 	John Schwartzman, Forte Systems, Inc. 		
#	07/04/2019
#
#	Commands:  make release, make debug, make clean
#			   make = make release
#   Requires:  maketest.sh
#
#############################################################################
PROG    			= db
SHELL   			= /bin/bash
SRCDIR	    		= src
RELEASE_DIR 		= release_dir
DEBUG_DIR   		= debug_dir
CPP_SRC				= $(shell find $(SRCDIR) -name "*.cpp")
CPP_HDR				= $(shell find $(SRCDIR) -name "*.h")
RELEASE_OBJ 		= $(patsubst $(SRCDIR)/%.cpp, \
					    $(RELEASE_DIR)/%.obj, $(CPP_SRC))
DEBUG_OBJ			= $(patsubst $(SRCDIR)/%.cpp, \
					    $(DEBUG_DIR)/%.obj, $(CPP_SRC))
RELEASE_CC_FLAGS 	= -O3 -c -Wall -pedantic -std=c++11
DEBUG_CC_FLAGS   	= -O0 -g -c -Wall -pedantic -std=c++11
vpath %.h $(CPP_HDR)
.PHONY: clean

release: $(RELEASE_DIR)/$(PROG) $(RELEASE_OBJ) Makefile
	@source maketest.sh && test release debug
	cp $(RELEASE_DIR)/$(PROG) .

debug: $(DEBUG_DIR)/$(PROG) $(DEBUG_OBJ) Makefile
	@source maketest.sh && test debug release
	cp $(DEBUG_DIR)/$(PROG) .

clean:
	@rm -f $(RELEASE_DIR)/$(PROG) $(RELEASE_OBJ) $(PROG) \
		   $(DEBUG_DIR)/$(PROG) $(DEBUG_OBJ) debug release

$(RELEASE_OBJ): $(CPP_SRC) $(CPP_HDR)

$(DEBUG_OBJ): $(CPP_SRC) $(CPP_HDR)

$(RELEASE_DIR)/$(PROG): $(RELEASE_OBJ) 
	g++ -o $@ $^ -L/usr/lib64 -lmysqlcppconn
#	cp $(RELEASE_DIR)/$(PROG) .

$(DEBUG_DIR)/$(PROG): $(DEBUG_OBJ)
	g++ -g -o $@ $^ -L/usr/lib64 -lmysqlcppconn
#	cp $(DEBUG_DIR)/$(PROG) .

$(RELEASE_DIR)/%.obj: $(SRCDIR)/%.cpp 
	g++ $(RELEASE_CC_FLAGS) -I /usr/include/jdbc -o $@ $<

$(DEBUG_DIR)/%.obj: $(SRCDIR)/%.cpp 
	g++ $(DEBUG_CC_FLAGS) -I /usr/include/jdbc -o $@ $<

#############################################################################
