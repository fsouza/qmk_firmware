// Copyright 2024 ZSA Technology Labs, Inc <@zsa>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef ORYX_ENABLE
#    ifndef SERIAL_NUMBER
#        define SERIAL_NUMBER "default/latest"
#    endif // SERIAL_NUMBER
#    ifndef RAW_USAGE_PAGE
#        define RAW_USAGE_PAGE 0xFF60
#    endif // RAW_USAGE_PAGE
#    ifndef RAW_USAGE_ID
#        define RAW_USAGE_ID 0x61
#    endif // RAW_USAGE_ID
#endif     // ORYX_ENABLE
