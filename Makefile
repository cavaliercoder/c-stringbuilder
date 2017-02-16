SOURCE_FILES = \
	main.c \
	sb.c

SOURCE_HEADERS = \
	sb.h

IPSUM = Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do \
	eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad \
	minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex \
	ea commodo consequat

all: main

main: $(SOURCE_FILES) $(HEADERS)
	gcc -g -o main $(SOURCE_FILES)

clean:
	rm -vf main

check: main
	./main $(IPSUM)

.PHONY: all clean check
