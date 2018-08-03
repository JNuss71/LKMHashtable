# LKMHashtable

This is a Linux Kernel Module (LKM) that impliments a system device for storing a hashtable. This utilizes the hashtable.h kernel library for its table. 

The code in this repository is derived from https://github.com/derekmolloy/exploringBB/tree/master/extras/kernel/ebbchar and good instructions for getting the LKM built is http://derekmolloy.ie/writing-a-linux-kernel-module-part-1-introduction/


## THE FOLLOWING WAS PROVIDED TO THE PROFESSOR AS AN EXPLINATION OF THE PROJECT

I based my LKM off of the tutorial code here: 
https://github.com/derekmolloy/exploringBB/tree/master/extras/kernel/ebbchar. 
This was an LKM that took in user input from the command line and stored it in the LKM to 
read out from the LKM. 

I uploaded my completed code for the first part of the project to Gradescope.

Process:
  The tutorial code provided me with the interface code that I had to modify slightly. What 
I first thought to do was learn how to use a kernel API for a hash table. I found hashtable.h after 
some googling. Understanding how to use it was one of the hardest tasks for the assignment. The 
documentation was shoddy at best for what to use and what each argument actual meant. I first 
established how to interface with a hash table in the kernel using hashtable.h in the init function 
of my LKM. I figured out some stuff and then determined how to store data using a struct with 
the hnode and data which I had as a 256 byte char array. It worked eventually, and I just had to 
work on how to interface my hash table with user input using the template read and write 
functions that were provided in the tutorial code. 
  
  The first step was initializing the hash table in the init function which I did earlier. The 
next step was establishing that I could read in an item from the user to put into a pre-designated 
key position and print it to the kernel log. Once I got user input set up I then programmed 
sending the output to the user through the buffer when the user tries to read from the LKM’s 
hash table at the same pre-designated key. Both reading, and writing worked just fine when I ran 
the template user interface code. I just had to establish that I could pass a key with the value I 
wanted to store and pass the key I want to get out. I chose to use the strsep that I saw when 
looking at the strings.h file to separate a string input on a delimiter that I decided to be ‘|’. So 
now I had to break the input into the key that comes to the left of the delimiter and the value that 
comes to the right of the delimiter. I had a few issues where I needed a double char pointer but I 
had a pointer to a char array passed to strsep. I had to malloc a new char pointer and copy the 
input message to its location. So, I had the input to the hash table working fine. I just had to 
figure out the reading from the hash table. I figured the user would pass it as the char buffer that 
I would write to. I programmed that, and it worked. Next I modified the user program to loop 
and have the correct prompt. Then I saw that since my message variable that was copied from the 
buffer was stored globally, if future key values were shorter in length then previous ones, it 
would append data that was not part of the input. Then I decided to fix this by just setting the 
message to the empty string before copying the buffer into the variable (kind of hacky but 
whatever). I then did a lot of input checking in the read and write functions. I made sure that the 
delimiter split two strings and to the left of the delimiter was a string that could be converted into 
a long using kstrtol in the write function. In the read function I made sure that the input key 
string could be converted into a long, and that the value for the key was there and was retrieved. 
I made sure that the kernel return error values were appropriate or the value was written 
successfully to the user on a match and returned the argument len.
	
Design was explained in the process.

  I liked that the project limited my resources and had me use problem solving strategies to 
decipher an API that I was unfamiliar with. It was cool to see how with a limited understanding 
of kernel hacking I was able to apply user space knowledge and knowledge from the class to 
come up with a plan of action to complete the task of writing kernel space code for the LKM. 
Basically, the biggest pro was that it was unlike any other projects I have done in college. That is 
why I have enjoyed this class so much. There are more considerations and novel concepts than 
writing simple software applications to complete a high-level problem. Seeing the module 
working across multiple programs was also cool to see. It was also cool that the whole interface 
was just reading and writing to files (I guess that is just \*nix in general with “everything being a 
file”)
      
  The fact that the documentation/resources for the hashtable.h API was complete garbage 
and even sometimes actively detrimental to my progress because the information was outdated or 
wrong. It seemed like once the API was understood, it was intuitive how to use it to complete the 
rest of part 1 (I think writing the code took the same amount of time as documentation reading). 
It is not really a bad thing but getting recommendations about what would make one’s solution 
better would be useful. 
