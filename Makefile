CC = g++

CLIENT_SRC = main.cpp Spy.cpp
SERVER_SRC = main.cpp
UTILS_SRC = utils.cpp
CFLAGS = -Wall -Werror -Wextra -g3

EXEC1 = server
OBJDIR1 = server_prog/obj/
SRCDIR1 = server_prog/src/
SRCS1 = $(addprefix $(SRCDIR1), $(SERVER_SRC))
OBJ1 = $(SRCS1:$(SRCDIR1)%.cpp=$(OBJDIR1)%.o)

EXEC2 = client
OBJDIR2 = client_prog/obj/
SRCDIR2 = client_prog/src/
SRCS2 = $(addprefix $(SRCDIR2), $(CLIENT_SRC))
OBJ2 = $(SRCS2:$(SRCDIR2)%.cpp=$(OBJDIR2)%.o)

UTILS_OBJDIR = utils/obj/
UTILS_SRCDIR = utils/src/
UTILS_SRCS = $(addprefix $(UTILS_SRCDIR), $(UTILS_SRC))
UTILS_OBJ = $(UTILS_SRCS:$(UTILS_SRCDIR)%.cpp=$(UTILS_OBJDIR)%.o)

all : $(EXEC1) $(EXEC2)

$(EXEC1) : $(OBJ1) $(UTILS_OBJ)
	$(CC) -o $@ $^

$(EXEC2) : $(OBJ2) $(UTILS_OBJ)
	$(CC) -o $@ $^


$(OBJDIR1)%.o : $(SRCDIR1)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR2)%.o : $(SRCDIR2)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(UTILS_OBJDIR)%.o : $(UTILS_SRCDIR)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean :
	rm -rf $(OBJ1)* $(OBJ2)*  $(UTILS_OBJ)*

mrproper : clean
	rm -rf $(EXEC1) $(EXEC2)