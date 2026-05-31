/* name : Hanan Mohammed K
   Batch_id : 25021B_135
   Project : Inverted Search
   Sample i/p : ./a.out f1.txt f2.txt
   Sample o/p : 1.create Database
                2.Search Database
                3.Display Database
                4.Save Database
                5.Update Database
                6.Exit 
   */
  #include"main.h"

int main(int argc,char *argv[])
{
   int size=27; // 26 for letters 1 for special characters and numbers

   //Hash Table initialisation
   hash_t arr_t[size];
   for(int i=0; i<size; i++)
   {
      arr_t[i].index=i;
      arr_t[i].link = NULL;
   }

   file_list*head = NULL; //filename single linked list initialisation
   if(argc>=2)
   {
      if(validate(argv,&head)==FAILURE)
      {
         printf("Validation Failed\n");
         return 0;
      }
   }
   else
   {
      printf("few arguments passed\n");
      return 0;
   }
   
   int flag=1;
   int update=0,create=0;
   while(flag)
   {
      printf("\nEnter your choice\n1.Create Data Base\n2.Search Data Base\n3.Display Data Base\n4.Save Data Base\n5.Update Data Base\n6.Exit\n");
      char choice;
      scanf(" %c",&choice);
      switch(choice)
      {
         case '1' :  {
                        if(create==1)
                        {
                           printf("DB already created\n");
                           break;
                        }
                        if(create_db(&head,arr_t)==SUCCESS)
                        {
                           create=1;
                           printf("DB created SUCCESSFULLY\n");
                        }
                        break;
                     }
         
         case '2' :  {
                        printf("\nEnter the word you want to search\n");
                        char word[50];
                        scanf("%s",word);   
                        search_db(arr_t,word);
                        break;
                     }

         case '3' :  {
                        if(display_db(arr_t)==FAILURE)
                        {
                           printf("Data Base is empty\n");
                        }
                        break;
                     }
         
         case '4' :  {
                        if(save_db(arr_t)==SUCCESS)
                        printf("DB saved successfully\n");
                        else
                        {
                           printf("File is empty\n");
                        }
                        break;
                     }

         case '5' :  {
                        if(create == 1 || update == 1 )
                        {
                           printf("DB already updated\n");
                           break;
                        }
                        if(update_db(&head,arr_t)==SUCCESS)
                        {
                           update=1;
                           printf("DB updated successfully\n");
                        }
                        else
                        printf("update error, file not found\n");
                        break;
                     }

         case '6' :  {
                        flag =0;
                        break;
                     }
         
         default  : printf("invalid choice\n");
      }
   }
   return 0;
}