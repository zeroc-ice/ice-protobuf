// **********************************************************************
//
// Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#ifndef HELLO_ICE
#define HELLO_ICE

[["cpp:include:Person.pb.h"]]
[["cpp:include:StreamProtobuf.h"]]

module Demo
{

["cpp:type:tutorial::Person"] sequence<byte> Person;

interface Hello
{
    idempotent void sayHello(Person p);
    void shutdown();
};

};

#endif
