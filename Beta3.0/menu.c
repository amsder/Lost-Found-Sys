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

char myKey[24] = "^?z(躅婀0Z6O噈XyY涇Lc";
enum 
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	ENTER = 13,
	ESC = 27,
	SPACE = 32	//空格为32？ 
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
	"＊   失物墙   ＊",
	"＊   寻物墙   ＊",
	"＊ 已结束交易 ＊",
	"＊  用户信息  ＊",
	"＊  修改密码  ＊",
	"＊    留言    ＊",
	"＊    退出    ＊",
};

//游客菜单 
char *vistor_menu[] = 
{
	"＊   失物墙   ＊",
	"＊   寻物墙   ＊",
	"＊    返回    ＊",
};
 
//用户菜单 
char *user_menu[] = 
{
	"＊   失物墙   ＊",
	"＊   寻物墙   ＊",
	"＊  我的帖子  ＊",
	"＊  我的信息  ＊",
	"＊    留言    ＊",
	"＊    退出    ＊",
};  
 
//用户菜单之我的帖子
char *user_post_menu[] = 
{	
	"＊  我的帖子  ＊",
	"＊发布失物帖子＊",
	"＊发布寻物帖子＊",	 
	"＊    返回    ＊",
}; 

//用户菜单->我的帖子->失物帖子 
char *user_lost_or_find_post_menu[] = 
{	
	"名称：",
	"地点：", 
	"描述：",
	"具体描述：",
	"[卡片]",
	"[钥匙]",
	"[球类]",
	"[书本]",
	"[衣服]",
	"[其他]",
	"[确认发布]",
	"[ 返回 ]",
};

//用户菜单->发布帖子->选择类别 
char *category_post_menu[] = 
{	
	"卡片",
	"钥匙",
	"球类",
	"书本",
	"衣服",
	"其他", 
}; 
 
//帖子详情页面 
char *post_detail_menu[] = 
{	
	"名称：",
	"具体描述：",
	"所在地点",
	"拥有者：",
	"联系方式：",
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
}Menu_Title={"欢迎进入失物招领管理系统！","注册界面","登录界面","管理员登录界面","管理员管理界面","游客界面","用户管理界面","管理帖子","发布失物帖子","发布寻物帖子","我的信息","修改信息","帖子详情页面","修改密码界面","此页面暂无内容！"};

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

//建立一个结构体来存放系统配置 
struct CONFIG
{
	int user_numbers;
	int lost_numbers;	//失物帖子的数量 
	int find_numbers;	//寻物帖子的数量
	int message_numbers;	//用户给管理员的留言个数 
	char secret_key[24]; 
}Config;

//建立一个结构体存放学生信息 
struct STUDENT_INFO
{
	char phone[12];
	char name[20];
	char studnum[12];
	char password[20];
	char repassword[20];
};

//主要存放用户登录信息 
struct USER_INFO
{
	int user_numbers;	//人数 
	int user_seriNum;	//编号  
	struct STUDENT_INFO StudInfo; 	//存放学生信息的结构体指针 
}User_Info;

//丢失or寻找的物品 
struct POST_THING
{
	int visible;	//是否可见，不可见为结束的交易 
	char user_name[20];	//用户名字 
	char phone[12];		//用户电话 
	char item_name[12];	//物品的名字 
	char site[20];			//地点 
	char category[12];		//类别 
	char brief[20];		//简述 
	char detail[50];		//详细描述 
	char time[20];	//发布时的时间 
	char IDnumber[10]; //帖子的唯一编号 
}; 

//在程序里缓存帖子数据
struct POST
{
	int lost_numbers;
	int find_numbers;
	struct POST_THING *Lost;
	struct POST_THING *Find;
}Post; 

//用户给管理员留言的结构体 
struct USER_MESSAGE
{
	int visible;	//是否可见，表示管理员是否已解决用户问题（重置密码） 
	char user_name[20];	//留言者名字 
	char user_phone[12];
	char content[60];	//限制六十字符以下
	char time[20];
};

//用户留言榜结构体 
struct MESSAGE_BOARD
{
	char user_name[20];	//留言者名字 
	char user_phone[12];
	char content[60];	//限制六十字以下
	char time[20];
	char IDnumber[10];
};	

//每个用户都有留言空间，用于存放他人的留言 
struct WORD_SPACE
{
	char master_name[20];
	char master_phone[12];
	int message_numbers;
	struct MESSAGE_BOARD Message[15];	//能避免使用指针*Message则避免，特别涉及到多重结构体在文件上读取时 
};

/**** 含结构体参数的函数，必须在结构体之后定义 ****/
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


/*   主函数    */ 
int main()
{
	ConsoleSet();
	WelcomPage();	   
    StartMenu_Option();
	
    return 0;
}

/******************************************* 
*   函数： void ConsoleSet() 
*	功能：控制台设置 
*	参数：无					
*	调用：开始时调用此函数初始化控制台 
*	作者：xxx
*******************************************/ 
void ConsoleSet()
{		
	// 设置窗口大小 以及前景背景色 
    system("mode con cols=60 lines=20");	//60字符宽，20字符高 
    system("color 70");
	//设置控制台标题 
    SetConsoleTitleA("失物招领管理系统");
    //获取当前的句柄---设置为标准输出句柄 
    HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE); 
    //设置控制台字体的大小
	CONSOLE_FONT_INFOEX Font_Set;
	Font_Set.cbSize = sizeof(Font_Set);
	Font_Set.dwFontSize.X = 13;
	Font_Set.dwFontSize.Y = 28;
	Font_Set.FontWeight = 700;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &Font_Set);
	//设置窗口的显示位置 
	SMALL_RECT rect = {0, 0, 60, 20};
	SetConsoleWindowInfo(Handle_Out, 1, &rect); 
    //定义光标信息结构体   
	CONSOLE_CURSOR_INFO Corsor_Info; 
    //获取光标信息
    GetConsoleCursorInfo(Handle_Out, &Corsor_Info); 
	//设置光标大小   
    Corsor_Info.dwSize = 1; 
	//设置光标不可见 FALSE   
    Corsor_Info.bVisible = 0; 
    //设置(应用)光标信息
    SetConsoleCursorInfo(Handle_Out, &Corsor_Info); 
 } 
 
 
/******************************************* 
*   函数： void ShowMenu(char **menu , char *menu_title ,char menu_size, int index , char statusColor)
*	功能：展示菜单 
*	参数：1.字符串数组menu为要展示的菜单 2.字符串menu_title为菜单的标题
		  3.整型数menu_size为菜单的大小  3.整型数index为索引值					
*	调用：传入菜单有关的信息和索引值，就会展示出菜单页面 
*	作者：xxx
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
		}
		//否则显示为白色 
		else
			SetConsoleTextAttribute(Handle_Out,0x70); 
		SetCursorPosition(Handle_Out,22,4+i);    
    	printf("%s",menu[i]);
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
*	作者：xxx
*******************************************/ 
void StartMenu_Option(void)
{
	system("color 70");		//*暂时加上去的*// 
	system("cls");	//清空屏幕	
	//重新设置字体不加粗 
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
				case 0: VistorMenu_Option(); break;  	//游客访问 
				case 1: SignInMenu_Option(); break;  	    //用户登录 
				case 2: AdminLoginMenu_Option();break;  	//管理员登录 
				case 3: SignUpMenu_Option(); break;  	//注册
				case 4: exit(1);  break;  	//退出
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
				case 0: Gets(Student_Info.phone,12);  break;  	//手机号 
				case 1: Gets(Student_Info.name,20);   break;  	//用户名 
				case 2: Gets(Student_Info.studnum,12); break;  	//学号 
				case 3: Gets(Student_Info.password,20);break;  	//密码
				case 4: Gets(Student_Info.repassword,20); break;  //再次输入密码 
				case 5:	if(JudgeUserInfo(Student_Info,SIGN_UP)==true){RedirectPage(Page.signup_menu);} break;//确认注册 
				case 6: StartMenu_Option();  break;  	//返回		
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
				case 0: Gets(Student_Info.phone,12); break;  	//手机号或学号 
				case 1: Gets(Student_Info.password,20);  break;  	//密码 
				case 2: if(JudgeUserInfo(Student_Info,SIGN_IN)==true){RedirectPage(Page.signin_menu);} break; //确认登录 
				case 3: StartMenu_Option(); break;        	//返回
				case 4: SignUpMenu_Option();  break;   	//还没注册 
				case 5: AskforResetPassword();  break;  	//重置密码 
		
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
				case 0: Gets(Student_Info.name,20);  break;  	//账号 
				case 1: Gets(Student_Info.password,20);  break; //密码 
				case 2: if(JudgeUserInfo(Student_Info,LOGIN)==true){RedirectPage(Page.admin_login_menu);} break;//确认登录 
				case 3: StartMenu_Option(); break;        	//返回		
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
		int user_input = GetUserInput(&index , MenuLength(admin_menu) ,1);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: ShowPostWall(Post.Lost, Page.admin_menu, LOST, 1, 1, 0); break;  	//失物墙  
				case 1: ShowPostWall(Post.Find, Page.admin_menu, FIND, 1, 1, 0); break;  	//寻物墙
				case 2: ShowOverPost(1, 1, 0); break;  	//已结束交易
				case 3: ViewUserInfo(); break;  	//用户信息 
				case 4: ChangePasswordMenu_Option(); break;			//修改密码 
				case 5: ShowUserMessage(); break;		//留言 
				case 6: StartMenu_Option(); 	break; 	//退出 
		
			}
		}
	} 
} 

//管理员界面选项操作  *格式同上面* 
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
				case 0: ShowPostWall(Post.Lost, Page.vistor_menu, LOST, 1, 1, 0); break;  	//失物墙  
				case 1: ShowPostWall(Post.Find, Page.vistor_menu, FIND, 1, 1, 0); break;  	//寻物墙
				case 2: StartMenu_Option(); 	break; 	//返回 
		
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
		int user_input = GetUserInput(&index , MenuLength(user_menu) ,1);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: ShowPostWall(Post.Lost, Page.user_menu, LOST, 1, 1, 0); break;  	//失物墙 
				case 1: ShowPostWall(Post.Find, Page.user_menu, FIND, 1, 1, 0); break;  	//寻物墙
				case 2: ShowUserPost(1, 1, 0); break;			//我的帖子
				case 3: UserMenu_MyInfo_Option(); break;  		//我的信息 
				case 4: ShowLeaveWord();		//留言 
				case 5: StartMenu_Option(); break; 	//退出 
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
		int user_input = GetUserInput(&index , MenuLength(user_myinfo_menu) ,1);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: puts(User_Info.StudInfo.phone); break;  	//手机号 
				case 1: puts(User_Info.StudInfo.studnum); break;  	//学号 
				case 2: puts(User_Info.StudInfo.name); break;  	//昵称 
				case 3: puts(User_Info.StudInfo.password); break;  //密码 
				case 4: UserMenu_ChangeInfo_Option(); break;		//修改 
				case 5: UserMenu_Option(); break;		//返回
				case 6: StartMenu_Option(); break; 	//退出 
		
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
		int user_input = GetUserInput(&index , MenuLength(user_change_info_menu) ,1);
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
		int user_input = GetUserInput(&index , MenuLength(change_password_menu) ,1);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0:  ChangeAdminPassword(); break;  	//修改我的密码 
				case 1:  ResetUserPasswordPage(); break;  	//重置用户密码 
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
		int user_input = GetUserInput(&index , MenuLength(blank_menu) ,1);
		if(user_input == ESC)
			exit(1) ;
		if(user_input == ENTER)
		{
			switch(index)
			{
				case 0: JudgePage(page); break;  	//返回上一级 
				case 1: exit(1);   		 break;  	//直接退出 
			}
		}
	}
} 


/******************************************* 
*   函数： void JudgePage(int page)
*	功能：判断选项所在的页面，并跳转到对应页面 
*	参数：int page为页面标识符					
*	调用：在空白页面时调用此函数，用于返回原来的页面 
*	作者：xxx
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
*   函数： void RedirectPage(int page)
*	功能：判断是否登录成功，然后跳转到对应页面 
*	参数：int page为页面标识符					
*	调用：确认登录时调用此函数 
*	作者：xxx
*******************************************/  
void RedirectPage(int page)
{
	system("cls"); 
	COORD Pos = {18,3};
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Handle_Out,Pos); 
	switch(page)
	{
		case 0: printf("修改昵称成功！3秒后将跳转..."); break;
		case 1: printf("修改密码成功！3秒后将跳转..."); break;  
		case 2: printf("注册成功！3秒后将跳转..."); break;  //表示用户注册成功 
		case 3: printf("登录成功！3秒后将跳转..."); break;	//表示用户登录成功 		 
		case 4: printf("登录成功！3秒后将跳转..."); break;  //表示管理员登录成功 
		case 5: printf("导出数据成功！3秒后将跳转..."); break;
		case 6: printf("重置密码成功！3秒后将跳转..."); break;
		case 7: printf("发布成功！3秒后将跳转..."); break;
		case 8: printf("修改成功！3秒后将跳转..."); break;
		case 9: printf("删除帖子成功！3秒后将跳转..."); break;
		case 10: printf("导出数据成功！3秒后将跳转..."); break;
		case 11: printf("导出数据成功！3秒后将跳转..."); break;
		case 12: printf("留言成功！3秒后将跳转..."); break;
		case 13: printf("提交申请成功！3秒后将跳转..."); break;
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
*   函数：JudgeUserInfo(struct STUDENT_INFO Student_Info,int signup_or_signin)
*	功能：判断用户输入的信息是否满足要求，并给出相应的告示 
*	参数：参数：1.学生信息结构体Student_Info,包括手机，用户名，学号，密码等 2.signup_or_signin为状态量					
*	调用：确认注册或确认登录时调用此函数，返回值1表示满足要求，0表示不满足要求 
*	作者：xxx
*******************************************/ 
int JudgeUserInfo(struct STUDENT_INFO Student_Info,int signup_or_signin)
{
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetCursorPosition(Handle_Out,20,12); 
	SetConsoleTextAttribute(Handle_Out,0x74);	//红色文字醒目 
	if(signup_or_signin==SIGN_UP)
	{
		if(!(strcmp(Student_Info.phone,"") && strcmp(Student_Info.name,"") && strcmp(Student_Info.studnum,"") && strcmp(Student_Info.password,"") && strcmp(Student_Info.repassword,"")))
		{
			printf("    请不要留空！     ");	//任意一个为空都不行 
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
		if(!(strcmp(Student_Info.phone,"") || strcmp(Student_Info.password,"")))
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
*	作者：xxx
*******************************************/ 
int SeekStudentInfo(struct STUDENT_INFO Student_Info,int signup_or_signin)
{
	int ifSignup = 0;
    int user_numbers = Config.user_numbers;
	struct STUDENT_INFO Student[user_numbers+1];	 			 
	FILE *fp;			
	//判断文件是否存在,不存在则创建一个 
	if((fp=fopen("student_info.dat","r"))==NULL) 
	{
		fp=fopen("student_info.dat","w");
		fclose(fp);
	} 
	EnDecryptFile("student_info.dat",myKey);	//解密文件 
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
		//只有用户新注册时才为其开辟一个留言空间 
		if(ifSignup==false)
		{
			FILE *fp1;		
			struct WORD_SPACE WSpace[user_numbers];	
			//判断文件是否存在,不存在则创建一个 
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
		   	//每当注册一个新用户时就自动为其分配一个留言空间，并初始化 
		   	strcpy(WSpace[user_numbers-1].master_name,Student_Info.name);
		   	strcpy(WSpace[user_numbers-1].master_phone,Student_Info.phone);
			WSpace[user_numbers-1].message_numbers = 0;	//开始时留言为0 
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
			EnDecryptFile("leave_word.dat",myKey);	//加密文件
		}
	}
	else if(signup_or_signin==SIGN_IN)
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
	EnDecryptFile("student_info.dat",myKey);	//加密文件 	
	//更新配置文件 
	Config.user_numbers = user_numbers;
    FILE *cg;
	cg=fopen("config","wb");
	fwrite(&Config,sizeof(struct CONFIG),1,cg);
	fclose(cg);
	EnDecryptFile("config",myKey);
	return ifSignup;	
}  
 
//获得用户登录信息 
void GetUserInformation(struct STUDENT_INFO Student_Info,int user_numbers,int seri_num)
{
	User_Info.StudInfo = Student_Info;
	User_Info.user_seriNum = seri_num;
	User_Info.user_numbers = user_numbers; 	
} 
 
/******************************************* 
*   函数： int  GetUserInput(int index , int menu_size , int status)
*	功能：按 ↑光标向上，按 ↓光标向下，ESC键退出,Enter键确认 
*	参数：1.索引值菜单index 2.菜单的大小 3.status为1表示上下按键，为0表示左右按键 2都可以					
*	调用：在菜单选项操作页面调用此函数，以判断按键 
*	作者：xxx
*******************************************/ 
int  GetUserInput(int *index , int menu_size , int status)
{
	int ch = getch();
	if(status!=2)
	switch(ch)
	{
		//如果选择上，那么光标向上移动 ，其他也同理 
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
*   函数：void CreatRandStr(char *str) 
*	功能：随机生成一段长字符串（作为帖子编号） 
*	参数：1.字符串str随机生成，长度为5位					
*	调用：发表帖子时调用此函数 
*	作者：xxx
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
*   函数：void EnDecryptFile(char *file, char *secretKey) 
*	功能：根据密钥加密或解密文件（通过与或方式） 
*	参数：1.file为要加密或解密的文件 2.secretKey为一段字符密钥					
*	调用：在读取文件前调用此函数进行解密，读取/写入文件结束后调用此函数进行加密 
*	作者：xxx
*******************************************/ 
void EnDecryptFile(char *file, char *secretKey)
{
	FILE *File,*TempFile;
	char buffer[21];  	//缓冲区，用于存放从文件读取的数据
	int readCount;  	//每次从文件中读取的字节数
	int	keyLen = strlen(secretKey);

	if((File = fopen(file, "rb"))==NULL)
	{
		fclose(File);
		File = fopen(file,"wb");
	}		
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
*	作者：xxx
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
*   函数： void ChangeUser_Name_Password(char *name_or_password,int status)
*	功能：修改用户的昵称或密码 
*	参数：1.name_or_password为要替换的字符串 2.status为1表示修改昵称，status为2表示修改密码					
*	调用：被ChangeUserInfoPage(status)函数调用 
*	作者：xxx
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
*   函数：void ChangeUserInfoPage(int status)
*	功能：修改用户的昵称或密码的页面，获得用户输入的字符串，并完成修改 
*	参数：2.status为1表示修改昵称，status为2表示修改密码					
*	调用：用户修改昵称或密码时调用函数 
*	作者：xxx
*******************************************/ 
void ChangeUserInfoPage(int status)
{
	system("cls");
	COORD Pos = {21,4};
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Handle_Out,Pos); 
	char *menu[] = {"确认","返回"};
	char *str[] = {"昵称","密码"};
	char new_str[20]="";
	int index = 0;
	printf("你确认修改%s吗？",str[status]);
	while(1)
	{
		for(int i=0;i<2;i++)
		{
			if(i == index)
				SetConsoleTextAttribute(Handle_Out,0x90);  //蓝色 
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
						printf("请输入新的%s：",str[status]);
						Gets(new_str,20);
						//判断字符串的长度
						while(strlen(new_str)<3)
						{
							SetCursorPosition(Handle_Out,19,12);
							SetConsoleTextAttribute(Handle_Out,0x74);
							printf("%s长度不能小于三位！",str[status]);
							SetCursorPosition(Handle_Out,32,9);
							SetConsoleTextAttribute(Handle_Out,0x70);
							printf("------------");
							SetCursorPosition(Handle_Out,16,8);
							printf("请输入新的%s：     ",str[status]);
							SetCursorPosition(Handle_Out,32,8);
							Gets(new_str,20);
						} 
						SetCursorPosition(Handle_Out,19,12);
						printf("                    ",str[status]);
						SetCursorPosition(Handle_Out,25,11);
						SetConsoleTextAttribute(Handle_Out,0x90);
						printf("[ 确认 ]");
						SetConsoleTextAttribute(Handle_Out,0x70);						
						ChangeUser_Name_Password(new_str,status);
						RedirectPage(status); 
					}	//确认
			case 1: UserMenu_ChangeInfo_Option(); break ;  	//返回		
		}
	}		 
}

/******************************************* 
*   函数： void  SetCursorPosition(HANDLE Handle_Out , int x , int y)
*	功能：设置光标的位置（x,y） 
*	参数：x为横坐标，y为纵坐标					
*	调用：设置光标位置时调用此函数 
*	作者：xxx
*******************************************/
void  SetCursorPosition(HANDLE Handle_Out , int x , int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(Handle_Out,Pos);
 } 
 
/******************************************* 
*   函数： void ViewUserInfo(void)
*	功能：查看用户信息 
*	参数：无					
*	调用：需要查看用户信息时调用此函数 
*	作者：Mxxx
*******************************************/
 void ViewUserInfo(void)
 {
	int user_numbers = Config.user_numbers;
	struct STUDENT_INFO Student[user_numbers];	//	 
	FILE *fp;		
	EnDecryptFile("student_info.dat",myKey);	//解密文件 
	fp=fopen("student_info.dat","rb");
    for(int i=0;i<user_numbers;i++)
		fread(&Student[i],sizeof(struct STUDENT_INFO),1,fp);  
   	fclose(fp);  	   	    		
	EnDecryptFile("student_info.dat",myKey);	//加密文件 	
			 		
	ShowUserInfo(Student,user_numbers);
 }
 
/******************************************* 
*   函数： void ChangeStudentInfo(struct STUDENT_INFO Student_Info,int seri_num)
*	功能：改变用户信息 
*	参数：1.Student_Info为要代替的结构体 2.seri_num为该结构体在Student[]中的索引值					
*	调用：需要改变用户信息时调用此函数 
*	作者：xxx
*******************************************/ 
void ChangeStudentInfo(struct STUDENT_INFO Student_Info,int seri_num)
{	
	int user_numbers = Config.user_numbers;	
	struct STUDENT_INFO Student[user_numbers];		 
	FILE *fp;		
	EnDecryptFile("student_info.dat",myKey);	//解密文件 
	fp=fopen("student_info.dat","rb");
    for(int i=0;i<user_numbers;i++)
		fread(&Student[i],sizeof(struct STUDENT_INFO),1,fp);  
   	fclose(fp);  
	   	    	
	//修改用户信息：传入一个结构体，替换掉原来的结构体
	Student[seri_num] = Student_Info;
	fp=fopen("student_info.dat","wb");
	fwrite(&Student,sizeof(struct STUDENT_INFO),user_numbers,fp);
	fclose(fp);	
	EnDecryptFile("student_info.dat",myKey);	//加密文件 	 
}
 
/******************************************* 
*   函数： void ShowUserInfo(struct STUDENT_INFO *Student,int user_numbers)
*	功能：展示用户信息,并有一键导出用户数据的选项 
*	参数：1.Student_Info为结构体数组 2.user_numbers为用户总数量				
*	调用：管理员查看用户信息时调用此函数 
*	作者：xxx
*******************************************/ 
void ShowUserInfo(struct STUDENT_INFO *Student,int user_numbers)
{	
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE); 
	int index = 0, a = 0;
	char *menu[] = {"[ 返回 ]","[ 导出数据 ]"};
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
		printf("用户信息");
		SetCursorPosition(Handle_Out,0,3);
		printf("    ┏━━━━━┏━━━━━━━━━┏━━━━━━━━━━━━━━━┏━━━━━━━━━━━━━━━┓ \n");
		printf("    ┃ 编号┃  名字   ┃     学号      ┃     手机号    ┃ \n");
		printf("    ┃━━━━━┃━━━━━━━━━┃━━━━━━━━━━━━━━━┃━━━━━━━━━━━━━━━┃ \n");
		if(user_numbers>12)
			for(int i=a;i<a+12;i++)
				printf("    ┃  %.2d ┃ %-8s┃  %-13s┃  %-13s┃ \n",i+1,Student[i].name,Student[i].studnum,Student[i].phone);
		else
			for(int i=0;i<user_numbers;i++)
				printf("    ┃  %.2d ┃ %-8s┃  %-13s┃  %-13s┃ \n",i+1,Student[i].name,Student[i].studnum,Student[i].phone);
		printf("    ┗━━━━━┗━━━━━━━━━┗━━━━━━━━━━━━━━━┗━━━━━━━━━━━━━━━┛ \n"); 
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
*   函数： void ExportUserInfo(struct STUDENT_INFO *Student,int user_numbers)
*	功能：导出用户数据 
*	参数：1.Student_Info为结构体数组 2.user_numbers为用户总数量				
*	调用：管理员查看用户信息时调用此函数导出所有用户注册数据到本地表格 
*	作者：xxx
*******************************************/
void ExportUserInfo(struct STUDENT_INFO *Student,int user_numbers)
{
	FILE *fp;
	if((fp = fopen("导出用户数据.xls","w"))!=NULL)
	{
		fprintf(fp,"编号\t名字\t学号\t手机号\n");
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
*   函数： int ResetUserPassword(char *phone_or_stdnum,int status)
*	功能：查看某用户是否存在，并可选择重置其密码为手机号 
*	参数：1.字符串phone_or_stdnum为传入的学号或手机号 2.user_numbers为状态参数				
*	调用：重置密码前可选择调用此函数判断用户是否存在。函数参数stetue取1直接重置密码，取0不重置密码 
*	作者：xxx
*******************************************/
int ResetUserPassword(char *phone_or_stdnum,int status)
{
	int ifSuccess = 0; 
	int user_numbers = Config.user_numbers;
	struct STUDENT_INFO Student[user_numbers];		 
	FILE *fp;			
	//判断文件是否存在,不存在则创建一个 
	if((fp=fopen("student_info.dat","r"))==NULL) 
	{
		fp=fopen("student_info.dat","w");
		fclose(fp);
	} 
	//解密文件并读取 
	EnDecryptFile("student_info.dat",myKey);	
	fp=fopen("student_info.dat","rb");
    for(int i=0;i<user_numbers;i++)
		fread(&Student[i],sizeof(struct STUDENT_INFO),1,fp);  
   	fclose(fp); 
	//判断该用户是否存在 
	for(int i=0;i<user_numbers;i++)   
	if(!(strcmp(Student[i].phone,phone_or_stdnum) && strcmp(Student[i].studnum,phone_or_stdnum)))
	{
		//表示该用户存在,那么则重置密码为学号 
		ifSuccess = true;
		if(status)
			strcpy(Student[i].password,Student[i].studnum); 
	} 
	//重新写入文件并加密	    		 
	fp=fopen("student_info.dat","wb");
   	fwrite(&Student,sizeof(struct STUDENT_INFO),user_numbers,fp);
	fclose(fp);
	EnDecryptFile("student_info.dat",myKey);

	return ifSuccess;	
} 
 
 
/******************************************* 
*   函数： void ResetUserPasswordPage(void)
*	功能：重置密码显示页面，可选择重置或不重置密码 
*	参数：无				
*	调用：管理员要重置用户密码时调用此函数 （在修改密码页面调用） 
*	作者：xxx
*******************************************/
void ResetUserPasswordPage(void) 
{
	system("cls");
	COORD Pos = {14,2};
	char str[12];
	int index = 0;
	char *menu[] = {"[确认]","[返回]"};
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Handle_Out,Pos);
	printf("请输入要重置的用户（学号或手机号）");
	SetCursorPosition(Handle_Out,20,4);	
	printf(":");	
	SetCursorPosition(Handle_Out,21,5);
	printf("--------------------");	
	SetCursorPosition(Handle_Out,26,6);
	printf("[ 确认 ]");	
	SetCursorPosition(Handle_Out,24,4);
	SetConsoleTextAttribute(Handle_Out,0x75);	//紫色字体 
	Gets(str,12);
	SetConsoleTextAttribute(Handle_Out,0x90);
	SetCursorPosition(Handle_Out,26,6);
	printf("[ 确认 ]");
	SetConsoleTextAttribute(Handle_Out,0x70);
	if(ResetUserPassword(str,0)==true)
	{
		SetCursorPosition(Handle_Out,26,6);
		printf("[ 确认 ]");
		SetCursorPosition(Handle_Out,18,8);
		printf("该用户存在，是否立即重置？");		
		while(1)
		{
			for(int i=0;i<2;i++)
			{
				if(i == index)
					SetConsoleTextAttribute(Handle_Out,0x90);  //蓝色 
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
		printf("[ 确认 ]");
		SetCursorPosition(Handle_Out,18,8);
		printf("该用户不存在！是否重新输入？");
		while(1)
		{
			for(int i=0;i<2;i++)
			{
				if(i == index)
					SetConsoleTextAttribute(Handle_Out,0x90);  //蓝色 
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


//用户->我的帖子->发布帖子界面选项操作  *格式同上面* 
void UserMenu_PubPost_Option(int status)
{
	system("cls");	//清空屏幕 
	char time[20];
	char len = strlen(Menu_Title.user_lost_post_menu);
	GetNowTime(time);
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,(WIDTH-len)/2,0);
	if(status==LOST)    
		printf("%s",Menu_Title.user_lost_post_menu);	//打印标题 
	else
		printf("%s",Menu_Title.user_find_post_menu);
	SetCursorPosition(Handle_Out,23,1);
	printf("%s",time);
	
	int y = 0;
	int value = 0;	//数字对应第几个类别 
	int menu_size = MenuLength(user_lost_or_find_post_menu);	//12
	char statusColor = 1;
	struct POST_THING Post_Thing = {1,"","","","","","","","",""};		//可见
	strcpy(Post_Thing.user_name,User_Info.StudInfo.name);	//发布时的名字为用户名字
	strcpy(Post_Thing.phone,User_Info.StudInfo.phone);		//发布时的电话为用户电话	
	 	
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
					case 0: Gets(Post_Thing.item_name,20); break ; 	//物品名称 
					case 1: Gets(Post_Thing.site,20); break ;  	//地点
					case 2: Gets(Post_Thing.brief,20); break ;  	//描述
					case 3: Gets(Post_Thing.detail,50); break ;  	//具体描述
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
					
					case 11: ShowUserPost(1,1,0); break;	//返回 
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

//发布帖子窗口	
void UserMenu_PubPost_OptionShow(int y , int statusColor)
{
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	for(int i=0;i<4;i++)
	{
		if(i == y)
		{
			if(statusColor==1)			
				SetConsoleTextAttribute(Handle_Out,0x90);  //浅蓝色 
			else
				SetConsoleTextAttribute(Handle_Out,0x10);  //蓝色 			
		} 
		else
			SetConsoleTextAttribute(Handle_Out,0x70); 
		SetCursorPosition(Handle_Out,22,4+i);    
    	printf("%s",user_lost_or_find_post_menu[i]);
	}
	SetConsoleTextAttribute(Handle_Out,0x70);
	SetCursorPosition(Handle_Out,22,9);
	printf("选择类别：");
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
			SetConsoleTextAttribute(Handle_Out,0x90);  //蓝色 
		else
			SetConsoleTextAttribute(Handle_Out,0x70); 
    	SetCursorPosition(Handle_Out,14+25*(i-10),15);
    	printf("%s",user_lost_or_find_post_menu[i]);
	}
}

//检查发布的帖子是否规范
int JudgePostInfo(struct POST_THING Post_Thing)
{
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out,0x75);
	SetCursorPosition(Handle_Out,22,13);
	if(!strcmp(Post_Thing.item_name,""))
	{
		printf("请填写物品的名称！");
		return 0;
	} 
	if(!strcmp(Post_Thing.site,""))
	{
		printf("请填写物品的地点！");
		return 0;
	}		
	if(!strcmp(Post_Thing.brief,""))
	{
		printf("请填写物品的描述！");
		return 0;
	}		
	if(!strcmp(Post_Thing.category,""))
	{
		printf("请选择物品的类别！");
		return 0;
	}		
	SetConsoleTextAttribute(Handle_Out,0x70);
	return 1;
} 

//存放失物信息	*先读取再写入
void WriteLostInfo(struct POST_THING Lost_Thing)
{	
	//加上帖子的编号   
	char rdnum[5];
	CreatRandStr(rdnum);
	sprintf(Lost_Thing.IDnumber,"S%s%d",rdnum,Post.lost_numbers);
	
	//更新帖子信息 
	Post.lost_numbers++;
	Post.Lost = realloc(Post.Lost,Post.lost_numbers*sizeof(struct POST_THING));
	Post.Lost[Post.lost_numbers-1] = Lost_Thing; 
	//他大爷的居然不能传递原来的地址，非要我弄个中间变量才不出错  
	struct POST_THING Lost[Post.lost_numbers];
	for(int i=0;i<Post.lost_numbers;i++)
		Lost[i] = Post.Lost[i];	    	
	FILE *fp;
	fp=fopen("lost_info.dat","wb");
   	fwrite(&Lost,sizeof(struct POST_THING),Post.lost_numbers,fp);
	fclose(fp);
	EnDecryptFile("lost_info.dat",myKey);	//加密文件 
			
	//更新配置文件 
	FILE *cg; 
	Config.lost_numbers = Post.lost_numbers;
	cg=fopen("config","wb");
	fwrite(&Config,sizeof(struct CONFIG),1,cg);
	fclose(cg);
	EnDecryptFile("config",myKey);		
} 
 

//存放寻物信息	*先读取再写入
void WriteFindInfo(struct POST_THING Find_Thing)
{
	//加上帖子的编号   
	char rdnum[5];
	CreatRandStr(rdnum);
	sprintf(Find_Thing.IDnumber,"X%s%d",rdnum,Post.find_numbers);
	
	//更新帖子信息 
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
	EnDecryptFile("find_info.dat",myKey);	//加密文件 
			
	//更新配置文件 
	FILE *cg;
	Config.find_numbers = Post.find_numbers;
	cg=fopen("config","wb");
	fwrite(&Config,sizeof(struct CONFIG),1,cg);
	fclose(cg);
	EnDecryptFile("config",myKey);		 	
} 
 

//展示失物墙/寻物墙 
void ShowPostWall(struct POST_THING *TPost, int page , int status , int pos, int aa, int bb)
{
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE); 
	int index = pos , a = aa , b = bb , post_numbers = 0;	//index为类别，a为翻页效果，b为详情切换 /*/a=1
	int menu_size = 9;
	int n = 1;	//n代表某类别的帖子的数量 
	int flash = 0;	//刷新为false 
	int post_visible_num = 0;	//可见帖子的数量 
	char *menu[] = {"[ 返回 ]","[全部]","[卡片]","[钥匙]","[球类]","[书本]","[衣服]","[其他]","[ 我的 ]"};	
	int cat[6] = {0,0,0,0,0,0};		//某一类帖子的长度 
	(status==LOST)?(post_numbers=Post.lost_numbers):(post_numbers=Post.find_numbers);
	struct POST_THING Post_Cat[6][post_numbers],Post_Visible[post_numbers];	//将所有帖子分成六类   //可见的帖子 
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
			printf("失物墙");
		else 
			printf("寻物墙");
		SetCursorPosition(Handle_Out,0,4);
		printf(" ----------------------------------------------------------\n");
		SetCursorPosition(Handle_Out,0,5);
		printf(" 编号   名称       简介\t\t        地点\n");
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
					SetConsoleTextAttribute(Handle_Out,0x90);	//蓝色 
				else
					SetConsoleTextAttribute(Handle_Out,0x70);	//白色
				SetCursorPosition(Handle_Out,54,7+i);
				printf("[详情]"); 
				if(b>=12)
				{
					SetConsoleTextAttribute(Handle_Out,0x90);
					SetCursorPosition(Handle_Out,54,7+11);
					printf("[详情]");
				}
			}
			n = cat[i-2];
		}
		
		if(index==1)
		{
			//展示所有可见帖子 
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
					SetConsoleTextAttribute(Handle_Out,0x90);	//蓝色 
				else
					SetConsoleTextAttribute(Handle_Out,0x70);	//白色
				SetCursorPosition(Handle_Out,54,7+i);
				printf("[详情]"); 
				if(b>=12)
				{
					SetConsoleTextAttribute(Handle_Out,0x90);
					SetCursorPosition(Handle_Out,54,7+11);
					printf("[详情]");
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
				flash = 0;	//按上下键时不刷新帖子 
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
				b = 0;	//使类别切换时光标总是在第一项	
				a = 1;	//切换时a必须>=0防止索引值出现负数！ 
				flash = 1;	//按左右键时刷新							
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
							ShowPostWall(TPost, page, status, pos, a, b);	//返回原来界面 
					}
					else if(index==1 && n!=0) {PostDetailPage(Post_Visible[b], page ,status , index, a, b);}
					else if(index>1&&index<8 && cat[index-2]!=0) {PostDetailPage(Post_Cat[index-2][b], page ,status , index, a, b);}	
			} break;
		}
	}
}

//展示帖子详情页面 
void PostDetailPage(struct POST_THING Post_Thing , int page , int status , int pos, int a, int b)
{
	system("cls");	//清空屏幕 
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	int index = 0;
	char *menu[]={"[给他留言]","[ 返回 ]"}; 
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,24,0);
	printf("帖子详情页面");
	
	//物品名字 
	SetCursorPosition(Handle_Out,20,3);
	printf("名称：%s",Post_Thing.item_name);
	//物品编号 
	SetCursorPosition(Handle_Out,20,4);
	printf("编号：%s",Post_Thing.IDnumber);
	//具体地点	
	SetCursorPosition(Handle_Out,20,5);
	printf("所在地点：%s",Post_Thing.site);
	//简介
	SetCursorPosition(Handle_Out,20,6);
	printf("简要介绍：%s",Post_Thing.brief);
	//所在描述
	SetCursorPosition(Handle_Out,20,7);
	printf("具体描述：%s",Post_Thing.detail);  
	SetCursorPosition(Handle_Out,10,9);
	printf("----------------------------------------");
	//发布时间 
	SetCursorPosition(Handle_Out,20,10);
	printf("时间：%s",Post_Thing.time);
	//拥有者
	SetCursorPosition(Handle_Out,20,11);
	printf("发布者：%s",Post_Thing.user_name);
	//联系方式
	SetCursorPosition(Handle_Out,20,12);
	printf("联系方式：%s",Post_Thing.phone); 
		
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
			//确认留言 
			if(index==0)
			{
				if(JudgeIsSignin(page))
					LeaveWord(Post_Thing, page, status, pos, a, b);
				else
					PostDetailPage(Post_Thing, page, status, pos, a, b);	//如为登录且也不登录则返回原来的页面					
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

//只有用户才能查看我的帖子 
void ShowUserPost(int pos, int aa, int bb)
{		
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE); 
	int index = pos , a = aa , b = bb;	//index为类别，a为翻页效果，b为详情切换 
	int menu_size = 7;
	int flash=0;	//刷新帖子 
	int n = 1;	//n代表某类别的帖子的数量 
	char *menu[] = {"[ 返回 ]","[失物贴]","[寻物贴]","[结束贴]","[导出数据]"};
	char *pubPost[] = {"[发布寻物帖子]","[发布失物帖子]"}; 
	int max=0;
	(Post.lost_numbers>Post.find_numbers) ? (max=Post.lost_numbers) : (max=Post.find_numbers);
	struct POST_THING Post_Cat[3][Post.lost_numbers+Post.find_numbers];	//某个人删除的帖子总不至于比总帖子数量还多吧 
	int cat[3] = {0,0};		//帖子的长度 
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
		printf("我的帖子");
		SetCursorPosition(Handle_Out,0,3);
		printf(" ----------------------------------------------------------\n");
		SetCursorPosition(Handle_Out,0,4);
		printf(" 编号   名称       简介\t\t        地点\n");
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
					SetConsoleTextAttribute(Handle_Out,0x90);	//蓝色 
				else
					SetConsoleTextAttribute(Handle_Out,0x70);	//白色
				SetCursorPosition(Handle_Out,54,6+j);
				if(i==3){
					SetConsoleTextAttribute(Handle_Out,0x70);
					if(pos==1)
						printf("[失物]");
					else
						printf("[寻物]"); 
				}
				else 
					printf("[查看]"); 
				if(b>=13)
				{
					SetConsoleTextAttribute(Handle_Out,0x90);
					SetCursorPosition(Handle_Out,54,6+12);
					if(i==3){					
						SetConsoleTextAttribute(Handle_Out,0x70);
						if(pos==1)
							printf("[失物]");
						else
							printf("[寻物]"); 
					}
					else 
						printf("[查看]"); 
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
					else if(index==1 && cat[index-1]!=0) {ViewMyPostPage(Post_Cat[index-1][b], index, a, b);}	//希望结构体数组的地址没有被释放掉吧 
					else if(index==2 && cat[index-1]!=0) {ViewMyPostPage(Post_Cat[index-1][b], index, a, b);}
					else if(index==3) {;} //已结束的帖子 
					else if(index==4) {
					ExportMyPostInfo(Post_Cat[0],cat[0],"失物", "w");
					ExportMyPostInfo(Post_Cat[1],cat[1],"寻物", "a");
					ExportMyPostInfo(Post_Cat[2],cat[2],"已结束","a");
					RedirectPage(10);
					}
					else if(index==5) {UserMenu_PubPost_Option(FIND);}
					else if(index==6) {UserMenu_PubPost_Option(LOST);}		
			} break;
		}
	}
}

//查看我的帖子 
void ViewMyPostPage(struct POST_THING Post_Thing, int pos, int a, int b)
{
	system("cls");	//清空屏幕 
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	int index = 0;
	char *menu[]={"[修改帖子]","[ 返回 ]","[删除帖子]"}; 
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,24,0);
	printf("帖子详情页面");
	
	//物品名字 
	SetCursorPosition(Handle_Out,20,3);
	printf("名称：%s",Post_Thing.item_name);
	//物品编号 
	SetCursorPosition(Handle_Out,20,4);
	printf("编号：%s",Post_Thing.IDnumber);
	//所在地点
	SetCursorPosition(Handle_Out,20,5);
	printf("所在地点：%s",Post_Thing.site);
	//简介
	SetCursorPosition(Handle_Out,20,6);
	printf("简要介绍：%s",Post_Thing.brief);
	//具体描述
	SetCursorPosition(Handle_Out,20,7);
	printf("具体描述：%s",Post_Thing.detail);  
	SetCursorPosition(Handle_Out,10,9);
	printf("----------------------------------------");
	//发布时间 
	SetCursorPosition(Handle_Out,20,10);
	printf("时间：%s",Post_Thing.time);
	//拥有者
	SetCursorPosition(Handle_Out,20,11);
	printf("发布者：%s",Post_Thing.user_name);
	//联系方式
	SetCursorPosition(Handle_Out,20,12);
	printf("联系方式：%s",Post_Thing.phone); 
		
	while(1)
	{
		for(int i=0;i<3;i++)
		{
			if(i==index)
				SetConsoleTextAttribute(Handle_Out, 0x90); 
			else
				SetConsoleTextAttribute(Handle_Out, 0x70); 
			SetCursorPosition(Handle_Out,6+(i)*(21-i),16);	//a[n]=a[1]+S[n-1] , a[n+1]-a[n]=b[n],s[n]为b[n]的求和公式 
			printf("%s",menu[i]);
		}
		int user_input = GetUserInput(&index,3,0);
		if(user_input==ESC)
			exit(1);
		if(user_input==ENTER)
		{
			if(index==0)
				ChangeMyPost(Post_Thing, pos, a, b);	//修改帖子 
			else if(index==1)
				ShowUserPost(pos,a,b);	//返回 
			else
				DeleteMyPost(Post_Thing, pos, a, b);	//删除帖子 
		}
	}	
}

//修改我的帖子 
void ChangeMyPost(struct POST_THING Post_Thing, int pos, int a, int b)
{	
	FILE *fp;
	int k=0,post_numbers=0;	
	//查看帖子在结构体数组中的位置	//比较编号和发表时间 
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
	printf("＊修改帖子＊");
	SetCursorPosition(Handle_Out,17,1);
	SetConsoleTextAttribute(Handle_Out, 0x7D);
	printf("(请在需要修改的地方重新输入)");	//紫色 
	SetConsoleTextAttribute(Handle_Out, 0x70);
	int index = 0;
	int menu_size = 6;
	char statusColor = 1;
	char *menu[] = {"名称：","所在地点：","简要介绍：","具体描述：","[完成修改]","[ 返回 ]"};
	
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
		printf("(请在需要修改的地方重新输入)");	//紫色 
		SetConsoleTextAttribute(Handle_Out, 0x70);
		for(int i=0;i<4;i++)
		{
			if(i == index)
			{
				if(statusColor==1)			
					SetConsoleTextAttribute(Handle_Out,0x90);  //浅蓝色 
				else
					SetConsoleTextAttribute(Handle_Out,0x10);  //蓝色 			
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
					SetConsoleTextAttribute(Handle_Out,0x90);  //浅蓝色 
				else
					SetConsoleTextAttribute(Handle_Out,0x10);  //蓝色 			
			} 
			else
				SetConsoleTextAttribute(Handle_Out,0x70); 
			SetCursorPosition(Handle_Out,20,3+2*i);    
	    	printf("%s",menu[i]);
		}
		SetCursorPosition(Handle_Out,17,1);
		SetConsoleTextAttribute(Handle_Out, 0x7D);
		printf("(请在需要修改的地方重新输入)");	//紫色 
		SetConsoleTextAttribute(Handle_Out,0x70);		
		if(user_input==ENTER)
		{
			statusColor = -statusColor;
			SetCursorPosition(Handle_Out,20+strlen(menu[index]),3+index*2);
			switch(index)
			{
				case 0:	Gets(Post_Thing.item_name,20); break;	//名称 
				case 1:	Gets(Post_Thing.site,20); break;	//所在地点 
				case 2:	Gets(Post_Thing.brief,20); break;	//简要介绍	
				case 3:	Gets(Post_Thing.detail,50); break;//具体描述 
				case 4:	{
					//修改后的信息不能为空或空格（2个） 
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
				case 5:	ViewMyPostPage(TPost[k], pos, a, b); break;	//返回 
			}
		}				
	}	
}

//删除帖子 
void DeleteMyPost(struct POST_THING Post_Thing, int pos, int a, int b)
{
	FILE *fp;
	int k=0,post_numbers=0;	
	//查看帖子在结构体数组中的位置	//比较编号和发表时间 
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
	printf("你确定删除帖子吗？");
	SetConsoleTextAttribute(Handle_Out, 0x70);
	SetCursorPosition(Handle_Out,21,7);
	int index = 0;
	char *menu[] = {"[ 确认 ]","[ 取消 ]"};
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

//输出用户帖子的信息到表格里 
void ExportMyPostInfo(struct POST_THING *Post, int post_numbers, char *cat, char *rw_mode)
{
	char file[30];
	sprintf(file,"%s的帖子信息.xls",User_Info.StudInfo.name);
	FILE *fp;
	if((fp = fopen(file,rw_mode))!=NULL)
	{
		fprintf(fp,"%s\n",cat);
		fprintf(fp,"编号\t名称\t类别\t地点\t简介\t具体描述\t发布时间\t可见\n");
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
 
//判断用户是否已登录 
int JudgeIsSignin(int page) 
{
	if(page==Page.user_menu)
		return 1;
	
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetCursorPosition(Handle_Out,17,4);
	printf("您还未登录，是否立即登录？");
	SetConsoleTextAttribute(Handle_Out, 0x70);
	SetCursorPosition(Handle_Out,21,7);
	int index = 0;
	char *menu[] = {"[ 确认 ]","[ 取消 ]"};
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
				SignInMenu_Option();	//前往登录页面
			else
				return 0;
		}	 
	}
	return 0;
} 
	

//展示已结束的帖子 
void ShowOverPost(int pos, int aa, int bb)
{		
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE); 
	int index = pos , a = aa , b = bb;	//a为翻页效果，b为详情切换 
	int menu_size = 4;
	int flash=0;	//刷新帖子 
	int n = 1;	//n代表某类别的帖子的数量 
	char *menu[] = {"[ 返回 ]","[ 失物贴 ]","[ 寻物贴 ]","[导出数据]"};
	int max=0;
	(Post.lost_numbers>Post.find_numbers) ? (max=Post.lost_numbers) : (max=Post.find_numbers);
	struct POST_THING Post_Cat[2][max];	//某个人删除的帖子总不至于比总帖子数量还多吧 
	int cat[2] = {0,0};		//帖子的长度 
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
		printf("已结束交易的帖子");
		SetCursorPosition(Handle_Out,0,3);
		printf(" ----------------------------------------------------------\n");
		SetCursorPosition(Handle_Out,0,4);
		printf(" 编号   名称       简介\t\t        地点\n");
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
					SetConsoleTextAttribute(Handle_Out,0x90);	//蓝色 
				else
					SetConsoleTextAttribute(Handle_Out,0x70);	//白色
				SetCursorPosition(Handle_Out,54,6+j);
				printf("[查看]"); 
				if(b>=13)
				{
					SetConsoleTextAttribute(Handle_Out,0x90);
					SetCursorPosition(Handle_Out,54,6+12);
					printf("[查看]"); 
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
					else if(index==1 && cat[index-1]!=0) {ViewOverPostPage(Post_Cat[index-1][b], index, a, b);}	//希望结构体数组的地址没有被释放掉吧 
					else if(index==2 && cat[index-1]!=0) {ViewOverPostPage(Post_Cat[index-1][b], index, a, b);}
					else if(index==3) {
					char *str = User_Info.StudInfo.name;
					strcpy(User_Info.StudInfo.name,"已结束的"); 
					ExportMyPostInfo(Post_Cat[0],cat[0],"失物", "w");
					ExportMyPostInfo(Post_Cat[1],cat[1],"寻物", "a");
					strcpy(User_Info.StudInfo.name,str);
					RedirectPage(11);
					}		
			} break;
		}
	}	
}

//查看已结束的帖子 
void ViewOverPostPage(struct POST_THING Post_Thing, int pos, int a, int b)
{
	system("cls");	//清空屏幕 
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	int index = 0;
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,24,0);
	printf("帖子详情页面");
	
	//物品名字 
	SetCursorPosition(Handle_Out,20,3);
	printf("名称：%s",Post_Thing.item_name);
	//物品编号 
	SetCursorPosition(Handle_Out,20,4);
	printf("编号：%s",Post_Thing.IDnumber);
	//所在地点
	SetCursorPosition(Handle_Out,20,5);
	printf("所在地点：%s",Post_Thing.site);
	//简介
	SetCursorPosition(Handle_Out,20,6);
	printf("简要介绍：%s",Post_Thing.brief);
	//具体描述
	SetCursorPosition(Handle_Out,20,7);
	printf("具体描述：%s",Post_Thing.detail);  
	SetCursorPosition(Handle_Out,10,9);
	printf("----------------------------------------");
	//发布时间 
	SetCursorPosition(Handle_Out,20,11);
	printf("时间：%s",Post_Thing.time);
	//拥有者
	SetCursorPosition(Handle_Out,20,12);
	printf("发布者：%s",Post_Thing.user_name);
	//联系方式
	SetCursorPosition(Handle_Out,20,13);
	printf("联系方式：%s",Post_Thing.phone); 
	
	SetConsoleTextAttribute(Handle_Out, 0x90);
	SetCursorPosition(Handle_Out,27,16);
	printf("[ 返回 ]");
	int user_input = getch();
	while(user_input!=ENTER);
	SetConsoleTextAttribute(Handle_Out, 0x70);
	SetCursorPosition(Handle_Out,27,16);
	printf("[ 返回 ]");
	ShowOverPost(1, a, b);	
}

//留言的页面 
void LeaveWord(struct POST_THING Post_Thing , int page , int status , int pos ,int a, int b)
{
	system("cls");
	char time[20];
	GetNowTime(time);
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,26,0);    
	printf("给他留言");	//打印标题 
	SetCursorPosition(Handle_Out,23,1);
	printf("%s",time);			//打印时间 
	int statusColor=1;
	int index=0;
	char *menu[3]={"留言：","[ 提交 ]","[ 返回 ]"}; 
	char word[60]=""; 
	
	SetCursorPosition(Handle_Out,0,7);    
    printf("     -------------------------------------------------\n\n");
    printf("     -------------------------------------------------");
	while(1)
	{
		if(index==0)
		{
			if(statusColor==1)			
				SetConsoleTextAttribute(Handle_Out,0x90);  //浅蓝色 
			else
				SetConsoleTextAttribute(Handle_Out,0x10);  //蓝色 			
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
				SetConsoleTextAttribute(Handle_Out,0x90);  //浅蓝色 
			else
				SetConsoleTextAttribute(Handle_Out,0x10);  //蓝色 			
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
    					printf("留言不能为空！");
						SetConsoleTextAttribute(Handle_Out,0x70);    					
					}
					else
					{
						WriteLeaveWord(Post_Thing, word);
						RedirectPage(12);
						PostDetailPage(Post_Thing, page, status, pos, a, b);
					}	
				} break;		//提交留言 
    			case 2: PostDetailPage(Post_Thing, page, status, pos, a, b); break;	//返回 		
			}
		}
	}
}

//写入用户留言信息到文件里 
void WriteLeaveWord(struct POST_THING Post_Thing , char *content)
{
	//留言时空间是肯定已经存在了
	//读取文件，获得结构体数组WSpace 
	FILE *fp; 
	struct WORD_SPACE WSpace[User_Info.user_numbers];
	EnDecryptFile("leave_word.dat",myKey);
	fp=fopen("leave_word.dat","rb");
    for(int i=0;i<User_Info.user_numbers;i++)
		fread(&WSpace[i],sizeof(struct WORD_SPACE),1,fp);  
   	fclose(fp);	
   	//比较帖子发主（乙）的号码，获得帖子发主（乙）的留言空间信息即索引值 
   	int k = 0;//* 
   	char time[20];
   	GetNowTime(time);
   	for(int i=0;i<User_Info.user_numbers;i++)
	if(!(strcmp(WSpace[i].master_phone,Post_Thing.phone)))
		k = i;	//存在是必然的，主要是为了找到索引值 ;
	WSpace[k].message_numbers++;
	if(WSpace[k].message_numbers>10)
	{
		for(int i=0;i<9;i++)
		{
			strcpy(WSpace[k].Message[i].user_name, WSpace[k].Message[i+1].user_name); //使留言总是自动去掉最老的，留言总数小于10 
			strcpy(WSpace[k].Message[i].user_phone, WSpace[k].Message[i+1].user_phone);
			strcpy(WSpace[k].Message[i].content, WSpace[k].Message[i+1].content);
			strcpy(WSpace[k].Message[i].time, WSpace[k].Message[i+1].time);
			strcpy(WSpace[k].Message[i].IDnumber,WSpace[k].Message[i+1].IDnumber);
		}
		strcpy(WSpace[k].Message[9].user_name, User_Info.StudInfo.name); //名字为登录得用户得名字 
		strcpy(WSpace[k].Message[9].user_phone, User_Info.StudInfo.phone);
		strcpy(WSpace[k].Message[9].content, content);
		strcpy(WSpace[k].Message[9].time, time);
		strcpy(WSpace[k].Message[WSpace[k].message_numbers-1].IDnumber,Post_Thing.IDnumber);
		WSpace[k].message_numbers=10;
	}	
	else
	{
		strcpy(WSpace[k].Message[WSpace[k].message_numbers-1].user_name,User_Info.StudInfo.name); //名字为登录得用户得名字 
		strcpy(WSpace[k].Message[WSpace[k].message_numbers-1].user_phone,User_Info.StudInfo.phone);
		strcpy(WSpace[k].Message[WSpace[k].message_numbers-1].content,content);
		strcpy(WSpace[k].Message[WSpace[k].message_numbers-1].time,time);
		strcpy(WSpace[k].Message[WSpace[k].message_numbers-1].IDnumber,Post_Thing.IDnumber);
	}
	
	fp=fopen("leave_word.dat","wb");
   	fwrite(&WSpace,sizeof(struct WORD_SPACE),User_Info.user_numbers,fp);
	fclose(fp);
	EnDecryptFile("leave_word.dat",myKey);	//加密文件 							 
} 

//展示留言信息 
void ShowLeaveWord(void)
{
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,27,0);    
	printf("留言榜");	//打印标题 
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
	printf("[ 返回 ]");
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
	   		printf("电话:%s  时间:%s  [%s]",WSpace[User_Info.user_seriNum].Message[num-1-i].user_phone,  WSpace[User_Info.user_seriNum].Message[num-1-i].time,  WSpace[User_Info.user_seriNum].Message[num-1-i].IDnumber);
	   		SetCursorPosition(Handle_Out,5,4+3*i);
	   		SetConsoleTextAttribute(Handle_Out, 0x74);
	   		printf("@%s：",WSpace[User_Info.user_seriNum].Message[num-1-i].user_name);
	   		SetConsoleTextAttribute(Handle_Out, 0x70);
	   		puts(WSpace[User_Info.user_seriNum].Message[num-1-i].content);
		}
	   	else
	   	for(int i=a;i<a+4;i++)
	   	{	   			   		
	   		SetCursorPosition(Handle_Out,5,3+3*(i-a));
	   		printf("电话:%s  时间:%s  [%s]",WSpace[User_Info.user_seriNum].Message[9-i].user_phone,  WSpace[User_Info.user_seriNum].Message[9-i].time,  WSpace[User_Info.user_seriNum].Message[num-1-i].IDnumber);
	   		SetCursorPosition(Handle_Out,5,4+3*(i-a));
	   		SetConsoleTextAttribute(Handle_Out, 0x74);
	   		printf("@%s：",WSpace[User_Info.user_seriNum].Message[9-i].user_name);
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

//只获取用户输入的前n部分 
void Gets(char *str, int n)
{
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE); 
	CONSOLE_CURSOR_INFO Corsor_Info; 
    GetConsoleCursorInfo(Handle_Out, &Corsor_Info);    
    Corsor_Info.bVisible = 1;	//显示光标 
    SetConsoleCursorInfo(Handle_Out, &Corsor_Info);
	char string[120];
	gets(string);
	for(int i=0;i<n;i++)
		str[i] = string[i];	
	Corsor_Info.bVisible = 0;	//关闭光标 
    SetConsoleCursorInfo(Handle_Out, &Corsor_Info);
    fflush(stdin);
}


//申请重置密码页面 
void AskforResetPassword(void)
{
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,24,0);    
	printf("申请重置密码");	 
	int statusColor=1;
	int index=0;
	char *menu[5]={"你的名字：","手机号：","留言管理员：","[ 确认 ]","[ 返回 ]"}; 
	char word[60]; 
	struct USER_MESSAGE User_Message={1,"","","",""};
	
	SetConsoleTextAttribute(Handle_Out,15 | 8 | 103 | 64);
	SetCursorPosition(Handle_Out,0,2); 
	printf("\t帮助：请用注册手机发送短信：“xxxx(手机号)\n"); 
	printf("\t      申请重置密码”到150133850000(手机号)\n");
	printf("\t      重置密码将在一个工作日内完成，完成后\n"); 
	printf("\t      密码将为你学号，请记得登录并修改。  \n"); 
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
					SetConsoleTextAttribute(Handle_Out,0x90);  //浅蓝色 
				else
					SetConsoleTextAttribute(Handle_Out,0x10);  //蓝色 			
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
			printf("\t帮助：请用注册手机发送短信：“xxxx(手机号)\n"); 
			printf("\t      申请重置密码”到150133850000(手机号)\n");
			printf("\t      重置密码将在一个工作日内完成，完成后\n"); 
			printf("\t      密码将为你学号，请记得登录并修改。  \n"); 
			SetConsoleTextAttribute(Handle_Out,0x70);
			statusColor = -statusColor;
		}
					
		for(int i=0;i<3;i++)
    	{
			if(index==i)
			{
				if(statusColor==1)			
					SetConsoleTextAttribute(Handle_Out,0x90);  //浅蓝色 
				else
					SetConsoleTextAttribute(Handle_Out,0x10);  //蓝色 			
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
    			case 0: Gets(User_Message.user_name,20); break;	//你的名字 
    			case 1: Gets(User_Message.user_phone,12); break;	//你的电话 
    			case 2: Gets(User_Message.content,60); break;	//留言内容 
    			case 3: {
    				if(!(strcmp(User_Message.user_name,"") && strcmp(User_Message.user_phone,"") && strcmp(User_Message.content,""))) 
    				{
    					SetCursorPosition(Handle_Out,23,14);
    					SetConsoleTextAttribute(Handle_Out,0x74);
    					printf("信息不能为空！");
						SetConsoleTextAttribute(Handle_Out,0x70);    					
					}	//判断信息是否为空 
					else
					{
						char time[20];
	    				GetNowTime(time);
	    				strcpy(User_Message.time,time);
	    				WriteUserMessage(User_Message);
						RedirectPage(13);
					}   				
				} break;		//提交留言 
    			case 4: SignInMenu_Option(); break;	//返回 		
			}
		}
	}
}

//存放用户申请重置密码信息	*先读取再写入
void WriteUserMessage(struct USER_MESSAGE User_Message)
{
	int message_numbers = Config.message_numbers;	
	struct USER_MESSAGE Message[message_numbers+1];	 
	FILE *fp;			
	//判断文件是否存在,不存在则创建一个 
	if((fp=fopen("user_message.dat","r"))==NULL) 
	{
		fp=fopen("user_message.dat","w");
		fclose(fp);
	} 
	EnDecryptFile("user_message.dat",myKey);	//解密文件 
	fp=fopen("user_message.dat","rb");
    for(int i=0;i<message_numbers;i++)
		fread(&Message[i],sizeof(struct USER_MESSAGE),1,fp);  
   	fclose(fp);  
		    	
	Message[message_numbers] = User_Message;	//追加信息 
	message_numbers++;
	fp=fopen("user_message.dat","wb");
   	fwrite(&Message,sizeof(struct USER_MESSAGE),message_numbers,fp);
	fclose(fp);
	EnDecryptFile("user_message.dat",myKey);	//加密文件 	
	//更新配置文件 
    FILE *cg;
	Config.message_numbers = message_numbers;
	cg=fopen("config","wb");
	fwrite(&Config,sizeof(struct CONFIG),1,cg);
	fclose(cg);
	EnDecryptFile("config",myKey);	
} 
 
//展示用户给管理员的留言信息 
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
	EnDecryptFile("user_message.dat",myKey);	//解密文件 
	fp=fopen("user_message.dat","rb");
    for(int i=0;i<message_numbers;i++)
		fread(&Message[i],sizeof(struct USER_MESSAGE),1,fp);  
   	fclose(fp);
	EnDecryptFile("user_message.dat",myKey);
		
	system("cls");
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,26,0);    
	printf("用户留言");	//打印标题 
	int flash=0; 
	int a = 0;	
	SetCursorPosition(Handle_Out,0,2);    
    printf("   -----------------------------------------------------");  
	SetConsoleTextAttribute(Handle_Out, 0x90);
	SetCursorPosition(Handle_Out,26,18);
	printf("[ 返回 ]");
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
	   		printf("电话：%s  时间：%s",Message[num-1-i].user_phone,  Message[num-1-i].time);
	   		SetCursorPosition(Handle_Out,10,4+3*i);
	   		SetConsoleTextAttribute(Handle_Out, 0x74);
	   		printf("@%s：",Message[num-1-i].user_name);
	   		SetConsoleTextAttribute(Handle_Out, 0x70);
	   		puts(Message[num-1-i].content);
		}
	   	else if(num>4 && num!=0)
	   	for(int i=a;i<a+4;i++)
	   	{	   			   		
	   		SetCursorPosition(Handle_Out,10,3+3*(i-a));
	   		printf("电话：%s  时间：%s",Message[num-1-i].user_phone,  Message[num-1-i].time);
	   		SetCursorPosition(Handle_Out,10,4+3*(i-a));
	   		SetConsoleTextAttribute(Handle_Out, 0x74);
	   		printf("@%s：",Message[num-1-i].user_name);
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

//修改管理员的密码 
void ChangeAdminPassword(void)
{
	system("cls");
	int index = 0;
	HANDLE Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle_Out, 0x70); 
	SetCursorPosition(Handle_Out,18,4); 
	printf("暂不支持修改管理员密码！");
		
	SetConsoleTextAttribute(Handle_Out, 0x90);
	SetCursorPosition(Handle_Out,26,9);
	printf("[ 返回 ]");
	int user_input = getch();
	while(user_input!=ENTER);
	SetConsoleTextAttribute(Handle_Out, 0x70);
	SetCursorPosition(Handle_Out,26,9);
	printf("[ 返回 ]");
	ChangePasswordMenu_Option();
} 

//从文件读取帖子的信息 
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
		EnDecryptFile("config",myKey);		//如果文件存在则解密 
		cg=fopen("config","rb"); 
		fread(&Config,sizeof(struct CONFIG),1,cg);
		fclose(cg);
		EnDecryptFile("config",myKey);	//加密配置文件
	}
	Post.lost_numbers = Config.lost_numbers;
	Post.find_numbers = Config.find_numbers;
	//*这里可别急用Post.Lost 
	struct POST_THING Lost[Post.lost_numbers];	//如果为0是否出问题 数组的大小可以为0！ 
	struct POST_THING Find[Post.find_numbers];
	FILE *fp1,*fp2;		
	EnDecryptFile("lost_info.dat",myKey);	//解密文件 	
	fp1=fopen("lost_info.dat","rb");
    for(int i=0;i<Post.lost_numbers;i++)
		fread(&Lost[i],sizeof(struct POST_THING),1,fp1);  
   	fclose(fp1);
   	
   	EnDecryptFile("find_info.dat",myKey);
	fp2=fopen("find_info.dat","rb");
    for(int i=0;i<Post.find_numbers;i++)
		fread(&Find[i],sizeof(struct POST_THING),1,fp2);  
   	fclose(fp2);   	   
	   	    		
	EnDecryptFile("lost_info.dat",myKey);	//加密文件
	EnDecryptFile("find_info.dat",myKey); 	
	
//	Post.Lost = Lost;	//不要把函数的(指针/)地址传递出去！函数生命周期结束后其地址会被释放！ 
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
	//对角 
	SetConsoleTextAttribute(Handle_Out, 0x74);	//红色 
	SetCursorPosition(Handle_Out,4,2);
	printf("┏");
	SetConsoleTextAttribute(Handle_Out, 0x71);	//蓝色 
	SetCursorPosition(Handle_Out,54,17);
	printf("┛ ");
	for(int i=0;i<16;i++)
	{
		SetConsoleTextAttribute(Handle_Out, 0x74);
		SetCursorPosition(Handle_Out,5+3*i,2);		
		printf("━━━");
		SetConsoleTextAttribute(Handle_Out, 0x72);
		SetCursorPosition(Handle_Out,2,i+3);	
		if(i<14)
			printf("  ┃ ");
		SetConsoleTextAttribute(Handle_Out, 0x71);	
		SetCursorPosition(Handle_Out,51-3*i,17);		
		printf("━━━");
		SetConsoleTextAttribute(Handle_Out, 0x76);
		SetCursorPosition(Handle_Out,54,16-i);	
		if(i<14)
			printf("┃ ");
		Sleep(50);
	}	
	
	//补全
	SetConsoleTextAttribute(Handle_Out, 0x72);
	SetCursorPosition(Handle_Out,5,17);
	printf("━");	 
	SetConsoleTextAttribute(Handle_Out, 0x74);
	SetCursorPosition(Handle_Out,53,2);
	printf("━");
	//对角 
	SetConsoleTextAttribute(Handle_Out, 0x72);	//绿色 
	SetCursorPosition(Handle_Out,4,17);
	printf("┗");
	SetConsoleTextAttribute(Handle_Out, 0x76);	//黄色
	SetCursorPosition(Handle_Out,54,2);
	printf("┓ ");	
	
	SetConsoleTextAttribute(Handle_Out, 0x74);
	SetCursorPosition(Handle_Out,24,7);
	printf("欢 "); 
	Sleep(200);
	SetConsoleTextAttribute(Handle_Out, 0x76);
	printf("迎 ");
	Sleep(200);
	SetConsoleTextAttribute(Handle_Out, 0x71);
	printf("进 ");
	Sleep(200);
	SetConsoleTextAttribute(Handle_Out, 0x72);
	printf("入");
	Sleep(300); 
	
	SetConsoleTextAttribute(Handle_Out, 0x75);
	SetCursorPosition(Handle_Out,22,9);
	printf("失物招领管理系统"); 
	Sleep(100); 
	SetConsoleTextAttribute(Handle_Out, 0x70);
	SetCursorPosition(Handle_Out,25,13);
	printf("2021年4月");	
	Sleep(500);
	GetPostData();
}
 
