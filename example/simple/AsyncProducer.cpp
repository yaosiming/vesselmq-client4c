// Producer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <thread>
#include <SendCallback.h>
#include <DefaultMQProducer.h>
#include <MQClientException.h>

inline void MySleep(long millis) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

void Usage(const char *program) {
    printf("Usage:%s [-n] [-c] [-v]\n", program);
    printf("\t -n ip:port\n");
    printf("\t -c message count\n");
    printf("\t -v message size \n");
}

class SampleSendCallback : public SendCallback {
public:
    void onSuccess(SendResult& sendResult) {
        std::cout << "MsgId: " << sendResult.getMsgId()
        <<", Queue Id: " << sendResult.getMessageQueue().getQueueId()
        << ", Send Status: " << sendResult.getSendStatus() << std::endl;
    }

    void onException(MQException& e) {
        std::cout << "Message delivery failed, cause: " << e.what() << std::endl;
    }

    virtual ~SampleSendCallback() {
        std::cout << "~Ctor invoked" << std::endl;
    };
};

int main(int argc, char *argv[]) {
    int count = 100;
    int size = 32;
    std::string* name_server_list = nullptr;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 < argc) {
                name_server_list = new std::string(argv[i + 1]);
                i++;
            } else {
                Usage(argv[0]);
                return 0;
            }

        } else if (strcmp(argv[i], "-c") == 0) {
            if (i + 1 < argc) {
                count = atoi(argv[i + 1]);
                i++;
            } else {
                Usage(argv[0]);
                return 0;
            }
        } else if (strcmp(argv[i], "-v") == 0) {
            if (i + 1 < argc) {
                size = atoi(argv[i + 1]);
                i++;
            } else {
                Usage(argv[0]);
                return 0;
            }
        } else {
            Usage(argv[0]);
            return 0;
        }
    }

    DefaultMQProducer producer("PG_CppClient");

    if (name_server_list != nullptr) {
        producer.setNamesrvAddr(*name_server_list);
    }

    producer.start();
    std::unique_ptr<SampleSendCallback> ptrSendCallback(new SampleSendCallback());

    std::string tags[] = {"TagA", "TagB", "TagC", "TagD", "TagE"};

    char key[16];
    std::string value("Hello Cpp Client");

    for (int i = 0; i < count; i++) {
        try {
            sprintf(key, "KEY%d", i);
            Message msg("TopicTest",// topic
                        tags[i % 5],// tag
                        key,// key
                        value.c_str(),// body
                        value.size());
            producer.send(msg, ptrSendCallback.get());
        }
        catch (MQClientException &e) {
            std::cout << e << std::endl;
            MySleep(3000);
        }
    }

    MySleep(30 * 1000);
    producer.shutdown();
    return 0;
}

