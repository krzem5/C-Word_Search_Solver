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
		o->_fl[i]=UINT16_MAX;
	}
	uint16_t k=0;
	for (uint8_t i=0;i<h;i++){
		for (uint8_t j=0;j<w;j++){
			o->dt[k]=dt[i][j];
			if (o->dt[k]>90){
				o->dt[k]-=32;
			}
			uint8_t l=((uint8_t)o->dt[k])-MIN_LETTER_ID;
			if (o->_fl[l]==UINT16_MAX){
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



uint8_t find_word_search(WordSearch* ws,const char* w,WordSearchWord* o){
	o->w=w;
	char sc=*w;
	if (!sc){
		return 0;
	}
	if (sc>90){
		sc-=32;
	}
	uint16_t l=0;
	uint16_t i=ws->_fl[sc-MIN_LETTER_ID];
	if (i==UINT16_MAX){
		return 0;
	}
	uint16_t e=ws->w*ws->h;
	while (i<e){
		if (ws->dt[i]==sc){
			if (!l){
				char* t=(char*)w+1;
				while (*t){
					t++;
				}
				l=(uint16_t)((uint64_t)(void*)t-(uint64_t)(void*)w)-1;
			}
			uint16_t j=i;
			uint16_t k=1;
			uint16_t m=l;
			char* n=(char*)w+1;
			while (m){
				j+=k;
				m--;
				char c=*n;
				if (c>90){
					c-=32;
				}
				if (c!=ws->dt[j]){
					goto _nxt0;
				}
				n++;
			}
			goto _end;
_nxt0:
			k+=ws->w;
			j=i;
			m=l;
			n=(char*)w+1;
			while (m){
				j+=k;
				m--;
				char c=*n;
				if (c>90){
					c-=32;
				}
				if (c!=ws->dt[j]){
					goto _nxt1;
				}
				n++;
			}
			goto _end;
_nxt1:
			k--;
			j=i;
			m=l;
			n=(char*)w+1;
			while (m){
				j+=k;
				m--;
				char c=*n;
				if (c>90){
					c-=32;
				}
				if (c!=ws->dt[j]){
					goto _nxt2;
				}
				n++;
			}
			goto _end;
_end:
			o->sx=i%ws->w;
			o->sy=i/ws->w;
			o->ex=j%ws->w;
			o->ey=j/ws->w;
			return 1;
		}
_nxt2:
		i++;
	}
	return 0;
}



void free_word_search(WordSearch* ws){
	free(ws);
}
