#ifndef I2C_CONTROL_H
#define I2C_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include "driver/i2c_master.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// -----------------------------------------------------------------------------
// Configuration Struct
// -----------------------------------------------------------------------------

/**
 * @brief I2C configuration structure
 *
 * Used to define GPIO pins, clock speed, and slave address for the I2C device.
 */
typedef struct {
    gpio_num_t sda;            ///< GPIO pin for I2C SDA line
    gpio_num_t scl;            ///< GPIO pin for I2C SCL line
    uint32_t clk_speed_hz;     ///< Clock speed in Hz (typically 100kHz or 400kHz)
    uint8_t device_addr;       ///< 7-bit I2C slave device address
} i2c_library_config_t;

// -----------------------------------------------------------------------------
// Public API Functions
// -----------------------------------------------------------------------------

/**
 * @brief Initialize the I2C master bus and add a device
 *
 * This sets up the I2C hardware, creates the bus, and connects to the target device.
 *
 * @param[out] bus_handle Pointer to hold the I2C bus handle
 * @param[out] dev_handle Pointer to hold the I2C device handle
 * @param[in] config Pointer to user-provided configuration
 *
 * @return ESP_OK on success, or ESP_ERR_xxx on failure
 */
esp_err_t i2c_library_init(i2c_master_bus_handle_t *bus_handle,
                           i2c_master_dev_handle_t *dev_handle,
                           const i2c_library_config_t *config);

/**
 * @brief Write a single byte to a specific I2C device register
 *
 * @param[in] dev I2C device handle
 * @param[in] reg Register address to write to
 * @param[in] value Data byte to write
 *
 * @return ESP_OK on success, or ESP_ERR_xxx on failure
 */
esp_err_t i2c_library_write_register(i2c_master_dev_handle_t dev, uint8_t reg, uint8_t value);

/**
 * @brief Read a single byte from a specific I2C device register
 *
 * @param[in] dev I2C device handle
 * @param[in] reg Register address to read from
 * @param[out] value Pointer to store the read byte
 *
 * @return ESP_OK on success, or ESP_ERR_xxx on failure
 */
esp_err_t i2c_library_read_register(i2c_master_dev_handle_t dev, uint8_t reg, uint8_t *value);

/**
 * @brief Example loop that blinks/toggles a device output via I2C
 *
 * Continuously writes 0x01 and 0x00 to register 0x15 with a 1ms delay.
 * Intended for devices like I/O expanders or LEDs.
 *
 * @param[in] dev I2C device handle
 */
void i2c_library_blink_loop(i2c_master_dev_handle_t dev);

#ifdef __cplusplus
}
#endif

#endif // I2C_CONTROL_H
