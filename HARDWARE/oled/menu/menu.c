#include "menu.h"
#include "OLED.H"
#include "Queue.h"
#include "stack.h"
#include "stmflash.h"   
#include "main.h"
#include "feedback.h"
Queue KeyQueue;//��ֵ����
MyStack DataStack;//����ջ
char KeyNum = 0;//ȫ�ֵļ�ֵ
Mycourse cour = { 0,2 ,0 };//��ʼ�����
Mycourse *course = &cour;//����ȫ�ֹ�겢��ʼ��
MenuPage *nowPage;//��ǰ��ҳ��
MenuPage firstPage;//ҳ��һ

int sequence=6;

MenuPage Servo_1;//ģʽ1
MenuPage Servo_2;//ģʽ2
MenuPage Servo_3;//ģʽ5
MenuPage Servo_4;//ģʽ5
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
extern  float  duty;
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
 *   (((__) (__)))   ��ɽ��ֹ��������ֹ���䲻������������֮
 */



//------------------------����ʾ�Ķ����ŵ�����--------------------------------
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
		Set_Courese(2);
		Show_Text(2,"I_set:%f",kkint1);
			  Change_Data3(2,&kkint1);	
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
//		 Change_Data(1,&sequence);                //0 ������ 1 ������ 2 �̺��� 3 ������ 4 ������ 5 ���̺�
//	})
//	
//_Menue(Width, "Width", &firstPage,
//	{
//		Set_Courese(1);
//		Show_Text(1,"Width:%f",camere_distance);
//		 Change_Data1(1,&camere_distance);              
//	})	
//-------------------------�˵���ʾ����-------------------------------------
		void Menue_Show()//��ʾ��ǰҳ��
	{
		OLED_Fill();
		nowPage->nowPage();
		OLED_Refresh_Gram();
	}
//-------------------------�˵���ʼ������-----------------------------------
	void Init_Menue(MenuPage *page)
	{
		OLED_Init();//��ʼ��LED
		OLED_Clear();//��LED����
		KeyQueue.first = 0;//��ʼ����ֵ����
		KeyQueue.last = 0;
		DataStack.top = -1;//��ʼ������ջ
		nowPage = page;//�õ���ʼ��ҳ��
	}
//-------------------------�������ļ�ֵ�������-----------------------------
	void KeyNumGet(int key)
	{
		IQueue(&KeyQueue, key);
	}
	void StringCopy(char *desition, char *source, char length)//copyһ���ַ����е�һ�����ȵ����ݵ���һ�ַ���
	{
		int i = 0;
		for (i = 0; i < length; i++)
		{
			*(desition++) = *(source++);
		}
	}
//------------------------���㵱ǰӦ����ʾ����------------------------------
	int CountLine(int location)
	{
		return location - course->page_skewing;
	}
//------------------------�ж��Ƿ��ڿ���ʾ����------------------------------
	int CanShow(int location)
	{
		int cm = location - course->page_skewing;
		return cm > 0 && cm < MAX_LINE + 1;
	}
//------------------------���ߺ���-----------------------------------------
	void Draw_line(float X1, float Y1, float X2, float Y2)
	{
		int i = 0;
		if ((X2 - X1) != 0)//�ж�б���Ƿ����
		{
			float k = (Y2 - Y1) / (X2 - X1);//�õ�ֱ�ߵ�б��
			float d = Y1 - k * X1;//�õ���Y��ļн�
			unsigned char length = abs((int)(X1 - X2)) + 1;//�õ�X�᷽����Ƶĳ���
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
//-------------------------------������-----------------------------------------
	void Draw_Rectangle(char x, char y, char width, char height)
	{
		Draw_line(x, y, x + width, y);
		Draw_line(x, y, x, y + height);
		Draw_line(x, y + height, x + width, y + height);
		Draw_line(x + width, y, x + width, y + height);
	}
//---------------------------------��Բ-----------------------------------------
	void Draw_Circle(float x, float y, float R)
	{
		float angle = 0;//��ʼ�Ƕ�
		for (angle = 0; angle < 360; angle += 1)
		{
			OLED_DrawPoint(R*sin(angle*3.14 / 180) + x, y + R * cos(angle*3.14 / 180), 1);
		}
	}
//---------------------------------�����--------------------------------------
	void Draw_course(char x, char y)
	{
		if (y > 7)
		{
			y = 7;
		}
		OLED_ShowString(x, y, ">");
	}
//--------------------------------�õ���ֵ-------------------------------------
	void Get_key(int allLine)
	{
		KeyNum = OQueue(&KeyQueue);
		if (KeyNum == KEY_DOWN)
		{
			course->set_y += 2;//���ָ���һ
			if (allLine > MAX_LINE)
			{
				if (course->set_y > MAX_LINE)
				{
					course->set_y = MAX_LINE;
					course->page_skewing += 1;//ҳ��ָ��ƫ������һ
					if (course->page_skewing > (allLine - MAX_LINE))//����ҳ��ָ��ƫ����������
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
					course->page_skewing -= 1;//ҳ��ƫ������һ
				}
			}
		}
		else if (KeyNum == kEY_BANK)//����Ƿ��ؼ�
		{
			if (nowPage->fatherPage != NULL)//����и�ҳ��
			{
				nowPage = nowPage->fatherPage;//�ı�ҳ��
				Pop(&DataStack, course);//ͬʱȡ������ջ���������
			}
		}
	}
//--------------------------------��ʾ�ı�----------------------------------------
	void Show_Text(char location, char *name, ...)
	{
		va_list vp;
		int d = 0; float f = 0;
		char *p;
		char ap[BUFF_LENGTH] = { 0 };
		char data[10] = { 0 };//���ڴ�������
		if (!CanShow(location))return;//���ڿ���ʾ����ֱ���˳�
		va_start(vp, name);
		p = strstr(name, "%");
		if (p)
		{
			StringCopy(ap, name, p - name);//�õ�%ǰ���ֵ
			p++;
			switch (*p)
			{
			case 'd':
			{d = va_arg(vp, int);//�õ�����
			sprintf(data, "%d", d);//������ת�����ַ���
			break; }
			case 'f':
			{
				f = va_arg(vp, double);//�õ�����
				sprintf(data, "%.2f", f);//������ת�����ַ���
				break; }
			default:break;
			}
			strcat(ap, data);//���������ַ���
			OLED_ShowString(10, CountLine(location), ap);//��ʾ
		}
		else
		{
			OLED_ShowString(10, CountLine(location), name);//��ʾ
		}
		va_end(vp);
	}
//---------------------------------��ֵ�ı亯��-------------------------------------------
	
		void Change_Data2(char location, int *data)
	{
		if ((course->page_skewing + course->set_y) == location)//�ж��Ƿ�ѡ�е�ǰ��
		{
			if (KeyNum == KEY_RIGHT)//�����ֵ��RIGHT�����ݼ�
			{
				*data += STEPNUM;//���ݼ
			}
			if (KeyNum == kEY_LEFT)
			{
				*data -= STEPNUM;
			}
		}
	
	}
	
	
			void Change_Data3(char location, int *data)
	{
		if ((course->page_skewing + course->set_y) == location)//�ж��Ƿ�ѡ�е�ǰ��
		{
			if (KeyNum == KEY_RIGHT)//�����ֵ��RIGHT�����ݼ�
			{
			
          STMFLASH_Write(FLASH_SAVE_ADDR,&kk1,1);
		*data -= STEPNUM;//���ݼ
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
		if ((course->page_skewing + course->set_y) == location)//�ж��Ƿ�ѡ�е�ǰ��
		{
			if (KeyNum == KEY_RIGHT)//�����ֵ��RIGHT�����ݼ�
			{
				*data += STEPNUM2;//���ݼ
	
			}
			if (KeyNum == kEY_LEFT)
			{
				*data -= STEPNUM2;

			}
		}
	
	}
	
	
	
	
	
	
	
	void Change_Data(char location, int *data)
	{
		if ((course->page_skewing + course->set_y) == location)//�ж��Ƿ�ѡ�е�ǰ��
		{
			if (KeyNum == KEY_RIGHT)//�����ֵ��RIGHT�����ݼ�
			{
				*data += STEPNUM;//���ݼ
			
			}
			if (KeyNum == kEY_LEFT)
			{
				*data -= STEPNUM;
			
			}
		}
	}
//---------------------------------��ֵ�ı亯��-------------------------------------------
		void Change_Data1(char location, float *data)
		{
			if ((course->page_skewing + course->set_y) == location)//�ж��Ƿ�ѡ�е�ǰ��
			{
				if (KeyNum == KEY_RIGHT)//�����ֵ��RIGHT�����ݼ�
				{
					*data += STEPNUM1;//���ݼ�
				}
				if (KeyNum == kEY_LEFT)
				{
					*data -= STEPNUM1;
				}
			}
		}	
	void Change_Data11(char location, float *data)
		{
			if ((course->page_skewing + course->set_y) == location)//�ж��Ƿ�ѡ�е�ǰ��
			{
				if (KeyNum == KEY_RIGHT)//�����ֵ��RIGHT�����ݼ�
				{
					*data += STEPNUM1;//���ݼ�
				}
				if (KeyNum == kEY_LEFT)
				{
					*data -= STEPNUM1;
				}
			}
		}	
	
//-----------------------------ҳ��ı亯��--------------------------------------------
	void Change_Page(char location, MenuPage *Page)
	{
		if (course->page_skewing + course->set_y == location)//�ж��Ƿ�ѡ�е�ǰ��
		{
			if (KeyNum == kEY_OK)//��ȷ����
			{
				if (Page != NULL)
				{
					Push(&DataStack, *course);//��ջ
					nowPage = Page;//�ı�ҳ��
					course->page_skewing = 0;//����ʼ��
					course->set_y = 1;
				}
			}
		}
	}
//---------------------------------����ҳ��-----------------------------------------------
	void Set_Courese(int allLine)//����ҳ�沢�����ù���λ��,���Ϊ��ҳ�����е�Show_Text()������
	{
		int set = 0;
		float sa = 0;
		Get_key(allLine);//�õ���ֵ
		set = strlen(nowPage->page);//�õ�����ĳ���
		sa = (127 - (set-1) * 6) / 2;
		Draw_line(0, 60, sa - 6, 60);
//	OLED_ShowString(sa - 6, 0, "<");
//	OLED_ShowString(sa + set * 6, 0, ">");
	OLED_ShowString(sa, 0, nowPage->page);//���Ʊ���
		Draw_line(sa + set * 6 + 6, 60, 128, 60);
		Draw_line(8, 0, 8, 63);
		Draw_course(0, course->set_y);
	}

