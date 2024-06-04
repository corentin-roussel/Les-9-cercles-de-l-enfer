CC = g++

CFLAGS = -Wall -Werror -Wextra -g3

SRC3 = LPTF_SocketBase.cpp LPTF_SocketServer.cpp LPTF_SocketClient.cpp LPTF_Packet.cpp
OBJDIR3 = utils/obj/
SRCDIR3 = utils/src/
SRCS3 = $(addprefix $(SRCDIR3), $(SRC3))
OBJ3 = $(SRCS3:$(SRCDIR3)%.cpp=$(OBJDIR3)%.o)

SRC1 = main.cpp
EXEC1 = server
OBJDIR1 = server_prog/obj/
SRCDIR1 = server_prog/src/
SRCS1 = $(addprefix $(SRCDIR1), $(SRC1))
OBJ1 = $(SRCS1:$(SRCDIR1)%.cpp=$(OBJDIR1)%.o)

SRC2 = main.cpp 
EXEC2 = client
OBJDIR2 = client_prog/obj/
SRCDIR2 = client_prog/src/
SRCS2 = $(addprefix $(SRCDIR2), $(SRC2))
OBJ2 = $(SRCS2:$(SRCDIR2)%.cpp=$(OBJDIR2)%.o)

all : $(EXEC1) $(EXEC2)

$(EXEC1) : $(OBJ1) $(OBJ3)
	$(CC) -o $@ $^

$(EXEC2) : $(OBJ2) $(OBJ3)
	$(CC) -o $@ $^


$(OBJDIR3)%.o : $(SRCDIR3)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR1)%.o : $(SRCDIR1)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR2)%.o : $(SRCDIR2)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -rf $(OBJ1)* $(OBJ2)*

mrproper : clean
	rm -rf $(EXEC1) $(EXEC2)