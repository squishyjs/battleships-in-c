.PHONY: all run clean debug help print-vars

TARGET := snake
SRC := main.c
BUILD_DIR := build
OBJ := $(BUILD_DIR)/main.o

CC ?= cc
UNAME_S := $(shell uname -s)

# Prefer pkg-config if raylib provides it.
PKG_CONFIG := $(shell command -v pkg-config 2>/dev/null)
RAYLIB_CFLAGS :=
RAYLIB_LIBS :=
ifneq ($(strip $(PKG_CONFIG)),)
RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib 2>/dev/null)
RAYLIB_LIBS := $(shell pkg-config --libs raylib 2>/dev/null)
endif

# Homebrew support (macOS): adds include/lib paths if brew exists.
BREW_PREFIX := $(shell command -v brew >/dev/null 2>&1 && brew --prefix 2>/dev/null)
BREW_CFLAGS :=
BREW_LDFLAGS :=
ifneq ($(strip $(BREW_PREFIX)),)
BREW_CFLAGS := -I$(BREW_PREFIX)/include
BREW_LDFLAGS := -L$(BREW_PREFIX)/lib
endif

CSTD := -std=c11
WARN := -Wall -Wextra -Wpedantic
OPT := -O2

CPPFLAGS ?=
CFLAGS ?=
LDFLAGS ?=
LDLIBS ?=

CPPFLAGS += $(RAYLIB_CFLAGS)
CFLAGS += $(CSTD) $(WARN) $(OPT) $(BREW_CFLAGS)
LDFLAGS += $(BREW_LDFLAGS)

# If pkg-config did not return libs, fall back to common platform flags.
ifeq ($(strip $(RAYLIB_LIBS)),)
  ifeq ($(UNAME_S),Darwin)
    LDLIBS += -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
  else
    LDLIBS += -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
  endif
else
  LDLIBS += $(RAYLIB_LIBS)
endif

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(OBJ): $(SRC) | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

run: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

debug: OPT := -O0 -g
debug: CFLAGS += -DDEBUG
debug: clean all

clean:
	@rm -rf $(BUILD_DIR)

print-vars:
	@echo "CC=$(CC)"
	@echo "UNAME_S=$(UNAME_S)"
	@echo "RAYLIB_CFLAGS=$(RAYLIB_CFLAGS)"
	@echo "RAYLIB_LIBS=$(RAYLIB_LIBS)"
	@echo "BREW_PREFIX=$(BREW_PREFIX)"
	@echo "CPPFLAGS=$(CPPFLAGS)"
	@echo "CFLAGS=$(CFLAGS)"
	@echo "LDFLAGS=$(LDFLAGS)"
	@echo "LDLIBS=$(LDLIBS)"

help:
	@echo "Targets: all (default), run, debug, clean"
