CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

INCDIR = inc
SRCDIR = src
OBJDIR = obj

SRCFS := $(wildcard $(SRCDIR)/*.c)
OBJFS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFS))

LIB = libmx.a

.PHONY: all install uninstall clean reinstall

all: install

install: $(LIB)

$(LIB): $(OBJDIR) $(OBJFS)
	ar rsc $(LIB) $(OBJFS)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

uninstall: clean
	rm -f $(LIB)

clean:
	rm -rf $(OBJDIR)

reinstall: uninstall all
