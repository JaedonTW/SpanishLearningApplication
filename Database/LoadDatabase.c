#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sqlite3.h>

#define MAX_WORD_LENGTH 50

// vocabularyList will load values from the text file
FILE* vocabularyList;

void INSERT_SQL(char* spanish, char* english, char* sqlstatement)
{
	char quote[2] = "\"";
	char comma[2] = ",";
	char InsertStatement[200] = "INSERT INTO VERB (ENG_Infinitive, SPN_Infinitive)\n";
	char ValueStatement[50]   = "VALUES(";
	char End[50]             = ");";

	strcat(InsertStatement,ValueStatement);
	strcat(InsertStatement,quote);
	strcat(InsertStatement,english);
	strcat(InsertStatement,quote);
	strcat(InsertStatement,comma);
	strcat(InsertStatement,quote);
	strcat(InsertStatement,spanish);
	strcat(InsertStatement,quote);
	strcat(InsertStatement,End);
	printf("%s\n",InsertStatement);
	strcpy(sqlstatement,InsertStatement);
}

int main(int argc, char** argv)
{
	char* spanishWord = malloc(sizeof(char) * MAX_WORD_LENGTH);
	char* englishWord = malloc(sizeof(char) * MAX_WORD_LENGTH);
	char* sqlStatement = malloc(sizeof(char) * 200);
		
	vocabularyList = fopen("Words.txt","r");

	while(fgets(spanishWord,MAX_WORD_LENGTH,vocabularyList) != NULL)
	{	
		fgets(englishWord,MAX_WORD_LENGTH,vocabularyList);	

		// remove newline character
		spanishWord[strcspn(spanishWord,"\n")] = 0;
		englishWord[strcspn(englishWord,"\n")] = 0;
	
		INSERT_SQL(spanishWord,englishWord,sqlStatement);
	}
	
	sqlite3* dbConnectionObject;

	int status = sqlite3_open("Vocabulary.db",&dbConnectionObject);
	
	if(status)
		printf("Bad Status: %d\n",status);
	
	free(spanishWord);
	free(englishWord);

	return EXIT_SUCCESS;
}
