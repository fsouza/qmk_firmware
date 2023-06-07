#!/usr/bin/env bash

set -euo pipefail

MY_DIR=$(cd "$(dirname "${0}")" && pwd -P)
GIT_DIR=${MY_DIR}/zsa_firmware
GIT_BRANCH=firmware22

function qmk_setup() {
    pushd "${GIT_DIR}"
    qmk setup "${QMK_REPO}" -b "${GIT_BRANCH}" -y
    popd
}

function main() {
    qmk_setup
}

main
