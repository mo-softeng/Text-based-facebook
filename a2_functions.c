/*****************
    Student Name 	= Mohammed Osman
    Student Number	= 101312104
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here
user_t *add_user(user_t *users, const char *username, const char *password)
{
    // Create a new user
    user_t *new_user = malloc(sizeof(user_t));
    assert(new_user != NULL);
    strcpy(new_user->username, username);
    strcpy(new_user->password, password);
    new_user->friends = NULL;
    new_user->posts = NULL;
    new_user->next = NULL;

    if (users == NULL || strcmp(username, users->username) < 0)
    {
        new_user->next = users;
        return new_user;
    }

    user_t *current = users;
    while (current->next != NULL && strcmp(username, current->next->username) > 0)
    {
        current = current->next;
    }

    // Insert the new user in the sorted position
    new_user->next = current->next;
    current->next = new_user;

    return users; // Return the (unchanged) head of the list
}

friend_t *create_friend(const char *username)
{
    friend_t *friend = malloc(sizeof(friend_t));
    strcpy(friend->username, username);
    friend->next = NULL;
    return friend;
}

void add_friend(user_t *user, const char *friend)
{
    // Create a new friend node
    friend_t *new_friend = create_friend(friend);
    assert(new_friend != NULL);

    friend_t *all_friends = user->friends; // header
    friend_t *prev_friend = NULL;

    // Check if the list is empty or new friend should be inserted at the head
    if (all_friends == NULL || strcmp(friend, all_friends->username) < 0)
    {
        new_friend->next = all_friends; // Insert at the head
        user->friends = new_friend;     // Update head of the list
        return;
    }

    // Traverse the list to find the correct position
    while (all_friends != NULL && strcmp(friend, all_friends->username) > 0)
    {
        prev_friend = all_friends;
        all_friends = all_friends->next;
    }

    // Insert the new friend in the sorted position
    new_friend->next = all_friends;
    prev_friend->next = new_friend;
    return;
}

post_t *create_post(const char *text)
{
    post_t *new_post = malloc(sizeof(post_t));
    assert(new_post != NULL);
    new_post->next = NULL;
    strcpy(new_post->content, text);
    return new_post;
}
void add_post(user_t *user, const char *text)
{
    post_t *post = create_post(text);

    // push to the head since its a stack
    post->next = user->posts;
    user->posts = post;
}
user_t *find_user(user_t *users, const char *username)
{ // doesnt modifiy users pointer because its passed by value.
    for (; users != NULL; users = users->next)
    {
        if (strcmp(users->username, username) == 0)
        {
            return users;
        }
    }
    return NULL;
}

_Bool delete_friend(user_t *user, char *friend_name)
{
    friend_t *friend_current = user->friends;
    friend_t *friend_prev = NULL;

    while (friend_current != NULL)
    {
        if (strcmp(friend_current->username, friend_name) == 0)
        {
            if (friend_prev == NULL)
            {
                user->friends = friend_current->next;
            }
            else
            {
                friend_prev->next = friend_current->next;
            }
            free(friend_current); // Free the memory
            return 1;
        }
        friend_prev = friend_current;          // Update previous pointer
        friend_current = friend_current->next; // Move to next node
    }
    return 0;
}

void display_all_user_posts(user_t *user)
{
    if (user->posts == NULL)
    {
        printf("No posts to show\n");
    }
    for (post_t *post = user->posts; post != NULL; post = post->next)
    {
        printf(". %s\n\n", post->content);
    }
}

void display_user_friends(user_t *user)
{
    if (user->friends == NULL)
    {
        printf("No friends to show\n");
    }
    for (friend_t *friends = user->friends; friends != NULL; friends = friends->next)
    {
        printf(".%s\n", friends->username);
    }
}

void display_posts_by_n(user_t *users, int number)
{
    char user_input;
    post_t *user_posts = users->posts;
    int n = number;
    if (!user_posts) {
        printf("User has no posts\n");
        return;
    }
    while (number != 0 && user_posts != NULL) {
        printf(". %s\n", user_posts->content);
        user_posts = user_posts->next;

        if (number == 1) {
            printf("Do you want to display more posts:(Y/N)"); 
            while (getchar() != '\n');
            scanf("%s", &user_input);
            if (user_input == 'Y' && user_posts != NULL) {
                number = 3;
                continue;
            } 
            else if (user_input == 'Y') {
                printf("\nNo more posts to show");
                return;
            } else {
                return;
            }
        }
        number--;
        
    }
 
}

void teardown(user_t *users)
{
    user_t *current_user = users;

    while (current_user != NULL) {
        user_t *next_user = current_user->next; // pointer to next user to save user.

        // free everything cur_user has:
        friend_t *user_friends = current_user->friends; 

        while (user_friends != NULL) {
            //repeat 
            friend_t *next_friend = user_friends->next;
            free(user_friends);
            user_friends = next_friend;
        }

        post_t *posts = current_user->posts;
        while (posts != NULL) {
            post_t *next_post = posts->next;
            free(posts);
            posts = next_post;
        }

        //now that everything has been freed, free the user
        free(current_user);
        current_user = next_user;

    }
}

_Bool delete_post(user_t *user)
{ // pop a post
    if (user->posts == NULL)
    {
        return false;
    }
    post_t *delete_post = user->posts;
    user->posts = delete_post->next;
    free(delete_post);
    return true;
}

void print_menu()
{
    printf("\n***********************************************\n");
    printf("\t\tMAIN MENU:\n");
    printf("***********************************************\n");
    printf("1. Register a new user\n");
    printf("2. Manage a user's profile (change password)\n");
    printf("3. Manage a user's posts (add/remove)\n");
    printf("4. Manage a user's friends (add/remove)\n");
    printf("5. Display a user’s posts\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}

void mainmenu(int *user_input_menu)
{
    do
    {
        print_menu();
        scanf("%d", user_input_menu);
        if (*user_input_menu >= 7 || *user_input_menu <= 0)
        {
            printf("Invalid choice. Please try again");
        }
    } while (*user_input_menu >= 7 || *user_input_menu <= 0);
}