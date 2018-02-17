#include <iostream>
#include <fstream>
#include <ctime>
#include <conio.h>
#include "Overnet.h"
#include "MsgPackTest.h"

using namespace std;

void onMessageReceived(char* buffer)
{
	MsgPack<int> message(buffer);
	printf("Received message type is [%d].\n", message.type());

	// If this is a text message
	if (message.type() == MESSAGE) {
		int textSize = message.size() - sizeof(int) * 2;
		char* text = new char[textSize];
		memset(text, 0, textSize);
		message.unpack(text, textSize);
		printf("%s", text);
	}

	// If this is a TEST BLOCK message
	if (message.type() == TEST_BLOCK) {
		int block_id = 0;
		int block_id_row = 0;
		int n = 0;
		int m = 0;
		int i, j;

		message.unpack(&block_id, sizeof(block_id));
		message.unpack(&block_id_row, sizeof(block_id_row));
		message.unpack(&n, sizeof(n));
		message.unpack(&m, sizeof(m));

		int *block = new int[n * m];
		message.unpack(block, sizeof(int) * n * m);

		// Output block to file
		ofstream fout;
		fout.open("out.txt");
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				fout << *(block + i * m + j) << " ";
			}
			fout << endl;
		}
		fout.close();
	}
}

int main() {

	// Before connect to the server
	// Do some [Tests]
	
	MsgPackTest tester;
	tester.Integer_13_13Returned();
	tester.Double_1337_1337Returned();
	tester.Char_CharReturned();
	tester.Array2x4_Array2x4Returned();
	tester.Array3x2DobuleInt();
	tester.Array4x2_Array4x2Returned();
	tester.End();

	// Connect to server
	// Uncomment the code below after [Tests]
	//Client client("18.196.4.216", 2000);
	//client.Run(onMessageReceived);

	cin.get();
	return 0;
}