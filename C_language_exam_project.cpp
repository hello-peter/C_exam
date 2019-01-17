//图书管理系统

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define bookfile "book.dat"  //宏定义书的文件名
#define passfile "daminpass.dat" //宏定义管理员密码文件名字
#define usersfile "usersfile.dat"  //宏定义用户账户名称储存文件
#define n 20 //宏定义密码长度
#define m 1000 //宏定义书籍的长度
typedef struct {
	char name[n]; //图书的名字
	int a; //记录这本书有没有被借 0表示被接 1表示没有被借
}book;
typedef struct {
	char usersname[n];  //账户名字
	char password[n];  //密码
	char books[n];  //记录借记的图书
}users;
char adminchoice = '0';
char choice = '0';
char foundchoice = '0';
char userschoice = '0';
char usersmenuchoice = '0';
void showmenu(void); //显示主菜单函数
void usersmenu(void);  //用户界面函数
void adminmenu(void); //管理员操作菜单
void admin(void);
int adminlogin(void); //管理员登陆函数
void changepassword(void);  //更改密码
void addbook(void); //添加图书操作
int foundindex(book a[m]); //查找图书的末端
void delectbook(void); //删除书籍函数
void changebook(void); //修改图书函数
void showbook(void);  //显示所有图书信息的函数
void userslogin(void);  //用户登陆函数
void usersregister(void);  //注册用户函数
void usersmenu(int f);  //用户登陆后的菜单
void foundbook(int f);  //查找函数
void borrowbook(int a);  //借书函数
void backbook(int a);  //还书函数
void showbooks(int f);  //用户查找函数
void changeuserspassword(int f);  //修改用户密码函数
void usersfirstmenu(void);
int main()
{
	showmenu();
	switch (choice) {
	case '1':
		usersfirstmenu();  //调用用户登录函数
		break;
	default:
		adminlogin();
		break;
	}

	return 0;
}

//主菜单函数
void showmenu(void)
{
	printf("欢迎来到图书馆管理系统\n");
	printf("--------------------\n");
	printf("(1)用户登录\t(2)管理员登陆");
	printf("--------------------\n");
	printf("请输入您想要选择的操作:\n");
loop:choice = getche();
	printf("\n");
	if ((choice - '0' > 2) || (choice - '0' < 0))
	{
		printf("输入有误!   请从新输入!\n");
		goto loop;
	}
}

//用户界面函数
void usersmenu(void) {
	printf("--------------------\n");
	printf("(1)修改密码\t(2)查找图书\t(3)显示图书信息\y(4)借还图书\t(5)退出系统");
	printf("--------------------\n");
	printf("请输入您的选择");
loop:userschoice = getche();
	if ((userschoice - '0') > 5 || (userschoice - '0') < 1) {
		printf("请输入正确选项");
	}
}
//管理员菜单显示函数
void adminmenu(void)
{
	printf("--------------------\n");
	printf("(1)添加图书\t(2)删除图书\t(3)修改图书信息\t(4)修改管理员密码\t(5)查看所有的图书\t(6)退出系统\n");
	printf("--------------------\n");
	printf("请输入您想要的操作:\n");
	loop:adminchoice = getche();
	if ((adminchoice - '0' > 6) || (adminchoice - '0' < 1))
	{
		printf("请输入正确的操作代码!\n");
		goto loop;
	}
}
//管理员操作函数
void admin(void)
{
	while (1) {
		adminmenu();
		switch (adminchoice) {
		case '1':
			addbook(); //调用添加图书函数
			break;
		case '2':
			delectbook(); //调用更改密码函数
			break;
		case '3':
			changebook(); //调用修改图书函数
			break;
		case '4':
			changepassword(); //调用修改管理员密码函数
			break;
		case '5':
			showbook();  //调用遍历图书函数
		default:
			exit(0);  //退出函数
			break;
		}
	}
}

//管理员登陆函数
int adminlogin(void)
{
	int c = 3;
	char a[n], b[n];
	printf("账户:admin\n");
	FILE *fp;
	if ((fp = fopen(passfile, "r")) == NULL) {
		printf("cannot open this file!!!\n");
		exit(0);
	}
	fgets(b, n, fp);
	printf("请输入密码:(10位以内)\n");
	printf("注:初始密码为123456789\n");
	loop:scanf("%s", a);
	while (c >= 0) {
	if (strcmp(a, b) == 0)
	{
		printf("密码正确!!!\n");
		printf("欢迎您，亲爱的管理员\n");
		system("pause");
	}
	else
	{
		printf("密码有误 请输入您的密码（您还有%d次机会）",c);
		c--;
		goto loop;
	}
	if (c < 0)
	{
		printf("您输入密码错误大于3次 系统将退出\n");
		exit(0);
	}
	admin();
}
}

//添加图书函数
void addbook(void)
{
	int b=0;
	char c,e;
	book a[m]; //定义书籍的数组
	FILE *fp;
	if ((fp = fopen(bookfile,"r")) == NULL) {
		printf("cannot open this file!!!\n");
	}
	for (int i = 0; i < m; i++)
		fread(&a[i],sizeof(book),1,fp);
	fclose(fp);
	b = foundindex(a);
		if (b == m - 1) {
			printf("没有位置添加图书了，系统将退出\n");
			exit(0);
		}
			loopy:printf("请输入您想添加书籍的名字:\n");
			scanf("%s", a[b].name);
			a[b].a = 1;  //0表示被借 1表示没有被借
			b++;
			printf("是否需要继续添加函数? 若想继续添加则可以按y\n");
			printf("\n");
			c = getche();
			if ((c =='y') || (c == 'Y'))
				goto loopy;
			if ((fp == fopen(bookfile, "w")) == NULL) {
				printf("录入文件不成功系统将退出\n");
				exit(0);
			}
			for (int i = 0; i < m; i++) {
				fwrite(&a[i], sizeof(book), 1, fp);
			}
			fclose(fp);
		printf("接下来的操作是?\n");
		printf("--------------------\n");
		printf("(1)返回上一级\t(2)退出系统\n");
		printf("--------------------\n");
		loop:e = getche();
		if (e<'1' || e>'2') {
			printf("请从新输入:\n");
			goto loop;
		}
		switch (e)
		{
		case '1':
			admin();
			break;
		default:
			exit(0);
			break;
		}
}

//更改管理员密码函数
void changepassword(void)
{
	char a[n],e;
	printf("请输入您的新密码:\n");
	scanf("%s",a);
	FILE *fp;
	fp = fopen(passfile,"w");
	if (!fputs(a,fp))
		printf("修改成功\n");
	else
		printf("修改失败\n");
	fclose(fp);
	printf("接下来的操作是?\n");
	printf("--------------------\n");
	printf("(1)返回上一级\t(2)退出系统\n");
	printf("--------------------\n");
loop:e = getche();
	if (e<'1' || e>'2') {
		printf("请从新输入:\n");
		goto loop;
	}
	switch (e)
	{
	case '1':
		admin();
		break;
	default:
		exit(0);
		break;
	}
}
int foundindex(book a[m]) {
	int b=0;
	for (int i = 0; i < m; i++) {
		if (strcmp(a[i].name,"noname")==0) {
			break;
		}
		b++;
	}
	return b;
}

//删除图书函数
void delectbook(void) {
	FILE *fp;
	char c[n],e;
	int b=0,d=0,f=0; //找到最后的位置
	if ((fp = fopen(bookfile, "r")) == NULL) {
		printf("cannot open this file\n");
		exit(0);
	}
	book a[m];
	for (int i = 0; i < m; i++) {
		fread(&a[i],sizeof(book),1,fp);
	}
	fclose(fp);
	b=foundindex(a);
	printf("请输入您想要删除的图书:\n");
	scanf("%s",c);
	for (int i = 0; i < b; i++) {
		if (strcmp(c, a[i].name) == 0) {
			d = i;
			f = 1;
			break;
		}
	}
	if (f = 0) {
		printf("未找到你所要删除的图书\n");
	}
	else {
		for (int i = d; i<=b; i++) {
			strcpy(a[i].name, a[i + 1].name);
			a[i].a = a[i + 1].a;
		}
		if ((fp = fopen(bookfile, "w")) == NULL) {
			printf("未能成功录入文件!\n");
			exit(0);
		}
		for (int i = 0; i < m; i++) {
			fwrite(&a[i],sizeof(book),1,fp);
		}
		fclose(fp);
	}
	printf("接下来的操作是?\n");
	printf("--------------------\n");
	printf("(1)返回上一级\t(2)退出系统\n");
	printf("--------------------\n");
loop:e = getche();
	if (e<'1' || e>'2') {
		printf("请从新输入:\n");
		goto loop;
	}
	switch (e)
	{
	case '1':
		admin();
		break;
	default:
		exit(0);
		break;
	}
}

//修改图书函数
void changebook(void) {
	FILE *fp;
	int b=0,e=0,f=0;  //记录最后的位置
	book a[m];
	char c[n],k;
	if ((fp = fopen(bookfile, "r")) == NULL)
	{
		printf("cannot open this file\n");
		exit(0);
	}
	for (int i = 0; i < m; i++) {
		fread(&a[i],sizeof(book),1,fp);
	}
	fclose(fp);
	b = foundindex(a);  //找到最后的位置
	printf("请输入您现在想要修改的书名名字:\n");
	scanf("%s",c);
	for (int i = 0; i < b; i++) {
		if (strcmp(c, a[i].name) == 0) {
			e = 1;
			f = i;
		}
	}
	if (e == 0) {
		printf("没有这本书!\n");
	}
	else {
		printf("请输入您想改变的书名:\n");
		scanf("%s",c);
		strcpy(a[f].name,c);
	}
	if ((fp = fopen(bookfile, "w")) == NULL) {
		printf("cannot open this file\n");
		exit(0);
	}
	for (int i = 0; i < m; i++) {
		fwrite(&a[i],sizeof(book),1,fp);
	}
	fclose(fp);
	printf("接下来的操作是?\n");
	printf("--------------------\n");
	printf("(1)返回上一级\t(2)退出系统\n");
	printf("--------------------\n");
loop:k = getche();
	if (k<'1' || k>'2') {
		printf("请从新输入:\n");
		goto loop;
	}
	switch (k)
	{
	case '1':
		admin();
		break;
	default:
		exit(0);
		break;
	}
}

//显示所有信息的函数
void showbook(void) {
	FILE *fp;
	book a[m];
	char e;
	int b;  //记录最后一个位置的整数
	if ((fp = fopen(bookfile, "r")) == NULL)
	{
		printf("cannot open this file");
	}
	for (int i = 0; i < m; i++) {
		fread(&a[i],sizeof(book),1,fp);
	}
	b = foundindex(a);
	printf("图书名\t\t\t借记状态\n");
	for (int i = 0; i < b; i++) {
		if (a[i].a == 1)
		{
			printf("%s\t\t没被借\n",a[i].name);
		}
		else {
			printf("%s\t被借\n",a[i].name);
		}
	}
	printf("接下来的操作是?\n");
	printf("--------------------\n");
	printf("(1)返回上一级\t(2)退出系统\n");
	printf("--------------------\n");
loop:e = getche();
	if (e<'1' || e>'2') {
		printf("请从新输入:\n");
		goto loop;
	}
	switch (e)
	{
	case '1':
		admin();
		break;
	default:
		exit(0);
		break;
	}
}

//用户界面选项

void usersfirstmenu(void) {
	printf("--------------------\n");
	printf("(1)登陆账户\t(2)注册用户");
	printf("--------------------\n");
	char f;
	printf("请输入您的选项:\n");
	loop:f = getche();
	if (((f - '0') > 2) || ((f - '0') < 0)) {
		printf("请选择正确选项\n");
		goto loop;
	}
	switch (f) {
	case '1':
		userslogin();  //用户登录函数
		break;
	default:
		usersregister();  //注册函数
	}
}

//用户登陆函数

void userslogin(void) {
	FILE *fp;
	int c = 3,e=0,f=0;
	users a[m];
	if ((fp = fopen(usersfile, "r")) == NULL) {
		printf("cannot open this file\n");
		exit(0);
	}
	for (int i = 0; i < m; i++) {
		fread(&a[i],sizeof(users),1,fp);
	}
	fclose(fp);
	users d;
	printf("请输入账号和密码:\n");
	printf("账户名:\n");
	scanf("%s",d.usersname);
	printf("密码:\n");
	scanf("%s",d.password);
	for (int i = 0; i < m; i++) {
		if (strcmp(a[i].usersname, d.usersname) == 0) {
			f = i;
			while (c > 0) {
				if (strcmp(a[i].password, d.password) == 0) {
					e = 1;
					break;
				}
				else
				{
					printf("请从新输入密码:\n");
					c--;
					scanf("%s", d.password);
				}
			}
			if (c < 0)
			{
				printf("您输入三次密码都不正确 系统将退出\n");
				exit(0);
				system("pause");
			}
		}
	}
		if (e == 0) {
			printf("没有此用户\n");
			exit(0);
			system("pause");
		}
		else
		{
			printf("登陆成功！！！\n");
			if (strcmp(a[f].books, "noname")==0) {
				printf("您没有借记图书!\n");
			}
			else {
				printf("您借阅的图书是:%s",a[f].books);
			}
			usersmenu(f);
		}

}

//用户登陆后的菜单

void usersmenu(int f)
{
	printf("-------------------\n");
	printf("(1)查找图书 \t(2)借图书\t(3)还书\t(4)显示所有图书\t(5)修改密码(6)退出程序\n");
	printf("-------------------\n");
loop:usersmenuchoice = getche();
	printf("\n");
	if (((usersmenuchoice - '0') > 6) || ((usersmenuchoice- '0') < 0)) {
		printf("请选择正确选项\n");
		goto loop;
	}
	switch (usersmenuchoice) {
	case '1':
		foundbook(f);  //调用查找图书函数
		break;
	case '2':
		borrowbook(f);  //调用借书函数
		break;
	case '3':
		backbook(f);  //调用还书函数
		break;
	case '4':
		showbooks(f);  //调用显示所有图书函数
		break;
	case '5':
		changeuserspassword(f);  //调用修改用户密码函数
		break;
	default:
		exit(0);
		break;
	}
}

//查找函数
void foundbook(int f)
{
	FILE *fp;
	book a[m];
	int d,e=0,h;
	if ((fp=fopen(bookfile, "r")) == NULL) {
		printf("cannot open this file\n");
		exit(0);
	}
	for (int i = 0; i < m; i++) {
		fread(&a[i],sizeof(book),1,fp);
	}
	fclose(fp);
	char b[n],g;
	printf("请输入您想要查询的书名:\n");
	scanf("%s",b);
	d = foundindex(a);
	for (int i = 0; i < d; i++) {
		if (strcmp(a[i].name, b) == 0) {
			e = 1;
			h = i;
			break;
		}
	}
	if (e == 0) {
		printf("没有此书!!!\n");
	}
	else 
	{
		printf("查询到此书!\n结果为:\n");
		printf("--------------------\n");
		printf("书名\t借阅状态\n");
		if (a[h].a == 0) {
			printf("%s\t被借阅\n",a[h].name);
		}
		else {
			printf("%s\t没有被借阅\n",a[h].name);
		}
		printf("--------------------\n");
		
	}
	printf("接下来的操作是?\n");
	printf("--------------------\n");
	printf("(1)返回上一级\t(2)退出系统\n");
	printf("--------------------\n");
loop:g = getche();
	if (g<'1' || g>'2') {
		printf("请从新输入:\n");
		goto loop;
	}
	switch (g)
	{
	case '1':
		usersmenu(f);
		break;
	default:
		exit(0);
		break;
	}
	}

//借记图书函数
void borrowbook(int a) {
	FILE *fp,*p;
	book b[m];
	users e[m];
	char c[n],g;
	int d,f=0;  //找到图书的最后一个位置
	d = foundindex(b);
	if ((fp = fopen(bookfile, "r")) == NULL) {
		printf("cannot open this file\n");
		exit(0);
	}
	for (int i=0;i<m;i++) {
		fread(&b[i],sizeof(book),1,fp);
	}
	fclose(fp);
	if ((p = fopen(usersfile, "r")) == NULL) {
		printf("cannot open this file\n");
		exit(0);
		system("pause");
	}
	for (int i = 0; i < m; i++) {
		fread(&e[i],sizeof(users),1,p);
	}
	fclose(p);
	if (strcmp(e[a].books, "noname") != 0) {
		printf("您已经有借了图书!!!请先归还图书!\n");
	}
	else
	{
		printf("请您输入您想要借的书\n");
		scanf("%s",c);
	}
	
	for (int i = 0; i < d; i++) {
		if (strcmp(c, b[i].name) == 0) {
			if (b[i].a == 1) {
				strcpy(e[a].books,b[i].name);
				b[i].a = 0;  //1表示没有被借 0表示被借
			f = 1;
			break;
		     }
			else {
				printf("您找的图书已经被借\n");
			}
		}
	}
	if (f == 1) {
		printf("借书成功！！！\n");
	}
	else {
		printf("未能找到您的书 借书未成功!!!\n");
	}
	if ((fp = fopen(bookfile, "w")) == NULL) {
		exit(0);
		system("pause");
	}
	for (int i = 0; i < m; i++) {
		fwrite(&b[i],sizeof(book),1,fp);
	}
	fclose(fp);
	if ((p = fopen(usersfile, "w")) == NULL) {
		exit(0);
		system("pause");
	}
	for (int i = 0; i < m; i++) {
		fwrite(&e[i],sizeof(users),1,p);
	}
	fclose(p);
	printf("接下来的操作是?\n");
	printf("--------------------\n");
	printf("(1)返回上一级\t(2)退出系统\n");
	printf("--------------------\n");
loop:g = getche();
	if (g<'1' || g>'2') {
		printf("请从新输入:\n");
		goto loop;
	}
	switch (g)
	{
	case '1':
		usersmenu(a);
		break;
	default:
		exit(0);
		break;
	}
}

//还书函数
void backbook(int a) {
	FILE *fp,*p;
	book b[m];
	users f[m];
	char c, g;
	int d;  //找到图书的最后一个位置
	d = foundindex(b);
	if ((p = fopen(usersfile, "r")) == NULL) {
		printf("cannot open this file\n");
		exit(0);
	}
	for (int i = 0; i < m; i++) {
		fread(&f[i],sizeof(users),1,p);
	}
	fclose(p);
	if ((fp = fopen(bookfile, "r")) == NULL) {
		printf("cannot open this file\n");
		exit(0);
	}
	for (int i = 0; i<m; i++) {
		fread(&b[i], sizeof(book), 1, fp);
	}
	fclose(fp);
	if (strcmp(f[a].books, "noname") == 0) {
		printf("您没有借阅图书!!!\n\n");
	}
	else
	{
		printf("确定要归还吗？\n（1）是\t(2)否");
		c = getche();
		printf("\n");
	}
	if (c == '1') {
		for (int i = 0; i < d; i++) {
			if (strcmp(b[i].name, f[a].books) == 0) {
				b[i].a = 1;
				strcpy(f[a].books,"noname");
				printf("还书成功!!!\n");;
				break;
			}
		}
	}
	if ((fp == fopen(bookfile, "w")) == NULL) {
		exit(0);
		system("pause");
	}
	for (int i = 0; i < m; i++) {
		fwrite(&b[i], sizeof(book), 1, fp);
	}
	fclose(fp);
	if ((p = fopen(usersfile, "w")) == NULL) {
		exit(0);
		system("pause");
	}
	for (int i = 0; i < m; i++) {
		fwrite(&f[i],sizeof(users),1,p);
	}
	fclose(p);
	printf("接下来的操作是?\n");
	printf("--------------------\n");
	printf("(1)返回上一级\t(2)退出系统\n");
	printf("--------------------\n");
loop:g = getche();
	if (g<'1' || g>'2') {
		printf("请从新输入:\n");
		goto loop;
	}
	switch (g)
	{
	case '1':
		usersmenu(a);
		break;
	default:
		exit(0);
		break;
	}
}

//用户显示所有图书函数
void showbooks(int f) {
	FILE *fp;
	book a[m];
	char e;
	int b;  //记录最后一个位置的整数
	if ((fp = fopen(bookfile, "r")) == NULL)
	{
		printf("cannot open this file");
	}
	for (int i = 0; i < m; i++) {
		fread(&a[i], sizeof(book), 1, fp);
	}
	b = foundindex(a);
	printf("图书名\t\t\t借记状态\n");
	for (int i = 0; i < b; i++) {
		if (a[i].a == 1)
		{
			printf("%s\t\t没被借\n", a[i].name);
		}
		else {
			printf("%s\t被借\n", a[i].name);
		}
	}
	printf("接下来的操作是?\n");
	printf("--------------------\n");
	printf("(1)返回上一级\t(2)退出系统\n");
	printf("--------------------\n");
loop:e = getche();
	if (e<'1' || e>'2') {
		printf("请从新输入:\n");
		goto loop;
	}
	switch (e)
	{
	case '1':
		usersmenu(f);
		break;
	default:
		exit(0);
		break;
	}
}

//修改用户密码函数
void changeuserspassword(int f) {
	FILE *fp;
	users a[m];
	char b[n],e;
	if ((fp = fopen(usersfile, "r")) == NULL) {
		printf("cannot open this file\n");
		exit(0);
		system("pause");
	}
	for (int i = 0; i < m; i++) {
		fread(&a[i],sizeof(users),1,fp);
	}
	fclose(fp);
	printf("请输入您想要修改的密码:\n");
	scanf("%s",b);
	strcpy(a[f].password,b);
	printf("修改密码成功\n");
	if ((fp = fopen(usersfile, "w"))==NULL) {
		exit(0);
		system("pause");
	}
	for (int i = 0; i < m; i++) {
		fwrite(&a[i],sizeof(users),1,fp);
	}
	fclose(fp);
	printf("接下来的操作是?\n");
	printf("--------------------\n");
	printf("(1)返回上一级\t(2)退出系统\n");
	printf("--------------------\n");
loop:e = getche();
	if (e<'1' || e>'2') {
		printf("请从新输入:\n");
		goto loop;
	}
	switch (e)
	{
	case '1':
		usersmenu(f);
		break;
	default:
		exit(0);
		break;
	}
}

//用户注册函数
void usersregister(void) {
	FILE *fp;
	users a[m];
	int f=0;
	char p;
	if ((fp = fopen(usersfile, "r")) == NULL)
	{
		printf("cannot open this file\n");
		exit(0);
		system("pause");
	}
	for (int i = 0; i < m; i++) {
		fread(&a[i],sizeof(users),1,fp);
	}
	fclose(fp);
	for (int i = 0; i < m; i++) {
		if (strcmp(a[i].usersname, "noname")==0) {
			f = i;
			break;
		}
	}
	printf("请输入您的用户名字:\n");
	loop:scanf("%s",a[f].usersname);
	for (int i = 0; i < f; i++) {
		if (strcmp(a[i].usersname, a[f].usersname) == 0) {
			printf("此名字已经被占用 请重新输入:\n");
			goto loop;
		}
	}
	printf("请输入您的密码:\n");
	scanf("%s",a[f].password);
	if ((fp = fopen(usersfile, "w")) == NULL) {
		exit(0);
		system("pause");
	}
	for (int i = 0; i < m; i++) {
		fwrite(&a[i],sizeof(users),1,fp);
	}
	fclose(fp);
	printf("您接下来的操作是?\n");
	printf("--------------------\n");
	printf("(1)登陆\t(2)退出程序\n");
	printf("--------------------\n");
loopy:p = getche();
	if ((p < '1') || (p > '2')) {
		printf("输入有误请从新输入\n");
		goto loopy;
	}
	switch (p) {
	case '1':
		usersfirstmenu();
		break;
	default:
		exit(0);
		break;
	}
} 










//创建用户文件函数
/*int main()
{
	FILE *fp;
	users a[m], c[m];
	remove(usersfile);
	if ((fp = fopen(usersfile, "w")) == NULL) {
		printf("cannot open this file\n");
		exit(0);
	}
	for (int i = 0; i < m; i++) {
		strcpy(a[i].usersname,"noname");
		strcpy(a[i].password,"noname");
		strcpy(a[i].books,"noname");
	}
	for(int i=0;i<m;i++)
	fwrite(&a[i],sizeof(users),1,fp);
	fclose(fp);
	if ((fp = fopen(usersfile, "r")) == NULL)
	{
		exit(0);
	}
	for (int i = 0; i < m; i++) {
		fread(&c[i],sizeof(users),1,fp);
	}
	for (int i = 0; i < m; i++) {
		printf("内容是:%s和%s\n",c[i].usersname,c[i].password);
	}
	fclose(fp);
	system("pause");
	return 0;

}*/

//创建图书文件
/*int main()
{
	FILE *fp;
	book a[m];
	if ((fp = fopen(bookfile, "w")) == NULL) {
		printf("cannot create this file\n");
		exit(0);
		system("pause");
	}
	for (int i = 0; i < m; i++) {
		strcpy(a[i].name,"noname");
		a[i].a = 1;
		fwrite(&a[i],sizeof(book),1,fp);
	}
	fclose(fp);
}*/
//创建管理员密码文件
/*int main()
{
	FILE *fp;
	char a[n];
	if ((fp = fopen(passfile, "w")) == NULL) {
		printf("cannot create this file\n");
		exit(0);
		system("pause");
	}
	printf("输入初始密码:\n");
	scanf("%s",a);
	fputs(a,fp);
	fclose(fp);
	return  0;
}*/

