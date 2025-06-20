
#include <stdio.h>
#include <string.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define RESET "\033[0m"

#define max_user 10

struct booking
{
    int TicketId;
    int trainno;
    char name[50];
    int age;
    char gender;
    char reservation_status[20];
};

typedef struct
{
    char username[30];
    char password[30];
} user;

user users;
int user_count = 0;

void register_user();
int login_user();
void fix_fgets_input(char *);
void input_password(char *);
void book_tickets();
void Cancel_tickets();
void view_passenger();
void search_tickets();
void view_reservation();
void optionmenu();

int flag = 0;

int main()
{
    int user_index;
    int options;
    while (1)
    {
        printf(RED "\n==================================================\n" RESET);
        printf(GREEN "        Welcome to the Railway Login System     \n" RESET);
        printf(BLUE "==================================================\n" RESET);
        printf(MAGENTA "\n1. Register\n2. Login\n3. Exit\n" RESET);
        printf(CYAN "Select an option: " RESET);
        scanf("%d", &options);
        getchar();

        switch (options)
        {
        case 1:
            register_user();
            flag = 0;
            break;
        case 2:
            user_index = login_user();
            if (flag == 1)
            {
                printf(GREEN "\nLogin successful! Welcome, %s!\n" RESET, users.username);
            }
            else
            {
                printf(RED "\nLogin unsuccessful! Please try again.\n" RESET);
                flag = 0;
            }
            break;
        case 3:
            printf(RED "\nExiting Program ....\n" RESET);
            return -1;
        default:
            printf(YELLOW "Invalid Option! Please Try Again.\n" RESET);
        }

        if (flag == 1)
        {
            int choices;
            printf(RED "\n==========================================\n" RESET);
            printf(GREEN "     Welcome to the Train Booking System  \n" RESET);
            printf(CYAN "     Your journey starts here!            \n" RESET);
            printf(YELLOW "     Book, Cancel, and Explore with ease! \n" RESET);
            printf(RED "==========================================\n" RESET);
            printf(MAGENTA "\n1. Book tickets\n2. Cancel Tickets\n3. View Passenger Details\n4. Search Tickets\n5. View Reservation status\n6. View Options\n7. Exit\n" RESET);

            while (1)
            {
                printf(CYAN "\nChoose an option -> " RESET);
                scanf("%d", &choices);
                switch (choices)
                {
                case 1:
                    book_tickets();
                    break;
                case 2:
                    Cancel_tickets();
                    break;
                case 3:
                    view_passenger();
                    break;
                case 4:
                    search_tickets();
                    break;
                case 5:
                    view_reservation();
                    break;
                case 6:
                    optionmenu();
                    break;
                case 7:
                    printf(RED "\n\n==========================================\n" RESET);
                    printf(GREEN "     Thank you for using our system!      \n" RESET);
                    printf(BLUE "     Exiting the Train Booking System     \n" RESET);
                    printf(YELLOW "     Have a great day! Safe travels :)    \n" RESET);
                    printf(RED "==========================================\n\n" RESET);
                    return -1;
                default:
                    printf(YELLOW "Invalid option"
                                  "! Please try again.\n" RESET);
                }
            }
        }
    }
    return 0;
}
void register_user()
{
    user u;
    FILE *file = fopen("users.txt", "a"); // append mode

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter new username: ");
    scanf("%s", u.username);
    printf("Enter new password: ");
    scanf("%s", u.password);

    fwrite(&u, sizeof(user), 1, file);
    fclose(file);

    printf("\033[1;32mUser registered successfully!\033[0m\n");
}
int login_user()
{
    user u;
    char uname[50], pass[50];
    int found = 0;

    FILE *file = fopen("users.txt", "r");

    if (file == NULL)
    {
        printf("No users registered yet!\n");
        return 0;
    }

    printf("Enter username: ");
    scanf("%s", uname);
    printf("Enter password: ");
    scanf("%s", pass);

    while (fread(&u, sizeof(user), 1, file))
    {
        if (strcmp(uname, u.username) == 0 && strcmp(pass, u.password) == 0)
        {
            found = 1;
            flag = 1;
            break;
        }
    }

    fclose(file);

    if (found)
    {
        printf("\033[1;32mLogin successful!\033[0m\n");
        return 1;
    }
    else
    {
        printf("\033[1;31mInvalid username or password!\033[0m\n");
        flag = 0;
        return 0;
    }
}
void fix_fgets_input(char *string)
{
    int index = strcspn(string, "\n");
    string[index] = '\0';
}
void book_tickets()
{
    struct booking train;
    FILE *fp = fopen("TrainData.txt", "a+");
    printf("Enter your tickets id : - ");
    scanf("%d", &train.TicketId);
    printf("Enter the train no : ");
    scanf("%d", &train.trainno);
    getchar();
    printf("Enter your name : ");
    fgets(train.name, 50, stdin);
    fix_fgets_input(train.name);
    printf("Enter your age : ");
    scanf("%d", &train.age);
    printf("Enter your gender (m or f) : ");
    scanf(" %c", &train.gender);
    printf("Enter the reservation status : ");
    scanf("%s", &train.reservation_status);
    fwrite(&train, sizeof(struct booking), 1, fp);
    fclose(fp);
    printf("Tickets Booking Succesfull \n");
}
void Cancel_tickets()
{
    int cancelId, found = 0;
    FILE *file, *temp;
    struct booking b;
    file = fopen("TrainData.txt", "rb");
    temp = fopen("temp.txt", "wb");
    if (file == NULL || temp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter the tickets id for cancel : ");
    scanf("%d", &cancelId);
    while (fread(&b, sizeof(struct booking), 1, file))
    {
        if (b.TicketId == cancelId)
        {
            found = 1;
            printf(GREEN "Tickets with ID %d canceld succesfully.\n" RESET, cancelId);
        }
        else
        {
            fwrite(&b, sizeof(struct booking), 1, temp);
        }
    }
    fclose(file);
    fclose(temp);
    remove("TrainData.txt");
    rename("temp.txt", "TrainData.txt");
    if (!found)
    {
        printf(RED "tickets id not found ! \n" RESET);
    }
}
void view_passenger()
{
    FILE *fp = fopen("TrainData.txt", "r");
    char ch[100];
    struct booking temp;
    printf("Here is the Passenger Name list : \n");
    while (fread(&temp, sizeof(struct booking), 1, fp))
    {
        printf("Name : %s\n", temp.name);
        printf("Tickets Id : %d\n", temp.TicketId);
        printf("Age : %d\n", temp.age);
        printf("Status : %s\n", temp.reservation_status);
        printf("\n");
    }
    fclose(fp);
}
void search_tickets()
{
    struct booking temp;
    FILE *fp = fopen("TrainData.txt", "ab+");
    int id;
    rewind(fp);
    int found = 0;
    printf("Enter your ticked id  : ");
    scanf("%d", &id);
    char ch[50];
    while (fread(&temp, sizeof(struct booking), 1, fp))
    {
        if (id == temp.TicketId)
        {
            printf(BLUE "Tickets found \n" RESET);

            printf("Name : %s\n", temp.name);
            printf("Train no : %d\n", temp.trainno);
            printf("Tickets Id : %d\n", temp.TicketId);
            printf("Age : %d\n", temp.age);
            printf("Age : %c\n", temp.gender);
            printf("Status : %s\n", temp.reservation_status);
            found = 1;
        }
    }
    if (found == 0)
    {
        printf(RED "No tickets found " RED);
    }
}
void view_reservation()
{
    FILE *fp = fopen("TrainData.txt", "r");
    if (fp == NULL)
    {
        printf("This file is empty !");
        fclose(fp);
        return;
    }
    int id, found = 0;
    struct booking res;
    printf("Enter your tickets id no : ");
    scanf("%d", &id);
    rewind(fp);
    while (fread(&res, sizeof(struct booking), 1, fp))
    {
        if (id == res.TicketId)
        {
            printf("your reservation status is here \n");
            printf("Name: %s\n", res.name);
            printf("Status : %s\n", res.reservation_status);
            found = 1;
        }
    }
    if (!found)
    {
        printf(RED "no reservation found with this id \n" RESET);
    }
    fclose(fp);
}
void optionmenu()
{
    printf(GREEN "1. Book tickets\n2. Cancel Tickets\n3. View Passenger Details\n4. Search Tickets\n5. View Reservation status\n7. Exit\n" RESET);
}
