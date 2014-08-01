# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgundlac <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/19 23:20:58 by fgundlac          #+#    #+#              #
#    Updated: 2014/07/23 18:14:50 by fgundlac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCDIR = .
OBJDIR = .
INCDIR = -I.

CFLAGS = -Wall -Wextra -Werror -ansi -pedantic -pedantic-errors
LDFLAGS = `SDL2/SDL2/bin/sdl2-config --libs`
CFLAGS += `SDL2/SDL2/bin/sdl2-config --cflags`

CC = clang
CFLAGS += -O3

LD = $(CC)

all:
ifeq ($(wildcard SDL2/.*),)
all: SDL2
endif

SDL2 = SDL2-2.0.3

SDL2:
	curl -o $(SDL2).tar.gz http://www.libsdl.org/release/$(SDL2).tar.gz
	@ tar xf $(SDL2).tar.gz
	( cd $(SDL2) \
		&& ./configure --prefix=$(shell pwd)/SDL2/ CC=$(CC) \
		&& $(MAKE) && $(MAKE) install )
	@ rm -rf $(SDL2).tar.gz
	@ rm -rf $(SDL2)

SDL2_IMAGE:
	wget -q http://trektawimbi.fr/SDL2_image-2.0.0.tar.gz
	tar xf SDL2_image-2.0.0.tar.gz
	( cd SDL2_image-2.0.0 \
		&& ./configure --prefix=$(shell pwd)/SDL2/ \
		&& $(MAKE) && $(MAKE) install )
	rm -rf SDL2_image-2.0.0.tar.gz
	mv SDL2_image-2.0.0/SDL_image.h SDL2/include/SDL2/SDL2_image.h
	rm -rf SDL2_image-2.0.0
	rm -rf SDL2-2.0.1

SDL2_Mixer:
	wget -q http://trektawimbi.fr/SDL2_mixer-2.0.0.tar.gz
	tar xf SDL2_mixer-2.0.0.tar.gz
	( cd SDL2_mixer-2.0.0 \
		&& ./configure --prefix=$(shell pwd)/SDL2/ \
		&& $(MAKE) && $(MAKE) install )
	rm -rf SDL2_mixer-2.0.0.tar.gz
	rm -rf SDL2_mixer-2.0.0
	rm -rf SDL2-2.0.1

clean:
	@ rm -rf $(SDL2)
	@ rm -rf $(SDL2).tar.gz

fclean: clean
	@ rm -rf SDL2

re: fclean all

.PHONY: all SDL2 SDL2_IMAGE
