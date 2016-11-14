#include "Storage.hpp"

int main() {
    ofstream os ("samplesCollection.test");
    text_oarchive archive(os);

    ReadSignature readSignature("test", 1.0, 2.0, 3.0);
    Samples samples = { {1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0} };
    SamplesCollection samplesCollection(readSignature, samples);

    archive << samplesCollection;
}
