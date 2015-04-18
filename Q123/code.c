#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Word{
	int length, t_index, s_index;
	char w[101];
}Word;

void Quicksort(Word[], int, int);
int Partition(Word[], int, int);
int word_compare(Word, Word);

int main(){
	int size_ignore=0, phase=0, size_title=0, size_word=0;
	int i, j, k, flag, start, t_index, s_index, length;
	char ignore_words[50][11], titles[200][1001];
	char line[1001], *ptr;
	Word words_list[1000];
	/*
		Part of Input
	*/
	while(fgets(line, 1001, stdin)!=NULL){
		if(strcmp(line, "::\n")==0){
			phase = 1;
			continue;
		}
		if(phase==0){
			i = 0;
			while(line[i]!='\n'&&line[i]!='\0'){
				ignore_words[size_ignore][i] = tolower(line[i]);
				i++;
			}
			ignore_words[size_ignore++][i] = '\0';
		}else{
			i = 0;
			while(line[i]!='\n'&&line[i]!='\0'){
				titles[size_title][i] = tolower(line[i]);
				i++;
			}
			titles[size_title++][i] = '\0';
		}
	}
	/*
		Get keywords from all titles.
	*/
	for(i=0; i<size_title; i++){
		start = 0;
		j = 0;
		while(titles[i][j]!='\0'){
			k = 0;
			while(titles[i][j]!=' '&&titles[i][j]!='\0'){
				line[k] = titles[i][j];
				j++; 
				k++;
			}
			j++;
			line[k] = '\0';
			flag = 1;
			for(k=0; k<size_ignore&&flag; k++){
				if(strcmp(line, ignore_words[k])==0)	flag = 0;
			}
			if(flag){
				k = 0;
				while(line[k]!='\0'){
					words_list[size_word].w[k] = line[k];
					k++;
				}
				words_list[size_word].w[k] = '\0';
				words_list[size_word].t_index = i;
				words_list[size_word].length = k;
				words_list[size_word++].s_index = start;
			}
			start = j;
		}
	}
	/*
		Sort all keywords.
	*/
	Quicksort(words_list, 0, size_word-1);
	/*
		Print out all titles ordered by keywords.
	*/
	for(i=0; i<size_word; i++){
		t_index = words_list[i].t_index;
		s_index = words_list[i].s_index;
		length = words_list[i].length;
		j = 0;
		while(titles[t_index][j]!='\0'){
			if(j>=s_index&&j<s_index+length){
				printf("%c", toupper(titles[t_index][j]));
			}else{
				printf("%c", titles[t_index][j]);
			}
			j++;
		}
		printf("\n");
	}
	return 0;
}

void Quicksort(Word words_list[], int left, int right){
	int q;
	if(left < right){
		q = Partition(words_list, left, right);
		Quicksort(words_list, left, q-1);
		Quicksort(words_list, q+1, right);
	}
}

int Partition(Word words_list[], int left, int right){
	Word temp;
	int i, j;
	i = left - 1;
	for(j=left; j<right; j++){
		if(word_compare(words_list[j], words_list[right])<=0){
			i = i + 1;
			temp = words_list[i];
			words_list[i] = words_list[j];
			words_list[j] = temp;
		}
	}
	temp = words_list[i+1];
	words_list[i+1] = words_list[right];
	words_list[right] = temp;
	return i+1;
}

int word_compare(Word a, Word b){
	int cmp = strcmp(a.w, b.w);
	if(cmp==0){
		if(a.t_index<b.t_index){
			return -1;
		}else if(a.t_index==b.t_index){
			if(a.s_index<b.s_index){
				return -1;
			}else if(a.s_index>b.s_index){
				return 1;
			}else{
				/*
					This condition shouldn't happen.
					Just list in case.
				*/
				return 0;
			}
		}else{
			return 1;
		}
	}else{
		return cmp;
	}
}
