/**
    UART Ring Buffer: Defines functions to interact with ring buffer
    @file UARTRingBuffer.c
    @author Josh Brake
    @version 1.0 10/7/2020
*/

#include "UARTRingBuffer.h"
#include <string.h>

ring_buffer rx_buffer = {{0}, 0, 0};

ring_buffer * _rx_buffer;

void init_ring_buffer(void){
    _rx_buffer = &rx_buffer;
}

void store_char(int8_t c, ring_buffer * buffer){
    uint32_t i = (uint32_t)(buffer->head + 1) % UART_BUFFER_SIZE;

    if(i != buffer->tail) {
        buffer->buffer[buffer->head] = c;
        buffer-> head = i;
    }
}

uint8_t read_char_buffer(void){
    if(_rx_buffer->head == _rx_buffer->tail) return -1;
    else {
        int8_t c = _rx_buffer->buffer[_rx_buffer->tail];
        _rx_buffer->tail = (uint32_t)(_rx_buffer->tail + 1) % UART_BUFFER_SIZE;
        return c;
    }
}

uint8_t is_data_available(void){
    return (uint8_t)((_rx_buffer->head - _rx_buffer->tail) % UART_BUFFER_SIZE);
}

void flush_buffer(void){
    memset(_rx_buffer->buffer, '\0', UART_BUFFER_SIZE);
    _rx_buffer->head = 0;
    _rx_buffer->tail = 0;
}

void usart_ISR(USART_TypeDef * USART){
    if(USART->SR.RXNE && USART->CR1.RXNEIE){
        uint8_t c = USART->DR.DR;
        store_char(c, _rx_buffer);
        return;
    }
}

uint8_t look_for_substring (uint8_t *str, uint8_t *buffertolookinto){
    uint32_t stringlength = strlen(str);
	volatile int bufferlength = strlen(buffertolookinto);
	uint32_t so_far = 0;
	uint32_t indx = 0;
repeat:
	while (str[so_far] != buffertolookinto[indx]) {
        if(indx >= bufferlength) return 0;
        indx++;
    }

	if (str[so_far] == buffertolookinto[indx])
	{
		while (str[so_far] == buffertolookinto[indx])
		{
			so_far++;
			indx++;
		}
	}

	else
	{
		so_far = 0;
		if (indx >= bufferlength) return 0;
		goto repeat;
	}

	if (so_far == stringlength) return 1;
	else return 0;
}
