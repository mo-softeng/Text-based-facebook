#ifndef A2_NODES_H
#define A2_NODES_H

/********* nodes.h ********
    Student Name 	= Mohammed Osman
    Student Number	= 101312104
*/

/********** DON'T MODIFY **********/
// Structure to represent a linked list of users
typedef struct user
{
    char username[30];
    char password[15];
    struct friend *friends; // linked list of friends
    struct post *posts; // stack of friends
    struct user *next; // next user
} user_t;

// Structure to represent linked list of a user's posts
typedef struct post
{
    char content[250];
    struct post *next;

} post_t;

// Structure to represent linked list of a user's posts
typedef struct friend
{
    char username[30];
    struct friend *next;
    struct post **posts;
    
}
friend_t;

#endif