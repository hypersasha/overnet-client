#include "MsgPack.h"

template <class T>
MsgPack<T>::MsgPack(int msgType, int msgSize) {
    messageSize = msgSize + sizeof(messageSize) + sizeof(messageType);
    messageType = msgType;
    buffer = new char[messageSize];

    // Add to buffer the FullSize of message
    // and it's type
    pre_pack(messageSize);
    pre_pack(messageType);
#ifdef DEBUG
	printf("[MsgPack] New message with %d bytes.\n", msgSize);
	printf("\n[MsgPack] Initialized new message instance with type %d.\nYou want put %d bytes.\nThe fullSize will be %d bytes.\n\n", msgType, msgSize, messageSize);
#endif // DEBUG
}

template <class T>
MsgPack<T>::MsgPack(char* buffer) {
    // Get full size from message
    pre_unpack(&messageSize, buffer);
    pre_unpack(&messageType, buffer);

    this->buffer = new char[messageSize];
    memcpy(this->buffer, (const void *)buffer, messageSize);
}

template <class T>
MsgPack<T>::~MsgPack() {
	delete[] buffer;
#ifdef DEBUG
	printf("\n[MsgPack] Instance is being deleted.\n\n");
#endif // DEBUG
}

template <class T>
template <typename PACK>
void MsgPack<T>::pack(PACK packet, int size) {
    if (size <= 0)
    {
        size = sizeof(packet);
        if (size <= 0)
        {
            perror("[Warning!] Size of DataPacket must be greater then 0.\n");
            exit(1);
        }
    }

    // Copy new packet to buffer
    memcpy(getPack() + offsetBytes, packet, size);
    offsetBytes += size;
    
#ifdef DEBUG
	printf("Copying data to buffer: offset is %d bytes.\n", offsetBytes);
#endif // DEBUG
}

template <class T>
template <typename PACK>
void MsgPack<T>::unpack(PACK destination, int size) {
    if (size <= 0)
    {
        perror("[Warning!] Size of DataPacket to unpack must be greater then 0.\n");
        exit(1);
    }

    // Copy pack to destination
    memcpy(destination, buffer + offsetBytes, size);
    offsetBytes += size;
}

template <class T>
void MsgPack<T>::pre_pack(int packet){
    memcpy(getPack() + offsetBytes, &packet, sizeof(packet));
    offsetBytes += sizeof(packet);
    //printf("Copying data to buffer: offset is %d bytes.\n", offsetBytes);
}

template <class T>
void MsgPack<T>::pre_unpack(int *packet, char * buffer) {
    memcpy(packet, buffer + offsetBytes, sizeof(packet));
    offsetBytes += sizeof(int);
}

template <class T>
int MsgPack<T>::size() {
    return messageSize;
}

template <class T>
int MsgPack<T>::type() {
    return messageType;
}

template <class T>
int MsgPack<T>::offset(){
    return offsetBytes;
}

template <class T>
int MsgPack<T>::addOffset(int offset) {
    offsetBytes += offset;
    return offsetBytes;
}

template <class T>
char* MsgPack<T>::getPack() {
    return buffer;
}
