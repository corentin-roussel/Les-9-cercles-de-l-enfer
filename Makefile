CC = g++

SRC = main.cpp
CFLAGS = -Wall -Werror -Wextra -g3

EXEC1 = server
OBJDIR1 = server_prog/obj/
SRCDIR1 = server_prog/src/
SRCS1 = $(addprefix $(SRCDIR1), $(SRC))
OBJ1 = $(SRCS1:$(SRCDIR1)%.cpp=$(OBJDIR1)%.o)

EXEC2 = client
OBJDIR2 = client_prog/obj/
SRCDIR2 = client_prog/src/
SRCS2 = $(addprefix $(SRCDIR2), $(SRC))
OBJ2 = $(SRCS2:$(SRCDIR2)%.cpp=$(OBJDIR2)%.o)

all : $(EXEC1) $(EXEC2)

$(EXEC1) : $(OBJ1)
	$(CC) -o $@ $^

$(EXEC2) : $(OBJ2)
	$(CC) -o $@ $^


$(OBJDIR1)%.o : $(SRCDIR1)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR2)%.o : $(SRCDIR2)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean :
	rm -rf $(OBJ1)* $(OBJ2)*

mrproper : clean
	rm -rf $(EXEC1) $(EXEC2)