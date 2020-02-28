//
// Created by 李成明 on 2020-02-26.
//

#include<iostream>
#include "/usr/local/include/hdf5.h"
#include "/usr/local/include/H5Cpp.h"
using namespace H5;

void read_file(float *&data, int &row, int &col, const std::string file, const std::string data_name) {
    hid_t fd;
    herr_t status;
    fd = H5Fopen(file.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
    hid_t dataset_id;
    dataset_id = H5Dopen2(fd, data_name.c_str(), H5P_DEFAULT);
    status = H5Dread(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
    hid_t dspace = H5Dget_space(dataset_id);
    hsize_t dims[2];
    H5Sget_simple_extent_dims(dspace, dims, NULL);
    row = dims[0];
    col = dims[1];
    status = H5Dclose(dataset_id);
    status = H5Fclose(fd);
}

int main() {
    std::string file_path = "/Users/ophunter/Documents/workspace/data/";
    std::string file_name = "sift-128-euclidean.hdf5";
    float* readResult = (float*) malloc(512000000 * sizeof(float));
//    float readResult[10000];
    int row, col;
    read_file(readResult, row, col, file_path + file_name, "train");
    std::cout << "data row: " << row << ", data col: " << col << std::endl;
//    delete readResult;
    free(readResult);
    readResult = nullptr;
    return 0;
}