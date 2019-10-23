#include <stdio.h>     //stdio.h의 헤더파일을 포함한다.
#include <stdlib.h>     //stdlib.h의 헤더파일을 포함한다.
#include <string.h>     //string.h의 헤더파일을 포함한다.

int main(void)
{
	char command[1000];     //크기가 1000인 char형 command배열을 선언한다.
	char executingList[10][1000];    //세로 크기가 10, 가로 크기가 1000인 char형 2차원 배열 executingList을 선언한다.
	char *executingListPtr[10];    //크키가 10인 char형 포인터배열 executingListPtr을 선언한다.
	
	while (1)    //무한루프를 돈다.
	{
		printf("$ ");	   //$를 출력한다.
		gets(command);	   //Enter키를 누를때까지 입력한 모든 문자가 command배열에 할당된다. 

		char *ptr = strtok(command," ");   //command에서 공백 문자를 기준으로 문자열을 자르고, 자른 문자열을 char형 포인터 ptr에 반환한다.

		if (ptr == NULL) continue;	  //반환값이 NULL값이면 반복문의 처음으로 돌아간다.
		printf ("StrTok:%s\r\n",ptr);   //ptr의 문자열을 출력한다.
		strcpy(executingList[0],ptr);	//ptr의 문자열을 인덱스가 0인 배열 executingList로 복사한다.
		executingListPtr[0]=&executingList[0][0];   //배열 executingList[0][0]의 주솟값을 executingListPtr[0]에 넣는다.

		int numberOfToken=0;   // int형 numberOfToken을 값을 0으로한다.
		for (numberOfToken=1;numberOfToken<9;numberOfToken++) //numberOfToken의 값을 1로하고, 값이 9미만이 될때까지, 값을 1씩 증가하면서 반복한다.
		{
			ptr = strtok(NULL," ");   // 다음 공백 문자를 기준으로 문자열을 잘라서 ptr포인터에 반환한다.
			if (ptr == NULL)   // 포인터가 NULL이면
			{
				executingListPtr[numberOfToken] = NULL;	// executingListPtr배열에서 numberOfToken번째 값에 NULL을 넣는다.
				break;		//break를 수행한다.
			}
			strcpy(executingList[numberOfToken],ptr);   // ptr의 문자열을 executingList[numberOfToken]으로 복사한다.
			executingListPtr[numberOfToken] = &executingList[numberOfToken][0];	   //executingList[numberOfToken][0]의 주솟값을 executingListPtr[numberOfToken]에다가 집어넣는다.
		}	

		for (numberOfToken=0;numberOfToken<9;numberOfToken++)	//numberOfToken의 값을 0로하고, 값이 8미만이 될때까지, 값을 1씩 증가하면서 반복한다.
		{
			if (executingListPtr[numberOfToken]!=NULL)	//executingListPtr[numberOfToken]의 값이 NULL이 아니면,
			{
				printf ("Tok %d->[%s]\r\n",numberOfToken, executingListPtr[numberOfToken]);    //numberOfToken의 값과, executingListPtr[numberOfToken]의 문자열을 출력한다.
			}
			else   //executingListPtr[numberOfToken]의 값이 NULL 이라면,
			{
				break;  //break를 수행한다.
			}
			
		}
		if (strcmp(executingListPtr[0],"도움")==0)    //executingListPtr[0]의 문자열과 도움을 비교하여 같으면 if문을 실행.(문자열이 같으면 0을 반환.)
		{
			printf ("도움말... 은 man 명령어를 실행시켜 보든지 말든지\r\n");     //printf를 수행한다.
			continue;  //반복문의 처음으로 돌아가서 계속한다.
		}
		/*여기서 부터*/
		pid_t newProcess=0;
		newProcess = fork();
		int returnCode = 0;
		
		if(newProcess == 0)
		{
			execvp (command, executingListPtr);
			exit(0);
		}
		else
		{
			wait(&returnCode);
		}
		/*여기까지 채워 넣으세요*/
	}
}
