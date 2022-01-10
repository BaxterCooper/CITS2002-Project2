# A Makefile to build our 'duplicates' project

# USED THIS FOR CLEAN ON WINDOWS
# ifeq ($(OS),Windows_NT) 
# RM = del /Q /F
# CP = copy /Y
# ifdef ComSpec
# SHELL := $(ComSpec)
# endif
# ifdef COMSPEC
# SHELL := $(COMSPEC)
# endif
# else
# RM = rm -rf
# CP = cp -f
# endif

PROJECT = duplicates
HEADERS = $(PROJECT).h
OBJ = duplicates.o directories.o files.o strSHA2.c display.o hashlist.o

C11 = cc -std=c11
CFLAGS = -Wall -Werror -pedantic 

$(PROJECT) : $(OBJ)
	$(C11) $(CFLAGS)-o $(PROJECT) $(OBJ)

%.o: %.c $(HEADERS)
	$(C11) $(CFLAGS)-c $<

clean:
	rm -f $(OBJ)
#	-$(RM) $(OBJ) - WINDOWS


