#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define ALPHABETIC_SIZE 26
char caesarCipher[]="qwertyuioplkjhgfdsazxcvbnm";
char regularalphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
void monoalphabetic(char*text){
	char ch;
	for(int i=0;text[i] !='\0';++i){
		ch=text[i];
		if(isupper(ch)){
			for(int j=0;j<ALPHABETIC_SIZE;++j){
				if(ch==regularalphabet[j]){
					text[i]=caesarCipher[j];
					break;
				}
			}
		}
		if(islower[ch]){
			for(int j=0;j<ALPHABETIC_SIZE;++j){
				if(ch==tolower(regularalphabet[j])){
					text[i]=tolower(caesarCipher[j]);
					break;
				}
			}
		}
	}
}
int main(){
	char text[100];
	printf("enter the string:");
	fgets(text,sizeof(text),stdin);
	monoalphabetic(text);
	printf("entropy string:%s",text);
	return 0;
}
