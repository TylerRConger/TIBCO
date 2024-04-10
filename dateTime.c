#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declare a global constant for amount of seconds in a day
int DAY = 86400;

// Takes in a time struct, and some pointers for hours, min, secs 
// Updates those pointers, does not return anything, just update in place
void getHMS(time_t someTime, int *hour, int *min, int *sec)
{
    // Divide by number of seconds (in an hour) and modulo for number of hours in a day (0-23)
    // Then save the hours in the passed value
    int myHours = (someTime / 3600) % 24;
    *hour = myHours;

    // Divide by number of seconds (in a minute) and modulo for number of minutes (0-59)
    // Then save the minutes in the passed value
    int myMins = (someTime / 60) % 60;
    *min = myMins;

    // Modulo so seconds are between 0-59 
    // Save the seconds in a passed value
    int mySecs = someTime % 60;
    *sec = mySecs;
}

// Take in a time struct and return the day of the week
// 0 - 6 represents the day of the week as shown below
// Sunday = 0, Monday = 1 ... Saturday = 6
// Do this without the builtins
int getDayOfWeek(time_t curTime)
{
    // 86400 seconds in a day
    int days = (int) curTime / DAY;

    // 7 days in a week, and start on thursday (+4)
    int dayOfWeek = (4 + days) % 7;

    return dayOfWeek;
}

// Take in a time struct and return the day of the week
// 0 - 6 represents the day of the week as shown below
// Sunday = 0, Monday = 1 ... Saturday = 6
int getDayOfWeekChecker(time_t curTime) 
{
    // Convert the given time to localtime, for cleanliness
    struct tm *timeinfo;
    timeinfo = localtime(&curTime);

    // Get the weekday
    int dayOfWeek = (timeinfo->tm_wday);

    // Return result
    return dayOfWeek;
}

// Take in all data about the time
// month, day, year, hour, min, second
// Each of these is zero based expect the year
// Without the use of builtins
time_t getTime(int month, int day, int year, int hour, int min, int sec)
{
    // Start at 0 (Jan 1st of 1970)
    time_t myTime = 0;
    int leapYear = 0;

    // Add up all the years that were passed, but not the current year as that is taken care of by the rest
    for (int i = 1970; i < year; i++)
    {
        myTime += 365 * DAY;

        // If that year was a leap year add the extra day
        if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
        {
            myTime += DAY;
        }
    }

    // List of the length of each month to be added to the total time
    int monthfulDays[] = {31, 28, 31, 30, 31, 31, 30, 31, 30, 31, 30, 31};

    // Loop through and add each month up to the one we are in
    for (int i = 0; i < month; i ++)
    {
        myTime += monthfulDays[i] * DAY;
        // Consider the case of we are in a leap year
        if (i == 1 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        {
            // If we are in a leap year add the extra day
            myTime += DAY;
        }
    }

    // Add hours (60 mins in an hour and 60 secs in a min)
    myTime += hour * 60 * 60;

    // Add minutes (60 seconds in a minute)
    myTime += min * 60;

    // Add seconds
    myTime += sec;

    return myTime;
}

// Take in all data about the time
// month, day, year, hour, min, second
// Each of these is zero based expect the year
time_t getTimeChecker(int month, int day, int year, int hour, int min, int sec)
{
    // Create an empty struct
    struct tm timeinfo = {0};
    time_t resultTime;

    // Save each of the values, day and year need to be altered slightly, everything else is the same
    timeinfo.tm_mon = month;
    timeinfo.tm_mday = day + 1; // time.h uses 1-31 for day
    timeinfo.tm_year = year - 1900; // adjust relative to 1900
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = min;
    timeinfo.tm_sec = sec;

    // Convert the struct to a time_t for return
    resultTime = mktime(&timeinfo);

    return resultTime;
}

int main(int argc, char** argv){

    // It's worth noting my system is set to GMT, if yours is not the checker tests may appear incorrect
    // This  is because time.h uses localtime for your system which is slightly different (21600 seconds if I switch to chicago time) 

    printf("\n\n");


    // Test case 1: January 1st, 2024 (Monday)
    time_t testTime1 = getTime(0, 0, 2024, 0, 0, 0);
    printf("Test case 1: %ld\n", testTime1);
    time_t testTime1C = getTimeChecker(0, 0, 2024, 0, 0, 0);
    printf("Test case checker 1: %ld\n", testTime1C);
    printf("Test case 1: Day of the week is %d\n", getDayOfWeek(testTime1));
    printf("Test case 1: Day of the week checker is %d\n", getDayOfWeekChecker(testTime1));

    printf("\n");
    
    // Test case 2: December 31st, 2023 (Sunday)
    time_t testTime2 = getTime(11, 30, 2023, 0, 0, 0);
    printf("Test case 2: %ld\n", testTime2);
    time_t testTime2C = getTimeChecker(11, 30, 2023, 0, 0, 0);
    printf("Test case checker 2: %ld\n", testTime2C);
    printf("Test case 2: Day of the week is %d\n", getDayOfWeek(testTime2));
    printf("Test case 2: Day of the week checker is %d\n", getDayOfWeekChecker(testTime2));
    
    printf("\n");

    // Test case 3: February 29th, 2000 (Tuesday)
    time_t testTime3 = getTime(1, 28, 2000, 12, 34, 56);
    printf("Test case 3: %ld\n", testTime3);
    time_t testTime3C = getTimeChecker(1, 28, 2000, 12, 34, 56);
    printf("Test case checker 3: %ld\n", testTime3C);
    printf("Test case 3: Day of the week is %d\n", getDayOfWeek(testTime3));
    printf("Test case 3: Day of the week checker is %d\n", getDayOfWeekChecker(testTime3));

    printf("\n");

    // Test case 4: November 15th, 1985 (Friday)
    time_t testTime4 = getTime(10, 14, 1985, 18, 45, 30);
    printf("Test case 4: %ld\n", testTime4);
    time_t testTime4C = getTimeChecker(10, 14, 1985, 18, 45, 30);
    printf("Test case checker 4: %ld\n", testTime4C);
    printf("Test case 4: Day of the week is %d\n", getDayOfWeek(testTime4));
    printf("Test case 4: Day of the week checker is %d\n", getDayOfWeekChecker(testTime4));

    printf("\n");

    // Test case 5: January 1st, 1970 (Thursday)
    time_t testTime5 = getTime(0, 0, 1970, 0, 0, 0);
    printf("Test case 5: %ld\n", testTime5);
    time_t testTime5C = getTimeChecker(0, 0, 1970, 0, 0, 0);
    printf("Test case checker 5: %ld\n", testTime5C);
    printf("Test case 5: Day of the week is %d\n", getDayOfWeek(testTime5));
    printf("Test case 5: Day of the week checker is %d\n", getDayOfWeekChecker(testTime5));
    
    printf("\n\n");
    
    // Test case 1: 12:00:00 (noon)
    int hour1, min1, sec1;
    getHMS(12 * 3600, &hour1, &min1, &sec1);
    printf("Test case 1: %02d:%02d:%02d\n", hour1, min1, sec1); 

    // Test case 2: 23:59:59 (end of the day)
    int hour2, min2, sec2;
    getHMS(23 * 3600 + 59 * 60 + 59, &hour2, &min2, &sec2);
    printf("Test case 2: %02d:%02d:%02d\n", hour2, min2, sec2);

    // Test case 3: 03:45:21
    int hour3, min3, sec3;
    getHMS(3 * 3600 + 45 * 60 + 21, &hour3, &min3, &sec3);
    printf("Test case 3: %02d:%02d:%02d\n", hour3, min3, sec3);

    // Test case 4: 00:00:00 (start of the day)
    int hour4, min4, sec4;
    getHMS(0, &hour4, &min4, &sec4);
    printf("Test case 4: %02d:%02d:%02d\n", hour4, min4, sec4);

    return 0;
}