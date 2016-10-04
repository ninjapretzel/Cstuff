
#include "str.h"

void String_ctor(String* this, char* ch) {
    this->len = strlen(ch);
    char* copy = malloc(len*sizeof(char));
    if (copy) {
        this->capacity = this->len;

    }


}

void String_dtor(String* this) {
    free(this->chars);
    free(this);
}

String newString(char* ch) {
    String* str = malloc(sizeof(String));
    String_ctor(str, ch);
    return str
}

void kill(String* this) { String_dtor(this); }
