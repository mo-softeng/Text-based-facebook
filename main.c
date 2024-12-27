/********* main.c ********
    Student Name 	= Mohammed Osman
    Student Number	= 101312104
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{

    int *user_input_menu = malloc(sizeof(int));
    char username[50];
    char password[50];
    int second_choice;
    char new_post[250];
    char friends_name[50];
    char delete_friend_[50];
    bool deleted;

    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);

    while (1)
    {
        mainmenu(user_input_menu);

        if (*user_input_menu == 1)
        {
            printf("Enter a username: ");
            scanf("%s", username);
            printf("Enter an up to 15 characters password: ");
            scanf("%s", password);
            users = add_user(users, username, password);
            printf("User added!\n");
            continue;
        }
        else if (*user_input_menu == 2)
        {
            printf("Enter a username to update their password: ");
            scanf("%s", username);
            user_t *update_user = find_user(users, username);
            if (update_user == NULL)
            {
                printf("-----------------------------------------\n");
                printf("\t\tUser Not Found\n");
                printf("-----------------------------------------\n");
            }
            else
            {
                printf("Enter old password: ");
                scanf("%s", password);
                if (strcmp(update_user->password, password) == 0)
                {
                    printf("Enter a new password. up to 15 characters: ");
                    scanf("%s", password);
                    strcpy(update_user->password, password);
                    printf("\n**** Password changed! ****\n");
                }
                else
                {
                    printf("Failed.\n");
                    continue;
                }
            }
        }
        else if (*user_input_menu == 3)
        {
            printf("Enter a username to manage posts: ");
            scanf("%s", username);
            user_t *user = find_user(users, username);
            if (user == NULL)
            {
                printf("-----------------------------------------\n");
                printf("\t\tUser Not Found\n");
                printf("-----------------------------------------\n");
                continue;
            }
            else if (user != NULL)
            {
                printf(" -----------------------------------------------------------------------\n");
                printf("\t\tManaging %s posts\n", username);
                printf("-----------------------------------------------------------------------\n");
                if (user->posts == NULL)
                {
                    printf("Note: No posts available for %s\n\n", username);
                }
                display_all_user_posts(user);
                while (1)
                {
                    do
                    {
                        printf("1. Add a new post\n");
                        printf("2. Remove a post\n");
                        printf("3. Return to main menu\n");
                        printf("Enter your choice: ");
                        scanf("%d", &second_choice);
                    } while (second_choice > 3 || second_choice <= 0);
                    if (second_choice == 3)
                    {
                        break;
                    }
                    else if (second_choice == 2)
                    {
                        if (delete_post(user))
                        {
                            display_all_user_posts(user);
                        }
                        else
                        {
                            printf("\nError\n");
                            continue;
                        }
                    }
                    else if (second_choice == 1)
                    {
                        printf("enter a post under 250 characters\n");
                        scanf(" %[^\n]s", new_post);
                        add_post(user, new_post);
                        printf("-----------------------------------------------------------------------\n");
                        printf("\t\t\t%s\n", user->username);
                        printf("-----------------------------------------------------------------------\n");
                        display_all_user_posts(user);
                        continue;
                    }
                }
                continue;
            }
        }
        else if (*user_input_menu == 4)
        {
            printf("Enter a username to manage friends: ");
            scanf("%s", username);
            user_t *user = find_user(users, username);
            if (user != NULL)
            {
                while (1)
                {
                    do
                    {
                        printf("1. Add a new friend\n");
                        printf("2. Remove a friend\n");
                        printf("3. Return to main menu\n");
                        printf("Enter your choice: ");
                        scanf("%d", &second_choice);
                    } while (second_choice > 3 || second_choice <= 0);

                    if (second_choice == 1)
                    {
                        printf("\nenter a friend’s name: ");
                        scanf("%s", friends_name);
                        add_friend(user, friends_name);
                        printf("\nFriend added.\n");
                        continue;
                    }
                    else if (second_choice == 2)
                    {
                        display_user_friends(user);
                        printf("\nwhich friend do you want to delete. Enter their username: ");
                        scanf("%s", delete_friend_);
                        friend_t *frie = user->friends;
                        while (frie != NULL)
                        {
                            if (strcmp(frie->username, delete_friend_) == 0)
                            {
                                if (delete_friend(user, delete_friend_))
                                {
                                    display_user_friends(user);
                                    deleted = 1;
                                }
                            }
                            else
                            {
                                frie = frie->next;
                            }
                        }
                        if (deleted)
                        {
                            printf("\nFriend delelted\n");
                        }
                        else
                        {
                            printf("\nInvalid friend name\n");
                            continue;
                        }
                    }
                    else if (second_choice == 3)
                    {
                        break;
                    }
                }
                continue;
            }
            else if (user == NULL)
            {
                printf("-----------------------------------------------------------------------\n");
                printf("\t\t\t%s\n", user->username);
                printf("-----------------------------------------------------------------------\n");
                continue;
            }
        }
        else if (*user_input_menu == 5)
        {
            printf("Enter a username to manage posts: ");
            scanf("%s", username);
            user_t *user = find_user(users, username);
            if (user == NULL)
            {
                printf("\nError\n");
                continue;
            }
            else if (user != NULL)
            {
                display_posts_by_n(user, 3);
                
            }
        }
        else if (*user_input_menu == 6)
        {
            teardown(users);
            printf("\nGoodbye!\n");
            break;
        }
    }
    free(user_input_menu);
}