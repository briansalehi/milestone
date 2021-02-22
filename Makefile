GUI = practice-manager-gui
CLI = practice-manager-cli
PROGRAM = practice-manager

.PHONY: all install uninstall unlink ${PROGRAM}

all: unlink ${PROGRAM}

unlink:
ifneq ($(wildcard ~/.local/bin/${PROGRAM}),)
	unlink ~/.local/bin/${PROGRAM}
endif

${PROGRAM}: ./prototype/${PROGRAM}
	chmod +x ./prototype/${PROGRAM}
	@echo "now run \`sudo make install\`"

install:
ifeq ($(wildcard /usr/share/milestone),)
	mkdir /usr/share/milestone
endif
	cp prototype/${PROGRAM} /usr/local/bin/
	cp -r ./share/* /usr/share/milestone/

uninstall:
	rm -f /usr/local/bin/${PROGRAM}
