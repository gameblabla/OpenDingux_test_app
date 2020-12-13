PRGNAME     = test.elf
CC			= gcc

OBJS		= main.o font/font_drawing.o

CFLAGS		= -O0 -g3 -I. -Ifont

CXXFLAGS = $(CFLAGS)

LDFLAGS     =  -lc -lgcc -lm -lSDL


# Rules to make executable
$(PRGNAME): $(OBJS)  
	$(CC) $(CFLAGS)  -o $(PRGNAME) $^ $(LDFLAGS)

$(OBJ_C) : %.o : %.c
	$(CC) $(CFLAGS) -std=gnu99 -c -o $@ $<

clean:
	rm -f $(PRGNAME) *.o font/*.o
