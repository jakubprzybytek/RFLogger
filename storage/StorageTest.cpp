#include "Storage.hpp"

int main() {
    ofstream os ("samplesCollection.test");
    text_oarchive archive(os);

    Samples samples = { {1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0} };
    SamplesCollection samplesCollection(samples);

    archive << samplesCollection;
}
