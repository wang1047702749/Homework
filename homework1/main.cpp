#include<QDebug>
#include<QList>
#include<QCoreApplication>

typedef quint32 word;                               //定义32位的字
typedef quint8 byte;                                //定义8位的字

#define i 0x12345678
#define _STR(s) #s                                  //把宏参数变为一个字符串
#define STR(s) _STR(s)                              //转换宏
#define HHI(xxx) ((byte)(((word)(xxx)>>24)))        //宏定义取32位数的最高8位
#define LHI(xxx) ((byte)(((word)(xxx)>>16)&0xFF))   //宏定义取32位数的次高8位
#define HLI(xxx) ((byte)(((word)(xxx)>>8)&0xFF))    //宏定义取32位数的次低8位
#define LLI(xxx) ((byte)(((word)(xxx)&0xFF)))       //宏定义取32位数的最低8位
#define MAX(x,y) (((x)>(y))?(x):(y))                //宏定义取最大值
#define MIN(x,y) (((x)<(y))?(x):(y))                //宏定义取最小值

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"原始值："<<STR(i)<<"=="<<i;           //分别以16进制和10进制输出i
    QList <quint8> Values;                          //定义一个8位的结构体
    Values<<HHI(i)<<LHI(i)<<HLI(i)<<LLI(i);         //将i的最高8位，次高8位次低8位，最低8位存入Values链表
    qDebug("0x%x==%d    0x%x==%d    0x%x==%d    0x%x==%d",Values.at(0),Values.at(0),
           Values.at(1),Values.at(1),Values.at(2),Values.at(2),Values.at(3),Values.at(3));
    qDebug("最高8位和次高8位最大值：0x%x<%d>",MAX(Values.at(0),Values.at(1)),MAX(Values.at(0),Values.at(1)));
    qDebug("次低8位和最低8位最大值：0x%x<%d>",MIN(Values.at(0),Values.at(1)),MIN(Values.at(2),Values.at(2)));
                                                    //分别以16进制和10进制输出最高8位，次高8位中的最大值与次低8位，最低8位中的最小值
    int _i=(Values.at(2)<<24)+(Values.at(0)<<16)+(Values.at(3)<<8)+Values.at(1);         //重新组合数值
    qDebug("重新组合后数值：0x%x<%d>",_i,_i);         //分别以16进制和10进制输出重组后的i
    qDebug()<<"排序前："<<Values;                   //输出排序前的Values链表
    std::sort(Values.begin(),Values.end(),[](int x,int y){return x>y;});        //将Values链表按从大到小排序
    qDebug()<<"排序后："<<Values;                   //输出排序后的Values链表
    return a.exec();
}

