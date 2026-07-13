/*
 * Copyright (C) 2023 Volodymyr Atamanenko
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/**
 * @file  patch.c
 * @brief Patching some of the .so internal functions or bridging them to native
 *        for better compatibility.
 */

#include "utils/utils.h"
#include <stdbool.h>
#include <stdint.h>
#include <kubridge.h>
#include <so_util/so_util.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void so_patch(void) {}