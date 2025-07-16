#ifndef _RS_485_
#define _RS_485_


// -------------------------------------LIBRARY HEADER FILE-----------------------------
// This header file is part of the RS485 Echo Application.
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "driver/uart.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"


// Public type definitions

typedef struct {
    int x;
    int y;
} Point;

// ----------------------------------FUNCTION declarations------------------------------
int library_init(void);
int calculate(Point p);
void library_cleanup(void);

// ----------------------------------Macro definitions----------------------------------
// #define TAG_rs485 "RS485_ECHO_APP"


#define ECHO_TEST_TXD           (17)
#define ECHO_TEST_RXD           (16)
#define ECHO_TEST_RTS           (5) // RTS for RS485 Half-Duplex Mode manages DE/~RE

// CTS is not used in RS485 Half-Duplex Mode
#define ECHO_TEST_CTS           (UART_PIN_NO_CHANGE)

#define BUF_SIZE                (127)
#define BAUD_RATE               (115200)

// Read packet timeout
#define PACKET_READ_TICS        (100 / portTICK_PERIOD_MS)
#define ECHO_TASK_STACK_SIZE    (1024)
#define ECHO_TASK_PRIO          (10)
#define ECHO_UART_PORT          (UART_NUM_0)

// Timeout threshold for UART = number of symbols (~10 tics) with unchanged state on receive pin
#define ECHO_READ_TOUT          (3) // 3.5T * 8 = 28 ticks, TOUT=3 -> ~24..33 ticks
#define BLINK_GPIO              (2) // GPIO for LED blink, not used in this example



//-----------------------------------Variable definitions--------------------------------
const int uart_num = ECHO_UART_PORT;
#define TAG "RS485_LOGS"


#endif // YOURLIB_H