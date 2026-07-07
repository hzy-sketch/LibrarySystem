#include <stdio.h>
#include <string.h>

//定义结构体
struct user{
	char username[20];
	char password[20];
};
//函数声明
void registerUser();

//主菜单
int main() {
    int choice;
    while (1) {
        printf("\n========================\n");
        printf("   图书管理系统\n");
        printf("========================\n");
        printf("1. 注册\n");
        printf("2. 登录\n");
        printf("0. 退出\n");
        printf("请输入：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                printf("登录功能待实现\n");
                break;
            case 0:
                printf("退出系统\n");
                return 0;
            default:
                printf("输入错误！\n");
        }
    }
}

//注册功能实现
void registerUser()
{
	struct user newUser;
	FILE *fp;

    	printf("请输入用户名：");
    	scanf("%s", newUser.username);
    	printf("请输入密码：");
    	scanf("%s", newUser.password);

    	fp = fopen("users.txt", "a");
    	if (fp == NULL) {
        	printf("文件打开失败！\n");
        	return;
    	}	
    	// 把结构体里的数据写入文件
    	fprintf(fp, "%s %s\n", newUser.username, newUser.password);
    	fclose(fp);
    	printf("注册成功！\n");
}
