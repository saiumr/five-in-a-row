 CC          = gcc

ifeq ($(OS), Windows_NT)
	# Windows
	SDL_DIR     = D:/exlibs/SDL_lib/SDL2-2.26.2/x86_64-w64-mingw32
	SDL_LIB     = -L$(SDL_DIR)/lib
	INCLUDES    = -I ./include -I $(SDL_DIR)/include
	MKDIR       = if not exist $(OBJS_DIR) mkdir $(OBJS_DIR)
	LIB         = $(SDL_LIB) -lmingw32 -lSDL2main -lSDL2
	RM = del /s/q
else
	#Unix-like
	INCLUDES    = $(shell pkg-config --cflags sdl2) -I ./include
	LIB         = $(shell pkg-config --libs sdl2)
	MKDIR       = mkdir -p $(OBJS_DIR)
	RM          = rm -rf
endif


TARGET      = fiar.exe
#add source directory
SRC         = ./src
CFLAGS      = -Wall

OBJS_DIR    = objs
# add object files
OBJS        = main.o init.o port.o DrawCircle.o
OUT_OBJS    = $(addprefix $(OBJS_DIR)/, $(OBJS))



all:$(TARGET)

$(TARGET):$(OUT_OBJS)
	$(CC) -o $(TARGET) $(OUT_OBJS) $(CFLAGS) $(INCLUDES) $(LIB)

# `|` represent "order-only prerequisite" -> $(OBJS_DIR)
$(OBJS_DIR)/%.o:$(SRC)/%.c | $(OBJS_DIR)
	$(CC) -c $< -o $@ $(INCLUDES) $(LIB)

$(OBJS_DIR):
	$(MKDIR)

.PHONY:clean
clean:
		$(RM) $(TARGET) $(OBJS_DIR)

