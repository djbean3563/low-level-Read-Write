/*application that uses low-level IO system calls (p.170K&R) to read from a file, write to a file, and verfies*/

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> //system calls

int main(int argc, char* argv[])
{
    int readFile, writeFile; //file descripters are non-negative int

    readFile = open(argv[1], O_RDONLY);
    if (readFile < 0) //error return negative
    {
        printf("Cannot open the file %s\n", argv[1]);
        exit(1);
    }

    writeFile = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);

    if (writeFile < 0) 
        printf("Cannot create the file %s\n", argv[2]);

    
    // read bytes from readFile and write them into writeFile

    char buf[1]; //1 byte means no buffering, could do chunks e.g. 1024, 4096
    int n; //number of bytes transferred
    while ((n = read(readFile, buf, 1)) > 0) //read returns 0 at EOF
    {
        write(writeFile, buf, n);
        write(1, buf, n); //stdout is 1, prints bytes onto screen while copying
    }    

    close(readFile);

    ////For Testing: insert char to make files different
    //char myChar;
    //myChar = 'd';
    //write(writeFile, &myChar, 1);

    close(writeFile);

    //test if the two files have the exactly same contents, and print the result

    readFile = open("readFile", O_RDONLY);
    int n2;
    int readFile2;
    readFile2 = open("writeFile", O_RDONLY);    
    
    while ((n = read(readFile, buf, 1)) > 0) 
    {
        n2 = read(readFile2, buf, 1);
        if (n != n2)
        {
           printf("not the same/n"); 
           close(readFile);
           close(readFile2);
           return -1;
        }
        
    }
    //at this point readFile  n == 0
    if (n2 = read(readFile2, buf, 1) != 0)//readFile2 still has more content
    {
        printf("not the same/n");
        close(readFile);
        close(readFile2);
        return -1;
    }
           
    printf("same/n");
    close(readFile);
    close(readFile2);


}   
