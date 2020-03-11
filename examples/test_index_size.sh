#!/bin/sh

./index_size_test 128 1000000 1 10 1 1 > index_nt1.out
ls -l precision.tree >> index_nt1.out
ls -lh precision.tree >> index_nt1.out
echo "---------------------------------------1---------------------------------------------"

./index_size_test 128 1000000 2 10 1 1 > index_nt2.out
ls -l precision.tree >> index_nt2.out
ls -lh precision.tree >> index_nt2.out
echo "---------------------------------------2---------------------------------------------"

./index_size_test 128 1000000 4 10 1 1 > index_nt4.out
ls -l precision.tree >> index_nt4.out
ls -lh precision.tree >> index_nt4.out
echo "---------------------------------------4---------------------------------------------"

./index_size_test 128 1000000 8 10 1 1 > index_nt8.out
ls -l precision.tree >> index_nt8.out
ls -lh precision.tree >> index_nt8.out
echo "---------------------------------------8---------------------------------------------"

./index_size_test 128 1000000 16 10 1 1 > index_nt16.out
ls -l precision.tree >> index_nt16.out
ls -lh precision.tree >> index_nt16.out
echo "---------------------------------------16----------------------------------------------"

./index_size_test 128 1000000 32 10 1 1 > index_nt32.out
ls -l precision.tree >> index_nt32.out
ls -lh precision.tree >> index_nt32.out
echo "----------------------------------------32---------------------------------------------"

./index_size_test 128 1000000 64 10 1 1 > index_nt64.out
ls -l precision.tree >> index_nt64.out
ls -lh precision.tree >> index_nt64.out
echo "-----------------------------------------64--------------------------------------------"

./index_size_test 128 1000000 128 10 1 1 > index_nt128.out
ls -l precision.tree >> index_nt128.out
ls -lh precision.tree >> index_nt128.out
echo "------------------------------------------128-------------------------------------------"

./index_size_test 128 1000000 256 10 1 1 > index_nt256.out
ls -l precision.tree >> index_nt256.out
ls -lh precision.tree >> index_nt256.out
echo "------------------------------------------256-----------------------------------------"

