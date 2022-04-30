# ----------------------------
# Makefile Options
# ----------------------------

NAME = NEWTON
ICON = icon.png
DESCRIPTION = "Newton Fractal Generator"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
