#!/usr/bin/env bash

set -euo pipefail

MY_DIR=$(cd "$(dirname "${0}")" && pwd -P)
GIT_DIR=${MY_DIR}/qmk_firmware
QMK_REPO=zsa/qmk_firmware
GIT_REPO=https://github.com/zsa/${QMK_REPO}.git
GIT_BRANCH=firmware22

function ensure_git_repo() {
    if [ -d "${GIT_DIR}" ]; then
        git -C "${GIT_DIR}" fetch origin
    else
        git clone -b "${GIT_BRANCH}" "${GIT_REPO}" "${GIT_DIR}"
    fi

    git -C "${GIT_DIR}" checkout origin/"${GIT_BRANCH}"
    make -C "${GIT_DIR}" git-submodules
}

function qmk_setup() {
    pushd "${GIT_DIR}"
    qmk setup "${QMK_REPO}" -b "${GIT_BRANCH}" -y
    popd
}

function main() {
    ensure_git_repo
    qmk_setup
}

main
