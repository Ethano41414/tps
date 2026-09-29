CC = gcc
CFLAGS = -Wall -Wextra -g
LDLIBS = -lm

TARGET = tp3

SRC = tp3.c \
    module/modtp3.c \
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