#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEAMS 10
#define MAX_EVENTS 5

typedef struct {
    char name[20];
    int score;
} Player;

typedef struct {
    char name[20];
    int scores[MAX_EVENTS];
    int totalScore;
    Player players[5];
    char events[MAX_EVENTS][20];
} Team;
Team teams[MAX_TEAMS];
int teamCount = 0;
void addTeam() {
    char name[20];
    printf("Please enter the team name: ");
    scanf("%s", name);
    int teamIndex;
    printf("Please enter the team index: ");
    scanf("%d", &teamIndex);
    for (int i = 0; i < teamCount; i++) {
        if (strcmp(teams[i].name, name) == 0) {
            printf("Team already exists, cannot add!\n");
            return;
        }
    }

    strcpy(teams[teamCount].name, name);
    teams[teamCount].totalScore = 0;

    // 输入运动会项目名称
    printf("Please enter the number of events for this team: ");
    int eventCount;
    scanf("%d", &eventCount);
    for (int i = 0; i < eventCount; i++) {
        printf("Please enter the name of event %d: ", i + 1);
        scanf("%s", teams[teamCount].events[i]);
    }

    teamCount++;

    printf("Team added successfully!\n");
}



void addPlayer() {
    int teamIndex;
    char name[20];
    printf("Please enter the team index: ");
    scanf("%d", &teamIndex);
    printf("Please enter the player name: ");
    scanf("%s", name);

    if (teamIndex < 1 || teamIndex > teamCount) {
        printf("Invalid team index!\n");
        return;
    }

    for (int i = 0; i < 5; i++) {
        if (strcmp(teams[teamIndex - 1].players[i].name, name) == 0) {
            printf("Player already exists, cannot add!\n");
            return;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (teams[teamIndex - 1].players[i].name[0] == '\0') {
            strcpy(teams[teamIndex - 1].players[i].name, name);
            teams[teamIndex - 1].players[i].score = 0;
            printf("Player added successfully!\n");
            return;
        }
    }

    printf("Team is full, cannot add!\n");
}
void displayTeamInfo() {
    int teamIndex;
    printf("Please enter the team index: ");
    scanf("%d", &teamIndex);

    if (teamIndex < 1 || teamIndex > teamCount) {
        printf("Invalid team index!\n");
        return;
    }

    printf("Team name: %s\n", teams[teamIndex - 1].name);
    printf("Total score: %d\n", teams[teamIndex - 1].totalScore);
    printf("Events:\n");
    for (int i = 0; i < MAX_EVENTS; i++) {
        if (teams[teamIndex - 1].events[i][0] != '\0') {
            printf("%d. %s\n", i + 1, teams[teamIndex - 1].events[i]);
        }
    }
    printf("Players:\n");
    for (int i = 0; i < 5; i++) {
        if (teams[teamIndex - 1].players[i].name[0] != '\0') {
            printf("%s: %d\n", teams[teamIndex - 1].players[i].name, teams[teamIndex - 1].players[i].score);
        }
    }
}


void generateReport() {
    printf("Team report:\n");
    for (int i = 0; i < teamCount; i++) {
        printf("Team name: %s\n", teams[i].name);
        printf("Total score: %d\n", teams[i].totalScore);
        printf("\n");
    }
}

void inputResultsAndCalculateScores() {
    int M, W;
    printf("Please enter the number of men's events: ");
    scanf("%d", &M);
    printf("Please enter the number of women's events: ");
    scanf("%d", &W);

    for (int i = 0; i < teamCount; i++) {
        printf("Please enter the scores for team %d:\n", i + 1);
        for (int j = 0; j < M + W; j++) {
            printf("Please enter the score for event %s: ", teams[i].events[j]);
            scanf("%d", &teams[i].scores[j]);
            teams[i].totalScore += teams[i].scores[j];
        }
    }

    printf("Scores calculated successfully!\n");
}
void queryScore() {
    int teamIndex, playerIndex;
    printf("Please enter the team index: ");
    scanf("%d", &teamIndex);
    printf("Please enter the player index: ");
    scanf("%d", &playerIndex);

    if (teamIndex < 1 || teamIndex > teamCount) {
        printf("Invalid team index!\n");
        return;
    }

    if (playerIndex < 1 || playerIndex > 5 || teams[teamIndex - 1].players[playerIndex - 1].name[0] == '\0') {
        printf("Invalid player index!\n");
        return;
    }

    printf("Team name: %s\n", teams[teamIndex - 1].name);
    printf("Player name: %s\n", teams[teamIndex - 1].players[playerIndex - 1].name);
    printf("Score: %d\n", teams[teamIndex - 1].players[playerIndex - 1].score);
}

void deletePlayer() {
    int teamIndex, playerIndex;
    printf("Please enter the team index: ");
    scanf("%d", &teamIndex);
    printf("Please enter the player index: ");
    scanf("%d", &playerIndex);

    if (teamIndex < 1 || teamIndex > teamCount) {
        printf("Invalid team index!\n");
        return;
    }

    if (playerIndex < 1 || playerIndex > 5 || teams[teamIndex - 1].players[playerIndex - 1].name[0] == '\0') {
        printf("Invalid player index!\n");
        return;
    }

    teams[teamIndex - 1].totalScore -= teams[teamIndex - 1].players[playerIndex - 1].score;
    teams[teamIndex - 1].scores[0] -= teams[teamIndex - 1].players[playerIndex - 1].score;
    teams[teamIndex - 1].players[playerIndex - 1].name[0] = '\0';

    printf("Player deleted successfully!\n");
}

void saveData() {
    FILE *fp = fopen("sportsmeet_data.txt", "w");
    if (fp == NULL) {
        printf("Failed to save data!\n");
        return;
    }

    for (int i = 0; i < teamCount; i++) {
        fprintf(fp, "%s\n", teams[i].name);
        fprintf(fp, "%d\n", teams[i].totalScore);
        for (int j = 0; j < 5; j++) {
            if (teams[i].players[j].name[0] != '\0') {
                fprintf(fp, "%s %d\n", teams[i].players[j].name, teams[i].players[j].score);
            }
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("Data saved successfully!\n");
}

void loadData() {
    FILE *fp = fopen("sportsmeet_data.txt", "r");
    if (fp == NULL) {
        printf("Failed to load data!\n");
        return;
    }



    while (1) {
        char name[20];
        int score;

        if (fscanf(fp, "%s", name) == EOF) {
            break;
        }

        strcpy(teams[teamCount].name, name);
        fscanf(fp, "%d", &teams[teamCount].totalScore);

        for (int i = 0; i < 5; i++) {
            if (fscanf(fp, "%s %d", name, &score) == EOF) {
                break;
            }
            strcpy(teams[teamCount].players[i].name, name);
            teams[teamCount].players[i].score = score;
        }

        teamCount++;
    }

    fclose(fp);
    printf("Data loaded successfully!\n");

}
    int main(){
        int choice;

        while (1) {
            printf("Please select an option:\n");
            printf("1. Add team\n");
            printf("2. Add player\n");
            printf("3. Display team information\n");
            printf("4. Generate report\n");
            printf("5. Input results and calculate scores\n");
            printf("6. Query score\n");
            printf("7. Delete player\n");
            printf("8. Save data\n");
            printf("9. Load data\n");
            printf("10. Quit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addTeam();
                    break;
                case 2:
                    addPlayer();
                    break;
                case 3:
                    displayTeamInfo();
                    break;
                case 4:
                    generateReport();
                    break;
                case 5:
                    inputResultsAndCalculateScores();
                    break;
                case 6:
                    queryScore();
                    break;
                case 7:
                    deletePlayer();
                    break;
                case 8:
                    saveData();
                    break;
                case 9:
                    loadData();
                    break;
                case 10:
                    printf("Goodbye!\n");
                    exit(0);
                default:
                    printf("Invalid choice! Please try again.\n");
                    break;
            }
        }

        return 0;
    }
