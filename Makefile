CFLAGS = -std=c99 -g -Wall -Wextra -pedantic -Wstrict-overflow \
	-fno-strict-aliasing -Wno-missing-field-initializers \
	-I/usr/include -I/usr/X11R6/include

LDFLAGS = -L/usr/lib -L/usr/X11R6/lib -lX11

all: nomouse
