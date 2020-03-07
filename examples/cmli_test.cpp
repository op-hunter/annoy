/*
 * precision_test.cpp

 *
 *  Created on: Jul 13, 2016
 *      Author: Claudio Sanhueza
 *      Contact: csanhuezalobos@gmail.com
 */

#include <iostream>
#include <iomanip>
#include "../src/kissrandom.h"
#include "../src/annoylib.h"
#include <chrono>
#include <algorithm>
#include <map>
#include <random>
#include "/usr/local/include/hdf5.h"
#include "/usr/local/include/H5Cpp.h"
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

int precision(int f=40, int n=1000000, int n_trees = 10, int search_k = 10, int query_times = 1000, int top_k = 100){
	std::cout << "enter test function, args: "
			  << "dim = " << f
			  << "num of vectors = " << n
			  << "num of query times = " << query_times
			  << "num of results = " << top_k
			  << "n_trees = " << n_trees << std::endl;
	std::chrono::high_resolution_clock::time_point t_start, t_end;

	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0.0, 1.0);

	//******************************************************
	//Building the tree
	AnnoyIndex<int, double, Angular, Kiss32Random> t = AnnoyIndex<int, double, Angular, Kiss32Random>(f);

	std::cout << "Building index ... be patient !!" << std::endl;
	std::cout << "\"Trees that are slow to grow bear the best fruit\" (Moliere)" << std::endl;

	float* read_data = (float*) malloc(512000000);
	std::cout << "start load data from " << file_path + file_name << std::endl;
	LoadData(file_path + file_name, read_data, "train", f, n);
	std::cout << "data load finished, new dim: " << f << ", new num of vectors: " << n << std::endl;


	std::cout << "start insert vectors into AnnoyIndex..." << std::endl;
	t_start = std::chrono::high_resolution_clock::now();
	long base = 0;
	for(int i=0; i<n; ++i){
		double *vec = (double *) malloc( f * sizeof(double) );
		base = (long)f * i;

		for(int z=0; z<f; ++z){
			vec[z] = read_data[base + z];
		}

		t.add_item(i, vec);

//		std::cout << "Loading objects ...\t object: "<< i+1 << "\tProgress:"<< std::fixed << std::setprecision(2) << (double) i / (double)(n + 1) * 100 << "%\r";

	}
	t_end = std::chrono::high_resolution_clock::now();
	auto insert_duration = std::chrono::duration_cast<std::chrono::seconds>( t_end - t_start ).count();
	std::cout << "Insert Done in " << insert_duration << " secs." << std::endl;
	std::cout << std::endl;
	free(read_data);
	std::cout << "Building index num_trees = " << n_trees << " ..." << std::endl;
	t_start = std::chrono::high_resolution_clock::now();
	t.build(n_trees);
	t_end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>( t_end - t_start ).count();
	std::cout << "Build Index Done in "<< duration << " secs." << std::endl;


	std::cout << "Saving index ...";
	t.save("precision.tree");
	std::cout << "Save Done" << std::endl;



	//******************************************************
	std::vector<int> results;
	t_start = std::chrono::high_resolution_clock::now();
	for (auto i = 0; i < query_times; ++ i) {
		int j = rand() % n;
		results.resize(top_k);
		t.get_nns_by_item(j, top_k, search_k, &results, nullptr);
		results.clear();
	}
	t_end = std::chrono::high_resolution_clock::now();
	auto query_duration = std::chrono::duration_cast<std::chrono::seconds>( t_end - t_start ).count();
	std::cout << "Query Done in " << query_duration << " secs. of " << query_times << " times query" << std::endl;

	/*
	std::vector<int> limits = {10, 100, 1000, 10000};
	int K=10;
	int prec_n = 1000;
	std::chrono::high_resolution_clock::time_point q_start, q_end;

	std::map<int, double> prec_sum;
	std::map<int, double> time_sum;
	std::vector<int> closest;

	//init precision and timers map
	for(std::vector<int>::iterator it = limits.begin(); it!=limits.end(); ++it){
		prec_sum[(*it)] = 0.0;
		time_sum[(*it)] = 0.0;
	}

	// doing the work
	for(int i=0; i<prec_n; ++i){

		//select a random node
		int j = rand() % n;

		std::cout << "finding nbs for " << j << std::endl;

		// getting the K closest
		t.get_nns_by_item(j, K, n, &closest, nullptr);

		std::vector<int> toplist;
		std::vector<int> intersection;

		for(std::vector<int>::iterator limit = limits.begin(); limit!=limits.end(); ++limit){

			t_start = std::chrono::high_resolution_clock::now();
			t.get_nns_by_item(j, (*limit), (size_t) -1, &toplist, nullptr); //search_k defaults to "n_trees * n" if not provided.
			t_end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t_end - t_start ).count();

			//intersecting results
			std::sort(closest.begin(), closest.end(), std::less<int>());
			std::sort(toplist.begin(), toplist.end(), std::less<int>());
			intersection.resize(std::max(closest.size(), toplist.size()));
			std::vector<int>::iterator it_set = std::set_intersection(closest.begin(), closest.end(), toplist.begin(), toplist.end(), intersection.begin());
			intersection.resize(it_set-intersection.begin());

			// storing metrics
			int found = intersection.size();
			double hitrate = found / (double) K;
			prec_sum[(*limit)] += hitrate;

			time_sum[(*limit)] += duration;


			//deallocate memory
			vector<int>().swap(intersection);
			vector<int>().swap(toplist);
		}

		//print resulting metrics
		for(std::vector<int>::iterator limit = limits.begin(); limit!=limits.end(); ++limit){
			std::cout << "limit: " << (*limit) << "\tprecision: "<< std::fixed << std::setprecision(2) << (100.0 * prec_sum[(*limit)] / (i + 1)) << "% \tavg. time: "<< std::fixed<< std::setprecision(6) << (time_sum[(*limit)] / (i + 1)) * 1e-04 << "s" << std::endl;
		}

		closest.clear(); vector<int>().swap(closest);

	}
	*/

	std::cout << "\nTest Done" << std::endl;
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
	else if(argc == 7){

		f = atoi(argv[1]);
		n = atoi(argv[2]);
		n_trees = atoi(argv[3]);
		search_k = atoi(argv[4]);
		int query_times = atoi(argv[5]);
		int top_k = atoi(argv[6]);

		feedback(f,n, n_trees, search_k);

		precision(f, n, n_trees, search_k, query_times, top_k);
	}
	else {
		help();
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}
