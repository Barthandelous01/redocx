CCFLAGS := $(shell xml2-config --cflags)
CCLIBS := $(shell xml2-config --libs)
CCZIP := -lzip

DEFAULT_GOAL := default

.PHONY : flags install


default :
	cc $(CCFLAGS) $(CCLIBS) $(CCZIP) -O3 redocx.c -o redocx

echo :
	@echo $(CCFLAGS)
	@echo $(CCLIBS)
	@echo $(CCZIP)

install :
	mv redocx /usr/local/bin/redocx
