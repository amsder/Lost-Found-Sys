#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h> 

#define  MenuLength(x)   (sizeof(x)/sizeof(x[0]))
#define  WIDTH 60
#define  HEIGHT 20
#define true 1
#define false 0
#define SIGN_UP 1
#define SIGN_IN 0
#define LOGIN 2
void GetNowTime(char *now_time);
void ConsoleSet(void);
void ShowMenu(char **menu , char *menu_title ,char menu_size, int index , char statusColor) ;
void StartMenu_Option(void);
void SignUpMenu_Option(void);
void SignInMenu_Option(void);
void AdminLoginMenu_Option(void); 
void AdminMenu_Option(void);
void UserMenu_Option(void);
void UserMenu_MyInfo_Option(void);
void UserMenu_ChangeInfo_Option(void);
void ChangePasswordMenu_Option(void);
void BlankMenu_Option(int page);
void JudgePage(int page);
void RedirectPage(int page);
//void CreatStudentInfo(struct STUDENT_INFO*);	//δ����STUDENT_INFOǰ���������� 
int  GetUserInput(int *index , int size);
void EnDecryptFile(char *file, char *secretKey);
void CreatRandStr(char *str);
void ChangeUserName(char *name_or_password,int status);
void ChangeUserInfoPage(int status); 
void SetCursorPosition(HANDLE Handle_Out , int x , int y);

char myKey[24] = "^?z(���0Z6O�mXyY�t��Lc";
//int studSeriNum = 0;	//�û��ı�� 
//ö�ٳ�����ֵ 
enum 
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	ENTER = 13,
	ESC = 27 
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
	"��ʧ��������Ϣ��",
	"��ʰ�﷢����Ϣ��",
	"������������Ϣ��",
	"��  �û���Ϣ  ��",
	"��  �޸�����  ��",
	"��    ����    ��",
	"��    �˳�    ��",
};
 
//�û��˵� 
char *user_menu[] = 
{
	"���鿴ʧ����Ϣ��",
	"���鿴ʰ����Ϣ��",
	"��  �ҵĽ���  ��",
	"��  �ҵ���Ϣ  ��",
	"��    ����    ��",
	"��    �˳�    ��",
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
	char *user_menu;
	char *user_myinfo_menu;
	char *user_change_info_menu; 
	char *change_password_menu;
	char *blank_menu;
}Menu_Title={"��ӭ����ʧ���������ϵͳ��","ע�����","��¼����","����Ա��¼����","����Ա�������","�û��������","�ҵ���Ϣ","�޸���Ϣ","�޸��������","��ҳ���������ݣ�"};

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
}Page={1,2,3,4,5,6,7,8,9};

//����һ���ṹ�������ϵͳ���� 
struct CONFIG
{
	int user_numbers;
	char secret_key[24]; 
};

//����һ��������ѧ����Ϣ 
struct STUDENT_INFO
{
	char phone[12];
	char name[20];
	char studnum[12];
	char password[20];
	char repassword[20];
};

struct USER_INFO
{
	int user_numbers;	//���� 
	int user_seriNum;	//��� 
	struct STUDENT_INFO StudInfo; 	//���ѧ����Ϣ�Ľṹ��ָ�� 
}User_Info;

int SeekStudentInfo(struct STUDENT_INFO Student_Info,int signup_or_signin);
int JudgeUserInfo(struct STUDENT_INFO Student_Info,int signup_or_signin);
void GetUserInformation(struct STUDENT_INFO Student_Info,int user_numbers,int seri_num);
void ChangeStudentInfo(struct STUDENT_INFO Student_Info,int seri_num);

int main()
{
	system("git add .");
	system("git commit -t");
	system("git push origin main"); 
	ConsoleSet();	   
    StartMenu_Option();
	
    return 0;
}

/******************************************* 
*   ������ void ConsoleSet() 
*	���ܣ�����̨���� 
*	��������					
*	���ã���ʼʱ���ô˺�����ʼ������̨ 
*	���ߣ�Mxx
*******************************************/ 
void ConsoleSet()
{
	// ���ô���λ�úʹ�С �Լ�ǰ������ɫ 
    system("mode con cols=60 lines=20");
    system("color 70");
	//���ÿ���̨���� 
    SetConsoleTitleA("ʧ���������ϵͳ");
    //��ȡ��ǰ�ľ��---����Ϊ��׼������ 
    HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
    //��������Ϣ�ṹ��
	CONSOLE_CURSOR_INFO Corsor_Info; 
    //��ȡ�����Ϣ
    GetConsoleCursorInfo(Handle_Out, &Corsor_Info); 
	//���ù���С   
    Corsor_Info.dwSize = 1; 
	//���ù�겻�ɼ� FALSE   
    Corsor_Info.bVisible =  0; 
    //����(Ӧ��)�����Ϣ
    SetConsoleCursorInfo(Handle_Out, &Corsor_Info); 
 } 
 
 
/******************************************* 
*   ������ void ShowMenu(char **menu , char *menu_title ,char menu_size, int index , char statusColor)
*	���ܣ�չʾ�˵� 
*	������1.�ַ�������menuΪҪչʾ�Ĳ˵� 2.�ַ���menu_titleΪ�˵��ı���
		  3.������menu_sizeΪ�˵��Ĵ�С  3.������indexΪ����ֵ					
*	���ã�����˵��йص���Ϣ������ֵ���ͻ�չʾ���˵�ҳ�� 
*	���ߣ�Mxx
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
			SetCursorPosition(Handle_Out,22,4+i);    
    		printf("%s",menu[i]);
		}
		//������ʾΪ��ɫ 
		else
		{
			//��ɫ 
			SetConsoleTextAttribute(Handle_Out,0x70); 
			SetCursorPosition(Handle_Out,22,4+i); 
    		printf("%s",menu[i]);
		}
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
*	���ߣ�Mxx
*******************************************/ 
void StartMenu_Option(void)
{
	system("color 70");		//*��ʱ����ȥ��*// 
	system("cls");	//�����Ļ	 
	int index = 0;
	while(1)
	{
		ShowMenu(start_menu , Menu_Title.start_menu , MenuLength(start_menu) , index , 1);
		int user_input = GetUserInput(&index , MenuLength(start_menu));
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: BlankMenu_Option(Page.start_menu); break ;  	//�οͷ��� 
				case 1: SignInMenu_Option(); break ;  	    //�û���¼ 
				case 2: AdminLoginMenu_Option();break ;  	//����Ա��¼ 
				case 3: SignUpMenu_Option(); break ;  	//ע��
				case 4: exit(1);  break ;  	//�˳�
		
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
	struct STUDENT_INFO Student_Info={" "," "," "," "," "};
	char phone_number[12],user_name[10],studnum[10],password[20],repassword[20];
	ShowMenu(signup_menu , Menu_Title.signup_menu , MenuLength(signup_menu) , index , 1);
	while(1)
	{	
		int user_input = GetUserInput(&index , MenuLength(signup_menu));
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
				case 0: gets(Student_Info.phone);  break ;  	//�ֻ��� 
				case 1: gets(Student_Info.name);   break ;  	//�û��� 
				case 2: gets(Student_Info.studnum); break ;  	//ѧ�� 
				case 3: gets(Student_Info.password);break ;  	//����
				case 4: gets(Student_Info.repassword); break ;  //�ٴ��������� 
				case 5:	if(JudgeUserInfo(Student_Info,SIGN_UP)==true){RedirectPage(Page.signup_menu);} break;//ȷ��ע�� 
				case 6: StartMenu_Option();  break ;  	//����		
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
	struct STUDENT_INFO Student_Info={" "," "," "," "," "};
	ShowMenu(signin_menu , Menu_Title.signin_menu , MenuLength(signin_menu) , index , 1);
	while(1)
	{		
		int user_input = GetUserInput(&index , MenuLength(signin_menu));
		if(user_input == ENTER	)
		{
			statusColor = -statusColor;
		}			 
		ShowMenu(signin_menu , Menu_Title.signin_menu , MenuLength(signin_menu),index , statusColor);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			statusColor = -statusColor;
			switch(index)
			{
				case 0: gets(Student_Info.phone);  break ;  	//�ֻ��Ż�ѧ�� 
				case 1: gets(Student_Info.password);  break ;  	//���� 
				case 2: if(JudgeUserInfo(Student_Info,SIGN_IN)==true){RedirectPage(Page.signin_menu);} break; //ȷ�ϵ�¼ 
				case 3: StartMenu_Option(); break ;        	//����
				case 4: SignUpMenu_Option();  break ;   	//��ûע�� 
				case 5: BlankMenu_Option(Page.signin_menu);  break ;  	//�������� 
		
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
	struct STUDENT_INFO Student_Info={" "," "," "," "," "};
	ShowMenu(admin_login_menu , Menu_Title.admin_login_menu , MenuLength(admin_login_menu) , index , 1);
	while(1)
	{		
		int user_input = GetUserInput(&index , MenuLength(admin_login_menu));
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
				case 0: gets(Student_Info.name);  break ;  	//�˺� 
				case 1: gets(Student_Info.password);  break ; //���� 
				case 2: if(JudgeUserInfo(Student_Info,LOGIN)==true){RedirectPage(Page.admin_login_menu);} break;//ȷ�ϵ�¼ 
				case 3: StartMenu_Option(); break ;        	//����		
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
		int user_input = GetUserInput(&index , MenuLength(admin_menu));
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: BlankMenu_Option(Page.admin_menu); break ;  	//ʧ��������Ϣ 
				case 1: BlankMenu_Option(Page.admin_menu); break ;  	//ʰ�﷢����Ϣ
				case 2: BlankMenu_Option(Page.admin_menu); break ;  	//����������Ϣ 
				case 3: BlankMenu_Option(Page.admin_menu); break ;  	//�û���Ϣ 
				case 4: ChangePasswordMenu_Option(); break ;//�޸����� 
				case 5: BlankMenu_Option(Page.admin_menu); break ;		//���� 
				case 6: StartMenu_Option(); 	break ; 	//�˳� 
		
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
		int user_input = GetUserInput(&index , MenuLength(user_menu));
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: BlankMenu_Option(Page.user_menu); break ;  	//�鿴ʧ����Ϣ 
				case 1: BlankMenu_Option(Page.user_menu); break ;  	//�鿴ʰ����Ϣ
				case 2: BlankMenu_Option(Page.user_menu); break ;	//�ҵĽ��� 
				case 3: UserMenu_MyInfo_Option(); break ;  			//�ҵ���Ϣ 
				case 4: StartMenu_Option(); break ;		//����
				case 5: StartMenu_Option(); break ; 	//�˳� 
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
		int user_input = GetUserInput(&index , MenuLength(user_myinfo_menu));
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: puts(User_Info.StudInfo.phone); break ;  	//�ֻ��� 
				case 1: puts(User_Info.StudInfo.studnum); break ;  	//ѧ�� 
				case 2: puts(User_Info.StudInfo.name); break ;  	//�ǳ� 
				case 3: puts(User_Info.StudInfo.password); break ;  //���� 
				case 4: UserMenu_ChangeInfo_Option(); break ;		//�޸� 
				case 5: UserMenu_Option(); break ;		//����
				case 6: StartMenu_Option(); break ; 	//�˳� 
		
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
		int user_input = GetUserInput(&index , MenuLength(user_change_info_menu));
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
		int user_input = GetUserInput(&index , MenuLength(change_password_menu));
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0:  BlankMenu_Option(Page.change_password_menu); break;  	//�޸��ҵ����� 
				case 1:  BlankMenu_Option(Page.change_password_menu); break;  	//�����û����� 
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
		int user_input = GetUserInput(&index , MenuLength(blank_menu));
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: JudgePage(page); break ;  	//������һ�� 
				case 1: exit(1);   		 break ;  	//ֱ���˳� 
			}
		}
	}
} 


/******************************************* 
*   ������ void JudgePage(int page)
*	���ܣ��ж�ѡ�����ڵ�ҳ�棬����ת����Ӧҳ�� 
*	������int pageΪҳ���ʶ��					
*	���ã��ڿհ�ҳ��ʱ���ô˺��������ڷ���ԭ����ҳ�� 
*	���ߣ�Mxx
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
	}
}

 
/******************************************* 
*   ������ void RedirectPage(int page)
*	���ܣ��ж��Ƿ��¼�ɹ���Ȼ����ת����Ӧҳ�� 
*	������int pageΪҳ���ʶ��					
*	���ã�ȷ�ϵ�¼ʱ���ô˺��� 
*	���ߣ�Mxx
*******************************************/  
void RedirectPage(int page)
{
	system("cls"); 
	COORD Pos = {20,3};
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Handle_Out,Pos); 
	switch(page)
	{
		case 0: printf("�޸��ǳƳɹ���3�����ת..."); break;
		case 1: printf("�޸�����ɹ���3�����ת..."); break;  
		case 2: printf("ע��ɹ���3�����ת..."); break;  //��ʾ�û�ע��ɹ� 
		case 3: printf("��¼�ɹ���3�����ת..."); break;	//��ʾ�û���¼�ɹ� 		 
		case 4: printf("��¼�ɹ���3�����ת..."); break;  //��ʾ����Ա��¼�ɹ� 
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
		default: BlankMenu_Option(page); break; 
	} 
}

 
/*******************************************
*   ������JudgeUserInfo(struct STUDENT_INFO Student_Info,int signup_or_signin)
*	���ܣ��ж��û��������Ϣ�Ƿ�����Ҫ�󣬲�������Ӧ�ĸ�ʾ 
*	������������1.ѧ����Ϣ�ṹ��Student_Info,�����ֻ����û�����ѧ�ţ������ 2.signup_or_signinΪ״̬��					
*	���ã�ȷ��ע���ȷ�ϵ�¼ʱ���ô˺���������ֵ1��ʾ����Ҫ��0��ʾ������Ҫ�� 
*	���ߣ�Mxx
*******************************************/ 
int JudgeUserInfo(struct STUDENT_INFO Student_Info,int signup_or_signin)
{
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetCursorPosition(Handle_Out,20,12); 
	SetConsoleTextAttribute(Handle_Out,0x74);	//��ɫ������Ŀ 
	if(signup_or_signin==SIGN_UP)
	{
		if(!(strcmp(Student_Info.phone," ") || strcmp(Student_Info.name," ") || strcmp(Student_Info.studnum," ") || strcmp(Student_Info.password," ") || strcmp(Student_Info.repassword," ")))
		{
			printf("    �벻Ҫ���գ�     ");
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
		if(!(strcmp(Student_Info.phone," ") || strcmp(Student_Info.password," ")))
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
*	���ߣ�Mxx
*******************************************/ 
int SeekStudentInfo(struct STUDENT_INFO Student_Info,int signup_or_signin)
{
	struct CONFIG Config;
	int user_numbers = 0;
	char secret_key[24];
	int ifSignup = 0;
	FILE *cg; 
	//�������ļ��ж�ȡ�û��������Լ���Կ 
	if((cg=fopen("config","rb"))!=NULL) 
	{
		fclose(cg);
		EnDecryptFile("config",myKey);		//����ļ���������� 
		cg=fopen("config","rb"); 
		fread(&Config,sizeof(struct CONFIG),1,cg);
		fclose(cg);
		user_numbers = Config.user_numbers;
		strcpy(secret_key,Config.secret_key);
	}
	else
		CreatRandStr(secret_key);
	struct STUDENT_INFO Student[user_numbers+1];		 
	FILE *fp;		
	//�ж��ļ��Ƿ����,�������򴴽�һ�� 
	if((fp=fopen("student_info.dat","r"))==NULL) 
	{
		fp=fopen("student_info.dat","w");
		fclose(fp);
	} 
	EnDecryptFile("student_info.dat",secret_key);	//�����ļ� 
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
	}
	else
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
	EnDecryptFile("student_info.dat",secret_key);	//�����ļ� 	
	//���������ļ� 
	Config.user_numbers = user_numbers;
	strcpy(Config.secret_key,secret_key);
	cg=fopen("config","wb");
	fwrite(&Config,sizeof(struct CONFIG),1,cg);
	fclose(cg);
	EnDecryptFile("config",myKey);
	return ifSignup;	
}  
 

void GetUserInformation(struct STUDENT_INFO Student_Info,int user_numbers,int seri_num)
{
	User_Info.StudInfo = Student_Info;
	User_Info.user_seriNum = seri_num;
	User_Info.user_numbers = user_numbers; 
	
} 
 
/******************************************* 
*   ������ int  GetUserInput(int *index , int menu_size)
*	���ܣ��� ��������ϣ��� ��������£�ESC���˳�,Enter��ȷ�� 
*	������1.����ֵ�˵�index 2.�˵��Ĵ�С					
*	���ã��ڲ˵�ѡ�����ҳ����ô˺��������жϰ��� 
*	���ߣ�Mxx
*******************************************/ 
int  GetUserInput(int *index , int menu_size)
{
	int ch = getch();
	switch(ch)
	{
		//���ѡ���ϣ���ô��������ƶ� ������Ҳͬ�� 
		case UP : (*index > 0) ? (*index -= 1) : (*index = menu_size - 1);  break;		
		case DOWN : (*index < menu_size - 1) ? (*index += 1) : (*index = 0);  break;
		case LEFT : (*index > 0) ? (*index -= 1) : (*index = menu_size - 1);  break;		
		case RIGHT : (*index < menu_size - 1) ? (*index += 1) : (*index = 0);  break;
		//�س� 
		case  ENTER: system("color 70"); return ENTER ;
		//ESC
		case ESC: system("color 70"); return ESC ;
	}
	return 0 ;
}


/*******************************************
*   ������void CreatRandStr(char *str) 
*	���ܣ��������һ�γ��ַ�������Ϊ��Կ�� 
*	������1.�ַ���str������ɣ�����Ϊ24λ					
*	���ã���Ҫ�����Կʱ���ô˺��� 
*	���ߣ�Mxx
*******************************************/ 
void CreatRandStr(char *str)
{
	int flag,charLengt;
	int k=0;
	srand((unsigned)time(NULL));
	for(int i=0;i<24;i++)
		str[k++]='!'+rand()%243;	
}


/*******************************************
*   ������void EnDecryptFile(char *file, char *secretKey) 
*	���ܣ�������Կ���ܻ�����ļ���ͨ�����ʽ�� 
*	������1.fileΪҪ���ܻ���ܵ��ļ� 2.secretKeyΪһ���ַ���Կ					
*	���ã��ڶ�ȡ�ļ�ǰ���ô˺������н��ܣ���ȡ/д���ļ���������ô˺������м��� 
*	���ߣ�Mxx
*******************************************/ 
void EnDecryptFile(char *file, char *secretKey)
{
	FILE *File,*TempFile;
	char buffer[21];  	//�����������ڴ�Ŵ��ļ���ȡ������
	int readCount;  	//ÿ�δ��ļ��ж�ȡ���ֽ���
	int	keyLen = strlen(secretKey);

	if((File = fopen(file, "rb"))==NULL)
		printf("File open failed!");		
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
*	���ߣ�Mxx
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

void ChangeStudentInfo(struct STUDENT_INFO Student_Info,int seri_num)
{
	struct CONFIG Config;
	FILE *cg;
	int user_numbers;
	char secret_key[24];	 
	
	EnDecryptFile("config",myKey);	//�����ļ� 
	cg=fopen("config","rb");
	fread(&Config,sizeof(struct CONFIG),1,cg);
	fclose(cg);
	user_numbers = Config.user_numbers;
	strcpy(secret_key,Config.secret_key);
	
	struct STUDENT_INFO Student[user_numbers+1];		 
	FILE *fp;		
	EnDecryptFile("student_info.dat",secret_key);	//�����ļ� 
	fp=fopen("student_info.dat","rb");
    for(int i=0;i<user_numbers;i++)
		fread(&Student[i],sizeof(struct STUDENT_INFO),1,fp);  
   	fclose(fp);  
	   	    	
	//�޸��û���Ϣ������һ���ṹ�壬�滻��ԭ���Ľṹ��
	Student[seri_num] = Student_Info;
	
	fp=fopen("student_info.dat","wb");
   	fwrite(&Student,sizeof(struct STUDENT_INFO),user_numbers,fp);
	fclose(fp);
	EnDecryptFile("student_info.dat",secret_key);	//�����ļ� 	
	//���������ļ� 
	Config.user_numbers = user_numbers;
	strcpy(Config.secret_key,secret_key);
	cg=fopen("config","wb");
	fwrite(&Config,sizeof(struct CONFIG),1,cg);
	fclose(cg);
	EnDecryptFile("config",myKey);
}

void ChangeUser_Name_Password(char *name_or_password,int status)
{
	if(status==0)
		strcpy(User_Info.StudInfo.name,name_or_password);
	if(status==1)
		strcpy(User_Info.StudInfo.password,name_or_password);
	ChangeStudentInfo(User_Info.StudInfo,User_Info.user_seriNum);
}

void ChangeUserInfoPage(int status)
{
	system("cls");
	COORD Pos = {22,4};
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Handle_Out,Pos); 
	char *menu[] = {"ȷ��","����"};
	char *str[] = {"�ǳ�","����"};
	char new_str[20];
	int index = 0;
	printf("��ȷ���޸�%s��",str[status]);
	while(1)
	{
		for(int i=0;i<2;i++)
		{
			if(i == index)
			{
				SetConsoleTextAttribute(Handle_Out,0x90);  //��ɫ 
				SetCursorPosition(Handle_Out,25+7*i,6);   
	    		printf("%s",menu[i]);
			}
			else
			{
				SetConsoleTextAttribute(Handle_Out,0x70); 
	    		SetCursorPosition(Handle_Out,25+7*i,6);
	    		printf("%s",menu[i]);
			}
		}
		int user_input = GetUserInput(&index , MenuLength(menu));
		if(user_input == ENTER)
		switch(index)
		{
			case 0: {
						SetCursorPosition(Handle_Out,20,8);
						printf("�������µ�%s��",str[status]);
						gets(new_str);
						SetCursorPosition(Handle_Out,25,10);
						SetConsoleTextAttribute(Handle_Out,0x90);
						printf("[ ȷ�� ]");
						SetConsoleTextAttribute(Handle_Out,0x70);
						while(1)
						{								
							if(user_input == ENTER)
							{
								ChangeUser_Name_Password(new_str,status);
								RedirectPage(status);
							}
							int user_input = GetUserInput(&index , 1);
						} 
					}	//ȷ��
			case 1: UserMenu_ChangeInfo_Option(); break ;  	//����		
		}
	}		 
}

void  SetCursorPosition(HANDLE Handle_Out , int x , int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(Handle_Out,Pos);
 } 
