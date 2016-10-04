
#ifndef STRING_INC
#define STRING_INC

typedef struct String {
    int len;
    int capacity;
    char* chars;
} String;

String* newString(char* src);

#endif // STRING_INC
