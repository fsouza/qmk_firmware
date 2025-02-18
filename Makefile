.PHONY: build
build: zsa_firmware/keyboards/zsa/moonlander/keymaps/mcoding  zsa_firmware/.build/moonlander_mcoding.bin

.PHONY: qmk_setup
qmk_setup:
	cd zsa_firmware && qmk setup -y

zsa_firmware/keyboards/zsa/moonlander/keymaps/mcoding: mcoding qmk_setup
	rm -rf "$@"
	cp -r "$<" "$@"

zsa_firmware/.build/moonlander_mcoding.bin: mcoding qmk_setup
	make -C zsa_firmware zsa/moonlander:mcoding
