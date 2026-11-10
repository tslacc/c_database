#include "strTokenizer.h"
#include <string.h>
#include <stdio.h>
#include <alloca.h>
static inline const char *movePointer(const char *inputStr, const char *const endPos, unsigned int side){
	const char *result = inputStr;
	while(result < endPos && (side^(*result=='\0'))){
		result++;
	}
	return result;
}
static const char *seekNextToken(const char * inputStr, const char *const endPos){
	printf("Seeking next token from pos %p %p\n", inputStr, endPos);
	const char *result = inputStr;
	result = movePointer(result, endPos, 1);
	result = movePointer(result, endPos, 0);
	printf("result is from pos %p %p\n", inputStr, endPos);
	return result;
}
static unsigned int countTokens(const char *inputStr, unsigned int len){
	unsigned int result = 0;
	
	const char *const endPos = inputStr+len;
	printf("counting tokens between %p, %p\n", inputStr, endPos);
	
	inputStr = movePointer(inputStr, endPos, 0);
	const char *nextPos = inputStr;
	printf("i, n, e %p %p %p\n", inputStr, nextPos, endPos);
	while(1){
		nextPos = seekNextToken(inputStr, endPos);
		printf("27. i, n, e %p %p %p\n", inputStr, nextPos, endPos);
		if(nextPos!=inputStr){
			result++;
		}else{
			break;
		}
		inputStr = nextPos;
	}
	return result;
}
static void destroyDelimiters(char *inputStr, unsigned int len){
	for(unsigned int i = 0; i < len; i++){
		if(inputStr[i] == ','||inputStr[i] == ' '){
			inputStr[i] = '\0';
		}
	}
}
void strTokenize(char *inputStr, struct StringTokens *result){
	unsigned int len = strlen(inputStr);
	printf("tokenizing \"%s\" w len %u\n", inputStr, len);
	destroyDelimiters(inputStr, len);
	printf("after destroy \"%.11s\" \n", inputStr);
	result->tokenCount = countTokens(inputStr, len);
	printf("Counted %u tokens\n", result->tokenCount);
	result->tokens = alloca(sizeof(unsigned int)*result->tokenCount);
	const char *pos = inputStr;
	for(unsigned int i = 0; i < result->tokenCount; i++){
		result->tokens[i] = seekNextToken(pos, inputStr+len) - inputStr;
		pos = inputStr+result->tokens[i];
	}
}
