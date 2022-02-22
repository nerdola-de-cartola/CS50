#include <cs50.h>
#include <strings.h>
#include <stdio.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool createCycle(int cycle_end, int cycle_start);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //Validates each vote
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(name, candidates[i]) == 0)
        {
            //ranks[rank] indicates the rank in this particular vote
            //i is the index of the candidate chose in the candidates array
            ranks[rank] = i;
            //printf("Position: %i\nVote go to: %s\n", ranks[rank], candidates[i]);
            return true;
        }

    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // i represents the rank of the current candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // j represents the rank of the current oponent
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                //printf("Candidato %s ganhou do candidato %s\n", candidates[ranks[i]], candidates[ranks[j]]);
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                //If one candidate is preferred over the other
                if (preferences[i][j] != preferences[j][i])
                {
                    if (preferences[i][j] > preferences[j][i])
                    {
                        pairs[pair_count].winner = i;
                        pairs[pair_count].loser = j;
                        //printf("Winner: %i; loser: %i\n", pairs[pair_count].winner, pairs[pair_count].loser);
                        pair_count++;
                    }
                }
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //Variables to facilitate the syntax
    pair current_pair;
    pair next_pair;

    //i represents the last position of the array that receives the weakest pair
    for (int i = pair_count - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            current_pair = pairs[j];
            next_pair = pairs[j + 1];

            if (preferences[current_pair.winner][current_pair.loser] < preferences[next_pair.winner][next_pair.loser])
            {
                pairs[j] = next_pair;
                pairs[j + 1] = current_pair;

            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //Variables to facilitate the syntax
    int winner;
    int loser;

    //Lock pairs if not create a cycle
    for (int i = 0; i < pair_count; i++)
    {
        winner = pairs[i].winner;
        loser = pairs[i].loser;

        if (!createCycle(loser, winner))
        {
            locked[winner][loser] = true;
        }
    }
}

bool createCycle(int cycle_end, int cycle_start)
{
    //If the end of the graph is equal to the end it creates a cycle
    if (cycle_end == cycle_start)
    {
        return true;
    }

    //Recursively loop through candidates
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[cycle_end][i])
        {
            //Complete the graph
            if (createCycle(i, cycle_start))
            {
                return true;
            }
        }
    }

    //There is no cycle being created, it`s safe to lock the pair
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    bool isWinner;

    //Check the 2D array for a column without "true"
    //This means that in the graph the candidate has no edges pointing in your direction
    for (int column = 0; column < pair_count; column++)
    {
        isWinner = true;

        for (int row = 0; row < pair_count && isWinner == true; row++)
        {
            if (locked[row][column])
            {
                isWinner = false;
            }
        }

        if (isWinner == true)
        {
            printf("%s\n", candidates[column]);
        }
    }
}