#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int xCal(int lnum,int num) {
    return num * num + lnum;
}

int main(int argc, char *argv[]) {
    int startn, endn;
    int day, month, year;
    int lucky_num;
    int i;
    int num;
    int result;
    time_t start, end;
    struct tm *timeinfo;
    char buffer[80];

    printf("Enter your Birthday DD MM YYYY: ");
    scanf("%d %d %d", &day, &month, &year);
    printf("Your birthday is %d-%d-%d\n", day, month, year);

    // calculate lucky number of birthday
    lucky_num = (day + month + year) % 10;
    printf("Your lucky number is %d\n", lucky_num);

    // run a for loop starting to finish by user given numbers
    printf("Enter the value of starting Number: ");
    scanf("%d", &startn);
    printf("Enter the value of ending Number: ");
    scanf("%d", &endn);

    // calculate x = given number squared + lucky number
    time(&start); // read system time before starting the loop
    for (i = startn; i <= endn; i++) {
        num = i;
        result = xCal(lucky_num, num);
        printf("%d ", result);
    }
    time(&end); // read system time after ending the loop

    // print all given numbers and calculated values in a same line using for loop
    printf("\n");

    // write all data to TXT file with student data and system time
    FILE *fp = fopen("output.txt", "w");
    if (fp == NULL) {
        printf("Error: Could not open file for writing\n");
        return 1;
    }
    timeinfo = localtime(&start);
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    fprintf(fp, "Start time: %s\n", buffer);
    timeinfo = localtime(&end);
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    fprintf(fp, "End time: %s\n", buffer);
    fprintf(fp, "Birthday: %d-%d-%d\n", day, month, year);
    fprintf(fp, "Lucky number: %d\n", lucky_num);
    fprintf(fp, "Numbers and their results:\n");
    for (i = startn; i <= endn; i++) {
        num = i;
        result =  xCal(lucky_num, num);
        fprintf(fp, "%d -> %d\n", num, result);
    }
    fclose(fp);

    // read the data from the text file and display the data with the current system time
    printf("Reading data from output.txt...\n");
    fp = fopen("output.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open file for reading\n");
        return 1;
    }
    char line[100];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);

    return 0;
}
