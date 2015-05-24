TARGET = discreta
SOURCE =  API.c main.c radixsort.c
OBJECT = $(SOURCE:.c=.o )
FLAG = -std=c99 -Wall -Werror -Wextra -g
CC = gcc

$(TARGET): object
	$(CC) $(FLAG) -o $@ $(OBJECT)

object: $(SOURCE)
	$(CC) $(FLAG) -c $(SOURCE)

.PHONY: clean

clean:
	rm $(OBJECT) $(TARGET)
