//yue ding shaungfang de duihua geshi
#ifndef PROTO_H_
#define PROTO_H_
#define KEYPATH "/etc/services"
#define KEYPROJ 'g'//biaoshi zhengxing
#define NAMESIZE 32
struct msg_st
{
    long mtype;
    char name[NAMESIZE];
    int math;
    int chinese;
};


#endif
