#!/bin/bash
taskset 0x1 ./TEST &
taskset 0x2 ./TEST &
taskset 0x4 ./TEST &
taskset 0x8 ./TEST &
