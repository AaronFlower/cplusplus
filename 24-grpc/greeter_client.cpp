//
// Created by eason on 2019/11/14.
//

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "protos/helloworld.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

class GreeterClient {
public:
    GreeterClient(std::shared_ptr<Channel> channel)
        :stub_(Greeter::NewStub(channel)) {

    }

    std::string SayHello(const std::string& user) {
        HelloRequest request;
        request.set_name(user);

        HelloReply reply;

        ClientContext context;

        Status status = stub_->SayHello(&context, request, &reply);

        if (status.ok()) {
            return reply.message();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                        << std::endl;
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint (in this case,
    // localhost at port 50051). We indicate that channel isn't authenticated
    // (use of InsecureChannelCredentials()).
    std::string target_endpoint("localhost:50051");
    GreeterClient greeter(grpc::CreateChannel(target_endpoint, grpc::InsecureChannelCredentials()));

    std::string user("my lord world");
    std::string reply = greeter.SayHello(user);
    std::cout << "Greeter received:" << reply << std::endl;
    return 0;
}




