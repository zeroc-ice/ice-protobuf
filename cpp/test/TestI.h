// **********************************************************************
//
// Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#ifndef TEST_I_H
#define TEST_I_H

#include <Test.h>

class MyClassI : virtual public Test::MyClass
{
public:

    virtual void shutdown(const Ice::Current&);

    virtual test::Message opMessage(const test::Message&, test::Message&, const Ice::Current&);
    virtual void opMessageAMD_async(const Test::AMD_MyClass_opMessageAMDPtr&, const test::Message&,
                                    const Ice::Current&);
};

#endif
