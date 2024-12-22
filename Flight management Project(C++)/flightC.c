#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int day = 19;
int month = 5;
int year = 2024;
bool loginflag = false;
int count = 0;

typedef struct {
    char username[50];
    char password[50];
} User;

typedef struct {
    User *users;
    int numberOfUsers;
} UserManager;

void registerUser(UserManager *um) {
    char username[50];
    char password[50];

    printf("Enter User Name: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    um->users[um->numberOfUsers].username[0] = '\0';
    um->users[um->numberOfUsers].password[0] = '\0';

    strcpy(um->users[um->numberOfUsers].username, username);
    strcpy(um->users[um->numberOfUsers].password, password);

    um->numberOfUsers++;

    printf("User Registered Successfully .....\n");
}

void loginUser(UserManager *um) {
    char username[50];
    char password[50];
    printf("Enter User Name: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    bool found = false;
    for (int i = 0; i < um->numberOfUsers; i++) {
        if (strcmp(um->users[i].username, username) == 0 && strcmp(um->users[i].password, password) == 0) {
            printf("Login Successfully .....\n");
            found = true;
            loginflag = true;
            break;
        }
    }

    if (!found) {
        printf("User Not Found .....\n");
    }
}

typedef struct {
    int day;
    int month;
    int year;
} Date;

void printDate(Date date) {
    printf("%d-%d-%d", date.day, date.month, date.year);
}

Date nextDate(Date date) {
    Date newDate = date;
    int days_in_month[] = { 31, (date.year % 4 == 0 && (date.year % 100 != 0 || date.year % 400 == 0)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (newDate.day == days_in_month[newDate.month - 1]) {
        if (newDate.month == 12) {
            newDate.day = 1;
            newDate.month = 1;
            newDate.year += 1;
        } else {
            newDate.day = 1;
            newDate.month += 1;
        }
    } else {
        newDate.day += 1;
    }

    return newDate;
}

typedef struct {
    char firstName[50];
    char lastName[50];
    char mobileNo[15];
    char email[50];
    char passportNo[20];
} Person;

void getFullName(Person person, char* fullName) {
    sprintf(fullName, "%s %s", person.firstName, person.lastName);
}


typedef struct {
    char from[50];
    char to[50];
} Location;

typedef struct {
    Location location;
    int planeNo;
    char time[10];
    Date date;
} PlaneInfo;

typedef struct {
    char ticketClass[20];
} Level;

typedef struct {
    Person person;
    PlaneInfo planeInfo;
    Level ticketClass;
    int totalPrice;
    int numPerson;
    bool show;
} Ticket;

void printTicket(Ticket ticket) {
    char fullName[100];
    getFullName(ticket.person, fullName);
    printf("Full Name           : %s\n", fullName);
    printf("Mobile No           : %s\n", ticket.person.mobileNo);
    printf("Email Id            : %s\n", ticket.person.email);
    printf("From                : %s\n", ticket.planeInfo.location.from);
    printf("To                  : %s\n", ticket.planeInfo.location.to);
    printf("Passport No         : %s\n", ticket.person.passportNo);
    printf("Flight Date         : ");
    printDate(ticket.planeInfo.date);
    printf("\nTime                : %s\n", ticket.planeInfo.time);
    printf("Number of Passenger : %d\n", ticket.numPerson);
    printf("Ticket Class        : %s\n", ticket.ticketClass.ticketClass);
    printf("Total Price         : %d\n", ticket.totalPrice);
}

void menu(Ticket *tickets, int *ticketCount);

void printStoredTicket(Ticket *tickets, int ticketCount) {
    char mobileNo[15];
    printf("Enter Mobile Number: ");
    scanf("%s", mobileNo);

    bool found = false;
    for (int i = 0; i < ticketCount; i++) {
        if (strcmp(tickets[i].person.mobileNo, mobileNo) == 0) {
            found = true;
            printTicket(tickets[i]);
        }
    }

    if (!found) {
        printf("Ticket not found\n");
    }
}

void cancelTicket(Ticket *tickets, int *ticketCount) {
    char mobileNo[15];
    printf("Enter Mobile Number: ");
    scanf("%s", mobileNo);

    bool found = false;
    for (int i = 0; i < *ticketCount; i++) {
        if (strcmp(tickets[i].person.mobileNo, mobileNo) == 0) {
            for (int j = i; j < *ticketCount - 1; j++) {
                tickets[j] = tickets[j + 1];
            }
            (*ticketCount)--;
            found = true;
            printf("Ticket Cancelled Successfully\n");
            break;
        }
    }

    if (!found) {
        printf("Ticket not found\n");
    }
}

void showAllData(Ticket *tickets, int ticketCount) {
    if (ticketCount == 0) {
        printf("No Tickets Found\n");
    } else {
        for (int i = 0; i < ticketCount; i++) {
            printTicket(tickets[i]);
            printf("----------------------------------------\n");
        }
    }
}

void setAllData(Ticket *ticket) {
    printf("Enter First Name: ");
    scanf("%s", ticket->person.firstName);
    printf("Enter Last Name: ");
    scanf("%s", ticket->person.lastName);

    while (1) {
        printf("Enter Mobile No.: ");
        scanf("%s", ticket->person.mobileNo);
        if (strlen(ticket->person.mobileNo) == 10) {
            break;
        }
        printf("Enter valid Number\n");
    }

    printf("Enter Email ID: ");
    scanf("%s", ticket->person.email);
    printf("Enter Passport No.: ");
    scanf("%s", ticket->person.passportNo);
    printf("Enter Number Of Person: ");
    scanf("%d", &ticket->numPerson);
    ticket->totalPrice *= ticket->numPerson;
}

void selectTime(Ticket *ticket) {
    const char *times[] = { "08:00", "12:00", "16:00", "20:00", "23:00" };

    while (1) {
        printf("Select A Time...\n");
        for (int i = 0; i < 5; i++) {
            printf("%d: %s\n", i + 1, times[i]);
        }
        printf("6: Back\n");

        int choice;
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 5) {
            strcpy(ticket->planeInfo.time, times[choice - 1]);
            setAllData(ticket);
            break;
        } else if (choice == 6) {
            break;
        } else {
            printf("Enter Valid Number.\n");
        }
    }
}

void selectDate(Ticket *ticket) {
    Date dates[5];
    dates[0].day = day;
    dates[0].month = month;
    dates[0].year = year;
    for (int i = 1; i < 5; i++) {
        dates[i] = nextDate(dates[i - 1]);
    }

    while (1) {
        printf("Select A Date...\n");
        for (int i = 0; i < 5; i++) {
            printf("%d: ", i + 1);
            printDate(dates[i]);
            printf("\n");
        }
        printf("6: Back\n");

        int choice;
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 5) {
            ticket->planeInfo.date = dates[choice - 1];
            selectTime(ticket);
            break;
        } else if (choice == 6) {
            break;
        } else {
            printf("Enter Valid Number.\n");
        }
    }
}

int getPrice(const char *city_name) {
    struct {
        const char *city;
        int price;
    } city_prices[] = {
        { "Ahmedabad", 1000 },
        { "Mumbai", 1500 },
        { "New Delhi", 2000 },
        { "Bangalore", 2500 },
        { "Chennai", 3000 },
        { "Kolkata", 3500 },
        { "Pune", 2000 },
        { "Jaipur", 1500 },
        { "Lucknow", 2500 },
        { "Chandigarh", 3500 },
    };

    for (int i = 0; i < 10; i++) {
        if (strcmp(city_prices[i].city, city_name) == 0) {
            return city_prices[i].price;
        }
    }

    return 0;
}

void selectLocation(Ticket *ticket) {
    const char *city_names[] = {
        "Ahmedabad", "Mumbai", "New Delhi", "Bangalore", "Chennai",
        "Kolkata", "Pune", "Jaipur", "Lucknow", "Chandigarh"
    };

    while (1) {
        printf("Select A City To Go...\n");
        for (int i = 0; i < 10; i++) {
            printf("%d: %s\n", i + 1, city_names[i]);
        }
        printf("11: Back\n");

        int choice;
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 10) {
            strcpy(ticket->planeInfo.location.to, city_names[choice - 1]);
            ticket->totalPrice = getPrice(ticket->planeInfo.location.to);
            selectDate(ticket);
            break;
        } else if (choice == 11) {
            break;
        } else {
            printf("Enter Valid Number.\n");
        }
    }
}

void selectClass(Ticket *ticket) {
    const char *classes[] = { "First Class", "Business Class", "Economy Class" };

    while (1) {
        printf("Select A Class...\n");
        for (int i = 0; i < 3; i++) {
            printf("%d: %s\n", i + 1, classes[i]);
        }
        printf("4: Back\n");

        int choice;
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3) {
            strcpy(ticket->ticketClass.ticketClass, classes[choice - 1]);
            ticket->totalPrice *= (choice == 1) ? 3 : (choice == 2) ? 2 : 1;
            selectLocation(ticket);
            break;
        } else if (choice == 4) {
            break;
        } else {
            printf("Enter Valid Number.\n");
        }
    }
}

void menu(Ticket *tickets, int *ticketCount) {
    while (1) {
        printf("1: Buy Ticket\n");
        printf("2: Print Ticket\n");
        printf("3: Cancel Ticket\n");
        printf("4: Show All Tickets\n");
        printf("5: Exit\n");
        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            tickets[*ticketCount].show = true;
            selectClass(&tickets[*ticketCount]);
            (*ticketCount)++;
        } else if (choice == 2) {
            printStoredTicket(tickets, *ticketCount);
        } else if (choice == 3) {
            cancelTicket(tickets, ticketCount);
        } else if (choice == 4) {
            showAllData(tickets, *ticketCount);
        } else if (choice == 5) {
            break;
        } else {
            printf("Enter Valid Number.\n");
        }
    }
}

void welcome() {
    UserManager um = { .users = malloc(100 * sizeof(User)), .numberOfUsers = 0 };
    Ticket *tickets = malloc(100 * sizeof(Ticket));
    int ticketCount = 0;

    while (1) {
        printf("1: Register\n");
        printf("2: Login\n");
        printf("3: Exit\n");
        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            registerUser(&um);
        } else if (choice == 2) {
            loginUser(&um);
            if (loginflag) {
                menu(tickets, &ticketCount);
            }
        } else if (choice == 3) {
            free(um.users);
            free(tickets);
            exit(0);
        } else {
            printf("Invalid Choice\n");
        }
    }
}

int main() {
    welcome();
    return 0;
}
