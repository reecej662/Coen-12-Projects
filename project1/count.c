//
//  count.c
//  count
//
//  Reece Jackson
//  1-12-15
//
//  Counts the words in an inputed text file
//  Prints number of words counted, otherwise returns -1
//

#include <stdio.h>

//define constants
#define MAX_WORD_LENGTH 30

int main(int argc, const char * argv[]) {
    
    //declare variables to be used
    FILE* text = NULL;
    char word[MAX_WORD_LENGTH];
    int count = 0;
    
    //open text file to read from
    if((text = fopen(argv[1], "r")) == NULL)
    {
        //return error if file can't be opened
        printf("Error: Unable to open file.\n");
        return -1;
    }
    
    //itterate over each word, increading count by 1 each time
    while(fscanf(text, "%s", word) != EOF)
        count++;
    
    //print the final result
    printf("%d total words\n", count);
    
    return 0;
}
