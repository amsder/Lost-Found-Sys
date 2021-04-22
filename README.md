# 失物招领管理系统


#### 前言：   

你是否曾丢失过东西，发朋友圈全校搜索，却依然找不回丢失的宝贝？

你是否曾在路上遇见过珍奇的东西，犹豫着捡还是不捡，捡又该交到何处去？

茫茫人海中，我们总会遇到它，它或许是我们的，也或许不是我们的，我们希望那些属于我们的会回到身边，不属于我们的会回到它主人的身边。也许某天，我们丢失了宝贝，当另一个人找到它并还给我们时，那将是多大的喜悦！或许某日，我们把捡到的东西交还给另一个人时，看着他眼神里流露出的激动，那将是何等令人兴奋！联络，在你我之间，在物物之间，这便是一种缘分。这只是一个简单的失物招领平台，却为你我搭建了一个联络。



------



<table><tr><td bgcolor=skyblue>
    <font face="黑体" size=5>目录</font>
    </td></tr></table>

- [前言](#前言)
- [声明](#声明)
- [隐私服务](#隐私服务)
- [操作简介](#操作简介)
- [功能介绍](#功能介绍)
  - [1.访客模式](#访客模式)
  - [2.用户模式](#用户模式)
  - [3.管理员模式](#管理员模式)
- [图片展示](#图片展示)



-----



#### 声明：   

​		本系统由某高校某院光三第8组全体同学开发，为C语言课设作业。开源目的是促进交流学习，<font color=red>请勿直接用于作业或其他不合理用途。如造成不当后果，请自行负责，一切与本系统及开发者无关。</font>如存在使用问题，请在此文下评论。



#### 隐私服务

您须获知：本系统获取您的名字、手机号、学号、密码，来源为您注册时的信息，您的学号和密码是绝对保密的，您的手机号和名字是公开--如果您发布过帖子，您的帖子信息是公开的，帖子上有您的名字和手机号，以及物品的相关信息。所有的数据文件都是经过加密的，您的信息安全是得到保证的。



#### 操作简介

本系统全部采用按键操作，当您需要选择某个选项时，按上下或左右键移动光标，再按Enter键确认。当您需要输入某个信息时，和上述不同的是：您按下Enter键后光标会从浅蓝变成深蓝，您就可输入信息，输入完毕后再按一次Enter键即可。

小技巧：当您需要更改输入的信息时，在光标深蓝的输入模式下，按一次[上箭头]，即可显示上次输入的信息。



#### 功能介绍

#####   访客模式

在此模式下，您无须登录即可进入失物墙和寻物墙，墙上帖子按类别展示，每条帖子都有详情选项，您可点进去查看详情。详情里有留言选项，但此模式下您无法留言。此外，墙右上角有[我的]选项，您须登录才能查看。



#####   用户模式

1. **注册**

   您的注册需要填写五项信息：手机号、名字、学号、密码和确认密码。这里要求您注册信息不能为空，且手机号为11位，学号为10位。注册完成后您的数据将存放在数据库里。

   

2. **登录**

   登录时您需要填写已注册的手机号或学号，以及对应的密码。

   

3. **重置密码**

   当您忘记密码时，您可选择重置密码：用您注册的手机号发送短信“xxx手机号申请重置密码”到15013385000。重置工作将会在一个工作日内完成，密码重置成功后将为您的学号。

   您也可选择留言管理员，描述您的需求。

   

4. **失物墙/寻物墙**

   在此界面您可按类别查看所有的失物信息和寻物信息，在帖子详情里可选择留言帖子发布者。此外，您可通过墙上右上角[我的]选项，快捷进入[我的帖子]。

   

5. **我的帖子**

   在此界面您可查看所有您已发布过的帖子，这包括失物贴、寻物贴和结束贴，结束贴为您已删除的帖子。每个帖子您都可查看详情，在详情页面您可修改帖子或删除帖子。此外，在[我的帖子]页面，您还可以操作：发布失物帖子、发布寻物帖子和导出帖子数据。帖子发布页面里您须填写物品名称、物品地点、物品类别、物品简要描述和具体描述，其中前四项信息是必须的。发布成功后，您可在[我的帖子]那里查看到。

   

6. **我的信息**

   在此界面您可查看您的名字、手机号、学号和密码，在您需要查看的地方按一次Enter即可显示信息。您可选择修改个人信息，这包括修改名字和密码，修改后的信息要求长度大于3个字符。

   

7. **留言**

   在此界面您可查看别人给您的留言，这主要是别人在您的某个帖子下面的留言，留言信息包括留言者的名字、手机号、留言帖子编号和留言时间。您可根据留言信息和留言者交流。此外，留言信息最多只能保留最新的十五条。



#####   管理员模式

1. **登录**

   管理员登录账号为root，密码为123456。暂不支持修改，请妥善保管。

   

2. **失物墙/寻物墙**

   在此界面您可按类别查看所有的失物信息和寻物信息，但您不能查看我的帖子和选择留言。

   

3. **已结束交易**

   在此界面您可查看所有已结束交易的帖子信息，其来源为用户删除的帖子。您可选择导出已结束交易的帖子的信息。

   

4. **用户信息**

   在此界面您可查看所有的已注册的用户信息，包括用户编号、用户名字、用户手机号和用户学号，您不能查看用户的密码。虽然所有演示的用户的密码都是111。您可选择一键导出上述的所有的用户信息。

   

5. **修改密码**

   您可在此界面重置用户的密码，具体操作为：输入用户的手机号或学号，如果该用户存在则可选择重置密码，若该用户不存在则不能重置密码。用户密码重置成功后将为用户学号。

   

6. **留言**

   在此界面您可查看用户给您的留言，其来源为用户忘记密码时给您的留言。您可根据用户的需求做出对应的回应。



#### 图片展示

1. 欢迎界面

   ![欢迎界面](http://tt.jinqisir.com/%E6%AC%A2%E8%BF%8E%E7%95%8C%E9%9D%A2.png)



2. 开始界面

   ![开始界面](http://tt.jinqisir.com/%E5%BC%80%E5%A7%8B%E7%95%8C%E9%9D%A2.png)



3. 游客界面

   ![游客界面](http://tt.jinqisir.com/%E6%B8%B8%E5%AE%A2%E7%95%8C%E9%9D%A2.png)



4. 失物墙

   ![失物墙](http://tt.jinqisir.com/%E5%A4%B1%E7%89%A9%E5%A2%99.png)



5. 帖子详情页面

   ![帖子详情页面](http://tt.jinqisir.com/%E5%B8%96%E5%AD%90%E8%AF%A6%E6%83%85%E9%A1%B5%E9%9D%A2.png)



6. 注册界面

   ![注册界面](http://tt.jinqisir.com/%E6%B3%A8%E5%86%8C%E7%95%8C%E9%9D%A2.png)



7. 申请重置密码页面

   ![申请重置密码页面](http://tt.jinqisir.com/%E7%94%B3%E8%AF%B7%E9%87%8D%E7%BD%AE%E5%AF%86%E7%A0%81%E9%A1%B5%E9%9D%A2.png)



8. 用户界面

   ![用户界面](http://tt.jinqisir.com/%E7%94%A8%E6%88%B7%E7%95%8C%E9%9D%A2.png)



9. 我的帖子页面

   ![我的帖子页面](http://tt.jinqisir.com/%E6%88%91%E7%9A%84%E5%B8%96%E5%AD%90%E9%A1%B5%E9%9D%A2.png)



10. 修改帖子页面

    ![修改帖子页面](http://tt.jinqisir.com/%E4%BF%AE%E6%94%B9%E5%B8%96%E5%AD%90%E9%A1%B5%E9%9D%A2.png)



11. 发布帖子页面

    ![发布帖子页面](http://tt.jinqisir.com/%E5%8F%91%E5%B8%83%E5%A4%B1%E7%89%A9%E5%B8%96%E5%AD%90%E9%A1%B5%E9%9D%A2.png)



12. 我的信息页面

    ![我的信息页面](http://tt.jinqisir.com/%E6%88%91%E7%9A%84%E4%BF%A1%E6%81%AF%E9%A1%B5%E9%9D%A2.png)



13. 留言榜页面

    ![留言榜页面](http://tt.jinqisir.com/%E7%95%99%E8%A8%80%E6%A6%9C%E9%A1%B5%E9%9D%A2.png)



14. 管理员界面

    ![管理员界面](http://tt.jinqisir.com/%E7%AE%A1%E7%90%86%E5%91%98%E7%95%8C%E9%9D%A2.png)



15. 用户信息页面

    ![用户信息页面](http://tt.jinqisir.com/%E7%94%A8%E6%88%B7%E4%BF%A1%E6%81%AF%E9%A1%B5%E9%9D%A2.png)