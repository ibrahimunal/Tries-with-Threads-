// C implementation of search and insert operations
// on Trie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <dirent.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
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

void *threadFunc(void *file);
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



//void *threadFunc(void *file);
struct TrieNode *root;
int main(int argc, char const *argv[])
{



   // FILE *fp;
    pthread_t threadList[10];
    //pthread_t thread
    //pthread_t thread2;
    //pthread_t thread3;
     // FILE *fp=fopen("data1.txt","r");
     // FILE *fp2=fopen("data2.txt","r");
      //FILE *fp3=fopen("data3.txt","r");
    int count=0;
    root=getNode();
    //DIR *folder;

   // struct dirent *entry;
   // folder=opendir("./data");
     char files[][12] = {"data1.txt","data2.txt","data3.txt","data4.txt","data5.txt","data6.txt","data7.txt","data8.txt","data9.txt","data10.txt"};
     /*pthread_mutex_lock(&mutex);
       pthread_create(&thread, NULL, threadFunc, (void *)fp);
       pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex);
       pthread_create(&thread2, NULL, threadFunc, (void *)fp2);
       pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex);
       pthread_create(&thread3, NULL, threadFunc, (void *)fp3);
       pthread_mutex_unlock(&mutex);
    */
    /* if(folder == NULL)
    {
        puts("Unable to read directory");
        return(1);
    }
      while( (entry=readdir(folder)) != NULL )
    {
    if (strstr(entry->d_name,"data")){
     printf("%s\n", entry->d_name);
   // fp=fopen(entry->d_name,"r");

      // pthread_mutex_lock(&mutex);
      if(! pthread_create(&threadList[count++], NULL, threadFunc, entry->d_name)){
          printf("Thread %d not created",count);
      }
      // pthread_mutex_unlock(&mutex);
    }

    }
       for(int i=0;i<10;i++){
    pthread_join(threadList[i], NULL);
    }
    closedir(folder);
*/
     //pthread_join(thread, NULL);
      //pthread_join(thread2, NULL)
       //pthread_join(thread3, NULL);
  for(int i=0; i<10; i++){
  // create threads
  printf("File %s\n", files[i]);
  pthread_create(&threadList[i], NULL, threadFunc,&(files[i])) ;
  }

      for(int i=0;i<10;i++){
    pthread_join(threadList[i], NULL);
    }
printf("No problem with threads");
    char *str = (char *)malloc(1000);
FILE *writeFile = fopen("output4.txt", "w+");
if(writeFile == NULL){
printf("output file not created");
}

    WriteToFile(str, root, writeFile);

    return 0;
}


void *threadFunc(void *file)
{
 int counter=0;
char *filename = (char *)file;
FILE *fp;
fp = fopen(filename,"r");
printf("File opened");
 if(fp==NULL){
 printf("Could not open file");
 exit(-1);
 }

  char line[1000];
    while (fgets(line,1000,fp)!= NULL){
    pthread_mutex_lock(&mutex);
    insert(root,line);
    pthread_mutex_unlock(&mutex);
    counter++;
        if(counter>30000){
        //data is too much the handle so a part of it taken..
        break;
        }
    }
    printf("File thread finish");
    pthread_exit(NULL);
}






