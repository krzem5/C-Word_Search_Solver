#include <word_search.h>



int main(int argc,const char** argv){
	const char* dt[]={"aBc","dEF","GhI"};
	WordSearch* ws=create_word_search(3,3,dt);
	print_word_search(ws);
	free_word_search(ws);
	return 0;
}
