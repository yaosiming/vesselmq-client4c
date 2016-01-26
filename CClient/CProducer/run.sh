#!/bin/sh

g++ -rdynamic -s -o CClientProducer CClientProducer.c -I ../../include/  /usr/lib/libCDefaultMQProducerWapper.so 

