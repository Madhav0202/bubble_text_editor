#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<termios.h>
#include<errno.h>

#define CTRL_KEY(k) ((k) & 0x1f)

struct termios orig_termios;


//creating enum to handling key event;




void disableRawMode()
{
   tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);

}

void enableRawMode()
{

   tcgetattr(STDIN_FILENO, &orig_termios);
   atexit(disableRawMode);
   struct termios raw = orig_termios;
   raw.c_lflag &= ~(ECHO | ICANON | ISIG);
   raw.c_iflag &= ~(IXON | ICRNL );             // disable Ctrl-S/Q and carriage return mapping
   raw.c_oflag &= ~(OPOST);                    // disable all output processing
   raw.c_cc[VMIN] = 0;                         // return as soon as any input is available
   raw.c_cc[VTIME] = 1;      
   tcsetattr(STDIN_FILENO,TCSAFLUSH, &raw);


}

int main()
{
	char c;
	enableRawMode();
	write(STDOUT_FILENO, "Welcome to bubble editor!\r\n",28);

	while(1)
	{
	   ssize_t nread = read(STDIN_FILENO, &c, 1);
	   if (nread == -1)
	   {
		perror("read");
		exit(1);	
	   }

	   
	  // write(STDOUT_FILENO, &c,1);
	   if(nread == 1)
	   {

            char buffer[32];
//            int len = snprintf(buffer, sizeof(buffer), "Key pressed: %d\r\n", c);
		if(c == CTRL_KEY('q'))
			break;
	   }
	}


	return 0;


}
