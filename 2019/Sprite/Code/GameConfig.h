#pragma once
//һЩ��Ϸ�趨

//��Ϸ�����趨
#define WINDOW_WIDTH 800            //���ڿ��
#define WINDOW_HEIGHT 600           //���ڸ߶�
#define DEFAULT_SPRITE_WIDTH 100    //Ĭ�Ͼ�����
#define DEFAULT_SPRITE_HEIGHT 100   //Ĭ�Ͼ���߶�
#define DEFAULT_TOOL_WIDTH 100      //Ĭ�ϵ��߿��
#define DEFAULT_TOOL_HEIGHT 100     //Ĭ�ϵ��߸߶�

//��Ϸʱ���趨
#define GAME_CLOCK_INTERVAL 40      //��Ϸ�ĵ�λʱ�䣬�����ƶ���ʱ��������λ ms��
#define SPRITE_CREATE_INTERVAL 1000 //���������ʱ��������λ ms��

//��Ϸ����Ĳ����趨
#define MAX_SPRITE 10               //ͬ�����Զ��������������������ħ��
#define CLEVER_PROBOBILITY 20       //���� AutoSprite ʱ������ Clever �ĸ���Ϊ 20%
#define DANGER_DISTANCE 150         //����Ϊ�ǡ�Σ�ա��ľ��루�������鵽��ҵľ��롢��ҵ���ħ�ľ��룩
#define TOOL_N 2                    //���ߵ�����

//����ģʽ
#define SHIFT_SPEED_UP              //�����Ժ󣬰�ס Shift ���Լ����û������ƶ�
#define MORE_TOOL                   //ʹ���ߵ������Ƶ��
#define ENABLE_SPEED_BOUNS          //�ڳ��ֶ�ħ�Ժ��û��������٣����ڵ��ߵĴ��ڣ�������ģʽ��ʹ��Ϸ��򵥣�


//����ģʽ
//#define NDEBUG                    //���ڽ������� assert �ж�
//#define DEBUG                     //���������еȵ��Գ��ù���
#ifdef DEBUG                        //�������¹��ܵ�ǰ���ǿ�����������
#define DEBUG_TOOL                  //�Ե��߹��ܽ��в��ԣ����߻�ֱ�ӵ���
//#define DEBUG_DEMON               //�Զ�ħ���ֽ��е���ʱ���Դ򿪣�ʹ�ö�ħ�������
#endif