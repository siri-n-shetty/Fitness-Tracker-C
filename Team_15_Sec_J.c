#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct WorkoutNode {
    char date[20];
    char exercise[50];
    int duration;      
    int caloriesBurnt;  
    struct WorkoutNode* next;
};

struct NutritionNode {
    char date[20];
    char food[50];
    int calorieIntake;  
    struct NutritionNode* next;
};

struct HealthNode {
    char date[20];
    float weight;          
    float height;          
    int calorieIntake;     
    struct HealthNode* next;
};

struct User {
    char username[50];
    char password[50];
    struct WorkoutNode* workoutLogs;
    struct NutritionNode* nutritionInfo;
    struct HealthNode* healthMetrics;
    struct User* next;
};

struct User* createUser(const char* username, const char* password) {
    struct User* newUser = (struct User*)malloc(sizeof(struct User));
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->workoutLogs = NULL;
    newUser->nutritionInfo = NULL;
    newUser->healthMetrics = NULL;
    newUser->next = NULL;
    return newUser;
}

void addUser(struct User** userList, const char* username, const char* password) {
    struct User* newUser = createUser(username, password);
    newUser->next = *userList;
    *userList = newUser;
}

struct User* findUser(struct User* userList, const char* username) {
    while (userList != NULL) {
        if (strcmp(userList->username, username) == 0) {
            return userList;
        }
        userList = userList->next;
    }
    return NULL;
}

struct User* authenticateUser(struct User* userList, const char* username, const char* password) {
    struct User* user = findUser(userList, username);
    if (user != NULL && strcmp(user->password, password) == 0) {
        return user;
    }
    return NULL;
}

void addWorkoutLog(struct WorkoutNode** head, const char* date, const char* exercise, int duration, int caloriesBurnt) {
    struct WorkoutNode* newNode = (struct WorkoutNode*)malloc(sizeof(struct WorkoutNode));
    strcpy(newNode->date, date);
    strcpy(newNode->exercise, exercise);
    newNode->duration = duration;
    newNode->caloriesBurnt = caloriesBurnt;
    newNode->next = *head;
    *head = newNode;
}

int chooseExercise() {
    int choice;
    printf("Choose an exercise:\n");
    printf("1. Swimming\n2. Running\n3. Skipping\n4. Cycling\n5. Walking\n");
    printf("6. Treadmill\n7. Climbing\n8. Trail Running\n9. Skiing\n10. Freestyle\n");
    printf("Enter your choice (1-10): ");
    scanf("%d", &choice);

    return choice;
}

void addNutritionInfo(struct NutritionNode** head, const char* date, const char* food, int calorieIntake) {
    struct NutritionNode* newNode = (struct NutritionNode*)malloc(sizeof(struct NutritionNode));
    strcpy(newNode->date, date);
    strcpy(newNode->food, food);
    newNode->calorieIntake = calorieIntake;
    newNode->next = *head;
    *head = newNode;
}

void addHealthMetrics(struct HealthNode** head, const char* date, float weight, float height) {
    struct HealthNode* newNode = (struct HealthNode*)malloc(sizeof(struct HealthNode));
    strcpy(newNode->date, date);
    newNode->weight = weight;
    newNode->height = height;
    newNode->next = *head;
    *head = newNode;
}

void displayWorkoutLogs(struct WorkoutNode* head) {
    printf("Workout Logs:\n");
    while (head != NULL) {
        printf("Date: %s, Exercise: %s, Duration: %d minutes, Calories burnt: %d\n", head->date, head->exercise, head->duration, head->caloriesBurnt);
        head = head->next;
    }
    printf("\n");
}

void displayNutritionInfo(struct NutritionNode* head) {
    printf("\nNutrition Information:\n");

    while (head != NULL) {
        printf("Date: %s, Food: %s, Calorie Intake: %d\n", head->date, head->food, head->calorieIntake);
        head = head->next;
    }

    printf("\n");
}

void displayHealthMetrics(struct HealthNode* head) {
    printf("Health Metrics:\n");
    while (head != NULL) {
        printf("Date: %s, Weight: %.2f kg, Height: %.2f meters\n", head->date, head->weight, head->height);
        head = head->next;
    }
    printf("\n");
}

void setCustomGoals(struct User* user) {
    float targetWeightLoss;
    int targetWeeklyWorkoutDuration;
    int targetCalorieLoss;

    printf("Enter your target weight loss (in kilograms): ");
    scanf("%f", &targetWeightLoss);

    printf("Enter your target weekly workout duration (in minutes): ");
    scanf("%d", &targetWeeklyWorkoutDuration);

    printf("Enter your target daily calorie loss (in calories): ");
    scanf("%d", &targetCalorieLoss);

    printf("Your entered goals:\n");
    printf("1. Target Weight Loss: %.2f kg\n", targetWeightLoss);
    printf("2. Target Weekly Workout Duration: %d minutes\n", targetWeeklyWorkoutDuration);
    printf("3. Target Daily Calorie Loss: %d calories\n", targetCalorieLoss);
}

void displayScatterPlot(struct NutritionNode* nutritionHead, struct WorkoutNode* workoutHead) {
    printf("\nScatter Plot of Workout Durations:\n");

    struct WorkoutNode* workoutDurationHead = workoutHead;  

    while (workoutDurationHead != NULL) {
        printf("%s: ", workoutDurationHead->date);

        for (int i = 0; i < workoutDurationHead->duration; i++) {
            printf("*");
        }

        printf("\n");
        workoutDurationHead = workoutDurationHead->next;
    }

    printf("\nLegend:\n");
    printf("* - 1 minute of workout\n");

    printf("\nScatter Plot of Calories Burnt:\n");

    struct WorkoutNode* caloriesBurntHead = workoutHead;  

    while (caloriesBurntHead != NULL) {
        printf("%s: ", caloriesBurntHead->date);

        for (int i = 0; i < caloriesBurntHead->caloriesBurnt/10; i++) {
            printf("*");
        }

        printf("\n");
        caloriesBurntHead = caloriesBurntHead->next;
    }

    printf("\nScatter Plot of Calorie Intake:\n");

    while (nutritionHead != NULL) {
        printf("%s: ", nutritionHead->date);

        for (int i = 0; i < nutritionHead->calorieIntake/10; i++) {
            printf("*");
        }

        printf("\n");
        nutritionHead = nutritionHead->next;
    }

    printf("\nLegend:\n");
    printf("* - 1 unit\n");
}


int main() {
    struct User* userList = NULL;
    struct User* currentUser = NULL;

    printf("Welcome to the Fitness Tracking System!\n");

    int choice;
    do {
        printf("\nMain Menu:\n\n1. Create Account\n2. Log In\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char username[50];
                char password[50];
                printf("Enter your username: ");
                scanf("%s", username);
                printf("Enter your password: ");
                scanf("%s", password);
                addUser(&userList, username, password);
                printf("Account created successfully!\n");
                break;
            }
            case 2: {
                char username[50];
                char password[50];
                printf("Enter your username: ");
                scanf("%s", username);
                printf("Enter your password: ");
                scanf("%s", password);
                currentUser = authenticateUser(userList, username, password);
                if (currentUser != NULL) {
                    printf("Login successful!\n");

                    int userChoice;
                    do {
                        printf("\nExplore the Menu:\n\n1. Update Workout Logs\n2. Update Nutrition Information\n3. Update Health Metrics\n");
                        printf("4. Display Workout Logs\n5. Display Nutrition Information\n6. Display Health Metrics\n7. Visulaization\n8. Set Achievable Goals\n");
                        printf("9. Logout\n\nEnter your choice: ");
                        scanf("%d", &userChoice);

                        switch (userChoice) {
                            case 1: {
                                char date[20];
                                char exercise[50];
                                int duration;
                                int caloriesBurnt;  
                                printf("Enter date (YYYY-MM-DD): ");
                                scanf("%s", date);

                                printf("Enter exercise: ");
                                
                                int exerciseChoice = chooseExercise();

                                switch (exerciseChoice) {
                                    case 1:
                                        strcpy(exercise, "Swimming");
                                        break;
                                    case 2:
                                        strcpy(exercise, "Running");
                                        break;
                                    case 3:
                                        strcpy(exercise, "Skipping");
                                        break;
                                    case 4:
                                        strcpy(exercise, "Cycling");
                                        break;
                                    case 5:
                                        strcpy(exercise, "Walking");
                                        break;
                                    case 6:
                                        strcpy(exercise, "Treadmill");
                                        break;
                                    case 7:
                                        strcpy(exercise, "Climbing");
                                        break;
                                    case 8:
                                        strcpy(exercise, "Trail Running");
                                        break;
                                    case 9:
                                        strcpy(exercise, "Skiing");
                                        break;
                                    case 10:
                                        strcpy(exercise, "Freestyle");
                                        break;
                                    default:
                                        printf("Invalid exercise choice.\n");
                                        break;
                                }

                                printf("Enter duration (minutes): ");
                                scanf("%d", &duration);
                                printf("Enter calories burnt: ");
                                scanf("%d", &caloriesBurnt);
                                addWorkoutLog(&currentUser->workoutLogs, date, exercise, duration, caloriesBurnt);
                                printf("Workout log added!\n");
                                break;
                            }

                            case 2: {
                                char date[20];
                                char food[50];
                                int calories;
                                printf("Enter date (YYYY-MM-DD): ");
                                scanf("%s", date);
                                printf("Enter food: ");
                                scanf("%s", food);
                                printf("Enter calories: ");
                                scanf("%d", &calories);
                                addNutritionInfo(&currentUser->nutritionInfo, date, food, calories);
                                printf("Nutrition information added!\n");
                                break;
                            }
                            case 3: {
                                char date[20];
                                float weight, height;
                                printf("Enter date (YYYY-MM-DD): ");
                                scanf("%s", date);
                                printf("Enter weight (kg): ");
                                scanf("%f", &weight);
                                printf("Enter height (meters): ");
                                scanf("%f", &height);
                                addHealthMetrics(&currentUser->healthMetrics, date, weight, height);
                                printf("Health metrics added!\n");
                                break;
                            }
                            case 4: {
                                displayWorkoutLogs(currentUser->workoutLogs);
                                break;
                            }
                            case 5: {
                                displayNutritionInfo(currentUser->nutritionInfo);
                                break;
                            }
                            case 6: {
                                displayHealthMetrics(currentUser->healthMetrics);
                                break;
                            }
                            case 7: {
                                displayScatterPlot(currentUser->nutritionInfo, currentUser->workoutLogs);
                                break;
                            }
                            case 8: {
                                setCustomGoals(currentUser);
                                break;
                            }
                            case 9: {
                                printf("Logging out...\n");
                                break;
                            }
                            default: {
                                printf("Invalid choice. Please try again.\n");
                            }
                        }
                    } while (userChoice != 9);
                } else {
                    printf("Login failed. Invalid username or password.\n");
                }
                break;
            }
            case 3: {
                printf("Exiting. Thank You!\n");
                break;
            }
            default: {
                printf("Invalid choice. Please try again.\n");
            }
        }
    } while (choice != 3);

    while (userList != NULL) {
        struct User* tempUser = userList;
        userList = userList->next;

        while (tempUser->workoutLogs != NULL) {
            struct WorkoutNode* temp = tempUser->workoutLogs;
            tempUser->workoutLogs = tempUser->workoutLogs->next;
            free(temp);
        }

        while (tempUser->nutritionInfo != NULL) {
            struct NutritionNode* temp = tempUser->nutritionInfo;
            tempUser->nutritionInfo = tempUser->nutritionInfo->next;
            free(temp);
        }

        while (tempUser->healthMetrics != NULL) {
            struct HealthNode* temp = tempUser->healthMetrics;
            tempUser->healthMetrics = tempUser->healthMetrics->next;
            free(temp);
        }

        free(tempUser);
    }

    return 0;
}