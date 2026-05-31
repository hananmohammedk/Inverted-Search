#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct hash
{
    int index;
    struct main_node* link;
}hash_t;

typedef struct sub_node
{
    char f_name[100];
    int w_count;
    struct sub_node* link;
}sub_node;

typedef struct main_node
{
    int file_count;
    char word[100];
    struct sub_node* s_node;
    struct main_node* m_node;
}main_node;

typedef struct file_list
{
    char file_name[100];
    struct file_list* link;
}file_list;

enum
{
    SUCCESS,
    FAILURE
};

int validate(char *argv[],file_list**head);
void insert_filelist(file_list**head,char*);
int check_duplicate(file_list**head,char*);
int create_db(file_list**head,hash_t*arr_t);
int display_db(hash_t *arr_t);
void search_db(hash_t *arr_t,char word[]);
int save_db(hash_t*arr_t);
int update_db(file_list**head, hash_t *arr_t);

#endif