//ͼ�����ϵͳ

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define bookfile "book.dat"  //�궨������ļ���
#define passfile "daminpass.dat" //�궨�����Ա�����ļ�����
#define usersfile "usersfile.dat"  //�궨���û��˻����ƴ����ļ�
#define n 20 //�궨�����볤��
#define m 1000 //�궨���鼮�ĳ���
typedef struct {
	char name[n]; //ͼ�������
	int a; //��¼�Ȿ����û�б��� 0��ʾ���� 1��ʾû�б���
}book;
typedef struct {
	char usersname[n];  //�˻�����
	char password[n];  //����
	char books[n];  //��¼��ǵ�ͼ��
}users;
char adminchoice = '0';
char choice = '0';
char foundchoice = '0';
char userschoice = '0';
char usersmenuchoice = '0';
void showmenu(void); //��ʾ���˵�����
void usersmenu(void);  //�û����溯��
void adminmenu(void); //����Ա�����˵�
void admin(void);
int adminlogin(void); //����Ա��½����
void changepassword(void);  //��������
void addbook(void); //���ͼ�����
int foundindex(book a[m]); //����ͼ���ĩ��
void delectbook(void); //ɾ���鼮����
void changebook(void); //�޸�ͼ�麯��
void showbook(void);  //��ʾ����ͼ����Ϣ�ĺ���
void userslogin(void);  //�û���½����
void usersregister(void);  //ע���û�����
void usersmenu(int f);  //�û���½��Ĳ˵�
void foundbook(int f);  //���Һ���
void borrowbook(int a);  //���麯��
void backbook(int a);  //���麯��
void showbooks(int f);  //�û����Һ���
void changeuserspassword(int f);  //�޸��û����뺯��
void usersfirstmenu(void);
int main()
{
	showmenu();
	switch (choice) {
	case '1':
		usersfirstmenu();  //�����û���¼����
		break;
	default:
		adminlogin();
		break;
	}

	return 0;
}

//���˵�����
void showmenu(void)
{
	printf("��ӭ����ͼ��ݹ���ϵͳ\n");
	printf("--------------------\n");
	printf("(1)�û���¼\t(2)����Ա��½");
	printf("--------------------\n");
	printf("����������Ҫѡ��Ĳ���:\n");
loop:choice = getche();
	printf("\n");
	if ((choice - '0' > 2) || (choice - '0' < 0))
	{
		printf("��������!   ���������!\n");
		goto loop;
	}
}

//�û����溯��
void usersmenu(void) {
	printf("--------------------\n");
	printf("(1)�޸�����\t(2)����ͼ��\t(3)��ʾͼ����Ϣ\y(4)�軹ͼ��\t(5)�˳�ϵͳ");
	printf("--------------------\n");
	printf("����������ѡ��");
loop:userschoice = getche();
	if ((userschoice - '0') > 5 || (userschoice - '0') < 1) {
		printf("��������ȷѡ��");
	}
}
//����Ա�˵���ʾ����
void adminmenu(void)
{
	printf("--------------------\n");
	printf("(1)���ͼ��\t(2)ɾ��ͼ��\t(3)�޸�ͼ����Ϣ\t(4)�޸Ĺ���Ա����\t(5)�鿴���е�ͼ��\t(6)�˳�ϵͳ\n");
	printf("--------------------\n");
	printf("����������Ҫ�Ĳ���:\n");
	loop:adminchoice = getche();
	if ((adminchoice - '0' > 6) || (adminchoice - '0' < 1))
	{
		printf("��������ȷ�Ĳ�������!\n");
		goto loop;
	}
}
//����Ա��������
void admin(void)
{
	while (1) {
		adminmenu();
		switch (adminchoice) {
		case '1':
			addbook(); //�������ͼ�麯��
			break;
		case '2':
			delectbook(); //���ø������뺯��
			break;
		case '3':
			changebook(); //�����޸�ͼ�麯��
			break;
		case '4':
			changepassword(); //�����޸Ĺ���Ա���뺯��
			break;
		case '5':
			showbook();  //���ñ���ͼ�麯��
		default:
			exit(0);  //�˳�����
			break;
		}
	}
}

//����Ա��½����
int adminlogin(void)
{
	int c = 3;
	char a[n], b[n];
	printf("�˻�:admin\n");
	FILE *fp;
	if ((fp = fopen(passfile, "r")) == NULL) {
		printf("cannot open this file!!!\n");
		exit(0);
	}
	fgets(b, n, fp);
	printf("����������:(10λ����)\n");
	printf("ע:��ʼ����Ϊ123456789\n");
	loop:scanf("%s", a);
	while (c >= 0) {
	if (strcmp(a, b) == 0)
	{
		printf("������ȷ!!!\n");
		printf("��ӭ�����װ��Ĺ���Ա\n");
		system("pause");
	}
	else
	{
		printf("�������� �������������루������%d�λ��ᣩ",c);
		c--;
		goto loop;
	}
	if (c < 0)
	{
		printf("����������������3�� ϵͳ���˳�\n");
		exit(0);
	}
	admin();
}
}

//���ͼ�麯��
void addbook(void)
{
	int b=0;
	char c,e;
	book a[m]; //�����鼮������
	FILE *fp;
	if ((fp = fopen(bookfile,"r")) == NULL) {
		printf("cannot open this file!!!\n");
	}
	for (int i = 0; i < m; i++)
		fread(&a[i],sizeof(book),1,fp);
	fclose(fp);
	b = foundindex(a);
		if (b == m - 1) {
			printf("û��λ�����ͼ���ˣ�ϵͳ���˳�\n");
			exit(0);
		}
			loopy:printf("��������������鼮������:\n");
			scanf("%s", a[b].name);
			a[b].a = 1;  //0��ʾ���� 1��ʾû�б���
			b++;
			printf("�Ƿ���Ҫ������Ӻ���? ��������������԰�y\n");
			printf("\n");
			c = getche();
			if ((c =='y') || (c == 'Y'))
				goto loopy;
			if ((fp == fopen(bookfile, "w")) == NULL) {
				printf("¼���ļ����ɹ�ϵͳ���˳�\n");
				exit(0);
			}
			for (int i = 0; i < m; i++) {
				fwrite(&a[i], sizeof(book), 1, fp);
			}
			fclose(fp);
		printf("�������Ĳ�����?\n");
		printf("--------------------\n");
		printf("(1)������һ��\t(2)�˳�ϵͳ\n");
		printf("--------------------\n");
		loop:e = getche();
		if (e<'1' || e>'2') {
			printf("���������:\n");
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

//���Ĺ���Ա���뺯��
void changepassword(void)
{
	char a[n],e;
	printf("����������������:\n");
	scanf("%s",a);
	FILE *fp;
	fp = fopen(passfile,"w");
	if (!fputs(a,fp))
		printf("�޸ĳɹ�\n");
	else
		printf("�޸�ʧ��\n");
	fclose(fp);
	printf("�������Ĳ�����?\n");
	printf("--------------------\n");
	printf("(1)������һ��\t(2)�˳�ϵͳ\n");
	printf("--------------------\n");
loop:e = getche();
	if (e<'1' || e>'2') {
		printf("���������:\n");
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

//ɾ��ͼ�麯��
void delectbook(void) {
	FILE *fp;
	char c[n],e;
	int b=0,d=0,f=0; //�ҵ�����λ��
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
	printf("����������Ҫɾ����ͼ��:\n");
	scanf("%s",c);
	for (int i = 0; i < b; i++) {
		if (strcmp(c, a[i].name) == 0) {
			d = i;
			f = 1;
			break;
		}
	}
	if (f = 0) {
		printf("δ�ҵ�����Ҫɾ����ͼ��\n");
	}
	else {
		for (int i = d; i<=b; i++) {
			strcpy(a[i].name, a[i + 1].name);
			a[i].a = a[i + 1].a;
		}
		if ((fp = fopen(bookfile, "w")) == NULL) {
			printf("δ�ܳɹ�¼���ļ�!\n");
			exit(0);
		}
		for (int i = 0; i < m; i++) {
			fwrite(&a[i],sizeof(book),1,fp);
		}
		fclose(fp);
	}
	printf("�������Ĳ�����?\n");
	printf("--------------------\n");
	printf("(1)������һ��\t(2)�˳�ϵͳ\n");
	printf("--------------------\n");
loop:e = getche();
	if (e<'1' || e>'2') {
		printf("���������:\n");
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

//�޸�ͼ�麯��
void changebook(void) {
	FILE *fp;
	int b=0,e=0,f=0;  //��¼����λ��
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
	b = foundindex(a);  //�ҵ�����λ��
	printf("��������������Ҫ�޸ĵ���������:\n");
	scanf("%s",c);
	for (int i = 0; i < b; i++) {
		if (strcmp(c, a[i].name) == 0) {
			e = 1;
			f = i;
		}
	}
	if (e == 0) {
		printf("û���Ȿ��!\n");
	}
	else {
		printf("����������ı������:\n");
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
	printf("�������Ĳ�����?\n");
	printf("--------------------\n");
	printf("(1)������һ��\t(2)�˳�ϵͳ\n");
	printf("--------------------\n");
loop:k = getche();
	if (k<'1' || k>'2') {
		printf("���������:\n");
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

//��ʾ������Ϣ�ĺ���
void showbook(void) {
	FILE *fp;
	book a[m];
	char e;
	int b;  //��¼���һ��λ�õ�����
	if ((fp = fopen(bookfile, "r")) == NULL)
	{
		printf("cannot open this file");
	}
	for (int i = 0; i < m; i++) {
		fread(&a[i],sizeof(book),1,fp);
	}
	b = foundindex(a);
	printf("ͼ����\t\t\t���״̬\n");
	for (int i = 0; i < b; i++) {
		if (a[i].a == 1)
		{
			printf("%s\t\tû����\n",a[i].name);
		}
		else {
			printf("%s\t����\n",a[i].name);
		}
	}
	printf("�������Ĳ�����?\n");
	printf("--------------------\n");
	printf("(1)������һ��\t(2)�˳�ϵͳ\n");
	printf("--------------------\n");
loop:e = getche();
	if (e<'1' || e>'2') {
		printf("���������:\n");
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

//�û�����ѡ��

void usersfirstmenu(void) {
	printf("--------------------\n");
	printf("(1)��½�˻�\t(2)ע���û�");
	printf("--------------------\n");
	char f;
	printf("����������ѡ��:\n");
	loop:f = getche();
	if (((f - '0') > 2) || ((f - '0') < 0)) {
		printf("��ѡ����ȷѡ��\n");
		goto loop;
	}
	switch (f) {
	case '1':
		userslogin();  //�û���¼����
		break;
	default:
		usersregister();  //ע�ắ��
	}
}

//�û���½����

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
	printf("�������˺ź�����:\n");
	printf("�˻���:\n");
	scanf("%s",d.usersname);
	printf("����:\n");
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
					printf("�������������:\n");
					c--;
					scanf("%s", d.password);
				}
			}
			if (c < 0)
			{
				printf("�������������붼����ȷ ϵͳ���˳�\n");
				exit(0);
				system("pause");
			}
		}
	}
		if (e == 0) {
			printf("û�д��û�\n");
			exit(0);
			system("pause");
		}
		else
		{
			printf("��½�ɹ�������\n");
			if (strcmp(a[f].books, "noname")==0) {
				printf("��û�н��ͼ��!\n");
			}
			else {
				printf("�����ĵ�ͼ����:%s",a[f].books);
			}
			usersmenu(f);
		}

}

//�û���½��Ĳ˵�

void usersmenu(int f)
{
	printf("-------------------\n");
	printf("(1)����ͼ�� \t(2)��ͼ��\t(3)����\t(4)��ʾ����ͼ��\t(5)�޸�����(6)�˳�����\n");
	printf("-------------------\n");
loop:usersmenuchoice = getche();
	printf("\n");
	if (((usersmenuchoice - '0') > 6) || ((usersmenuchoice- '0') < 0)) {
		printf("��ѡ����ȷѡ��\n");
		goto loop;
	}
	switch (usersmenuchoice) {
	case '1':
		foundbook(f);  //���ò���ͼ�麯��
		break;
	case '2':
		borrowbook(f);  //���ý��麯��
		break;
	case '3':
		backbook(f);  //���û��麯��
		break;
	case '4':
		showbooks(f);  //������ʾ����ͼ�麯��
		break;
	case '5':
		changeuserspassword(f);  //�����޸��û����뺯��
		break;
	default:
		exit(0);
		break;
	}
}

//���Һ���
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
	printf("����������Ҫ��ѯ������:\n");
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
		printf("û�д���!!!\n");
	}
	else 
	{
		printf("��ѯ������!\n���Ϊ:\n");
		printf("--------------------\n");
		printf("����\t����״̬\n");
		if (a[h].a == 0) {
			printf("%s\t������\n",a[h].name);
		}
		else {
			printf("%s\tû�б�����\n",a[h].name);
		}
		printf("--------------------\n");
		
	}
	printf("�������Ĳ�����?\n");
	printf("--------------------\n");
	printf("(1)������һ��\t(2)�˳�ϵͳ\n");
	printf("--------------------\n");
loop:g = getche();
	if (g<'1' || g>'2') {
		printf("���������:\n");
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

//���ͼ�麯��
void borrowbook(int a) {
	FILE *fp,*p;
	book b[m];
	users e[m];
	char c[n],g;
	int d,f=0;  //�ҵ�ͼ������һ��λ��
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
		printf("���Ѿ��н���ͼ��!!!���ȹ黹ͼ��!\n");
	}
	else
	{
		printf("������������Ҫ�����\n");
		scanf("%s",c);
	}
	
	for (int i = 0; i < d; i++) {
		if (strcmp(c, b[i].name) == 0) {
			if (b[i].a == 1) {
				strcpy(e[a].books,b[i].name);
				b[i].a = 0;  //1��ʾû�б��� 0��ʾ����
			f = 1;
			break;
		     }
			else {
				printf("���ҵ�ͼ���Ѿ�����\n");
			}
		}
	}
	if (f == 1) {
		printf("����ɹ�������\n");
	}
	else {
		printf("δ���ҵ������� ����δ�ɹ�!!!\n");
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
	printf("�������Ĳ�����?\n");
	printf("--------------------\n");
	printf("(1)������һ��\t(2)�˳�ϵͳ\n");
	printf("--------------------\n");
loop:g = getche();
	if (g<'1' || g>'2') {
		printf("���������:\n");
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

//���麯��
void backbook(int a) {
	FILE *fp,*p;
	book b[m];
	users f[m];
	char c, g;
	int d;  //�ҵ�ͼ������һ��λ��
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
		printf("��û�н���ͼ��!!!\n\n");
	}
	else
	{
		printf("ȷ��Ҫ�黹��\n��1����\t(2)��");
		c = getche();
		printf("\n");
	}
	if (c == '1') {
		for (int i = 0; i < d; i++) {
			if (strcmp(b[i].name, f[a].books) == 0) {
				b[i].a = 1;
				strcpy(f[a].books,"noname");
				printf("����ɹ�!!!\n");;
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
	printf("�������Ĳ�����?\n");
	printf("--------------------\n");
	printf("(1)������һ��\t(2)�˳�ϵͳ\n");
	printf("--------------------\n");
loop:g = getche();
	if (g<'1' || g>'2') {
		printf("���������:\n");
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

//�û���ʾ����ͼ�麯��
void showbooks(int f) {
	FILE *fp;
	book a[m];
	char e;
	int b;  //��¼���һ��λ�õ�����
	if ((fp = fopen(bookfile, "r")) == NULL)
	{
		printf("cannot open this file");
	}
	for (int i = 0; i < m; i++) {
		fread(&a[i], sizeof(book), 1, fp);
	}
	b = foundindex(a);
	printf("ͼ����\t\t\t���״̬\n");
	for (int i = 0; i < b; i++) {
		if (a[i].a == 1)
		{
			printf("%s\t\tû����\n", a[i].name);
		}
		else {
			printf("%s\t����\n", a[i].name);
		}
	}
	printf("�������Ĳ�����?\n");
	printf("--------------------\n");
	printf("(1)������һ��\t(2)�˳�ϵͳ\n");
	printf("--------------------\n");
loop:e = getche();
	if (e<'1' || e>'2') {
		printf("���������:\n");
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

//�޸��û����뺯��
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
	printf("����������Ҫ�޸ĵ�����:\n");
	scanf("%s",b);
	strcpy(a[f].password,b);
	printf("�޸�����ɹ�\n");
	if ((fp = fopen(usersfile, "w"))==NULL) {
		exit(0);
		system("pause");
	}
	for (int i = 0; i < m; i++) {
		fwrite(&a[i],sizeof(users),1,fp);
	}
	fclose(fp);
	printf("�������Ĳ�����?\n");
	printf("--------------------\n");
	printf("(1)������һ��\t(2)�˳�ϵͳ\n");
	printf("--------------------\n");
loop:e = getche();
	if (e<'1' || e>'2') {
		printf("���������:\n");
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

//�û�ע�ắ��
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
	printf("�����������û�����:\n");
	loop:scanf("%s",a[f].usersname);
	for (int i = 0; i < f; i++) {
		if (strcmp(a[i].usersname, a[f].usersname) == 0) {
			printf("�������Ѿ���ռ�� ����������:\n");
			goto loop;
		}
	}
	printf("��������������:\n");
	scanf("%s",a[f].password);
	if ((fp = fopen(usersfile, "w")) == NULL) {
		exit(0);
		system("pause");
	}
	for (int i = 0; i < m; i++) {
		fwrite(&a[i],sizeof(users),1,fp);
	}
	fclose(fp);
	printf("���������Ĳ�����?\n");
	printf("--------------------\n");
	printf("(1)��½\t(2)�˳�����\n");
	printf("--------------------\n");
loopy:p = getche();
	if ((p < '1') || (p > '2')) {
		printf("�����������������\n");
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










//�����û��ļ�����
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
		printf("������:%s��%s\n",c[i].usersname,c[i].password);
	}
	fclose(fp);
	system("pause");
	return 0;

}*/

//����ͼ���ļ�
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
//��������Ա�����ļ�
/*int main()
{
	FILE *fp;
	char a[n];
	if ((fp = fopen(passfile, "w")) == NULL) {
		printf("cannot create this file\n");
		exit(0);
		system("pause");
	}
	printf("�����ʼ����:\n");
	scanf("%s",a);
	fputs(a,fp);
	fclose(fp);
	return  0;
}*/

