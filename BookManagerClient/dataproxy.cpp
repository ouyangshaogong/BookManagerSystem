#include "dataproxy.h"
#include "datacommonfunc.h"
#include <QDate>

DataProxy::~DataProxy()
{
    qDebug() << "DataProxy析构了";
}

void DataProxy::AddLevel(int nLevel)
{
    int level = 0;
    level += nLevel;
    NotifyMsg notifyRet;
    notifyRet.nMsg = MSG_ADDLEVEL;
    DataCommonFunc::Instance()->SendNotifyCationToView(notifyRet);
}

int DataProxy::AddUser(UserModel userModel)
{
    int nRet = 0;

    qDebug() << userModel.GetUserName().c_str();
    qDebug() << userModel.GetSex().c_str();
    qDebug() << userModel.GetBirth().c_str();
    qDebug() << userModel.GetAddress().c_str();
    qDebug() << userModel.GetPhone().c_str();
    qDebug() << QString::number(userModel.GetUserType());

    return nRet;
}

int DataProxy::DeleteUser(int userid)
{
    int nRet = 0;
    qDebug() << "DataProxy::DeleteUser" << QString::number(userid);
    return nRet;
}

int DataProxy::ModifyUser(int userid, string address)
{
    int nRet = 0;
    qDebug() << "DataProxy::ModifyUser" << QString::number(userid);
    qDebug() << "DataProxy::ModifyUser" << address.c_str();

    return nRet;
}

int DataProxy::QueryAllUser(set<UserModel> &setUserData)
{
    int nRet = 0;
    int count = 85;
    UserModel userModel[85];
    string strUserName[85] = {"彭万里", "高大山", "谢大海", "马宏宇", "林莽", "黄强辉", "章汉夫", "范长江", "林君雄", "谭平山"
                              "朱希亮", "李四光", "甘铁生", "张绍祖", "马继祖", "程孝先", "宗敬先", "年广嗣", "汤绍箕", "吕显祖"
                              "何光宗", "孙念祖", "马建国", "节振国", "冯兴国", "郝爱民", "于学忠", "马连良", "胡宝善", "李宗仁"
                              "洪学智", "余克勤", "吴克俭", "杨惟义", "李文信", "王德茂", "李书诚", "杨勇", "高尚德", "刁富贵"
                              "汤念祖", "吕奉先", "何光宗", "冷德友", "安怡孙", "贾德善", "蔡德霖", "关仁", "郑义贾怡", "孙天民"
                              "赵大华", "赵进喜", "赵德荣", "赵德茂", "钱汉祥", "钱运高", "钱生禄", "孙寿康", "孙应吉", "孙顺达"
                              "李秉贵", "李厚福", "李开富", "王子久", "刘永生", "刘宝瑞", "关玉和", "王仁兴", "李际泰", "罗元发"
                              "刘造时", "刘乃超", "刘长胜", "张成基", "张国柱", "张志远", "张广才", "吕德榜", "吕文达", "吴家栋"
                              "吴国梁", "吴立功李大江", "张石山", "王海"};

    for (int i = 0; i < count; ++i)
    {
        userModel[i].SetUserID(i + 1);
        userModel[i].SetReaderID(i + 1);
        userModel[i].SetUserName(strUserName[i]);
    }

    for (int i = 0; i < count; ++i)
    {
        if (i % 2 == 0)
        {
            userModel[i].SetSex("男");
        }
        else
        {
            userModel[i].SetSex("女");
        }
    }

    int i = 0;
    for(int m = 3; m <= 7; ++m)
    {
        for (int d = 1; d <= 15; ++d)
        {
            QDate date(1990, m, d);
            userModel[i].SetBirth(date.toString("yyyy-MM-dd").toUtf8().data());
            i++;
        }
    }

    string strAddress[] = {"纽约", "东京", "大阪", "北京", "西安", "上海", "华盛顿", "纽西蓝", "京都", "横滨",
                           "金陵", "建业", "建康", "江宁", "石头城", "临安", "钱塘", "武林", "姑苏", "吴郡",
                           "平江", "淮上", "江都", "广陵", "淮扬", "郢都", "郑城"};

    int iCount = 5;
    int u = 0;
    for (i = 0; i < iCount; ++i)
    {
        int jCount = 17;
        for (int j = 0; j < jCount; ++j)
        {
            userModel[u].SetAddress(strAddress[j]);
            u++;
        }
    }

    u = 0;
    for (i = 0; i < count; ++i)
    {
        userModel[i].SetUserType(i % 3);
    }

    u = 0;
    string strPhone("187293652");
    for (i = 0; i < count; ++i)
    {
        string tmpstr = strPhone + to_string(i + 10);
        userModel[i].SetPhone(tmpstr);
    }

    for (i = 0; i < count; ++i)
    {
        setUserData.insert(userModel[i]);
    }

    return nRet;
}

void DataProxy::AddBook()
{
    string str("AddBook");
    NotifyMsg notify;
    DataCommonFunc::Instance()->SendNotifyCationToView(notify);
}

void DataProxy::DeleteBook()
{
    string str("DeleteBook");
    NotifyMsg notify;
    DataCommonFunc::Instance()->SendNotifyCationToView(notify);
}

void DataProxy::ModifyBook()
{
    string str("ModifyBook");
    NotifyMsg notify;
    DataCommonFunc::Instance()->SendNotifyCationToView(notify);
}

void DataProxy::QueryBook()
{
    string str("QueryBook");
    NotifyMsg notify;
    DataCommonFunc::Instance()->SendNotifyCationToView(notify);
}

int DataProxy::QueryAllBook(set<BookModel> &setBookModel)
{
    int nRet = 0;
    int count = 60;
    string strBookName[] = {"巴尔扎克转", "木心回忆录", "甘地传", "故事的从扑", "关于书的书", "海明威传", "寒夜", "幻情心境", "红楼梦", "黄金时代",
                            "金庸笔下的情义世界", "金庸武侠评论", "金庸小说的爱情世界", "金庸小说论稿", "另眼看金庸", "论金庸小说的民族意识", "论金庸小说的影视剧技巧", "网人论金庸", "我看金庸", "香港的前途",
                            "胡适书话", "胡适自传", "梁实秋传", "林语堂书话", "林语堂自传一", "林语堂自传二", "林语堂自传三", "林语堂自传四", "林语堂自传五", "林语堂自传六",
                            "爱与生的苦恼", "安娜", "茶花女", "悲惨世界", "雷雨", "飘", "挪威的森林", "围城", "正在发育", "麦田里的守望者",
                            "linux安全体系与编程", "linux程序设计", "linux高级程序设计", "linux二进制分析", "linux环境编程", "linux内核编程", "linux性能调优", "unix环境高级编程", "程序员的自我修养", "深入理解linux内核",
                            "c++Plus Primer", "c++STL程序员开发指南", "c++沉思录", "c++开发实战", "编程之美", "编程珠玑", "设计模式", "leetcode", "c语言程序设计", "高性能MySQL"};
    int i = 0;
    BookModel bookModel[60];
    for (i = 0; i < count; ++i)
    {
        bookModel[i].SetName(strBookName[i]);
        bookModel[i].SetBookID(i);
        bookModel[i].SetClassID(i % 10);
    }
    string strAuthor[] = {"路遥", "陀思妥耶夫斯基", "村上春树", "托尔斯泰", "大仲马", "普鲁斯特", "马里奥·普佐", "荷马", "乔斯坦·贾德", "乔伊斯",
            "塞林格", "但丁", "陈忠实", "歌德", "莎士比亚", "福楼拜", "紫式部", "福克纳", "曹雪芹", "博尔赫斯"
            "马尔克斯", "三岛由纪夫", "卡夫卡", "艾略特", "菲茨杰拉德", "托马斯·曼", "穆齐尔", "胡适", "林语堂", "金庸"};
    for (i = 0; i < count; ++i)
    {
        bookModel[i].SetAuthor(strAuthor[i % 30]);
    }

    string strPublish[] = {"培生", "新星出版社", "汤姆森路透", "里德爱斯维尔", "威科", "企鹅兰登书屋", "中国南方出版传媒集团", "阿歇特图书", "麦格希教育", "环球出版集团"};
    for (i = 0; i < count; ++i)
    {
        bookModel[i].SetPublish(strPublish[i % 10]);
    }
    //ISBN从4开始生成十位数字
    string strISBN("41240317");
    for (i = 0; i < count; ++i)
    {
        string tmpstr = strISBN + to_string(i + 13);
        bookModel[i].SetISBN(tmpstr);
    }
    //简介，统一生成一种介绍
    for (i = 0; i < count; ++i)
    {
        string str("牵出一生的纠缠。大学时代的赵默笙阳光灿烂，对法学系大才子何以琛一见倾心，开朗直率的她拔足倒追，终于使");
        bookModel[i].SetIntroduction(str);
    }

    //语言
    string strLanguage[] = {"中文", "英文", "日本", "韩文", "法文", "俄语", "意大利语", "波斯文", "梵语", "土耳其文"};
    for (i = 0; i < count; ++i)
    {
        bookModel[i].SetLanguage(strLanguage[i % 10]);
    }

    //价格　60 -> 200
    for (i = 0; i < count; ++i)
    {
        bookModel[i].SetPrice(i + 67);
    }

    //出版日期　随机生成
    int nD = 0;
    for(int m = 7; m <= 8; ++m)
    {
        for (int d = 1; d <= 30; ++d)
        {
            QDate date(2007, m, d);
            bookModel[nD].SetPubDate(date.toString("yyyy-MM-dd").toUtf8().data());
            nD++;
        }
    }
    //剩余数量0 -> 20
    for (i = 0; i < count; ++i)
    {
        bookModel[i].SetNumber(i % 20);
    }

    for (i = 0; i < count; ++i)
    {
        setBookModel.insert(bookModel[i]);
    }

    return nRet;
}

