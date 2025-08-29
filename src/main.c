#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<termios.h>
#include<errno.h>

#define CTRL_KEY(k) ((k) & 0x1f)

struct termios orig_termios;

void disableRawMode()
{
   tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);

}

void enableRawMode()
{

   tcgetattr(STDOUT_FILENO, &orig_termios);
   atexit(disableRawMode);

   struct termios raw = orig_termios;
   raw.c_lflag &= ~(ECHO | ICANON);

   tcsetattr(STDIN_FILENO,TCSAFLUSH, &raw);


}

int main()
{
	enableRawMode();
	char c;
	write(STDOUT_FILENO, "Welcome to bubble editor!\r\n",28);

	while(1)
	{
	   ssize_t nread = read(STDIN_FILENO, &c, 2);
	   if (nread == -1)
	   {
		perror("read");
		exit(1);	
	   }

	   if(nread == 1)
	   {
		printf("key pressed %d \r\n",c );
		if(c == CTRL_KEY('q'))
			break;
	   }
	}


	return 0;


}
