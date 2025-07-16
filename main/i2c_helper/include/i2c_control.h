#ifndef I2C_CONTROL_H
#define I2C_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

// --- Includes ---
#include <stdio.h>
#include <string.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_console.h"
#include "esp_vfs_fat.h"
#include "cmd_system.h"
#include "cmd_i2ctools.h"
#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"


// --- Macros and Constants ---
// Define constants, macros, or configuration options

// --- Type Definitions ---
// Define enums, structs, typedefs, etc.

// --- Function Declarations ---
// Declare all public functions that this library exposes

#ifdef __cplusplus
}
#endif

#endif // YOUR_LIBRARY_H