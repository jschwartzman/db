#############################################################################
#	Makefile for Database Project
# 	John Schwartzman, Forte Systems, Inc. 		
#	07/14/2019
#
#	Commands:  make release, make debug, make clean
#			   make = make release
#   Requires:  maketest.sh
#
#############################################################################
PROG    	= db
SHELL   	= /bin/bash
SRCDIR	    = src
RELEASE_DIR = release_dir
DEBUG_DIR   = debug_dir
CPP_SRC		= $(wildcard $(SRCDIR)/*.cpp)
CPP_HDR		= $(wildcard $(SRCDIR)/*.h)
RELEASE_OBJ = $(patsubst $(SRCDIR)/%.cpp, $(RELEASE_DIR)/%.obj, $(CPP_SRC))
DEBUG_OBJ	= $(patsubst $(SRCDIR)/%.cpp, $(DEBUG_DIR)/%.obj, $(CPP_SRC))
REL_CCFLAGS = -O3 -c -Wall -pedantic -std=c++11
DBG_CCFLAGS = -O0 -g -c -Wall -pedantic -std=c++11

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

$(RELEASE_DIR)/$(PROG): $(RELEASE_OBJ)
	g++ -o $@ $^ -L/usr/lib64 -lmysqlcppconn

$(DEBUG_DIR)/$(PROG): $(DEBUG_OBJ)
	g++ -g -o $@ $^ -L/usr/lib64 -lmysqlcppconn

$(RELEASE_DIR)/%.obj: $(SRCDIR)/%.cpp $(CPP_HDR)
	@mkdir -p $(@D)
	g++ $(REL_CCFLAGS) -I /usr/include/jdbc -o $@ $<

$(DEBUG_DIR)/%.obj: $(SRCDIR)/%.cpp $(CPP_HDR)
	@mkdir -p $(@D)	
	g++ $(DBG_CCFLAGS) -I /usr/include/jdbc -o $@ $<

#############################################################################
