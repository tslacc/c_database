#include "strTokenizer.h"
#include <string.h>
#include <alloca.h>
static inline void movePointer(const char *inputStr, const char *const endPos, unsigned int side){
	while(inputStr < endPos && (side^(*inputStr=='\0'))){
		inputStr++;
	}
}
static const char *seekNextToken(const char *const inputStr, const char *const endPos){
	const char *result = inputStr;
	movePointer(result, endPos, 1);
	movePointer(result, endPos, 0);
	return result;
}
static unsigned int countTokens(const char *inputStr, unsigned int len){
	unsigned int result = 0;
	const char *const endPos = inputStr+len;
	
	movePointer(inputStr, endPos, 0);
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
	result->tokens = alloca(sizeof(unsigned int)*result->tokenCount);
	const char *pos = inputStr;
	for(unsigned int i = 0; i < result->tokenCount; i++){
		result->tokens[i] = seekNextToken(pos, inputStr+len) - inputStr;
		pos = inputStr+result->tokens[i];
	}
}
