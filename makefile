CC = gcc
CFLAGS = -Wall -Wextra
BUILD_DIR = build

all: $(BUILD_DIR)/app

$(BUILD_DIR)/app: main.o student_ops.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ main.o student_ops.o

main.o: main.c student_ops.h person.h
	$(CC) $(CFLAGS) -c main.c

student_ops.o: student_ops.c student_ops.h person.h
	$(CC) $(CFLAGS) -c student_ops.c

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
ifeq ($(OS),Windows_NT)
	del /Q *.o build\app.exe 2>nul || exit 0 && cls
else
	rm -f *.o build/app
endif


