#ifndef LAB1_LLIB_DIALOGUE_MENU_HPP
#define LAB1_LLIB_DIALOGUE_MENU_HPP

#include "encoder.hpp"

bool choose_action(TEncoder &encoder);
bool choose_string_type(TEncoder &encoder, bool encode=1);
bool dialogue_action_on_string(TEncoder &encoder, bool encode=1);
bool dialogue_action_on_c_string(TEncoder &encoder, bool encode=1);
bool dialogue_action_on_char_array(TEncoder &encoder, bool encode=1);

#endif
