#include "../common/stdUtils.hpp"

#include "Storage.hpp"

void exportTest() {
	
	cout << "Export text" << endl;
	
	Storage storage("StorageTest-");
	storage.setReadSignature("test", 1.0, 2.0, 3.0, 4);

	Samples samples = { {1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0} };
	cout << samples << endl;
	
	storage << Timestamped(Timestamp::NOW(), samples);
}

void importTest() {
	
	cout << "Import text" << endl;
	
	SamplesCollection samplesCollection;
	
	Storage storage("StorageTest-");
	storage >> samplesCollection;
	
	cout << samplesCollection.timestampedSamplesList.front().samples << endl;
}

int main() {
	exportTest();
	importTest();
}
