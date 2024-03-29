#include "menu.h"
#include "OLED.H"
#include "Queue.h"
#include "stack.h"
#include "stmflash.h"   
#include "main.h"
#include "feedback.h"
Queue KeyQueue;//键值队列
MyStack DataStack;//数据栈
char KeyNum = 0;//全局的键值
Mycourse cour = { 0,2 ,0 };//初始化光标
Mycourse *course = &cour;//定义全局光标并初始化
MenuPage *nowPage;//当前的页面
MenuPage firstPage;//页面一

int sequence=6;

MenuPage Servo_1;//模式1
MenuPage Servo_2;//模式2
MenuPage Servo_3;//模式5
MenuPage Servo_4;//模式5
MenuPage Servo_5;
MenuPage Sequence;
MenuPage Width1;
MenuPage Servo_51;
MenuPage Sequence1;
MenuPage Width;
MenuPage Servo_513;
MenuPage Sequence13;
MenuPage Width3;
MenuPage Sequence133;
MenuPage Width2;
 int target_v,kkint1=119,kkint2=119;
u16 kk=119;
float pkp=3.203;
extern int sin_max,c,V;
extern  float  duty,I_set;
extern u16 rrr;
extern u16 kk1;
/**
 * http://www.flvcd.com/
 *  .--,       .--,
 * ( (  \.---./  ) )
 *  '.__/o   o\__.'
 *     {=  ^  =}
 *      >  -  <
 *     /       \
 *    //       \\
 *   //|   .   |\\
 *   "'\       /'"_.-~^`'-.
 *      \  _  /--'         `
 *    ___)( )(___
 *   (((__) (__)))   高山仰止，景行行止，虽不能至，心往向之
 */



//------------------------想显示的东西放到这里--------------------------------
_Menue(firstPage, "MENU", PAGE_NULL,
	{
		
	Set_Courese(12);
		Show_Text(2,"efficiency:0.96");
		
		Change_Page(2,&Servo_1);
		
		Show_Text(4,"Iin(A):%f",(float)(ADC_2[adc_size]-1919.5312)/kkint1);
	  Change_Data3(4,&kkint1);	

		
		Change_Page(4,&Servo_2);
//		
		Show_Text(6,"Uin(v):%f",(float)ADC_3[adc_size]/4095*pkp*11 );

	             Change_Data1(6,&pkp);
		
		Show_Text(10,"Uout(v):%d",ADC_1[adc_size]);

		

         Show_Text(8,"PWM_duty:%f ",duty);
//	
		
			Change_Data1(8,&duty);
			if(duty>0.99)duty=0.99;
			if(duty<0.10)duty=0.10;
		
	})
_Menue(Servo_1, "sin_max", &firstPage,
	{
		Set_Courese(2);
		Show_Text(2,"sin_max:%d",sin_max);
        Change_Data3(2,&sin_max);
//					if(sin_max > rrr)
//					sin_max = rrr;
	})

_Menue(Servo_2, "I_set", &firstPage,
	{
		Set_Courese(6);
		Show_Text(2,"I_set:%f",I_set);
		Change_Data12(2,&I_set);	
		Show_Text(4,"Iin(A):%f",(float)(ADC_2[adc_size]-1919.5312)/kkint1);
		Show_Text(6,"Iin:%d",ADC_2[adc_size]);
	})
	
_Menue(Servo_3, "Hz", &firstPage,
	{
		Set_Courese(1);
		Show_Text(1,"Hz:%d",Hz);
		 Change_Data4(1,&Hz);
		
	})
	
//_Menue(Servo_4, "p", &firstPage,
//	{
//		Set_Courese(1);
//		Show_Text(1,"p:%d");

////		if(Servo4.target>1250)Servo4.target=1250;else if(Servo4.target<250)Servo4.target=250;
//	})
//	
//_Menue(Servo_5, "Servo5", &firstPage,
//	{
//		Set_Courese(1);
//		Show_Text(1,"Servo5_angele:%d",Servo5.target);
//		 Change_Data(1,&Servo5.target);
//		if(Servo5.target>1250)Servo5.target=1250;else if(Servo5.target<250)Servo5.target=250;
//	})
//	
//_Menue(Sequence, "Sequence", &firstPage,
//	{
//		Set_Courese(1);
//		Show_Text(1,"Sequence:%d",sequence);
//		 Change_Data(1,&sequence);                //0 红绿蓝 1 红蓝绿 2 绿红蓝 3 绿蓝红 4 蓝红绿 5 蓝绿红
//	})
//	
//_Menue(Width, "Width", &firstPage,
//	{
//		Set_Courese(1);
//		Show_Text(1,"Width:%f",camere_distance);
//		 Change_Data1(1,&camere_distance);              
//	})	
//-------------------------菜单显示函数-------------------------------------
		void Menue_Show()//显示当前页面
	{
		OLED_Fill();
		nowPage->nowPage();
		OLED_Refresh_Gram();
	}
//-------------------------菜单初始化函数-----------------------------------
	void Init_Menue(MenuPage *page)
	{
		OLED_Init();//初始化LED
		OLED_Clear();//对LED请屏
		KeyQueue.first = 0;//初始化键值队列
		KeyQueue.last = 0;
		DataStack.top = -1;//初始化数据栈
		nowPage = page;//得到初始化页面
	}
//-------------------------将按键的键值存入队列-----------------------------
	void KeyNumGet(int key)
	{
		IQueue(&KeyQueue, key);
	}
	void StringCopy(char *desition, char *source, char length)//copy一个字符串中的一定长度的数据到另一字符串
	{
		int i = 0;
		for (i = 0; i < length; i++)
		{
			*(desition++) = *(source++);
		}
	}
//------------------------计算当前应该显示的行------------------------------
	int CountLine(int location)
	{
		return location - course->page_skewing;
	}
//------------------------判断是否在可显示的行------------------------------
	int CanShow(int location)
	{
		int cm = location - course->page_skewing;
		return cm > 0 && cm < MAX_LINE + 1;
	}
//------------------------画线函数-----------------------------------------
	void Draw_line(float X1, float Y1, float X2, float Y2)
	{
		int i = 0;
		if ((X2 - X1) != 0)//判断斜率是否存在
		{
			float k = (Y2 - Y1) / (X2 - X1);//得到直线的斜率
			float d = Y1 - k * X1;//得到与Y轴的夹角
			unsigned char length = abs((int)(X1 - X2)) + 1;//得到X轴方向绘制的长度
			for (i = 0; i < length; i++)
			{
				OLED_DrawPoint(X1 + i, k*(X1 + i) + d, 1);
			}
		}
		else
		{
			for (i = 0; i < Y2 - Y1 + 1; i++)
			{
				OLED_DrawPoint(X1, Y1 + i, 1);
			}
		}
	}
//-------------------------------画矩形-----------------------------------------
	void Draw_Rectangle(char x, char y, char width, char height)
	{
		Draw_line(x, y, x + width, y);
		Draw_line(x, y, x, y + height);
		Draw_line(x, y + height, x + width, y + height);
		Draw_line(x + width, y, x + width, y + height);
	}
//---------------------------------画圆-----------------------------------------
	void Draw_Circle(float x, float y, float R)
	{
		float angle = 0;//初始角度
		for (angle = 0; angle < 360; angle += 1)
		{
			OLED_DrawPoint(R*sin(angle*3.14 / 180) + x, y + R * cos(angle*3.14 / 180), 1);
		}
	}
//---------------------------------画光标--------------------------------------
	void Draw_course(char x, char y)
	{
		if (y > 7)
		{
			y = 7;
		}
		OLED_ShowString(x, y, ">");
	}
//--------------------------------得到键值-------------------------------------
	void Get_key(int allLine)
	{
		KeyNum = OQueue(&KeyQueue);
		if (KeyNum == KEY_DOWN)
		{
			course->set_y += 2;//光标指针加一
			if (allLine > MAX_LINE)
			{
				if (course->set_y > MAX_LINE)
				{
					course->set_y = MAX_LINE;
					course->page_skewing += 1;//页面指针偏移量加一
					if (course->page_skewing > (allLine - MAX_LINE))//限制页面指针偏移量的增加
					{
						course->page_skewing = allLine - MAX_LINE;
					}
				}
			}
			else
			{
				if (course->set_y > allLine)
				{
					course->set_y = allLine;
				}
			}
		}
		else if (KeyNum == KEY_UP)
		{
			course->set_y -= 2;
			if (course->set_y < 2)
			{
				course->set_y = 2;
				if (course->page_skewing > 0)
				{
					course->page_skewing -= 1;//页面偏移量减一
				}
			}
		}
		else if (KeyNum == kEY_BANK)//如果是返回键
		{
			if (nowPage->fatherPage != NULL)//如果有父页面
			{
				nowPage = nowPage->fatherPage;//改变页面
				Pop(&DataStack, course);//同时取出数据栈里面的数据
			}
		}
	}
//--------------------------------显示文本----------------------------------------
	void Show_Text(char location, char *name, ...)
	{
		va_list vp;
		int d = 0; float f = 0;
		char *p;
		char ap[BUFF_LENGTH] = { 0 };
		char data[10] = { 0 };//用于储存数据
		if (!CanShow(location))return;//不在可显示的行直接退出
		va_start(vp, name);
		p = strstr(name, "%");
		if (p)
		{
			StringCopy(ap, name, p - name);//得到%前面的值
			p++;
			switch (*p)
			{
			case 'd':
			{d = va_arg(vp, int);//得到数据
			sprintf(data, "%d", d);//将数据转换成字符串
			break; }
			case 'f':
			{
				f = va_arg(vp, double);//得到数据
				sprintf(data, "%.2f", f);//讲数据转换成字符串
				break; }
			default:break;
			}
			strcat(ap, data);//连接两个字符串
			OLED_ShowString(10, CountLine(location), ap);//显示
		}
		else
		{
			OLED_ShowString(10, CountLine(location), name);//显示
		}
		va_end(vp);
	}
//---------------------------------数值改变函数-------------------------------------------
	
		void Change_Data2(char location, int *data)
	{
		if ((course->page_skewing + course->set_y) == location)//判断是否选中当前行
		{
			if (KeyNum == KEY_RIGHT)//如果键值是RIGHT则数据加
			{
				*data += STEPNUM;//数据�
			}
			if (KeyNum == kEY_LEFT)
			{
				*data -= STEPNUM;
			}
		}
	
	}
	
	
			void Change_Data3(char location, int *data)
	{
		if ((course->page_skewing + course->set_y) == location)//判断是否选中当前行
		{
			if (KeyNum == KEY_RIGHT)//如果键值是RIGHT则数据加
			{
			
          STMFLASH_Write(FLASH_SAVE_ADDR,&kk1,1);
		*data -= STEPNUM;//数据�
			}
			if (KeyNum == kEY_LEFT)
			{
				
		  STMFLASH_Write(FLASH_SAVE_ADDR,&kk1,1);	
          *data += STEPNUM;
			}
		}
	
	}
				void Change_Data4(char location, int *data)
	{
		if ((course->page_skewing + course->set_y) == location)//判断是否选中当前行
		{
			if (KeyNum == KEY_RIGHT)//如果键值是RIGHT则数据加
			{
				*data += STEPNUM2;//数据�
	
			}
			if (KeyNum == kEY_LEFT)
			{
				*data -= STEPNUM2;

			}
		}
	
	}
	
	
	
	
	
	
	
	void Change_Data(char location, int *data)
	{
		if ((course->page_skewing + course->set_y) == location)//判断是否选中当前行
		{
			if (KeyNum == KEY_RIGHT)//如果键值是RIGHT则数据加
			{
				*data += STEPNUM;//数据�
			
			}
			if (KeyNum == kEY_LEFT)
			{
				*data -= STEPNUM;
			
			}
		}
	}
//---------------------------------数值改变函数-------------------------------------------
		void Change_Data1(char location, float *data)
		{
			if ((course->page_skewing + course->set_y) == location)//判断是否选中当前行
			{
				if (KeyNum == KEY_RIGHT)//如果键值是RIGHT则数据加
				{
					*data += STEPNUM;//数据加
				}
				if (KeyNum == kEY_LEFT)
				{
					*data -= STEPNUM;
				}
			}
		}	
	void Change_Data11(char location, float *data)
		{
			if ((course->page_skewing + course->set_y) == location)//判断是否选中当前行
			{
				if (KeyNum == KEY_RIGHT)//如果键值是RIGHT则数据加
				{
					*data += STEPNUM1;//数据加
				}
				if (KeyNum == kEY_LEFT)
				{
					*data -= STEPNUM1;
				}
			
				}	
			}	
				void Change_Data12(char location, float *data)
		{
			if ((course->page_skewing + course->set_y) == location)//判断是否选中当前行
			{
				if (KeyNum == KEY_RIGHT)//如果键值是RIGHT则数据加
				{
					*data += STEPNUM12;//数据加
				}
				if (KeyNum == kEY_LEFT)
				{
					*data -= STEPNUM12;
				}
			}
		}
	
//-----------------------------页面改变函数--------------------------------------------
	void Change_Page(char location, MenuPage *Page)
	{
		if (course->page_skewing + course->set_y == location)//判断是否选中当前行
		{
			if (KeyNum == kEY_OK)//是确定键
			{
				if (Page != NULL)
				{
					Push(&DataStack, *course);//进栈
					nowPage = Page;//改变页面
					course->page_skewing = 0;//光标初始化
					course->set_y = 1;
				}
			}
		}
	}
//---------------------------------绘制页面-----------------------------------------------
	void Set_Courese(int allLine)//绘制页面并且设置光标的位置,入口为该页面所有的Show_Text()的行数
	{
		int set = 0;
		float sa = 0;
		Get_key(allLine);//得到键值
		set = strlen(nowPage->page);//得到标题的长度
		sa = (127 - (set-1) * 6) / 2;
		Draw_line(0, 60, sa - 6, 60);
//	OLED_ShowString(sa - 6, 0, "<");
//	OLED_ShowString(sa + set * 6, 0, ">");
	OLED_ShowString(sa, 0, nowPage->page);//绘制标题
		Draw_line(sa + set * 6 + 6, 60, 128, 60);
		Draw_line(8, 0, 8, 63);
		Draw_course(0, course->set_y);
	}

