#include <QDebug>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <String>
#include <QByteArray>
#include <QDateTime>


typedef struct{
     QStringList list_stud;            //统一存储每个学生信息
} studData;

//重载运算符直接输出studData结构
QDebug operator<< (QDebug d, const studData &data) {
    for(int i=0;i<data.list_stud.size();i++)
    {
        d.noquote()<<data.list_stud.at(i);
    }
    qDebug()<<"";
    return d;
}

// 自定义用于排序的类
class sort_Column {
public:
    int Column;
    sort_Column(int Choose_Column) {
        Column = Choose_Column;
    }
    bool operator() (const studData& t1,const studData& t2) const;


};


//自定义比较各列并排序的函数
bool sort_Column::operator()(const studData &t1,const  studData &t2) const
{
//    qDebug()<<t1.list_stud.at(Column);
    if( t1.list_stud.at(Column)>t2.list_stud.at(Column))
        return true;
    return false;
\
}


class ScoreSorter
{
public:
    ScoreSorter(QString dataFile);
    void readFile();
    void doSort();
private:
    QString datafile;       //文件名
    QList <studData> stud;  //定义结构体链表
    QStringList    title;   //数据表头
};

//构造函数传递文件名
ScoreSorter::ScoreSorter(QString dataFile){
      datafile=dataFile;
}


//文件逐行读取并保存在结构体链表中
void ScoreSorter::readFile(){
        QFile file(datafile);
        if (!file.open(QFile::ReadOnly|QIODevice::Text)){
          qDebug()<<QString("文件 %1 打开失败").arg(datafile);
             return ;
        }
//        QTextStream in(&file);
//        file.setCodec("utf-8");
        qDebug().noquote().nospace()<<"开始读取文件："<<datafile;
        studData eve;
        //保存表头目录
        QString line1(file.readLine());
                title = line1.split(" ", QString::SkipEmptyParts);
                if(title.last() == "\n") title.removeLast();
        while (!file.atEnd()) {
            QString line =file.readLine();
            eve.list_stud=line.split("  ", QString::SkipEmptyParts); //保证数据按空格截取正常,去除\n
            if((eve.list_stud).last() == "\n") eve.list_stud.removeLast();
            if(eve.list_stud.size()==0) continue;
            stud.append(eve);
            QString str(line);
            qDebug()<<str;
        }
        file.close();
        qDebug().noquote().nospace()<<"文件读取完成："<<datafile;
}

//对txt文本文件按要求排序并输出到sorted_data.txt文本中
void ScoreSorter::doSort()
{
//对文本数据逐列排序
    for(int i=1;i<title.size();i++)
    {
        sort_Column now_Column(i-1);
        std::sort(stud.begin() , stud.end() , now_Column );

        qDebug()<<"排序后输出，当前排序第 "<<i <<" 列：";
         qDebug() << title;
        for(int i=0;i<stud.size();i++)
        qDebug() <<stud.at(i);
        qDebug()<<"-------------------------------------------------------\n";
    }
}


// 自定义消息处理程序,重载qDebug（）实现同时输出文件及控制台
//原文：https://blog.csdn.net/liang19890820/article/details/51838096
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toUtf8();

     // 设置输出信息格式
        QString strMessage = QString::fromLocal8Bit("%1 ").arg(localMsg.constData());
    // 输出信息至文件中（读写、追加形式）
       QFile file("sorted_data.txt");
       file.open(QIODevice::ReadWrite | QIODevice::Append);
       QTextStream stream(&file);
       qDebug().noquote().nospace() << strMessage;
       stream << strMessage<< "\r\n";
       file.flush();
       file.close();
}



int main()
{
// 安装消息处理程序
    qInstallMessageHandler(myMessageOutput);
    QString datafile = "data.txt";

//     如果排序后文件已存在，则删除之
    QFile f("sorted_"+datafile);
    if (f.exists()){
        f.remove();
    }

    ScoreSorter s(datafile);
    s.readFile();
    s.doSort();

    return 0;
}
