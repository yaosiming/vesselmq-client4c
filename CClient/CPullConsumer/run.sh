#!/bin/sh

g++ -rdynamic -s -o CPullConsumer CPullConsumer.c -I ../../include/  /usr/lib/libCPullConsumerWapper.so

