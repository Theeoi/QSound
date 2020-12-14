CDIR=code
CC=g++
CFLAGS=-L$(CDIR)
LIBS=-lfmod -lfmodL -lncurses

_DEPS = playSound.h
DEPS = $(patsubst %,$(CDIR)/%,$(_DEPS))

_OBJ = qSound.o playSound.o
OBJ = $(patsubst %,$(CDIR)/%,$(_OBJ))

$(CDIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

qSound: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(CDIR)/*.o *~ core $(INCDIR)/*~
