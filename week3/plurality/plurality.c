#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    char* name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
int vote(char* name);
void print_winner(void);
char *get_string(char *prompt);
int get_int(char *prompt);


int main(int argc, char* argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        char* name = get_string("Vote: ");

        // Check for invalid vote
        if (vote(name) == 1)
        {
            printf("Invalid vote.\n");
        }
        free(name);
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
int vote(char* name)
{
    for(size_t i = 0, n = sizeof(candidates) / sizeof(candidate); i < n; i++) {
        if (strcmp(name, candidates[i].name) == 0) {
            candidates[i].votes++;
            return 0;
        }
    }

    return 1;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Find the maximum number of votes

    // Print the candidate (or candidates) with maximum votes
}

// sort candidates
void sort_candidates(candidate candidates[]) {
}

// Gets a string
char *get_string(char *prompt) {
    printf("%s", prompt);
    char input[256];

    // Getting input
    while (fgets(input, sizeof input, stdin) == NULL) {
        printf("Error when reading input\n");
    }

    // First check and removing newline character
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    // Allocating memory to return
    char *result = malloc(strlen(input) + 1);
    if (result == NULL) {
        printf("Error allocating memory for string\n");
        return NULL;
    }

    // Copying string to be able to return a valid memory (and not something out
    // of scope)
    strcpy(result, input);

    return result;
}

int get_int(char* prompt) {
    printf("%s", prompt);
    char input[256];

    while(fgets(input, sizeof input, stdin) == NULL) {
        printf("Error when getting int\n");
    }

    // Removing newline character
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    return atoi(input);
}
