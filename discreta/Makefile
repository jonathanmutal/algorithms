TARGET = discreta
SOURCE =  API.c
OBJECT = $(SOURCE:.c=.o )
FLAG = -std=c99 -Wall -Werror -Wextra
CC = gcc

all: $(TARGET)
	./$(TARGET)

$(TARGET): object
	$(CC) $(FLAG) -o $@ $(OBJECT)

object: $(SOURCE)
	$(CC) $(FLAG) -c $(SOURCE)

.PHONY: clean

clean:
	rm $(OBJECT) $(TARGET)
