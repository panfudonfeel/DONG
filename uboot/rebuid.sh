#!/bin/bash
source ../kernel_v1/evn.sh
make clean
make smdk6410_config
make
