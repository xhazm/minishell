# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/13 16:40:53 by vmiseiki          #+#    #+#              #
#    Updated: 2022/02/02 20:42:27 by lpfleide         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER = libft.h

GCC = gcc
CFLAGS = -Wall -Wextra -Werror -c

SRC =	ft_memset.c		ft_bzero.c		ft_memcpy.c		ft_striteri.c	ft_memmove.c	ft_memchr.c		ft_memcmp.c		\
		ft_strlen.c 	ft_strlcpy.c	ft_strlcat.c	ft_strchr.c		ft_strrchr.c	ft_strnstr.c	ft_strncmp.c	\
		ft_atoi.c		ft_isalpha.c	ft_isdigit.c	ft_isalnum.c	ft_isascii.c	ft_isprint.c	ft_toupper.c	\
		ft_tolower.c	ft_calloc.c		ft_strdup.c		ft_substr.c		ft_strjoin.c	ft_strtrim.c	ft_split.c		\
		ft_itoa.c		ft_strmapi.c	ft_putchar_fd.c ft_putstr_fd.c	ft_putendl_fd.c ft_putnbr_fd.c	ft_strlen2D.c	\
		ft_strdup2D.c	ft_strcmp.c		ft_garbage_collector.c 			ft_free2darr.c

BONUS_SRC = ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c	ft_lstlast.c	ft_lstadd_back.c	\
			ft_lstdelone.c	ft_lstclear.c		ft_lstiter.c	ft_lstmap.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME) bonus

$(NAME): $(SRC) $(HEADER)
	@$(GCC) $(CFLAGS) $(SRC)
	@ar -crs $(NAME) $(OBJ)

bonus: $(BONUS_SRC) $(HEADER)
	@$(GCC) $(CFLAGS) $(BONUS_SRC)
	@ar -crs $(NAME) $(BONUS_OBJ)
	
clean:
	@rm -f *.o

fclean: clean
	@rm -f *.a

re: fclean all

.PHONY: all clean fclean re bonus