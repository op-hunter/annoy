//
// Created by 李成明 on 2020-02-28.
//
#include <iostream>
#include <iomanip>
#include "../src/kissrandom.h"
#include "../src/xannoylib.h"
#include <chrono>
#include <algorithm>
#include <map>
#include <random>
#include "/usr/local/include/hdf5.h"
#include "/usr/local/include/H5Cpp.h"
#include "../src/ConcurrentBitset.h"
using namespace H5;

std::string file_path = "/Users/ophunter/Documents/workspace/data/";
std::string file_name = "sift-128-euclidean.hdf5";

void LoadData(const std::string file_location, float *&data, const std::string data_name, int &dim, int &num_vets) {
    hid_t fd;
    herr_t status;
    fd = H5Fopen(file_location.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
    hid_t dataset_id;
    dataset_id = H5Dopen2(fd, data_name.c_str(), H5P_DEFAULT);
    status = H5Dread(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
    hid_t dspace = H5Dget_space(dataset_id);
    hsize_t dims[2];
    H5Sget_simple_extent_dims(dspace, dims, NULL);
    num_vets = dims[0];
    dim = dims[1];
    status = H5Dclose(dataset_id);
    status = H5Fclose(fd);
}

int precision(int f=40, int n=1000000, int n_trees = 10, int search_k = 10, int query_times = 1000, int top_k = 100, int dp = 0){
    std::cout << "enter test function, args: "
              << "dim = " << f
              << "num of vectors = " << n
              << "num of query times = " << query_times
              << "num of results = " << top_k
              << "del percent = " << dp
              << "n_trees = " << n_trees << std::endl;
    std::chrono::high_resolution_clock::time_point t_start, t_end;

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    //******************************************************
    //Building the tree
    AnnoyIndex<int, float, Angular, Kiss32Random> t = AnnoyIndex<int, float, Angular, Kiss32Random>(f);

    std::cout << "Loading index ..." << std::endl;
    t_start = std::chrono::high_resolution_clock::now();
    t.load("precision.tree");
    t_end = std::chrono::high_resolution_clock::now();
    auto load_duration = std::chrono::duration_cast<std::chrono::milliseconds>( t_end - t_start ).count();
    std::cout << "Load Index Done in "<< load_duration << " ms." << std::endl;


    //******************************************************
    std::vector<int> results;
    faiss::ConcurrentBitsetPtr bitset = std::make_shared<faiss::ConcurrentBitset>(n + 1);
    int del_cnt = n / 100 * dp;
    while (del_cnt --) {
        int di = rand() % n + 1;
        if (bitset->test((faiss::ConcurrentBitset::id_type_t)di)) {
            del_cnt ++;
        }
        bitset->set((faiss::ConcurrentBitset::id_type_t)di);
    }
    t_start = std::chrono::high_resolution_clock::now();
    for (auto i = 0; i < query_times; ++ i) {
        int j = rand() % n + 1;
//        int j = n - 1;
//        results.resize(top_k);
        std::cout << "query id: " << j << std::endl;
//        bitset->set(j);
//        std::cout << "the deleted vec:" << std::endl;
//        for (auto dd = 0; dd < f; ++ dd)
//            std::cout << read_data[j * f + dd] << "  ";
//        std::cout << std::endl;
        t.get_nns_by_item(j, top_k, search_k, &results, nullptr, bitset);
        std::cout << "the " << i + 1 << "th query result:" << std::endl;
        for (auto c = 0; c < results.size(); ++ c) {
            std::cout << "result id: " << results[c] << std::endl;
//            for (auto dd = 0; dd < f; ++ dd)
//                std::cout << read_data[results[c] * f + dd] << "  ";
//            std::cout << std::endl;
        }
        std::cout << "-------------------------------------------------------------------------" << std::endl;
        results.clear();
    }
    t_end = std::chrono::high_resolution_clock::now();
    auto query_duration = std::chrono::duration_cast<std::chrono::milliseconds>( t_end - t_start ).count();
    std::cout << "Query Done in " << query_duration << " ms. of " << query_times << " times query" << std::endl;

    std::cout << "\nTest Done" << std::endl;
//    free(vec);
//    free(read_data);
    return 0;
}


void help(){
    std::cout << "Annoy Precision C++ example" << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "(default)		./precision" << std::endl;
    std::cout << "(using parameters)	./precision num_features num_nodes num_trees search_k query_times top_k" << std::endl;
    std::cout << std::endl;
}

void feedback(int f, int n, int n_trees, int search_k){
    std::cout<<"Runing precision example with:" << std::endl;
    std::cout<<"num. features: "<< f << std::endl;
    std::cout<<"num. nodes: "<< n << std::endl;
    std::cout<<"num. trees: "<< n_trees << std::endl;
    std::cout<<"num. inspect nodes: "<< search_k << std::endl;
    std::cout << std::endl;
}


int main(int argc, char **argv) {
    int f, n, n_trees, search_k;


    if(argc == 1){
        f = 40;
        n = 1000000;
        n_trees = 10;
        search_k = 10;

        feedback(f,n, n_trees, search_k);

        precision(40, 1000000, n_trees, search_k);
    }
    else if(argc == 8){

        f = atoi(argv[1]);
        n = atoi(argv[2]);
        n_trees = atoi(argv[3]);
        search_k = atoi(argv[4]);
        int query_times = atoi(argv[5]);
        int top_k = atoi(argv[6]);
        int dp = atoi(argv[7]);

        feedback(f,n, n_trees, search_k);

        precision(f, n, n_trees, search_k, query_times, top_k, dp);
    }
    else {
        help();
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}
