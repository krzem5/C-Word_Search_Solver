#ifndef __WORD_SEARCH_H__
#define __WORD_SEARCH_H__ 1
#include <stdint.h>



#define LETTER_COUNT 26



typedef struct __WORD_SEARCH WordSearch;
typedef struct __WORD_SEARCH_WORD WordSearchWord;



struct __WORD_SEARCH{
	uint8_t w;
	uint8_t h;
	uint16_t _fl[LETTER_COUNT];
	char* _w;
	char dt[];
};



struct __WORD_SEARCH_WORD{
	const char* w;
	uint8_t sx;
	uint8_t sy;
	uint8_t ex;
	uint8_t ey;
};



WordSearch* create_word_search(uint8_t w,uint8_t h,const char** dt);



void print_word_search(WordSearch* ws);



uint8_t find_word_search(WordSearch* ws,const char* w,WordSearchWord* o);



void free_word_search(WordSearch* ws);



#endif
