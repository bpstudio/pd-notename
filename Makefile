# Pure Data external: notename (MIDI note -> symbol like C-4 / C#4)
# Build: make
# Optional: make PDDIR=/path/to/Pd.app/Contents/Resources

lib.name = notename
class.sources = notename.c

datafiles = notename-help.pd

PDLIBBUILDER_DIR = .
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
