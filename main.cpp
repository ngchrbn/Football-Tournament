#include <iostream>
using namespace std;

const int nTeams = 2;    // Number of Teams
const int nScores = 3;    // Number of Scores for each team

void buildTeams(char teams[], char scores[][nScores], int points[nTeams]);

void displayTeams(char teams[], char scores[][nScores], int points[]);

int searchTeam(char teams[], int index, char team);

void showChampion(char teams[], const int points[]);

int calculatePoints(char scores[][nScores], int index, int points[nTeams]);

void editScores(char teams[], char scores[][nScores], int points[]);

void editTeamName(char teams[]);

int main() {
    int points[nTeams] {0}; // Hold the total points for each team
    char teams[nTeams];  // Hold the teams names
    char scores[nTeams][nScores]; // Hold the teams scores
    int choice;
    bool stop = false;   //  Continue the program

    buildTeams(teams, scores, points);

    while (!stop)
    {
        cout << "\nList all the teams enter (1)\n"
             << "Edit a team's Scores enter (2)\n"
             << "Show the champion enter (3)\n"
             << "Edit a team's name enter (4)\n"
             << "Exit enter (0)\n";
        cout << "==> Choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                displayTeams(teams, scores, points);
                break;
            case 2:
                editScores(teams, scores, points);
                break;
            case 3:
                showChampion(teams, points);
                break;
            case 4:
                editTeamName(teams);
                break;
            case 0:
            {
                stop = true;
                cout << "Thank you for using the program\n";
                break;
            }
            default:
                cout << "Wrong choice!Try Again\n";
        }
    }
    return 0;
}

/* Get from the user, the teams names and scores then calculate their points */
void buildTeams(char teams[nTeams], char scores[][nScores], int points[nTeams]) {
    for (int i = 0; i < nTeams; ++i) {
        cout << "Enter team " << (i+1) << " name: ";
        cin >> teams[i];
        cout << "Enter team " << teams[i] << " scores: ";
        for (int j=0; j<nScores; ++j) {
            cin >> scores[i][j];
        }
        cout << teams[i] << "'s score is " << calculatePoints(scores, i, points)
            << " and it is saved for the team\n";
    }
}

/* List all the teams names and their scores and points */
void displayTeams(char teams[nTeams], char scores[][nScores], int points[nTeams]) {
    cout << endl;
    for (int i=0; i<nTeams; ++i) {
        cout << "Team " << (i+1) << " name: "<< teams[i]
                << "\n==> Scores: ";
        for (int j=0; j<nScores; ++j) {
            cout << scores[i][j] << " ";
        }
        cout << "\n==> Points: " << points[i] << endl;
    }
}


/* Output the team with highest points */
void showChampion(char teams[nTeams], const int points[nTeams]) {
    int indexOfChampion = 0;
    int champion = points[0];
    for (int i = 1; i < nTeams; ++i) {
        if (points[i] > champion)
        {
            champion = points[i];
            indexOfChampion = i;
        }
        else
            continue;
    }
    cout << "The champion is team " << teams[indexOfChampion] <<
            " with " << champion << " points" << endl;


}

/* Search if a team name given is present in the array
 * Return -1 if the team is not found
 * Else return the index of the team in the array
 */
int searchTeam(char teams[nTeams], int index , char team) {
    if (teams[index] == team)
        return index;
    else if (index == -1)
        return -1;
    else
        return searchTeam(teams, index - 1, team);
}

/* Edit the scores of a team */
void editScores(char teams[nTeams], char scores[][nScores], int points[nTeams]) {
    char team;  // the team name to be searched
    int result; // Hold -1 if team name not found else its index in the array
    cout << "Enter team name to edit: ";
    cin >> team;
    result = searchTeam(teams, nTeams, team);
    if (result == -1)
    {
        cout << "The team name given doesn't exist!\n";
        return;
    }
    else
    {
        cout << "Enter new scores: ";
        for (int i = 0; i < nScores; ++i) {
            cin >> scores[result][i];
        }
    }
    cout<< teams[result] << "'s score is changed to " << calculatePoints(scores, result, points)
        << " and it is saved for the team\n";
}

/* Calculate the total point of a given team
 * Return the total point for a team
 */
int calculatePoints(char scores[][nScores], int index, int points[nTeams]) {
    points[index] = 0;  // Reinitialise the points to zero to be recalculated
    for (int j = 0; j < nScores; ++j) {
        switch (scores[index][j]) {
            case 'W':
            case 'w':
                points[index] += 5;
                break;
            case 'd':
            case 'D':
                points[index] += 2;
                break;
            case 'l':
            case 'L':
                points[index] += 0;
                break;
            default:
                points[index] =0;
        }
    }
    return points[index];
}

/* Edit a team name */
void editTeamName(char teams[nTeams]) {
    char team;  // Hold the team name to be modified
    cout << "Enter the team name to be modified: ";
    cin >> team;
    int index = searchTeam(teams, nTeams, team);
    if (index == -1)
    {
        cout << "The team name given doesn't exist!\n";
        return;
    }
    else
    {
        cout << "Enter a new name for team " << teams[index] << ": ";
        cin >> team;
        teams[index] = team;
    }
}