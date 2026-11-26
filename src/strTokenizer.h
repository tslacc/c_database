struct StringTokens{
	unsigned int tokenCount;
	unsigned int *tokens;
};
void strTokenize(char *inputStr, struct StringTokens *result);
