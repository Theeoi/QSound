CDIR=code
CC=g++
CFLAGS=-L$(CDIR)
LIBS=-lfmod -lfmodL

_DEPS = sound.h
DEPS = $(patsubst %,$(CDIR)/%,$(_DEPS))

_OBJ = qSound.o sound.o
OBJ = $(patsubst %,$(CDIR)/%,$(_OBJ))

$(CDIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

qSound: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(CDIR)/*.o *~ core $(INCDIR)/*~
