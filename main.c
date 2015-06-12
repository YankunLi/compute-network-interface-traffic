#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

long *my_ipconfig(char *ath0)
{
    int nDevLen = strlen(ath0);

    if (nDevLen < 1 || nDevLen > 100)
    {
        printf("dev length too long \n");
        return NULL;
    }

    int fd = open("/proc/net/dev", O_RDONLY | O_EXCL);

    if (-1 == fd)
    {
        printf("/proc/net/dev not exits!\n");
        return NULL;
    }

    char buf[1024*2];
    //重定位
    lseek(fd, 0, SEEK_SET);
    int nBytes = read(fd, buf, sizeof(buf)-1);
    if (-1 == nBytes)
    {
        perror("read error");
        close(fd);
        return NULL;
    }

    buf[nBytes] = '\n';
    //查找字串
    char * pDev = strstr(buf, ath0);
    if (NULL == pDev)
    {
        printf("don't find dev %s\n", ath0);
        return NULL;
    }
    char *p;
    char *ifconfig_value;
    int i = 0;
    static long rx2_tx10[2];
    //分割字符串
    for (p = strtok(pDev, " :\t\r\n"); p; p = strtok(NULL, " :\t\r\n"))
    {
        i++;
        ifconfig_value = (char*)malloc(20);
        strcpy(ifconfig_value, p);
        printf("%d  === %s\n", i,p);

        if(i == 2)
        {
            rx2_tx10[0] = atol(ifconfig_value); //字符串转换成整形
        }

        if(i == 10)
        {
            rx2_tx10[1] = atol(ifconfig_value);
            break;
        }
        free(ifconfig_value);
        }
        return rx2_tx10;
}

int main()
{
    long *ifconfig_result;
    double re_mb;
   // char * args = "eth0";
    ifconfig_result = my_ipconfig("eth0");
    re_mb = (double) ifconfig_result[0]/(1024 * 1024);
    printf("recive %0.2f\n", re_mb);

    re_mb = (double) ifconfig_result[1]/(1024 * 1024);
    printf("send %0.2f\n", re_mb);
}
