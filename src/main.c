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

//当前登录用户
char currentUser[20]="";
int isAdmin=0;

/****************函数声明*****************/
//注册函数
void registerUser();
//登录函数//
int loginUser();
//添加图书
void addBook();
//查看图书
void showBooks();
//删除图书
void deleteBook();
//借阅图书
void borrowBook();
//归还图书
void returnBook();
//主菜单
int main() {
    int choice;
    int loggedIn=0;
    while (1) {
        printf("\n========================\n");
        printf("   图书管理系统\n");
        printf("========================\n");
        printf("1. 注册\n");
        printf("2. 登录\n");
	    printf("3.图书管理(需要登录！)\n");
        printf("0. 退出\n");
        printf("请输入：");
        scanf("%d", &choice);
        getchar();

        switch(choice){
            case 1:
                registerUser();
                break;
            case 2:
                if(loginUser()){
        		printf("登录成功！欢迎进入图书管理系统！\n");
			loggedIn=1;
    		}else{
        		printf("用户名或密码错误！\n");
    		}
                break;
	    case 3:{
		if(!loggedIn){
		    printf("请先登录!\n");
		    break;
		}

		int sub;
		if(isAdmin){
		    printf("\n1.添加图书\n2.查看图书\n3.删除图书\n4.借阅图书\n5.归还图书\n请输入:");
		    scanf("%d",&sub);
		    getchar();
		    if(sub==1)addBook();
		    else if(sub==2)showBooks();
		    else if(sub==3)deleteBook();
		    else if(sub==4)borrowBook();
		    else if(sub==5)returnBook();
		    else printf("输入错误!\n");
		}else{
		    printf("\n1.查看图书\n2.借阅图书\n3.归还图书\n请输入:");
		    scanf("%d",&sub);
		    getchar();
		    if(sub==1)showBooks();
		    else if(sub==2)borrowBook();
		    else if(sub==3)returnBook();
		    else printf("输入错误!\n");
		}

		break;
                }
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

	 /* 检查是否为管理员 */
	 if(!found){
		 fp=fopen("admin.txt","r");
		 if(fp!=NULL){
			 while(fscanf(fp,"%s %s",fileUser.username,fileUser.password)!=EOF){
				 if(strcmp(inputUser.username,fileUser.username)==0&&
				    strcmp(inputUser.password,fileUser.password)==0){
					 found=1;
					 isAdmin=1;
					 break;
				 }
			 }
			 fclose(fp);
		 }
	 }

	 if(found){
		printf("登录成功！\n");
		strcpy(currentUser,inputUser.username);
		if(isAdmin)printf("当前身份:管理员\n");
		else printf("当前身份:普通用户\n");
		return 1;   // ✅ 成功
	 }else{
		printf("用户名或密码错误！\n");
		return 0;   // ❌ 失败
	 }

}

//实现添加图书功能
void addBook(){
    struct book b,exist;
    FILE*fp,*temp;
    int found=0;

    printf("请输入书名:");
    scanf("%s",b.name);
    printf("请输入作者:");
    scanf("%s",b.author);
    printf("请输入数量:");
    scanf("%d",&b.quantity);

    fp=fopen("books.txt","r");
    temp=fopen("temp.txt","w");

    if(fp!=NULL){
        while(fscanf(fp,"%[^|]|%[^|]|%d\n",
            exist.name,exist.author,&exist.quantity)==3){
            if(strcmp(exist.name,b.name)==0&&
               strcmp(exist.author,b.author)==0){
                exist.quantity+=b.quantity;
                found=1;
            }
            fprintf(temp,"%s|%s|%d\n",
                exist.name,exist.author,exist.quantity);
        }
        fclose(fp);
    }

    if(!found){
        fprintf(temp,"%s|%s|%d\n",b.name,b.author,b.quantity);
    }

    fclose(temp);
    remove("books.txt");
    rename("temp.txt","books.txt");

    if(found)printf("图书已存在,数量已合并!当前库存:%d\n",exist.quantity);
    else printf("添加成功!\n");
}

//实现查看图书功能
void showBooks(){
    FILE*fp;
    struct book books[100];
    int count=0,i,j;
    struct book tmp;

    fp=fopen("books.txt","r");
    if(fp==NULL){
        printf("暂无图书信息!\n");
        return;
    }

    while(fscanf(fp,"%[^|]|%[^|]|%d\n",
        books[count].name,books[count].author,&books[count].quantity)==3){
        count++;
    }
    fclose(fp);

    if(count==0){
        printf("暂无图书信息!\n");
        return;
    }

    /* 按数量降序排序(冒泡) */
    for(i=0;i<count-1;i++){
        for(j=0;j<count-1-i;j++){
            if(books[j].quantity<books[j+1].quantity){
                tmp=books[j];
                books[j]=books[j+1];
                books[j+1]=tmp;
            }
        }
    }

    printf("\n当前图书列表(按数量排序):\n");
    printf("----------------------------\n");
    printf("书名\t作者\t数量\n");

    for(i=0;i<count;i++){
        printf("%s\t%s\t%d\n",
            books[i].name,books[i].author,books[i].quantity);
    }

    printf("----------------------------\n");
}

//实现图书删除功能
void deleteBook(){
    FILE*fp,*temp;
    char name[50],author[50];
    char delname[50];
    int quantity;
    int found=0;

    printf("请输入要删除的书名:");
    scanf("%s",delname);

    fp=fopen("books.txt","r");
    if(fp==NULL){
        printf("暂无图书信息!\n");
        return;
    }

    temp=fopen("temp.txt","w");

    while(fscanf(fp,"%[^|]|%[^|]|%d\n",name,author,&quantity)==3){
        if(strcmp(name,delname)==0){
            found=1;
            continue;
        }
        fprintf(temp,"%s|%s|%d\n",name,author,quantity);
    }

    fclose(fp);
    fclose(temp);

    remove("books.txt");
    rename("temp.txt","books.txt");

    if(found)printf("删除成功!\n");
    else printf("未找到该图书!\n");
}

//实现借阅图书功能
void borrowBook(){
    FILE*bfp,*temp;
    char bname[50],author[50],borrowName[50];
    int quantity,found=0;

    if(currentUser[0]=='\0'){
        printf("请先登录!\n");
        return;
    }

    printf("请输入要借阅的书名:");
    scanf("%s",borrowName);

    /* 先检查图书是否存在 + 库存 */
    bfp=fopen("books.txt","r");
    if(bfp==NULL){
        printf("暂无图书信息!\n");
        return;
    }

    temp=fopen("temp.txt","w");

    while(fscanf(bfp,"%[^|]|%[^|]|%d\n",bname,author,&quantity)==3){
        if(strcmp(bname,borrowName)==0){
            found=1;
            if(quantity<=0){
                printf("该书库存不足,无法借阅!\n");
                fclose(bfp);
                fclose(temp);
                remove("temp.txt");
                return;
            }
            quantity--;
        }
        fprintf(temp,"%s|%s|%d\n",bname,author,quantity);
    }

    fclose(bfp);
    fclose(temp);

    if(!found){
        printf("未找到该图书!\n");
        remove("temp.txt");
        return;
    }

    /* 再检查是否重复借阅 */
    bfp=fopen("borrows.txt","r");
    if(bfp!=NULL){
        char bu[20],bn[50];
        while(fscanf(bfp,"%s %[^\n]",bu,bn)!=EOF){
            if(strcmp(bu,currentUser)==0&&strcmp(bn,borrowName)==0){
                printf("您已经借过这本书了!\n");
                fclose(bfp);
                remove("temp.txt");
                return;
            }
        }
        fclose(bfp);
    }

    /* 写入借阅记录 */
    bfp=fopen("borrows.txt","a");
    if(bfp==NULL){
        printf("借阅记录文件打开失败!\n");
        remove("temp.txt");
        return;
    }

    fprintf(bfp,"%s %s\n",currentUser,borrowName);
    fclose(bfp);

    remove("books.txt");
    rename("temp.txt","books.txt");

    printf("借阅成功!\n");
}

//实现归还图书功能
void returnBook(){
    FILE*bfp,*tempB,*bookFp,*tempBook;
    char returnName[50],bu[20],bn[50],bname[50],author[50];
    int quantity,found=0;

    if(currentUser[0]=='\0'){
        printf("请先登录!\n");
        return;
    }

    printf("请输入要归还的书名:");
    scanf("%s",returnName);

    /* 先确认图书是否存在 */
    bookFp=fopen("books.txt","r");
    if(bookFp==NULL){
        printf("暂无图书信息!\n");
        return;
    }

    while(fscanf(bookFp,"%[^|]|%[^|]|%d\n",bname,author,&quantity)==3){
        if(strcmp(bname,returnName)==0){found=1;break;}
    }
    fclose(bookFp);

    if(!found){
        printf("未找到该图书!\n");
        return;
    }

    /* 再确认是否真的借过 */
    found=0;
    bfp=fopen("borrows.txt","r");
    if(bfp==NULL){
        printf("暂无借阅记录!\n");
        return;
    }

    tempB=fopen("temp_borrow.txt","w");

    while(fscanf(bfp,"%s %[^\n]",bu,bn)!=EOF){
        if(strcmp(bu,currentUser)==0&&strcmp(bn,returnName)==0){found=1;continue;}
        fprintf(tempB,"%s %s\n",bu,bn);
    }

    fclose(bfp);
    fclose(tempB);

    if(!found){
        printf("您未借过该书,无法归还!\n");
        remove("temp_borrow.txt");
        return;
    }

    remove("borrows.txt");
    rename("temp_borrow.txt","borrows.txt");

    /* 恢复图书库存 */
    bookFp=fopen("books.txt","r");
    if(bookFp==NULL){
        printf("图书文件打开失败!\n");
        return;
    }

    tempBook=fopen("temp.txt","w");

    while(fscanf(bookFp,"%[^|]|%[^|]|%d\n",bname,author,&quantity)==3){
        if(strcmp(bname,returnName)==0)quantity++;
        fprintf(tempBook,"%s|%s|%d\n",bname,author,quantity);
    }

    fclose(bookFp);
    fclose(tempBook);

    remove("books.txt");
    rename("temp.txt","books.txt");

    printf("归还成功!\n");
}
