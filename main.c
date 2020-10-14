// If you are not compiling with the gcc option --std=gnu99, then
// uncomment the following line or you might get a compiler warning
//#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* struct for movie information */
struct movie
{
    char *movName;
    int *movYear;
    char *movLang;
    float *movRate;


    struct movie *next;
};

/* Parse the current line which is space delimited and create a
*  movie struct with the data in this line
*/
struct moive *createMovie(char *currLine)
{
  printf("Adding a new movie");
    struct movie *currMovie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char *saveptr;
    printf("Adding the title of the movie");
    // The first token is the title
    char *token = strtok_r(currLine, " ", &saveptr);
    currMovie->movName = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->movName, token);

    // The next token is the release year
    printf("Adding the year of the movie");
    int *int_token = NULL;
    currMovie->movYear = malloc(sizeof(int));
    currMovie->movYear = int_token;
    // The next token is the language(s)
    //
    // This one is gonna need a lot of editing since there can be multiple languages, (array?)
    //
    printf("Adding the languages of the movie");
    // The first token is the title
    currMovie->movLang = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->movLang, token);


    printf("Adding the rating of the movie");
    // The last token is the rating
    float *float_token = NULL;
    currMovie->movRate = malloc(sizeof(float));
    currMovie->movRate = float_token;

    // Set the next node to NULL in the newly created movie entry
    currMovie->next = NULL;

    return currMovie;
}

/*
* Return a linked list of movies by parsing data from
* each line of the specified file.
*/
struct movie *processFile(char *filePath)
{
  printf("Begning to process the file");
    // Open the specified file for reading only
    FILE *movieFile = fopen(filePath, "r");

    char *currLine = NULL;
    size_t len = 0;
    int nread;
    char *token;

    // The head of the linked list
    struct movie *head = NULL;
    // The tail of the linked list
    struct movie *tail = NULL;

    // Read the file line by line
    while ((nread = getline(&currLine, &len, movieFile)) != -1)
    {
        // Get a new movie node corresponding to the current line
        struct movie *newNode = createMovie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    free(currLine);
    fclose(movieFile);
    return head;
}

/*
* Print data for the given movie
*/
void printMovie(struct movie* aMovie){
  printf("%s, %d %s, %f\n", aMovie->movName,
               aMovie->movYear,
               aMovie->movName,
               aMovie->movRate);
}
/*
* Print the linked list of movies
*/
void printMovieList(struct movie *list)
{
    while (list != NULL)
    {
        printMovie(list);
        list = list->next;
    }
}

/*
*   Process the file provided as an argument to the program to
*   create a linked list of movie structs and print out the list.
*   Compile the program as follows:
*       gcc --std=gnu99 -o movies main.c
*/

int main(int argc, char *argv[])
{
  printf("Starting...");
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movie_info1.txt\n");
        return EXIT_FAILURE;
    }
    struct movie *list = processFile(argv[1]);
    printMovieList(list);
    return EXIT_SUCCESS;
}
