#
# lem-in
#
# Makefile
#

#
# Config
#

# Project name
NAME := lem-in

# Project directories
DIRS := srcs include

# Obj directory
O_DIR := o

# Makefiles to call
LIBS := libft

# Number of threads
THREADS := 1

# C compiler
C_CC := clang

# Linking compiler
LD_CC := clang

# Clang flags
C_FLAGS := -Wall -Wextra -Werror -O2

# Linking flags
LD_FLAGS := -Llibft -lft

# Clang include flags
C_HEADS := -Iinclude -Ilibft

#
# Internal
#

O_FILES := o/srcs/main.o \
	o/srcs/parse_raw.o \
	o/srcs/solve_find.o \
	o/srcs/solve_sort.o \
	o/srcs/ft_subis.o \
	o/srcs/parser.o \
	o/srcs/print.o \
	o/srcs/path_find.o

MSG_0 := printf '\033[0;32m%-19.19s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-19.19s\033[0;0m\n'
MSG_END := printf '\n'

.SILENT:

all: $(LIBS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && $(MSG_END) || $(MSG_1) $@

o/srcs/main.o: srcs/main.c include/lem_in.h include/parser.h
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/parse_raw.o: srcs/parse_raw.c include/lem_in.h include/parser.h
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/solve_find.o: srcs/solve_find.c include/lem_in.h include/parser.h
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/solve_sort.o: srcs/solve_sort.c include/lem_in.h include/parser.h
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/ft_subis.o: srcs/ft_subis.c include/lem_in.h include/parser.h
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/parser.o: srcs/parser.c include/lem_in.h include/parser.h
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/print.o: srcs/print.c include/lem_in.h include/parser.h
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/path_find.o: srcs/path_find.c include/lem_in.h include/parser.h
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

$(LIBS):
	@make -C $@
.PHONY: $(LIBS)

clean:
	@rm -f $(O_FILES) 2> /dev/null || true
	@rmdir -p o/srcs $(O_DIR) 2> /dev/null || true
.PHONY: clean

fclean: clean
	@rm -f $(NAME)
.PHONY: fclean

re: fclean all
.PHONY: re
