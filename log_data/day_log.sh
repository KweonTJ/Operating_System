#!/bin/bash

current_date=$(date +"%Y-%m-%d")

for i in {0..5}; do
    log_date=$(date -d "$current_date -$i day" +"%Y-%m-%d")
    touch "$log_date.log"
    echo "$log_date.log"
done

