/************************************************************************
* 文件名称： main.c
* 内容摘要：
*     本文件为主函数入口，实现系统的运行。
*************************************************************************/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include ".\\File\File.h"
#include ".\\Log_in\Log_in.h"
#include ".\\Admin\Admin.h"
#include ".\\Customer\Customer.h"

int main()
{
    int role, exit_flag;
    
    // 直接登录，不需要员工链表
    role = Log_in(NULL);  // 传入 NULL 或适应修改后的 Log_in 函数
    
    while (1)
    {
        if (role == 0)  // 管理员
        {
            exit_flag = Ui_admin();
        }
        else if (role == 1)  // 顾客
        {
            exit_flag = Ui_customer();
        }
        
        if (exit_flag == 1)  // 退出系统
        {
            break;
        }
        else  // 注销登录
        {
            role = Log_in(NULL);  // 重新登录
        }
    }
    
    system("cls");
    printf("\n\n\n\n\t\t\t已退出系统.....");
    return 0;
}