#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "Customer.h"

// 顾客主界面
int Ui_Customer();

// 自助点菜
void Customer_OrderDishes(void);

// 自助结账
void Customer_CheckOut(void);

// 订单查询（仅已买/未买）
void Customer_OrderSearch(void);

#endif