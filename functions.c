#include"main.h"

int validate(char *argv[],file_list**head)
{
    int i=1;
    while(argv[i])
    {
        char*pos = strrchr(argv[i],'.');
        if(pos != NULL && strcmp(pos,".txt")==0)
        {
            FILE *fp = fopen(argv[i],"r");
            if(fp==NULL)
            {
                printf("%s opening failed\n",argv[i]);
                return FAILURE;
            }
            int ch;
            ch = fgetc(fp);

            if(ch==EOF)
            {
                i++;
                fclose(fp);
                continue;
            }
            
            if(check_duplicate(head,argv[i])==SUCCESS)
            {
                i++;
                continue;
            }
            insert_filelist(head,argv[i]);
            fclose(fp);
        }
        i++;
    }
	if (*head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
        file_list* temp = *head;
        printf("\nFiles added ");
	    while (temp)		
	    {
		    printf("-> %s", temp ->file_name);
		    temp = temp -> link;
	    }

	   printf("\n");
    }
    return SUCCESS;
}

void insert_filelist(file_list **head,char *arr)
{
    file_list *new = malloc(sizeof(file_list));
    strcpy(new->file_name,arr);
    new->link=NULL;

    if(*head==NULL)
    {
        *head=new;
        return;
    }
    
    file_list*temp = *head;
    while(temp->link!= NULL)
    {
        temp = temp->link;
    }
    temp->link=new;
    return;
}

int check_duplicate(file_list**head,char*arr)
{
    if(*head==NULL)
    return FAILURE;

    file_list*temp = *head;
    while(temp!=NULL)
    {
        if(strcmp(temp->file_name,arr)==0)
        return SUCCESS;
        temp = temp->link;
    }
    return FAILURE;
}

int create_db(file_list**head,hash_t*arr_t)
{
    file_list *temp = *head;
    while(temp)
    {
        FILE *fp = fopen(temp->file_name,"r");//read filename in loop and open one by one
        char word[50];
        int first;
        while(fscanf(fp,"%s",word)!=EOF) // scan word by word from opened file
        {
            if(isalpha(word[0]))
            {
                if(islower(word[0]))
                {
                    first = word[0]-'a';
                }
                else
                {
                    first = word[0]-'A';
                }
            }
            else
            {
                first = 26;// hash key;
            }

            if((arr_t[first].link)==NULL)
            {
                //create a main node if link is NULL
                main_node*new = malloc(sizeof(main_node));
                arr_t[first].link=new;
                new->file_count=1;
                strcpy(new->word,word);
                new->m_node=NULL;

                //create sub node
                sub_node*s_new = malloc(sizeof(sub_node));
                new->s_node=s_new;
                strcpy(s_new->f_name,temp->file_name);
                s_new->w_count=1;
                s_new->link=NULL;
            }
            else
            {
                main_node* m_temp = arr_t[first].link;
                // traverse main node and check if the word is present
                int flag=0;
                while(m_temp)
                {
                    sub_node* s_temp = m_temp->s_node;
                    if(strcmp(m_temp->word,word)==0)
                    {
                        //if the word is present in the main node traverse sub node to check the filename
                        while(s_temp)
                        {
                            if(strcmp(s_temp->f_name,temp->file_name)==0)
                            {
                                s_temp->w_count++;
                                flag=1;
                                break;
                            }
                            if(s_temp->link==NULL)
                            {
                                //if filename not fouund create a new sub node and link it
                                sub_node*s_new = malloc(sizeof(sub_node));
                                strcpy(s_new->f_name,temp->file_name);
                                s_new->w_count=1;
                                s_new->link=NULL;
                                s_temp->link=s_new;
                                m_temp->file_count++;
                                flag=1;
                                break;
                            }
                            s_temp = s_temp->link;
                        }
                    }

                    if(flag)
                    break; // if found the word, then break the loop

                    if(m_temp->m_node==NULL)
                    {
                        //if word not found create a new main node and link it
                        main_node*m_new = malloc(sizeof(main_node));
                        m_temp->m_node=m_new;
                        m_new->file_count=1;
                        strcpy(m_new->word,word);
                        m_new->m_node=NULL;
                        
                        //create a sub node respect to it
                        sub_node*s_new = malloc(sizeof(sub_node));
                        m_new->s_node= s_new;
                        strcpy(s_new->f_name,temp->file_name);
                        s_new->w_count=1;
                        s_new->link=NULL;
                        break;
                    }
                    m_temp= m_temp->m_node;
                }
            }
        }
        temp=temp ->link;
    }
    return SUCCESS;
}

int display_db(hash_t *arr_t)
{
    int flag=0;
    printf("\n----------------------------------------------------------\n");
    printf("%-10s %-13s%-10s  %-10s%-10s","Index", "Word", "Filecount", "File(s)", "Word count");
    printf("\n----------------------------------------------------------\n");
    for(int i=0; i<27; i++)
    {
        
        if(arr_t[i].link != NULL)
        {
            
            main_node*m_temp = arr_t[i].link;
            while(m_temp)
            {
                printf("%-5d->    ",arr_t[i].index);
                printf("%-15s %-9d",m_temp->word,m_temp->file_count);
                sub_node*s_temp = m_temp->s_node;
                while(s_temp)
                {
                    printf("%-6s\t %-5d",s_temp->f_name,s_temp->w_count);
                    s_temp=s_temp->link;
                    if(s_temp!=NULL)
                    {
                        printf("\n");
                        printf("%-36s"," ");
                    }

                }
                m_temp=m_temp->m_node;
                printf("\n");
                flag=1;
            }
            //printf("\n");
        }
    }
    printf("----------------------------------------------------------\n");
    if(flag==0)
    return FAILURE;
    else
    return SUCCESS;
}

void search_db(hash_t* arr_t,char word[])
{
    int first;
    if(isalpha(word[0]))
    {
        if(islower(word[0]))
        first=word[0]-'a';
        else
        first=word[0]-'A';
    }
    else{
        first=26;
    }

    if(arr_t[first].link)// check directly if the key is present by checking the link part
    {
        int flag=0;
        main_node* m_temp=arr_t[first].link;
        while(m_temp)
        {
            if(strcmp(m_temp->word,word)==0)
            {
                printf("%s found in %d file(s)\n",word,m_temp->file_count);
                sub_node*s_temp = m_temp->s_node;
                while (s_temp)
                {
                    printf("%s %d\n",s_temp->f_name,s_temp->w_count);
                    s_temp=s_temp->link;
                }
                flag=1;
                break;
            }
            m_temp=m_temp->m_node;
        }
        if(flag==0)
        {
            printf("word not found\n");  
            return;
        }
    }
    else
    {
        printf("word not found\n");
        return;
    }
}

int save_db(hash_t *arr_t)
{
    FILE *fp;
    fp = fopen("backup.txt","w+");//create a file named backup.txt and save hash table
    for(int i=0; i<27; i++)
    {
        if(arr_t[i].link != NULL)
        {
            fprintf(fp,"#%d;",arr_t[i].index);
            main_node*m_temp = arr_t[i].link;
            while(m_temp)
            {
                fprintf(fp,"%s;%d;",m_temp->word,m_temp->file_count);
                sub_node*s_temp = m_temp->s_node;
                while(s_temp)
                {
                    fprintf(fp,"%s;%d;",s_temp->f_name,s_temp->w_count);
                    s_temp=s_temp->link;
                }
                m_temp=m_temp->m_node;
            }
            fprintf(fp,"#\n");
        }
    }
    int ch;
    rewind(fp);
    if((ch=fgetc(fp)==EOF))
    return FAILURE;


    fclose(fp);
    return SUCCESS;
}

int update_db(file_list **head, hash_t *arr_t)
{
    FILE *fp = fopen("backup.txt","r");
    if(fp==NULL)
    return FAILURE;

    int ch = fgetc(fp);
    if(ch!='#')
    {
        printf("Backup file invalid\n");
        return FAILURE;
    }

    rewind(fp);
    
    int c;
    while((c = fgetc(fp))!=EOF)//run till EOF
    {
        ungetc(c,fp);

        int index;
        fscanf(fp,"#%d;",&index);
        int ch;
        while(1)
        {
            ch=fgetc(fp);
            if(ch == '#')
            {
                if((ch=fgetc(fp))=='\n')
                {
                    ungetc(ch,fp);
                    break;
                }
                ungetc(ch,fp);
            }
            fseek(fp,-1,SEEK_CUR);
            int file_count;
            char word[100];
            fscanf(fp,"%[^;];%d;",word,&file_count);

            main_node*new = malloc(sizeof(main_node));
            if(arr_t[index].link==NULL)
            {
                arr_t[index].link=new;
            }
            else
            {
                main_node*m_temp = arr_t[index].link;
                while(m_temp->m_node != NULL)
                {
                    m_temp=m_temp->m_node;
                }
                m_temp->m_node=new;
            }
            new->file_count=file_count;
            strcpy(new->word,word);
            new->m_node=NULL;
            new->s_node=NULL;

            for(int i=0; i<file_count; i++)
            {
                file_list *temp = *head;
                file_list *prev = NULL;

                char filename[100];
                int word_count;
                fscanf(fp,"%[^;];%d;",filename,&word_count);

                while(temp)
                {
                    if(strcmp(temp->file_name,filename)==0)
                    {
                        if(prev==NULL)
                        {
                            *head = temp->link;
                            free(temp);
                            break;
                        }
                        prev->link=temp->link;
                        free(temp);
                        break;
                    }
                    prev=temp;
                    temp=temp->link;
                }

                sub_node*s_new = malloc(sizeof(sub_node));
                if(new->s_node==NULL)
                {
                    new->s_node=s_new;
                }
                else
                {
                    sub_node*s_temp = new->s_node;
                    while(s_temp->link!=NULL)
                    {
                        s_temp=s_temp->link;
                    }
                    s_temp->link=s_new;
                }

                strcpy(s_new->f_name,filename);
                s_new->w_count=word_count;
                s_new->link=NULL;
                
            }

        }
        fgetc(fp);
    }
    return SUCCESS;
}