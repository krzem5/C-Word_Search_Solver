#include <word_search.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>



#define MIN_LETTER_ID 65



WordSearch* create_word_search(uint8_t w,uint8_t h,const char** dt){
	WordSearch* o=malloc(sizeof(WordSearch)+(w>h?h:w)*sizeof(char)+(uint16_t)w*h*sizeof(char));
	o->w=w;
	o->h=h;
	for (uint8_t i=0;i<LETTER_COUNT;i++){
		o->_fl[i]=UINT16_MAX;
	}
	o->_w=(char*)(void*)((uint64_t)(void*)o+sizeof(WordSearch)+(uint16_t)w*h*sizeof(char));
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
	uint8_t l=0;
	uint16_t i=ws->_fl[sc-MIN_LETTER_ID];
	if (i==UINT16_MAX){
		return 0;
	}
	uint16_t e=ws->w*ws->h;
	uint8_t mn_sz;
	while (i<e){
		if (ws->dt[i]==sc){
			o->sx=i%ws->w;
			o->sy=i/ws->w;
			if (!l){
				char* t=(char*)w+1;
				char* t2=ws->_w;
				while (*t){
					*t2=*t;
					if (*t2>90){
						(*t2)-=32;
					}
					t++;
					t2++;
				}
				l=(uint8_t)((uint64_t)(void*)t-(uint64_t)(void*)w)-1;
				if (!l){
					o->ex=o->sx;
					o->ey=o->sy;
					return 1;
				}
				mn_sz=(ws->w>ws->h?ws->h:ws->w);
				if (l+1>mn_sz){
					return 0;
				}
				mn_sz-=l+1;
				l--;
			}
			uint16_t j;
			uint8_t k;
			char* m;
			if (o->sx>=ws->w-l-1){
				goto _nxt0;
			}
			j=i+1;
			k=l;
			m=ws->_w;
_loop0:
			if (*m!=ws->dt[j]){
				goto _nxt0;
			}
			if (k){
				j++;
				k--;
				m++;
				goto _loop0;
			}
			goto _end;
_nxt0:
			if (o->sy>=ws->h-l-1){
				goto _nxt1;
			}
			j=i+ws->w;
			k=l;
			m=ws->_w;
_loop1:
			if (*m!=ws->dt[j]){
				goto _nxt1;
			}
			if (k){
				j+=ws->w;
				k--;
				m++;
				goto _loop1;
			}
			goto _end;
_nxt1:
			if (o->sx>mn_sz||o->sy>mn_sz){
				goto _nxt2;
			}
			uint16_t n=ws->w+1;
			j=i+n;
			k=l;
			m=ws->_w;
_loop2:
			if (*m!=ws->dt[j]){
				goto _nxt2;
			}
			if (k){
				j+=n;
				k--;
				m++;
				goto _loop2;
			}
			goto _end;
_end:
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
