/**
 * Use kNN (by KD-tree) to classify minist dataset
 * Training set: 60,000 images
 * Testing set: 10,000 images
 */

#define USE_MNIST_LOADER
#define MNIST_DOUBLE

#include <iostream>
#include <vector>
#include <mutex>    // for mutex
#include <thread>   // for thread
#include <ctime>    // for CLOCKS_PER_SEC
/* #include <chrono> */

#include "mnist.h"
#include "point.h"
#include "kdTree.h"

using std::vector;
using std::pair;
using std::mutex;
using std::thread;
using std::cout;
using std::endl;
using std::ctime;
using std::ref;

using dataset = vector<pair<Point<784>, unsigned int>>;
using uint = unsigned int;

// number of threads to use for kNN calssification
static const int numThreads = 8;
static int numProcessed;
static int correctCount;
static mutex lock;


// Perform kNN classification on dataset[start, end) using kd-tree
// and update global counters
static void kNN(
        int start,
        int end,
        const KDTree<784, uint>& kdTree,
        size_t k,
        const dataset& data) {
    for (int i = start; i < end; ++i) {
        const auto &p = data[i];
        uint label = kdTree.kNNValue(p.first, k);

        lock.lock();
        ++numProcessed;
        if (label == p.second) ++correctCount;
        if (numProcessed % 500 == 0) cout << numProcessed << "..." << endl;
        lock.unlock();
    }
}

// Transform loaded data to the format that KD-Tree constructor accepts
void vectorize(mnist_data* rawData, uint count, dataset& data) {
    for (int i = 0; i < count; ++i) {
        vector<double> x;
        for (int j = 0; j < 28; ++j) {
            for (int k = 0; k < 28; ++k) {
                x.push_back(rawData[i].data[j][k]);
            }
        }

        Point<784> pt;
        copy(x.begin(), x.end(), pt.begin());
        data.push_back({pt, rawData[i].label});
    }
}

int main(void)
{
    // Load the MNIST dataset
    mnist_data *rawTrainData, *rawTestData;
    uint trainCnt, testCnt;

    mnist_load("mnist_data/train-images-idx3-ubyte",
            "mnist_data/train-labels-idx1-ubyte",
            &rawTrainData,
            &trainCnt
        );

    mnist_load("mnist_data/t10k-images-idx3-ubyte",
            "mnist_data/t10k-labels-idx1-ubyte",
            &rawTestData,
            &testCnt
        );

    cout << "[+] Finished loading data from disk!" << endl
        << "[+] Training set size: " << trainCnt << endl
        << "[+] Testing set sie: " << testCnt << endl;

    // Data vectorization.
    dataset trainData, testData;
    vectorize(rawTrainData, trainCnt, trainData);
    vectorize(rawTestData, testCnt, testData);

    cout << "[+] Finish data vectorizition" << endl;

    // construct kd-Tree using training set
    KDTree<784, uint> tree(trainData);

    cout << "[+] KD-Tree built completely" << endl;

    // sanity check on the training set
    cout << endl
       << "start sanity check: contains() should return `true` for training "
      << "data, and 1-NN (k = 1) training set accuracy should be perfect \n";

    bool sanityPass = true;
    for (int i = 0; i < 100; ++i) {
        Point<784> pt = trainData[i].first;
        if (!tree.contains(pt) || tree.kNNValue(pt, 1) != trainData[i].second) {
            sanityPass = false;
            break;
        }
    }

    if (sanityPass) {
        cout << "[+] sanity check PASSED!" << endl;
    } else {
        cout << "[+] sanity check FAILED!" << endl;
    }

    // Evaluate on testing data
    size_t k = 3;
    numProcessed = 0;
    correctCount = 0;
    int cntPerThread = testCnt / numThreads;
    clock_t c_start = clock();
    auto t_start = std::chrono::high_resolution_clock::now();
    vector<thread> threads;

    cout << "[+] start evaluating kNN performance on the test set \n"
        << "\t k = " << k << endl;
    for (int i = 0; i < numThreads; ++i) {
        int start = i * cntPerThread;
        int end = (i == numThreads - 1) ? testCnt : start + cntPerThread;
        threads.push_back(thread(kNN, start, end, ref(tree), k, ref(testData)));
    }

    for (thread &t : threads) {
        t.join();
    }

    clock_t c_end = clock();
    auto t_end = std::chrono::high_resolution_clock::now();

    cout << "[+] Test accuracy: " << correctCount * 100.0 / testCnt << "%\n";
    cout << "[+] CPU Time elapsed: " <<
        (double)(c_end - c_start) << endl;
    cout << "[+] Wall time elapsed: " <<
        std::chrono::duration<double>(t_end - t_start).count() << endl;

    free(rawTrainData);
    free(rawTestData);

    return 0;
}
