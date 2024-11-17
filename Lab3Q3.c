#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_TEAMS 1  // Number of teams allowed
#define Sq_size 20   // Maximum squad size

// Struct for player details
typedef struct {
    char name[26];  // Player's full name
    int kit_number; // Kit number (1-99)
    char club[30];  // Club name
    struct {
        int day, month, year; // Date of birth
    } dob;
    char position[20]; // Player's position
} player_t;

// Struct for team details
typedef struct {
    char name[21]; // Team name
    player_t players[Sq_size]; // Array of players
    int player_count; // Current number of players
} team_t;

// Function prototypes
void display_menu(); // Show menu options
void enroll_club(team_t teams[], int *T_num); // Register a new team
void add_player(team_t teams[], int T_num); // Add a player to a team
void search_update(team_t teams[], int T_num); // Search and update player
void display_club_statistics(team_t teams[], int T_num); // Show team stats
void handle_error(const char *msg); // Display error messages

int main() {
    team_t teams[NUM_TEAMS]; // Array for teams
    int T_num = 0, choice; // Number of teams and user choice

    while (1) {
        display_menu(); // Display menu
        scanf("%d", &choice); // Get user choice
        getchar(); // Clear buffer
        switch (choice) {
            case 1: enroll_club(teams, &T_num); break; // Enroll team
            case 2: add_player(teams, T_num); break; // Add player
            case 3: search_update(teams, T_num); break; // Search/update
            case 4: display_club_statistics(teams, T_num); break; // Show stats
            default: handle_error("Exiting program."); return 0; // Exit
        }
    }
}

// Display menu options
void display_menu() {
    printf("\n--- League Team Management ---\n");
    printf("1. Register a Team\n");
    printf("2. Add Player to Team\n");
    printf("3. Search/Update Player\n");
    printf("4. Show Team Statistics\n");
    printf("Select an option: ");
}

// Register a new team
void enroll_club(team_t teams[], int *T_num) {
    if (*T_num >= NUM_TEAMS) { // Check team limit
        handle_error("Team limit reached.");
        return;
    }
    printf("Enter team name: ");
    fgets(teams[*T_num].name, sizeof(teams[*T_num].name), stdin); // Get team name
    teams[*T_num].name[strcspn(teams[*T_num].name, "\n")] = '\0'; // Remove newline
    teams[*T_num].player_count = 0; // Initialize player count
    (*T_num)++;
    printf("Team registered.\n");
}

// Add player to a team
void add_player(team_t teams[], int T_num) {
    if (T_num == 0) { // No teams available
        handle_error("No teams available.");
        return;
    }

    // List teams
    for (int i = 0; i < T_num; i++) {
        printf("%d. %s\n", i + 1, teams[i].name);
    }
    printf("Select a team: ");
    int team_index;
    scanf("%d", &team_index);
    getchar(); // Clear buffer
    team_index--;

    if (team_index < 0 || team_index >= T_num) { // Invalid selection
        handle_error("Invalid team selection.");
        return;
    }

    team_t *team = &teams[team_index];
    printf("Current player count: %d\n", team->player_count);

    if (team->player_count >= Sq_size) { // Squad full
        handle_error("Squad full.");
        return;
    }

    player_t new_player;
    printf("Enter player name: ");
    fgets(new_player.name, sizeof(new_player.name), stdin); // Get player name
    new_player.name[strcspn(new_player.name, "\n")] = '\0'; // Remove newline

    printf("Enter kit number (1-99): ");
    scanf("%d", &new_player.kit_number);
    getchar();

    printf("Enter player position: ");
    fgets(new_player.position, sizeof(new_player.position), stdin); // Get position
    new_player.position[strcspn(new_player.position, "\n")] = '\0'; // Remove newline

    printf("Enter DOB (dd mm yyyy): ");
    scanf("%d %d %d", &new_player.dob.day, &new_player.dob.month, &new_player.dob.year);
    getchar();

    // Check for duplicates
    for (int i = 0; i < team->player_count; i++) {
        if (strcmp(team->players[i].name, new_player.name) == 0 || 
            team->players[i].kit_number == new_player.kit_number) {
            handle_error("Duplicate player or kit number.");
            return;
        }
    }

    team->players[team->player_count++] = new_player; // Add player
    printf("Player added to team.\n");
}

// Search and update player
void search_update(team_t teams[], int T_num) {
    char search_name[26];
    int search_kit, choice, found = 0;

    printf("Search by (1) Name or (2) Kit Number: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        printf("Enter player name: ");
            fgets(search_name, sizeof(search_name), stdin);
            search_name[strcspn(search_name, "\n")] = '\0'; // Get search name
    } else if (choice == 2) {
        printf("Enter kit number: ");
        scanf("%d", &search_kit);
        getchar();
    } else {
        handle_error("Invalid search choice.");
        return;
    }

    // Search for player
    for (int i = 0; i < T_num && !found; i++) {
        for (int j = 0; j < teams[i].player_count; j++) {
            player_t *player = &teams[i].players[j];
            if ((choice == 1 && strcasecmp(player->name, search_name) == 0) || 
                (choice == 2 && player->kit_number == search_kit)) {
                found = 1;
                printf("Player found: %s, Kit: %d, DOB: %d-%d-%d, Position: %s\n", 
                    player->name, player->kit_number, player->dob.day, player->dob.month, 
                    player->dob.year, player->position);
                printf("Enter new position: ");
                fgets(player->position, sizeof(player->position), stdin); // Update position
                player->position[strcspn(player->position, "\n")] = '\0'; // Remove newline
                printf("Player updated.\n");
                break;
            }
        }
    }

    if (!found) {
        handle_error("Player not found.");
    }
}

// Show team statistics
void display_club_statistics(team_t teams[], int T_num) {
    for (int i = 0; i < T_num; i++) {
        team_t *team = &teams[i];
        printf("\nTeam: %s\n", team->name);
        printf("Players: %d\n", team->player_count);

        int total_age = 0;
        for (int j = 0; j < team->player_count; j++) {
            player_t *player = &team->players[j];
            int age = 2024 - player->dob.year; // Calculate age
            total_age += age;

            printf(" %d. %s, Kit: %d, Age: %d, Position: %s\n", 
                j + 1, player->name, player->kit_number, age, player->position);
        }

        printf("Average Age: %.2f\n", team->player_count ? (float)total_age / team->player_count : 0.0);
    }
}

// Display error messages
void handle_error(const char *msg) {
    printf("Error: %s\n", msg); // Show error
}
