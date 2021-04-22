#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h> 

#define MenuLength(x)  (sizeof(x)/sizeof(x[0]))
#define WIDTH 60
#define HEIGHT 20
#define true 1
#define false 0
#define SIGN_UP 1
#define SIGN_IN 0
#define LOGIN 2
#define LOST 1
#define FIND 2

void AdminLoginMenu_Option(void);  
void AdminMenu_Option(void);
void AskforResetPassword(void);
void BlankMenu_Option(int page);
void ChangeAdminPassword(void);
void ChangePasswordMenu_Option(void);
void ChangeUserName(char *name_or_password,int status);
void ChangeUserInfoPage(int status); 
void ConsoleSet(void);
void CreatRandStr(char *str);
void EnDecryptFile(char *file, char *secretKey);
void GetNowTime(char *now_time);
void GetPostData(void);
void Gets(char *str, int n);
int  GetUserNumber(void);
int  GetUserInput(int *index , int size , int status);
int  JudgeIsSignin(int page); 
void JudgePage(int page);
void RedirectPage(int page);
int  ResetUserPassword(char *phone_or_stdnum,int status); 
void ResetUserPasswordPage(void); 
void SetCursorPosition(HANDLE Handle_Out , int x , int y);
void ShowLeaveWord(void);
void ShowMenu(char **menu , char *menu_title ,char menu_size, int index , char statusColor);
void ShowUserMessage(void);
void ShowUserPost(int pos, int aa, int bb);
void ShowOverPost(int pos, int aa, int bb);
void SignUpMenu_Option(void);
void SignInMenu_Option(void);
void StartMenu_Option(void);
void UserMenu_ChangeInfo_Option(void);
void UserMenu_PubPost_Option(int status);
void UserMenu_PubPost_OptionShow(int y , int statusColor);
void UserMenu_MyInfo_Option(void);
void UserMenu_Option(void);
void ViewUserInfo(void);
void VistorMenu_Option(void);
void WelcomPage(void);

char myKey[24] = "^?z(���0Z6O�mXyY�t��Lc";
enum 
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	ENTER = 13,
	ESC = 27,
	SPACE = 32	//�ո�Ϊ32�� 
};

//��ʼ�˵�
char *start_menu[] = 
{
	"��  �οͷ���  ��",
	"��  �û���¼  ��",
	"�� ����Ա��¼ ��",
	"��    ע��    ��",
	"��    �˳�    ��",
};

//ע��˵�
char *signup_menu[] = 
{
	"�ֻ��ţ�", 
	"�û�����",
	"ѧ�ţ�",
	"���룺",
	"�ٴ��������룺",
	"[ ȷ��ע�� ]", 
	"[   ����   ]",
};

//�û���¼�˵�
char *signin_menu[] = 
{
	"�ֻ���/ѧ�ţ�", 
	"���룺",
	"[ ȷ�ϵ�¼ ]", 
	"[   ����   ]",
	"û���˺ţ����ע��", 
	"�������룿��������",
};

//����Ա��¼ 
char *admin_login_menu[] = 
{
	"�˺ţ�", 
	"���룺",
	"[ ȷ�ϵ�¼ ]", 
	"[   ����   ]",
};

//����Ա�˵� 
char *admin_menu[] = 
{
	"��   ʧ��ǽ   ��",
	"��   Ѱ��ǽ   ��",
	"�� �ѽ������� ��",
	"��  �û���Ϣ  ��",
	"��  �޸�����  ��",
	"��    ����    ��",
	"��    �˳�    ��",
};

//�οͲ˵� 
char *vistor_menu[] = 
{
	"��   ʧ��ǽ   ��",
	"��   Ѱ��ǽ   ��",
	"��    ����    ��",
};
 
//�û��˵� 
char *user_menu[] = 
{
	"��   ʧ��ǽ   ��",
	"��   Ѱ��ǽ   ��",
	"��  �ҵ�����  ��",
	"��  �ҵ���Ϣ  ��",
	"��    ����    ��",
	"��    �˳�    ��",
};  
 
//�û��˵�֮�ҵ�����
char *user_post_menu[] = 
{	
	"��  �ҵ�����  ��",
	"������ʧ�����ӣ�",
	"������Ѱ�����ӣ�",	 
	"��    ����    ��",
}; 

//�û��˵�->�ҵ�����->ʧ������ 
char *user_lost_or_find_post_menu[] = 
{	
	"���ƣ�",
	"�ص㣺", 
	"������",
	"����������",
	"[��Ƭ]",
	"[Կ��]",
	"[����]",
	"[�鱾]",
	"[�·�]",
	"[����]",
	"[ȷ�Ϸ���]",
	"[ ���� ]",
};

//�û��˵�->��������->ѡ����� 
char *category_post_menu[] = 
{	
	"��Ƭ",
	"Կ��",
	"����",
	"�鱾",
	"�·�",
	"����", 
}; 
 
//��������ҳ�� 
char *post_detail_menu[] = 
{	
	"���ƣ�",
	"����������",
	"���ڵص�",
	"ӵ���ߣ�",
	"��ϵ��ʽ��",
};

//�û��˵�֮�û���Ϣ 
char *user_myinfo_menu[] = 
{
	"�ֻ��ţ�",
	"  ѧ�ţ�",
	"  �ǳƣ�",
	"  ���룺",
	"[ �޸� ]",
	"[ ���� ]",
	"[ �˳� ]",
};  

char *user_change_info_menu[] = 
{
	"��  �޸��ǳ�  ��",
	"��  �޸�����  ��",
	"��    ����    ��", 
};
 
//�޸�����˵� 
char *change_password_menu[] = 
{
	"���޸��ҵ����룪",
	"�������û����룪",
	"��    ����    ��", 
};

//��ҳ��˵� 
char *blank_menu[] = 
{
	"�� ������һ�� ��",
	"��  ֱ���˳�  ��",
};

//�˵�ҳ��ı��� 
struct MENU_TITLE 
{
	char *start_menu;
	char *signup_menu;
	char *signin_menu;
	char *admin_login_menu; 
	char *admin_menu;
	char *vistor_menu; 
	char *user_menu;
	char *user_post_menu;
	char *user_lost_post_menu; 
	char *user_find_post_menu;
	char *user_myinfo_menu;
	char *user_change_info_menu;
	char *post_detail_menu; 
	char *change_password_menu;
	char *blank_menu;
}Menu_Title={"��ӭ����ʧ���������ϵͳ��","ע�����","��¼����","����Ա��¼����","����Ա�������","�οͽ���","�û��������","��������","����ʧ������","����Ѱ������","�ҵ���Ϣ","�޸���Ϣ","��������ҳ��","�޸��������","��ҳ���������ݣ�"};

struct PAGE
{
	int start_menu;
	int signup_menu;
	int signin_menu;
	int admin_login_menu;
	int admin_menu;
	int user_menu;
	int user_myinfo_menu;
	int change_password_menu;
	int user_change_info_menu; 
	int user_post_menu;
	int vistor_menu;
}Page={1,2,3,4,5,6,7,8,9,10,11};

//����һ���ṹ�������ϵͳ���� 
struct CONFIG
{
	int user_numbers;
	int lost_numbers;	//ʧ�����ӵ����� 
	int find_numbers;	//Ѱ�����ӵ�����
	int message_numbers;	//�û�������Ա�����Ը��� 
	char secret_key[24]; 
}Config;

//����һ���ṹ����ѧ����Ϣ 
struct STUDENT_INFO
{
	char phone[12];
	char name[20];
	char studnum[12];
	char password[20];
	char repassword[20];
};

//��Ҫ����û���¼��Ϣ 
struct USER_INFO
{
	int user_numbers;	//���� 
	int user_seriNum;	//���  
	struct STUDENT_INFO StudInfo; 	//���ѧ����Ϣ�Ľṹ��ָ�� 
}User_Info;

//��ʧorѰ�ҵ���Ʒ 
struct POST_THING
{
	int visible;	//�Ƿ�ɼ������ɼ�Ϊ�����Ľ��� 
	char user_name[20];	//�û����� 
	char phone[12];		//�û��绰 
	char item_name[12];	//��Ʒ������ 
	char site[20];			//�ص� 
	char category[12];		//��� 
	char brief[20];		//���� 
	char detail[50];		//��ϸ���� 
	char time[20];	//����ʱ��ʱ�� 
	char IDnumber[10]; //���ӵ�Ψһ��� 
}; 

//�ڳ����ﻺ����������
struct POST
{
	int lost_numbers;
	int find_numbers;
	struct POST_THING *Lost;
	struct POST_THING *Find;
}Post; 

//�û�������Ա���ԵĽṹ�� 
struct USER_MESSAGE
{
	int visible;	//�Ƿ�ɼ�����ʾ����Ա�Ƿ��ѽ���û����⣨�������룩 
	char user_name[20];	//���������� 
	char user_phone[12];
	char content[60];	//������ʮ�ַ�����
	char time[20];
};

//�û����԰�ṹ�� 
struct MESSAGE_BOARD
{
	char user_name[20];	//���������� 
	char user_phone[12];
	char content[60];	//������ʮ������
	char time[20];
	char IDnumber[10];
};	

//ÿ���û��������Կռ䣬���ڴ�����˵����� 
struct WORD_SPACE
{
	char master_name[20];
	char master_phone[12];
	int message_numbers;
	struct MESSAGE_BOARD Message[15];	//�ܱ���ʹ��ָ��*Message����⣬�ر��漰�����ؽṹ�����ļ��϶�ȡʱ 
};

/**** ���ṹ������ĺ����������ڽṹ��֮���� ****/
void ChangeMyPost(struct POST_THING Post_Thing, int pos, int a, int b); 
void ChangeStudentInfo(struct STUDENT_INFO Student_Info,int seri_num);
void DeleteMyPost(struct POST_THING Post_Thing, int pos, int a, int b);
void ExportUserInfo(struct STUDENT_INFO *Student,int user_numbers);
void ExportMyPostInfo(struct POST_THING *Post, int post_numbers, char *cat, char *rw_mode);
void GetUserInformation(struct STUDENT_INFO Student_Info,int user_numbers,int seri_num);
int  JudgePostInfo(struct POST_THING Post_Thing);
int  JudgeUserInfo(struct STUDENT_INFO Student_Info,int signup_or_signin);
void LeaveWord(struct POST_THING Post_Thing , int page , int status , int pos, int a, int b);
void PostDetailPage(struct POST_THING Post_Thing, int page, int status, int pos, int a, int b); 
int  SeekStudentInfo(struct STUDENT_INFO Student_Info,int signup_or_signin);
void ShowPostWall(struct POST_THING *Post, int page, int status, int pos, int aa, int bb);
void ShowUserInfo(struct STUDENT_INFO *Student,int user_numbers);
void ViewMyPostPage(struct POST_THING Post_Thing, int pos, int a, int b);
void ViewOverPostPage(struct POST_THING Post_Thing, int pos, int a, int b);
void WriteFindInfo(struct POST_THING Find_Thing);
void WriteLostInfo(struct POST_THING Lost_Thing); 
void WriteLeaveWord(struct POST_THING Post_Thing , char *content);
void WriteUserMessage(struct USER_MESSAGE User_Message); 


/*   ������    */ 
int main()
{
	ConsoleSet();
	WelcomPage();	   
    StartMenu_Option();
	
    return 0;
}

/******************************************* 
*   ������ void ConsoleSet() 
*	���ܣ�����̨���� 
*	��������					
*	���ã���ʼʱ���ô˺�����ʼ������̨ 
*	���ߣ�xxx
*******************************************/ 
void ConsoleSet()
{		
	// ���ô��ڴ�С �Լ�ǰ������ɫ 
    system("mode con cols=60 lines=20");	//60�ַ���20�ַ��� 
    system("color 70");
	//���ÿ���̨���� 
    SetConsoleTitleA("ʧ���������ϵͳ");
    //��ȡ��ǰ�ľ��---����Ϊ��׼������ 
    HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE); 
    //���ÿ���̨����Ĵ�С
	CONSOLE_FONT_INFOEX Font_Set;
	Font_Set.cbSize = sizeof(Font_Set);
	Font_Set.dwFontSize.X = 13;
	Font_Set.dwFontSize.Y = 28;
	Font_Set.FontWeight = 700;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &Font_Set);
	//���ô��ڵ���ʾλ�� 
	SMALL_RECT rect = {0, 0, 60, 20};
	SetConsoleWindowInfo(Handle_Out, 1, &rect); 
    //��������Ϣ�ṹ��   
	CONSOLE_CURSOR_INFO Corsor_Info; 
    //��ȡ�����Ϣ
    GetConsoleCursorInfo(Handle_Out, &Corsor_Info); 
	//���ù���С   
    Corsor_Info.dwSize = 1; 
	//���ù�겻�ɼ� FALSE   
    Corsor_Info.bVisible = 0; 
    //����(Ӧ��)�����Ϣ
    SetConsoleCursorInfo(Handle_Out, &Corsor_Info); 
 } 
 
 
/******************************************* 
*   ������ void ShowMenu(char **menu , char *menu_title ,char menu_size, int index , char statusColor)
*	���ܣ�չʾ�˵� 
*	������1.�ַ�������menuΪҪչʾ�Ĳ˵� 2.�ַ���menu_titleΪ�˵��ı���
		  3.������menu_sizeΪ�˵��Ĵ�С  3.������indexΪ����ֵ					
*	���ã�����˵��йص���Ϣ������ֵ���ͻ�չʾ���˵�ҳ�� 
*	���ߣ�xxx
*******************************************/  
void ShowMenu(char **menu , char *menu_title ,char menu_size, int index , char statusColor)
{ 	
	char time[20];
	char len = strlen(menu_title);
	GetNowTime(time);
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	//������ʾ������̨�ն˵ľ���λ�� 
	SetCursorPosition(Handle_Out,(WIDTH-len)/2,0);    
	printf("%s",menu_title);	//��ӡ���� 
	SetCursorPosition(Handle_Out,23,1);
	printf("%s",time);			//��ӡʱ�� 
	
	for(int i = 0 ; i < menu_size ; i++)
	{
		if(i == index)
		{
			if(statusColor==1)			
				SetConsoleTextAttribute(Handle_Out,0x90);  //ǳ��ɫ 
			else
				SetConsoleTextAttribute(Handle_Out,0x10);  //��ɫ 			
		}
		//������ʾΪ��ɫ 
		else
			SetConsoleTextAttribute(Handle_Out,0x70); 
		SetCursorPosition(Handle_Out,22,4+i);    
    	printf("%s",menu[i]);
	}
    SetCursorPosition(Handle_Out,22+strlen(menu[index]),4+index);
	//ˢ�±�׼��������� 
	fflush(stdout);
} 


/******************************************* 
*   ������ void StartMenu_Option(void)
*	���ܣ���¼�����ѡ����� 
*	��������					
*	���ã��˺�������ò˵���ʾ��������ʵ�ֲ˵�ѡ��Ŀ��ӻ����� 
*	���ߣ�xxx
*******************************************/ 
void StartMenu_Option(void)
{
	system("color 70");		//*��ʱ����ȥ��*// 
	system("cls");	//�����Ļ	
	//�����������岻�Ӵ� 
	CONSOLE_FONT_INFOEX Font_Set;
	Font_Set.cbSize = sizeof(Font_Set);
	Font_Set.dwFontSize.X = 13;
	Font_Set.dwFontSize.Y = 28;
	Font_Set.FontWeight = FW_THIN;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &Font_Set);
	int index = 0;
	while(1)
	{
		ShowMenu(start_menu , Menu_Title.start_menu , MenuLength(start_menu) , index , 1);
		int user_input = GetUserInput(&index , MenuLength(start_menu) ,1);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: VistorMenu_Option(); break;  	//�οͷ��� 
				case 1: SignInMenu_Option(); break;  	    //�û���¼ 
				case 2: AdminLoginMenu_Option();break;  	//����Ա��¼ 
				case 3: SignUpMenu_Option(); break;  	//ע��
				case 4: exit(1);  break;  	//�˳�
			}
		}
	} 
} 

//ע�����ѡ�����  *��ʽͬ����* 
void SignUpMenu_Option(void)
{
	system("cls");	//�����Ļ 
	int index = 0;
	char statusColor = 1;
	struct STUDENT_INFO Student_Info={"","","","",""};
	while(1)
	{
		ShowMenu(signup_menu , Menu_Title.signup_menu , MenuLength(signup_menu) , index , 1);
		int user_input = GetUserInput(&index , MenuLength(signup_menu) ,1);
		if(user_input == ENTER	)
		{
			statusColor = -statusColor;
		}			 
		ShowMenu(signup_menu , Menu_Title.signup_menu , MenuLength(signup_menu),index , statusColor);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			statusColor = -statusColor;
			switch(index)
			{
				case 0: Gets(Student_Info.phone,12);  break;  	//�ֻ��� 
				case 1: Gets(Student_Info.name,20);   break;  	//�û��� 
				case 2: Gets(Student_Info.studnum,12); break;  	//ѧ�� 
				case 3: Gets(Student_Info.password,20);break;  	//����
				case 4: Gets(Student_Info.repassword,20); break;  //�ٴ��������� 
				case 5:	if(JudgeUserInfo(Student_Info,SIGN_UP)==true){RedirectPage(Page.signup_menu);} break;//ȷ��ע�� 
				case 6: StartMenu_Option();  break;  	//����		
			}
		}
	} 
}


//�û���¼����ѡ�����  *��ʽͬ����* 
void SignInMenu_Option(void)
{
	system("cls");	//�����Ļ 
	int index = 0;
	char statusColor = 1;
	struct STUDENT_INFO Student_Info={"","","","",""};
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);  
	while(1)
	{		
		ShowMenu(signin_menu , Menu_Title.signin_menu , MenuLength(signin_menu) , index , 1);
		int user_input = GetUserInput(&index , MenuLength(signin_menu) ,1);
		if(user_input == ENTER)
			statusColor = -statusColor;			 
		ShowMenu(signin_menu , Menu_Title.signin_menu , MenuLength(signin_menu),index , statusColor);
		SetConsoleTextAttribute(Handle_Out, 0x70);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			statusColor = -statusColor;
			switch(index)
			{
				case 0: Gets(Student_Info.phone,12); break;  	//�ֻ��Ż�ѧ�� 
				case 1: Gets(Student_Info.password,20);  break;  	//���� 
				case 2: if(JudgeUserInfo(Student_Info,SIGN_IN)==true){RedirectPage(Page.signin_menu);} break; //ȷ�ϵ�¼ 
				case 3: StartMenu_Option(); break;        	//����
				case 4: SignUpMenu_Option();  break;   	//��ûע�� 
				case 5: AskforResetPassword();  break;  	//�������� 
		
			}
		}
	} 
} 

//����Ա��¼����ѡ�����  *��ʽͬ����* 
void AdminLoginMenu_Option(void)
{
	system("cls");	//�����Ļ 
	int index = 0;
	char statusColor = 1;
	struct STUDENT_INFO Student_Info={"","","","",""};	
	while(1)
	{
		ShowMenu(admin_login_menu , Menu_Title.admin_login_menu , MenuLength(admin_login_menu) , index , 1);	
		int user_input = GetUserInput(&index , MenuLength(admin_login_menu) ,1);
		if(user_input == ENTER	)
		{
			statusColor = -statusColor;
		}			 
		ShowMenu(admin_login_menu , Menu_Title.admin_login_menu , MenuLength(admin_login_menu),index , statusColor);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			statusColor = -statusColor;
			switch(index)
			{
				case 0: Gets(Student_Info.name,20);  break;  	//�˺� 
				case 1: Gets(Student_Info.password,20);  break; //���� 
				case 2: if(JudgeUserInfo(Student_Info,LOGIN)==true){RedirectPage(Page.admin_login_menu);} break;//ȷ�ϵ�¼ 
				case 3: StartMenu_Option(); break;        	//����		
			}
		}
	} 
}

//����Ա����ѡ�����  *��ʽͬ����* 
void AdminMenu_Option(void)
{
	system("cls");
	int index = 0 ;
	while(1)
	{
		ShowMenu(admin_menu , Menu_Title.admin_menu , MenuLength(admin_menu) , index , 1);
		int user_input = GetUserInput(&index , MenuLength(admin_menu) ,1);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: ShowPostWall(Post.Lost, Page.admin_menu, LOST, 1, 1, 0); break;  	//ʧ��ǽ  
				case 1: ShowPostWall(Post.Find, Page.admin_menu, FIND, 1, 1, 0); break;  	//Ѱ��ǽ
				case 2: ShowOverPost(1, 1, 0); break;  	//�ѽ�������
				case 3: ViewUserInfo(); break;  	//�û���Ϣ 
				case 4: ChangePasswordMenu_Option(); break;			//�޸����� 
				case 5: ShowUserMessage(); break;		//���� 
				case 6: StartMenu_Option(); 	break; 	//�˳� 
		
			}
		}
	} 
} 

//����Ա����ѡ�����  *��ʽͬ����* 
void VistorMenu_Option(void)
{
	system("cls");
	int index = 0 ;
	while(1)
	{
		ShowMenu(vistor_menu , Menu_Title.vistor_menu , MenuLength(vistor_menu) , index , 1);
		int user_input = GetUserInput(&index , MenuLength(vistor_menu) ,1);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: ShowPostWall(Post.Lost, Page.vistor_menu, LOST, 1, 1, 0); break;  	//ʧ��ǽ  
				case 1: ShowPostWall(Post.Find, Page.vistor_menu, FIND, 1, 1, 0); break;  	//Ѱ��ǽ
				case 2: StartMenu_Option(); 	break; 	//���� 
		
			}
		}
	} 
} 


//�û�����ѡ�����  *��ʽͬ����* 
void UserMenu_Option(void)
{	
	system("cls");
	int index = 0 ;
	while(1)
	{
		char title[20],*ch = "��ӭ����";
		sprintf(title,"%s%s",ch,User_Info.StudInfo.name);
		ShowMenu(user_menu , title , MenuLength(user_menu) , index , 1);
		int user_input = GetUserInput(&index , MenuLength(user_menu) ,1);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: ShowPostWall(Post.Lost, Page.user_menu, LOST, 1, 1, 0); break;  	//ʧ��ǽ 
				case 1: ShowPostWall(Post.Find, Page.user_menu, FIND, 1, 1, 0); break;  	//Ѱ��ǽ
				case 2: ShowUserPost(1, 1, 0); break;			//�ҵ�����
				case 3: UserMenu_MyInfo_Option(); break;  		//�ҵ���Ϣ 
				case 4: ShowLeaveWord();		//���� 
				case 5: StartMenu_Option(); break; 	//�˳� 
			}
		}
	} 
}

//�û�->�ҵ���Ϣ����ѡ�����  *��ʽͬ����* 
void UserMenu_MyInfo_Option(void)
{
	system("cls");
	int index = 0 ;
	while(1)
	{
		ShowMenu(user_myinfo_menu , Menu_Title.user_myinfo_menu , MenuLength(user_myinfo_menu) , index , 1);
		int user_input = GetUserInput(&index , MenuLength(user_myinfo_menu) ,1);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: puts(User_Info.StudInfo.phone); break;  	//�ֻ��� 
				case 1: puts(User_Info.StudInfo.studnum); break;  	//ѧ�� 
				case 2: puts(User_Info.StudInfo.name); break;  	//�ǳ� 
				case 3: puts(User_Info.StudInfo.password); break;  //���� 
				case 4: UserMenu_ChangeInfo_Option(); break;		//�޸� 
				case 5: UserMenu_Option(); break;		//����
				case 6: StartMenu_Option(); break; 	//�˳� 
		
			}
		}
	} 
}

//�û�->�ҵ���Ϣ->�޸���Ϣ����ѡ�����  *��ʽͬ����*
void UserMenu_ChangeInfo_Option(void)
{
	system("cls");
	int index = 0;
	while(1)
	{
		ShowMenu(user_change_info_menu , Menu_Title.user_change_info_menu , MenuLength(user_change_info_menu) , index , 1);
		int user_input = GetUserInput(&index , MenuLength(user_change_info_menu) ,1);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0:  ChangeUserInfoPage(0); break;  	//�޸��ǳ�
				case 1:  ChangeUserInfoPage(1); break;  	//�޸����� 
				case 2:  UserMenu_MyInfo_Option(); 	 break;     //���� 
			}
		}
	}
}
 

//�޸��������ѡ�����  *��ʽͬ����*
void ChangePasswordMenu_Option(void)
{
	system("cls");
	int index = 0;
	while(1)
	{
		ShowMenu(change_password_menu , Menu_Title.change_password_menu , MenuLength(change_password_menu) , index , 1);
		int user_input = GetUserInput(&index , MenuLength(change_password_menu) ,1);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0:  ChangeAdminPassword(); break;  	//�޸��ҵ����� 
				case 1:  ResetUserPasswordPage(); break;  	//�����û����� 
				case 2:  AdminMenu_Option(); 	 break;     //�˳� 
			}
		}
	}
} 

//��ҳ��ѡ�����  *��ʽͬ����*
void BlankMenu_Option(int page)
{
	system("cls");
	int index = 0;
	while(1)
	{
		ShowMenu(blank_menu , Menu_Title.blank_menu , MenuLength(blank_menu) , index , 1);
		int user_input = GetUserInput(&index , MenuLength(blank_menu) ,1);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: JudgePage(page); break;  	//������һ�� 
				case 1: exit(1);   		 break;  	//ֱ���˳� 
			}
		}
	}
} 


/******************************************* 
*   ������ void JudgePage(int page)
*	���ܣ��ж�ѡ�����ڵ�ҳ�棬����ת����Ӧҳ�� 
*	������int pageΪҳ���ʶ��					
*	���ã��ڿհ�ҳ��ʱ���ô˺��������ڷ���ԭ����ҳ�� 
*	���ߣ�xxx
*******************************************/ 
void JudgePage(int page)
{
	switch(page)
	{
		case 1: StartMenu_Option();  break;
		case 2: SignUpMenu_Option(); break;
		case 3: SignInMenu_Option(); break;
		case 4: AdminLoginMenu_Option();break;
		case 5: AdminMenu_Option();  break;
		case 6: UserMenu_Option();   break;
		case 7: UserMenu_MyInfo_Option(); break;
		case 8: ChangePasswordMenu_Option();break;
		case 9: UserMenu_ChangeInfo_Option();break;
		case 10: ShowUserPost(1,1,0);break;
		case 11: VistorMenu_Option();
	}
}

 
/******************************************* 
*   ������ void RedirectPage(int page)
*	���ܣ��ж��Ƿ��¼�ɹ���Ȼ����ת����Ӧҳ�� 
*	������int pageΪҳ���ʶ��					
*	���ã�ȷ�ϵ�¼ʱ���ô˺��� 
*	���ߣ�xxx
*******************************************/  
void RedirectPage(int page)
{
	system("cls"); 
	COORD Pos = {18,3};
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Handle_Out,Pos); 
	switch(page)
	{
		case 0: printf("�޸��ǳƳɹ���3�����ת..."); break;
		case 1: printf("�޸�����ɹ���3�����ת..."); break;  
		case 2: printf("ע��ɹ���3�����ת..."); break;  //��ʾ�û�ע��ɹ� 
		case 3: printf("��¼�ɹ���3�����ת..."); break;	//��ʾ�û���¼�ɹ� 		 
		case 4: printf("��¼�ɹ���3�����ת..."); break;  //��ʾ����Ա��¼�ɹ� 
		case 5: printf("�������ݳɹ���3�����ת..."); break;
		case 6: printf("��������ɹ���3�����ת..."); break;
		case 7: printf("�����ɹ���3�����ת..."); break;
		case 8: printf("�޸ĳɹ���3�����ת..."); break;
		case 9: printf("ɾ�����ӳɹ���3�����ת..."); break;
		case 10: printf("�������ݳɹ���3�����ת..."); break;
		case 11: printf("�������ݳɹ���3�����ת..."); break;
		case 12: printf("���Գɹ���3�����ת..."); break;
		case 13: printf("�ύ����ɹ���3�����ת..."); break;
		default: printf("��¼ʧ�ܣ�3��󽫷���..."); break; //��ʾ�û���¼ʧ��
	} 
	
	Sleep(1500);	//�ȴ�1.5�� 
	switch(page)
	{
		case 0: UserMenu_MyInfo_Option(); break; 
		case 1: UserMenu_MyInfo_Option(); break;  
		case 2: SignInMenu_Option(); break;  //ע��ɹ�����ת��¼���� 
		case 3: UserMenu_Option(); break;	//��ʾ�û���¼�ɹ� 		 
		case 4: AdminMenu_Option(); break;      //��ʾ����Ա��¼�ɹ� 
		case 5: ViewUserInfo(); break;
		case 6: ChangePasswordMenu_Option();
		case 7: ShowUserPost(1,1,0); break;
		case 8: ShowUserPost(1,1,0); break;
		case 9: ShowUserPost(1,1,0); break;
		case 10: ShowUserPost(1,1,0); break;
		case 11: ShowOverPost(1,1,0); break;
		case 12: break;
		case 13: SignInMenu_Option(); break; 
		default: BlankMenu_Option(page); break; 
	} 
}

 
/*******************************************
*   ������JudgeUserInfo(struct STUDENT_INFO Student_Info,int signup_or_signin)
*	���ܣ��ж��û��������Ϣ�Ƿ�����Ҫ�󣬲�������Ӧ�ĸ�ʾ 
*	������������1.ѧ����Ϣ�ṹ��Student_Info,�����ֻ����û�����ѧ�ţ������ 2.signup_or_signinΪ״̬��					
*	���ã�ȷ��ע���ȷ�ϵ�¼ʱ���ô˺���������ֵ1��ʾ����Ҫ��0��ʾ������Ҫ�� 
*	���ߣ�xxx
*******************************************/ 
int JudgeUserInfo(struct STUDENT_INFO Student_Info,int signup_or_signin)
{
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetCursorPosition(Handle_Out,20,12); 
	SetConsoleTextAttribute(Handle_Out,0x74);	//��ɫ������Ŀ 
	if(signup_or_signin==SIGN_UP)
	{
		if(!(strcmp(Student_Info.phone,"") && strcmp(Student_Info.name,"") && strcmp(Student_Info.studnum,"") && strcmp(Student_Info.password,"") && strcmp(Student_Info.repassword,"")))
		{
			printf("    �벻Ҫ���գ�     ");	//����һ��Ϊ�ն����� 
			return 0;
		} 	
		else if(strlen(Student_Info.phone)!=11)
		{
			printf("��������ȷ���ֻ����룡");
			return 0;
		}
		else if(strlen(Student_Info.studnum)!=10)
		{
			printf("   �������ѧ�ţ�   ");
			return 0;
		}
		else if(strcmp(Student_Info.password,Student_Info.repassword))
		{
			printf(" �����������벻һ�£� ");
			return 0;
		}
		else if(SeekStudentInfo(Student_Info,SIGN_UP)==true)
		{
			printf("    ���˺���ע�ᣡ    ");
			return 0; 
		}
	}
	else if(signup_or_signin==SIGN_IN)
	{
		if(!(strcmp(Student_Info.phone,"") || strcmp(Student_Info.password,"")))
		{
			printf(" �������˺������룡   ");
			return 0;
		}
		else if(SeekStudentInfo(Student_Info,SIGN_IN)==false)
		{
			printf(" �˺Ż����벻��ȷ��   ");
			return 0; 
		}
	}
	else
	{
		//����Ա��¼
		if(strcmp(Student_Info.name,"root") || strcmp(Student_Info.password,"123456")) 
		{
			printf(" �˺Ż����벻��ȷ��   ");
			return 0; 
		}
	}
	SetConsoleTextAttribute(Handle_Out,0x70);	//�ָ�ԭ����ɫ 
	
	return 1;
}
 
 
/******************************************* 
*   ������int SeekStudentInfo(struct STUDENT_INFO Student_Info,int signup_or_signin) 
*	���ܣ������ע�����ж��˺��Ƿ��Ѵ��ڣ�û���򴴽�һ�����˻�������ǵ�¼���ж��˺��Ƿ���ȷ�� 
*		  signup_or_signinΪ1��ʾע�ᣬΪ0��ʾ��¼ 
*	������1.ѧ����Ϣ�ṹ��Student_Info,�����ֻ����û�����ѧ�ţ������ 2.signup_or_signinΪ״̬��					
*	���ã��ڵ��ȷ��ע���ȷ�ϵ�¼�����ô˺���(�� JudgeUserInfo(Student_Info��signup_or_signin)��������) 
*		  ����ע�᣺1��ʾ��ע�ᣬ���޷���ע�ᡣ0��ʾΪע�ᣬ������ע��
*		  ���ڵ�¼��1��ʾ�˺ź�������ȷ��0��ʾ�˺Ż�������� 
*	���ߣ�xxx
*******************************************/ 
int SeekStudentInfo(struct STUDENT_INFO Student_Info,int signup_or_signin)
{
	int ifSignup = 0;
    int user_numbers = Config.user_numbers;
	struct STUDENT_INFO Student[user_numbers+1];	 			 
	FILE *fp;			
	//�ж��ļ��Ƿ����,�������򴴽�һ�� 
	if((fp=fopen("student_info.dat","r"))==NULL) 
	{
		fp=fopen("student_info.dat","w");
		fclose(fp);
	} 
	EnDecryptFile("student_info.dat",myKey);	//�����ļ� 
	fp=fopen("student_info.dat","rb");
    for(int i=0;i<user_numbers;i++)
		fread(&Student[i],sizeof(struct STUDENT_INFO),1,fp);  
   	fclose(fp);  	    	
	//SIGN_UP��ʾע�ᣬSIGN_IN��ʾ��¼ 
	if(signup_or_signin==SIGN_UP)
	{
		for(int i=0;i<user_numbers;i++)
		if(!(strcmp(Student[i].phone,Student_Info.phone) && strcmp(Student[i].studnum,Student_Info.studnum)))
			ifSignup = true;	//��ʾ���˺���ע�� 
		if(ifSignup==false)
		{
			Student[user_numbers] = Student_Info;	//���ûע����׷����Ϣ 
			user_numbers++;
		}
		//ֻ���û���ע��ʱ��Ϊ�俪��һ�����Կռ� 
		if(ifSignup==false)
		{
			FILE *fp1;		
			struct WORD_SPACE WSpace[user_numbers];	
			//�ж��ļ��Ƿ����,�������򴴽�һ�� 
			if((fp1=fopen("leave_word.dat","r"))==NULL) 
			{
				fp1=fopen("leave_word.dat","w");
				fclose(fp1);
			}
			EnDecryptFile("leave_word.dat",myKey);
			fp1=fopen("leave_word.dat","rb");
		    for(int i=0;i<user_numbers-1;i++)
				fread(&WSpace[i],sizeof(struct WORD_SPACE),1,fp1);  
		   	fclose(fp1);
		   	//ÿ��ע��һ�����û�ʱ���Զ�Ϊ�����һ�����Կռ䣬����ʼ�� 
		   	strcpy(WSpace[user_numbers-1].master_name,Student_Info.name);
		   	strcpy(WSpace[user_numbers-1].master_phone,Student_Info.phone);
			WSpace[user_numbers-1].message_numbers = 0;	//��ʼʱ����Ϊ0 
			for(int i=0;i<10;i++)
			{
				strcpy(WSpace[user_numbers-1].Message[i].user_name," ");
				strcpy(WSpace[user_numbers-1].Message[i].user_phone," ");
				strcpy(WSpace[user_numbers-1].Message[i].content," ");
				strcpy(WSpace[user_numbers-1].Message[i].time," ");
				strcpy(WSpace[user_numbers-1].Message[i].IDnumber," ");
			}  
			fp1=fopen("leave_word.dat","wb");
		   	fwrite(&WSpace,sizeof(struct WORD_SPACE),user_numbers,fp1);
			fclose(fp1);
			EnDecryptFile("leave_word.dat",myKey);	//�����ļ�
		}
	}
	else if(signup_or_signin==SIGN_IN)
	{
		for(int i=0;i<user_numbers;i++)
		if(!(strcmp(Student[i].phone,Student_Info.phone) && strcmp(Student[i].studnum,Student_Info.phone)) && !strcmp(Student[i].password,Student_Info.password))
		{
			ifSignup = 1;	//����˺���������ȷ���򷵻�1			
			GetUserInformation(Student[i],user_numbers,i);	//������Ϣ���������Ա��ⲿ���� 
		} 
	} 
	fp=fopen("student_info.dat","wb");
   	fwrite(&Student,sizeof(struct STUDENT_INFO),user_numbers,fp);
	fclose(fp);
	EnDecryptFile("student_info.dat",myKey);	//�����ļ� 	
	//���������ļ� 
	Config.user_numbers = user_numbers;
    FILE *cg;
	cg=fopen("config","wb");
	fwrite(&Config,sizeof(struct CONFIG),1,cg);
	fclose(cg);
	EnDecryptFile("config",myKey);
	return ifSignup;	
}  
 
//����û���¼��Ϣ 
void GetUserInformation(struct STUDENT_INFO Student_Info,int user_numbers,int seri_num)
{
	User_Info.StudInfo = Student_Info;
	User_Info.user_seriNum = seri_num;
	User_Info.user_numbers = user_numbers; 	
} 
 
/******************************************* 
*   ������ int  GetUserInput(int index , int menu_size , int status)
*	���ܣ��� ��������ϣ��� ��������£�ESC���˳�,Enter��ȷ�� 
*	������1.����ֵ�˵�index 2.�˵��Ĵ�С 3.statusΪ1��ʾ���°�����Ϊ0��ʾ���Ұ��� 2������					
*	���ã��ڲ˵�ѡ�����ҳ����ô˺��������жϰ��� 
*	���ߣ�xxx
*******************************************/ 
int  GetUserInput(int *index , int menu_size , int status)
{
	int ch = getch();
	if(status!=2)
	switch(ch)
	{
		//���ѡ���ϣ���ô��������ƶ� ������Ҳͬ�� 
		case UP: if(status){(*index > 0) ? (*index -= 1) : (*index = menu_size - 1);}  break;		
		case DOWN: if(status){(*index < menu_size - 1) ? (*index += 1) : (*index = 0);}  break;
		case LEFT: if(!status){(*index > 0) ? (*index -= 1) : (*index = menu_size - 1);}  break;		
		case RIGHT: if(!status){(*index < menu_size - 1) ? (*index += 1) : (*index = 0);}  break;		 
		case  ENTER: system("color 70"); return ENTER;
		case ESC: system("color 70"); return ESC;
	}
	else
	switch(ch)
	{
		case UP: (*index > 0) ? (*index -= 1) : (*index = menu_size - 1);  break;		
		case DOWN: (*index < menu_size - 1) ? (*index += 1) : (*index = 0);  break;
		case LEFT: (*index > 0) ? (*index -= 1) : (*index = menu_size - 1);  break;		
		case RIGHT: (*index < menu_size - 1) ? (*index += 1) : (*index = 0);  break;		
		case  ENTER: system("color 70"); return ENTER;
		case ESC: system("color 70"); return ESC;
	}
	return 0;
}

/*******************************************
*   ������void CreatRandStr(char *str) 
*	���ܣ��������һ�γ��ַ�������Ϊ���ӱ�ţ� 
*	������1.�ַ���str������ɣ�����Ϊ5λ					
*	���ã���������ʱ���ô˺��� 
*	���ߣ�xxx
*******************************************/ 
void CreatRandStr(char *str)
{
	int a[5];
	srand((unsigned)time(NULL));
	for(int i=0;i<5;i++)
	{
		a[i] = rand() % 10;
	}
	sprintf(str,"%d%d%d%d%d",a[0],a[1],a[2],a[3],a[4]);	
}


/*******************************************
*   ������void EnDecryptFile(char *file, char *secretKey) 
*	���ܣ�������Կ���ܻ�����ļ���ͨ�����ʽ�� 
*	������1.fileΪҪ���ܻ���ܵ��ļ� 2.secretKeyΪһ���ַ���Կ					
*	���ã��ڶ�ȡ�ļ�ǰ���ô˺������н��ܣ���ȡ/д���ļ���������ô˺������м��� 
*	���ߣ�xxx
*******************************************/ 
void EnDecryptFile(char *file, char *secretKey)
{
	FILE *File,*TempFile;
	char buffer[21];  	//�����������ڴ�Ŵ��ļ���ȡ������
	int readCount;  	//ÿ�δ��ļ��ж�ȡ���ֽ���
	int	keyLen = strlen(secretKey);

	if((File = fopen(file, "rb"))==NULL)
	{
		fclose(File);
		File = fopen(file,"wb");
	}		
	if((TempFile = fopen("temp", "wb"))==NULL)
		printf("File open failed!");
	// ���ϵش��ļ��ж�ȡ keyLen ���ȵ����ݣ����浽buffer��ֱ���ļ�����
	while( (readCount=fread(buffer, 1, keyLen, File)) > 0 )
	{		
		for(int i=0; i<readCount; i++)
			buffer[i] ^= secretKey[i];	//��buffer�е��������ֽڽ����������
		fwrite(buffer, 1, readCount, TempFile);
	}	
	fclose(TempFile);fclose(File);
	//ʵ���ļ����Ƹ��ǹ��� 
	char ch;
	TempFile = fopen("temp", "rb");
	File = fopen(file, "wb");
	while(!feof(TempFile))
	{
		fread(&ch,1,1,TempFile);
		fwrite(&ch,1,1,File);
	}
	fclose(TempFile);fclose(File);
	system("del temp");
}


/******************************************* 
*   ������ void GetNowTime(char *now_time) 
*	���ܣ���ȡ��ǰʱ�䣬�����贫��ı���
*	�������ַ���					
*	���ã�����һ���ַ������ѵ�ǰʱ�䰴��һ���ĸ�ʽ������ַ���
*	���ߣ�xxx
*******************************************/ 
void GetNowTime(char *now_time) 
{
    time_t now;
    time(&now);
    struct tm *target_time;
    target_time = localtime(&now);
    char year[5],month[3],day[3],hour[3],min[3];
    
    sprintf(year,"%d",1900 + target_time->tm_year);
    sprintf(month,"%d",target_time->tm_mon+1);
    sprintf(day,"%d",target_time->tm_mday);
    sprintf(hour,"%d",target_time->tm_hour);
    sprintf(min,"%d",target_time->tm_min);
    sprintf(now_time,"%s-%s-%s-%s:%s",year,month,day,hour,min); 
}


/******************************************* 
*   ������ void ChangeUser_Name_Password(char *name_or_password,int status)
*	���ܣ��޸��û����ǳƻ����� 
*	������1.name_or_passwordΪҪ�滻���ַ��� 2.statusΪ1��ʾ�޸��ǳƣ�statusΪ2��ʾ�޸�����					
*	���ã���ChangeUserInfoPage(status)�������� 
*	���ߣ�xxx
*******************************************/ 
void ChangeUser_Name_Password(char *name_or_password,int status)
{
	if(status==0)
		strcpy(User_Info.StudInfo.name,name_or_password);
	if(status==1)
		strcpy(User_Info.StudInfo.password,name_or_password);
	ChangeStudentInfo(User_Info.StudInfo,User_Info.user_seriNum);
}

/******************************************* 
*   ������void ChangeUserInfoPage(int status)
*	���ܣ��޸��û����ǳƻ������ҳ�棬����û�������ַ�����������޸� 
*	������2.statusΪ1��ʾ�޸��ǳƣ�statusΪ2��ʾ�޸�����					
*	���ã��û��޸��ǳƻ�����ʱ���ú��� 
*	���ߣ�xxx
*******************************************/ 
void ChangeUserInfoPage(int status)
{
	system("cls");
	COORD Pos = {21,4};
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Handle_Out,Pos); 
	char *menu[] = {"ȷ��","����"};
	char *str[] = {"�ǳ�","����"};
	char new_str[20]="";
	int index = 0;
	printf("��ȷ���޸�%s��",str[status]);
	while(1)
	{
		for(int i=0;i<2;i++)
		{
			if(i == index)
				SetConsoleTextAttribute(Handle_Out,0x90);  //��ɫ 
			else
				SetConsoleTextAttribute(Handle_Out,0x70); 
			SetCursorPosition(Handle_Out,24+7*i,6);
	    	printf("%s",menu[i]);
		}
		int user_input = GetUserInput(&index , MenuLength(menu) ,0);
		if(user_input == ENTER)
		switch(index)
		{
			case 0: {
						SetCursorPosition(Handle_Out,32,9);
						printf("------------");
						SetCursorPosition(Handle_Out,16,8);
						printf("�������µ�%s��",str[status]);
						Gets(new_str,20);
						//�ж��ַ����ĳ���
						while(strlen(new_str)<3)
						{
							SetCursorPosition(Handle_Out,19,12);
							SetConsoleTextAttribute(Handle_Out,0x74);
							printf("%s���Ȳ���С����λ��",str[status]);
							SetCursorPosition(Handle_Out,32,9);
							SetConsoleTextAttribute(Handle_Out,0x70);
							printf("------------");
							SetCursorPosition(Handle_Out,16,8);
							printf("�������µ�%s��     ",str[status]);
							SetCursorPosition(Handle_Out,32,8);
							Gets(new_str,20);
						} 
						SetCursorPosition(Handle_Out,19,12);
						printf("                    ",str[status]);
						SetCursorPosition(Handle_Out,25,11);
						SetConsoleTextAttribute(Handle_Out,0x90);
						printf("[ ȷ�� ]");
						SetConsoleTextAttribute(Handle_Out,0x70);						
						ChangeUser_Name_Password(new_str,status);
						RedirectPage(status); 
					}	//ȷ��
			case 1: UserMenu_ChangeInfo_Option(); break ;  	//����		
		}
	}		 
}

/******************************************* 
*   ������ void  SetCursorPosition(HANDLE Handle_Out , int x , int y)
*	���ܣ����ù���λ�ã�x,y�� 
*	������xΪ�����꣬yΪ������					
*	���ã����ù��λ��ʱ���ô˺��� 
*	���ߣ�xxx
*******************************************/
void  SetCursorPosition(HANDLE Handle_Out , int x , int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(Handle_Out,Pos);
 } 
 
/******************************************* 
*   ������ void ViewUserInfo(void)
*	���ܣ��鿴�û���Ϣ 
*	��������					
*	���ã���Ҫ�鿴�û���Ϣʱ���ô˺��� 
*	���ߣ�Mxxx
*******************************************/
 void ViewUserInfo(void)
 {
	int user_numbers = Config.user_numbers;
	struct STUDENT_INFO Student[user_numbers];	//	 
	FILE *fp;		
	EnDecryptFile("student_info.dat",myKey);	//�����ļ� 
	fp=fopen("student_info.dat","rb");
    for(int i=0;i<user_numbers;i++)
		fread(&Student[i],sizeof(struct STUDENT_INFO),1,fp);  
   	fclose(fp);  	   	    		
	EnDecryptFile("student_info.dat",myKey);	//�����ļ� 	
			 		
	ShowUserInfo(Student,user_numbers);
 }
 
/******************************************* 
*   ������ void ChangeStudentInfo(struct STUDENT_INFO Student_Info,int seri_num)
*	���ܣ��ı��û���Ϣ 
*	������1.Student_InfoΪҪ����Ľṹ�� 2.seri_numΪ�ýṹ����Student[]�е�����ֵ					
*	���ã���Ҫ�ı��û���Ϣʱ���ô˺��� 
*	���ߣ�xxx
*******************************************/ 
void ChangeStudentInfo(struct STUDENT_INFO Student_Info,int seri_num)
{	
	int user_numbers = Config.user_numbers;	
	struct STUDENT_INFO Student[user_numbers];		 
	FILE *fp;		
	EnDecryptFile("student_info.dat",myKey);	//�����ļ� 
	fp=fopen("student_info.dat","rb");
    for(int i=0;i<user_numbers;i++)
		fread(&Student[i],sizeof(struct STUDENT_INFO),1,fp);  
   	fclose(fp);  
	   	    	
	//�޸��û���Ϣ������һ���ṹ�壬�滻��ԭ���Ľṹ��
	Student[seri_num] = Student_Info;
	fp=fopen("student_info.dat","wb");
	fwrite(&Student,sizeof(struct STUDENT_INFO),user_numbers,fp);
	fclose(fp);	
	EnDecryptFile("student_info.dat",myKey);	//�����ļ� 	 
}
 
/******************************************* 
*   ������ void ShowUserInfo(struct STUDENT_INFO *Student,int user_numbers)
*	���ܣ�չʾ�û���Ϣ,����һ�������û����ݵ�ѡ�� 
*	������1.Student_InfoΪ�ṹ������ 2.user_numbersΪ�û�������				
*	���ã�����Ա�鿴�û���Ϣʱ���ô˺��� 
*	���ߣ�xxx
*******************************************/ 
void ShowUserInfo(struct STUDENT_INFO *Student,int user_numbers)
{	
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE); 
	int index = 0, a = 0;
	char *menu[] = {"[ ���� ]","[ �������� ]"};
	while(1)
	{
		for(int i=0;i<2;i++)
		{
			if(i==index)
				SetConsoleTextAttribute(Handle_Out,0x90);
			else 
				SetConsoleTextAttribute(Handle_Out,0x70);
			SetCursorPosition(Handle_Out,48*i,0);
			printf("%s",menu[i]);
		}			
		SetConsoleTextAttribute(Handle_Out,0x70);				
		SetCursorPosition(Handle_Out,25,1);
		printf("�û���Ϣ");
		SetCursorPosition(Handle_Out,0,3);
		printf("    �������������������������������������������������������������������������������������������������� \n");
		printf("    �� ��ũ�  ����   ��     ѧ��      ��     �ֻ���    �� \n");
		printf("    �������������������������������������������������������������������������������������������������� \n");
		if(user_numbers>12)
			for(int i=a;i<a+12;i++)
				printf("    ��  %.2d �� %-8s��  %-13s��  %-13s�� \n",i+1,Student[i].name,Student[i].studnum,Student[i].phone);
		else
			for(int i=0;i<user_numbers;i++)
				printf("    ��  %.2d �� %-8s��  %-13s��  %-13s�� \n",i+1,Student[i].name,Student[i].studnum,Student[i].phone);
		printf("    �������������������������������������������������������������������������������������������������� \n"); 
		int user_input = getch();	
		switch(user_input)
		{
			case DOWN: a++; if(a>user_numbers-12){a=user_numbers-12;} break;
			case UP: a--; if(a<0){a=0;} break;
			case LEFT: index=0; break;
			case RIGHT: index=1; break;
			case ENTER: index==0?AdminMenu_Option():ExportUserInfo(Student,user_numbers);RedirectPage(5); break;
			case ESC: exit(1); break;
		}
	}
}

/******************************************* 
*   ������ void ExportUserInfo(struct STUDENT_INFO *Student,int user_numbers)
*	���ܣ������û����� 
*	������1.Student_InfoΪ�ṹ������ 2.user_numbersΪ�û�������				
*	���ã�����Ա�鿴�û���Ϣʱ���ô˺������������û�ע�����ݵ����ر�� 
*	���ߣ�xxx
*******************************************/
void ExportUserInfo(struct STUDENT_INFO *Student,int user_numbers)
{
	FILE *fp;
	if((fp = fopen("�����û�����.xls","w"))!=NULL)
	{
		fprintf(fp,"���\t����\tѧ��\t�ֻ���\n");
		for(int i=0;i<user_numbers;i++)
		{
			fprintf(fp,"%d \t %s \t %s \t %s\n",i+1,Student[i].name,Student[i].studnum,Student[i].phone);
		}
		fclose(fp);
	}
	else
		printf("file open fail.\n");
} 
   	
   	
/******************************************* 
*   ������ int ResetUserPassword(char *phone_or_stdnum,int status)
*	���ܣ��鿴ĳ�û��Ƿ���ڣ�����ѡ������������Ϊ�ֻ��� 
*	������1.�ַ���phone_or_stdnumΪ�����ѧ�Ż��ֻ��� 2.user_numbersΪ״̬����				
*	���ã���������ǰ��ѡ����ô˺����ж��û��Ƿ���ڡ���������stetueȡ1ֱ���������룬ȡ0���������� 
*	���ߣ�xxx
*******************************************/
int ResetUserPassword(char *phone_or_stdnum,int status)
{
	int ifSuccess = 0; 
	int user_numbers = Config.user_numbers;
	struct STUDENT_INFO Student[user_numbers];		 
	FILE *fp;			
	//�ж��ļ��Ƿ����,�������򴴽�һ�� 
	if((fp=fopen("student_info.dat","r"))==NULL) 
	{
		fp=fopen("student_info.dat","w");
		fclose(fp);
	} 
	//�����ļ�����ȡ 
	EnDecryptFile("student_info.dat",myKey);	
	fp=fopen("student_info.dat","rb");
    for(int i=0;i<user_numbers;i++)
		fread(&Student[i],sizeof(struct STUDENT_INFO),1,fp);  
   	fclose(fp); 
	//�жϸ��û��Ƿ���� 
	for(int i=0;i<user_numbers;i++)   
	if(!(strcmp(Student[i].phone,phone_or_stdnum) && strcmp(Student[i].studnum,phone_or_stdnum)))
	{
		//��ʾ���û�����,��ô����������Ϊѧ�� 
		ifSuccess = true;
		if(status)
			strcpy(Student[i].password,Student[i].studnum); 
	} 
	//����д���ļ�������	    		 
	fp=fopen("student_info.dat","wb");
   	fwrite(&Student,sizeof(struct STUDENT_INFO),user_numbers,fp);
	fclose(fp);
	EnDecryptFile("student_info.dat",myKey);

	return ifSuccess;	
} 
 
 
/******************************************* 
*   ������ void ResetUserPasswordPage(void)
*	���ܣ�����������ʾҳ�棬��ѡ�����û��������� 
*	��������				
*	���ã�����ԱҪ�����û�����ʱ���ô˺��� �����޸�����ҳ����ã� 
*	���ߣ�xxx
*******************************************/
void ResetUserPasswordPage(void) 
{
	system("cls");
	COORD Pos = {14,2};
	char str[12];
	int index = 0;
	char *menu[] = {"[ȷ��]","[����]"};
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Handle_Out,Pos);
	printf("������Ҫ���õ��û���ѧ�Ż��ֻ��ţ�");
	SetCursorPosition(Handle_Out,20,4);	
	printf(":");	
	SetCursorPosition(Handle_Out,21,5);
	printf("--------------------");	
	SetCursorPosition(Handle_Out,26,6);
	printf("[ ȷ�� ]");	
	SetCursorPosition(Handle_Out,24,4);
	SetConsoleTextAttribute(Handle_Out,0x75);	//��ɫ���� 
	Gets(str,12);
	SetConsoleTextAttribute(Handle_Out,0x90);
	SetCursorPosition(Handle_Out,26,6);
	printf("[ ȷ�� ]");
	SetConsoleTextAttribute(Handle_Out,0x70);
	if(ResetUserPassword(str,0)==true)
	{
		SetCursorPosition(Handle_Out,26,6);
		printf("[ ȷ�� ]");
		SetCursorPosition(Handle_Out,18,8);
		printf("���û����ڣ��Ƿ��������ã�");		
		while(1)
		{
			for(int i=0;i<2;i++)
			{
				if(i == index)
					SetConsoleTextAttribute(Handle_Out,0x90);  //��ɫ 
				else
					SetConsoleTextAttribute(Handle_Out,0x70); 
		    	SetCursorPosition(Handle_Out,22+10*i,10);
		    	printf("%s",menu[i]);
			}
			int user_input = GetUserInput(&index , MenuLength(menu) ,0);
			if(user_input == ENTER)
			{
				if(index==0)
				{
					ResetUserPassword(str,true);
					RedirectPage(6);
				}
				else
					ChangePasswordMenu_Option();
			}
		}
	}
	else
	{
		SetCursorPosition(Handle_Out,26,6);
		printf("[ ȷ�� ]");
		SetCursorPosition(Handle_Out,18,8);
		printf("���û������ڣ��Ƿ��������룿");
		while(1)
		{
			for(int i=0;i<2;i++)
			{
				if(i == index)
					SetConsoleTextAttribute(Handle_Out,0x90);  //��ɫ 
				else
					SetConsoleTextAttribute(Handle_Out,0x70); 
		    	SetCursorPosition(Handle_Out,22+10*i,10);
		    	printf("%s",menu[i]);
			}
			int user_input = GetUserInput(&index , MenuLength(menu),0);
			if(user_input == ENTER)
			{
				if(index==0)
				{
					ResetUserPasswordPage();
				}
				else
					ChangePasswordMenu_Option();
			}
		}
	}
}


//�û�->�ҵ�����->�������ӽ���ѡ�����  *��ʽͬ����* 
void UserMenu_PubPost_Option(int status)
{
	system("cls");	//�����Ļ 
	char time[20];
	char len = strlen(Menu_Title.user_lost_post_menu);
	GetNowTime(time);
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,(WIDTH-len)/2,0);
	if(status==LOST)    
		printf("%s",Menu_Title.user_lost_post_menu);	//��ӡ���� 
	else
		printf("%s",Menu_Title.user_find_post_menu);
	SetCursorPosition(Handle_Out,23,1);
	printf("%s",time);
	
	int y = 0;
	int value = 0;	//���ֶ�Ӧ�ڼ������ 
	int menu_size = MenuLength(user_lost_or_find_post_menu);	//12
	char statusColor = 1;
	struct POST_THING Post_Thing = {1,"","","","","","","","",""};		//�ɼ�
	strcpy(Post_Thing.user_name,User_Info.StudInfo.name);	//����ʱ������Ϊ�û�����
	strcpy(Post_Thing.phone,User_Info.StudInfo.phone);		//����ʱ�ĵ绰Ϊ�û��绰	
	 	
	while(1)
	{	
		UserMenu_PubPost_OptionShow(y,statusColor);	
		int user_input = getch();
		if(user_input==ENTER)
			statusColor = -statusColor;
		UserMenu_PubPost_OptionShow(y,statusColor);	
		SetConsoleTextAttribute(Handle_Out, 0x70); 
		switch(user_input)
		{
			case UP: {
				if(y==0)
					y=11;
				else if(y>=0 && y<4)
					y--;
				else if(y>=4 && y<7)
					y=3;
				else if(y>=7 && y<11)
					y-=3;
				else if(y==11)
					y--;
			} break;
			case DOWN: {
				if(y>=0 && y<4)
					y++;
				else if(y>=4 && y<7)
					y+=3;
				else if(y>=7 && y<10)
					y=10;
				else if(y==10)
					y++;
				else if(y==11)
					y=0;
			} break;
			case LEFT: (y > 0) ? (y--) : (y = 11); break;
			case RIGHT: (y < 11) ? (y++) : (y = 0); break;
			case ESC: exit(1); break;
			case ENTER: {
				statusColor = -statusColor;
				SetCursorPosition(Handle_Out,22+strlen(user_lost_or_find_post_menu[y]),4+y);
				switch(y)
				{
					case 0: Gets(Post_Thing.item_name,20); break ; 	//��Ʒ���� 
					case 1: Gets(Post_Thing.site,20); break ;  	//�ص�
					case 2: Gets(Post_Thing.brief,20); break ;  	//����
					case 3: Gets(Post_Thing.detail,50); break ;  	//��������
					case 10:{
							if(JudgePostInfo(Post_Thing))
							{
								char now_time[20];
								GetNowTime(now_time); 
								strcpy(Post_Thing.time,now_time);
								if(status==LOST){WriteLostInfo(Post_Thing);}
								else {WriteFindInfo(Post_Thing);}
								RedirectPage(7);
							}
					} break;
					
					case 11: ShowUserPost(1,1,0); break;	//���� 
					default: {
						strcpy(Post_Thing.category,category_post_menu[y-4]); 
						SetConsoleTextAttribute(Handle_Out,0x75);
						SetCursorPosition(Handle_Out,32,9); 
						printf("%s",category_post_menu[y-4]);	
					}break;
				}					
			}	 
		}
	}
}

//�������Ӵ���	
void UserMenu_PubPost_OptionShow(int y , int statusColor)
{
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	for(int i=0;i<4;i++)
	{
		if(i == y)
		{
			if(statusColor==1)			
				SetConsoleTextAttribute(Handle_Out,0x90);  //ǳ��ɫ 
			else
				SetConsoleTextAttribute(Handle_Out,0x10);  //��ɫ 			
		} 
		else
			SetConsoleTextAttribute(Handle_Out,0x70); 
		SetCursorPosition(Handle_Out,22,4+i);    
    	printf("%s",user_lost_or_find_post_menu[i]);
	}
	SetConsoleTextAttribute(Handle_Out,0x70);
	SetCursorPosition(Handle_Out,22,9);
	printf("ѡ�����");
	for(int i=4;i<7;i++)
	{
		if(i == y)
			SetConsoleTextAttribute(Handle_Out,0x90);
		else
			SetConsoleTextAttribute(Handle_Out,0x70);
		SetCursorPosition(Handle_Out,18+9*(i-4),10);    
    	printf("%s",user_lost_or_find_post_menu[i]);
	}
	for(int i=7;i<10;i++)
	{
		if(i == y)
			SetConsoleTextAttribute(Handle_Out,0x90);
		else
			SetConsoleTextAttribute(Handle_Out,0x70);
		SetCursorPosition(Handle_Out,18+9*(i-7),11);    
    	printf("%s",user_lost_or_find_post_menu[i]);
	}
	for(int i=10;i<12;i++)
	{
		if(i == y)
			SetConsoleTextAttribute(Handle_Out,0x90);  //��ɫ 
		else
			SetConsoleTextAttribute(Handle_Out,0x70); 
    	SetCursorPosition(Handle_Out,14+25*(i-10),15);
    	printf("%s",user_lost_or_find_post_menu[i]);
	}
}

//��鷢���������Ƿ�淶
int JudgePostInfo(struct POST_THING Post_Thing)
{
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out,0x75);
	SetCursorPosition(Handle_Out,22,13);
	if(!strcmp(Post_Thing.item_name,""))
	{
		printf("����д��Ʒ�����ƣ�");
		return 0;
	} 
	if(!strcmp(Post_Thing.site,""))
	{
		printf("����д��Ʒ�ĵص㣡");
		return 0;
	}		
	if(!strcmp(Post_Thing.brief,""))
	{
		printf("����д��Ʒ��������");
		return 0;
	}		
	if(!strcmp(Post_Thing.category,""))
	{
		printf("��ѡ����Ʒ�����");
		return 0;
	}		
	SetConsoleTextAttribute(Handle_Out,0x70);
	return 1;
} 

//���ʧ����Ϣ	*�ȶ�ȡ��д��
void WriteLostInfo(struct POST_THING Lost_Thing)
{	
	//�������ӵı��   
	char rdnum[5];
	CreatRandStr(rdnum);
	sprintf(Lost_Thing.IDnumber,"S%s%d",rdnum,Post.lost_numbers);
	
	//����������Ϣ 
	Post.lost_numbers++;
	Post.Lost = realloc(Post.Lost,Post.lost_numbers*sizeof(struct POST_THING));
	Post.Lost[Post.lost_numbers-1] = Lost_Thing; 
	//����ү�ľ�Ȼ���ܴ���ԭ���ĵ�ַ����Ҫ��Ū���м�����Ų�����  
	struct POST_THING Lost[Post.lost_numbers];
	for(int i=0;i<Post.lost_numbers;i++)
		Lost[i] = Post.Lost[i];	    	
	FILE *fp;
	fp=fopen("lost_info.dat","wb");
   	fwrite(&Lost,sizeof(struct POST_THING),Post.lost_numbers,fp);
	fclose(fp);
	EnDecryptFile("lost_info.dat",myKey);	//�����ļ� 
			
	//���������ļ� 
	FILE *cg; 
	Config.lost_numbers = Post.lost_numbers;
	cg=fopen("config","wb");
	fwrite(&Config,sizeof(struct CONFIG),1,cg);
	fclose(cg);
	EnDecryptFile("config",myKey);		
} 
 

//���Ѱ����Ϣ	*�ȶ�ȡ��д��
void WriteFindInfo(struct POST_THING Find_Thing)
{
	//�������ӵı��   
	char rdnum[5];
	CreatRandStr(rdnum);
	sprintf(Find_Thing.IDnumber,"X%s%d",rdnum,Post.find_numbers);
	
	//����������Ϣ 
	Post.find_numbers++;
	Post.Find = realloc(Post.Find,Post.find_numbers*sizeof(struct POST_THING));
	Post.Find[Post.find_numbers-1] = Find_Thing;  
	struct POST_THING Find[Post.find_numbers];
	for(int i=0;i<Post.find_numbers;i++)
		Find[i] = Post.Find[i]; 	    	
	FILE *fp;
	fp=fopen("find_info.dat","wb");
   	fwrite(&Find,sizeof(struct POST_THING),Post.find_numbers,fp);
	fclose(fp);
	EnDecryptFile("find_info.dat",myKey);	//�����ļ� 
			
	//���������ļ� 
	FILE *cg;
	Config.find_numbers = Post.find_numbers;
	cg=fopen("config","wb");
	fwrite(&Config,sizeof(struct CONFIG),1,cg);
	fclose(cg);
	EnDecryptFile("config",myKey);		 	
} 
 

//չʾʧ��ǽ/Ѱ��ǽ 
void ShowPostWall(struct POST_THING *TPost, int page , int status , int pos, int aa, int bb)
{
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE); 
	int index = pos , a = aa , b = bb , post_numbers = 0;	//indexΪ���aΪ��ҳЧ����bΪ�����л� /*/a=1
	int menu_size = 9;
	int n = 1;	//n����ĳ�������ӵ����� 
	int flash = 0;	//ˢ��Ϊfalse 
	int post_visible_num = 0;	//�ɼ����ӵ����� 
	char *menu[] = {"[ ���� ]","[ȫ��]","[��Ƭ]","[Կ��]","[����]","[�鱾]","[�·�]","[����]","[ �ҵ� ]"};	
	int cat[6] = {0,0,0,0,0,0};		//ĳһ�����ӵĳ��� 
	(status==LOST)?(post_numbers=Post.lost_numbers):(post_numbers=Post.find_numbers);
	struct POST_THING Post_Cat[6][post_numbers],Post_Visible[post_numbers];	//���������ӷֳ�����   //�ɼ������� 
	for(int i=0;i<post_numbers;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(!strcmp(TPost[i].category,category_post_menu[j]) && (TPost[i].visible==1))
			{
				Post_Cat[j][(cat[j])] = TPost[i];
				cat[j]++;
			}
		}
		if(TPost[i].visible==1)
		{
			Post_Visible[post_visible_num] = TPost[i];
			post_visible_num++;
		}		
	} 
				
	while(1)
	{
		if(flash) 
			system("cls");			 
		for(int i=1;i<8;i++)
		{
			if(i==index)
				SetConsoleTextAttribute(Handle_Out,0x90);
			else 
				SetConsoleTextAttribute(Handle_Out,0x70);
			SetCursorPosition(Handle_Out,3+8*(i-1),3);
			printf("%s",menu[i]);
		}
		if(index==0)
			SetConsoleTextAttribute(Handle_Out,0x90);
		else
			SetConsoleTextAttribute(Handle_Out,0x70);
		SetCursorPosition(Handle_Out,0,0);
		printf("%s",menu[0]);
		if(index==8)
			SetConsoleTextAttribute(Handle_Out,0x90);
		else
			SetConsoleTextAttribute(Handle_Out,0x70);
		SetCursorPosition(Handle_Out,52,0);
		printf("%s",menu[8]);
					
		SetConsoleTextAttribute(Handle_Out,0x70);				
		SetCursorPosition(Handle_Out,27,1);
		if(status==LOST)
			printf("ʧ��ǽ");
		else 
			printf("Ѱ��ǽ");
		SetCursorPosition(Handle_Out,0,4);
		printf(" ----------------------------------------------------------\n");
		SetCursorPosition(Handle_Out,0,5);
		printf(" ���   ����       ���\t\t        �ص�\n");
		printf(" ----------------------------------------------------------\n");	
		
		for(int i=2;i<8;i++)
		if(i==index)
		{
			if(cat[i-2]>12)
			{
				if(a>12)
				for(int k=a-12;k<a;k++)
					printf("  %.2d    %-10s%-20s  %-15s\n",k+1,Post_Cat[i-2][k].item_name,Post_Cat[i-2][k].brief,Post_Cat[i-2][k].site);							
				else
				for(int k=0;k<12;k++)
					printf("  %.2d    %-10s%-20s  %-15s\n",k+1,Post_Cat[i-2][k].item_name,Post_Cat[i-2][k].brief,Post_Cat[i-2][k].site);					
			}
			else
			for(int k=0;k<cat[i-2];k++)
				printf("  %.2d    %-10s%-20s  %-15s\n",k+1,Post_Cat[i-2][k].item_name,Post_Cat[i-2][k].brief,Post_Cat[i-2][k].site);	
			int max = cat[i-2];
			if(max>12) {max=12;}
			for(int i=0;i<max;i++)
			{
				if(i==b)
					SetConsoleTextAttribute(Handle_Out,0x90);	//��ɫ 
				else
					SetConsoleTextAttribute(Handle_Out,0x70);	//��ɫ
				SetCursorPosition(Handle_Out,54,7+i);
				printf("[����]"); 
				if(b>=12)
				{
					SetConsoleTextAttribute(Handle_Out,0x90);
					SetCursorPosition(Handle_Out,54,7+11);
					printf("[����]");
				}
			}
			n = cat[i-2];
		}
		
		if(index==1)
		{
			//չʾ���пɼ����� 
			if(post_visible_num>12)
			{
				if(a>12)
				for(int i=a-12;i<a;i++)
					printf("  %.2d    %-10s%-20s  %-15s\n",i+1,Post_Visible[i].item_name,Post_Visible[i].brief,Post_Visible[i].site); 							
				else
				for(int i=0;i<12;i++)
					printf("  %.2d    %-10s%-20s  %-15s\n",i+1,Post_Visible[i].item_name,Post_Visible[i].brief,Post_Visible[i].site);			
			}
			else
			for(int i=0;i<post_visible_num;i++)
				printf("  %.2d    %-10s%-20s  %-15s\n",i+1,Post_Visible[i].item_name,Post_Visible[i].brief,Post_Visible[i].site);
			int max = post_visible_num;
			if(max>12) {max=12;}
			for(int i=0;i<max;i++)
			{
				if(i==b)
					SetConsoleTextAttribute(Handle_Out,0x90);	//��ɫ 
				else
					SetConsoleTextAttribute(Handle_Out,0x70);	//��ɫ
				SetCursorPosition(Handle_Out,54,7+i);
				printf("[����]"); 
				if(b>=12)
				{
					SetConsoleTextAttribute(Handle_Out,0x90);
					SetCursorPosition(Handle_Out,54,7+11);
					printf("[����]");
				}
			}
			n = post_visible_num; 
		}
					
		SetConsoleTextAttribute(Handle_Out,0x70);		
		int user_input = getch();	
		switch(user_input)
		{
			case DOWN: {
				a++;
				b++; 
				if(a>n){a=n;}
				if(b>n-1){b=n-1;}
				flash = 0;	//�����¼�ʱ��ˢ������ 
			} break;
			case UP: {
				a--;
				b--; 
				if(a<1){a=1;}
				if(b<0){b=0;}
				flash = 0;
			} break;
			case LEFT: {
				if(index>0&&index<8) {index--;}					
				else if(index==0) {index=1;}					
				else if(index==8) {index=0;}
				b = 0;	//ʹ����л�ʱ��������ڵ�һ��	
				a = 1;	//�л�ʱa����>=0��ֹ����ֵ���ָ����� 
				flash = 1;	//�����Ҽ�ʱˢ��							
			} break;
			case RIGHT: {
				if(index>0&&index<8) {index++;}					
				else if(index==0) {index=8;}					
				else if(index==8) {index=7;}
				b = 0;	
				a = 1;
				flash = 1;							
			} break;
			case ESC: exit(1); break;
			case ENTER: {
					if(index==0) {JudgePage(page);}
					else if(index==8) 
					{
						if(JudgeIsSignin(page)) 
							ShowUserPost(1,1,0);
						else
							ShowPostWall(TPost, page, status, pos, a, b);	//����ԭ������ 
					}
					else if(index==1 && n!=0) {PostDetailPage(Post_Visible[b], page ,status , index, a, b);}
					else if(index>1&&index<8 && cat[index-2]!=0) {PostDetailPage(Post_Cat[index-2][b], page ,status , index, a, b);}	
			} break;
		}
	}
}

//չʾ��������ҳ�� 
void PostDetailPage(struct POST_THING Post_Thing , int page , int status , int pos, int a, int b)
{
	system("cls");	//�����Ļ 
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	int index = 0;
	char *menu[]={"[��������]","[ ���� ]"}; 
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,24,0);
	printf("��������ҳ��");
	
	//��Ʒ���� 
	SetCursorPosition(Handle_Out,20,3);
	printf("���ƣ�%s",Post_Thing.item_name);
	//��Ʒ��� 
	SetCursorPosition(Handle_Out,20,4);
	printf("��ţ�%s",Post_Thing.IDnumber);
	//����ص�	
	SetCursorPosition(Handle_Out,20,5);
	printf("���ڵص㣺%s",Post_Thing.site);
	//���
	SetCursorPosition(Handle_Out,20,6);
	printf("��Ҫ���ܣ�%s",Post_Thing.brief);
	//��������
	SetCursorPosition(Handle_Out,20,7);
	printf("����������%s",Post_Thing.detail);  
	SetCursorPosition(Handle_Out,10,9);
	printf("----------------------------------------");
	//����ʱ�� 
	SetCursorPosition(Handle_Out,20,10);
	printf("ʱ�䣺%s",Post_Thing.time);
	//ӵ����
	SetCursorPosition(Handle_Out,20,11);
	printf("�����ߣ�%s",Post_Thing.user_name);
	//��ϵ��ʽ
	SetCursorPosition(Handle_Out,20,12);
	printf("��ϵ��ʽ��%s",Post_Thing.phone); 
		
	while(1)
	{
		for(int i=0;i<2;i++)
		{
			if(i==index)
				SetConsoleTextAttribute(Handle_Out, 0x90); 
			else
				SetConsoleTextAttribute(Handle_Out, 0x70); 
			SetCursorPosition(Handle_Out,12+28*i,16);
			printf("%s",menu[i]);
		}
		int user_input = GetUserInput(&index,2,0);
		if(user_input==ESC)
			exit(1);
		if(user_input==ENTER)
		{
			//ȷ������ 
			if(index==0)
			{
				if(JudgeIsSignin(page))
					LeaveWord(Post_Thing, page, status, pos, a, b);
				else
					PostDetailPage(Post_Thing, page, status, pos, a, b);	//��Ϊ��¼��Ҳ����¼�򷵻�ԭ����ҳ��					
			} 
			else
			{
				if(status==LOST)
					ShowPostWall(Post.Lost, page, LOST, pos, a, b);
				else 
					ShowPostWall(Post.Find, page, FIND, pos, a, b);
			}				
		}
	}	
}

//ֻ���û����ܲ鿴�ҵ����� 
void ShowUserPost(int pos, int aa, int bb)
{		
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE); 
	int index = pos , a = aa , b = bb;	//indexΪ���aΪ��ҳЧ����bΪ�����л� 
	int menu_size = 7;
	int flash=0;	//ˢ������ 
	int n = 1;	//n����ĳ�������ӵ����� 
	char *menu[] = {"[ ���� ]","[ʧ����]","[Ѱ����]","[������]","[��������]"};
	char *pubPost[] = {"[����Ѱ������]","[����ʧ������]"}; 
	int max=0;
	(Post.lost_numbers>Post.find_numbers) ? (max=Post.lost_numbers) : (max=Post.find_numbers);
	struct POST_THING Post_Cat[3][Post.lost_numbers+Post.find_numbers];	//ĳ����ɾ���������ܲ����ڱ���������������� 
	int cat[3] = {0,0};		//���ӵĳ��� 
	for(int i=0;i<Post.lost_numbers;i++)
	{
		if(!strcmp(Post.Lost[i].phone,User_Info.StudInfo.phone) && (Post.Lost[i].visible==1))
		{
			Post_Cat[0][(cat[0])] = Post.Lost[i];
			cat[0]++;
		}
		else if(!strcmp(Post.Lost[i].phone,User_Info.StudInfo.phone) && (Post.Lost[i].visible==0))
		{
			Post_Cat[2][(cat[2])] = Post.Lost[i];
			cat[2]++;
		}
	} 
	
	for(int i=0;i<Post.find_numbers;i++)
	{
		if(!strcmp(Post.Find[i].phone,User_Info.StudInfo.phone) && (Post.Find[i].visible==1))
		{
			Post_Cat[1][(cat[1])] = Post.Find[i];
			cat[1]++;
		}
		else if(!strcmp(Post.Find[i].phone,User_Info.StudInfo.phone) && (Post.Find[i].visible==0))
		{
			Post_Cat[2][(cat[2])] = Post.Find[i];
			cat[2]++;
		}
	} 
					
	while(1)
	{
		if(flash) 
			system("cls");				 
		for(int i=0;i<5;i++)
		{
			if(i==index)
				SetConsoleTextAttribute(Handle_Out,0x90);
			else 
				SetConsoleTextAttribute(Handle_Out,0x70);
			SetCursorPosition(Handle_Out,3+11*i,2);
			printf("%s",menu[i]);
		}
		for(int i=0;i<2;i++)
		{
			if(i==(index-5))
				SetConsoleTextAttribute(Handle_Out,0x90);
			else 
				SetConsoleTextAttribute(Handle_Out,0xb0);
			SetCursorPosition(Handle_Out,46*(1-i),0);
			printf("%s",pubPost[i]);		
		}					
		SetConsoleTextAttribute(Handle_Out,0x70);				
		SetCursorPosition(Handle_Out,26,0);
		printf("�ҵ�����");
		SetCursorPosition(Handle_Out,0,3);
		printf(" ----------------------------------------------------------\n");
		SetCursorPosition(Handle_Out,0,4);
		printf(" ���   ����       ���\t\t        �ص�\n");
		printf(" ----------------------------------------------------------\n");	
						
		for(int i=1;i<4;i++)
		if(i==index) 
		{
			if(cat[i-1]>13)
			{
				if(a>13)
				for(int k=a-13;k<a;k++)
					printf("  %.2d    %-10s%-20s  %-15s\n",k+1,Post_Cat[i-1][k].item_name,Post_Cat[i-1][k].brief,Post_Cat[i-1][k].site);							
				else
				for(int k=0;k<13;k++)
					printf("  %.2d    %-10s%-20s  %-15s\n",k+1,Post_Cat[i-1][k].item_name,Post_Cat[i-1][k].brief,Post_Cat[i-1][k].site);					
			}
			else
			for(int k=0;k<cat[i-1];k++)
				printf("  %.2d    %-10s%-20s  %-15s\n",k+1,Post_Cat[i-1][k].item_name,Post_Cat[i-1][k].brief,Post_Cat[i-1][k].site);	
			int max = cat[i-1];
			if(max>13) {max=13;}
			for(int j=0;j<max;j++)
			{
				if(j==b)
					SetConsoleTextAttribute(Handle_Out,0x90);	//��ɫ 
				else
					SetConsoleTextAttribute(Handle_Out,0x70);	//��ɫ
				SetCursorPosition(Handle_Out,54,6+j);
				if(i==3){
					SetConsoleTextAttribute(Handle_Out,0x70);
					if(pos==1)
						printf("[ʧ��]");
					else
						printf("[Ѱ��]"); 
				}
				else 
					printf("[�鿴]"); 
				if(b>=13)
				{
					SetConsoleTextAttribute(Handle_Out,0x90);
					SetCursorPosition(Handle_Out,54,6+12);
					if(i==3){					
						SetConsoleTextAttribute(Handle_Out,0x70);
						if(pos==1)
							printf("[ʧ��]");
						else
							printf("[Ѱ��]"); 
					}
					else 
						printf("[�鿴]"); 
				}
			}
			n = cat[i-1];
		}
					
		SetConsoleTextAttribute(Handle_Out,0x70);		
		int user_input = getch();	
		switch(user_input)
		{
			case DOWN: {
				a++;
				b++; 
				if(a>n){a=n;}
				if(b>n-1){b=n-1;}
				flash=0;
				if(index==6) {index=0;}
				if(index==5) {index=4;}
			} break;				
			case UP: {
				a--;
				b--; 
				if(a<1){a=1;}
				if(b<0){b=0;}
				flash=0;
				if(index==0) {index=6;}
				if(index==4) {index=5;}
			} break;			
			case LEFT:{
				if(index>0 && index<=4) index--;
				else if(index==0) {index=4;}
				else if(index==5) {index=6;}
				else if(index==6) {index=5;}
				b=0; a=1; 
				flash=1;
				break;
			} 
			case RIGHT:{
				if(index>=0 && index<4) index++;
				else if(index==4) {index=0;}
				else if(index==5) {index=6;}
				else if(index==6) {index=5;}
				b=0; a=1; 
				flash=1;
				break;
			}
			case ESC: exit(1); break;
			case ENTER: {
					if(index==0) {UserMenu_Option();}					
					else if(index==1 && cat[index-1]!=0) {ViewMyPostPage(Post_Cat[index-1][b], index, a, b);}	//ϣ���ṹ������ĵ�ַû�б��ͷŵ��� 
					else if(index==2 && cat[index-1]!=0) {ViewMyPostPage(Post_Cat[index-1][b], index, a, b);}
					else if(index==3) {;} //�ѽ��������� 
					else if(index==4) {
					ExportMyPostInfo(Post_Cat[0],cat[0],"ʧ��", "w");
					ExportMyPostInfo(Post_Cat[1],cat[1],"Ѱ��", "a");
					ExportMyPostInfo(Post_Cat[2],cat[2],"�ѽ���","a");
					RedirectPage(10);
					}
					else if(index==5) {UserMenu_PubPost_Option(FIND);}
					else if(index==6) {UserMenu_PubPost_Option(LOST);}		
			} break;
		}
	}
}

//�鿴�ҵ����� 
void ViewMyPostPage(struct POST_THING Post_Thing, int pos, int a, int b)
{
	system("cls");	//�����Ļ 
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	int index = 0;
	char *menu[]={"[�޸�����]","[ ���� ]","[ɾ������]"}; 
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,24,0);
	printf("��������ҳ��");
	
	//��Ʒ���� 
	SetCursorPosition(Handle_Out,20,3);
	printf("���ƣ�%s",Post_Thing.item_name);
	//��Ʒ��� 
	SetCursorPosition(Handle_Out,20,4);
	printf("��ţ�%s",Post_Thing.IDnumber);
	//���ڵص�
	SetCursorPosition(Handle_Out,20,5);
	printf("���ڵص㣺%s",Post_Thing.site);
	//���
	SetCursorPosition(Handle_Out,20,6);
	printf("��Ҫ���ܣ�%s",Post_Thing.brief);
	//��������
	SetCursorPosition(Handle_Out,20,7);
	printf("����������%s",Post_Thing.detail);  
	SetCursorPosition(Handle_Out,10,9);
	printf("----------------------------------------");
	//����ʱ�� 
	SetCursorPosition(Handle_Out,20,10);
	printf("ʱ�䣺%s",Post_Thing.time);
	//ӵ����
	SetCursorPosition(Handle_Out,20,11);
	printf("�����ߣ�%s",Post_Thing.user_name);
	//��ϵ��ʽ
	SetCursorPosition(Handle_Out,20,12);
	printf("��ϵ��ʽ��%s",Post_Thing.phone); 
		
	while(1)
	{
		for(int i=0;i<3;i++)
		{
			if(i==index)
				SetConsoleTextAttribute(Handle_Out, 0x90); 
			else
				SetConsoleTextAttribute(Handle_Out, 0x70); 
			SetCursorPosition(Handle_Out,6+(i)*(21-i),16);	//a[n]=a[1]+S[n-1] , a[n+1]-a[n]=b[n],s[n]Ϊb[n]����͹�ʽ 
			printf("%s",menu[i]);
		}
		int user_input = GetUserInput(&index,3,0);
		if(user_input==ESC)
			exit(1);
		if(user_input==ENTER)
		{
			if(index==0)
				ChangeMyPost(Post_Thing, pos, a, b);	//�޸����� 
			else if(index==1)
				ShowUserPost(pos,a,b);	//���� 
			else
				DeleteMyPost(Post_Thing, pos, a, b);	//ɾ������ 
		}
	}	
}

//�޸��ҵ����� 
void ChangeMyPost(struct POST_THING Post_Thing, int pos, int a, int b)
{	
	FILE *fp;
	int k=0,post_numbers=0;	
	//�鿴�����ڽṹ�������е�λ��	//�Ƚϱ�źͷ���ʱ�� 
	(pos==1)?(post_numbers=Post.lost_numbers):(post_numbers=Post.find_numbers);
	struct POST_THING TPost[post_numbers];
	if(pos==1)
	for(int i=0;i<Post.lost_numbers;i++)
	{
		TPost[i] = Post.Lost[i]; 
		if(!(strcmp(TPost[i].IDnumber,Post_Thing.IDnumber) || strcmp(TPost[i].time,Post_Thing.time)))
			k = i;
	}
	else
	for(int i=0;i<Post.find_numbers;i++)
	{
		TPost[i] = Post.Find[i];
		if(!(strcmp(TPost[i].IDnumber,Post_Thing.IDnumber) || strcmp(TPost[i].time,Post_Thing.time)))
			k = i;
	}
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x70);
	SetCursorPosition(Handle_Out,24,0);
	printf("���޸����ӣ�");
	SetCursorPosition(Handle_Out,17,1);
	SetConsoleTextAttribute(Handle_Out, 0x7D);
	printf("(������Ҫ�޸ĵĵط���������)");	//��ɫ 
	SetConsoleTextAttribute(Handle_Out, 0x70);
	int index = 0;
	int menu_size = 6;
	char statusColor = 1;
	char *menu[] = {"���ƣ�","���ڵص㣺","��Ҫ���ܣ�","����������","[����޸�]","[ ���� ]"};
	
	SetCursorPosition(Handle_Out,26,4);    
    printf("--------------------");
    SetCursorPosition(Handle_Out,30,6);    
    printf("----------------");
    SetCursorPosition(Handle_Out,30,8);    
    printf("----------------");
    SetCursorPosition(Handle_Out,30,10);    
    printf("----------------------------\n\n");
    printf("------------------------------------------------------------");
	while(1)
	{
		SetCursorPosition(Handle_Out,17,1);
		SetConsoleTextAttribute(Handle_Out, 0x7D);
		printf("(������Ҫ�޸ĵĵط���������)");	//��ɫ 
		SetConsoleTextAttribute(Handle_Out, 0x70);
		for(int i=0;i<4;i++)
		{
			if(i == index)
			{
				if(statusColor==1)			
					SetConsoleTextAttribute(Handle_Out,0x90);  //ǳ��ɫ 
				else
					SetConsoleTextAttribute(Handle_Out,0x10);  //��ɫ 			
			} 
			else
				SetConsoleTextAttribute(Handle_Out,0x70); 
			SetCursorPosition(Handle_Out,20,3+2*i);    
	    	printf("%s",menu[i]);
		}
		for(int i=4;i<menu_size;i++)
		{
			if(i==index)
				SetConsoleTextAttribute(Handle_Out,0x90);
			else
				SetConsoleTextAttribute(Handle_Out,0x70);
			SetCursorPosition(Handle_Out,12+28*(i-4),15);    
	    	printf("%s",menu[i]);
		}
		int user_input = GetUserInput(&index,menu_size,2);
		if(user_input==ENTER)
			statusColor = -statusColor;
		
		for(int i=0;i<4;i++)
		{
			if(i == index)
			{
				if(statusColor==1)			
					SetConsoleTextAttribute(Handle_Out,0x90);  //ǳ��ɫ 
				else
					SetConsoleTextAttribute(Handle_Out,0x10);  //��ɫ 			
			} 
			else
				SetConsoleTextAttribute(Handle_Out,0x70); 
			SetCursorPosition(Handle_Out,20,3+2*i);    
	    	printf("%s",menu[i]);
		}
		SetCursorPosition(Handle_Out,17,1);
		SetConsoleTextAttribute(Handle_Out, 0x7D);
		printf("(������Ҫ�޸ĵĵط���������)");	//��ɫ 
		SetConsoleTextAttribute(Handle_Out,0x70);		
		if(user_input==ENTER)
		{
			statusColor = -statusColor;
			SetCursorPosition(Handle_Out,20+strlen(menu[index]),3+index*2);
			switch(index)
			{
				case 0:	Gets(Post_Thing.item_name,20); break;	//���� 
				case 1:	Gets(Post_Thing.site,20); break;	//���ڵص� 
				case 2:	Gets(Post_Thing.brief,20); break;	//��Ҫ����	
				case 3:	Gets(Post_Thing.detail,50); break;//�������� 
				case 4:	{
					//�޸ĺ����Ϣ����Ϊ�ջ�ո�2���� 
					if(!(strcmp(Post_Thing.item_name,"") && strcmp(Post_Thing.item_name," ") && strcmp(Post_Thing.item_name,"  ")))
						strcpy(Post_Thing.item_name,TPost[k].item_name);
						
					if(!(strcmp(Post_Thing.site,"") && strcmp(Post_Thing.site," ") && strcmp(Post_Thing.site,"  ")))
						strcpy(Post_Thing.site,TPost[k].site);
						
					if(!(strcmp(Post_Thing.brief,"") && strcmp(Post_Thing.brief," ") && strcmp(Post_Thing.brief,"  ")))
						strcpy(Post_Thing.brief,TPost[k].brief);
					
					if(!(strcmp(Post_Thing.detail,"") && strcmp(Post_Thing.detail," ") && strcmp(Post_Thing.detail,"  ")))
						strcpy(Post_Thing.detail,TPost[k].detail);
						
					TPost[k]=Post_Thing;
					FILE *fp;
					if(pos==1)
					{
						fp=fopen("lost_info.dat","wb");
						Post.Lost[k] = Post_Thing; 
						fwrite(&TPost,sizeof(struct POST_THING),post_numbers,fp);
						fclose(fp);
						EnDecryptFile("lost_info.dat",myKey);
					} 
					else 
					{
						fp=fopen("find_info.dat","wb");
						Post.Find[k] = Post_Thing;
						fwrite(&TPost,sizeof(struct POST_THING),post_numbers,fp);
						fclose(fp);
						EnDecryptFile("find_info.dat",myKey);
					}							 
					RedirectPage(8);					 					
				}break; 
				case 5:	ViewMyPostPage(TPost[k], pos, a, b); break;	//���� 
			}
		}				
	}	
}

//ɾ������ 
void DeleteMyPost(struct POST_THING Post_Thing, int pos, int a, int b)
{
	FILE *fp;
	int k=0,post_numbers=0;	
	//�鿴�����ڽṹ�������е�λ��	//�Ƚϱ�źͷ���ʱ�� 
	(pos==1)?(post_numbers=Post.lost_numbers):(post_numbers=Post.find_numbers);
	struct POST_THING TPost[post_numbers];
	if(pos==1)
	for(int i=0;i<Post.lost_numbers;i++)
	{
		TPost[i] = Post.Lost[i]; 
		if(!(strcmp(TPost[i].IDnumber,Post_Thing.IDnumber) || strcmp(TPost[i].time,Post_Thing.time)))
			k = i;
	}
	else
	for(int i=0;i<Post.find_numbers;i++)
	{
		TPost[i] = Post.Find[i];
		if(!(strcmp(TPost[i].IDnumber,Post_Thing.IDnumber) || strcmp(TPost[i].time,Post_Thing.time)))
			k = i;
	}
	
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x74);
	SetCursorPosition(Handle_Out,21,4);
	printf("��ȷ��ɾ��������");
	SetConsoleTextAttribute(Handle_Out, 0x70);
	SetCursorPosition(Handle_Out,21,7);
	int index = 0;
	char *menu[] = {"[ ȷ�� ]","[ ȡ�� ]"};
	while(1)
	{
		for(int i=0;i<2;i++)
		{
			if(i==index)
				SetConsoleTextAttribute(Handle_Out, 0x90);
			else
				SetConsoleTextAttribute(Handle_Out, 0x70);
			SetCursorPosition(Handle_Out,17+18*i,7);
			printf("%s",menu[i]);
		}
		SetConsoleTextAttribute(Handle_Out, 0x70);
		int user_input = GetUserInput(&index,2,0);
		if(user_input==ENTER)
		{
			if(index==0)
			{
				TPost[k].visible = 0;
				FILE *fp;
				if(pos==1)
				{
					fp=fopen("lost_info.dat","wb");
					Post.Lost[k].visible = 0; 
					fwrite(&TPost,sizeof(struct POST_THING),post_numbers,fp);
					fclose(fp);
					EnDecryptFile("lost_info.dat",myKey);
				} 
				else 
				{
					fp=fopen("find_info.dat","wb");
					Post.Find[k].visible = 0;
					fwrite(&TPost,sizeof(struct POST_THING),post_numbers,fp);
					fclose(fp);
					EnDecryptFile("find_info.dat",myKey);
				} 
				RedirectPage(9);
			}
			else
				ViewMyPostPage(Post_Thing, pos, a, b);	
		}		
	}	
} 

//����û����ӵ���Ϣ������� 
void ExportMyPostInfo(struct POST_THING *Post, int post_numbers, char *cat, char *rw_mode)
{
	char file[30];
	sprintf(file,"%s��������Ϣ.xls",User_Info.StudInfo.name);
	FILE *fp;
	if((fp = fopen(file,rw_mode))!=NULL)
	{
		fprintf(fp,"%s\n",cat);
		fprintf(fp,"���\t����\t���\t�ص�\t���\t��������\t����ʱ��\t�ɼ�\n");
		for(int i=0;i<post_numbers;i++)
		{
			fprintf(fp,"%d\t %s\t %s\t %s\t %s\t %s\t %s\t %d\n",i+1,Post[i].item_name, Post[i].category, Post[i].site, Post[i].brief, Post[i].detail, Post[i].time, Post[i].visible);
		}
		fprintf(fp,"\n\n");
		fclose(fp);
	}
	else
		printf("file open fail.\n");
} 
 
//�ж��û��Ƿ��ѵ�¼ 
int JudgeIsSignin(int page) 
{
	if(page==Page.user_menu)
		return 1;
	
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetCursorPosition(Handle_Out,17,4);
	printf("����δ��¼���Ƿ�������¼��");
	SetConsoleTextAttribute(Handle_Out, 0x70);
	SetCursorPosition(Handle_Out,21,7);
	int index = 0;
	char *menu[] = {"[ ȷ�� ]","[ ȡ�� ]"};
	while(1)
	{
		for(int i=0;i<2;i++)
		{
			if(i==index)
				SetConsoleTextAttribute(Handle_Out, 0x90);
			else
				SetConsoleTextAttribute(Handle_Out, 0x70);
			SetCursorPosition(Handle_Out,17+18*i,7);
			printf("%s",menu[i]);
		}
		SetConsoleTextAttribute(Handle_Out, 0x70);
		int user_input = GetUserInput(&index,2,0);
		if(user_input==ENTER)
		{
			if(index==0)
				SignInMenu_Option();	//ǰ����¼ҳ��
			else
				return 0;
		}	 
	}
	return 0;
} 
	

//չʾ�ѽ��������� 
void ShowOverPost(int pos, int aa, int bb)
{		
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE); 
	int index = pos , a = aa , b = bb;	//aΪ��ҳЧ����bΪ�����л� 
	int menu_size = 4;
	int flash=0;	//ˢ������ 
	int n = 1;	//n����ĳ�������ӵ����� 
	char *menu[] = {"[ ���� ]","[ ʧ���� ]","[ Ѱ���� ]","[��������]"};
	int max=0;
	(Post.lost_numbers>Post.find_numbers) ? (max=Post.lost_numbers) : (max=Post.find_numbers);
	struct POST_THING Post_Cat[2][max];	//ĳ����ɾ���������ܲ����ڱ���������������� 
	int cat[2] = {0,0};		//���ӵĳ��� 
	for(int i=0;i<Post.lost_numbers;i++)
	if(Post.Lost[i].visible==0)
	{
		Post_Cat[0][(cat[0])] = Post.Lost[i];
		cat[0]++;
	}	
	for(int i=0;i<Post.find_numbers;i++)
	if(Post.Find[i].visible==0)
	{
		Post_Cat[1][(cat[1])] = Post.Find[i];
		cat[1]++;
	}

	while(1)
	{
		if(flash) 
			system("cls");			 
		for(int i=0;i<4;i++)
		{
			if(i==index)
				SetConsoleTextAttribute(Handle_Out,0x90);
			else 
				SetConsoleTextAttribute(Handle_Out,0x70);
			SetCursorPosition(Handle_Out,5+14*i,2);
			printf("%s",menu[i]);
		}					
		SetConsoleTextAttribute(Handle_Out,0x70);				
		SetCursorPosition(Handle_Out,22,0);
		printf("�ѽ������׵�����");
		SetCursorPosition(Handle_Out,0,3);
		printf(" ----------------------------------------------------------\n");
		SetCursorPosition(Handle_Out,0,4);
		printf(" ���   ����       ���\t\t        �ص�\n");
		printf(" ----------------------------------------------------------\n");	
						
		for(int i=1;i<3;i++)
		if(i==index) {
			if(cat[i-1]>13)
			{
				if(a>13)
				for(int k=a-13;k<a;k++)
					printf("  %.2d    %-10s%-20s  %-15s\n",k+1,Post_Cat[i-1][k].item_name,Post_Cat[i-1][k].brief,Post_Cat[i-1][k].site);							
				else
				for(int k=0;k<13;k++)
					printf("  %.2d    %-10s%-20s  %-15s\n",k+1,Post_Cat[i-1][k].item_name,Post_Cat[i-1][k].brief,Post_Cat[i-1][k].site);					
			}
			else
			for(int k=0;k<cat[i-1];k++)
				printf("  %.2d    %-10s%-20s  %-15s\n",k+1,Post_Cat[i-1][k].item_name,Post_Cat[i-1][k].brief,Post_Cat[i-1][k].site);	
			int max = cat[i-1];
			if(max>13) {max=13;}
			for(int j=0;j<max;j++)
			{
				if(j==b)
					SetConsoleTextAttribute(Handle_Out,0x90);	//��ɫ 
				else
					SetConsoleTextAttribute(Handle_Out,0x70);	//��ɫ
				SetCursorPosition(Handle_Out,54,6+j);
				printf("[�鿴]"); 
				if(b>=13)
				{
					SetConsoleTextAttribute(Handle_Out,0x90);
					SetCursorPosition(Handle_Out,54,6+12);
					printf("[�鿴]"); 
				}
			}
			n = cat[i-1];
		}
					
		SetConsoleTextAttribute(Handle_Out,0x70);		
		int user_input = getch();	
		switch(user_input)
		{
			case DOWN: {
				a++;
				b++; 
				if(a>n){a=n;}
				if(b>n-1){b=n-1;}
				flash=0;
			} break;
			case UP: {
				a--;
				b--; 
				if(a<1){a=1;}
				if(b<0){b=0;}
				flash=0;
			} break;
			case LEFT: (index > 0) ? (index--) : (index = menu_size-1); b = 0;flash=1; break; 
			case RIGHT: (index < menu_size-1) ? (index++) : (index = 0); b = 0;flash=1; break; 
			case ESC: exit(1); break;
			case ENTER: {
					if(index==0) {AdminMenu_Option();}					
					else if(index==1 && cat[index-1]!=0) {ViewOverPostPage(Post_Cat[index-1][b], index, a, b);}	//ϣ���ṹ������ĵ�ַû�б��ͷŵ��� 
					else if(index==2 && cat[index-1]!=0) {ViewOverPostPage(Post_Cat[index-1][b], index, a, b);}
					else if(index==3) {
					char *str = User_Info.StudInfo.name;
					strcpy(User_Info.StudInfo.name,"�ѽ�����"); 
					ExportMyPostInfo(Post_Cat[0],cat[0],"ʧ��", "w");
					ExportMyPostInfo(Post_Cat[1],cat[1],"Ѱ��", "a");
					strcpy(User_Info.StudInfo.name,str);
					RedirectPage(11);
					}		
			} break;
		}
	}	
}

//�鿴�ѽ��������� 
void ViewOverPostPage(struct POST_THING Post_Thing, int pos, int a, int b)
{
	system("cls");	//�����Ļ 
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	int index = 0;
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,24,0);
	printf("��������ҳ��");
	
	//��Ʒ���� 
	SetCursorPosition(Handle_Out,20,3);
	printf("���ƣ�%s",Post_Thing.item_name);
	//��Ʒ��� 
	SetCursorPosition(Handle_Out,20,4);
	printf("��ţ�%s",Post_Thing.IDnumber);
	//���ڵص�
	SetCursorPosition(Handle_Out,20,5);
	printf("���ڵص㣺%s",Post_Thing.site);
	//���
	SetCursorPosition(Handle_Out,20,6);
	printf("��Ҫ���ܣ�%s",Post_Thing.brief);
	//��������
	SetCursorPosition(Handle_Out,20,7);
	printf("����������%s",Post_Thing.detail);  
	SetCursorPosition(Handle_Out,10,9);
	printf("----------------------------------------");
	//����ʱ�� 
	SetCursorPosition(Handle_Out,20,11);
	printf("ʱ�䣺%s",Post_Thing.time);
	//ӵ����
	SetCursorPosition(Handle_Out,20,12);
	printf("�����ߣ�%s",Post_Thing.user_name);
	//��ϵ��ʽ
	SetCursorPosition(Handle_Out,20,13);
	printf("��ϵ��ʽ��%s",Post_Thing.phone); 
	
	SetConsoleTextAttribute(Handle_Out, 0x90);
	SetCursorPosition(Handle_Out,27,16);
	printf("[ ���� ]");
	int user_input = getch();
	while(user_input!=ENTER);
	SetConsoleTextAttribute(Handle_Out, 0x70);
	SetCursorPosition(Handle_Out,27,16);
	printf("[ ���� ]");
	ShowOverPost(1, a, b);	
}

//���Ե�ҳ�� 
void LeaveWord(struct POST_THING Post_Thing , int page , int status , int pos ,int a, int b)
{
	system("cls");
	char time[20];
	GetNowTime(time);
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,26,0);    
	printf("��������");	//��ӡ���� 
	SetCursorPosition(Handle_Out,23,1);
	printf("%s",time);			//��ӡʱ�� 
	int statusColor=1;
	int index=0;
	char *menu[3]={"���ԣ�","[ �ύ ]","[ ���� ]"}; 
	char word[60]=""; 
	
	SetCursorPosition(Handle_Out,0,7);    
    printf("     -------------------------------------------------\n\n");
    printf("     -------------------------------------------------");
	while(1)
	{
		if(index==0)
		{
			if(statusColor==1)			
				SetConsoleTextAttribute(Handle_Out,0x90);  //ǳ��ɫ 
			else
				SetConsoleTextAttribute(Handle_Out,0x10);  //��ɫ 			
		} 
		else
			SetConsoleTextAttribute(Handle_Out,0x70); 
		SetCursorPosition(Handle_Out,12,5);    
    	printf("%s",menu[0]);
    	
		for(int i=1;i<3;i++)
		{
			if(i==index)
				SetConsoleTextAttribute(Handle_Out,0x90);
			else
				SetConsoleTextAttribute(Handle_Out,0x70);
			SetCursorPosition(Handle_Out,12+28*(i-1),14);    
	    	printf("%s",menu[i]);
		}
		
		int user_input = GetUserInput(&index,3,2);
		if(user_input==ENTER)
			statusColor = -statusColor;		
		if(index==0)
		{
			if(statusColor==1)			
				SetConsoleTextAttribute(Handle_Out,0x90);  //ǳ��ɫ 
			else
				SetConsoleTextAttribute(Handle_Out,0x10);  //��ɫ 			
		} 
		else
			SetConsoleTextAttribute(Handle_Out,0x70); 
		SetCursorPosition(Handle_Out,12,5);    
    	printf("%s",menu[0]);
    	SetConsoleTextAttribute(Handle_Out,0x70); 
    	if(user_input==ENTER)
    	{
    		statusColor = -statusColor;	
    		SetCursorPosition(Handle_Out,18,5);
    		switch(index)
    		{
    			case 0: Gets(word,60); break;
    			case 1: {
    				if(!(strcmp(word,""))) 
    				{
    					SetCursorPosition(Handle_Out,23,11);
    					SetConsoleTextAttribute(Handle_Out,0x74);
    					printf("���Բ���Ϊ�գ�");
						SetConsoleTextAttribute(Handle_Out,0x70);    					
					}
					else
					{
						WriteLeaveWord(Post_Thing, word);
						RedirectPage(12);
						PostDetailPage(Post_Thing, page, status, pos, a, b);
					}	
				} break;		//�ύ���� 
    			case 2: PostDetailPage(Post_Thing, page, status, pos, a, b); break;	//���� 		
			}
		}
	}
}

//д���û�������Ϣ���ļ��� 
void WriteLeaveWord(struct POST_THING Post_Thing , char *content)
{
	//����ʱ�ռ��ǿ϶��Ѿ�������
	//��ȡ�ļ�����ýṹ������WSpace 
	FILE *fp; 
	struct WORD_SPACE WSpace[User_Info.user_numbers];
	EnDecryptFile("leave_word.dat",myKey);
	fp=fopen("leave_word.dat","rb");
    for(int i=0;i<User_Info.user_numbers;i++)
		fread(&WSpace[i],sizeof(struct WORD_SPACE),1,fp);  
   	fclose(fp);	
   	//�Ƚ����ӷ������ң��ĺ��룬������ӷ������ң������Կռ���Ϣ������ֵ 
   	int k = 0;//* 
   	char time[20];
   	GetNowTime(time);
   	for(int i=0;i<User_Info.user_numbers;i++)
	if(!(strcmp(WSpace[i].master_phone,Post_Thing.phone)))
		k = i;	//�����Ǳ�Ȼ�ģ���Ҫ��Ϊ���ҵ�����ֵ ;
	WSpace[k].message_numbers++;
	if(WSpace[k].message_numbers>10)
	{
		for(int i=0;i<9;i++)
		{
			strcpy(WSpace[k].Message[i].user_name, WSpace[k].Message[i+1].user_name); //ʹ���������Զ�ȥ�����ϵģ���������С��10 
			strcpy(WSpace[k].Message[i].user_phone, WSpace[k].Message[i+1].user_phone);
			strcpy(WSpace[k].Message[i].content, WSpace[k].Message[i+1].content);
			strcpy(WSpace[k].Message[i].time, WSpace[k].Message[i+1].time);
			strcpy(WSpace[k].Message[i].IDnumber,WSpace[k].Message[i+1].IDnumber);
		}
		strcpy(WSpace[k].Message[9].user_name, User_Info.StudInfo.name); //����Ϊ��¼���û������� 
		strcpy(WSpace[k].Message[9].user_phone, User_Info.StudInfo.phone);
		strcpy(WSpace[k].Message[9].content, content);
		strcpy(WSpace[k].Message[9].time, time);
		strcpy(WSpace[k].Message[WSpace[k].message_numbers-1].IDnumber,Post_Thing.IDnumber);
		WSpace[k].message_numbers=10;
	}	
	else
	{
		strcpy(WSpace[k].Message[WSpace[k].message_numbers-1].user_name,User_Info.StudInfo.name); //����Ϊ��¼���û������� 
		strcpy(WSpace[k].Message[WSpace[k].message_numbers-1].user_phone,User_Info.StudInfo.phone);
		strcpy(WSpace[k].Message[WSpace[k].message_numbers-1].content,content);
		strcpy(WSpace[k].Message[WSpace[k].message_numbers-1].time,time);
		strcpy(WSpace[k].Message[WSpace[k].message_numbers-1].IDnumber,Post_Thing.IDnumber);
	}
	
	fp=fopen("leave_word.dat","wb");
   	fwrite(&WSpace,sizeof(struct WORD_SPACE),User_Info.user_numbers,fp);
	fclose(fp);
	EnDecryptFile("leave_word.dat",myKey);	//�����ļ� 							 
} 

//չʾ������Ϣ 
void ShowLeaveWord(void)
{
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,27,0);    
	printf("���԰�");	//��ӡ���� 
	int flash=0; 
	int a = 0;	
	SetCursorPosition(Handle_Out,0,2);    
    printf("   -----------------------------------------------------");
    
    FILE *fp;
    struct WORD_SPACE WSpace[User_Info.user_numbers];
	EnDecryptFile("leave_word.dat",myKey);
	fp=fopen("leave_word.dat","rb");
    for(int i=0;i<User_Info.user_numbers;i++)
		fread(&WSpace[i],sizeof(struct WORD_SPACE),1,fp);  
   	fclose(fp);	
   	EnDecryptFile("leave_word.dat",myKey);
   	
   	int num = WSpace[User_Info.user_seriNum].message_numbers;
   	
	SetConsoleTextAttribute(Handle_Out, 0x90);
	SetCursorPosition(Handle_Out,26,18);
	printf("[ ���� ]");
	SetConsoleTextAttribute(Handle_Out, 0x70);
	while(1)	
	{
		if(flash)
		{
			SetCursorPosition(Handle_Out,0,3);
	   		for(int j=0;j<15;j++)
	   			printf("                                                          \n");   		
		}
		if(num<5)
	   	for(int i=0;i<num;i++)
	   	{
	   		SetCursorPosition(Handle_Out,5,3+3*i);
	   		printf("�绰:%s  ʱ��:%s  [%s]",WSpace[User_Info.user_seriNum].Message[num-1-i].user_phone,  WSpace[User_Info.user_seriNum].Message[num-1-i].time,  WSpace[User_Info.user_seriNum].Message[num-1-i].IDnumber);
	   		SetCursorPosition(Handle_Out,5,4+3*i);
	   		SetConsoleTextAttribute(Handle_Out, 0x74);
	   		printf("@%s��",WSpace[User_Info.user_seriNum].Message[num-1-i].user_name);
	   		SetConsoleTextAttribute(Handle_Out, 0x70);
	   		puts(WSpace[User_Info.user_seriNum].Message[num-1-i].content);
		}
	   	else
	   	for(int i=a;i<a+4;i++)
	   	{	   			   		
	   		SetCursorPosition(Handle_Out,5,3+3*(i-a));
	   		printf("�绰:%s  ʱ��:%s  [%s]",WSpace[User_Info.user_seriNum].Message[9-i].user_phone,  WSpace[User_Info.user_seriNum].Message[9-i].time,  WSpace[User_Info.user_seriNum].Message[num-1-i].IDnumber);
	   		SetCursorPosition(Handle_Out,5,4+3*(i-a));
	   		SetConsoleTextAttribute(Handle_Out, 0x74);
	   		printf("@%s��",WSpace[User_Info.user_seriNum].Message[9-i].user_name);
	   		SetConsoleTextAttribute(Handle_Out, 0x70);
	   		puts(WSpace[User_Info.user_seriNum].Message[9-i].content);
		}
		flash = 0;
		int user_input = getch();	
		switch(user_input)
		{
			case DOWN: a++; if(a>num-4){a=num-4;} flash=1; break;
			case UP: a--; if(a<0){a=0;} flash=1; break;
			case ENTER: UserMenu_Option(); break;
			case ESC: exit(1); break;
		}	
	}
} 

//ֻ��ȡ�û������ǰn���� 
void Gets(char *str, int n)
{
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE); 
	CONSOLE_CURSOR_INFO Corsor_Info; 
    GetConsoleCursorInfo(Handle_Out, &Corsor_Info);    
    Corsor_Info.bVisible = 1;	//��ʾ��� 
    SetConsoleCursorInfo(Handle_Out, &Corsor_Info);
	char string[120];
	gets(string);
	for(int i=0;i<n;i++)
		str[i] = string[i];	
	Corsor_Info.bVisible = 0;	//�رչ�� 
    SetConsoleCursorInfo(Handle_Out, &Corsor_Info);
    fflush(stdin);
}


//������������ҳ�� 
void AskforResetPassword(void)
{
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,24,0);    
	printf("������������");	 
	int statusColor=1;
	int index=0;
	char *menu[5]={"������֣�","�ֻ��ţ�","���Թ���Ա��","[ ȷ�� ]","[ ���� ]"}; 
	char word[60]; 
	struct USER_MESSAGE User_Message={1,"","","",""};
	
	SetConsoleTextAttribute(Handle_Out,15 | 8 | 103 | 64);
	SetCursorPosition(Handle_Out,0,2); 
	printf("\t����������ע���ֻ����Ͷ��ţ���xxxx(�ֻ���)\n"); 
	printf("\t      �����������롱��150133850000(�ֻ���)\n");
	printf("\t      �������뽫��һ������������ɣ���ɺ�\n"); 
	printf("\t      ���뽫Ϊ��ѧ�ţ���ǵõ�¼���޸ġ�  \n"); 
	SetConsoleTextAttribute(Handle_Out,0x70);
	
	SetCursorPosition(Handle_Out,0,12);    
    printf("     -------------------------------------------------");
	while(1)
	{	 
    	for(int i=0;i<3;i++)
    	{
			if(index==i)
			{
				if(statusColor==1)			
					SetConsoleTextAttribute(Handle_Out,0x90);  //ǳ��ɫ 
				else
					SetConsoleTextAttribute(Handle_Out,0x10);  //��ɫ 			
			} 
			else
				SetConsoleTextAttribute(Handle_Out,0x70); 
			SetCursorPosition(Handle_Out,8,8+i); 
			printf("%s",menu[i]);  
		}  	
		for(int i=3;i<5;i++)
		{
			if(i==index)
				SetConsoleTextAttribute(Handle_Out,0x90);
			else
				SetConsoleTextAttribute(Handle_Out,0x70);
			SetCursorPosition(Handle_Out,12+28*(i-3),16);    
	    	printf("%s",menu[i]);
		}
		
		int user_input = GetUserInput(&index,5,2);
		if(user_input==ENTER)
		{
			SetConsoleTextAttribute(Handle_Out,15 | 8 | 103 | 64);
			SetCursorPosition(Handle_Out,0,2); 
			printf("\t����������ע���ֻ����Ͷ��ţ���xxxx(�ֻ���)\n"); 
			printf("\t      �����������롱��150133850000(�ֻ���)\n");
			printf("\t      �������뽫��һ������������ɣ���ɺ�\n"); 
			printf("\t      ���뽫Ϊ��ѧ�ţ���ǵõ�¼���޸ġ�  \n"); 
			SetConsoleTextAttribute(Handle_Out,0x70);
			statusColor = -statusColor;
		}
					
		for(int i=0;i<3;i++)
    	{
			if(index==i)
			{
				if(statusColor==1)			
					SetConsoleTextAttribute(Handle_Out,0x90);  //ǳ��ɫ 
				else
					SetConsoleTextAttribute(Handle_Out,0x10);  //��ɫ 			
			} 
			else
				SetConsoleTextAttribute(Handle_Out,0x70); 
			SetCursorPosition(Handle_Out,8,8+i); 
			printf("%s",menu[i]);  
		}
    	SetConsoleTextAttribute(Handle_Out,0x70); 
    	if(user_input==ENTER)
    	{
    		statusColor = -statusColor;	
    		SetCursorPosition(Handle_Out,8+strlen(menu[index]),8+index);
    		switch(index)
    		{	
    			case 0: Gets(User_Message.user_name,20); break;	//������� 
    			case 1: Gets(User_Message.user_phone,12); break;	//��ĵ绰 
    			case 2: Gets(User_Message.content,60); break;	//�������� 
    			case 3: {
    				if(!(strcmp(User_Message.user_name,"") && strcmp(User_Message.user_phone,"") && strcmp(User_Message.content,""))) 
    				{
    					SetCursorPosition(Handle_Out,23,14);
    					SetConsoleTextAttribute(Handle_Out,0x74);
    					printf("��Ϣ����Ϊ�գ�");
						SetConsoleTextAttribute(Handle_Out,0x70);    					
					}	//�ж���Ϣ�Ƿ�Ϊ�� 
					else
					{
						char time[20];
	    				GetNowTime(time);
	    				strcpy(User_Message.time,time);
	    				WriteUserMessage(User_Message);
						RedirectPage(13);
					}   				
				} break;		//�ύ���� 
    			case 4: SignInMenu_Option(); break;	//���� 		
			}
		}
	}
}

//����û���������������Ϣ	*�ȶ�ȡ��д��
void WriteUserMessage(struct USER_MESSAGE User_Message)
{
	int message_numbers = Config.message_numbers;	
	struct USER_MESSAGE Message[message_numbers+1];	 
	FILE *fp;			
	//�ж��ļ��Ƿ����,�������򴴽�һ�� 
	if((fp=fopen("user_message.dat","r"))==NULL) 
	{
		fp=fopen("user_message.dat","w");
		fclose(fp);
	} 
	EnDecryptFile("user_message.dat",myKey);	//�����ļ� 
	fp=fopen("user_message.dat","rb");
    for(int i=0;i<message_numbers;i++)
		fread(&Message[i],sizeof(struct USER_MESSAGE),1,fp);  
   	fclose(fp);  
		    	
	Message[message_numbers] = User_Message;	//׷����Ϣ 
	message_numbers++;
	fp=fopen("user_message.dat","wb");
   	fwrite(&Message,sizeof(struct USER_MESSAGE),message_numbers,fp);
	fclose(fp);
	EnDecryptFile("user_message.dat",myKey);	//�����ļ� 	
	//���������ļ� 
    FILE *cg;
	Config.message_numbers = message_numbers;
	cg=fopen("config","wb");
	fwrite(&Config,sizeof(struct CONFIG),1,cg);
	fclose(cg);
	EnDecryptFile("config",myKey);	
} 
 
//չʾ�û�������Ա��������Ϣ 
void ShowUserMessage(void)
{
	int message_numbers = Config.message_numbers;		
	struct USER_MESSAGE Message[message_numbers+1];
	FILE *fp;
	if((fp=fopen("user_message.dat","r"))==NULL) 
	{
		fp=fopen("user_message.dat","w");
		fclose(fp);
	} 
	EnDecryptFile("user_message.dat",myKey);	//�����ļ� 
	fp=fopen("user_message.dat","rb");
    for(int i=0;i<message_numbers;i++)
		fread(&Message[i],sizeof(struct USER_MESSAGE),1,fp);  
   	fclose(fp);
	EnDecryptFile("user_message.dat",myKey);
		
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,26,0);    
	printf("�û�����");	//��ӡ���� 
	int flash=0; 
	int a = 0;	
	SetCursorPosition(Handle_Out,0,2);    
    printf("   -----------------------------------------------------");  
	SetConsoleTextAttribute(Handle_Out, 0x90);
	SetCursorPosition(Handle_Out,26,18);
	printf("[ ���� ]");
	SetConsoleTextAttribute(Handle_Out, 0x70);
	int num = message_numbers;
	while(1)	
	{
		if(flash)
		{
			SetCursorPosition(Handle_Out,0,3);
	   		for(int j=0;j<15;j++)
	   			printf("                                                          \n");   		
		}
		if(num<5 && num!=0)
	   	for(int i=0;i<num;i++)
	   	{
	   		SetCursorPosition(Handle_Out,10,3+3*i);
	   		printf("�绰��%s  ʱ�䣺%s",Message[num-1-i].user_phone,  Message[num-1-i].time);
	   		SetCursorPosition(Handle_Out,10,4+3*i);
	   		SetConsoleTextAttribute(Handle_Out, 0x74);
	   		printf("@%s��",Message[num-1-i].user_name);
	   		SetConsoleTextAttribute(Handle_Out, 0x70);
	   		puts(Message[num-1-i].content);
		}
	   	else if(num>4 && num!=0)
	   	for(int i=a;i<a+4;i++)
	   	{	   			   		
	   		SetCursorPosition(Handle_Out,10,3+3*(i-a));
	   		printf("�绰��%s  ʱ�䣺%s",Message[num-1-i].user_phone,  Message[num-1-i].time);
	   		SetCursorPosition(Handle_Out,10,4+3*(i-a));
	   		SetConsoleTextAttribute(Handle_Out, 0x74);
	   		printf("@%s��",Message[num-1-i].user_name);
	   		SetConsoleTextAttribute(Handle_Out, 0x70);
	   		puts(Message[num-1-i].content);
		}
		flash = 0;
		int user_input = getch();	
		switch(user_input)
		{
			case DOWN: a++; if(a>num-4){a=num-4;} flash=1; break;
			case UP: a--; if(a<0){a=0;} flash=1; break;
			case ENTER: AdminMenu_Option(); break;
			case ESC: exit(1); break;
		}	
	}
} 

//�޸Ĺ���Ա������ 
void ChangeAdminPassword(void)
{
	system("cls");
	int index = 0;
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,18,4); 
	printf("�ݲ�֧���޸Ĺ���Ա���룡");
		
	SetConsoleTextAttribute(Handle_Out, 0x90);
	SetCursorPosition(Handle_Out,26,9);
	printf("[ ���� ]");
	int user_input = getch();
	while(user_input!=ENTER);
	SetConsoleTextAttribute(Handle_Out, 0x70);
	SetCursorPosition(Handle_Out,26,9);
	printf("[ ���� ]");
	ChangePasswordMenu_Option();
} 

//���ļ���ȡ���ӵ���Ϣ 
void GetPostData(void)
{
	FILE *cg;	
	if((cg=fopen("config","rb"))==NULL) 
	{
		cg=fopen("config","w");
		fclose(cg);
		Config.lost_numbers = 0;
		Config.find_numbers = 0;
		Config.user_numbers = 0;
		Config.message_numbers = 0;
	} 	
	else 
	{
		fclose(cg);
		EnDecryptFile("config",myKey);		//����ļ���������� 
		cg=fopen("config","rb"); 
		fread(&Config,sizeof(struct CONFIG),1,cg);
		fclose(cg);
		EnDecryptFile("config",myKey);	//���������ļ�
	}
	Post.lost_numbers = Config.lost_numbers;
	Post.find_numbers = Config.find_numbers;
	//*����ɱ���Post.Lost 
	struct POST_THING Lost[Post.lost_numbers];	//���Ϊ0�Ƿ������ ����Ĵ�С����Ϊ0�� 
	struct POST_THING Find[Post.find_numbers];
	FILE *fp1,*fp2;		
	EnDecryptFile("lost_info.dat",myKey);	//�����ļ� 	
	fp1=fopen("lost_info.dat","rb");
    for(int i=0;i<Post.lost_numbers;i++)
		fread(&Lost[i],sizeof(struct POST_THING),1,fp1);  
   	fclose(fp1);
   	
   	EnDecryptFile("find_info.dat",myKey);
	fp2=fopen("find_info.dat","rb");
    for(int i=0;i<Post.find_numbers;i++)
		fread(&Find[i],sizeof(struct POST_THING),1,fp2);  
   	fclose(fp2);   	   
	   	    		
	EnDecryptFile("lost_info.dat",myKey);	//�����ļ�
	EnDecryptFile("find_info.dat",myKey); 	
	
//	Post.Lost = Lost;	//��Ҫ�Ѻ�����(ָ��/)��ַ���ݳ�ȥ�������������ڽ��������ַ�ᱻ�ͷţ� 
//	Post.Find = Find; 
	Post.Lost = (struct POST_THING *)malloc(Post.lost_numbers*sizeof(struct POST_THING));
	Post.Find = (struct POST_THING *)malloc(Post.find_numbers*sizeof(struct POST_THING));
	for(int i=0;i<Post.lost_numbers;i++)
		Post.Lost[i] = Lost[i];
	for(int i=0;i<Post.find_numbers;i++)
		Post.Find[i] = Find[i];
} 

void WelcomPage(void)
{
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE); 
	//�Խ� 
	SetConsoleTextAttribute(Handle_Out, 0x74);	//��ɫ 
	SetCursorPosition(Handle_Out,4,2);
	printf("��");
	SetConsoleTextAttribute(Handle_Out, 0x71);	//��ɫ 
	SetCursorPosition(Handle_Out,54,17);
	printf("�� ");
	for(int i=0;i<16;i++)
	{
		SetConsoleTextAttribute(Handle_Out, 0x74);
		SetCursorPosition(Handle_Out,5+3*i,2);		
		printf("������");
		SetConsoleTextAttribute(Handle_Out, 0x72);
		SetCursorPosition(Handle_Out,2,i+3);	
		if(i<14)
			printf("  �� ");
		SetConsoleTextAttribute(Handle_Out, 0x71);	
		SetCursorPosition(Handle_Out,51-3*i,17);		
		printf("������");
		SetConsoleTextAttribute(Handle_Out, 0x76);
		SetCursorPosition(Handle_Out,54,16-i);	
		if(i<14)
			printf("�� ");
		Sleep(50);
	}	
	
	//��ȫ
	SetConsoleTextAttribute(Handle_Out, 0x72);
	SetCursorPosition(Handle_Out,5,17);
	printf("��");	 
	SetConsoleTextAttribute(Handle_Out, 0x74);
	SetCursorPosition(Handle_Out,53,2);
	printf("��");
	//�Խ� 
	SetConsoleTextAttribute(Handle_Out, 0x72);	//��ɫ 
	SetCursorPosition(Handle_Out,4,17);
	printf("��");
	SetConsoleTextAttribute(Handle_Out, 0x76);	//��ɫ
	SetCursorPosition(Handle_Out,54,2);
	printf("�� ");	
	
	SetConsoleTextAttribute(Handle_Out, 0x74);
	SetCursorPosition(Handle_Out,24,7);
	printf("�� "); 
	Sleep(200);
	SetConsoleTextAttribute(Handle_Out, 0x76);
	printf("ӭ ");
	Sleep(200);
	SetConsoleTextAttribute(Handle_Out, 0x71);
	printf("�� ");
	Sleep(200);
	SetConsoleTextAttribute(Handle_Out, 0x72);
	printf("��");
	Sleep(300); 
	
	SetConsoleTextAttribute(Handle_Out, 0x75);
	SetCursorPosition(Handle_Out,22,9);
	printf("ʧ���������ϵͳ"); 
	Sleep(100); 
	SetConsoleTextAttribute(Handle_Out, 0x70);
	SetCursorPosition(Handle_Out,25,13);
	printf("2021��4��");	
	Sleep(500);
	GetPostData();
}
 
