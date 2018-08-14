CC = gcc
INC = ./libft
CHECK = checker
PUSHS = push_swap
CSRCS = push_swap.c
PSRCS = chaecker.c
COBJS = $(patsubst %.c, %.o, $(CSRCS))
POBJS = $(patsubst %.c, %.o, $(PSRCS))
LIBD = -L$(INC) -lft
CFLAGS = -g -fsanitize=address -Wall -Werror -Wextra -I$(INC) 
OFLAGS =  -fsanitize=address -o $(NAME) $(OBJS) $(LIBD)
DFLAGS = $(CFLAGS) -g $(LIBD) $(DSRCS) -o
DNAME = $(NAME)_debug
DOBJS = $(patsubst %.c, %.o, $(DSRCS))

all: $(PUSHS) $(CHECK)

libft.a : ./libft/Makefile
	make -C ./libft/
$(PUSHS): libft.a $(POBJS)
	$(CC) $(OFLAGS)
$(CHECK): libft.a $(COBJS)
	$(CC) $(OFLAGS)

$(POBJS): $(PSRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
$(COBJS): $(CSRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

clean:
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft/
	rm -f $(NAME)
	rm -f $(DNAME)
	rm -rf $(DNAME).dSYM
re: fclean
	make

debugp: $(DPUSHS)
debugc: $(DCHECK)

$(DPUSHS): fclean libft.a
	$(CC) $(DFLAGS) $(DPUSHS)
	lldb $(DNAME) $(DARGS)

$(DCHECK): fclean libft.a
	$(CC) $(DFLAGS) $(DNAME)
	lldb $(DNAME) $(DARGS)
