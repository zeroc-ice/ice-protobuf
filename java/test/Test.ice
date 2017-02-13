// **********************************************************************
//
// Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#ifndef TEST_ICE
#define TEST_ICE

module ProtobufTest
{

["java:protobuf:test.TestPB.Message"] sequence<byte> Message;

class MyClass
{
    void shutdown();

    Message opMessage(Message i, out Message o);

    ["amd"] Message opMessageAMD(Message i, out Message o);
};

// Remaining type definitions are there to verify that the generated
// code compiles correctly.

sequence<Message> SLS;
sequence<SLS> SLSS;
dictionary<int, Message> SLD;
dictionary<int, SLS> SLSD;
struct Foo
{
    Message SLmem;
    SLS SLSmem;
};

exception Bar
{
    Message SLmem;
    SLS SLSmem;
};

class Baz
{
    Message SLmem;
    SLS SLSmem;
};

};

#endif
