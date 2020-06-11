// C implementation of search and insert operations
// on Trie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (93)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)' ')

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
    int count;

};
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = NULL;


    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    if (pNode)
    {
        int i;

        pNode->isEndOfWord = false;

        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
        pNode->count = 0;
    }

    return pNode;
}

void insert(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;

    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (index > ' ' || index < ' ' + ALPHABET_SIZE)
        {
               if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
        }

    }
    pCrawl->isEndOfWord = true;
    pCrawl->count++;
}


void WriteToFile(char *str, struct TrieNode *node, FILE *fPtr)
{

    if (node->isEndOfWord)
    {

        fprintf(fPtr, "%s : %d\n", str, node->count);
    }

    for (char index = 0; index < ALPHABET_SIZE; ++index)
    {
        char next = ' ' + index;
        struct TrieNode *child = node->children[index];
        if (child)
        {
            str[strlen(str)] = next;
            str[strlen(str) + 1] = '\0';
            WriteToFile(str, child, fPtr);
            str[strlen(str) - 1] = '\0';
        }
    }
}

bool search(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}
// function to check if current node is leaf node or not
bool isLeafNode(struct TrieNode* root)
{
    return root->isEndOfWord != false;
}

void task3(){
clock_t begin = clock();
    struct TrieNode *root = getNode();
    char *str = (char *)malloc(1000);
  int counter=0;
  int i =0;
  int size=100;
  char ch;
  char buffer[10000];
   // Buffer to store data
  char line[100];
  FILE * stream;
  FILE *fptr;
  stream = fopen("data1.txt", "r");
  fptr= fopen("output3.txt", "w+");
  while(counter < 10000){

  fread(&buffer, sizeof(char), size, stream);
    if(buffer[size] != '\n'){

    //printf("rest of the sentence is \n");
        while ((ch = fgetc(stream)) != '\n')
        {
           strncat(buffer, &ch, 1);
        }
        char * token = strtok(buffer, "\n");

         while( token != NULL ) {
        //printf( "%s\n", token ); //printing each token
        insert(root,token);
        token = strtok(NULL, "\n");

        }


    }
    //insert(root,buffer);
  //printf("%d :%s \n",counter, buffer);
  counter++;
  buffer[size]='\0'; // resets the buffer

  }

  fclose(stream);
  WriteToFile(str, root,fptr);
  clock_t finish = clock();
  double timePassed = (double)(finish - begin) / CLOCKS_PER_SEC;
  printf("Please check output3.txt \n");
  printf("Time passed : %f seconds\n", timePassed);

}

void task2(){

    clock_t begin = clock();
    FILE *fp =fopen("data1.txt","r");
    FILE *fPtr = fopen("output2.txt","w+");
    struct TrieNode *root = getNode();
    int counter=0;

    char *str = (char *)malloc(1000);

    char *line=malloc(sizeof(char *)*1000);
    while (fgets(line,100,fp)!= NULL){
    insert(root,line);
    counter++;
        if(counter>300000){
        //data is too much the handle so a part of it taken..
        break;
        }
    }
    WriteToFile(str, root,fPtr);
    clock_t finish = clock();
    double timePassed = (double)(finish - begin) / CLOCKS_PER_SEC;
    printf("Please check output2.txt \n");
    printf("Time passed : %f seconds\n", timePassed);

}

void task6(){
clock_t begin = clock();
    struct TrieNode *root = getNode();
    char *str = (char *)malloc(1000);
  int counter=0;
  int i =0;
  int size=100;
  char ch;
  char buffer[1000000];
   // Buffer to store data
  char line[100];
  FILE * stream;
  FILE *fptr;
  stream = fopen("data1.txt", "r");
  fptr= fopen("output6.txt", "w+");




    //printf("rest of the sentence is \n");
        while ((ch = fgetc(stream)) != NULL)
        {
        strncat(buffer, &ch, 1);
        if(counter>10000){
        break;
        }
           counter++;
        }

       char * token = strtok(buffer, "\n");

         while( token != NULL ) {
        //printf( "%s\n", token ); //printing each token
        insert(root,token);
        token = strtok(NULL, "\n");

        }


    WriteToFile(str, root,fptr);
  //printf("%d :%s \n",counter, buffer);
    clock_t finish = clock();
    double timePassed = (double)(finish - begin) / CLOCKS_PER_SEC;
    printf("Please check output6.txt \n");
    printf("Time passed : %f seconds\n", timePassed);



  fclose(stream);






}

//void *threadFunc(void *file);

int main(int argc, char const *argv[])
{
    //root=getNode();

    //pthread_t  thread;
    task3();
    task2();
    task6();
    /*
    char *str = (char *)malloc(1000);
    FILE *writeFile = fopen("output4.txt", "w+");
    FILE *fp=fopen("data2.txt","r");
    //pthread_mutex_lock(&mutex);
    pthread_create(&thread, NULL, threadFunc, (void *)fp);
    //pthread_mutex_unlock(&mutex);
    pthread_join(thread, NULL);
    WriteToFile(str, root, writeFile);
 */

    return 0;
}


/*
void *threadFunc(void *file)
{
 int counter=0;
 FILE *fp = (FILE *)file;
 char *line=malloc(sizeof(char *)*1000);
    while (fgets(line,10000,fp)!= NULL){
    //pthread_mutex_lock(&mutex);
    insert(root,line);
    //pthread_mutex_unlock(&mutex);
    counter++;
        if(counter>30000){
        //data is too much the handle so a part of it taken..
        break;
        }
    }
    pthread_exit(NULL);
}
*/





