NAME	=	uls

CC 	= 	clang
CFLAGS	=	-std=c11 -Wall -Wextra -Werror -Wpedantic

SRCDIR	=	src
INCDIR	=	inc
OBJDIR	=	obj

LMXDIR	=	libmx
LMXA:=	$(LMXDIR)/libmx.a
LMXINC:=	$(LMXDIR)/inc

INC		=	uls.h
INCS	=	$(addprefix $(INCDIR)/, $(INC))

SRCS	=	$(wildcard $(SRCDIR)/*.c)
OBJS	=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

CLEAR = \r\33[2K
GREEN = \033[32;1m
YELLOW = \033[33;1m
RED = \033[31;1m
NORMAL = \033[0m

all: install

install: $(LMXA) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LMXDIR) -lmx -o $@
	@printf "${CLEAR}$@ ${GREEN}created${NORMAL}\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR) -I$(LMXINC)
	@printf "${CLEAR}$(NAME) ${YELLOW}compile ${NORMAL}$(<:$(SRCDIR)/%.c=%) "	

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $@

$(LMXA):
	@make -sC $(LMXDIR)
	
clean:
	@make -sC $(LMXDIR) $@
	@rm -rf $(OBJDIR)
	@printf "$(OBJDIR)\t   $(RED)deleted$(NORMAL)\n"

uninstall: clean
	@make -sC $(LMXDIR) $@
	@rm -rf $(NAME)
	@printf "$(NAME) ${RED}uninstalled${NORMAL}\n"

reinstall: uninstall install

start: install
	./$(NAME) test/test