#include "rs_485.h"
#include "esp_mac.h"


void echo_send(const int port, const char* str, uint8_t length)
{
    if (uart_write_bytes(port, str, length) != length) {
        ESP_LOGE(TAG, "Send data critical failure.");
        // add your code to handle sending failure here
        abort();
    }
}
void rs485_init()
{
    uart_config_t uart_config = {
        .baud_rate = BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
        .source_clk = UART_SCLK_DEFAULT,
    };

    // Set UART log level
    esp_log_level_set(TAG, ESP_LOG_INFO);

    ESP_LOGI(TAG, "Start RS485 application test and configure UART.");
    ESP_ERROR_CHECK(uart_driver_install(uart_num, BUF_SIZE * 2, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config)); // Configure UART parameters
    ESP_LOGI(TAG, "UART set pins, mode and install driver.");
    ESP_ERROR_CHECK(uart_set_pin(uart_num, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));  // Set UART pins as per KConfig settings
    ESP_ERROR_CHECK(uart_set_mode(uart_num, UART_MODE_RS485_HALF_DUPLEX));
    ESP_ERROR_CHECK(uart_set_rx_timeout(uart_num, ECHO_READ_TOUT));
    echo_send(uart_num, "Start RS485 UART test.\r\n", 24);
    ESP_LOGI(TAG, "UART start receive loop.\r");

}

// An example of echo test with hardware flow control on UART
static void echo_task(void *arg)
{
    rs485_init();
    uint8_t* data = (uint8_t*) malloc(BUF_SIZE);// Allocate buffers for UART
    while (1) {
        //Read data from UART
        int len = uart_read_bytes(uart_num, data, BUF_SIZE, PACKET_READ_TICS);

        //Write data back to UART
        if (len > 0) {
            echo_send(uart_num, "\r\n", 2);
            char prefix[] = "RS485 Received: [";
            echo_send(uart_num, prefix, (sizeof(prefix) - 1));
            ESP_LOGI(TAG, "Received %u bytes:", len);
            printf("[ ");
            for (int i = 0; i < len; i++) {
                printf("0x%.2X ", (uint8_t)data[i]);
                echo_send(uart_num, (const char*)&data[i], 1);
                // Add a Newline character if you get a return character from paste (Paste tests multibyte receipt/buffer)
                if (data[i] == '\r') {
                    echo_send(uart_num, "\n", 1);
                }
            }
            printf("] \n");
            echo_send(uart_num, "]\r\n", 3);
        } else {
            // Echo a "." to show we are alive while we wait for input
            echo_send(uart_num, ".", 1);
            ESP_ERROR_CHECK(uart_wait_tx_done(uart_num, 10));
        }
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
    //A uart read/write example without event queue;
    xTaskCreate(echo_task, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, ECHO_TASK_PRIO, NULL);
}
