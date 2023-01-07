#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
void print_winner(void);
bool with_edge_is_cycle(int originOrigin, int origin, int destiny);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0) //checks if names is in candidates
        {
            ranks[rank] = i; //candidate i is in this rank for this voter
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++) //this i j loop takes out numbers that repeat
        {
            preferences[ranks[i]][ranks[j]] = preferences[ranks[i]][ranks[j]] + 1; //the sum of votes for one candidate over the other
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++) //for each possible pair checks whos the winners
        {
            if (preferences[i][j] > preferences[j][i]) //if i wins
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
            else if (preferences[i][j] < preferences[j][i]) //if j wins
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count ++;
            }
        }//ties does nothing
    }
    return;
}

// Bubble Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int n = pair_count - 1;
    pair tempPair; //stores temporarely the pair to swap
    bool swap;
    while (n > 0) //bubble sort
    {
        swap = false;
        for (int i = 0; i < n; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] <
                preferences[pairs[i + 1].winner][pairs[i + 1].loser]) //if i pair has less votes than i + 1 pair swaps
            {
                tempPair.winner = pairs[i].winner; //stores temporarely
                tempPair.loser = pairs[i].loser;
                pairs[i].winner = pairs[i + 1].winner; //puts i + 1 in i
                pairs[i].loser = pairs[i + 1].loser;
                pairs[i + 1].winner = tempPair.winner; //puts temporarely in i + 1
                pairs[i + 1].loser = tempPair.loser;
                swap = true; //there was a swap
            }
        }
        if (swap)
        {
            n--; //last pair checked is already in position
        }
        else //ends early if there wasnt a swap
        {
            break;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++) //for each pair
    {
        if (!with_edge_is_cycle(pairs[i].winner, pairs[i].winner, pairs[i].loser)) //if adding the edge dont create a cycle
        {
            locked[pairs[i].winner][pairs[i].loser] = true; //adds edge
        }
    }
    return;
}

bool with_edge_is_cycle(int originOrigin, int origin, int destiny)
{
    for (int i = 0; i < candidate_count; i++) //i is the number of next node to check on the graph
    {
        if (i == origin || i == destiny)// if i is where we came from or where were are skip
        {
            continue;
        }
        else if (locked[destiny][i]) //from the desnity node to the i node checks if there is an edge
        {
            if (i == originOrigin) //if the edge comes back to the first node
            {
                return true; //there is a cycle
            }
            else if (with_edge_is_cycle(originOrigin, destiny, i)) //checks another destiny node from this node
            {
                return true; //returns true if there was a cycle from another node down the line
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    bool winner;
    for (int i = 0; i < candidate_count; i++)
    {
        winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i]) //in j beats i, i is not a winner
            {
                winner = false;
                break;
            }
        }
        if (winner) //if no one beats i, i is a winner
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}

//I wasn't able to implement the more eficient i j loop (commented below) that takes out repeted numbers
//if doesnt print when some pairs are a tie, probably something wrong with the ifs
/*
void print_winner(void)
{
    int winner[3] = {0};
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (!locked[i][j]) //se o candidado i não vence de j
            {
                winner[j] = winner[j] + 1; //soma a vitoria de j
                if (winner[j] == candidate_count - 1)
                {
                    printf("%s\n", candidates[j]);
                    return;
                }
            }
            else if (!locked[j][i])
            {
                winner[i] = winner[i] + 1; //soma a vitoria de i
                if (winner[i] == candidate_count-1)
                {
                    printf("%s\n", candidates[i]);
                    return;
                }
            }
        }
    }
}
*/