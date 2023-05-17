#include <stdio.h>

// Function to determine the day of the week using Zeller's Congruence
int getStartDay(int month, int day, int year) {
    if (month < 3) {
        month += 12;
        year--;
    }
    int h = (day + 2 * month + (3 * (month + 1) / 5) + year + year / 4 - year / 100 + year / 400) % 7;
    return h;
}

// Function to get the number of days in a month
int getNumDays(int month, int year) {
    int numDays;

    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            numDays = 29;
        } else {
            numDays = 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        numDays = 30;
    } else {
        numDays = 31;
    }

    return numDays;
}

// Function to display the calendar for a given month and year
void displayCalendar(int month, int year) {
    int i, j, day, numDays, startDay;

    // Array to store the names of the months
    char *months[] = {"January", "February", "March", "April", "May", "June",
                      "July", "August", "September", "October", "November", "December"};

    // Array to store the names of the days of the week
    char *daysOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    // Calculate the number of days in the given month and year
    numDays = getNumDays(month, year);

    // Determine the starting day of the month
    startDay = getStartDay(month, 1, year);

    // Print the month and year
    printf("\n%s %d\n", months[month - 1], year);

    // Print the days of the week
    for (i = 0; i < 7; i++) {
        printf("%s\t", daysOfWeek[i]);
    }
    printf("\n");

    // Print the calendar
    for (i = 0; i < startDay; i++) {
        printf("\t");
    }

    for (i = 1; i <= numDays; i++) {
        printf("%d\t", i);

        if ((startDay + i) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

int main() {
    int month, year;
    // Get the month and year from the user
    printf("Enter the month (1-12): ");
    scanf("%d", &month);
    printf("Enter the year: ");
    scanf("%d", &year);

    // Display the calendar
    displayCalendar(month, year);

    return 0;
}
