#!/bin/sh

g++ -rdynamic -s -o CPushconsumer CPushconsumer.c -I ../../include/  /usr/lib/libCPushConsumerWapper.so

