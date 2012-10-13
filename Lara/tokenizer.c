/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>


/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */


typedef struct TokenizerT_ {
	char* sep;
	char* string;
	char* currPos;
	int current;
	
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
		
	if (separators == NULL || ts == NULL){
		return NULL;
	}
	
	tk=(TokenizerT*)malloc(sizeof(TokenizerT));
	//copy and malloc separators into tk
	tk->sep= strdup(separators);
	//copy and malloc ts into tk
	tk->string= strdup(ts);
 	tk->currPos=tk->string;
 	tk->current=0;
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
	char* nextChar = tk->currPos;
	char* token = NULL;
	//char* temp;
	//int length = 0;
	int i, j;
	//int copy = 0;
	int length = 0;
	
	for(j=0;j<strlen(tk->sep);j++){
		for (i=0;i<strlen(tk->currPos);i++){
			if ((tk->currPos[i] == tk->sep[j])||tk->currPos[i]=='\0')
			{
				if (length == 0)
				{
					continue;
				}
				else
				{
					token= (char*)malloc(length+1);
					strncpy(token,tk->currPos,length);
					token[length+1]='\0';
					//nextChar=nextChar+1;
					nextChar=nextChar+length;
					tk->currPos=nextChar;
					return token;
				}
			}
			else
			{
				length++;
			}
		}
	}
	
	/*while ((nextChar[0]=='\0' && copy ==1) || nextChar[0]!='\0'){

		for(i=0;i<strlen(tk->sep);i++){
			if (nextChar[0]==tk->sep[i] || nextChar[0]=='\0'){
				if (copy==0){
					nextChar=nextChar+1;
					tk->currPos = nextChar;
					break;
				}
				else{
					length= (strlen(tk->currPos)-strlen(nextChar));
					token= (char*)malloc(length+1);
					strncpy(token,tk->currPos,length);
					token[length+1]='\0';
					tk->currPos = nextChar+1;
					return token;
				}
			}
			if(nextChar[i+1]=='\0')
				copy=1;
		}
		if (copy==1 || strcmp(nextChar,tk->currPos) ==0){
			copy=1;
			nextChar=nextChar+1;
		}
		
	}*/
	

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
	char* token;
	
	if (argc!=3){
		puts("Error: Invalid number of arguments!!");
		return -1;
	}

	tk = TKCreate(argv[1],argv[2]);
	
	do{
		token = TKGetNextToken(tk);
		if(token!=0){
			printf("%s\n",token);
			free(token);
		}
	
	}while(token!=0);
	
	TKDestroy(tk);
  return 0;
}
