#!/usr/bin/env bash

for i in {1..30000..20}; do ./matrix $i 1; done > i\ externoC.csv
for i in {1..30000..20}; do ./matrix $i 2; done  > j\ externoC.csv
for i in {1..30000..20}; do ./matrix2 $i 1; done > i\ externoF.csv
for i in {1..30000..20}; do ./matrix2 $i 0; done > j\ externoF.csv


