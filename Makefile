.PHONY: build
build: qmk_firmware/keyboards/moonlander/keymaps/mcoding  qmk_firmware/.build/moonlander_mcoding.bin

.PHONY: qmk_firmware
qmk_firmware:
	./setup.sh

qmk_firmware/keyboards/moonlander/keymaps/mcoding: mcoding qmk_firmware
	rm -rf "$@"
	cp -r "$<" "$@"

qmk_firmware/.build/moonlander_mcoding.bin: mcoding qmk_firmware 
	make -C qmk_firmware moonlander:mcoding
