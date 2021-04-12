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
//void CreatStudentInfo(struct STUDENT_INFO*);	//未定义STUDENT_INFO前不能声明！ 
int  GetUserInput(int *index , int size);
void EnDecryptFile(char *file, char *secretKey);
void CreatRandStr(char *str);
void ChangeUserName(char *name_or_password,int status);
void ChangeUserInfoPage(int status); 
void SetCursorPosition(HANDLE Handle_Out , int x , int y);

char myKey[24] = "^?z(躅婀0Z6O噈XyY涇Lc";
//int studSeriNum = 0;	//用户的编号 
//枚举出按键值 
enum 
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	ENTER = 13,
	ESC = 27 
};

//开始菜单
char *start_menu[] = 
{
	"＊  游客访问  ＊",
	"＊  用户登录  ＊",
	"＊ 管理员登录 ＊",
	"＊    注册    ＊",
	"＊    退出    ＊",
};

//注册菜单
char *signup_menu[] = 
{
	"手机号：", 
	"用户名：",
	"学号：",
	"密码：",
	"再次输入密码：",
	"[ 确认注册 ]", 
	"[   返回   ]",
};

//用户登录菜单
char *signin_menu[] = 
{
	"手机号/学号：", 
	"密码：",
	"[ 确认登录 ]", 
	"[   返回   ]",
	"没有账号？点击注册", 
	"忘记密码？申请重置",
};

//管理员登录 
char *admin_login_menu[] = 
{
	"账号：", 
	"密码：",
	"[ 确认登录 ]", 
	"[   返回   ]",
};

//管理员菜单 
char *admin_menu[] = 
{
	"＊失物求助信息＊",
	"＊拾物发布信息＊",
	"＊结束交易信息＊",
	"＊  用户信息  ＊",
	"＊  修改密码  ＊",
	"＊    留言    ＊",
	"＊    退出    ＊",
};
 
//用户菜单 
char *user_menu[] = 
{
	"＊查看失物信息＊",
	"＊查看拾物信息＊",
	"＊  我的交易  ＊",
	"＊  我的信息  ＊",
	"＊    返回    ＊",
	"＊    退出    ＊",
}; 
 
//用户菜单之用户信息 
char *user_myinfo_menu[] = 
{
	"手机号：",
	"  学号：",
	"  昵称：",
	"  密码：",
	"[ 修改 ]",
	"[ 返回 ]",
	"[ 退出 ]",
};  

char *user_change_info_menu[] = 
{
	"＊  修改昵称  ＊",
	"＊  修改密码  ＊",
	"＊    返回    ＊", 
};
 
//修改密码菜单 
char *change_password_menu[] = 
{
	"＊修改我的密码＊",
	"＊重置用户密码＊",
	"＊    返回    ＊", 
};

//空页面菜单 
char *blank_menu[] = 
{
	"＊ 返回上一级 ＊",
	"＊  直接退出  ＊",
};

//菜单页面的标题 
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
}Menu_Title={"欢迎进入失物招领管理系统！","注册界面","登录界面","管理员登录界面","管理员管理界面","用户管理界面","我的信息","修改信息","修改密码界面","此页面暂无内容！"};

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

//建立一个结构体来存放系统配置 
struct CONFIG
{
	int user_numbers;
	char secret_key[24]; 
};

//建立一个链表存放学生信息 
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
	int user_numbers;	//人数 
	int user_seriNum;	//编号 
	struct STUDENT_INFO StudInfo; 	//存放学生信息的结构体指针 
}User_Info;

int SeekStudentInfo(struct STUDENT_INFO Student_Info,int signup_or_signin);
int JudgeUserInfo(struct STUDENT_INFO Student_Info,int signup_or_signin);
void GetUserInformation(struct STUDENT_INFO Student_Info,int user_numbers,int seri_num);
void ChangeStudentInfo(struct STUDENT_INFO Student_Info,int seri_num);

int main()
{
	system("git pull");
	ConsoleSet();	   
    StartMenu_Option();
	
    return 0;
}

/******************************************* 
*   函数： void ConsoleSet() 
*	功能：控制台设置 
*	参数：无					
*	调用：开始时调用此函数初始化控制台 
*	作者：Mxx
*******************************************/ 
void ConsoleSet()
{
	// 设置窗口位置和大小 以及前景背景色 
    system("mode con cols=60 lines=20");
    system("color 70");
	//设置控制台标题 
    SetConsoleTitleA("失物招领管理系统");
    //获取当前的句柄---设置为标准输出句柄 
    HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
    //定义光标信息结构体
	CONSOLE_CURSOR_INFO Corsor_Info; 
    //获取光标信息
    GetConsoleCursorInfo(Handle_Out, &Corsor_Info); 
	//设置光标大小   
    Corsor_Info.dwSize = 1; 
	//设置光标不可见 FALSE   
    Corsor_Info.bVisible =  0; 
    //设置(应用)光标信息
    SetConsoleCursorInfo(Handle_Out, &Corsor_Info); 
 } 
 
 
/******************************************* 
*   函数： void ShowMenu(char **menu , char *menu_title ,char menu_size, int index , char statusColor)
*	功能：展示菜单 
*	参数：1.字符串数组menu为要展示的菜单 2.字符串menu_title为菜单的标题
		  3.整型数menu_size为菜单的大小  3.整型数index为索引值					
*	调用：传入菜单有关的信息和索引值，就会展示出菜单页面 
*	作者：Mxx
*******************************************/  
void ShowMenu(char **menu , char *menu_title ,char menu_size, int index , char statusColor)
{	
	char time[20];
	char len = strlen(menu_title);
	GetNowTime(time);
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	//设置显示到控制台终端的具体位置 
	SetCursorPosition(Handle_Out,(WIDTH-len)/2,0);    
	printf("%s",menu_title);	//打印标题 
	SetCursorPosition(Handle_Out,23,1);
	printf("%s",time);			//打印时间 
	
	for(int i = 0 ; i < menu_size ; i++)
	{
		if(i == index)
		{
			if(statusColor==1)			
				SetConsoleTextAttribute(Handle_Out,0x90);  //浅蓝色 
			else
				SetConsoleTextAttribute(Handle_Out,0x10);  //蓝色 
			SetCursorPosition(Handle_Out,22,4+i);    
    		printf("%s",menu[i]);
		}
		//否则显示为白色 
		else
		{
			//白色 
			SetConsoleTextAttribute(Handle_Out,0x70); 
			SetCursorPosition(Handle_Out,22,4+i); 
    		printf("%s",menu[i]);
		}
	}
    SetCursorPosition(Handle_Out,22+strlen(menu[index]),4+index);
	//刷新标准输出缓冲区 
	fflush(stdout);
} 


/******************************************* 
*   函数： void StartMenu_Option(void)
*	功能：登录界面的选项操作 
*	参数：无					
*	调用：此函数会调用菜单显示函数，并实现菜单选项的可视化操作 
*	作者：Mxx
*******************************************/ 
void StartMenu_Option(void)
{
	system("color 70");		//*暂时加上去的*// 
	system("cls");	//清空屏幕	 
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
				case 0: BlankMenu_Option(Page.start_menu); break ;  	//游客访问 
				case 1: SignInMenu_Option(); break ;  	    //用户登录 
				case 2: AdminLoginMenu_Option();break ;  	//管理员登录 
				case 3: SignUpMenu_Option(); break ;  	//注册
				case 4: exit(1);  break ;  	//退出
		
			}
		}
	} 
} 

//注册界面选项操作  *格式同上面* 
void SignUpMenu_Option(void)
{
	system("cls");	//清空屏幕 
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
				case 0: gets(Student_Info.phone);  break ;  	//手机号 
				case 1: gets(Student_Info.name);   break ;  	//用户名 
				case 2: gets(Student_Info.studnum); break ;  	//学号 
				case 3: gets(Student_Info.password);break ;  	//密码
				case 4: gets(Student_Info.repassword); break ;  //再次输入密码 
				case 5:	if(JudgeUserInfo(Student_Info,SIGN_UP)==true){RedirectPage(Page.signup_menu);} break;//确认注册 
				case 6: StartMenu_Option();  break ;  	//返回		
			}
		}
	} 
} 

//用户登录界面选项操作  *格式同上面* 
void SignInMenu_Option(void)
{
	system("cls");	//清空屏幕 
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
				case 0: gets(Student_Info.phone);  break ;  	//手机号或学号 
				case 1: gets(Student_Info.password);  break ;  	//密码 
				case 2: if(JudgeUserInfo(Student_Info,SIGN_IN)==true){RedirectPage(Page.signin_menu);} break; //确认登录 
				case 3: StartMenu_Option(); break ;        	//返回
				case 4: SignUpMenu_Option();  break ;   	//还没注册 
				case 5: BlankMenu_Option(Page.signin_menu);  break ;  	//重置密码 
		
			}
		}
	} 
} 

//管理员登录界面选项操作  *格式同上面* 
void AdminLoginMenu_Option(void)
{
	system("cls");	//清空屏幕 
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
				case 0: gets(Student_Info.name);  break ;  	//账号 
				case 1: gets(Student_Info.password);  break ; //密码 
				case 2: if(JudgeUserInfo(Student_Info,LOGIN)==true){RedirectPage(Page.admin_login_menu);} break;//确认登录 
				case 3: StartMenu_Option(); break ;        	//返回		
			}
		}
	} 
}

//管理员界面选项操作  *格式同上面* 
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
				case 0: BlankMenu_Option(Page.admin_menu); break ;  	//失物求助信息 
				case 1: BlankMenu_Option(Page.admin_menu); break ;  	//拾物发布信息
				case 2: BlankMenu_Option(Page.admin_menu); break ;  	//结束交易信息 
				case 3: BlankMenu_Option(Page.admin_menu); break ;  	//用户信息 
				case 4: ChangePasswordMenu_Option(); break ;//修改密码 
				case 5: BlankMenu_Option(Page.admin_menu); break ;		//留言 
				case 6: StartMenu_Option(); 	break ; 	//退出 
		
			}
		}
	} 
} 

//用户界面选项操作  *格式同上面* 
void UserMenu_Option(void)
{
	system("cls");
	int index = 0 ;
	while(1)
	{
		char title[20],*ch = "欢迎您！";
		sprintf(title,"%s%s",ch,User_Info.StudInfo.name);
		ShowMenu(user_menu , title , MenuLength(user_menu) , index , 1);
		int user_input = GetUserInput(&index , MenuLength(user_menu));
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: BlankMenu_Option(Page.user_menu); break ;  	//查看失物信息 
				case 1: BlankMenu_Option(Page.user_menu); break ;  	//查看拾物信息
				case 2: BlankMenu_Option(Page.user_menu); break ;	//我的交易 
				case 3: UserMenu_MyInfo_Option(); break ;  			//我的信息 
				case 4: StartMenu_Option(); break ;		//返回
				case 5: StartMenu_Option(); break ; 	//退出 
			}
		}
	} 
}

//用户->我的信息界面选项操作  *格式同上面* 
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
				case 0: puts(User_Info.StudInfo.phone); break ;  	//手机号 
				case 1: puts(User_Info.StudInfo.studnum); break ;  	//学号 
				case 2: puts(User_Info.StudInfo.name); break ;  	//昵称 
				case 3: puts(User_Info.StudInfo.password); break ;  //密码 
				case 4: UserMenu_ChangeInfo_Option(); break ;		//修改 
				case 5: UserMenu_Option(); break ;		//返回
				case 6: StartMenu_Option(); break ; 	//退出 
		
			}
		}
	} 
}

//用户->我的信息->修改信息界面选项操作  *格式同上面*
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
				case 0:  ChangeUserInfoPage(0); break;  	//修改昵称
				case 1:  ChangeUserInfoPage(1); break;  	//修改密码 
				case 2:  UserMenu_MyInfo_Option(); 	 break;     //返回 
			}
		}
	}
}
 

//修改密码界面选项操作  *格式同上面*
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
				case 0:  BlankMenu_Option(Page.change_password_menu); break;  	//修改我的密码 
				case 1:  BlankMenu_Option(Page.change_password_menu); break;  	//重置用户密码 
				case 2:  AdminMenu_Option(); 	 break;     //退出 
			}
		}
	}
} 

//空页面选项操作  *格式同上面*
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
				case 0: JudgePage(page); break ;  	//返回上一级 
				case 1: exit(1);   		 break ;  	//直接退出 
			}
		}
	}
} 


/******************************************* 
*   函数： void JudgePage(int page)
*	功能：判断选项所在的页面，并跳转到对应页面 
*	参数：int page为页面标识符					
*	调用：在空白页面时调用此函数，用于返回原来的页面 
*	作者：Mxx
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
*   函数： void RedirectPage(int page)
*	功能：判断是否登录成功，然后跳转到对应页面 
*	参数：int page为页面标识符					
*	调用：确认登录时调用此函数 
*	作者：Mxx
*******************************************/  
void RedirectPage(int page)
{
	system("cls"); 
	COORD Pos = {20,3};
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Handle_Out,Pos); 
	switch(page)
	{
		case 0: printf("修改昵称成功！3秒后将跳转..."); break;
		case 1: printf("修改密码成功！3秒后将跳转..."); break;  
		case 2: printf("注册成功！3秒后将跳转..."); break;  //表示用户注册成功 
		case 3: printf("登录成功！3秒后将跳转..."); break;	//表示用户登录成功 		 
		case 4: printf("登录成功！3秒后将跳转..."); break;  //表示管理员登录成功 
		default: printf("登录失败！3秒后将返回..."); break; //表示用户登录失败
	} 
	
	Sleep(1500);	//等待1.5秒 
	switch(page)
	{
		case 0: UserMenu_MyInfo_Option(); break; 
		case 1: UserMenu_MyInfo_Option(); break;  
		case 2: SignInMenu_Option(); break;  //注册成功则跳转登录界面 
		case 3: UserMenu_Option(); break;	//表示用户登录成功 		 
		case 4: AdminMenu_Option(); break;      //表示管理员登录成功 
		default: BlankMenu_Option(page); break; 
	} 
}

 
/*******************************************
*   函数：JudgeUserInfo(struct STUDENT_INFO Student_Info,int signup_or_signin)
*	功能：判断用户输入的信息是否满足要求，并给出相应的告示 
*	参数：参数：1.学生信息结构体Student_Info,包括手机，用户名，学号，密码等 2.signup_or_signin为状态量					
*	调用：确认注册或确认登录时调用此函数，返回值1表示满足要求，0表示不满足要求 
*	作者：Mxx
*******************************************/ 
int JudgeUserInfo(struct STUDENT_INFO Student_Info,int signup_or_signin)
{
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetCursorPosition(Handle_Out,20,12); 
	SetConsoleTextAttribute(Handle_Out,0x74);	//红色文字醒目 
	if(signup_or_signin==SIGN_UP)
	{
		if(!(strcmp(Student_Info.phone," ") || strcmp(Student_Info.name," ") || strcmp(Student_Info.studnum," ") || strcmp(Student_Info.password," ") || strcmp(Student_Info.repassword," ")))
		{
			printf("    请不要留空！     ");
			return 0;
		} 	
		else if(strlen(Student_Info.phone)!=11)
		{
			printf("请输入正确的手机号码！");
			return 0;
		}
		else if(strlen(Student_Info.studnum)!=10)
		{
			printf("   请检查你的学号！   ");
			return 0;
		}
		else if(strcmp(Student_Info.password,Student_Info.repassword))
		{
			printf(" 两次密码输入不一致！ ");
			return 0;
		}
		else if(SeekStudentInfo(Student_Info,SIGN_UP)==true)
		{
			printf("    该账号已注册！    ");
			return 0; 
		}
	}
	else if(signup_or_signin==SIGN_IN)
	{
		if(!(strcmp(Student_Info.phone," ") || strcmp(Student_Info.password," ")))
		{
			printf(" 请输入账号与密码！   ");
			return 0;
		}
		else if(SeekStudentInfo(Student_Info,SIGN_IN)==false)
		{
			printf(" 账号或密码不正确！   ");
			return 0; 
		}
	}
	else
	{
		//管理员登录
		if(strcmp(Student_Info.name,"root") || strcmp(Student_Info.password,"123456")) 
		{
			printf(" 账号或密码不正确！   ");
			return 0; 
		}
	}
	SetConsoleTextAttribute(Handle_Out,0x70);	//恢复原来颜色 
	
	return 1;
}
 
 
/******************************************* 
*   函数：int SeekStudentInfo(struct STUDENT_INFO Student_Info,int signup_or_signin) 
*	功能：如果是注册则判断账号是否已存在，没有则创建一个新账户；如果是登录则判断账号是否正确。 
*		  signup_or_signin为1表示注册，为0表示登录 
*	参数：1.学生信息结构体Student_Info,包括手机，用户名，学号，密码等 2.signup_or_signin为状态量					
*	调用：在点击确认注册或确认登录后会调用此函数(被 JudgeUserInfo(Student_Info，signup_or_signin)函数调用) 
*		  对于注册：1表示已注册，即无法再注册。0表示为注册，即可以注册
*		  对于登录：1表示账号和密码正确，0表示账号或密码错误 
*	作者：Mxx
*******************************************/ 
int SeekStudentInfo(struct STUDENT_INFO Student_Info,int signup_or_signin)
{
	struct CONFIG Config;
	int user_numbers = 0;
	char secret_key[24];
	int ifSignup = 0;
	FILE *cg; 
	//从配置文件中读取用户的数量以及密钥 
	if((cg=fopen("config","rb"))!=NULL) 
	{
		fclose(cg);
		EnDecryptFile("config",myKey);		//如果文件存在则解密 
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
	//判断文件是否存在,不存在则创建一个 
	if((fp=fopen("student_info.dat","r"))==NULL) 
	{
		fp=fopen("student_info.dat","w");
		fclose(fp);
	} 
	EnDecryptFile("student_info.dat",secret_key);	//解密文件 
	fp=fopen("student_info.dat","rb");
    for(int i=0;i<user_numbers;i++)
		fread(&Student[i],sizeof(struct STUDENT_INFO),1,fp);  
   	fclose(fp);  	    	
	//SIGN_UP表示注册，SIGN_IN表示登录 
	if(signup_or_signin==SIGN_UP)
	{
		for(int i=0;i<user_numbers;i++)
		if(!(strcmp(Student[i].phone,Student_Info.phone) && strcmp(Student[i].studnum,Student_Info.studnum)))
			ifSignup = true;	//表示该账号已注册 
		if(ifSignup==false)
		{
			Student[user_numbers] = Student_Info;	//如果没注册则追加信息 
			user_numbers++;
		}
	}
	else
	{
		for(int i=0;i<user_numbers;i++)
		if(!(strcmp(Student[i].phone,Student_Info.phone) && strcmp(Student[i].studnum,Student_Info.phone)) && !strcmp(Student[i].password,Student_Info.password))
		{
			ifSignup = 1;	//如果账号与密码正确，则返回1
			GetUserInformation(Student[i],user_numbers,i);	//缓存信息到程序里以便外部调用 
		} 
	} 
	fp=fopen("student_info.dat","wb");
   	fwrite(&Student,sizeof(struct STUDENT_INFO),user_numbers,fp);
	fclose(fp);
	EnDecryptFile("student_info.dat",secret_key);	//加密文件 	
	//更新配置文件 
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
*   函数： int  GetUserInput(int *index , int menu_size)
*	功能：按 ↑光标向上，按 ↓光标向下，ESC键退出,Enter键确认 
*	参数：1.索引值菜单index 2.菜单的大小					
*	调用：在菜单选项操作页面调用此函数，以判断按键 
*	作者：Mxx
*******************************************/ 
int  GetUserInput(int *index , int menu_size)
{
	int ch = getch();
	switch(ch)
	{
		//如果选择上，那么光标向上移动 ，其他也同理 
		case UP : (*index > 0) ? (*index -= 1) : (*index = menu_size - 1);  break;		
		case DOWN : (*index < menu_size - 1) ? (*index += 1) : (*index = 0);  break;
		case LEFT : (*index > 0) ? (*index -= 1) : (*index = menu_size - 1);  break;		
		case RIGHT : (*index < menu_size - 1) ? (*index += 1) : (*index = 0);  break;
		//回车 
		case  ENTER: system("color 70"); return ENTER ;
		//ESC
		case ESC: system("color 70"); return ESC ;
	}
	return 0 ;
}


/*******************************************
*   函数：void CreatRandStr(char *str) 
*	功能：随机生成一段长字符串（作为密钥） 
*	参数：1.字符串str随机生成，长度为24位					
*	调用：需要随机密钥时调用此函数 
*	作者：Mxx
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
*   函数：void EnDecryptFile(char *file, char *secretKey) 
*	功能：根据密钥加密或解密文件（通过与或方式） 
*	参数：1.file为要加密或解密的文件 2.secretKey为一段字符密钥					
*	调用：在读取文件前调用此函数进行解密，读取/写入文件结束后调用此函数进行加密 
*	作者：Mxx
*******************************************/ 
void EnDecryptFile(char *file, char *secretKey)
{
	FILE *File,*TempFile;
	char buffer[21];  	//缓冲区，用于存放从文件读取的数据
	int readCount;  	//每次从文件中读取的字节数
	int	keyLen = strlen(secretKey);

	if((File = fopen(file, "rb"))==NULL)
		printf("File open failed!");		
	if((TempFile = fopen("temp", "wb"))==NULL)
		printf("File open failed!");
	// 不断地从文件中读取 keyLen 长度的数据，保存到buffer，直到文件结束
	while( (readCount=fread(buffer, 1, keyLen, File)) > 0 )
	{		
		for(int i=0; i<readCount; i++)
			buffer[i] ^= secretKey[i];	//对buffer中的数据逐字节进行异或运算
		fwrite(buffer, 1, readCount, TempFile);
	}	
	fclose(TempFile);fclose(File);
	//实现文件复制覆盖功能 
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
*   函数： void GetNowTime(char *now_time) 
*	功能：获取当前时间，并赋予传入的变量
*	参数：字符串					
*	调用：传入一个字符串，把当前时间按照一定的格式赋予该字符串
*	作者：Mxx
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
	
	EnDecryptFile("config",myKey);	//解密文件 
	cg=fopen("config","rb");
	fread(&Config,sizeof(struct CONFIG),1,cg);
	fclose(cg);
	user_numbers = Config.user_numbers;
	strcpy(secret_key,Config.secret_key);
	
	struct STUDENT_INFO Student[user_numbers+1];		 
	FILE *fp;		
	EnDecryptFile("student_info.dat",secret_key);	//解密文件 
	fp=fopen("student_info.dat","rb");
    for(int i=0;i<user_numbers;i++)
		fread(&Student[i],sizeof(struct STUDENT_INFO),1,fp);  
   	fclose(fp);  
	   	    	
	//修改用户信息：传入一个结构体，替换掉原来的结构体
	Student[seri_num] = Student_Info;
	
	fp=fopen("student_info.dat","wb");
   	fwrite(&Student,sizeof(struct STUDENT_INFO),user_numbers,fp);
	fclose(fp);
	EnDecryptFile("student_info.dat",secret_key);	//加密文件 	
	//更新配置文件 
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
	char *menu[] = {"确认","返回"};
	char *str[] = {"昵称","密码"};
	char new_str[20];
	int index = 0;
	printf("你确认修改%s吗？",str[status]);
	while(1)
	{
		for(int i=0;i<2;i++)
		{
			if(i == index)
			{
				SetConsoleTextAttribute(Handle_Out,0x90);  //蓝色 
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
						printf("请输入新的%s：",str[status]);
						gets(new_str);
						SetCursorPosition(Handle_Out,25,10);
						SetConsoleTextAttribute(Handle_Out,0x90);
						printf("[ 确认 ]");
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
					}	//确认
			case 1: UserMenu_ChangeInfo_Option(); break ;  	//返回		
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
