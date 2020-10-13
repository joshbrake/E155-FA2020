/**
    Main: Contains main function
    @file main.c
    @author Josh Brake
    @version 1.0 10/7/2020
*/

#include "STM32F401RE.h"
#include "main.h"
#include <string.h>
#include "UARTRingBuffer.h"

/** Initialize the ESP and print out IP address to terminal
 */
void initESP8266(USART_TypeDef * ESP_USART, USART_TypeDef * TERM_USART){
    uint8_t volatile str[BUFFER_SIZE] = "";

    // Disable echo
    sendString(ESP_USART, "ATE0\r\n");
    readString(ESP_USART, str);
    sendString(TERM_USART, str);
    delay_millis(DELAY_TIM, CMD_DELAY_MS);

    // Enable multiple connections
    sendString(ESP_USART, "AT+CIPMUX=1\r\n");
    readString(ESP_USART, str);
    sendString(TERM_USART, str);
    delay_millis(DELAY_TIM, CMD_DELAY_MS);

    // Create TCP server on port 80
    sendString(ESP_USART, "AT+CIPSERVER=1,80\r\n");
    readString(ESP_USART, str);
    sendString(TERM_USART, str);
    delay_millis(DELAY_TIM, CMD_DELAY_MS);

    // Connect to WiFi network
    uint8_t connect_cmd[128] = "";
    sprintf(connect_cmd,"AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASSWORD);

    sendString(ESP_USART, connect_cmd);
    readString(ESP_USART, str);
    sendString(TERM_USART, str);
    delay_millis(DELAY_TIM, CMD_DELAY_MS);

    // Wait for connection
    delay_millis(DELAY_TIM, 10000);

    // Print out status
    sendString(ESP_USART, "AT+CIFSR\r\n");
    readString(ESP_USART, str);
    sendString(TERM_USART, str);
}

/** Send command to ESP and echo to the terminal.
    @param C-string (i.e., pointer to start of a null-terminated array
        of characters.
*/
void serveWebpage(uint8_t str []) {
    USART_TypeDef * ESP_USART = id2Port(ESP_USART_ID);
    USART_TypeDef * TERM_USART = id2Port(TERM_USART_ID);
    uint8_t cmd_response[BUFFER_SIZE] = "";

    uint32_t str_length = strlen(str)+2;
    

    memset(cmd_response, 0, BUFFER_SIZE);
    // Send to terminal what we're sending
    sendString(TERM_USART, "Serving: ");
    sendString(TERM_USART, str);
    sendString(TERM_USART, "\r\n");

    // Send HTML
    memset(cmd_response, 0, BUFFER_SIZE);
    uint8_t cmd[BUFFER_SIZE] = "";
    sprintf(cmd, "AT+CIPSEND=0,%d\r\n",str_length);
    sendString(ESP_USART, cmd);
    delay_millis(DELAY_TIM, CMD_DELAY_MS);
    readString(ESP_USART, cmd_response);
    sendString(TERM_USART, cmd_response);

    memset(cmd_response, 0, BUFFER_SIZE);
    sendString(ESP_USART, str);
    sendString(ESP_USART, "\r\n");
    delay_millis(DELAY_TIM, CMD_DELAY_MS);
    readString(ESP_USART, cmd_response);
    sendString(TERM_USART, cmd_response);

}

/** Map USART1 IRQ handler to our custom ISR
 */
void USART1_IRQHandler(){
    USART_TypeDef * ESP_USART = id2Port(ESP_USART_ID);
    usart_ISR(ESP_USART);
}

int main(void) {
    // Configure flash latency and set clock to run at 84 MHz
    configureFlash();
    configureClock();

    // Enable GPIOA clock
    RCC->AHB1ENR.GPIOAEN = 1;

    // Initialize timer
    RCC->APB1ENR |= (1 << 0); // TIM2_EN
    initTIM(DELAY_TIM);

    // Set up LED pin as output
    pinMode(GPIOA, LED_PIN, GPIO_OUTPUT);

    // Configure ESP and Terminal UARTs
    USART_TypeDef * ESP_USART = initUSART(ESP_USART_ID, 115200);
    USART_TypeDef * TERM_USART = initUSART(TERM_USART_ID, 115200);

    // Configure USART1 interrupt
    // Enable interrupts globally
    __enable_irq();

    // Configure interrupt for USART1
    *NVIC_ISER1 |= (1 << 5);
    ESP_USART->CR1.RXNEIE = 1;
    
    // Initialize ring buffer
    init_ring_buffer();
    flush_buffer();

    // Initialize ESP
    delay_millis(DELAY_TIM, 1000);
    initESP8266(ESP_USART, TERM_USART);
    delay_millis(DELAY_TIM, 500);

    // Set up temporary buffers for requests
    uint8_t volatile http_request[BUFFER_SIZE] = "";
    uint8_t volatile temp_str[BUFFER_SIZE] = "";
    
    while(1) {
        // Clear temp_str buffer
        memset(http_request, 0, BUFFER_SIZE);
        volatile uint32_t http_req_len = 0;

        // Loop through and read any data available in the buffer
        if(is_data_available()) {
            do{
                memset(temp_str, 0, BUFFER_SIZE);
                readString(ESP_USART, temp_str); // Read in available bytes
                strcat(http_request, temp_str); // Append to current http_request string
                http_req_len = strlen(http_request); // Store length of request
                delay_millis(DELAY_TIM, 20); // Delay
            } while(is_data_available()); // Check for end of transaction

            // Echo received string to the terminal
            sendString(TERM_USART, http_request);

            // Search to see if there was a GET request
            volatile uint8_t get_request = look_for_substring("GET", http_request);

            // If a GET request, process the request
            if(get_request == 1){
                // Look for "REQ" in http_request
                volatile uint8_t button_req = look_for_substring("REQ", http_request);
                volatile uint8_t favicon_req = look_for_substring("favicon", http_request);

                if(!favicon_req){
                    
                    /* Look for request data and process it
                        If REQ=ON, then turn LED on.
                        If REQ=OFF, then turn LED off.
                        If we don't recognize the REQ, then send message to terminal and don't do anything.
                    */
                    if(button_req == 1){
                        volatile uint8_t button_req_type;
                        if(look_for_substring("=ON", http_request)) button_req_type = REQ_LED_ON;
                        else if(look_for_substring("=OFF", http_request)) button_req_type = REQ_LED_OFF;
                        else button_req_type = REQ_UNKNOWN;

                        switch(button_req_type){
                            case REQ_LED_ON:
                                digitalWrite(GPIOA, LED_PIN, 1);
                                sendString(TERM_USART, "Turning LED on.\n");
                                break;
                            case REQ_LED_OFF:
                                digitalWrite(GPIOA, LED_PIN, 0);
                                sendString(TERM_USART, "Turning LED off.\n");
                                break;
                            case REQ_UNKNOWN:
                                sendString(TERM_USART, "Unknown request.\n");
                        }
                    }

                    // Serve the individual HTML commands for the webpage
                    serveWebpage("<!DOCTYPE html>");
                    serveWebpage("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
                    serveWebpage("<title>ESP8266 Demo</title>");
                    serveWebpage("<h3>ESP8266</h3>");
                    serveWebpage("<p>Welcome to MicroPs IoT lab!</p>");
                    serveWebpage("<form action=\"REQ=ON\"><input type=\"submit\" value = \"LED ON\"></form>");
                    serveWebpage("<form action=\"REQ=OFF\"><input type=\"submit\" value = \"LED OFF\"></form>");

                    // Read if LED is on or off and display to webpage.
                    if(digitalRead(GPIOA, LED_PIN)){
                        serveWebpage("<p>LED is ON.</p>");
                    }
                    else {
                        serveWebpage("<p>LED is OFF.</p>");
                    }
                }

                // Close connection
                memset(temp_str, 0, BUFFER_SIZE);
                sendString(ESP_USART, "AT+CIPCLOSE=0\r\n");
                readString(ESP_USART, temp_str);
                sendString(TERM_USART,temp_str);
            }
        }
    }
}