/**
 * @file   testebbchar.c
 * @author Jared Nussbaum
 * @version 0.1
 * @brief  A Linux user space program that communicates with the ebbchar.c LKM. You can pass hashes to the LKM using stdin. For this example to work the device
 * must be called /dev/ebbchar.
 * @see This was derived from https://github.com/derekmolloy/exploringBB/tree/master/extras/kernel/ebbchar
*/
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_LENGTH 256               ///< The buffer length (crude but fine)
static char receive[BUFFER_LENGTH];     ///< The receive buffer from the LKM

int main(){
   int ret, fd;
   char stringToSend[BUFFER_LENGTH];
   printf("Starting device test code example...\n");
   fd = open("/dev/ebbchar", O_RDWR);             // Open the device with read/write access
   if (fd < 0){
      perror("Failed to open the device...");
      return errno;
   }

   while(1){
   printf("Type in a key and value to send to the kernel module in the form \"key|value\":\n");
   scanf("%[^\n]%*c", stringToSend);                // Read in a string (with spaces)
   printf("Writing message to the device [%s].\n", stringToSend);
   ret = write(fd, stringToSend, strlen(stringToSend)); // Send the string to the LKM
   if (ret < 0){
      perror("Failed to write the message to the device.");
   }

   printf("Enter the key to read back from the device...\n");
   scanf("%[^\n]%*c", receive);   
   //getchar();

   printf("Reading from the device...\n");
   ret = read(fd, receive, BUFFER_LENGTH);        // Read the response from the LKM
   if(ret < 0){
      perror("Failed to read the message from the device.");
      //return 0;
   }
   else{
    printf("The received message is: [%s]\n", receive);
   }

   }
   printf("End of the program\n");
   return 0;
}
