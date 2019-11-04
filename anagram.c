#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

char **read_dict(char *filename, int *lines)
{
    //get file size
    struct stat st;
    if (stat(filename, &st) == -1)
    {
        fprintf(stderr, "Can't get info about %s\n", filename);
        exit(1);
    }
    int len = st.st_size;
    
    //malloc space for entire file
    char *file = (char *)malloc(len * sizeof(char));
    
    //read entire file into memory
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        fprintf(stderr, "Can't open %s for reading\n", filename);
        exit(1);
    }
    fread(file, 1, len, f);
    fclose(f);
    
    //replace \n with \0
    int count = 0;
    for (int i = 0; i <= len; i++)
    {
        if(file[i] == '\n')
        {
            file[i] = '\0';
            count++;
        }
    }
    
    //malloc space for array of pointers
    char ** line = malloc((count+1) * sizeof(char*));
    
    //fill in addresses
    int word = 0;
    line[word] = file; //the first word in the file
    word++;
    for (int i = 1; i < len; i++)
    {
        if(file[i] == '\0' && (i+1) < len)
        {
            line[word] = &file[i + 1]; //the file pointer plus the distance to this newline
            word++;
        }
    }
    
    line[word] = NULL;
    
    //return address of second array
    *lines = word;
    return line;
}

int isAnagram(char a[], char b[])
{
  int left[26] = {0};
  int right[26] = {0};
  int i = 0;

  //calculate character frequency of a[]
  while (a[i] != '\0')
  {
    left[a[i]-'a']++;
    i++;
  }

  i = 0;

  while (b[i] != '\0')
  {
    right[b[i]-'a']++;
    i++;
  }

  //compare character frequency to b[]
  for (i = 0; i < 26; i++)
  {
    if (left[i] != right[i])
      return 0;
  }
  return 1;
}

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    printf("CJ's Anagram Finder\nUsage: %s word dictionary.txt\n", argv[0]);
    exit(1);
  }else{
    printf("Looking For Anagrams For: %s\n",argv[1]);
  }

  //Load dictionary
  int dictCount = 0;
  char **dict = read_dict(argv[2],&dictCount);

  //Is it faster to sort the dictionary? Why?
  //qsort(dict  ,dictCount,sizeof(char *),order);

  //Iterate through dictionary
  for(int i = 0; i < dictCount; i++)
  {
    //If anagram to input word then output the anagram
    if(isAnagram(dict[i],argv[1])){
      printf("%s\n",dict[i]);
    }
  }
}
