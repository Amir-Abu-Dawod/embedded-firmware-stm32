/*
 * ring_buffer.h
 *
 *  Created on: May 19, 2026
 *      Author: amira
 */

#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_

#include <stdint.h>
#include <stdbool.h>

#define RB_SIZE 128U

typedef struct
{
    uint8_t buffer[RB_SIZE];
    //volatile on head and tail, because they are shared between ISR context and main-loop context.
    volatile uint16_t head;
    volatile uint16_t tail;
} ring_buffer_t;

void rb_init(ring_buffer_t *rb);
bool rb_is_empty(const ring_buffer_t *rb);
bool rb_is_full(const ring_buffer_t *rb);
bool rb_push(ring_buffer_t *rb, uint8_t data);
bool rb_pop(ring_buffer_t *rb, uint8_t *data);
uint16_t rb_count(const ring_buffer_t *rb);

#endif /* INC_RING_BUFFER_H_ */
