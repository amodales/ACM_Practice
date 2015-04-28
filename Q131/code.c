#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Card{
	int rank;
	char suit;
}Card;

typedef struct Pattern{
	Card cards[5];
}Pattern;

int check[5], count;

int Recognize(Pattern);
void Get_Combination(int [10][5], int, int, int);
void Build_Pattern(Pattern[], Card[]);

int main(){
	Card ret, cards[10];
	Pattern all[32];
	int i, j, max, temp;
	char line[31];
	while(fgets(line, 31, stdin)!=NULL){
		i = 0;
		j = 0;
		/*
			Input
		*/
		while(line[i]!='\n'){
			switch(line[i]){
				case 'A':
					ret.rank = 1;
					break;
				case 'T':
					ret.rank = 10;
					break;
				case 'J':
					ret.rank = 11;
					break;
				case 'Q':
					ret.rank = 12;
					break;
				case 'K':
					ret.rank = 13;
					break;
				default:
					ret.rank = line[i] - '0';
			}
			i++;
			ret.suit = line[i];
			i++;
			if(line[i]==' ')	i++;
			cards[j++] = ret;
		}
		/*
			Process
		*/
		Build_Pattern(all, cards);
		max = Recognize(all[0]);
		for(i=1; i<32; i++){
			temp = Recognize(all[i]);
			if(temp>max)	max = temp;
		}
		/*
			Output
		*/
		printf("Hand:");
		for(i=0; i<5; i++){
			switch(cards[i].rank){
				case 1:
					printf(" A");
					break;
				case 10:
					printf(" T");
					break;
				case 11:
					printf(" J");
					break;
				case 12:
					printf(" Q");
					break;
				case 13:
					printf(" K");
					break;
				default:
					printf(" %d", cards[i].rank);
			}
			printf("%c", cards[i].suit);
		}
		printf(" Deck:");
		for(i=5; i<10; i++){
			switch(cards[i].rank){
				case 1:
					printf(" A");
					break;
				case 10:
					printf(" T");
					break;
				case 11:
					printf(" J");
					break;
				case 12:
					printf(" Q");
					break;
				case 13:
					printf(" K");
					break;
				default:
					printf(" %d", cards[i].rank);
			}
			printf("%c", cards[i].suit);
		}
		printf(" Best hand: ");
		switch(max){
			case 0:
				printf("highest-card\n");
				break;
			case 1:
				printf("one-pair\n");
				break;
			case 2:
				printf("two-pairs\n");
				break;
			case 3:
				printf("three-of-a-kind\n");
				break;
			case 4:
				printf("straight\n");
				break;
			case 5:
				printf("flush\n");
				break;
			case 6:
				printf("full-house\n");
				break;
			case 7:
				printf("four-of-a-kind\n");
				break;
			case 9:
				printf("straight-flush\n");
				break;
		}
	}
	return 0;
}

void Build_Pattern(Pattern all[], Card cards[]){
	Pattern ret;
	int combination[10][5];
	int i, j, k, l, index=0;
	for(i=0; i<=5; i++){
		/*
			Choose i cards in deck to replace cards in hand.
		*/
		for(j=0; j<i; j++){
			ret.cards[j] = cards[5+j];
		}
		/*
			Get all (5-i)-combinations of {0, 1, 2, 3, 4}
		*/
		memset(check, 0, sizeof(check));
		count = 0;
		Get_Combination(combination, 5-i, 0, 0);
		for(k=0; k<count; k++){
			j = i;
			for(l=0; l<5-i; l++){
				ret.cards[j++] = cards[combination[k][l]];
			}
			all[index++] = ret;
		}
	}
}

void Get_Combination(int comb[10][5], int max, int level, int sel){
	int i, j;
	if(sel!=max&&level!=5){
		check[level] = 1;
		Get_Combination(comb, max, level+1, sel+1);
		check[level] = 0;
		Get_Combination(comb, max, level+1, sel);
	}
	if(sel==max){
		for(i=0, j=0; i<5; i++){
			if(check[i]==1){
				comb[count][j++] = i;
			}
		}
		count++;
	}
}

int Recognize(Pattern a){
	int count1[13], count2[4], i, j, check;
	int ret = 0, pair = 0, three = 0, four = 0;
	memset(count1, 0, sizeof(count1));
	memset(count2, 0, sizeof(count2));
	for(i=0; i<5; i++){
		count1[a.cards[i].rank-1]++;
		switch(a.cards[i].suit){
			case 'C':
				count2[0]++;
				break;
			case 'H':
				count2[1]++;
				break;
			case 'D':
				count2[2]++;
				break;
			case 'S':
				count2[3]++;
				break;
		}
		if(count1[a.cards[i].rank-1]==2){
			pair++;
		}
		if(count1[a.cards[i].rank-1]==3){
			three++;
			pair--;
		}
		if(count1[a.cards[i].rank-1]==4){
			three--;
			four++;
		}
	}
	/*
		highest-card    = 0000 = 0
		one-pair        = 0001 = 1
		two-pairs       = 0010 = 2
		three-of-a-kind = 0011 = 3
		straight        = 0100 = 4
		flush           = 0101 = 5
		full-house      = 0110 = 6
		four-of-a-kind  = 0111 = 7
		straight-flush  = 1001 = 9
		P.S. Letting straight-flush be 9 is 
		     for simplifing calculation.
	*/
	if(pair==1&&three==0){
		ret = 1;
	}else if(pair==2){
		ret = 2;
	}else if(three==1&&pair==0){
		ret = 3;
	}else if(three==1&&pair==1){
		ret = 6;
	}else if(four==1){
		ret = 7;
	}else{
		for(i=0; i<4; i++){
			if(count2[i]==5){
				ret += 5;
			}
		}
		for(i=0; i<10; i++){
			check = 1;
			for(j=0; j<5; j++){
				if(count1[(i+j)%13]!=1){
					check = 0;
				}
			}
			if(check){
				ret += 4;
				break;
			}
		}
	}
	return ret;
}
