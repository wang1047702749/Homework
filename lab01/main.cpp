#include <QCoreApplication>
#include <iostream>
#include <algorithm>
#include <QDebug>
#include <vector>
using namespace std;

//定义名为学生的结构体存放学生的学号、姓名、课程1及课程2成绩
struct Student
{
    int No;
    QString Name;
    int Lesson1;
    int Lesson2;
    //构造函数
    Student(int no,QString name,int lesson1,int lesson2){
        No=no;
        Name=name;
        Lesson1=lesson1;
        Lesson2=lesson2;
    };

};

//定义输出函数
void print_self(Student T){
    qDebug()<<T.No<<"\t"<<T.Name<<"\t"<<T.Lesson1<<"\t"<<T.Lesson2<<endl;
}
void print(vector<Student> ivec){
    qDebug()<<"学号"<<"\t\t"<<"姓名"<<"\t\t"<<"课程1"<<"\t"<<"课程2"<<"\t\t"<<endl;
    for_each(ivec.begin(),ivec.end(),print_self);
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //创建各个学生的档案
    vector<Student> ivec;
    ivec.push_back(Student(1403160111,"林冲",80,75));
    ivec.push_back(Student(1403160121,"鲁智深",74,95));
    ivec.push_back(Student(1403160108,"武松",84,67));
    ivec.push_back(Student(1403160115,"宋江",87,68));

    //输出原成绩及按各种排序方式后的成绩
    qDebug()<<"原成绩如下："<<endl;
    print(ivec);
    qDebug()<<"------------------------------------"<<endl;

    qDebug()<<"按姓名排序结果如下："<<endl;
    std::sort(ivec.begin(),ivec.end(),[](Student &T1,Student &T2){return T1.Name>T2.Name;});
    print(ivec);
    qDebug()<<"------------------------------------"<<endl;

    qDebug()<<"按课程1排序结果如下："<<endl;
    std::sort(ivec.begin(),ivec.end(),[](Student &T1,Student &T2){return T1.Lesson1>T2.Lesson1;});
    print(ivec);
    qDebug()<<"------------------------------------"<<endl;

    qDebug()<<"按课程2排序结果如下："<<endl;
    std::sort(ivec.begin(),ivec.end(),[](Student &T1,Student &T2){return T1.Lesson2>T2.Lesson2;});
    print(ivec);
    cout<<endl;

    return a.exec();
}
