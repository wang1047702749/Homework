#include <QDebug>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <String>
#include<iostream>
#include<QDataStream>
#include <QByteArray>



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
        while (!file.atEnd()) {
            QString line =file.readLine();
            eve.list_stud=line.split("  ", QString::SkipEmptyParts); //保证数据按空格截取正常,去除\n
            if((eve.list_stud).last() == "\n") eve.list_stud.removeLast();
            if(eve.list_stud.size()==0) continue;
            stud.append(eve);
            QString str(line);
            qDebug()<<str;
//            for(auto s:data)
//                qDebug().noquote().nospace()<<s;
        }
        file.close();
        qDebug().noquote().nospace()<<"文件读取完成："<<datafile;
}

//对txt文本文件按要求排序并输出到sorted_data.txt文本中
void ScoreSorter::doSort()
{
    QFile file("sorted_"+datafile);
//    file.open(QIODevice::ReadWrite | QIODevice::Text);
    if (!file.open(QFile::WriteOnly|QIODevice::Text)){
      qDebug()<<QString("文件 %1 打开失败").arg(datafile);
         return ;
    }
    qDebug().noquote().nospace()<<"开始写入文件："<<datafile;
    QTextStream txtout(&file);
    txtout.setCodec("utf-8");  //采用“utf-8”编码
//对文本数据逐列排序
    for(int i=1;i<title.size();i++)
    {
        sort_Column now_Column(i-1);
        std::sort(stud.begin() , stud.end() , now_Column );

        qDebug()<<"排序后输出，当前排序第 "<<i <<" 列：";
        qDebug()<< title;
        for(int i=0;i<stud.size();i++)
        qDebug() <<stud.at(i);
        qDebug()<<"-------------------------------------------------------\n";


    for(int j=0;j<title.size();j++)
        txtout<<title.at(j)<<"\t";
    txtout<<"\r\n";
    for(int i=0;i<stud.size();i++)
    {
        for(int j=0;j<title.size()-1;j++)
            txtout<<stud.at(i).list_stud.at(j)<<"\t";
        txtout<<"\r\n";
    }
    txtout<<"-------------------------------------------------------------"<<"\r\n";
    }

    file.close();
    qDebug().noquote().nospace()<<"文件写入完成："<<datafile;
    }


// 自定义消息处理程序
//原文：https://blog.csdn.net/liang19890820/article/details/51838096
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
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
    // 打印信息
    qDebug("This is a debug message.");
    qWarning("This is a warning message.");
    qCritical("This is a critical message.");
    qFatal("This is a fatal message.");
    return 0;
}
