//
// Created by Alexander on 15.02.18.
//

#ifndef UNIXSERVER_MSGPACKTEST_H
#define UNIXSERVER_MSGPACKTEST_H


class MsgPackTest {
public:
    MsgPackTest();
    ~MsgPackTest();

    void Integer_13_13Returned();
    void Double_1337_1337Returned();
    void Char_CharReturned();
    void Array10x10_Array10x10Returned();
    void Array2x4_Array2x4Returned();
    void Array4x2_Array4x2Returned();
    void Array5x2_Array5x2Returned();
    void Array3x2DobuleInt();
	void End();
};


#endif //UNIXSERVER_MSGPACKTEST_H
