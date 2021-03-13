GUI = practice-manager-gui
CLI = practice-manager-cli
PROGRAM = practice-manager

.PHONY: all install uninstall unlink ${PROGRAM}

all: unlink ./prototype/${PROGRAM} ./prorotype/gui/${GUI}

unlink:
ifneq ($(wildcard ~/.local/bin/${PROGRAM}),)
	unlink ~/.local/bin/${PROGRAM}
endif

./prototype/${PROGRAM}:
	chmod +x ./prototype/${PROGRAM}

./prorotype/gui/${GUI}:
	make -C ./prototype/gui/
	@echo "now run \`sudo make install\`"

install:
ifeq ($(wildcard /usr/share/milestone),)
	mkdir /usr/share/milestone
endif
	cp prototype/${PROGRAM} /usr/local/bin/
	cp prototype/gui/${GUI} /usr/local/bin/
	cp -r ./share/* /usr/share/milestone/

clean: ./prototype/gui/${GUI}
	make -C ./prototype/gui/ clean

uninstall:
	rm -f /usr/local/bin/${PROGRAM}
