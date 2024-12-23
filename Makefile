# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 16:33:26 by cpoulain          #+#    #+#              #
#    Updated: 2024/12/17 16:56:12 by cpoulain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Commands

RM				=	/usr/bin/rm -f
ECHO			=	/usr/bin/echo

# Includes

include			Files.mk

# Directories

SRC_DIR			:=	src
INC_DIR			:=	include
OBJ_DIR			:=	build

# Third party

THIRD_PARTY_DIR	:=	third_party

# LIBFT

LIBFT_DIR		:=	42_libft_full
LIBFT_PATH		:=	$(THIRD_PARTY_DIR)/$(LIBFT_DIR)
LIBFT_INC_H		:=	libft.h
LIBFT_TARGET	:=	libftfull.a
LIBFT_GIT		:=	https://github.com/CodeWithCharles/42_libft_full.git

# MiniLibX

MLX_DIR			:=	minilibx-linux
MLX_PATH		:=	$(THIRD_PARTY_DIR)/$(MLX_DIR)
MLX_INC_H		:=	mlx.h
MLX_TARGET		:=	libmlx.a
MLX_GIT			:=	https://github.com/42Paris/minilibx-linux.git

# Common

THDPTY_TARGETS	:=	$(LIBFT_TARGET) $(MLX_TARGET)

# Targets

TARGET			:=	fdf
THDPTY_LIBFT_H	:=	$(INC_DIR)/$(LIBFT_INC_H)
THDPTY_MLX_H	:=	$(INC_DIR)/$(MLX_INC_H)

# Compiler

CC				:=	cc
CFLAGS			:=	-Wall -Wextra -Werror -Ofast -g
LIBFLAGS		:=	-L/usr/lib -lX11 -lXext -lXrandr -lXi -lXinerama -lXcursor -lm
# Files definition

# Objs formatter

OBJS			=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))

# Terminal colors

TERM_RESET		:=	\033[0m
TERM_BLACK		:=	\033[30m
TERM_RED		:=	\033[31m
TERM_GREEN		:=	\033[32m
TERM_YELLOW		:=	\033[33m
TERM_BLUE		:=	\033[34m
TERM_MAGENTA	:=	\033[35m
TERM_CYAN		:=	\033[36m
TERM_WHITE		:=	\033[37m

TERM_UP			:=	\033[1A
TERM_CLEAR_LINE	:=	\033[2K\r

# Flags

OBJ_HEADER_FLAG	:=	.obj_header_done
HEADER_FLAG		:=	.header_done
# Phony rules

all: $(TARGET)

clean:
	@if [ -e $(OBJ_DIR) ]; then \
		printf "$(TERM_YELLOW)Removing %d objects from \"%s\" folder...\n$(TERM_RESET)" $(words $(OBJS)) $(OBJ_DIR);\
		$(RM) -r $(OBJ_DIR);\
	fi

fclean: clean
	@if [ -e $(TARGET) ]; then \
		printf "$(TERM_YELLOW)Removing \"%s\"...\n$(TERM_RESET)" $(TARGET);\
		$(RM) $(TARGET);\
		$(RM) libft.h;\
	fi
	@if [ -e $(INC_DIR)/$(LIBFT_INC_H) ]; then \
		printf "$(TERM_YELLOW)Removing \"%s\"...\n$(TERM_RESET)" $(INC_DIR)/$(LIBFT_INC_H); \
		$(RM) $(THDPTY_LIBFT_H);\
	fi
	@if [ -e $(LIBFT_TARGET) ]; then \
		printf "$(TERM_YELLOW)Removing \"%s\"...\n$(TERM_RESET)" $(LIBFT_TARGET); \
		$(RM) $(LIBFT_TARGET);\
	fi
	@if [ -e $(INC_DIR)/$(MLX_INC_H) ]; then \
		printf "$(TERM_YELLOW)Removing \"%s\"...\n$(TERM_RESET)" $(INC_DIR)/$(MLX_INC_H); \
		$(RM) $(THDPTY_MLX_H);\
	fi
	@if [ -e $(MLX_TARGET) ]; then \
		printf "$(TERM_YELLOW)Removing \"%s\"...\n$(TERM_RESET)" $(MLX_TARGET); \
		$(RM) $(MLX_TARGET);\
	fi

cleanlibs:
	@$(MAKE) clean -C $(LIBFT_PATH)
	@$(MAKE) clean -C $(MLX_PATH)

tests: $(TEST_TARGET)

fcleanlibs:
	@$(MAKE) fclean -C $(LIBFT_PATH)
	@$(RM) $(LIBFT_TARGET)
	@$(RM) $(THDPTY_LIBFT_H)
	@$(RM) $(MLX_TARGET)
	@$(RM) $(THDPTY_MLX_H)

re: fclean all

norminette:
	@norminette $(SRC_DIR) $(INC_DIR) | grep -Ev '^Notice|OK!$$'	\
	&& $(ECHO) -e '\033[1;31mNorminette KO!'						\
	|| $(ECHO) -e '\033[1;32mNorminette OK!'

_header:
	@printf "$(TERM_GREEN)Welcome to $(TERM_BLUE) \"%s\"$(TERM_GREEN) builder !\n$(TERM_RESET)" $(TARGET)

_obj_header:
	@printf "$(TERM_MAGENTA)Building objects into \"%s\" folder...\n$(TERM_RESET)" $(OBJ_DIR)

_obj_footer:
	@printf "$(TERM_UP)$(TERM_CLEAR_LINE)$(TERM_GREEN)Done building $(TERM_BLUE)%d$(TERM_GREEN) object(s) !\n$(TERM_RESET)" $(words $(OBJS))

# Binary / Lib generation

$(TARGET): $(THDPTY_TARGETS) $(OBJS)
	@$(MAKE) _obj_footer
	@printf "$(TERM_MAGENTA)Making executable $(TERM_BLUE)\"%s\"$(TERM_MAGENTA)...$(TERM_RESET)" $@
	@$(CC) $(OBJS) -I$(INC_DIR) $(LIBFT_TARGET) $(MLX_TARGET) -o $@ $(LIBFLAGS) $(CFLAGS)
	@printf "$(TERM_CLEAR_LINE)$(TERM_GREEN)Done building executable $(TERM_BLUE)\"%s\"$(TERM_GREEN) !\n$(TERM_RESET)" $@
	@$(RM) $(OBJ_HEADER_FLAG)
	@$(RM) $(HEADER_FLAG)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if [ ! -f $(HEADER_FLAG) ]; then \
		$(MAKE) _header; \
		touch $(HEADER_FLAG); \
	fi
	@if [ ! -f $(OBJ_HEADER_FLAG) ]; then \
		$(MAKE) _obj_header; \
		touch $(OBJ_HEADER_FLAG); \
	fi
	@printf "$(TERM_CLEAR_LINE)$(TERM_MAGENTA)Compiling $(TERM_BLUE)\"%s\"$(TERM_MAGENTA)...\n$(TERM_RESET)" $@
	@mkdir -p $(@D)
	@$(CC) -c $< -o $@ -I$(INC_DIR) $(CFLAGS)
	@printf "$(TERM_UP)"

# Third party compilation


$(MLX_TARGET):
	@if [ ! -d "$(MLX_PATH)/.git" ]; then \
		printf "$(TERM_YELLOW)Cloning third party library \"%s\" in \"%s\"...\n$(TERM_RESET)" $(MLX_GIT) $(MLX_PATH);\
		git clone $(MLX_GIT) $(MLX_PATH);\
	fi
	@printf "$(TERM_MAGENTA)Making archive $(TERM_BLUE)\"%s\"$(TERM_MAGENTA)...$(TERM_RESET)" $@
	@$(MAKE) -C $(MLX_PATH)
	@cp $(MLX_PATH)/$@ ./
	@cp -u $(MLX_PATH)/$(MLX_INC_H) $(INC_DIR)/
	@printf "$(TERM_CLEAR_LINE)$(TERM_GREEN)Done copying archive $(TERM_BLUE)\"%s\"$(TERM_GREEN) !\n$(TERM_RESET)" $@

$(LIBFT_TARGET):
	@if [ ! -d "$(LIBFT_PATH)/.git" ]; then \
		printf "$(TERM_YELLOW)Cloning third party library \"%s\" in \"%s\"...\n$(TERM_RESET)" $(LIBFT_GIT) $(LIBFT_PATH);\
		git clone $(LIBFT_GIT) $(LIBFT_PATH);\
	fi
	@printf "$(TERM_MAGENTA)Making archive $(TERM_BLUE)\"%s\"$(TERM_MAGENTA)...$(TERM_RESET)" $@
	@$(MAKE) -C $(LIBFT_PATH)
	@cp $(LIBFT_PATH)/$@ ./
	@cp -u $(LIBFT_PATH)/$(LIBFT_INC_H) $(INC_DIR)/
	@printf "$(TERM_CLEAR_LINE)$(TERM_GREEN)Done copying archive $(TERM_BLUE)\"%s\"$(TERM_GREEN) !\n$(TERM_RESET)" $@

.PHONY: all clean fclean re norminette _header _obj_footer _obj_header cleanlibs fcleanlibs tests _obj_test_footer
