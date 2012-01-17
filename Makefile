#
#Copyright (C) 2011 Jack Culhane - jackculhane@gmail.com
#
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

CC := gcc
LIBTOOL := libtool
  
LIB_INSTALL_DIR = $(HOME)/.purple/plugins

PIDGIN_PLUGIN = buzz_resp

PIDGIN_CFLAGS  = $(shell pkg-config pidgin --cflags)
GTK_CFLAGS   = $(shell pkg-config gtk+-2.0 --cflags)
PIDGIN_LIBS    = $(shell pkg-config pidgin --libs)
GTK_LIBS     = $(shell pkg-config gtk+-2.0 --libs)
PIDGIN_LIBDIR  = $(shell pkg-config --variable=libdir pidgin)/pidgin

all: $(PIDGIN_PLUGIN).so

install: all
	cp $(PIDGIN_PLUGIN).so $(LIB_INSTALL_DIR)

buzz_resp.so: $(PIDGIN_PLUGIN).o 
	$(CC) -shared $(CFLAGS) $< -o $@ $(PIDGIN_LIBS) -Wall,--export-dynamic -Wl,-soname

$(PIDGIN_PLUGIN).o:$(PIDGIN_PLUGIN).c 
	$(CC) -g $(CFLAGS) -Wall -fPIC -c $< -o $@ $(PIDGIN_CFLAGS) -DHAVE_CONFIG_H

clean:
	rm -rf *.o *.c~ *.h~ *.so *.la .libs
