#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define IP_MAX 15
#define BIN_MAX 35
#define SEGMENT_MAX 255


int convert_to_bin();
int is_ip_valid(char ip_string[]);

int convert_to_ip();
int is_bin_valid(char bin_string[]);

void print_with_border(char str[]);


int main() 
{
    print_with_border("Welcome to Sawyer's Networking Tool");

    int tool_index;
    while(1)
    {
        printf("\033[36mTools -\n");
        printf("1.\033[38;5;208m IP to BIN\n");
        printf("\033[36m2.\033[38;5;208m BIN to IP\n");
        printf("\033[36m3.\033[38;5;208m\n");
        printf("\033[36m4.\033[38;5;208m\033[36m\n\n");
        
        printf("Enter the number of the tool to use:\033[38;5;208m ");
        scanf("%d", &tool_index);

        if((tool_index == 1 && !convert_to_bin()) || (tool_index == 2 && !convert_to_ip()))
        {
            print_with_border("Invalid input, please try again");
        }
    }
}


int convert_to_bin()
{
    printf("\033[36mEnter the IP address:\033[38;5;208m ");

    char ip_string[IP_MAX];
    scanf("%s", ip_string);

    if(!is_ip_valid(ip_string))
    {
        return 0;
    }

    int ip_array[4] = {0};
    int segment_index = 0;

    for(int i = 0; i <= strlen(ip_string); i++)
    {
        if(isdigit(ip_string[i]))
        {
            ip_array[segment_index] = ip_array[segment_index] * 10 + ip_string[i] - '0';
        }
        else
        {
            segment_index++;
        }
    }

    char bin_string[BIN_MAX];
    bin_string[0] = '\0';

    for(int i = 0; i < 4; i++)
    {
        char bin_segment[9];
        bin_segment[8] = '\0';

        for(int j = 7; j >= 0; j--)
        {
            bin_segment[j] = (ip_array[i] & 1) + '0';
            ip_array[i] >>= 1;
        }

        strcat(bin_string, bin_segment);

        if(i < 3)
        {
            strcat(bin_string, ".");
        }
    }

    print_with_border(bin_string);

    return 1;
}

int is_ip_valid(char ip_string[])
{
    int period_count = 0;
    int current_segment = 0;

    if(ip_string[0] == '.')
    {
        return 0;
    }

    for(int i = 0; ip_string[i] != '\0'; i++)
    {
        if(!isdigit(ip_string[i]) && ip_string[i] != '.')
        {
            return 0;
        }

        if(ip_string[i] == '.')
        {
            if(current_segment > SEGMENT_MAX)
            {
                return 0;
            }

            current_segment = 0;
            period_count++;
        } 
        else
        {
            int digit = ip_string[i] - '0';
            current_segment = current_segment * 10 + digit;
        }
    }

    if(current_segment > SEGMENT_MAX || period_count != 3)
    {
        return 0;
    }

    return 1;
}


int convert_to_ip()
{
    printf("\033[36mEnter the binary address:\033[38;5;208m ");

    char bin_string[BIN_MAX];
    scanf("%s", bin_string);

    if(!is_bin_valid(bin_string))
    {
        return 0;
    }
    
    int bin_array[BIN_MAX] = {0};
    int ip_array[4] = {0};

    for(int i = 0; i < strlen(bin_string); i++)
    {
        bin_array[i] = bin_string[i] - '0';
    }

    int count = 0;

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            ip_array[i] = ip_array[i] * 2 + bin_array[count];
            count++;
        }
        count++;
    }

    char ip_string[IP_MAX];
    ip_string[0] = '\0';

    for(int i = 0; i < 4; i++)
    {
        char ip_segment[8];

        sprintf(ip_segment, "%d", ip_array[i]);

        strcat(ip_string, ip_segment);
        
        if(i < 3)
        {
            strcat(ip_string, ".");
        }
    }

    print_with_border(ip_string);

    return 1;
}

int is_bin_valid(char bin_string[])
{
    if(strlen(bin_string) != BIN_MAX) 
    {
        return 0;
    }

    int period_count = 0;
    for(int i = 0; i < strlen(bin_string); i++)
    {
        if(i % 9 == 8)
        {
            if(bin_string[i] != '.')
            {
                return 0;
            }
            period_count++;
        } 
        else if(bin_string[i] != '0' && bin_string[i] != '1') 
        {
            return 0;
        }
    }

    if(period_count != 3) 
    {
        return 0;
    }

    return 1;
}


void print_with_border(char str[])
{
    printf("\n\033[38;5;208m+------");
    
    for(int i = 0; i < strlen(str); i++)
    {
        printf("-");
    }

    printf("+\n| -\033[36m %s \033[38;5;208m- |\n+", str);
    
    for(int i = 0; i < strlen(str); i++)
    {
        printf("-");
    }

    printf("------+\033[0m\n\n");
}