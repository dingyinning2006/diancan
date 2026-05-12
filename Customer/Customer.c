#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "Customer.h"

// 顾客主菜单
int Ui_Customer()
{
    int n;
    while(1)
    {
        system("cls");
        printf("\n\n\n\t\t\t顾客自助点餐系统\n\n");
        printf("\t\t\t1、开始点餐\n\n");
        printf("\t\t\t2、自助结账\n\n");
        printf("\t\t\t3、订单查询\n\n");
        printf("\t\t\t4、退出系统\n\n");
        printf("\t\t\t请选择功能：");

        n = glb_putString(NULL,'1','4',1,2);
        switch(n)
        {
            case 1:
                Customer_OrderDishes();
                break;
            case 2:
                Customer_CheckOut();
                break;
            case 3:
                Customer_OrderSearch();
                break;
            case 4:
                return 1;
        }
    }
}

// 点菜
void Customer_OrderDishes(void)
{
	FILE *fd;
	int n,count1;
	pList pMenu,pOrder,pTitle;
    struct Order_t *pNew;
	char tabpath[30] ="./Date/Cache/order_tmp.txt";

	fd = File_open("./Date/Menu.txt");
	pMenu = File_read(fd,sizeof(struct Menu_t));	
	fd = File_open("./Date/Cache/Order.txt");
    pOrder = File_read(fd,sizeof(struct Order_t));

	// 新建订单
	pNew = Order_init();
	List_add(pOrder,pNew);
	File_write(fd,pOrder,sizeof(struct Order_t),0);

	fd = fopen(tabpath,"w+");
    pTitle = File_read(fd,sizeof(struct Title_t));

    // 打印菜单
	Order_print(pMenu,pTitle,pNew);
	count1 = List_count(pMenu);

	while (1)	
	{
		JR_EmptyRaw(count1+3,count1+12);
		JR_SetCursor(count1+3,0);
		printf("\t\t(1)：加菜\n");
		printf("\t\t(2)：退菜\n");
		printf("\t\t(3)：返回上一级\n");
		printf("\t\t请输入要操作的功能：");
        n = glb_putString(NULL,'1','3',1,2);
		switch(n)
		{ 
		 case 1:
			 Order_add(count1,pNew,pTitle,pOrder,pMenu,tabpath);
		     break;
		 case 2:
			 Order_del(count1,pNew,pTitle,pMenu,pOrder,tabpath);
			 break;
		 case 3:
		     break;
		}	
		if (n == 3) break;
	}	 
	List_free(pOrder);
	List_free(pMenu);
	List_free(pTitle);
}

// 结账
void Customer_CheckOut(void)
{
	FILE *fp;
	int money;
	pList pt,pTitle,pOrder,ps;
	struct Order_t *data;
	char txt[] = ".txt";
    char tabpath[30] ="./Date/Cache/order_tmp.txt";

	fp = File_open("./Date/Cache/Order.txt");
	pOrder = File_read(fp,sizeof(struct Order_t));

	pt = pOrder->pNext;
	if (pt == NULL)
	{
		printf("\n暂无未支付订单，按任意键返回...");
		getch();
		return;
	}

	data = (struct Order_t *)(pt->pData);
	fp = File_open(tabpath);
	pTitle = File_read(fp,sizeof(struct Title_t));

	Title_print(pTitle,data);
	printf("\n确认订单并结账？(y)确定、(n)返回：");
	if (glb_putString(NULL,0,0,1,1) == 'y')
	{
		printf("\n请输入支付金额：");
		money = glb_putString(NULL,'0','9',5,2);
		if (money < data->money)
		{
			printf("\n支付金额不足，无法结账，按任意键返回...");
			getch();
			return;
		}
		printf("\n找零：%d 元",money - data->money);

		fp = File_open("./Date/Order/Order.txt");
		fseek(fp,0,2);
		fwrite(data,sizeof(struct Order_t),1,fp);
		fflush(fp);

		ps = pOrder;
		ps->pNext = pt->pNext;
		free(pt);
		fp = fopen("./Date/Cache/Order.txt","w+");
		File_write(fp,pOrder,sizeof(struct Order_t),0);

		printf("\n结账成功！感谢光临");
	}
	else
		printf("\n取消结账");

	printf("\n按任意键返回...");
	getch();
	List_free(pTitle);
    List_free(pOrder);
}

// 订单查询
void Customer_OrderSearch(void)
{
	int n;
	while (1)
	{
		system("cls");
		printf("\n\n\t\t\t订单查询\n\n");
		printf("\t\t\t1、未买单查询\n\n");
		printf("\t\t\t2、历史订单查询\n\n");
		printf("\t\t\t3、返回\n\n");
		printf("\t\t\t请选择：");
		n = glb_putString(NULL,'1','3',1,2);
		if(n == 1)
		{
			FILE *fp;
			pList pOrder;
			fp = File_open("./Date/Cache/Order.txt");
			pOrder = File_read(fp,sizeof(struct Order_t));
			Order_search_unbuy(pOrder);
			List_free(pOrder);
			getch();
		}
		else if(n == 2)
		{
			Order_search_buy();
			getch();
		}
		else
		{
			break;
		}
	}
}