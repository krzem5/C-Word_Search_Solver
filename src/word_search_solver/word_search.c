#include <word_search.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>



#define MIN_LETTER_ID 65



WordSearch* create_word_search(uint8_t w,uint8_t h,const char** dt){
	WordSearch* o=malloc(sizeof(WordSearch)+(uint16_t)w*h*sizeof(char));
	o->w=w;
	o->h=h;
	for (uint8_t i=0;i<LETTER_COUNT;i++){
		o->_fl[i]=UINT8_MAX;
	}
	uint16_t k=0;
	for (uint8_t i=0;i<h;i++){
		for (uint8_t j=0;j<w;j++){
			o->dt[k]=dt[i][j]-(dt[i][j]>90?32:0);
			uint8_t l=((uint8_t)o->dt[k])-MIN_LETTER_ID;
			if (o->_fl[l]==UINT8_MAX){
				o->_fl[l]=k;
			}
			k++;
		}
	}
	return o;
}



void print_word_search(WordSearch* ws){
	printf("%hhu x %hhu:\n",ws->w,ws->h);
	uint16_t k=0;
	for (uint8_t i=0;i<ws->h;i++){
		for (uint8_t j=0;j<ws->w;j++){
			if (j){
				putchar(' ');
			}
			putchar(ws->dt[k]);
			k++;
		}
		putchar('\n');
	}
}



WordSearchMove find_word_search(WordSearch* ws,const char* w);



void free_word_search(WordSearch* ws){
	free(ws);
}
