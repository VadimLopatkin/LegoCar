#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
 
int main(int argc,char** argv)
{
        printf("Starting\n");
        struct termios tio;
        struct termios stdio;
        struct termios old_stdio;
        int tty_fd;
	int i;
 
        unsigned char array[5]={0xaa, 0x00, 0x00, 0x00, 0x55};
	unsigned char array_out[4];
        tcgetattr(STDOUT_FILENO,&old_stdio);
 
        printf("Please start\n");
        memset(&stdio,0,sizeof(stdio));
        stdio.c_iflag=0;
        stdio.c_oflag=0;
        stdio.c_cflag=0;
        stdio.c_lflag=0;
        stdio.c_cc[VMIN]=1;
        stdio.c_cc[VTIME]=0;


        tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
        tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking

        // printf("Testing!!!!!!!\n");
        // return 0;
 
        memset(&tio,0,sizeof(tio));
        tio.c_iflag=0;
        tio.c_oflag=0;
        tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
        tio.c_lflag=0;
        tio.c_cc[VMIN]=1;
        tio.c_cc[VTIME]=5;


        tty_fd=open(argv[1], O_RDWR | O_NONBLOCK);      
        cfsetospeed(&tio,B115200);            // 115200 baud
        cfsetispeed(&tio,B115200);            // 115200 baud
 
        tcsetattr(tty_fd,TCSANOW,&tio);

        // printf("Finished!");
        // return 0;


        while (1)
        {
		for (i=0; i <= 4; i++)
		{
                	write(tty_fd,&array[i],1);              // if new data is available on the serial port, print it out
			usleep(5000);
		}
		/*while (read(tty_fd,array_out,1)<=0);
		usleep(5000);
		read(tty_fd,&array_out[1],3);
		write(tty_fd,array_out,4); */
		usleep(100000);
        }
 
        close(tty_fd);
        tcsetattr(STDOUT_FILENO,TCSANOW,&old_stdio);
 
        return EXIT_SUCCESS;
}