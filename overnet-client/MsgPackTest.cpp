#include "MsgPackTest.h"
#include "MsgPack.h"
#include "MsgPack.cpp"
#include <iostream>
#include <string>

MsgPackTest::MsgPackTest(){}
MsgPackTest::~MsgPackTest(){}

void MsgPackTest::Integer_13_13Returned() {
    try {
        int test = 1488;
        MsgPack<int> tester(0, sizeof(test));
        tester.pack(&test, sizeof(test));

        int testResult = 0;
        MsgPack<int> tester_unpack(tester.getPack());
        tester_unpack.unpack(&testResult, sizeof(testResult));

        if (test != testResult || 0 != tester_unpack.type() || (sizeof(test) + sizeof(int) + sizeof(int)) != tester_unpack.size())
        {
            throw "Integer_13";
		}
		else {
			puts("Test Integer_13 passed!");
		}
    } catch (const char* e)
    {
        printf("[MsgPackTest] FAILED TEST #%s", e);
    }
}

void MsgPackTest::Double_1337_1337Returned() {
    try {
        double test = 13.37;
        MsgPack<double> tester(0, sizeof(test));
        tester.pack(&test, sizeof(test));

        double testResult = 0;
        MsgPack<double> tester_unpack(tester.getPack());
        tester_unpack.unpack(&testResult, sizeof(testResult));

        printf("[MsgPackTest] Result: %f", testResult);
        if (test != testResult)
        {
            throw "Double_1337";
        }
    } catch (const char* e)
    {
        printf("[MsgPackTest] FAILED TEST #%s", e);
    }
}

void MsgPackTest::Char_CharReturned() {
    try {
        std::string test = "This\nis\na test\nstring.\n";
        int size = strlen(test.c_str());

        // Initiate new char array and put string here. size+1 for \0 symbol
		std::cout << sizeof(char) << std::endl;
        char *str = new char[size + 1];
		memset(str, 0, size + 1);
        strncpy(str, test.c_str(), size);
        str[size + 1] = '\0';

        // Pack this char
        MsgPack<const void*> motd(12, size + 1);
        motd.pack((const void *)str, size + 1);

        // Extract packed char
        char *testResult = new char[size + 1];
        MsgPack<const void *> motd_extract(motd.getPack());
        motd_extract.unpack(testResult, size + 1);

        printf("[MsgPackTest] Test string:\n%s", str);
        printf("[MsgPackTest] Result string:\n%s", testResult);

        // Check
        if (strcmp(str, testResult) != 0)
        {
            throw "Char";
        }
		else {
			puts("Test Char passed!");
		}
    } catch (const char* e) {
        printf("[MsgPackTest] FAILED TEST #%s", e);
    }
}

void MsgPackTest::Array10x10_Array10x10Returned() {
    int n = 10, m = 10;
    printf("[MsgPackTest] Initializing %d x %d array.\n", n, m);
    int *a = new int[n * m];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            *(a + i * n + j) = rand() % 10;
            std::cout << *(a + i * n + j) << " ";
        }
        std::cout << std::endl;
    }

    int size = sizeof(int) * n * m;

    MsgPack<const void *> motd(1, size);
    motd.pack((const void *)a, size);

    // Extract
    int *b = new int[n * m];
    printf("[MsgPackTest] Extracting dynamic int array.\n");
    MsgPack<const void *> motd_extract(motd.getPack());
    motd_extract.unpack(b, size);

    try {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (*(b + i * n + j) != *(a + i * n + j))
                {
                    throw "Array";
                }
                std::cout << *(b + i * n + j) << " ";
            }
            std::cout << std::endl;
        }
    } catch (const char* e)
    {
        printf("[MsgPackTest] FAILED TEST #%s", e);
    }
}

void MsgPackTest::Array2x4_Array2x4Returned() {
    int n = 2, m = 4;
    printf("[MsgPackTest] Initializing %d x %d array.\n", n, m);
    int *a = new int[n * m];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            *(a + i * n + j) = rand() % 10;
            std::cout << *(a + i * n + j) << " ";
        }
        std::cout << std::endl;
    }

    int size = sizeof(int) * n * m;

    MsgPack<const void *> motd(1, size);
    motd.pack((const void *)a, size);

    // Extract
    int *b = new int[n * m];
    printf("[MsgPackTest] Extracting dynamic int array.\n");
    MsgPack<const void *> motd_extract(motd.getPack());
    motd_extract.unpack(b, size);

    try {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (*(b + i * n + j) != *(a + i * n + j))
                {
                    throw "Array";
                }
                std::cout << *(b + i * n + j) << " ";
            }
            std::cout << std::endl;
        }
    } catch (const char* e)
    {
        printf("[MsgPackTest] FAILED TEST #%s", e);
    }
}

void MsgPackTest::Array4x2_Array4x2Returned() {
    int n = 3, m = 2;
    printf("[MsgPackTest] Initializing %d x %d array.\n", n, m);
    int *a = new int[n * m];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            *(a + i * n + j) = rand() % 10;
            std::cout << *(a + i * n + j) << " ";
        }
        std::cout << std::endl;
    }

    int size = sizeof(int) * n * m;

    MsgPack<const void *> motd(1, size);
    motd.pack((const void *)a, size);

    // Extract
    int *b = new int[n * m];
    printf("[MsgPackTest] Extracting dynamic int array.\n");
    MsgPack<const void *> motd_extract(motd.getPack());
    motd_extract.unpack(b, size);

    try {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (*(b + i * n + j) != *(a + i * n + j))
                {
                    throw "Array";
                }
                std::cout << *(b + i * n + j) << " ";
            }
            std::cout << std::endl;
        }
    } catch (const char* e)
    {
        printf("[MsgPackTest] FAILED TEST #%s", e);
    }
}

void MsgPackTest::Array5x2_Array5x2Returned() {
    int n = 5, m = 2;
    printf("[MsgPackTest] Initializing %d x %d array.\n", n, m);
    int *a = new int[n * m];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            *(a + i * n + j) = rand() % 10;
            std::cout << *(a + i * n + j) << " ";
        }
        std::cout << std::endl;
    }

    int size = sizeof(int) * n * m;

    MsgPack<const void *> motd(1, size);
    motd.pack((const void *)a, size);

    // Extract
    int *b = new int[n * m];
    printf("[MsgPackTest] Extracting dynamic int array.\n");
    MsgPack<const void *> motd_extract(motd.getPack());
    motd_extract.unpack(b, size);

    try {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (*(b + i * n + j) != *(a + i * n + j))
                {
                    throw "Array";
                }
                std::cout << *(b + i * n + j) << " ";
            }
            std::cout << std::endl;
        }
    } catch (const char* e)
    {
        printf("[MsgPackTest] FAILED TEST #%s", e);
    }
}

void MsgPackTest::Array3x2DobuleInt() {
    int n = 3, m = 2;
    printf("[MsgPackTest] Initializing %d x %d array.\n", n, m);
    int *a = new int[n * m];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            *(a + i * n + j) = rand() % 10;
            std::cout << *(a + i * n + j) << " ";
        }
        std::cout << std::endl;
    }

    int size = sizeof(int) * n * m;

    MsgPack<const void *> motd(1, size + sizeof(double) + sizeof(int));
    motd.pack((const void *)a, size);

    // Now pack double
    double test = 14.88;
    motd.pack(&test, sizeof(double));

    // Pack Int
    int testInt = 1337;
    motd.pack(&testInt, sizeof(int));

    // Extract
    int *b = new int[n * m];
    printf("[MsgPackTest] Extracting dynamic int array.\n");
    MsgPack<const void *> motd_extract(motd.getPack());
    motd_extract.unpack(b, size);

    try {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (*(b + i * n + j) != *(a + i * n + j))
                {
                    throw "Array3x2DoubleInt_Array3x2";
                }
                std::cout << *(b + i * n + j) << " ";
            }
            std::cout << std::endl;
        }
    } catch (const char* e)
    {
        printf("[MsgPackTest] FAILED TEST #%s", e);
        exit(1);
    }

    double testResult = 0.0;
    motd_extract.unpack(&testResult, sizeof(testResult));

    int testIntResult = 0;
    motd_extract.unpack(&testIntResult, sizeof(testIntResult));

    try {
        if (test != testResult || testInt != testIntResult)
        {
            throw "Array3x2DoubleInt_Double_Int";
        }
    } catch (const char *e)
    {
        printf("[MsgPackTest] FAILED TEST #%s", e);
    }
}

void MsgPackTest::End() {
	puts("\n\n************** YEAH! ******************\nAll test were complete.\nPlease, check console for '[MsgPackTest] FAILED' logs.\n");
}