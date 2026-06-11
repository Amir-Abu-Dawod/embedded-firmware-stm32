/*
 * ring_buffer.c
 *
 *  Created on: May 19, 2026
 *      Author: amira
 */

#include "ring_buffer.h"

static uint16_t rb_next_index(uint16_t index)
{
    index++;

    if (index >= RB_SIZE) //I used branch wraparound instead of % to avoid modulo cost.
    {
        index = 0;
    }

    return index;
}

void rb_init(ring_buffer_t *rb)
{
    rb->head = 0;
    rb->tail = 0;
}

bool rb_is_empty(const ring_buffer_t *rb)
{
    return rb->head == rb->tail;
}

bool rb_is_full(const ring_buffer_t *rb)
{
    return rb_next_index(rb->head) == rb->tail;
}

bool rb_push(ring_buffer_t *rb, uint8_t data)
{
    uint16_t next = rb_next_index(rb->head);

    if (next == rb->tail)
    {
        return false;
    }

    rb->buffer[rb->head] = data;
    rb->head = next;

    return true;
}

bool rb_pop(ring_buffer_t *rb, uint8_t *data)
{
    if (rb_is_empty(rb))
    {
        return false;
    }

    *data = rb->buffer[rb->tail];
    rb->tail = rb_next_index(rb->tail);

    return true;
}

uint16_t rb_count(const ring_buffer_t *rb)
{
    uint16_t head = rb->head;
    uint16_t tail = rb->tail;

    if (head >= tail)
    {
        return head - tail;
    }

    return (RB_SIZE - tail) + head;
}
