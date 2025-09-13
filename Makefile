BUILD_TYPE ?= debug

CC = gcc
RM = rm -f

CFLAGS_DEBUG = -Wall -Wextra -g -DDEBUG -O0
CFLAGS_RELEASE = -Wall -Wextra -O2 -DNDEBUG

ifeq ($(BUILD_TYPE), debug)
    CFLAGS = $(CFLAGS_DEBUG)
    TARGET = encorder_debug
    BUILD_MSG = "Building DEBUG version"
else ifeq ($(BUILD_TYPE), release)
    CFLAGS = $(CFLAGS_RELEASE)
    TARGET = encorder_release
    BUILD_MSG = "Building RELEASE version"
else
    CFLAGS = $(CFLAGS_DEBUG)
    TARGET = encorder_debug
    BUILD_MSG = "Building DEFAULT (debug) version"
endif

SOURCES = main.c lib.c
HEADERS = lib.h
OBJECTS = $(SOURCES:.c=.o)

define PRINT_STATUS
	@echo "================================"
	@echo $(BUILD_MSG)
	@echo "Target: $(TARGET)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@echo "================================"
endef

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(PRINT_STATUS)
	@echo "Linking $(TARGET)..."
	$(CC) $(OBJECTS) -o $@
	@echo "Build complete: $(TARGET)"

%.o: %.c $(HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean-debug:
	@echo "Cleaning debug build..."
	$(RM) *.o encorder_debug

clean-release:
	@echo "Cleaning release build..."
	$(RM) *.o encorder_release

clean:
	@echo "Cleaning all builds..."
	$(RM) *.o encorder_debug encorder_release

rebuild-debug: BUILD_TYPE = debug
rebuild-debug: clean-debug $(TARGET)

rebuild-release: BUILD_TYPE = release
rebuild-release: clean-release $(TARGET)

debug: BUILD_TYPE = debug
debug: $(TARGET)

release: BUILD_TYPE = release
release: $(TARGET)

rebuild: clean all

.PHONY: all clean clean-debug clean-release debug release rebuild rebuild-debug rebuild-release
