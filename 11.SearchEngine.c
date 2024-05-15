#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXLEN 100
#define MAXLINKS 10


typedef struct _page_t
{
    char *url;
    int visited;
    struct _page_t *links[MAXLINKS];
    struct _page_t *next;
} page_t;

void addPage(page_t **web, char *url);
void printWeb(page_t *web);
page_t *findPage(page_t *web, char *url);
void addLink(page_t *web, char *source_url, char *dest_url);
void removePage(page_t **web, char *url);
int searchPage (page_t *page, char *keyword);
void searchWeb (page_t *web, char *keyword);
void resetVisited (page_t *web, int *r);
void reachable (page_t *page);

int main(void)
{   
    char source[MAXLEN], dest[MAXLEN];
    page_t *find = NULL;
    page_t *web = {NULL};
    char url1[MAXLEN] = "\0";
    char cmd = '\0';
    char filename[100];
    char keyword[MAXLEN] = "\0";
    int value = 0;
    int  r = 0;
    while (1)
    {
        printf("Command? ");
        scanf(" %c", &cmd);
        switch (cmd)
        {
        case 'r':
        printf("Page URL? ");
        scanf(" %s", url1);
        find = findPage(web, url1);
        if(find == NULL){
            printf("No such page \"%s\"\n", url1);
        }else{
        resetVisited(web, &r);
        reachable(find);
        }
        break;
        case 'v':
        resetVisited(web, &r);
        printf("Reset %d pages\n", r);
        break;
        case 'S':
        printf("Search web for word? ");
        scanf("%s", keyword);
        if(web != NULL){
            searchWeb(web, keyword);
        }
        break;
        case 's':
       printf("Search word in page? ");
       scanf(" %s %s", url1, filename);
       find = findPage(web, filename);
       if(find == NULL){
             printf("No page \"%s\"\n", filename);
       }else{
          value = searchPage(find, url1);
           
        if(value){
            printf("Page \"%s\" contains the word \"%s\"\n", filename, url1);
        }else{
           printf("Page \"%s\" does not contain the word \"%s\"\n", filename, url1);
        } 
       }
        break;
        case 'P':
            printf("Page URL? ");
            scanf(" %s", url1);
            removePage(&web, url1);
            break;
        case 'l':
            printf("Source & destination URL? ");
            scanf(" %s %s", source, dest);
            addLink(web, source, dest);
            break;
        case 'f':
            printf("Page URL? ");
            scanf(" %s", url1);
            find = findPage(web, url1);
            if (find == NULL)
            {
                printf("URL \"%s\" is not on the web\n", url1);
            }
            else
            {
                printf("URL \"%s\" is on the web\n", url1);
            }
            break;
        case 'w':
            if (web != NULL)
            {
                printWeb(web);
            }
            break;
        case 'p':
            printf("Page URL? ");
            scanf(" %s", url1);
            addPage(&web, url1);
            break;
        case 'q':
            printf("Bye!\n");
            while (web != NULL)
            {
                removePage(&web, web->url);
            }
            return 0;
            break;
        default:
            printf("Unknown command '%c'\n", cmd);
            break;
        }
    }
    /* your code here! */
}

void addPage(page_t **web, char *url)
{
    page_t *new_node = (page_t *)malloc(sizeof(page_t));
    page_t *site = *web;

    /*if (site != NULL)
         printf(" %s", site->url);*/
    // i checked her because before *web was always pointing to the first position of new_node
    new_node->url = (char *)malloc(MAXLEN * sizeof(char)); // apparently i needed to malloc separately for the url
    strcpy(new_node->url, url);
    // printf("%s", new_node->url);
    new_node->visited = -1;
    for (int i = 0; i < MAXLINKS; i++)
    {
        if (new_node->links[i] == NULL)
        {
            continue;
        }
        new_node->links[i] = NULL;
    }

    new_node->next = NULL;

    while (site != NULL)
    {
        if (strcmp(url, site->url) == 0)
        {
            printf("URL \"%s\" is already on the web\n", url);

            free(new_node->url);
            free(new_node);
            return;
        }
        site = site->next;
    }
    site = *web;

    if (site == NULL)
    {
        *web = new_node;
        return;
        // somehow when web then always points to the values in new node
        // i think i fixed that
    }
    else if (strcmp(url, site->url) < 0) // we check if we can insert in the first position
    {
        new_node->next = *web;
        *web = new_node;
        return;
    }
    else
    {
        while (site->next != NULL)
        {
            if (strcmp(url, site->next->url) < 0)
            { // we check from the second position onwards
                new_node->next = site->next;
                site->next = new_node;
                return;
            }
            site = site->next;
        }
    }
    site->next = new_node; // in  case we get here that means we have to insert at the end of the list
}

void printWeb(page_t *web)
{
    page_t *tmp = web;

    while (tmp != NULL)
    {
        printf("{URL=\"%s\",visited=%d} ->", tmp->url, tmp->visited);

        for (int i = 0; i < MAXLINKS; i++)
        {
            if (tmp->links[i] == NULL)
            {
                continue;
            }
            else
            {
                printf(" \"%s\"", tmp->links[i]->url);
            }
        }

        printf("\n");
        tmp = tmp->next;
    }
}

page_t *findPage(page_t *web, char *url)
{
    page_t *tmp = web;
    while (tmp != NULL)
    {
        if (strcmp(tmp->url, url) == 0)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void addLink(page_t *web, char *source_url, char *dest_url)
{
    page_t *findSource = NULL;
    page_t *findDest = NULL;
    findSource = findPage(web, source_url);
    findDest = findPage(web, dest_url);
    if (findSource == NULL)
    {
        printf("Source URL \"%s\" is not on the web\n", source_url);
        return;
    }
    else if (findDest == NULL)
    {
        printf("Destination URL \"%s\" is not on the web\n", dest_url);
        return;
    }
    else if (findSource == findDest)
    {
        printf("Source and destination URL cannot be the same\n");
        return;
    }
    else if (findSource->links[MAXLINKS - 1] != NULL)
    {
        printf("Maximum number of links reached\n");
        return;
    }
    for (int i = 0; i < MAXLINKS; i++)
    {
        if (findSource->links[i] == NULL)
        {
            continue;
        }
        if (findSource->links[i] == findDest)
        {
            printf("\"%s\" is already a destination for \"%s\"\n", dest_url, source_url);
            return;
        }
    }
    for (int i = 0; i < MAXLINKS; i++)
    {
        if (findSource->links[i] == NULL)
        {
            findSource->links[i] = findDest;
            return;
        }
    }
}

void removePage(page_t **web, char *url)
{
    page_t *removed = findPage(*web, url);
    if (removed == NULL)
    {
        printf("URL \"%s\" is not on the web\n", url);
        return;
    }
    page_t *tmp = *web;
    if (tmp == removed)
    {
        page_t *rem = *web;
        while (rem != NULL)
        {
            for (int i = 0; i < MAXLINKS; i++)
            {
                if (rem->links[0] == NULL)
                {
                    continue;
                }
                if (rem->links[i] == NULL)
                {
                    continue;
                }
                else if (rem->links[i] == removed)
                {
                    rem->links[i] = NULL;
                }
            }
            rem = rem->next;
        }
        *web = tmp->next;
        free(removed->url);
        free(removed);
        tmp = tmp->next;
        return;
    }
    while (tmp->next != NULL)
    {
        if (tmp->next == removed)
        {
            page_t *rem = *web;
            while (rem != NULL)
            {
                for (int i = 0; i < MAXLINKS; i++)
                {
                    if (rem->links[i] != NULL)
                    {
                        if (rem->links[i] == removed)
                        {
                            rem->links[i] = NULL;
                        }
                    }
                }
                rem = rem->next;
            }
            tmp->next = tmp->next->next;
            free(removed->url);
            free(removed);
            return;
        }
        tmp = tmp->next;
    }
}


int searchPage(page_t *page, char *keyword) {
    FILE *file;
    char word[MAXLEN]; 
    // Open file for reading
    file = fopen(page->url, "r");
    if (file == NULL) {
        printf("Error opening file");
        return 0; // Return 0 to indicate failure
    }
    // Read words from the file until the end of file (EOF) is reached
    while (fscanf(file, "%9s", word) != EOF) {
        // Compare the word with the keyword
        if (strcmp(word, keyword) == 0) {
            fclose(file); // Close the file before returning
            return 1; // Return 1 to indicate success (keyword found)
        }
    }

    // Close the file
    fclose(file);

    // Return 0 to indicate that the keyword was not found
    return 0;
}

void searchWeb (page_t *web, char *keyword){
   FILE *file;
   char word[MAXLEN];
    while(web != NULL){
        file = fopen(web->url, "r");
        if (file == NULL) {
        printf("Error opening file");
        return;
    }
    while (fscanf(file, "%9s", word) != EOF) {
        if (strcmp(word, keyword) == 0) {
            fclose(file); 
            printf("%s\n", web->url);
            break;
        }
    }
        web = web->next;
    }
}

void resetVisited (page_t *web, int *r){
    while(web != NULL){
        if(web->visited != 0){
            web->visited = 0;
           (*r)++;
        }
        web = web->next;
    }
}


void reachable (page_t *page){
    if(page->visited == 1){
        return;
    }
    page->visited = 1;
    printf("%s\n", page->url);
    for(int i = 0; i < MAXLINKS; i++){
        if(page->links[i] == NULL){
            continue;
        }else{
            reachable(page->links[i]);
        }
    }
    return;
}
