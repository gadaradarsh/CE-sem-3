#include <iostream>
#include <conio.h>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;
// global

int day = 19;
int month = 05;
int year = 2024;
bool loginflag = false;
int count = 0;



class level;
class PlaneInfo;
class location;
class Person;
class Date;
class Ticket;l
class User;
class UserManager;

class User
{
    char *username;
    char *password;

public:
    User()
    {
        username = new char[50];
        password = new char[50];
    }

    User(const char *u, const char *p)
    {
        username = new char[strlen(u) + 1];
        strcpy(username, u);
        password = new char[strlen(p) + 1];
        strcpy(password, p);
    }

    User(const User &other)
    {
        username = new char[strlen(other.username) + 1];
        strcpy(username, other.username);
        password = new char[strlen(other.password) + 1];
        strcpy(password, other.password);
    }

    User &operator=(const User &other)
    {
        if (this != &other)
        {
            delete[] username;
            delete[] password;
            username = new char[strlen(other.username) + 1];
            strcpy(username, other.username);
            password = new char[strlen(other.password) + 1];
            strcpy(password, other.password);
        }
        return *this;
    }

    ~User()
    {
        delete[] username;
        delete[] password;
    }

    bool checkName(const char *name) const
    {
        return strcmp(username, name) == 0;
    }

    bool checkPass(const char *pass) const
    {
        return strcmp(password, pass) == 0;
    }

    const char *getUser() const
    {
        return username;
    }

    const char *getPass() const
    {
        return password;
    }
};

class UserManager
{
    static int numberOfUsers;
    User *users;

public:
   UserManager() : users(nullptr) {}

    ~UserManager()
    {
        delete[] users;
    }

    void registerUser()
    {
        char username[50];
        char password[50];

        cout << "Enter User Name: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        User *tempUsers = new User[numberOfUsers + 1];
        for (int i = 0; i < numberOfUsers; ++i)
        {
            tempUsers[i] = users[i];
        }

        tempUsers[numberOfUsers] = User(username, password);

        delete[] users;
        users = tempUsers;
        ++numberOfUsers;

        cout << "User Registered Successfully .....";
        _getch();
    }

    void loginUser()
    {
        char username[50];
        char password[50];

        cout << "Enter User Name: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        bool found = false;
        for (int i = 0; i < numberOfUsers; ++i)
        {
            if (users[i].checkName(username) && users[i].checkPass(password))
            {
                cout << "Login Successfully .....";
                found = true;
                loginflag = true;
                break;
            }
        }

        if (!found)
        {
            cout << "User Not Found .....";
        }
        cin.get(); 
        _getch();
    }
};

int UserManager::numberOfUsers = 0;

class Date
{
protected:
    int day;
    int month;
    int year;

public:
    Date() {}
    Date(int d, int m, int y)
    {
        day = d;
        month = m;
        year = y;
    }

    void setday(int a)
    {
        day = a;
    }

    void setmonth(int a)
    {
        month = a;
    }

    void setyear(int a)
    {
        year = a;
    }

    void setdate(Date d)
    {
        this->day = d.day;
        this->month = d.month;
        this->year = d.year;
    }

    int getday() const
    {
        return day;
    }

    int getmonth() const
    {
        return month;
    }

    int getyear() const
    {
        return year;
    }

    void incday()
    {
        day++;
    }

    void incmonth()
    {
        month++;
    }

    void incyear()
    {
        year++;
    }

    void print() const
    {
        cout << day << '-' << month << '-' << year;
    }

    Date nextDate(void)
    {
        Date nextdate;
        int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (getmonth() == 2 && (getyear() % 4 == 0 && (getyear() % 100 != 0 || getyear() % 400 == 0)))
        {
            if (getday() == 29)
            {
                incmonth();
                setday(1);
            }
            else
                incday();
        }
        else if (days[getmonth()] == 31)
        {
            if (getday() == 31)
            {
                if (getmonth() == 12)
                {
                    year++;
                    setmonth(1);
                    setday(1);
                }
                else
                {
                    incmonth();
                    setday(1);
                }
            }
            else
            {
                incday();
            }
        }
        else if (getmonth() == 2)
        {
            if (getday() == 28)
            {
                setday(1);
                incmonth();
            }
            else
            {
                incday();
            }
        }
        else
        {
            if (getday() == 30)
            {
                if (getmonth() == 12)
                {
                    year++;
                    setmonth(1);
                    setday(1);
                }
                else
                {
                    incmonth();
                    setday(1);
                }
            }
            else
            {
                incday();
            }
        }

        nextdate.setday(getday());
        nextdate.setmonth(getmonth());
        nextdate.setyear(getyear());
        return nextdate;
    }
};

class Person
{
protected:
    char *firstName;
    char *lastName;
    char *mobileNo;
    char *email;
    char *passportNo;

public:
    Person()
    {
        firstName = new char[50];
        lastName = new char[50];
        mobileNo = new char[50];
        email = new char[50];
        passportNo = new char[50];
    }
    Person(char *fn, char *ln, char *mn, char *em, char *pn)
    {
        firstName = new char[strlen(fn)];
        strcpy(firstName, fn);
        lastName = new char[strlen(ln)];
        strcpy(lastName, ln);
        mobileNo = new char[strlen(mn)];
        strcpy(mobileNo, mn);
        email = new char[strlen(em)];
        strcpy(email, em);
        passportNo = new char[strlen(pn)];
        strcpy(passportNo, pn);
    }

    char *getFirstName()
    {
        return firstName;
    }
    char *getLastName()
    {
        return lastName;
    }
    char *getMobileNo()
    {
        return mobileNo;
    }
    char *getEmail()
    {
        return email;
    }

    char *getfullname()
    {
        char *fn = new char[strlen(firstName) + strlen(lastName) + 1];
        strcpy(fn, firstName);
        strcat(fn, " ");
        strcat(fn, lastName);
    }
};

class location
{
protected:
    char *from;
    char *to;

public:
    location()
    {
        from = new char[10];
        strcpy(from, "Surat");
        to = new char[20];
    }
    location(char *t)
    {
        to = new char[strlen(t)];
        strcpy(to, t);
    }
    ~location()
    {
        delete[] from;
        delete[] to;
    }
    char *getFrom()
    {
        return from;
    }
    char *getTo()
    {
        return to;
    }

    void setFrom(char *a)
    {
        from = a;
    }
    void setTo(char *a)
    {
        to = new char[strlen(a) + 1];
        strcpy(to, a);
    }
};

class PlaneInfo : public location
{
protected:
    Date date;
    float planeNo;
    char *time;

public:
    PlaneInfo() {}
    PlaneInfo(float pn, char *t, char *from, char *to, Date d) : location(to)
    {
        date.setdate(d);
        planeNo = pn;
        time = new char[strlen(t)];
        strcpy(time, t);
    }
    ~PlaneInfo()
    {
        delete[] time;
    }
};

class level
{
protected:
    char *ticketClass;

public:
    level() {}
    level(char *tc)
    {
        ticketClass = new char[strlen(tc)];
        strcpy(ticketClass, tc);
    }
    void setLevel(char *tc)
    {
        ticketClass = new char[strlen(tc)];
        strcpy(ticketClass, tc);
    }
    char *getLevel()
    {
        return ticketClass;
    }
    void printLevel()
    {
        cout << ticketClass;
    }
    ~level()
    {
        delete[] ticketClass;
    }
};

class Ticket : public Person, public PlaneInfo
{
protected:
    bool show = true;
    level ticketClass;
    float totalprice;
    int numPerson;

public:
    Ticket()
    {
        totalprice = 0;
        mobileNo[0] = '0';
    }
    Ticket(char *tc, float tp, int np, char *firstName, char *lastName,
           char *mobileNo, char *email, char *passportNo, float pn, char *t, char *from, char *to, Date d)
        : Person(firstName, lastName, mobileNo, email, passportNo),
          PlaneInfo(pn, t, from, to, d)
    {
        ticketClass = level(tc);
        totalprice = tp;
        numPerson = np;
    }
    // menu
    void menu(Ticket *);
    void booktic();
    // int storetic();
    void printStoretic(Ticket *);
    void showAllData(Ticket *);
    void cancletic(Ticket *);
    void selectClass();
    void selectDate();
    char *selectLocation();
    int getPrice(char *);
    void selectTime();
    void setAllData();
    void print();
};

void Ticket::menu(Ticket *t)
{
    int choice;
    do
    {
        system("cls");

        cout << endl
             << "1. Book Ticket" << endl;
        cout << "2. Cancel Ticket" << endl;
        cout << "3. Show Ticket" << endl;
        cout << "4. Show All Ticket" << endl;
        cout << "5. Log Out" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        int flag = false; 

        switch (choice)
        {
        case 1:
            t[count].booktic();
            break;
        case 2:
            cancletic(t);
            break;
        case 3:
            printStoretic(t);
            break;
        case 4:
            showAllData(t);
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);
}

void Ticket::print()
{

    cout.fill('.');
    cout << endl
         << "Full Name           : " << setw(40) << right << getfullname();
    cout << endl
         << "Mobile No           : " << setw(40) << right << mobileNo;
    cout << endl
         << "Email Id            : " << setw(40) << right << email;
    cout << endl
         << "From                : " << setw(40) << right << from;
    cout << endl
         << "To                  : " << setw(40) << right << to;
    cout << endl
         << "Passport No         : " << setw(40) << right << passportNo;
    cout << endl
         << "Flight Date         : " << setw(33) << right;
    date.print();
    cout << endl
         << "Time                : " << setw(40) << right << time;
    cout << endl
         << "Number of Passenger : " << setw(40) << right << numPerson;
    cout << endl
         << "Ticket Class        : " << setw(40) << right << ticketClass.getLevel();
    cout << endl
         << "Total Price         : " << setw(40) << right << totalprice << endl;
}

void Ticket::printStoretic(Ticket *t)
{
    system("cls");

   

    bool flag = false;

    char tmobile[11];
    cout << "Enter Mobile Number: ";
    cin.ignore();
    cin >> tmobile;

    for (int i = 0; i < count; i++)
    {
        if (!strcmp(tmobile, t[i].mobileNo))
        {
            flag = true;
            t[i].print();
        }
    }


    if (!flag)
    {
        cout << endl
             << "Ticket was not found";
    }
    cout << endl
         << endl
         << "Return back(press any kay)";
    _getch();
}

void Ticket::cancletic(Ticket *t)
{
    bool flag = false;
    char tmobile[11];
    cout << "Enter Mobile Number: ";
    cin.ignore();
    cin >> tmobile;

    for (int i = 0; i < count; i++)
    {

        if (!strcmp(tmobile, t[i].mobileNo))
        {
            flag = true;
            for (int j = i; j < count; j++)
            {
                t[j] = t[j + 1];
            }
            count--;
        }
    }
}



void Ticket::showAllData(Ticket *t)
{
    system("cls");

    bool flag = false;

    for (int i = 0; i < count; i++)
    {
        flag = true;
        t[i].print();
        cout << endl
             << "-------------------------------------------" << endl;
    }


    if (!flag)
    {
        cout << endl
             << "Ticket was not found";
    }
    cout << endl
         << endl
         << "Return back(press any kay)";
    _getch();
}

void Ticket::setAllData()
{
    system("cls");

    cout << endl
         << endl
         << "Enter First Name: ";
    cin.ignore();
    cin >> firstName;
    cout << endl
         << "Enter Last Name: ";
    cin.ignore();
    cin >> lastName;
    int flag = true;
    do
    {
        if (!flag)
        {
            cout << "Enter valid Number" << endl;
        }
        cout << endl
             << "Enter Mobile No.: ";
        cin.ignore();
        cin >> mobileNo;
        if (strlen(mobileNo) != 10)
        {
            flag = false;
        }

    } while (strlen(mobileNo) != 10);

    cout << endl
         << "Enter Email ID: ";
    cin.ignore();
    cin >> email;
    cout << endl
         << "Enter Passport No.: ";
    cin.ignore();
    cin >> passportNo;
    cout << endl
         << "Enter Number Of Person: ";
    cin.ignore();
    cin >> numPerson;

    totalprice = totalprice * numPerson;

    count++;

    cout << endl
         << endl
         << "(Enter any key)" << endl;
    char c = _getch();
}

void Ticket::selectTime()
{
    int n;
    bool fleg = false;
    do
    {
        system("cls");

        cout << endl
             << "Select A Time...";
        cout << endl
             << endl
             << "1: 08:00";
        cout << endl
             << "2: 12:00";
        cout << endl
             << "3: 16:00";
        cout << endl
             << "4: 20:00";
        cout << endl
             << "5: 23:00";

        cout << endl
             << "6: Back";
        cout << endl
             << endl
             << "Select One Option: ";
        cin >> n;

        switch (n)
        {
        case 1 ... 5:
            if (n == 1)
                time = "08:00";
            else if (n == 2)
                time = "12:00";
            else if (n == 3)
                time = "16:00";
            else if (n == 4)
                time = "20:00";
            else if (n == 5)
                time = "23:00";

            setAllData();

            break;
        case 6:
            break;
        default:
            cout << endl
                 << "Enter Valid Number.";
            break;
        }
    } while (n > 6 || n < 1);
}

void Ticket::selectDate()
{
    int n;
    Date dates[5];
    dates[0].setday(::day);
    dates[0].setmonth(::month);
    dates[0].setyear(::year);

    do
    {
        system("cls");

        cout << endl
             << "Select A Date...";
        cout << endl
             << endl
             << "1: ";
        dates[0].print();
        dates[1] = dates[0].nextDate();
        cout << endl
             << "2: ";
        dates[1].print();
        dates[2] = dates[1].nextDate();
        cout << endl
             << "3: ";
        dates[2].print();
        dates[3] = dates[2].nextDate();
        cout << endl
             << "4: ";
        dates[3].print();
        dates[4] = dates[3].nextDate();
        cout << endl
             << "5: ";
        dates[4].print();

        cout << endl
             << "6: Back";
        cout << endl
             << endl
             << "Select One Option: ";
        cin >> n;

        switch (n)
        {
        case 1 ... 5:
            if (n == 1)
                date.setdate(dates[0]);
            else if (n == 2)
                date.setdate(dates[1]);
            else if (n == 3)
                date.setdate(dates[2]);
            else if (n == 4)
                date.setdate(dates[3]);
            else if (n == 5)
                date.setdate(dates[4]);

            selectTime();

            break;
        case 6:
            break;
        default:
            cout << endl
                 << "Enter Valid Number.";
            break;
        }
    } while (n > 6 || n < 1);
}

void Ticket::booktic()
{
    cout << "To:" << endl;
    char *city_name = selectLocation();
    if (!strcmp(city_name, "Back"))
        return;
    setTo(city_name);
    totalprice = getPrice(city_name);

    selectClass();
}



void Ticket::selectClass()
{
    int n;
    bool fleg = false;
    do
    {
        system("cls");

        if (fleg)
        {
            cout << endl
                 << "Enter Valid Number.";
            fleg = false;
        }
        cout << endl
             << endl
             << "1: First Class           (Extra 1500 Rs.)";
        cout << endl
             << "2: Business Class        (Extra 1000 Rs.)";
        cout << endl
             << "3: Economy Class         (No Extra Cost)";
        cout << endl
             << "4: Back";
        cout << endl
             << endl
             << "Select One Option: ";
        cin >> n;
        switch (n)
        {
        case 1 ... 3:
            if (n == 1)
            {
                ticketClass.setLevel("First Class");
                totalprice += 1500;
            }
            else if (n == 2)
            {
                ticketClass.setLevel("Business Class");
                totalprice += 500;
            }
            else
            {
                ticketClass.setLevel("Economy Class");
            }

            selectDate();
            break;

        case 4:
            break;

        default:
            fleg = true;
            break;
        }
    } while (n > 4 || n < 1);
}

int Ticket::getPrice(char *state)
{
    if (!strcmp(state, "Ahmedabad"))
        return 5000;
    else if (!strcmp(state, "Mumbai"))
        return 6000;
    else if (!strcmp(state, "Delhi"))
        return 5100;
    else if (!strcmp(state, "Chennai"))
        return 7000;
    else if (!strcmp(state, "Rajasthan"))
        return 1000;
    else if (!strcmp(state, "Maharashtra"))
        return 4000;
    else if (!strcmp(state, "Goa"))
        return 5600;
    else if (!strcmp(state, "Kerala"))
        return 5840;
    return 0;
}

char *Ticket::selectLocation()
{
    int choice;
    do
    {
        system("cls");

        cout << endl
             << "Travel Surat To...";
        cout << endl
             << endl
             << setw(20) << left << "1: Ahmedabad" << setw(7) << "5000 Rs.";
        cout << endl
             << setw(20) << left << "2: Mumbai" << setw(7) << "6000 Rs.";
        cout << endl
             << setw(20) << left << "3: Delhi" << setw(7) << "5100 Rs.";
        cout << endl
             << setw(20) << left << "4: Chennai" << setw(7) << "7000 Rs.";
        cout << endl
             << setw(20) << left << "5: Rajasthan" << setw(7) << "1000 Rs.";
        cout << endl
             << setw(20) << left << "6: Maharashtra" << setw(7) << "4000 Rs.";
        cout << endl
             << setw(20) << left << "7: Goa" << setw(7) << "5600 Rs.";
        cout << endl
             << setw(20) << left << "8: Kerala" << setw(7) << "5840 Rs.";
        cout << endl
             << setw(20) << left << "9: Back";
        cout << endl
             << endl
             << "Select One Option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            return "Ahmedabad";
        case 2:
            return "Mumbai";
        case 3:
            return "Delhi";
        case 4:
            return "Chennai";
        case 5:
            return "Rajasthan";
        case 6:
            return "Maharashtra";
        case 7:
            return "Goa";
        case 8:
            return "Kerala";
        case 9:
            return "Back";
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice < 1 || choice > 9);
}

int main()
{
    UserManager usermanager;
    int n;
    bool fleg = false;
    Ticket *t = new Ticket[50];

    do
    {
        system("cls");
        if (fleg)
        {
            cout << endl
                 << "Enter Valid Number.";
            fleg = false;
        }
        cout << endl
             << endl
             << "1: Registration User";
        cout << endl
             << "2: Login User";
        cout << endl
             << "3: Quit";
        cout << endl
             << endl
             << "Select One Option: ";

        cin >> n;

        switch (n)
        {
        case 1:
            usermanager.registerUser();
            break;

        case 2:
            usermanager.loginUser();
            if (loginflag)
            {
                t[count].menu(t);
            }
            break;

        case 3:
            break;

        default:
            fleg = true;
            break;
        }
    } while (n != 3);
}
