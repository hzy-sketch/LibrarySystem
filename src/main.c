#include <stdio.h>
#include <string.h>

/************定义结构体**************/
//用户信息结构体
struct user{
	char username[20];
	char password[20];
};
//图书信息结构体
struct book{
	char name[50];
	char author[50];
	int quantity;
};

/****************函数声明*****************/
//注册函数
void registerUser();
//登录函数
int loginUser();
//添加图书
void addBook();
//查看图书
void showBooks();

//主菜单
int main() {
    int choice;
    while (1) {
        printf("\n========================\n");
        printf("   图书管理系统\n");
        printf("========================\n");
        printf("1. 注册\n");
        printf("2. 登录\n");
	printf("3.图书管理\n");
        printf("0. 退出\n");
        printf("请输入：");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                registerUser();
                break;
            case 2:
                if(loginUser()){
        		printf("登录成功！欢迎进入图书管理系统！\n");
    		}else{
        		printf("用户名或密码错误！\n");
    		}
                break;
	    case 3:{
	
		int sub;
		printf("\n1.添加图书\n2.查看图书\n请输入:");
		scanf("%d",&sub);

		if(sub==1)addBook();
		else if(sub==2)showBooks();
		else printf("输入错误!\n");

		break;
                }
		addBook();
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

//登录功能实现
int loginUser()
{

	 struct user inputUser;
	 struct user fileUser;
	 FILE *fp;
	 int found=0;

	 printf("请输入用户名：");
	 scanf("%s",inputUser.username);

	 printf("请输入密码：");
	 scanf("%s",inputUser.password);

	 fp=fopen("users.txt","r");
	 if(fp==NULL){
                 printf("用户文件不存在！\n");
		 return 0;
	 }

	 while(fscanf(fp,"%s %s",fileUser.username,fileUser.password)!=EOF) 
	 {

		 if(strcmp(inputUser.username,fileUser.username)==0&&
		    strcmp(inputUser.password, fileUser.password)==0) 
		 {
                         found=1;
		         break;
		 }
	 }

	 fclose(fp);

	 if(found){
		printf("登录成功！\n");
		return 1;   // ✅ 成功
	 }else{
		printf("用户名或密码错误！\n");
		return 0;   // ❌ 失败
	 }

}

//实现添加图书功能
void addBook(){
    struct book b;
    FILE*fp;

    printf("请输入书名:");
    scanf("%s",b.name);

    printf("请输入作者:");
    scanf("%s",b.author);

    printf("请输入数量:");
    scanf("%d",&b.quantity);

    fp=fopen("books.txt","a");
    if(fp==NULL){
        printf("文件打开失败!\n");
        return;
    }

    fprintf(fp,"%s|%s|%d\n",b.name,b.author,b.quantity);
    fclose(fp);

    printf("添加成功!\n");
}

//实现查看图书功能
void showBooks(){
    FILE*fp;
    char name[50],author[50];
    int quantity;

    fp=fopen("books.txt","r");
    if(fp==NULL){
        printf("暂无图书信息!\n");
        return;
    }

    printf("\n当前图书列表:\n");
    printf("----------------------------\n");
    printf("书名\t作者\t数量\n");

    while(fscanf(fp,"%[^|]|%[^|]|%d\n",name,author,&quantity)==3){
        printf("%s\t%s\t%d\n",name,author,quantity);
    }

    printf("----------------------------\n");

    fclose(fp);
}
