#include <iostream>
#include <fstream>
#include <ctime>
#include <conio.h>
#include "Overnet.h"
#include "MsgPackTest.h"

using namespace std;

int blockFile = 0;
Client client("52.165.239.104", 2000);

void onMessageReceived(char* buffer)
{
	MsgPack<int> message(buffer);

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

		int i = 0, j = 0, rows = 0, cols = 0, blockId = 0, blockIdRow = 0, dimension = 0;

		// Unpack all parameters
		message.unpack(&rows, sizeof(rows));
		message.unpack(&cols, sizeof(cols));
		message.unpack(&blockId, sizeof(blockId));
		message.unpack(&blockIdRow, sizeof(blockIdRow));
		message.unpack(&dimension, sizeof(dimension));

		int *first_block = new int[rows * cols];
		message.unpack(first_block, sizeof(int) * rows * cols);

		int *second_block = new int[rows * cols];
		message.unpack(second_block, sizeof(int) * rows * cols);

		printf("[OVERNET] New block received (%d x %d), calculating...\n", rows, cols);

		// Print sum of blocks
		/*for (i = 0; i < rows; ++i) {
			for (j = 0; j < cols; ++j) {
				*(second_block + i * cols + j) = *(first_block + i * cols + j) + *(second_block + i * cols + j);
				cout << *(second_block + i * cols + j) << '\t';
			}
			cout << endl;
		}*/

		// Send response
		int packetSize = sizeof(rows) + sizeof(cols) + sizeof(blockId) + sizeof(blockIdRow) + sizeof(dimension);
		packetSize += sizeof(int) * rows * cols;

		MsgPack<const void *> resp(RESULT, packetSize);

		// Pack parameters
		resp.pack(&rows, sizeof(rows));
		resp.pack(&cols, sizeof(cols));
		resp.pack(&blockId, sizeof(blockId));
		resp.pack(&blockIdRow, sizeof(blockIdRow));
		resp.pack(&dimension, sizeof(dimension));

		// Pack result block
		resp.pack((const void *)second_block, sizeof(int) * rows * cols);

		//resp.pack(&response, sizeof(response));
		client.Send(resp.getPack(), resp.size());

		delete[] first_block;
		delete[] second_block;
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
	// client.Run(onMessageReceived);

	cin.get();
	return 0;
}