#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DAYS 7
#define MAX_ENTRIES 100
#define CALORIES_PER_STEP 0.05
// Stores the health metrics for each day you want
typedef struct{
    char date[11]; // casual date format: yyyy-mm-dd
    int steps;
    int calories;
    float water;
    float sleep;
    int heart_rate;
    char name[55];
    int gender;
    float weight;
    float height;
} HealthMetrics;

HealthMetrics health_log[MAX_ENTRIES];
int entry_count = 0; // starts a count to keep track the entries

//The health metrics are stored for each day
typedef struct {
    int day;
    HealthMetrics metrics;
} DailyData;

//user profile :
typedef struct {
    char name[55];
    int age;
    int gender;
    float height;
    float weight;
    int steps;
    float stride_length;
    float activity_level;
}HealthProfile;

//Stores the steps and day
typedef struct{
    int days;
    int steps;
} StepData;

HealthProfile user;

//Function prototypes to be used in the main function (main idea the to do list side project from my github account)
void add_entry(/*arguments*/);
void view_report();
void save_data();
void load_data();
void generate_weekly_summary();
void analyze_trends();
void estimate_caloric_expenditure();
void generate_ascii_chart();
void alert_unhealthy_patterns();
void predict_future_health();
void load_user_profile();
void save_user_profile();
void delete_entry();
void compare_days();


// For the function about ascii bar chart the whole idea is like exp from 2d games from the past and my repository of tick tac toc in c
void draw(const char *name_of_value, int value, const char *date){
    printf("%-20s", name_of_value); //left aligning by 20 characters
    for (int i = 0; i < value; i++){
        printf("|");
    }
    printf(" %d (%s)\n", value, date);
}

//Shows an entry from the health log array and checks if date and name are similar to others from previous entries so it can open the right report
void view_report(){
    char date[11];
    char name[55];
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter the date (YYYY-MM-DD) to view the report:");
    scanf("%s", date);
    int found = 0;
        for (int i = 0; i < entry_count; i++) {
            if (strcmp(health_log[i].date, date) == 0 && strcmp(health_log[i].name, name) == 0 ){
                printf("\nHealth Report for %s on %s\n", name, date);
                printf("Steps: %d\n", health_log[i].steps);
                printf("Calories: %d\n", health_log[i].calories);
                printf("Water: %.1f liters\n", health_log[i].water);
                printf("Sleep: %.1f hours\n", health_log[i].sleep);
                if (health_log[i].heart_rate != -1)//for option 0 == if the user had count the heart_rate that day!
                    printf("Heart Rate: %d bpm\n", health_log[i].heart_rate);
                    printf("Stride Length: %.2f meters\n", user.stride_length);
                found = 1;
                break;
            }
        }
        if (!found){
            printf("No official record found for %s on %s\n", name, date);
        }
    }

    void viewDailyDate(DailyData data[], int day){
        for (int i = 0; i < DAYS; i++) {
            if (data[i].day == day){
                printf("Daily data for day %d:\n", day);
                printf("Steps: %d\n", data[i].metrics.steps);
                printf("Calories that have been consumed: %d\n", data[i].metrics.calories);
                printf("Water you drunk: %.1f L\n", data[i].metrics.water);
                printf("The time you slept: %.1f hours\n", data[i].metrics.sleep);
                if (data[i].metrics.heart_rate != -1)
                    printf("Heart Rate: %d bpm\n", data[i].metrics.heart_rate);
                return;
            }
        }
    
    printf("No data found for day %d\n", day);
    printf("Error in the matrix! Please dear user enter a valid day\n");}

    //Generates the weekly summary of the health metrics
    void generate_weekly_summary(){
        int totalSteps = 0;
        int totalCalories = 0;
        float totalWater = 0;
        float totalSleep = 0;
        int totalHeart = 0;
        int heartCount = 0;
    
        for (int i = 0; i<entry_count; i++){
            totalSteps += health_log[i].steps;
            totalCalories += health_log[i].calories;
            totalWater += health_log[i].water;
            totalSleep += health_log[i].sleep;
            if (health_log[i].heart_rate != -1){
                totalHeart += health_log[i].heart_rate;
                heartCount++; //ok about the special case of heart rate
            }
        }
    
    //weekly summary of the health metrics
    printf("Weekly summary of your health metrics for this week:\n");
    printf("The average steps of this week are: %d\n", totalSteps / entry_count);
    printf("Average calories you have consumed: %d kcal\n", totalCalories / entry_count);
    printf("You have drunk this week: %.2f litters of water\n", totalWater / entry_count);
    printf("You have slept about: %.2f hours\n", totalSleep / entry_count);
    if (heartCount > 0){
        printf("Average heart rate: %d bmp\n", totalHeart / heartCount);
    }
}

//analyze the trends of metrics(task 2)!
void analyze_trends(){
    int maxSteps = 0;
    int maxCalories = 0;
    int maxStepsDay = 0;
    int maxCaloriesDay = 0;

//finds the day with the most cal and steps
    for (int i = 0; i < entry_count; i++){
        if (health_log[i].steps > maxSteps){
            maxSteps = health_log[i].steps;
            maxStepsDay = i;//for the steps
        }
        if (health_log[i].calories > maxCalories){
            maxCalories = health_log[i].calories;
            maxCaloriesDay = i;//for the calories 
        }
    }
    printf("Trend Analysis:\n");
printf("The day with the most steps was %s with %d steps\n", health_log[maxStepsDay].date, maxSteps);
printf("The day with the most calories consumed was %s wth %d kcal", health_log[maxCaloriesDay].date, maxCalories);
}

//for the bmr and tdee calculations :
float calcBMR(HealthProfile profile) {
    float bmr;
    if (profile.gender == 1){
        bmr = 10 * profile.weight + 6.25 * profile.height - 5 * profile.age + 5;
    } else {
        bmr = 10 * profile.weight + 6.25 * profile.height - 5 * profile.age - 161;
    }
    return bmr;
}

//calc the burned calories
//float calcBurn(HealthProfile profile) {
//    return profile.steps * profile.stride_length * profile.weight * 0.57;
//}EVEN WITH THAT OPTIONS STILL ZERO WHY;;

// Calculate burned calories by steps
void calculate_burned_calories_by_step() {
    printf("Calculating burned calories by steps:\n");
    for (int i = 0; i < entry_count; i++) {
        float burned_calories = health_log[i].steps * CALORIES_PER_STEP;
        printf("Date: %s, Name: %s, Steps: %d, Burned Calories: %.2f\n", health_log[i].date, health_log[i].name, health_log[i].steps, burned_calories);
    }
} 

float calcTDEE(HealthProfile profile){
    float BMR = calcBMR(profile);
    return BMR * profile.activity_level;
}
// prints 0 for a whatever reason
float calcBurn(HealthProfile profile){
    return profile.steps * CALORIES_PER_STEP; //burns calories for each step
}

//now the hard part is ascii bar chart for the health metrics so the user can see the progress if he select a certain date
void generate_ascii_chart(){
    printf("Generating Ascii chart:\n");
    for (int i = 0; i < entry_count; i++){
        printf("\nDate: %s\n", health_log[i].date);
        draw("Steps", health_log[i].steps / 1000, health_log[i].date);
        draw("Calories", health_log[i].calories / 100, health_log[i].date);
        draw("Water", (int)(health_log[i].water * 10), health_log[i].date);
        draw("Sleep", (int) (health_log[i].sleep * 10), health_log[i].date);
    }
}


void alert_unhealthy_patterns(){
    printf("Alerting unhealthy patterns:\n");
    for (int i = 0; i < entry_count; i++){
        if (health_log[i].water < 2.0){
            printf("You have drunk less than 2 liters of water on %s\n", health_log[i].date);
            printf("Please you must drink more water!\n");
        }
        if (health_log[i].sleep < 7.0){
            printf("You have slept less than 7 hours on %s\n", health_log[i].date);
            printf("Please you must sleep more!\n");
        }
    }
}

void predict_future_health(){
    printf("Predicting future health:\n");
    int n = entry_count; // gets the number of the entries that user have inserted
    if (n < 2){
        printf("Not enough data to predict future health, please add more data!\n");
        return;//if the user have less than 2 entries the fuction cant work and then exits
    }
double x = 0, y = 0, xy = 0, x2 = 0;
for (int i = 0; i < n; i++){
    x += i;
    y += health_log[i].steps;
    xy += i * health_log[i].steps;
    x2 += i * i;
}//maths
double m = (n * xy - x * y) / (n * x2 - x * x);
double b = (y - m * x) / n;

printf("Predicted steps for next 7 days:\n");
for (int i = n; i < n + 7; i++){
    double predicted_steps = m * i + b;
    printf("Day %d: %.0f steps\n", i - n + 1, predicted_steps);
    }
}


void estimate_caloric_expenditure(){
    float TDEE = calcTDEE(user);
    printf("Your estimated caloric expenditure is: %.2f\n", TDEE);
    float burn = calcBurn(user);
    printf("You have burned %.2f calories\n", burn);
    float BMR = calcBMR(user);
    printf("Your BMR is: %.2f\n", BMR);
}

void delete_entry(){
    char date[11];
    printf("Enter the date (YYYY-MM-DD) of the entry you want to delete: ");
    scanf("%s", date);
    int found = 0;
    for (int i = 0; i < entry_count; i++){
        if (strcmp(health_log[i].date, date) == 0){
            found = 1;
            for (int j = i; j < entry_count - 1; j++){
                health_log[j] = health_log[j + 1];
            }
            entry_count--;
            printf("Entry deleted successfully!\n");
            break;
        }
    }
    if (!found){
        printf("No entry found for %s\n", date);
    }
}

void compare_days(){
    char date1[11], date2[11];
    printf("Enter the first date (YYYY-MM-DD) that you want to compare: ");
    scanf("%s", date1);
    printf("Enter the second date (YYYY-MM-DD) that you want to compare: ");
    scanf("%s", date2);

HealthMetrics *entry1 = NULL, *entry2 = NULL; //for the dates that the user will enter
//search for the dates in log
for (int i = 0; i < entry_count; i++) {
    if (strcmp(health_log[i].date, date1) == 0) {
        entry1 = &health_log[i];
    }
    if (strcmp(health_log[i].date, date2) == 0) {
        entry2 = &health_log[i];
    }
}
//checks if the dates are true and then compares them
if (entry1 && entry2) {
    printf("\nComparison between %s and %s:\n", date1, date2);
    printf("Metric            %s    %s\n", date1, date2);
    printf("Steps             %d    %d\n", entry1->steps, entry2->steps);
    printf("Calories          %d    %d\n", entry1->calories, entry2->calories);
    printf("Water (L)         %.1f  %.1f\n", entry1->water, entry2->water);
    printf("Sleep (hours)     %.1f  %.1f\n", entry1->sleep, entry2->sleep);
    if (entry1->heart_rate != -1 && entry2->heart_rate != -1) {
        printf("Heart Rate (bpm)  %d    %d\n", entry1->heart_rate, entry2->heart_rate);
    } else {
        printf("Heart Rate (bpm)  N/A   N/A\n");
    }
} else {
    printf("One or both dates not found in the log.\n");//if something goes wrong with the dates
}
}


//lets start the program
int main() {
    int choice;
    load_user_profile();
    load_data();
printf("Welcome to your Personal Health Tracker in your computer!\n");
printf("Rules: You can add your health metrics for each day and view them later.\n");
printf("You can also generate weekly summaries, analyze trends and even compare days!\n");
printf("Look out all the rules and options in the menu below:\n");
printf("Notes:\n1)For the weekly summary (option 3) you must entry 7 continuous days\n");
printf("2)For the trends analysis (option 4) you must have at least 2 entries\n");
printf("3)For the future health prediction (option 8) you must have at least 2 entries\n");
printf("4)For the comparison between days (option 11) you must have at least 2 entries\n");
printf("5)For the caloric expenditure (option 5) you must have entered your profile\n");
printf("Also with option 5 you see the calories you have burned, your BMR and TDEE!\n");

    //like i said the program i want to look like a to do list in compiler from python sooo.....
    while(1){
        printf("\nYour Personal Health Tracker Project\n");
        printf("1. Add health entry\n");
        printf("2. View health report\n");
        printf("3. Generate weekly summary\n");
        printf("4. Analyze trends\n");
        printf("5. Estimate caloric expenditure\n");
        printf("6. Generate ASCII bar chart\n");
        printf("7. Alert for unhealthy patterns\n");
        printf("8. Predictions for your future health\n");
        printf("9. Save and Exit\n");
        printf("10. Delete entry\n");
        printf("11. Compare days\n");
        printf("12. Calculate BMI\n");
        printf("13. Export to CSV\n");
        printf("14. Exit\n");
        printf("Please choose an option to do what you want to do: ");
        scanf("%d", &choice);
        printf("\n");
        printf("\n");

        switch (choice){
            case 1: add_entry(); break;
            case 2: view_report(); break;
            case 3:generate_weekly_summary(); break;
            case 4:analyze_trends(); break;
            case 5:estimate_caloric_expenditure(); break;
            case 6:generate_ascii_chart(); break;
            case 7:alert_unhealthy_patterns(); break;
            case 8:predict_future_health(); break;
            case 9:save_data(); save_user_profile(); exit(0);
            case 10:delete_entry(); break;
            case 11:compare_days(); break;
            case 12:calculate_burned_calories_by_step(); break;
            case 13:export_to_csv(); break;
            case 14:printf("Goodbye! Have a nice day!\n"); exit(0);
            default:printf("You choose an invalid option! Try again!\n");
        }
    }
    return 0;
}
//program ends here 

void add_entry(){
    if (entry_count >= MAX_ENTRIES){
        printf("Health log is full! You can delete to empty space!\n");
        return;
    }
HealthMetrics new_entry;

printf("Enter your name please: ");
scanf("%s", new_entry.name);
printf("Enter gender (1 for male, 2 for female): ");
scanf("%d", &new_entry.gender);
printf("Enter your height in cm: ");
scanf("%f", &new_entry.height);
printf("Enter your weight in kg: ");
scanf("%f", &new_entry.weight);
printf("Enter the date (YYYY-MM-DD):");
scanf("%s", new_entry.date);
printf("Enter the steps you have taken: ");
scanf("%d", &new_entry.steps);  
printf("Enter the calories you have consumed:");
scanf("%d", &new_entry.calories);
printf("Enter the water you have drunk:");
scanf("%f", &new_entry.water);
printf("Enter the hours you have slept:");
scanf("%f", &new_entry.sleep);
printf("Enter your heart rate (bpm), (optional, press -1 to skip that step): ");
scanf("%d", &new_entry.heart_rate);
printf("Enter the stride length in meters:");
scanf("%f", &user.stride_length);
printf("Enter your activity level (1.2 for little to no exercise, 1.375 for light exercise, 1.55 for moderate exercise, 1.725 for heavy exercise, 1.9 for very heavy exercise): ");
    scanf("%f", &user.activity_level);
    health_log[entry_count++] = new_entry; //adds the new entry to the health log array
    printf("Entry added successfully!\n");
}

//394-434 save and load data
void save_data() {
    FILE *file = fopen("health_log.txt", "w");
    if (!file) {
        printf("Error saving data!\n");
        return;
    }
    for (int i = 0; i < entry_count; i++) {
        fprintf(file, "%s %d %d %.1f %.1f %d %s %d %.1f %.1f\n", health_log[i].date, health_log[i].steps,
                health_log[i].calories, health_log[i].water, health_log[i].sleep, health_log[i].heart_rate,
                health_log[i].name, health_log[i].gender, health_log[i].weight, health_log[i].height);
    }
    fclose(file);
}

void load_data() {
    FILE *file = fopen("health_log.txt", "r");
    if (!file) return;

    while (fscanf(file, "%s %d %d %f %f %d %s %d %f %f", health_log[entry_count].date, &health_log[entry_count].steps,
                &health_log[entry_count].calories, &health_log[entry_count].water,
                &health_log[entry_count].sleep, &health_log[entry_count].heart_rate,
                health_log[entry_count].name, &health_log[entry_count].gender, &health_log[entry_count].weight, &health_log[entry_count].height) != EOF) {
        entry_count++;
    }
    fclose(file);
}

void load_user_profile() {
    FILE *file = fopen("user_profile.txt", "r");
    if (!file) {
        printf("Error loading user profile!\n");
        return;
    }
    fscanf(file, "%s %d %d %f %f %d %d %f %f", user.name, &user.age, &user.gender, &user.height, &user.weight, &user.steps, &user.stride_length, &user.activity_level);
    fclose(file);
}

void save_user_profile() {
    FILE *file = fopen("user_profile.txt", "w");
    if (!file) {
        printf("Error saving user profile!\n");
        return;
    }
    fprintf(file, "%s %d %d %.1f %.1f %f %d %.2f %.2f\n", user.name, user.age, user.gender, user.height, user.weight, user.steps, user.stride_length, user.activity_level);
    fclose(file);
    printf("User profile saved successfully!\n");
}

void export_to_csv() {
    FILE *file = fopen("health_log.csv", "w");
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }

    fprintf(file, "Date,Steps,Calories,Water,Sleep,Heart Rate,Name,Gender,Weight,Height\n");
    for (int i = 0; i < entry_count; i++) {
        fprintf(file, "%s,%d,%d,%.1f,%.1f,%d,%s,%d,%.1f,%.1f\n", health_log[i].date, health_log[i].steps,
                health_log[i].calories, health_log[i].water, health_log[i].sleep, health_log[i].heart_rate,
                health_log[i].name, health_log[i].gender, health_log[i].weight, health_log[i].height);
    }
    fclose(file);
    printf("Data exported to health_log.csv successfully!\n");
}
