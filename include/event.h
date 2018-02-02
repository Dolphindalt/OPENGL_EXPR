#ifndef EVENT_H
#define EVENT_H

extern bool key_up, key_down, key_left, key_right, key_lshift, key_z, key_x;

void handle_input(bool &running);

#endif