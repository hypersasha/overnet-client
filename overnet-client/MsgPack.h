//
// Created by Alexander on 14.02.18.
//

#ifndef UNIXSERVER_MSGPACK_H
#define UNIXSERVER_MSGPACK_H

#include <iostream>
#include <cstdio>
#include <cstring>

template <class T>
class MsgPack {
public:
    MsgPack(int, int);
    MsgPack(char *);
    ~MsgPack();

    template <typename PACK>
    void pack(PACK, int);

    template <typename PACK>
    void unpack(PACK, int);

    char* getPack();

    int addOffset(int);
    int offset();
    int size();
    int type();

private:
    void pre_pack(int);
    void pre_unpack(int *, char*);

    int offsetBytes = 0;
    int messageSize = 0;
    int messageType = 0;

    char *buffer;
};
#endif //UNIXSERVER_MSGPACK_H
