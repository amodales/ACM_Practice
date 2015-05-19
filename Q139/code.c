#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct com{
	char code[7];
	int length;
	char name[26];
	double price;
}Company;

int Search(Company [], char [], int, int);
int code_compare(char [], Company);
int GetPhoneNumLength(char [], int *, int *);

int main(){
	Company i_com[1000], n_com[1000], temp;
	int i_size = 0, n_size = 0, i, j, m, n, num, length;
	char line[1000], *str, phone[17];
	/*
		Input
	*/
	while(fgets(line, 1000, stdin)!=NULL){
		if(strcmp(line, "000000\n")==0)	break;
		i = 0;
		while(line[i]!=' '){
			temp.code[i] = line[i];
			i++;
		}
		temp.code[i] = '\0';
		temp.length = i++;
		j = 0;
		while(line[i]!='$'){
			temp.name[j++] = line[i++];
		}
		temp.name[j] = '\0';
		i++;
		num = 0;
		while(line[i]!='\n'){
			num = num * 10 + line[i] - '0';
			i++;
		}
		temp.price = (double) num / 100;
		if(temp.code[0]=='0'&&temp.code[1]=='0'&&temp.length>=3&&temp.length<=5){
			i_com[i_size++] = temp;
		}else{
			n_com[n_size++] = temp;
		}
	}
	/*
		Telphone Log
	*/
	while(GetPhoneNumLength(phone, &num, &length)){
		if(phone[0]!='0'){
			/*	Local, Free	*/
			printf("%-16s%-25s%10s%5d%6.2f%7.2f\n", phone, "Local", phone, num, 
					0.0, 0.0);
		}else{
			/*	Non-Local, Not Free	*/
			i = Search(i_com, phone, i_size, 0);
			j = Search(n_com, phone, n_size, 1);
			if(i!=-1&&j==-1){
				/*
					International
				*/	
				for(m=i_com[i].length, n=0; m<length; m++){
					line[n++] = phone[m];
				}
				line[n] = '\0';
				printf("%-16s%-25s%10s%5d%6.2f%7.2f\n", phone, i_com[i].name, line, num,
						i_com[i].price, i_com[i].price*num);
			}else if(i==-1&&j!=-1){
				/*
					National
				*/
				for(m=n_com[j].length, n=0; m<length; m++){
					line[n++] = phone[m];
				}
				line[n] = '\0';
				printf("%-16s%-25s%10s%5d%6.2f%7.2f\n", phone, n_com[j].name, line,
						num, n_com[j].price, n_com[j].price*num);
			}else{
				printf("%-16s%-25s%10s%5d%6s%7.2f\n", phone, "Unknown", "", num, "",
						-1.00);
			}
		}
	}
	return 0;
}

int code_compare(char phone[], Company com){
	int i=0;
	while(i<com.length){
		if(phone[i]=='\0'||phone[i]<com.code[i]){
			return -1;
		}
		if(phone[i]>com.code[i]){
			return 1;
		}
		i++;	
	}
	return 0;
}

int Search(Company com[], char phone[], int size, int mode){
	int i, ret = -1, len = strlen(phone), left, right;
	left = 4;
	right = (mode==0)? 10: 7;
	for(i=0; i<size; i++){
		if(code_compare(phone, com[i])==0){
			if((len - com[i].length)>=left&&(len - com[i].length)<=right){
				if(ret==-1){
					ret = i;
				}else{
					return -1;
				}
			}
		}
	}
	return ret;
}

int GetPhoneNumLength(char phone[], int *num, int *length){
	int n=0, i=0;
	char ch = fgetc(stdin);
	if(ch=='#')	return 0;
	phone[i++] = ch;
	ch = fgetc(stdin);
	while(ch!=' '&&ch!='\n'){
		phone[i++] = ch;
		ch = fgetc(stdin);
	}
	phone[i] = '\0';
	*length = i;
	while(ch==' '||ch=='\n'){
		ch = fgetc(stdin);
	}
	while(ch!='\n'&&ch!=' '){
		n = n * 10 + ch - '0';
		ch = fgetc(stdin);
	}
	*num = n;
	return 1;
}
