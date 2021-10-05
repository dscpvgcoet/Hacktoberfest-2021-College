#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>

int main(void)
{
	int fd1[2],nbytes=1,fd2[2],a=0;
	pid_t pid;
	char string[80];
	char readbuffer[80];
	char ch='a',ch1='\n';
	FILE *fp;
	pipe(fd1);
	pipe(fd2);

	if((pid=fork())==-1)
	{
		perror("fork");
		exit(1);
	}

	if(pid==0)
	{	
		close(fd1[1]);
		read(fd1[0],readbuffer,sizeof(readbuffer));
	
		printf("filename %s is being read by child process through pipe 1\n\t",readbuffer);
		fp=fopen(readbuffer,"r");

		close(fd2[0]);

		printf("\n content of %s are being sent to parent process through pipe2\n\t",readbuffer);
		while(a!=-1)
		{
			a=fscanf(fp,"%c",&ch);
			write(fd2[1],&ch,sizeof(ch));
		}
		close(fd2[1]);
		exit(0);
	}
	else
	{
		close(fd1[0]);
		printf("\n\t In parent process\n");
		printf("\n\tEnter name of file::\n\t");
		scanf("%s",string);
		printf("\n filenames %s is being set by parent process to child process through pipe1\n\t ",string);	
		write(fd1[1],string,(strlen(string)+1));
		wait(NULL);
		close(fd1[1]);
		close(fd2[1]);
		printf("\n content of %s are being received  by parent process through pipe2\n\t ",string);

		printf("\n\tIn parent process");
		printf("\n\tReceived message");
		while(nbytes!=0)
		{
			printf("%c",ch1);
			nbytes=read(fd2[0],&ch1,sizeof(ch1));
		}
		close(fd2[0]);
	}
	return(0);
}
