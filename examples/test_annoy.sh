#!/bin/sh

n_trees=100
search_k=100
top_k=1
query_time=5
FILE_DIR="/Users/ophunter/Documents/workspace/annoy/examples/test_result/"
EXE_NAME="nat"

echo "------------------------------------------------------------------------------"
echo "the 1th test args:"
FILE_NAME="nt"${n_trees}"_sk"${search_k}"_tk"${top_k}"_qt"${query_time}".out"
echo "n_trees = "${n_trees}" search_k = "${search_k}" top_k = "${top_k}" query_time = "${query_time}" file_name = "${FILE_NAME}
./xnat 128 1000000 ${n_trees} ${search_k} ${query_time} ${top_k} > ${FILE_NAME}

search_k=1000
echo "------------------------------------------------------------------------------"
echo "the 2th test args:"
FILE_NAME="nt"${n_trees}"_sk"${search_k}"_tk"${top_k}"_qt"${query_time}".out"
echo "n_trees = "${n_trees}" search_k = "${search_k}" top_k = "${top_k}" query_time = "${query_time}" file_name = "${FILE_NAME}
./xnat 128 1000000 ${n_trees} ${search_k} ${query_time} ${top_k} > ${FILE_NAME}

search_k=10000
echo "------------------------------------------------------------------------------"
echo "the 3th test args:"
FILE_NAME="nt"${n_trees}"_sk"${search_k}"_tk"${top_k}"_qt"${query_time}".out"
echo "n_trees = "${n_trees}" search_k = "${search_k}" top_k = "${top_k}" query_time = "${query_time}" file_name = "${FILE_NAME}
./xnat 128 1000000 ${n_trees} ${search_k} ${query_time} ${top_k} > ${FILE_NAME}

search_k=100000
echo "------------------------------------------------------------------------------"
echo "the 4th test args:"
FILE_NAME="nt"${n_trees}"_sk"${search_k}"_tk"${top_k}"_qt"${query_time}".out"
echo "n_trees = "${n_trees}" search_k = "${search_k}" top_k = "${top_k}" query_time = "${query_time}" file_name = "${FILE_NAME}
./xnat 128 1000000 ${n_trees} ${search_k} ${query_time} ${top_k} > ${FILE_NAME}

query_time=1
echo "------------------------------------------------------------------------------"
echo "the 5th test args:"
FILE_NAME="nt"${n_trees}"_sk"${search_k}"_tk"${top_k}"_qt"${query_time}".out"
echo "n_trees = "${n_trees}" search_k = "${search_k}" top_k = "${top_k}" query_time = "${query_time}" file_name = "${FILE_NAME}
./xnat 128 1000000 ${n_trees} ${search_k} ${query_time} ${top_k} > ${FILE_NAME}

query_time=10
echo "------------------------------------------------------------------------------"
echo "the 6th test args:"
FILE_NAME="nt"${n_trees}"_sk"${search_k}"_tk"${top_k}"_qt"${query_time}".out"
echo "n_trees = "${n_trees}" search_k = "${search_k}" top_k = "${top_k}" query_time = "${query_time}" file_name = "${FILE_NAME}
./xnat 128 1000000 ${n_trees} ${search_k} ${query_time} ${top_k} > ${FILE_NAME}

query_time=100
echo "------------------------------------------------------------------------------"
echo "the 7th test args:"
FILE_NAME="nt"${n_trees}"_sk"${search_k}"_tk"${top_k}"_qt"${query_time}".out"
echo "n_trees = "${n_trees}" search_k = "${search_k}" top_k = "${top_k}" query_time = "${query_time}" file_name = "${FILE_NAME}
./xnat 128 1000000 ${n_trees} ${search_k} ${query_time} ${top_k} > ${FILE_NAME}

query_time=1000
echo "------------------------------------------------------------------------------"
echo "the 8th test args:"
FILE_NAME="nt"${n_trees}"_sk"${search_k}"_tk"${top_k}"_qt"${query_time}".out"
echo "n_trees = "${n_trees}" search_k = "${search_k}" top_k = "${top_k}" query_time = "${query_time}" file_name = "${FILE_NAME}
./xnat 128 1000000 ${n_trees} ${search_k} ${query_time} ${top_k} > ${FILE_NAME}

query_time=10000
echo "------------------------------------------------------------------------------"
echo "the 9th test args:"
FILE_NAME="nt"${n_trees}"_sk"${search_k}"_tk"${top_k}"_qt"${query_time}".out"
echo "n_trees = "${n_trees}" search_k = "${search_k}" top_k = "${top_k}" query_time = "${query_time}" file_name = "${FILE_NAME}
./xnat 128 1000000 ${n_trees} ${search_k} ${query_time} ${top_k} > ${FILE_NAME}

#query_time=100000
#echo "------------------------------------------------------------------------------"
#echo "the 10th test args:"
#FILE_NAME="nt"${n_trees}"_sk"${search_k}"_tk"${top_k}"_qt"${query_time}".out"
#echo "n_trees = "${n_trees}" search_k = "${search_k}" top_k = "${top_k}" query_time = "${query_time}" file_name = "${FILE_NAME}
#./nat 128 1000000 ${n_trees} ${search_k} ${query_time} ${top_k} > ${FILE_NAME}

#query_time=1000000
#echo "------------------------------------------------------------------------------"
#echo "the 11th test args:"
#FILE_NAME="nt"${n_trees}"_sk"${search_k}"_tk"${top_k}"_qt"${query_time}".out"
#echo "n_trees = "${n_trees}" search_k = "${search_k}" top_k = "${top_k}" query_time = "${query_time}" file_name = "${FILE_NAME}
#./nat 128 1000000 ${n_trees} ${search_k} ${query_time} ${top_k} > ${FILE_NAME}
#
