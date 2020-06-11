

Project consist multiple C files. Here are some commands to run the code in terminal

task.c file consist the task2,task3 and task 6 which runs them both and creates output2.txt and output3.txt
it gives a warning when first command it entered. dont worry enter the second command afterward.
to run them please enter commands below.
*********************************
gcc -o task task.c
./task
*********************************
NOTE: please put the 10 (data.txt) files project file. Otherwise it might give segmentation error
just because could not find the files.


other c file is thread.c which reads all the text files concurrently and create a mutual trie.
This function writes its input to output4.txt

to run the file please enter commands below.
*********************************
gcc -o thread thread.c -lpthread
./thread
*********************************
For unknown reason it might require to enter the command again when it give segmentation error.

Please check the output files after commands.



Design Overview: I implemented a Trie Data Structure in order to sort queries. some of the task asks to do it with threads. So with the help of pthread.h library i was able to insert the queries from different data files concurrently. To prevent deadlock situtation mutexes are used.


I was able to implement the trie and thread tasks(not all of them). I had some issues while merging the tries and could not complete the task5 and task6 completely. Detailed explaination is provided in REPORT file.
