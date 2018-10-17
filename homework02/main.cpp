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

//重载运算符输出studData结构
QDebug operator<< (QDebug d, const studData &data) {
    for(int i=0;i<data.list_stud.size();i++)
    {
        d.noquote()<<data.list_stud.at(i);
    }
    qDebug()<<"";
    return d;
}

// 自定义用于比较各列的函数
class sort_Column {
public:
    int Column;
    sort_Column(int Choose_Column) {
        Column = Choose_Column;
    }
    bool operator() (const studData& t1,const studData& t2) const;


};


//自定义比较函数
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
    QString datafile;
    QList <studData> stud;
    QStringList    title;   //数据表头
};

ScoreSorter::ScoreSorter(QString dataFile){
      datafile=dataFile;

}



void ScoreSorter::readFile(){
        QFile file(datafile);
        if (!file.open(QFile::ReadOnly|QIODevice::Text)){
          qDebug()<<QString("文件 %1 打开失败").arg(datafile);
             return ;
        }
//        QTextStream in(&file);
//        in.setCodec("utf-8");
        qDebug().noquote().nospace()<<"开始读取文件："<<datafile;
        studData eve;
        QString line1(file.readLine());
                title = line1.split(" ", QString::SkipEmptyParts);
        while (!file.atEnd()) {
            QString line =file.readLine();
            eve.list_stud=line.split("  ", QString::SkipEmptyParts); //保证数据的截取正常,去除\n
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

void ScoreSorter::doSort()
{
    QFile file("sorted_"+datafile);
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream txtout(&file);
    txtout.setCodec("utf-8");  //采用“utf-8”编码

    for(int i=1;i<title.size();i++)
    {
        sort_Column now_Column(i-1);
        std::sort(stud.begin() , stud.end() , now_Column );

        qDebug()<<"排序后输出，当前排序第 "<<i <<" 列：";
        qDebug()<< title;
        for(int i=0;i<stud.size();i++)
        qDebug() <<stud.at(i);
        qDebug()<<"---------------------------------\n";


    for(int j=0;j<title.size();j++)
        txtout<<title.at(j)<<"\t";
    txtout<<"\r\n";
    for(int i=0;i<stud.size();i++)
    {
        for(int j=0;j<title.size()-1;j++)
            txtout<<stud.at(i).list_stud.at(j)<<"\t";
        txtout<<"\r\n";
    }
    txtout<<"---------------------------------------"<<"\r\n";
    }
    file.close();

    }



int main()
{
//    qInstallMessageHandler(myMessageOutput);
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
