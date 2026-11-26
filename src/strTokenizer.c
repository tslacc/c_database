#include "strTokenizer.h"
#include <string.h>
#include <stdio.h>
#include <alloca.h>
#include <stdlib.h>
static inline const char *movePointer(const char *inputStr, const char *const endPos, unsigned int side){
	const char *result = inputStr;
	while(result < endPos && (side^(*result=='\0'))){
		result++;
	}
	return result;
}
static const char *seekNextToken(const char * inputStr, const char *const endPos){
	const char *result = inputStr;
	result = movePointer(result, endPos, 1);
	result = movePointer(result, endPos, 0);
	return result;
}
static unsigned int countTokens(const char *inputStr, unsigned int len){
	unsigned int result = 0;
	const char *const endPos = inputStr+len;
	inputStr = movePointer(inputStr, endPos, 0);
	const char *nextPos = inputStr;
	while(1){
		nextPos = seekNextToken(inputStr, endPos);
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
	destroyDelimiters(inputStr, len);
	result->tokenCount = countTokens(inputStr, len);
	result->tokens = malloc(sizeof(unsigned int)*result->tokenCount);
	const char *pos = inputStr;
	movePointer(pos, inputStr+len, 0);
	result->tokens[0] = pos-inputStr;
	for(unsigned int i = 1; i < result->tokenCount; i++){
		result->tokens[i] = seekNextToken(pos, inputStr+len) - inputStr;
		pos = inputStr+result->tokens[i];
	}
}
