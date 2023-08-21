/*
** EPITECH PROJECT, 2023
** B-NWP-400-TLS-4-1-myteams-benjamin.bourez
** File description:
** cirecular_buffer
*/

#ifndef CIRCULAR_BUFFER_H_
    #define CIRCULAR_BUFFER_H_

    #include <stddef.h>
    #include <stdbool.h>
    typedef struct circular_buffer_s {
        char *buffer;
        char *head_buffer;
        char *queue_buffer;
        int size;
    } circular_buffer_t;

    /**
     * @brief initialisation of circular buffer structure
     * @param cb a pointer to the circular buffer structure
     * @param size the size of the buffer
     *
    */
    void cb_init(circular_buffer_t *cb, size_t size);
    /**
     * @brief destroy the circular buffer structure and free the memory
     * @param cb a pointer to the circular buffer structure
    */
    void cb_destroy(circular_buffer_t *cb);
    /**
     * @brief add a char to the circular buffer
     * @param str_to_and the char to add
     * @param cb a pointer to the circular buffer structure
    */
    void add_to_buffer(char str_to_and, circular_buffer_t *buffer);
    /**
     * @brief read the circular buffer and return a string if it find a \\n
     * @param cb a pointer to the circular buffer structure
     * @return char* the string read, NULL if no \\n is found
    */
    char *read_circular_buffer_string(circular_buffer_t *cb);
    /**
     * @brief check if the circular buffer is empty
     * @param cb a pointer to the circular buffer structure
     * @return bool true if the buffer is empty, false otherwise
    */
    bool is_buffer_empty(circular_buffer_t *cb);

#endif /* !CIRCULAR_BUFFER_H_ */
