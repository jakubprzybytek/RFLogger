#include "Storage.hpp"

int main() {
	Storage storage("StorageTest-");
	storage.setReadSignature("test", 1.0, 2.0, 3.0, 4);

	Samples samples = { {1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0} };

	storage << Timestamped(7, samples);
}
