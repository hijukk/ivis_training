Create console application which counts prime numbers on separate threads.

prime numbers should be searched in a range from 0 to N, where N-s are provided by user as a command line arguments;

user should be able to provide multiple numbers (a separate thread must be created for each number;

there is no limit of how many numbers user can specify;

calculated prime numbers should be written to a text file:

use a pool of 2 files (log1.txt, log2.txt);

threads can choose any file they want for writing to;

files should be open the whole time program is running.

Expected input and output:


'''./threadsApp 20 15 19

cat ./log1.txt
thread[1] finished. prime numbers between 0 and 20: 8
thread[3] finished. prime numbers between 0 and 19: 7

cat ./log2.txt
thread[2] finished. prime numbers between 0 and 15: 6'''
 
