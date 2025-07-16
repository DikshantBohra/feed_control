#ifndef _OTA_CONFIG_H_
#define _OTA_CONFIG_H_

#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"

#if CONFIG_BOOTLOADER_APP_ANTI_ROLLBACK
#include "esp_efuse.h"
#endif

#if CONFIG_EXAMPLE_CONNECT_WIFI
#include "esp_wifi.h"
#endif

#if CONFIG_BT_BLE_ENABLED || CONFIG_BT_NIMBLE_ENABLED
#include "ble_api.h"
#endif


static const char *TAG = "OTA_CONFIG";
extern const uint8_t server_cert_pem_start[] asm("_binary_ca_cert_pem_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_ca_cert_pem_end");




void advanced_ota_example_task(void *pvParameter);
esp_err_t _http_client_init_cb(esp_http_client_handle_t http_client);
esp_err_t validate_image_header(esp_app_desc_t *new_app_info);
void event_handler(void* arg, esp_event_base_t event_base,int32_t event_id, void* event_data);


#endif /* __ESP_WIFI_H__ */