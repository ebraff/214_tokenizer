/* 
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <wchar.h>


/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */
typedef struct TokenizerT_ {
	char* sep;
	char* string;
	char* currPos;
	
} TokenizerT;


/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 * 
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *separators, char *ts) {
	
	TokenizerT *tk;
	int i, j, t;
	char *temp = (char*) malloc(5);	
	j = 0;
	if (separators == NULL || ts == NULL){
		return NULL;
	}	
	
	tk=(TokenizerT*)malloc(sizeof(TokenizerT));
	tk->sep=(char*)malloc(strlen(separators));
	tk->string=(char*)malloc(strlen(ts));
	
	for(i = 0; i < strlen(separators); i++){
		
		if (separators[i] == '\\')
		{
			i++;
			switch(separators[i]){
				case 'n':
					tk->sep[j] = '\n';
					break;
				case 'v':
					tk->sep[j] = '\v';
					break;
				case 't':
					tk->sep[j] = '\t';
					break;
				case 'b':
					tk->sep[j] = '\b';
					break;
				case 'r':
					tk->sep[j] = '\r';
					break;
				case 'f':
					tk->sep[j] = '\f';
					break;
				case 'a':
					tk->sep[j] = '\a';
					break;
				case '\\':
					tk->sep[j] = '\\';
					break;
				case '?':
					tk->sep[j] = '\?';
					break;
				case '\'':
					tk->sep[j] = '\'';
					break;
				case '"':
					tk->sep[j] = '\"';
					break;
				case '0':	//octal \000					
					strncpy(temp+1, separators+i, 3);
					temp[0]='0';
					temp[4] = '\0';	
					if(strcmp(temp,"0039")>0 && strcmp(temp,"0078")<0) /*Only puts characters between 0039 and 0078 (the ones that can be easily printed)
																		*into a single char*/
					{
						sscanf(temp, "%o",&t); /*--------------scans the string into a single octal character*/
						tk->sep[j]=t;
						i+=2;
					}else{
						i--;
						j--;
					}
									 
					break;
				case '1':	//octal \100
					strncpy(temp+1, separators+i, 3);
					temp[0]='0';
					temp[4] = '\0';	
					if(strcmp(temp,"0099")>0 && strcmp(temp,"0177")<0) /*Only puts characters between 0099 and 0177 (the ones that can be easily printed)
																		*into a single char*/
					{
						sscanf(temp, "%o",&t); /*--------------scans the string into a single octal character*/
						tk->sep[j]=t;
						i+=2;
					}else{
						i--;
						j--;
					}
					break;
				case 'x':	//hex	\xhh
					strncpy(temp+1, separators+i, 3);
					temp[0] = '0';
					temp[4] = '\0';
					if(strcmp(temp,"0x1F")>0 && strcmp(temp,"0x7F")<0) /*Only puts characters between 0x1F and 0x7F (the ones that can be easily printed)
																		*into a single char*/
					{
						sscanf(temp, "%x", &t); /*--------------scans the string into a single hexidecimal character*/
						tk->sep[j]=t;
						i+=2;
					}else{
						i--;
						j--;
					}
					
					break;
				default:
					i--;
					j--;
					break;
			}
		}
		else /*not a special case*/
		{
			tk->sep[j]=separators[i];
		}
		j++;
	}
	tk->sep[j] = '\0';
	
	
	/*SAME THING FOR TS*/
	j = 0;
	for(i = 0; i < strlen(ts); i++){
		
		if (ts[i] == '\\')
		{
			i++;
			switch(ts[i]){
				case 'n':
					tk->string[j] = '\n';
					break;
				case 'v':
					tk->string[j] = '\v';
					break;
				case 't':
					tk->string[j] = '\t';
					break;
				case 'b':
					tk->string[j] = '\b';
					break;
				case 'r':
					tk->string[j] = '\r';
					break;
				case 'f':
					tk->string[j] = '\f';
					break;
				case 'a':
					tk->string[j] = '\a';
					break;
				case '\\':
					tk->string[j] = '\\';
					break;
				case '?':
					tk->string[j] = '\?';
					break;
				case '\'':
					tk->string[j] = '\'';
					break;
				case '"':
					tk->string[j] = '\"';
					break;
				case '0':	//octal \000					
					strncpy(temp+1, ts+i, 3);
					temp[0]='0';
					temp[4] = '\0';	
					if(strcmp(temp,"0039")>0 && strcmp(temp,"0078")<0) /*Only puts characters between 0039 and 0078 (the ones that can be easily printed)
																		*into a single char*/
					{
						sscanf(temp, "%o",&t); /*--------------scans the string into a single octal character*/
						tk->string[j]=t;
						i+=2;
					}else{
						i--;
						j--;
					}
									 
					break;
				case '1':	//octal \100
					strncpy(temp+1, ts+i, 3);
					temp[0]='0';
					temp[4] = '\0';	
					if(strcmp(temp,"0099")>0 && strcmp(temp,"0177")<0) /*Only puts characters between 0099 and 0177 (the ones that can be easily printed)
																		*into a single char*/
					{
						sscanf(temp, "%o",&t);/*--------------scans the string into a single octal character*/
						tk->string[j]=t;
						i+=2;
					}else{
						i--;
						j--;
					}
					break;
				case 'x':	//hex	\xhh
					strncpy(temp+1, ts+i, 3);
					temp[0] = '0';
					temp[4] = '\0';
					if(strcmp(temp,"0x1F")>0 && strcmp(temp,"0x7F")<0) /*Only puts characters between 0x1F and 0x7F (the ones that can be easily printed)
																		*into a single char*/
					{
						sscanf(temp, "%x", &t); /*--------------scans the string into a single hexidecimal character*/
						tk->string[j]=t;
						i+=2;
					}else{
						i--;
						j--;
					}
					
					break;
				default:
					i--;
					j--;
					break;
			}
		}
		else /*not a special case*/
		{
			tk->string[j]=ts[i];
		}
		j++;
		
	}
	tk->string[j] = '\0';
 	tk->currPos=tk->string;
 	free(temp);
 	return tk;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
	free(tk->sep);
	free(tk->string);
	free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {
	char* delim;
	char* token;
	int length;
	
	/*points to first instance of a delimiter in currPos*/
	delim = strpbrk(tk->currPos,tk->sep);
	
	/*if the delimiter isn't null and the 2nd index isn't a string end, then the last letter is a delimeter*/
	while(delim!=NULL && tk->currPos[1]!='\0'){		
		if(delim!=tk->currPos){ /*--------------------------found a delimiter and it's after the current char*/
			length= (strlen(tk->currPos)-strlen(delim)); /*-token's length is the current position's pointer - location of delimeter*/
			token= (char*)malloc(length+1);
			strncpy(token,tk->currPos,length); /*-----------copy up to length into token*/
			token[length]='\0'; /*--------------------------add '\0' to end of current token string*/
			tk->currPos = delim+1; /*-----------------------increments pointer*/
			return token;	
			}
		else{ /*--------------------------------------------currently on a delimeter; delimeter is at beginning of current string*/
			tk->currPos = tk->currPos+1; delim = strpbrk(tk->currPos,
			tk->sep); /*------------------------------------takes in 2 strings; gives back first occurrence*/
			}
		}
	/*if you're not on the null terminator and you're past the last deliminator, there has to be more
	prints rest of string*/
	if (tk->currPos[0]!='\0'&& tk->currPos!=delim){
		token = strdup(tk->currPos);
		tk->currPos=tk->currPos+strlen(tk->currPos);
		return token;
	}
  return 0;
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv){
	TokenizerT *tk;
	int size;
	char* token;
	
	if (argc!=3){
		puts("Error: Invalid number of arguments!!!");
		return -1;
	}
	
	size=strlen(argv[1]);	
	tk = TKCreate(argv[1],argv[2]); /*malloc the struct and substitute special characters*/
	
	do{ /*----------------------------get each token at a time, print them, and free them*/
		token = TKGetNextToken(tk);
		if(token!=0){
			printf("%s\n",token);
			free(token);
		}
	
	}while(token!=0);
	
	TKDestroy(tk); /*----------------free the rest of the struct*/
  return 0;
}
