CC = gcc
CFLAGS = -Wall -Wextra -g
LDLIBS = -lm

TARGET = tp4

SRC = tp4.c 

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