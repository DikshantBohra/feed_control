#include "i2c_control.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_check.h"

/**
 * @brief Initialize I2C master bus and add device.
 */
esp_err_t i2c_library_init(i2c_master_bus_handle_t *bus_handle,
                           i2c_master_dev_handle_t *dev_handle,
                           const i2c_library_config_t *config)
{
    i2c_master_bus_config_t bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_NUM_0,
        .scl_io_num = config->scl,
        .sda_io_num = config->sda,
        .glitch_ignore_cnt = 7,
        .flags = {
            .enable_internal_pullup = false
        },
    };

    ESP_RETURN_ON_ERROR(i2c_new_master_bus(&bus_config, bus_handle), "i2c", "Failed to create I2C bus");

    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = config->device_addr,
        .scl_speed_hz = config->clk_speed_hz,
    };

    return i2c_master_bus_add_device(*bus_handle, &dev_config, dev_handle);
}




/**
 * @brief Write 1 byte to device register.
 */
esp_err_t i2c_library_write_register(i2c_master_dev_handle_t dev, uint8_t reg, uint8_t value)
{
    uint8_t data[] = { reg, value };
    return i2c_master_transmit(dev, data, sizeof(data), -1);
}



/**
 * @brief Read 1 byte from device register.
 */
esp_err_t i2c_library_read_register(i2c_master_dev_handle_t dev, uint8_t reg, uint8_t *value)
{
    // Write the register address
    esp_err_t err = i2c_master_transmit(dev, &reg, 1, -1);
    if (err != ESP_OK) return err;

    // Read 1 byte
    return i2c_master_receive(dev, value, 1, -1);
}



/**
 * @brief Loop to toggle register 0x15 value between 0x01 and 0x00.
 */
void i2c_library_blink_loop(i2c_master_dev_handle_t dev)
{
    while (true) {
        i2c_library_write_register(dev, 0x15, 0x01);
        vTaskDelay(pdMS_TO_TICKS(1));
        i2c_library_write_register(dev, 0x15, 0x00);
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}
