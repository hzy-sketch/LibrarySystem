#include <stdio.h>

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
                printf("注册功能待实现\n");
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
