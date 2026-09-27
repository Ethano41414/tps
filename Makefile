CC = gcc
CFLAGS = -Wall -Wextra -g
LDLIBS = -lm

TARGET = tp1b

SRC = tp2.c \
    module/modtp1b.c \
	module/interface.c

OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean $(TARGET)