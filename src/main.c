#include <word_search.h>
#include <stdio.h>
#include <windows.h>



int main(int argc,const char** argv){
	SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS);
	LARGE_INTEGER f;
	LARGE_INTEGER s;
	LARGE_INTEGER e;
	QueryPerformanceFrequency(&f);
	const char* dt[]={"aBc","dEF","GhI"};
	WordSearch* ws=create_word_search(3,3,dt);
	print_word_search(ws);
	WordSearchWord w;
	QueryPerformanceCounter(&s);
	uint8_t o=find_word_search(ws,"aef",&w);
	QueryPerformanceCounter(&e);
	if (o){
		printf("Word: %hhu, %hhu -> %hhu, %hhu\n",w.sx,w.sy,w.ex,w.ey);
	}
	else{
		printf("Word not Found!\n");
	}
	printf("Time: %.6fs\n",(e.QuadPart-s.QuadPart)*1e6/f.QuadPart*1e-6);
	free_word_search(ws);
	return 0;
}
