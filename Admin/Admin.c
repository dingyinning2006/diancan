/************************************************************************
* 文件名称： Admin.c
* 内容摘要：
*     本文件实现关于管理员管理数据的功能。
*************************************************************************/
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "..\\File\File.h"
#include "..\\Admin\Admin.h"
#include "..\\List\List.h"
#include "..\\Menu\Menu.h"
#include "..\\Glb_putstring\\Glb_putstring.h"

int Ui_admin()
{  
    int n;
    
    while(1)
    {    
        system("cls");
        printf("\n\n\n\t\t\t管理员功能选择界面\n\n");
        printf("\t\t\t1、菜谱管理\n\n");
        printf("\t\t\t2、注销\n\n");
        printf("\t\t\t3、退出\n\n");
        printf("\t\t\t请输入您所要选择的功能：");
        
        n = glb_putString(NULL,'1','3',1,2);
        
        switch(n)
        {
            case 1:  // 菜谱管理
                Menu_manage();
                break;
            case 2:  // 注销
                return 0;
            case 3:  // 退出
                return 1;
        }                          
    }    

}




void Menu_manage()
{
    char dirname[] = "./Date/Menu.txt";
    FILE *fp;
    pList head;
    int n;
    fp = File_open(dirname);
    head = File_read(fp,sizeof(struct Menu_t));
    while(1)
    {     
        system("cls");
        printf("\n\n\n\t\t\t菜谱管理界面\n\n");
        printf("\t\t\t1、增加菜谱\n\n"); 
        printf("\t\t\t2、删除菜谱\n\n");
        printf("\t\t\t3、修改菜谱\n\n"); 
        printf("\t\t\t4、查询菜谱\n\n"); 
        printf("\t\t\t5、返回\n\n"); 
        printf("\t\t\t请输入您要操作的功能：");
        n = glb_putString(NULL,'1','5',1,2);
        switch(n)
        {
        case 1:    
            List_print(head,Menu_print);
            File_add(fp,head,sizeof(struct Menu_t),Menu_add);
            head = File_read(fp,sizeof(struct Menu_t));
            List_print(head,Menu_print);
            break;
        case 2:
            List_print(head,Menu_print);
            File_del(fp,dirname,head,sizeof(struct Menu_t),Menu_del);
            List_print(head,Menu_print);
            break;
        case 3:
            List_print(head,Menu_print);
            File_updata(fp,head,sizeof(struct Menu_t),Menu_updata);
            head = File_read(fp,sizeof(struct Menu_t));
            List_print(head,Menu_print);
            break;
        case 4: 
    
            Menu_search(head);
            break;
        case 5:
            break;
        }
        if (n == 5)
        {
            break;
        }
        else
        {
            printf("\n按<Esc>键返回...");
            while(getch() != 27)
            {}
        }
        
    }
    List_free(head);
}