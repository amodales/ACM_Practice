#include <stdio.h>
#include <stdlib.h>

typedef enum {NOT, A, MOD, BA, DA, LA, NAM, PREDA, 
		VPRED, STATE, PREDSTR, PREDNAM, PREDS, PREDC, SENT, PERIOD,
		FIN, END_PROGRAM, ERROR} Type;

Type lookahead, stack[1000];
int size, st[1000];

Type getNextToken();
Type peek();

int is_vowel(char);

void GoTo_State(Type, int);
void state_0(Type);
void state_1();
void state_2(Type);
void state_3(Type);
void state_4();
void state_5(Type);
void state_6(Type);
void state_7(Type);
void state_8(Type);
void state_9();
void state_10(Type);
void state_11();
void state_12(Type);
void state_13();
void state_14(Type);
void state_15(Type);
void state_16(Type);
void state_17(Type);
void state_18(Type);

int main(){
	int i;
	lookahead = NOT;
	while(1==1){
		size = 0;
		state_0(getNextToken());
		if(stack[0]==FIN&&peek()==PERIOD){
			printf("Good\n");
		}else{
			printf("Bad!\n");
			while(peek()!=PERIOD){
				getNextToken();
			}
		}
		getNextToken();
		if(peek()==END_PROGRAM)	break;
	}
	return 0;
}

Type peek(){
	Type ret;
	int index = 0;
	char c, line[500];
	int accept = 0;
	if(lookahead!=NOT)	return lookahead;
	do{
		c = fgetc(stdin);
		switch(c){
			case ' ': case '\n':
				if(index!=0)	accept = 1;
				break;
			case '#':
				lookahead = END_PROGRAM;
				accept = 1;
				break;
			case EOF:
				/*
					This condition shouldn't happen.
				*/
				accept = 1;
				break;
			case '.':
				if(index==0)	lookahead = PERIOD;
				else ungetc(c, stdin);
				accept = 1;
				break;
			default:
				if(c>='a'&&c<='z')	line[index++] = c;
				break;
		}
	}while(!accept);
	if(index!=0){
		if(is_vowel(line[index-1])){
			if(index==1){
				lookahead = A;
			}else if(index==2){
				if(line[0]=='g')	lookahead = MOD;
				if(line[0]=='b')	lookahead = BA;
				if(line[0]=='d')	lookahead = DA;
				if(line[0]=='l')	lookahead = LA;
			}else if(index==5){
				if(!is_vowel(line[0])&&!is_vowel(line[1])&&is_vowel(line[2])&&!is_vowel(line[3])){
					lookahead = PREDA;
				}else if(!is_vowel(line[0])&&is_vowel(line[1])&&!is_vowel(line[2])&&!is_vowel(line[3])){
					lookahead = PREDA;
				}else{
					lookahead = ERROR;
				}
			}else{
				lookahead = ERROR;
			}
		}else{
			lookahead = NAM;
		}
	}
	return lookahead;
}

Type getNextToken(){
	Type ret;
	ret = peek();
	lookahead = NOT;
	return ret;
}

int is_vowel(char c){
	switch(c){
		case 'a': case 'e': case 'i': case 'o': case 'u':
			return 1;
			break;
		default:
			return 0;
	}
}

void GoTo_State(Type tok, int state){
	switch(state){
		case 0:	state_0(tok); break;
		case 2: state_2(tok); break;
		case 3: state_3(tok); break;
		case 5: state_5(tok); break;
		case 6: state_6(tok); break;
		case 7: state_7(tok); break;
		case 8: state_8(tok); break;
		case 10: state_10(tok); break;
		case 12: state_12(tok); break;
		case 14: state_14(tok); break;
		case 15: state_15(tok); break;
		case 16: state_16(tok); break;
		case 17: state_17(tok); break;
		case 18: state_18(tok); break;
		default:
			printf("Are you fucking kidding me? %d\n\n", state);
	}
}

void state_0(Type tok){
	stack[size] = tok;
	st[size++] = 0;
	switch(tok){
		case SENT:
			stack[size-1] = FIN;
			break;
		case STATE: case PREDC:
			state_1();
			break;
		case PREDNAM:
			state_2(getNextToken());
			break;
		case LA:
			state_3(getNextToken());
			break;
		case NAM:
			state_4();
			break;
		case DA:
			state_5(getNextToken());
			break;
		default:
			lookahead = tok;
	}
}

void state_1(){
	GoTo_State(SENT, st[--size]);
}

void state_2(Type tok){
	stack[size] = tok;
	st[size++] = 2;
	switch(tok){
		case VPRED:
			state_6(getNextToken());
			break;
		case MOD:
			state_14(getNextToken());
			break;
		case BA:
			state_7(getNextToken());
			break;
		default:
			lookahead = tok;
	}
}

void state_3(Type tok){
	stack[size] = tok;
	st[size++] = 3;
	switch(tok){
		case PREDSTR:
			state_8(getNextToken());
			break;
		case PREDA:
			state_9();
			break;
		default:
			lookahead = tok;
	}
}

void state_4(){
	GoTo_State(PREDNAM, st[--size]);
}

void state_5(Type tok){
	stack[size] = tok;
	st[size++] = 5;
	switch(tok){
		case PREDS:
			state_10(getNextToken());
			break;
		case PREDSTR:
			state_16(getNextToken());
			break;
		case PREDA:
			state_9();
			break;
		default:
			lookahead = tok;
	}
}

void state_6(Type tok){
	switch(tok){
		case PREDNAM:
			stack[size] = tok;
			st[size++] = 6;
			state_11();
			break;
		case LA:
			stack[size] = tok;
			st[size++] = 6;
			state_3(getNextToken());
			break;
		case NAM:
			stack[size] = tok;
			st[size++] = 6;
			state_4();
			break;
		case PERIOD:
			lookahead = tok;
			size = size - 2;
			GoTo_State(STATE, st[size]);
			break;
	}
}

void state_7(Type tok){
	stack[size] = tok;
	st[size++] = 7;
	switch(tok){
		case PREDS:
			state_12(getNextToken());
			break;
		case PREDSTR:
			state_16(getNextToken());
			break;
		case PREDA:
			state_9();
			break;
		default:
			lookahead = tok;
	}
}

void state_8(Type tok){
	switch(tok){
		case PREDA:
			stack[size] = tok;
			st[size++] = 8;
			state_13();
			break;
		case PERIOD: case BA: case MOD:
			lookahead = tok;
			size = size - 2;
			GoTo_State(PREDNAM, st[size]);
			break;
	}
}

void state_9(){
	GoTo_State(PREDSTR, st[--size]);
}

void state_10(Type tok){
	switch(tok){
		case A:
			stack[size] = tok;
			st[size++] = 10;
			state_15(getNextToken());
			break;
		case PERIOD:
			lookahead = tok;
			size = size - 2;
			GoTo_State(PREDC, st[size]);
			break;
	}
}

void state_11(){
	size = size - 3;
	GoTo_State(STATE, st[size]);
}

void state_12(Type tok){
	switch(tok){
		case A:
			stack[size] = tok;
			st[size++] = 12;
			state_15(getNextToken());
			break;
		case PERIOD:
			lookahead = tok;
			size = size - 3;
			GoTo_State(PREDC, st[size]);
			break;
	}
}

void state_13(){
	size = size - 2;
	GoTo_State(PREDSTR, st[size]);
}

void state_14(Type tok){
	stack[size] = tok;
	st[size++] = 14;
	switch(tok){
		case PREDSTR:
			state_18(getNextToken());
			break;
		case PREDA:
			state_9();
			break;
		default:
			lookahead = tok;
	}
}

void state_15(Type tok){
	stack[size] = tok;
	st[size++] = 15;
	switch(tok){
		case PREDSTR:
			state_17(getNextToken());
			break;
		case PREDA:
			state_9();
			break;
		default:
			lookahead = tok;
	}
}

void state_16(Type tok){
	switch(tok){
		case PREDA:
			stack[size] = tok;
			st[size++] = 16;
			state_13(getNextToken());
			break;
		case A: case PERIOD:
			lookahead = tok;
			GoTo_State(PREDS, st[--size]);
			break;
	}
}

void state_17(Type tok){
	switch(tok){
		case PREDA:
			stack[size] = tok;
			st[size++] = 17;
			state_13(getNextToken());
			break;
		case A: case PERIOD:
			lookahead = tok;
			size = size - 3;
			GoTo_State(PREDS, st[size]);
			break;
	}
}

void state_18(Type tok){
	switch(tok){
		case PREDA:
			stack[size] = tok;
			st[size++] = 18;
			state_13(getNextToken());
			break;
		case LA: case NAM: case PERIOD:
			lookahead = tok;
			size = size - 2;
			GoTo_State(VPRED, st[size]);
			break;
	}
}
